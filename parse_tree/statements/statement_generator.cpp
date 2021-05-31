#include "../parse_tree.h"
#include "../../manager/quadrubles_generator.h"


string BlockNode::generateQuad(quadrublesGenerator* context) {
    string ret;

    for (int i = 0; i < statements.size(); ++i) {
        ret += statements[i]->generateQuad(context);
    }
    
    return ret;
}

string VarDeclarationNode::generateQuad(quadrublesGenerator* context) {
    string ret;

    if (value) {
        ret += value->generateQuad(context);
        ret += utils.dtypeConvQuad(value->type, type->type);
    }

    if (value || context->declareFuncParams) {
        ret += utils.operationToQuadrables(POP, type->type) + " " + alias + "\n";
    }

    return ret;
}

string MultiVarDeclarationNode::generateQuad(quadrublesGenerator* context) {
    string ret;

    for (int i = 0; i < vars.size(); ++i) {
        ret += vars[i]->generateQuad(context);
    }

    return ret;
}