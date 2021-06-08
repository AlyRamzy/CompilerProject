#ifndef __NODES_H_
#define __NODES_H_

#include <iostream>
#include <string>

#include "utils.h"

class ScopeContext;
class quadrublesGenerator;

class Node;
class StatementNode;
class DeclarationNode;
class VarDeclarationNode;
class FunctionNode;
class ExpressionNode;
class IdentifierNode;
class TypeNode;

typedef vector<Node*> NodeList;
typedef vector<StatementNode*> StmtList;
typedef vector<VarDeclarationNode*> VarList;
typedef vector<ExpressionNode*> ExprList;



/* ------------------------ Basic nodes -----------------*/

class Node {
public:
    Location loc;
    Utils utils;

    Node() {}

    Node(const Location& loc) {
        this->loc = loc;
    }

    virtual ~Node() {}

    virtual bool analyze(ScopeContext* context) {
        return true;
    }

    virtual string generateQuad(quadrublesGenerator* context) {
        return "";
    }

    virtual string toString() {
        return "";
    }
};

class StatementNode : public Node {
public:
    StatementNode() {}

    StatementNode(const Location& loc) : Node(loc) {}

    virtual string toString(int ind = 0) {
        return string(ind, ' ') + ";" ;
    }
};

class DeclarationNode : public StatementNode {
public:
    TypeNode* type;
    IdentifierNode* ident;

    string alias;                       
    int used = 0;                       
    bool initialized = false;           

    DeclarationNode(const Location& loc) : StatementNode(loc) {}

    virtual string declaredHeader() = 0;

    virtual string declaredType() = 0;
};

class ExpressionNode : public StatementNode {
public:
    dataTypes type = ERROR;        
    DeclarationNode* reference = NULL;  
    bool constant = false;              
    bool used = false;                  

    ExpressionNode() {}

    ExpressionNode(const Location& loc) : StatementNode(loc) {}

    virtual int getConstIntValue() {
        return -1;
    }
    
    virtual bool analyze(ScopeContext* context) {
        return analyze(context, false);
    }

    virtual bool analyze(ScopeContext* context, bool valueUsed) {
        used = valueUsed;
        return true;
    }

    virtual string exprTypeStr() {
        return reference ? reference->declaredType() : utils.dtypeToStr(type);
    }
};

class TypeNode : public Node {
    public :
    dataTypes type;
    TypeNode(const Location& loc, dataTypes type) : Node(loc) {
        this->type = type;
    }

    virtual string toString(int ind = 0) {
        return string(ind, ' ') + utils.dtypeToStr(type);
    }
};

class ErrorNode : public StatementNode {
    public :
    string what;

    ErrorNode(const Location& loc, const string& what) : StatementNode(loc) {
        this->what = what;
        this->loc.pos -= this->loc.len - 1;
    }

    virtual bool analyze(ScopeContext* context);

    virtual string toString(int ind) {
        return string(ind, ' ') + ">> ERROR" ;
    }
};

/* ------------------------ expression nodes ---------------------*/

class ExpressionContainerNode : public ExpressionNode {
    public :
    ExpressionNode* expr;

    ExpressionContainerNode(const Location& loc, ExpressionNode* expr) : ExpressionNode(loc) {
        this->expr = expr;
    }

    virtual ~ExpressionContainerNode() {
        if (expr) delete expr;
    }

    virtual int getConstIntValue() {
        return expr->getConstIntValue();
    }

    virtual bool analyze(ScopeContext* context, bool valueUsed);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        return expr->toString(ind);
    }
};

class AssignmentOperationNode : public ExpressionNode {
    public :
    ExpressionNode* lhs;
    ExpressionNode* rhs;

    AssignmentOperationNode(const Location& loc, ExpressionNode* lhs, ExpressionNode* rhs) : ExpressionNode(loc) {
        this->lhs = lhs;
        this->rhs = rhs;
    }

    virtual ~AssignmentOperationNode() {
        if (lhs) delete lhs;
        if (rhs) delete rhs;
    }

    virtual bool analyze(ScopeContext* context, bool valueUsed);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        return string(ind, ' ') + "(" + lhs->toString() + " = " + rhs->toString() + ")";
    }
};

class BinaryOperationNode : public ExpressionNode {
    public:
    operations opr;
    ExpressionNode* lhs;
    ExpressionNode* rhs;

    BinaryOperationNode(const Location& loc, operations opr, ExpressionNode* lhs, ExpressionNode* rhs) : ExpressionNode(loc) {
        this->opr = opr;
        this->lhs = lhs;
        this->rhs = rhs;
    }

    virtual ~BinaryOperationNode() {
        if (lhs) delete lhs;
        if (rhs) delete rhs;
    }

    virtual int getConstIntValue();

    virtual bool analyze(ScopeContext* context, bool valueUsed);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string getOpr() {
        return "binary operator '" + utils.oprToString(opr) + "'";
    }

    virtual string toString(int ind = 0) {
        return string(ind, ' ') + "(" + lhs->toString() + " " + utils.oprToString(opr) + " " + rhs->toString() + ")";
    }
};

class UnaryOperationNode : public ExpressionNode {
    public :
    operations opr;
    ExpressionNode* expr;

    UnaryOperationNode(const Location& loc, operations opr, ExpressionNode* expr) : ExpressionNode(loc) {
        this->opr = opr;
        this->expr = expr;
    }

    virtual ~UnaryOperationNode() {
        if (expr) delete expr;
    }

    virtual int getConstIntValue();

    virtual bool analyze(ScopeContext* context, bool valueUsed);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string getOpr() {
        return "unary operator '" + utils.oprToString(opr) + "'";
    }

    virtual string toString(int ind = 0) {
        string ret = string(ind, ' ') + "(";
        
        ret += utils.oprToString(opr) + expr->toString();

        ret += ")";
        return ret;
    }
};

class IdentifierNode : public ExpressionNode {
    public :
    string name;

    IdentifierNode(const Location& loc, const char* name) : ExpressionNode(loc) {
        this->name = name;
    }

    virtual int getConstIntValue();

    virtual bool analyze(ScopeContext* context, bool valueUsed);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        return string(ind, ' ') + name;
    }
};

class ValueNode : public ExpressionNode {
    public:
    string value;

    ValueNode(const Location& loc, dataTypes type, const char* value) : ExpressionNode(loc) {
        this->type = type;
        this->value = value;
        this->constant = true;
    }

    virtual int getConstIntValue();

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        return string(ind, ' ') + value;
    }
};

/*-------------------------- statement nodes -----------------------------*/


class BlockNode : public StatementNode {
    public:
    StmtList statements;

    BlockNode() {}

    BlockNode(const Location& loc) : StatementNode(loc) {}

    BlockNode(const Location& loc, const StmtList& statements) : StatementNode(loc) {
        this->statements = statements;
    }

    virtual ~BlockNode() {
        for (int i = 0; i < statements.size(); ++i) {
            delete statements[i];
        }
    }

    virtual bool analyze(ScopeContext* context);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        string ret = string(ind, ' ') + "{\n";
        for (int i = 0; i < statements.size(); ++i) {
            ret += statements[i]->toString(ind + 4) + "\n";
        }
        ret += string(ind, ' ') + "}";
        return ret;
    }
};

class VarDeclarationNode : public DeclarationNode {
    public : 
    ExpressionNode* value;
    bool constant;

    VarDeclarationNode(TypeNode* type, IdentifierNode* ident, ExpressionNode* value = NULL, bool constant = false)
            : DeclarationNode(type->loc) {
        this->type = type;
        this->ident = ident;
        this->value = value;
        this->constant = constant;
        this->initialized = (value != NULL);
    }

    virtual ~VarDeclarationNode() {
        if (type) delete type;
        if (ident) delete ident;
        if (value) delete value;
    }

    virtual bool analyze(ScopeContext* context);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        string ret = string(ind, ' ') + declaredHeader();
        if (value) {
            ret += " = " + value->toString();
        }
        return ret;
    }

    virtual string declaredHeader() {
        return (constant ? "const " : "") + type->toString() + " " + ident->name;
    }

    virtual string declaredType() {
        return (constant ? "const " : "") + type->toString();
    }
};


class EnumDeclarationNode : public DeclarationNode {
    public : 
    VarList paramList;
    int currentValue = 0;
    

    EnumDeclarationNode( const Location& loc,IdentifierNode* ident, const VarList& paramList)
            : DeclarationNode(loc) {
        this->ident = ident;
        this->paramList = paramList;
   
       
    }

    virtual ~EnumDeclarationNode() {
       
        if (ident) delete ident;
        

        for (int i = 0; i < paramList.size(); ++i) {
            delete paramList[i];
        }
    }

    virtual bool analyze(ScopeContext* context);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        string ret = string(ind, ' ')+"(" ;
        for (int i = 0; i < paramList.size(); ++i) {
            ret += (i > 0 ? ", " : "") + paramList[i]->toString();
        }
        ret += ")\n";
        
        return ret;
    }

    virtual string declaredHeader() {
        string ret = type->toString() + " " + "(";
        for (int i = 0; i < paramList.size(); ++i) {
            ret += (i > 0 ? ", " : "") + paramList[i]->type->toString();
        }
        ret += ")";
        return ret;
    }

    virtual string declaredType() {
        string ret = type->toString() + "(*)(";
        for (int i = 0; i < paramList.size(); ++i) {
            ret += (i > 0 ? ", " : "") + paramList[i]->type->toString();
        }
        ret += ")";
        return ret;
    }
};
/* --------------------------- branch nodes -------------------------*/

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

/*-------------------------- function nodes --------------------*/

class FunctionNode : public DeclarationNode {
    public : 
    VarList paramList;
    BlockNode* body;

    FunctionNode(TypeNode* type, IdentifierNode* ident, const VarList& paramList, BlockNode* body)
            : DeclarationNode(type->loc) {
        this->type = type;
        this->ident = ident;
        this->paramList = paramList;
        this->body = body;
        this->initialized = true;
    }

    virtual ~FunctionNode() {
        if (type) delete type;
        if (ident) delete ident;
        if (body) delete body;

        for (int i = 0; i < paramList.size(); ++i) {
            delete paramList[i];
        }
    }

    virtual bool analyze(ScopeContext* context);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        string ret = string(ind, ' ') + type->toString() + " " + ident->toString() + "(";
        for (int i = 0; i < paramList.size(); ++i) {
            ret += (i > 0 ? ", " : "") + paramList[i]->toString();
        }
        ret += ")\n";
        ret += body->toString(ind);
        return ret;
    }

    virtual string declaredHeader() {
        string ret = type->toString() + " " + ident->name + "(";
        for (int i = 0; i < paramList.size(); ++i) {
            ret += (i > 0 ? ", " : "") + paramList[i]->type->toString();
        }
        ret += ")";
        return ret;
    }

    virtual string declaredType() {
        string ret = type->toString() + "(*)(";
        for (int i = 0; i < paramList.size(); ++i) {
            ret += (i > 0 ? ", " : "") + paramList[i]->type->toString();
        }
        ret += ")";
        return ret;
    }
};

class FunctionCallNode : public ExpressionNode {
    public : 
    IdentifierNode* ident;
    ExprList argList;
    FunctionNode* func;

    FunctionCallNode(IdentifierNode* ident, const ExprList& argList) : ExpressionNode(ident->loc) {
        this->ident = ident;
        this->argList = argList;
    }

    virtual ~FunctionCallNode() {
        if (ident) delete ident;

        for (int i = 0; i < argList.size(); ++i) {
            delete argList[i];
        }
    }

    virtual bool analyze(ScopeContext* context, bool valueUsed);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        string ret = string(ind, ' ') + ident->name + "(";
        for (int i = 0; i < argList.size(); ++i) {
            ret += (i > 0 ? ", " : "") + argList[i]->toString();
        }
        ret += ")";
        return ret;
    }
};

class ReturnStmtNode : public StatementNode {
    public:
    ExpressionNode* value;
    FunctionNode* func;

    ReturnStmtNode(const Location& loc, ExpressionNode* value) : StatementNode(loc) {
        this->value = value;
    }

    virtual ~ReturnStmtNode() {
        if (value) delete value;
    }

    virtual bool analyze(ScopeContext* context);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        string ret = string(ind, ' ') + "return";
        if (value) {
            ret += " " + value->toString();
        }
        return ret;
    }
};

#endif