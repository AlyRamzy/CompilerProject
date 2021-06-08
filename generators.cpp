#include "nodes.h"
#include "manager/quadrubles_generator.h"


/* -------------------------- expression generators ----------------------------*/

string ExpressionContainerNode::generateQuad(quadrublesGenerator* context) {
    return expr->generateQuad(context);
}

string AssignmentOperationNode::generateQuad(quadrublesGenerator* context) {
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

string BinaryOperationNode::generateQuad(quadrublesGenerator* context) {
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

string UnaryOperationNode::generateQuad(quadrublesGenerator* context) {
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

/* ----------------------- statement generators ----------------------*/

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

string EnumDeclarationNode::generateQuad(quadrublesGenerator* context) {
    string ret ; 

    for (int i = 0; i < paramList.size(); ++i) {
        ret += paramList[i]->generateQuad(context);
    }
    return ret;
   
}

/* ------------------------- branch generators --------------------------*/

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

/* -------------------------------- function generators ------------------------*/

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