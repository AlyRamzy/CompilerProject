#include "../parse_tree.h"
#include "../../manager/quadrubles_generator.h"


string ExprContainerNode::generateQuad(quadrublesGenerator* context) {
    return expr->generateQuad(context);
}

string AssignOprNode::generateQuad(quadrublesGenerator* context) {
    string ret;

    ret += lhs->generateQuad(context);
    ret += rhs->generateQuad(context);
    ret += utils.dtypeConvQuad(rhs->type, type);
    ret += utils.operationToQuadrables(POP, type) + " " + lhs->reference->alias + "\n";

    if (used) {
        ret += utils.operationToQuadrables(PUSH, type) + " " + lhs->reference->alias + "\n";
    }

    return ret;
}

string BinaryOprNode::generateQuad(quadrublesGenerator* context) {
    string ret;
    
    dataTypes t = max(lhs->type, rhs->type);

    if (used) {
        ret += lhs->generateQuad(context);
        ret += utils.dtypeConvQuad(lhs->type, t);

        ret += rhs->generateQuad(context);
        ret += utils.dtypeConvQuad(rhs->type, t);

        ret += utils.operationToQuadrables(opr, t) + "\n";
    }
    else {
        ret += lhs->generateQuad(context);
        ret += rhs->generateQuad(context);
    }

    return ret;
}

string UnaryOprNode::generateQuad(quadrublesGenerator* context) {
    string ret;
    
    ret += expr->generateQuad(context);

    if (used) {
        ret += utils.dtypeConvQuad(expr->type, type);
    }

    switch (opr) {
        case U_MINUS:
        case NOT:
        case LOGICAL_NOT:
            if (used) {
                ret += utils.operationToQuadrables(opr, type) + "\n";
            }
            break;
    }

    return ret;
}

string IdentifierNode::generateQuad(quadrublesGenerator* context) {
    string ret;
    if (used) {
        ret += utils.operationToQuadrables(PUSH, type) + " " + reference->alias + "\n";;
    }
    return ret;
}

string ValueNode::generateQuad(quadrublesGenerator* context) {
    string ret;
    if (used) {
        ret += utils.operationToQuadrables(PUSH, type) + " " + value + "\n";
    }
    return ret;
}