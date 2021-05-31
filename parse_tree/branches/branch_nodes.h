#ifndef __CONTROL_NODES_H_
#define __CONTROL_NODES_H_

#include "../basic_nodes.h"
#include "../statements/statement_nodes.h"
#include "../expressions/expression_nodes.h"

class IfNode : public StatementNode {
    public : 
    ExpressionNode* cond;
    StatementNode* ifBody;
    StatementNode* elseBody;

    IfNode(const Location& loc, ExpressionNode* cond, StatementNode* ifBody, StatementNode* elseBody = NULL)
            : StatementNode(loc) {
        this->cond = cond;
        this->ifBody = ifBody;
        this->elseBody = elseBody;
    }

    virtual ~IfNode() {
        if (cond) delete cond;
        if (ifBody) delete ifBody;
        if (elseBody) delete elseBody;
    }

    virtual bool analyze(ScopeContext* context);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        string ret = string(ind, ' ') + "if (" + cond->toString() + ")\n";
        ret += ifBody->toString(ind + (dynamic_cast<BlockNode*>(ifBody) ? 0 : 4));

        if (elseBody) {
            ret += "\n" + string(ind, ' ') + "else\n";
            ret += elseBody->toString(ind + (dynamic_cast<BlockNode*>(elseBody) ? 0 : 4));
        }

        return ret;
    }
};

class CaseLabelNode : public StatementNode {
    public : 
    ExpressionNode* expr;
    StatementNode* stmt;

    CaseLabelNode(const Location& loc, ExpressionNode* expr, StatementNode* stmt) : StatementNode(loc) {
        this->expr = expr;
        this->stmt = stmt;
    }

    virtual ~CaseLabelNode() {
        if (expr) delete expr;
        if (stmt) delete stmt;
    }

    virtual bool analyze(ScopeContext* context);

    virtual string toString(int ind = 0) {
        string ret = string(max(0, ind - 4), ' ') + (expr ? "case " + expr->toString() + ":\n" : "default:\n");
        ret += stmt->toString(ind);
        return ret;
    }
};

class SwitchNode : public StatementNode {
    public : 
    ExpressionNode* cond;
    StatementNode* body;

    bool hasDefaultLabel = false;                   
    unordered_map<int, CaseLabelNode*> caseMap;     
    ExprList caseLabels;                            
    vector<StmtList> caseStmts;                     
    VarList initializedVars;                       


    SwitchNode(const Location& loc, ExpressionNode* cond, StatementNode* body) : StatementNode(loc) {
        this->cond = cond;
        this->body = body;
    }

    virtual ~SwitchNode() {
        if (cond) delete cond;
        if (body) delete body;
    }

    virtual void populate() {
        BlockNode* block = dynamic_cast<BlockNode*>(body);

        if (block == NULL) {
            addCaseBlock(body);
            return;
        }

        for (int i = 0; i < block->statements.size(); ++i) {
            addCaseBlock(block->statements[i]);
        }
    }

    virtual void addCaseBlock(StatementNode* stmt) {
        CaseLabelNode* caseLabel;

        while (caseLabel = dynamic_cast<CaseLabelNode*>(stmt)) {
            caseLabels.push_back(caseLabel->expr);
            caseStmts.push_back(StmtList());

            stmt = caseLabel->stmt;
        }

        if (caseStmts.size() > 0) {
            caseStmts.back().push_back(stmt);
        }
    }

    virtual bool analyze(ScopeContext* context);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        string ret = string(ind, ' ') + "switch (" + cond->toString() + ")\n";
        ret += body->toString(ind + (dynamic_cast<BlockNode*>(body) ? 0 : 4));
        return ret;
    }
};

class WhileNode : public StatementNode {
    public:
    ExpressionNode* cond;
    StatementNode* body;

    WhileNode(const Location& loc, ExpressionNode* cond, StatementNode* body) : StatementNode(loc) {
        this->cond = cond;
        this->body = body;
    }

    virtual ~WhileNode() {
        if (cond) delete cond;
        if (body) delete body;
    }

    virtual bool analyze(ScopeContext* context);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        string ret = string(ind, ' ') + "while (" + cond->toString() + ") \n";
        ret += body->toString(ind + (dynamic_cast<BlockNode*>(body) ? 0 : 4));
        return ret;
    }
};

class RepeatUntilNode : public StatementNode {
    public:
    ExpressionNode* cond;
    StatementNode* body;

    RepeatUntilNode(const Location& loc, ExpressionNode* cond, StatementNode* body) : StatementNode(loc) {
        this->cond = cond;
        this->body = body;
    }

    virtual ~RepeatUntilNode() {
        if (cond) delete cond;
        if (body) delete body;
    }

    virtual bool analyze(ScopeContext* context);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        string ret = string(ind, ' ') + "do\n";
        ret += body->toString(ind + (dynamic_cast<BlockNode*>(body) ? 0 : 4)) + "\n";
        ret += string(ind, ' ') + "while (" + cond->toString() + ");";
        return ret;
    }
};

class ForNode : public StatementNode {
    public:
    StatementNode* initStmt;
    ExpressionNode* cond;
    ExpressionNode* inc;
    StatementNode* body;

    ForNode(const Location& loc, StatementNode* initStmt, ExpressionNode* cond, ExpressionNode* inc,
            StatementNode* body) : StatementNode(loc) {
        this->initStmt = initStmt;
        this->cond = cond;
        this->inc = inc;
        this->body = body;
    }

    virtual ~ForNode() {
        if (initStmt) delete initStmt;
        if (cond) delete cond;
        if (inc) delete inc;
        if (body) delete body;
    }

    virtual bool analyze(ScopeContext* context);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        string ret = string(ind, ' ') + "for (";
        ret += (initStmt ? initStmt->toString() : "") + ";";
        ret += (cond ? cond->toString() : "") + ";";
        ret += (inc ? inc->toString() : "") + ")\n";
        ret += body->toString(ind + (dynamic_cast<BlockNode*>(body) ? 0 : 4));
        return ret;
    }
};

class BreakStmtNode : public StatementNode {
    public:

    BreakStmtNode(const Location& loc) : StatementNode(loc) {}

    virtual bool analyze(ScopeContext* context);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        return string(ind, ' ') + "break";
    }
};

class ContinueStmtNode : public StatementNode {
    public:

    ContinueStmtNode(const Location& loc) : StatementNode(loc) {}

    virtual bool analyze(ScopeContext* context);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        return string(ind, ' ') + "continue";
    }
};

#endif