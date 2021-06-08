#include "nodes.h"
#include "manager/scope_context.h"

/* -------------------- expression analyzers ----------------------*/

bool ExpressionContainerNode::analyze(ScopeContext* context, bool valueUsed) {
    if (!context->initializeVar && context->isGlobalScope()) {
        context->log("expression is not allowed in global scope", loc, LOG_ERROR);
        return false;
    }

    bool ret = expr->analyze(context, valueUsed);

    type = expr->type;
    reference = expr->reference;
    constant = expr->constant;
    used = valueUsed;

    return ret;
}

bool AssignmentOperationNode::analyze(ScopeContext* context, bool valueUsed) {
    if (!(rhs->analyze(context, true) & lhs->analyze(context, false))) {
        // Note that I used a bitwise AND to execute both lhs and rhs expressions
        return false;
    }

    if (lhs->type == FUNC_PTR) {
        context->log("assignment of function '" + lhs->reference->declaredHeader() + "'", lhs->loc, LOG_ERROR);
        return false;
    }
    if (lhs->reference == NULL) {
        context->log("lvalue required as left operand of assignment", lhs->loc, LOG_ERROR);
        return false;
    }
    if (lhs->reference && lhs->constant) {
        context->log("assignment of constant variable '" + lhs->reference->declaredHeader() + "'", lhs->loc, LOG_ERROR);
        return false;
    }
    if (rhs->type == VOID || rhs->type == FUNC_PTR) {
        context->log("invalid conversion from '" + rhs->exprTypeStr() + "' to '" + lhs->exprTypeStr() + "'", rhs->loc, LOG_ERROR);
        return false;
    }

    type = lhs->type;
    reference = lhs->reference;
    constant = lhs->constant;
    used = valueUsed;

    reference->initialized = true;

    return true;
}

bool BinaryOperationNode::analyze(ScopeContext* context, bool valueUsed) {
    if (!(lhs->analyze(context, valueUsed) & rhs->analyze(context, valueUsed))) {
        // Note that I used a bitwise AND to execute both lhs and rhs expressions
        return false;
    }

    if (lhs->type == VOID || lhs->type == FUNC_PTR ||
        rhs->type == VOID || rhs->type == FUNC_PTR ||
        (utils.isBitwise(opr) || opr == MOD) && (lhs->type == FLOAT || rhs->type == FLOAT)) {
        context->log("invalid operands of types '" + lhs->exprTypeStr() + "' and '" + rhs->exprTypeStr() + "' to " +
                     getOpr(), loc, LOG_ERROR);
        return false;
    }

    if (utils.isLogical(opr)) {
        type = BOOL;
    } else {
        type = max(lhs->type, rhs->type);
    }

    constant = (lhs->constant && rhs->constant);
    used = valueUsed;

    return true;
}

bool UnaryOperationNode::analyze(ScopeContext* context, bool valueUsed) {
    if (!expr->analyze(context, valueUsed || utils.isAssign(opr))) {
        return false;
    }

    if (expr->type == VOID || expr ->type == FUNC_PTR ||
        expr->type == FLOAT && utils.isBitwise(opr)) {
        context->log("invalid operand of type '" + expr->exprTypeStr() + "' to " + getOpr(), loc, LOG_ERROR);
        return false;
    }

    if (utils.isAssign(opr)) {
        if (expr->reference == NULL) {
            context->log("lvalue required as an operand of increment/decrement operator", expr->loc, LOG_ERROR);
            return false;
        }
        if (expr->reference && expr->constant) {
            context->log("increment/decrement of read-only variable '" + expr->reference->declaredHeader() + "'",
                         expr->loc, LOG_ERROR);
            return false;
        }
    }

    type = (utils.isLogical(opr) ? BOOL : expr->type);
    reference = NULL;
    constant = expr->constant;
    used = valueUsed;

    return true;
}

bool IdentifierNode::analyze(ScopeContext* context, bool valueUsed) {
    DeclarationNode* ptr = context->getSymbol(name);

    if (ptr == NULL) {
        context->log("'" + name + "' was not declared in this scope", loc, LOG_ERROR);
        return false;
    }

    reference = ptr;

    if (dynamic_cast<FunctionNode*>(ptr)) {
        type = FUNC_PTR;
    } else {
        type = ptr->type->type;
        constant = ((VarDeclarationNode*) ptr)->constant;
    }

    used = valueUsed;

    if (used) {
        reference->used++;
    }

    if (used && !reference->initialized) {
        context->log("variable or field '" + name + "' used without being initialized", loc, LOG_ERROR);
        return false;
    }

    return true;
}

/* -------------------------- statement analyzers ---------------------*/

bool ErrorNode::analyze(ScopeContext* context) {
    context->log(what, loc, LOG_ERROR);
    return false;
}

bool BlockNode::analyze(ScopeContext* context) {
    if (context->isGlobalScope()) {
        context->log("block is not allowed in global scope", loc, LOG_ERROR);
        return false;
    }

    bool ret = true;

    context->addScope(BLOCK, this);

    for (int i = 0; i < statements.size(); ++i) {
        ret &= statements[i]->analyze(context);
    }

    context->popScope();

    return ret;
}

bool VarDeclarationNode::analyze(ScopeContext* context) {
    bool ret = true;

    if (type->type == VOID) {
        context->log("variable or field '" + ident->name + "' declared void", ident->loc, LOG_ERROR);
        ret = false;
    }
    else if (!context->declareSymbol(this)) {
        context->log("'" + declaredHeader() + "' redeclared", ident->loc, LOG_ERROR);
        ret = false;
    }

    if (context->declareFuncParams) {
        initialized = true;
    }

    if (value) {
        context->initializeVar = true;
        ret &= value->analyze(context, true);
        context->initializeVar = false;
    }

    if (ret && value != NULL && (value->type == VOID || value->type == FUNC_PTR)) {
        context->log("invalid conversion from '" + value->exprTypeStr() + "' to '" + type->toString() + "'", value->loc, LOG_ERROR);
        ret = false;
    }
    else if (context->declareFuncParams && value != NULL) {
        context->log("default function parameters are not allowed", value->loc, LOG_ERROR);
        ret = false;
    }
    else if (constant && value == NULL && !context->declareFuncParams) {
        context->log("uninitialized const '" + ident->name + "'", ident->loc, LOG_ERROR);
        ret = false;
    }

    SwitchNode* switchStmt = context->getSwitchScope();

    if (switchStmt != NULL && value != NULL) {
        switchStmt->initializedVars.push_back(this);
    }

    return ret;
}
bool EnumDeclarationNode::analyze(ScopeContext* context) {

    bool ret = true;

    if (!context->isGlobalScope()) {
        context->log("a enum-definition is not allowed here", loc, LOG_ERROR);
        return false;
    }

   
    for (int i = 0; i < paramList.size(); ++i) {
        ret &= paramList[i]->analyze(context);
        
        if(paramList[i]->initialized){

            currentValue =  stoi(((ValueNode *)paramList[i]->value)->value)+1;
   
        }
        else{
            const char * temp = to_string(currentValue).c_str();
           paramList[i]->value = new ValueNode(paramList[i]->loc, INT,temp);
           paramList[i]->value->used = true;
           paramList[i]->initialized = true;
           currentValue+=1;
        }

        
        
    }

    return ret;

}

/* ------------------------- branch analyzers -----------------------*/

bool IfNode::analyze(ScopeContext* context) {
    if (context->isGlobalScope()) {
        context->log("if-statement is not allowed in global scope", loc, LOG_ERROR);
        return false;
    }

    bool ret = true;

    context->addScope(IF, this);

    ret &= cond->analyze(context, true);

    if (ret && cond->type == VOID) {
        context->log("invalid conversion from '" + cond->exprTypeStr() + "' to 'bool'", cond->loc, LOG_ERROR);
        ret = false;
    }

    ret &= ifBody->analyze(context);

    if (elseBody) {
        ret &= elseBody->analyze(context);
    }

    context->popScope();

    return ret;
}

bool CaseLabelNode::analyze(ScopeContext* context) {
    SwitchNode* switchStmt = context->getSwitchScope();

    if (switchStmt == NULL) {
        context->log("case label not within switch statement", loc, LOG_ERROR);
        return false;
    }

    bool ret = true;

    if (switchStmt->initializedVars.size() > 0) {
        context->log("jump to case label", expr->loc, LOG_ERROR);
        ret = false;

        const VarList& list = switchStmt->initializedVars;

        for (int i = 0; i < list.size(); ++i) {
            context->log("crosses initialization of '" + list[i]->declaredHeader() + "'", list[i]->ident->loc, LOG_NOTE);
        }
    }

    if (expr) {     // case label
        ret = expr->analyze(context, true);

        if (ret && !expr->constant) {
            context->log("constant expression required in case label", expr->loc, LOG_ERROR);
            ret = false;
        }
        if (ret && !utils.isValidInt(expr->type)) {
            context->log("case quantity not an integer", expr->loc, LOG_ERROR);
            ret = false;
        }
        if (ret && expr->constant && utils.isValidInt(expr->type)) {
            int val = expr->getConstIntValue();

            if (switchStmt->caseMap.count(val)) {
                context->log("duplicate case value", loc, LOG_ERROR);
                context->log("previously used here", switchStmt->caseMap[val]->loc, LOG_NOTE);
                ret = false;
            }

            switchStmt->caseMap[val] = this;
        }
    }
    else {          // default label
        if (switchStmt->hasDefaultLabel) {
            context->log("multiple default labels in one switch", loc, LOG_ERROR);
            ret = false;
        }

        switchStmt->hasDefaultLabel = true;
    }

    ret &= stmt->analyze(context);

    return ret;
}

bool SwitchNode::analyze(ScopeContext* context) {
    if (context->isGlobalScope()) {
        context->log("switch-statement is not allowed in global scope", loc, LOG_ERROR);
        return false;
    }

    bool ret = true;

    populate(); // Pre-compute switch cases and statements

    context->addScope(SWITCH, this);

    ret &= cond->analyze(context, true);

    if (!utils.isValidInt(cond->type)) {
        context->log("switch quantity not an integer", cond->loc, LOG_ERROR);
        ret = false;
    }

    ret &= body->analyze(context);

    context->popScope();

    return ret;
}

bool WhileNode::analyze(ScopeContext* context) {
    if (context->isGlobalScope()) {
        context->log("while-statement is not allowed in global scope", loc, LOG_ERROR);
        return false;
    }

    bool ret = true;

    context->addScope(LOOP, this);

    ret &= cond->analyze(context, true);

    if (ret && cond->type == VOID) {
        context->log("invalid conversion from '" + cond->exprTypeStr() + "' to 'bool'", cond->loc, LOG_ERROR);
        ret = false;
    }

    ret &= body->analyze(context);

    context->popScope();

    return ret;
}

bool RepeatUntilNode::analyze(ScopeContext* context) {
    if (context->isGlobalScope()) {
        context->log("repeat-until-statement is not allowed in global scope", loc, LOG_ERROR);
        return false;
    }

    bool ret = true;

    context->addScope(LOOP, this);

    ret &= cond->analyze(context, true);

    if (ret && cond->type == VOID) {
        context->log("invalid conversion from '" + cond->exprTypeStr() + "' to 'bool'", cond->loc, LOG_ERROR);
        ret = false;
    }

    ret &= body->analyze(context);

    context->popScope();

    return ret;
}

bool ForNode::analyze(ScopeContext* context) {
    if (context->isGlobalScope()) {
        context->log("for-statement is not allowed in global scope", loc, LOG_ERROR);
        return false;
    }

    bool ret = true;

    context->addScope(LOOP, this);

    if (initStmt) {
        ret &= initStmt->analyze(context);
    }

    if (cond) {
        ret &= cond->analyze(context, true);

        if (ret && cond->type == VOID) {
            context->log("invalid conversion from '" + cond->exprTypeStr() + "' to 'bool'", cond->loc, LOG_ERROR);
            ret = false;
        }
    }

    if (inc) {
        ret &= inc->analyze(context, false);
    }

    ret &= body->analyze(context);

    context->popScope();

    return ret;
}

bool BreakStmtNode::analyze(ScopeContext* context) {
    if (!context->hasBreakScope()) {
        context->log("break-statement not within loop or switch", loc, LOG_ERROR);
        return false;
    }

    return true;
}

bool ContinueStmtNode::analyze(ScopeContext* context) {
    if (!context->hasLoopScope()) {
        context->log("continue-statement not within loop", loc, LOG_ERROR);
        return false;
    }

    return true;
}

/* ------------------------- function analyzers -----------------*/

bool FunctionNode::analyze(ScopeContext* context) {
    if (!context->isGlobalScope()) {
        context->log("a function-definition is not allowed here", ident->loc, LOG_ERROR);
        return false;
    }

    bool ret = true;

    if (!context->declareSymbol(this)) {
        context->log("'" + declaredHeader() + "' redeclared", ident->loc, LOG_ERROR);
        ret = false;
    }

    context->addScope(FUNCTION, this);

    context->declareFuncParams = true;
    for (int i = 0; i < paramList.size(); ++i) {
        ret &= paramList[i]->analyze(context);
    }
    context->declareFuncParams = false;

    ret &= body->analyze(context);

    context->popScope();

    return ret;
}

bool FunctionCallNode::analyze(ScopeContext* context, bool valueUsed) {
    bool ret = true;

    DeclarationNode* ptr = context->getSymbol(ident->name);
    func = dynamic_cast<FunctionNode*>(ptr);

    if (ptr == NULL) {
        context->log("'" + ident->name + "' was not declared in this scope", loc, LOG_ERROR);
        ret = false;
    }
    else if (func == NULL) {
        context->log("'" + ident->name + "' cannot be used as a function", loc, LOG_ERROR);
        ret = false;
    }
    else if (argList.size() > func->paramList.size()) {
        context->log("too many arguments to function '" + func->declaredHeader() + "'", loc, LOG_ERROR);
        ret = false;
    }
    else if (argList.size() < func->paramList.size()) {
        context->log("too few arguments to function '" + func->declaredHeader() + "'", loc, LOG_ERROR);
        ret = false;
    } else {
        type = ptr->type->type;
    }

    for (int i = 0; i < argList.size(); ++i) {
        if (!argList[i]->analyze(context, true)) {
            ret = false;
            continue;
        }

        if (func && argList[i]->type == VOID || argList[i]->type == FUNC_PTR) {
            context->log("invalid conversion from '" + argList[i]->exprTypeStr() + "' to '" +
                         func->paramList[i]->type->toString() + "' in function '" +
                         func->declaredHeader() + "' call", argList[i]->loc, LOG_ERROR);
            return false;
        }
    }

    used = valueUsed;

    if (ret) {
        func->used++;
    }

    return ret;
}

bool ReturnStmtNode::analyze(ScopeContext* context) {
    func = context->getFunctionScope();

    if (func == NULL) {
        context->log("return-statement not within function", loc, LOG_ERROR);
        return false;
    }

    if (value) {    // return expression exists
        if (!value->analyze(context, true)) {
            return false;
        }

        if (func->type->type == VOID && value->type != VOID) {
            context->log("return-statement with '" + value->exprTypeStr() + "' value, in function returning 'void'",
                         value->loc, LOG_ERROR);
            return false;
        }
    }
    else {          // No return expression
        if (func->type->type != VOID) {
            context->log("return-statement with no value, in function returning '" + func->type->toString() + "'", loc, LOG_ERROR);
            return false;
        }
    }

    return true;
}
