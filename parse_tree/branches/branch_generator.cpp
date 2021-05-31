#include "../parse_tree.h"
#include "../../manager/quadrubles_generator.h"


string IfNode::generateQuad(quadrublesGenerator* context) {
    string ret;
    int label1 = context->labelCounter++;

    ret += cond->generateQuad(context);
    ret += utils.operationToQuadrables(JZ, cond->type) + " L" + to_string(label1) + "\n";
    ret += ifBody->generateQuad(context);

    if (elseBody) {
        int label2 = context->labelCounter++;

        ret += utils.operationToQuadrables(JMP) + " L" + to_string(label2) + "\n";
        ret += "L" + to_string(label1) + ":\n";
        ret += elseBody->generateQuad(context);
        ret += "L" + to_string(label2) + ":\n";
    }
    else {
        ret += "L" + to_string(label1) + ":\n";
    }

    return ret;
}

string SwitchNode::generateQuad(quadrublesGenerator* context) {
    string ret;
    vector<pair<int, int>> labelPairs;
    int defaultLabel = -1;
    int breakLabel = context->labelCounter++;

    ret += cond->generateQuad(context);
    ret += utils.operationToQuadrables(POP, cond->type) + " SWITCH_COND@" + to_string(breakLabel) + "\n";
    context->breakLabels.push(breakLabel);

    for (int i = 0; i < caseLabels.size(); i++) {
        int label1 = context->labelCounter++;
        if (caseLabels[i] == NULL) {
            defaultLabel = label1;
            labelPairs.push_back({-1, label1});
        }
        else {
            int label2 = context->labelCounter++;
            labelPairs.push_back({label1, label2});
        }
    }

    for (int i = 0; i < caseLabels.size(); i++) {
        if (caseLabels[i]) {
            if (i > 0) {
                ret += utils.operationToQuadrables(JMP) + " L" + to_string(labelPairs[i].second) + "\n";
            }

            dataTypes resultType = max(cond->type, caseLabels[i]->type);

            ret += "L" + to_string(labelPairs[i].first) + ":\n";
            ret += utils.operationToQuadrables(PUSH, cond->type) + " SWITCH_COND@" + to_string(context->breakLabels.top()) + "\n";
            ret += utils.dtypeConvQuad(cond->type, resultType);
            ret += utils.operationToQuadrables(PUSH, caseLabels[i]->type) + " " + to_string(caseLabels[i]->getConstIntValue()) + "\n";
            ret += utils.dtypeConvQuad(caseLabels[i]->type, resultType);
            ret += utils.operationToQuadrables(EQ, resultType) + "\n";
            ret += utils.operationToQuadrables(JZ, BOOL) + " L";

            if (i == caseLabels.size() - 1) {               // my case label is last
                ret += (hasDefaultLabel ? to_string(defaultLabel) : to_string(breakLabel)) + "\n";
            }
            else if (labelPairs[i + 1].first == -1) {       // my next label is default
                ret += ((i + 1 == caseLabels.size() - 1) ? to_string(defaultLabel) : to_string(labelPairs[i + 2].first)) + "\n";
            }
            else {                                          // my next is case
                ret += to_string(labelPairs[i + 1].first) + "\n";
            }
        }

        ret += "L" + to_string(labelPairs[i].second) + ":\n";

        for (int j = 0;j < caseStmts[i].size();j++) {
            ret += caseStmts[i][j]->generateQuad(context);
        }
    }

    context->breakLabels.pop();
    ret += "L" + to_string(breakLabel) + ":\n";

    return ret;
}

string WhileNode::generateQuad(quadrublesGenerator* context) {
    string ret;
    int label1 = context->labelCounter++;
    int label2 = context->labelCounter++;

    ret += "L" + to_string(label1) + ":\n";
    ret += cond->generateQuad(context);
    ret += utils.operationToQuadrables(JZ, cond->type) + " L" + to_string(label2) + "\n";

    context->breakLabels.push(label2);
    context->continueLabels.push(label1);

    ret += body->generateQuad(context);

    context->breakLabels.pop();
    context->continueLabels.pop();

    ret += utils.operationToQuadrables(JMP) + " L" + to_string(label1) + "\n";
    ret += "L" + to_string(label2) + ":\n";

    return ret;
}

string RepeatUntilNode::generateQuad(quadrublesGenerator* context) {
    string ret;
    int label1 = context->labelCounter++;
    int label2 = context->labelCounter++;
    int label3 = context->labelCounter++;

    ret += "L" + to_string(label1) + ":\n";

    context->breakLabels.push(label3);
    context->continueLabels.push(label2);

    ret += body->generateQuad(context);

    context->continueLabels.pop();
    context->breakLabels.pop();

    ret += "L" + to_string(label2) + ":\n";
    ret += cond->generateQuad(context);
    ret += utils.operationToQuadrables(JZ, cond->type) + " L" + to_string(label1) + "\n";
    ret += "L" + to_string(label3) + ":\n";

    return ret;
}

string ForNode::generateQuad(quadrublesGenerator* context) {
    string ret;
    int label1 = context->labelCounter++;
    int label2 = context->labelCounter++;
    int label3 = context->labelCounter++;

    if (initStmt) {
        ret += initStmt->generateQuad(context);
    }

    ret += "L" + to_string(label1) + ":\n";

    if (cond) {
        ret += cond->generateQuad(context);
        ret += utils.operationToQuadrables(JZ, cond->type) + " L" + to_string(label3) + "\n";
    }

    context->breakLabels.push(label3);
    context->continueLabels.push(label2);

    ret += body->generateQuad(context);

    context->continueLabels.pop();
    context->breakLabels.pop();

    ret += "L" + to_string(label2) + ":\n";

    if (inc) {
        ret += inc->generateQuad(context);
    }

    ret += utils.operationToQuadrables(JMP) + " L" + to_string(label1) + "\n";
    ret += "L" + to_string(label3) + ":\n";

    return ret;
}

string BreakStmtNode::generateQuad(quadrublesGenerator* context) {
    return utils.operationToQuadrables(JMP) + " L" + to_string(context->breakLabels.top()) + "\n";
}

string ContinueStmtNode::generateQuad(quadrublesGenerator* context) {
    return utils.operationToQuadrables(JMP) + " L" + to_string(context->continueLabels.top()) + "\n";
}