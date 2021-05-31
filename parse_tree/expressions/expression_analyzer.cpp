#include "../parse_tree.h"
#include "../../manager/scope_context.h"


bool ExprContainerNode::analyze(ScopeContext* context, bool valueUsed) {
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

bool AssignOprNode::analyze(ScopeContext* context, bool valueUsed) {
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
        context->log("assignment of read-only variable '" + lhs->reference->declaredHeader() + "'", lhs->loc, LOG_ERROR);
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

bool BinaryOprNode::analyze(ScopeContext* context, bool valueUsed) {
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

bool UnaryOprNode::analyze(ScopeContext* context, bool valueUsed) {
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
