#include "../parse_tree.h"
#include "../../manager/quadrubles_generator.h"


string FunctionNode::generateQuad(quadrublesGenerator* context) {
    string ret;

    ret += "PROC " + alias + "\n";
    context->declareFuncParams = true;

    for (int i = 0; i < paramList.size(); ++i) {
        ret += paramList[i]->generateQuad(context);
    }

    context->declareFuncParams = false;
    ret += body->generateQuad(context);
    ret += "ENDP " + alias + "\n";

    return ret;
}

string FunctionCallNode::generateQuad(quadrublesGenerator* context) {
    string ret;

    for (int i = (int) argList.size() - 1; i >= 0; --i) {
        ret += argList[i]->generateQuad(context);
        ret += utils.dtypeConvQuad(argList[i]->type, func->paramList[i]->type->type);
    }

    ret += "CALL " + func->alias + "\n";

    return ret;
}

string ReturnStmtNode::generateQuad(quadrublesGenerator* context) {
    string ret;

    if (value) {
        ret += value->generateQuad(context);
        ret += utils.dtypeConvQuad(value->type, func->type->type);
    }

    ret += "RET\n";

    return ret;
}