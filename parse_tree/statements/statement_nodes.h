#ifndef __STATEMENT_NODES_H_
#define __STATEMENT_NODES_H_

#include "../basic_nodes.h"
#include "../expressions/expression_nodes.h"


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

#endif