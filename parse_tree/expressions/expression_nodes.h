#ifndef __OPERATOR_NODES_H_
#define __OPERATOR_NODES_H_

#include "../basic_nodes.h"

class ExprContainerNode : public ExpressionNode {
    public :
    ExpressionNode* expr;

    ExprContainerNode(const Location& loc, ExpressionNode* expr) : ExpressionNode(loc) {
        this->expr = expr;
    }

    virtual ~ExprContainerNode() {
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

class AssignOprNode : public ExpressionNode {
    public :
    ExpressionNode* lhs;
    ExpressionNode* rhs;

    AssignOprNode(const Location& loc, ExpressionNode* lhs, ExpressionNode* rhs) : ExpressionNode(loc) {
        this->lhs = lhs;
        this->rhs = rhs;
    }

    virtual ~AssignOprNode() {
        if (lhs) delete lhs;
        if (rhs) delete rhs;
    }

    virtual bool analyze(ScopeContext* context, bool valueUsed);

    virtual string generateQuad(quadrublesGenerator* context);

    virtual string toString(int ind = 0) {
        return string(ind, ' ') + "(" + lhs->toString() + " = " + rhs->toString() + ")";
    }
};

class BinaryOprNode : public ExpressionNode {
    public:
    operations opr;
    ExpressionNode* lhs;
    ExpressionNode* rhs;

    BinaryOprNode(const Location& loc, operations opr, ExpressionNode* lhs, ExpressionNode* rhs) : ExpressionNode(loc) {
        this->opr = opr;
        this->lhs = lhs;
        this->rhs = rhs;
    }

    virtual ~BinaryOprNode() {
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

class UnaryOprNode : public ExpressionNode {
    public :
    operations opr;
    ExpressionNode* expr;

    UnaryOprNode(const Location& loc, operations opr, ExpressionNode* expr) : ExpressionNode(loc) {
        this->opr = opr;
        this->expr = expr;
    }

    virtual ~UnaryOprNode() {
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

#endif