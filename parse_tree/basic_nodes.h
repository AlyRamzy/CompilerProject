#ifndef __BASIC_NODES_H_
#define __BASIC_NODES_H_

#include <iostream>
#include <string>


#include "../utils.h"

class ScopeContext;
class quadrublesGenerator;

class Node;
class StatementNode;
class DeclarationNode;
class VarDeclarationNode;
class FunctionNode;
class ExpressionNode;
class IdentifierNode;
class TypeNode;

typedef vector<Node*> NodeList;
typedef vector<StatementNode*> StmtList;
typedef vector<VarDeclarationNode*> VarList;
typedef vector<ExpressionNode*> ExprList;

class Node {
public:
    Location loc;
    Utils utils;

    Node() {}

    Node(const Location& loc) {
        this->loc = loc;
    }

    virtual ~Node() {}

    virtual bool analyze(ScopeContext* context) {
        return true;
    }

    virtual string generateQuad(quadrublesGenerator* context) {
        return "";
    }

    virtual string toString() {
        return "";
    }
};

class StatementNode : public Node {
public:
    StatementNode() {}

    StatementNode(const Location& loc) : Node(loc) {}

    virtual string toString(int ind = 0) {
        return string(ind, ' ') + ";" ;
    }
};

class DeclarationNode : public StatementNode {
public:
    TypeNode* type;
    IdentifierNode* ident;

    string alias;                       
    int used = 0;                       
    bool initialized = false;           

    DeclarationNode(const Location& loc) : StatementNode(loc) {}

    virtual string declaredHeader() = 0;

    virtual string declaredType() = 0;
};

class ExpressionNode : public StatementNode {
public:
    dataTypes type = ERROR;        
    DeclarationNode* reference = NULL;  
    bool constant = false;              
    bool used = false;                  

    ExpressionNode() {}

    ExpressionNode(const Location& loc) : StatementNode(loc) {}

    virtual int getConstIntValue() {
        return -1;
    }
    
    virtual bool analyze(ScopeContext* context) {
        return analyze(context, false);
    }

    virtual bool analyze(ScopeContext* context, bool valueUsed) {
        used = valueUsed;
        return true;
    }

    virtual string exprTypeStr() {
        return reference ? reference->declaredType() : utils.dtypeToStr(type);
    }
};

class TypeNode : public Node {
    public :
    dataTypes type;
    TypeNode(const Location& loc, dataTypes type) : Node(loc) {
        this->type = type;
    }

    virtual string toString(int ind = 0) {
        return string(ind, ' ') + utils.dtypeToStr(type);
    }
};

class ErrorNode : public StatementNode {
    public :
    string what;

    ErrorNode(const Location& loc, const string& what) : StatementNode(loc) {
        this->what = what;
        this->loc.pos -= this->loc.len - 1;
    }

    virtual bool analyze(ScopeContext* context);

    virtual string toString(int ind) {
        return string(ind, ' ') + ">> ERROR" ;
    }
};

#endif