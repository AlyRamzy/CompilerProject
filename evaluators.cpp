#include "nodes.h"

int BinaryOprNode::getConstIntValue() {
    int l = lhs->getConstIntValue();
    int r = rhs->getConstIntValue();

    switch (opr) {
        case ADD:
            return l + r;
        case SUB:
            return l - r;
        case MUL:
            return l * r;
        case DIV:
            return l / r;
        case MOD:
            return l % r;
        case AND:
            return l & r;
        case OR:
            return l | r;
        case XOR:
            return l ^ r;
        case LOGICAL_AND:
            return l && r;
        case LOGICAL_OR:
            return l || r;
        case GT:
            return l > r;
        case GTE:
            return l >= r;
        case LT:
            return l < r;
        case LTE:
            return l <= r;
        case EQ:
            return l == r;
        case NEQ:
            return l != r;
    }
    return -1;
}

int UnaryOprNode::getConstIntValue() {
    int v = expr->getConstIntValue();

    switch (opr) {
        case U_PLUS:
            return v;
        case U_MINUS:
            return -v;
        case NOT:
            return ~v;
        case LOGICAL_NOT:
            return !v;
    }

    return -1;
}

int IdentifierNode::getConstIntValue() {
    VarDeclarationNode* var = dynamic_cast<VarDeclarationNode*>(reference);

    if (utils.isValidInt(type) && var != NULL && var->initialized) {
        return var->value->getConstIntValue();
    }

    return -1;
}

int ValueNode::getConstIntValue() {
    switch (type) {
        case BOOL:
            return value == "true";
        case CHAR:
            return value[1];
        case INT:
            return atoi(value.c_str());
    }

    return -1;
}
