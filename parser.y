%{

#include<iostream>
#include<string>

#include"nodes.h"
using namespace std;

extern int yylex();
extern Location curLoc;

void yyerror(const char* s);

StatementNode* programRoot = NULL;
%}

%union {
    BlockNode*                  blockNode;
    StatementNode*              stmtNode;
    VarDeclarationNode*         varDeclNode;
    IfNode*                     ifNode;
    SwitchNode*                 switchNode;
    CaseLabelNode*              caseStmtNode;
    WhileNode*                  whileNode;
    RepeatUntilNode*            repeatUntilNode;
    ForNode*                    forNode;
    FunctionNode*               functionNode;
    FunctionCallNode*           functionCallNode;
    ReturnStmtNode*             returnStmtNode;
    ExpressionNode*             exprNode;
    TypeNode*                   typeNode;
    ValueNode*                  valueNode;
    IdentifierNode*             identifierNode;
    EnumDeclarationNode*        enumDeclarationNode;

    StmtList*                   stmtList;
    ExprList*                   exprList;
    VarList*                    varList;

    Token token;
    Location location;
}

// Data types
%token <location> TYPE_INT_TOKEN
%token <location> TYPE_FLOAT_TOKEN
%token <location> TYPE_CHAR_TOKEN
%token <location> TYPE_BOOL_TOKEN
%token <location> TYPE_VOID_TOKEN

// Keywords
%token <location> CONST_TOKEN
%token <location> IF_TOKEN
%token <location> ELSE_TOKEN
%token <location> SWITCH_TOKEN
%token <location> CASE_TOKEN
%token <location> DEFAULT_TOKEN
%token <location> FOR_TOKEN
%token <location> WHILE_TOKEN
%token <location> REPEAT_TOKEN
%token <location> UNTIL_TOKEN
%token <location> BREAK_TOKEN
%token <location> CONTINUE_TOKEN
%token <location> RETURN_TOKEN
%token <location> ENUM_TOKEN

// Operators
%token <location> LOGICAL_AND_TOKEN
%token <location> LOGICAL_OR_TOKEN
%token <location> EQ_TOKEN
%token <location> NEQ_TOKEN
%token <location> GTE_TOKEN
%token <location> LTE_TOKEN

// Values
%token <token> INTEGER_TOKEN
%token <token> FLOAT_TOKEN
%token <token> CHAR_TOKEN
%token <token> BOOL_TOKEN
%token <token> IDENTIFIER_TOKEN

%type <blockNode>           program stmt_block
%type <stmtNode>            stmt branch_body for_init_stmt
%type <stmtList>            stmt_list
%type <varDeclNode>         var_decl
%type <ifNode>              if_stmt 
%type <switchNode>          switch_stmt
%type <caseStmtNode>        case_stmt
%type <whileNode>           while_stmt
%type <repeatUntilNode>     repeat_until_stmt
%type <forNode>             for_stmt for_header
%type <functionNode>        function function_header
%type <functionCallNode>    function_call
%type <returnStmtNode>      return_stmt
%type <varList>             param_list param_list_ext enum_elements enum_list_ext
%type <exprList>            arg_list arg_list_ext
%type <exprNode>            expression for_expr
%type <typeNode>            type
%type <valueNode>           value 
%type <identifierNode>      ident enum_name
%type <enumDeclarationNode> enum_stmt  

%type <location>  '-' '+' '*' '/' '%' '&' '|' '^' '~' '!' '<' '>' '=' '(' ')' '{' '}' '[' ']' ',' ':' ';'

%destructor {
    if ($$ != NULL) {
        delete $$;
        $$ = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
<blockNode> <stmtNode> <varDeclNode> 
<ifNode> <switchNode> <caseStmtNode>
<whileNode> <repeatUntilNode> <forNode> <enumDeclarationNode>
<functionNode> <functionCallNode> <returnStmtNode>
<stmtList> <varList> <exprList>
<exprNode> <typeNode> <valueNode> <identifierNode>

%right      '='
%left       LOGICAL_OR_TOKEN
%left       LOGICAL_AND_TOKEN
%left       '|'
%left       '^'
%left       '&'
%left       EQ_TOKEN NEQ_TOKEN
%left       LTE_TOKEN GTE_TOKEN '<' '>'
%left       '-' '+'
%left       '*' '/' '%'
%right      '!' '~'
%right      U_PLUS_TOKEN U_MINUS_TOKEN

%nonassoc   IF_UNMAT
%nonassoc   ELSE_TOKEN

%%

program:            /* empty */                 { $$ = NULL; programRoot = new BlockNode(); }
    |               stmt_list                   { $$ = NULL; programRoot = new BlockNode((*$1)[0]->loc, *$1); delete $1; }
    ;

stmt_list:          stmt                        { $$ = new StmtList(); $$->push_back($1); }
    |               stmt_block                  { $$ = new StmtList(); $$->push_back($1); }
    |               stmt_list stmt              { $$ = $1; $$->push_back($2); }
    |               stmt_list stmt_block        { $$ = $1; $$->push_back($2); }
    ;

stmt_block:         '{' '}'                     { $$ = new BlockNode($<location>1); }
    |               '{' stmt_list '}'           { $$ = new BlockNode($<location>1, *$2); delete $2; }
    ;

stmt:               ';'                         { $$ = new StatementNode($<location>1); }
    |               BREAK_TOKEN ';'             { $$ = new BreakStmtNode($<location>1); }
    |               CONTINUE_TOKEN ';'          { $$ = new ContinueStmtNode($<location>1); }
    |               expression ';'              { $$ = new ExprContainerNode($1->loc, $1); }
    |               var_decl ';'                { $$ = $1; }
    |               if_stmt                     { $$ = $1; }
    |               switch_stmt                 { $$ = $1; }
    |               case_stmt                   { $$ = $1; }
    |               while_stmt                  { $$ = $1; }
    |               repeat_until_stmt ';'       { $$ = $1; }
    |               for_stmt                    { $$ = $1; }
    |               function                    { $$ = $1; }
    |               return_stmt ';'             { $$ = $1; }
    |               enum_stmt ';'               { $$ = $1; }
    ;

branch_body:        stmt                        { $$ = $1; }
    |               stmt_block                  { $$ = $1; }
    ;



var_decl:           type ident                              { $$ = new VarDeclarationNode($1, $2); }
    |               CONST_TOKEN type ident                  { $$ = new VarDeclarationNode($2, $3, NULL, true); }
    |               type ident '=' expression               { $$ = new VarDeclarationNode($1, $2, $4); }
    |               CONST_TOKEN type ident '=' expression   { $$ = new VarDeclarationNode($2, $3, $5, true); }
    ;


expression:         ident '=' expression                    { $$ = new AssignOprNode($2, $1, $3); }
    |               expression '+' expression               { $$ = new BinaryOprNode($2, ADD, $1, $3); }
    |               expression '-' expression               { $$ = new BinaryOprNode($2, SUB, $1, $3); }
    |               expression '*' expression               { $$ = new BinaryOprNode($2, MUL, $1, $3); }
    |               expression '/' expression               { $$ = new BinaryOprNode($2, DIV, $1, $3); }
    |               expression '%' expression               { $$ = new BinaryOprNode($2, MOD, $1, $3); }
    |               expression '&' expression               { $$ = new BinaryOprNode($2, AND, $1, $3); }
    |               expression '|' expression               { $$ = new BinaryOprNode($2, OR, $1, $3); }
    |               expression '^' expression               { $$ = new BinaryOprNode($2, XOR, $1, $3); }
    |               expression LOGICAL_AND_TOKEN expression { $$ = new BinaryOprNode($2, LOGICAL_AND, $1, $3); }
    |               expression LOGICAL_OR_TOKEN expression  { $$ = new BinaryOprNode($2, LOGICAL_OR, $1, $3); }
    |               expression '>' expression               { $$ = new BinaryOprNode($2, GT, $1, $3); }
    |               expression GTE_TOKEN expression         { $$ = new BinaryOprNode($2, GTE, $1, $3); }
    |               expression '<' expression               { $$ = new BinaryOprNode($2, LT, $1, $3); }
    |               expression LTE_TOKEN expression         { $$ = new BinaryOprNode($2, LTE, $1, $3); }
    |               expression EQ_TOKEN expression          { $$ = new BinaryOprNode($2, EQ, $1, $3); }
    |               expression NEQ_TOKEN expression         { $$ = new BinaryOprNode($2, NEQ, $1, $3); }
    |               '+' expression %prec U_PLUS_TOKEN       { $$ = new UnaryOprNode($1, U_PLUS, $2); }
    |               '-' expression %prec U_MINUS_TOKEN      { $$ = new UnaryOprNode($1, U_MINUS, $2); }
    |               '~' expression                          { $$ = new UnaryOprNode($1, NOT, $2); }
    |               '!' expression                          { $$ = new UnaryOprNode($1, LOGICAL_NOT, $2); }
    |               '(' expression ')'                      { $$ = new ExprContainerNode($1, $2); }
    |               value                                   { $$ = $1; }
    |               ident                                   { $$ = $1; }
    |               function_call                           { $$ = $1; }
    ;


if_stmt:            IF_TOKEN '(' expression ')' branch_body %prec IF_UNMAT          { $$ = new IfNode($1, $3, $5); }
    |               IF_TOKEN '(' expression ')' branch_body ELSE_TOKEN branch_body  { $$ = new IfNode($1, $3, $5, $7); }
    ;

switch_stmt:        SWITCH_TOKEN '(' expression ')' branch_body   { $$ = new SwitchNode($1, $3, $5); }
    ;

case_stmt:          CASE_TOKEN expression ':' stmt                { $$ = new CaseLabelNode($1, $2, $4); }
    |               DEFAULT_TOKEN ':' stmt                        { $$ = new CaseLabelNode($1, NULL, $3); }
    ;


while_stmt:         WHILE_TOKEN '(' expression ')' branch_body                { $$ = new WhileNode($1, $3, $5); }
    ;

repeat_until_stmt:  REPEAT_TOKEN branch_body UNTIL_TOKEN '(' expression ')'   { $$ = new RepeatUntilNode($1, $5, $2); }
    ;

for_stmt:           for_header branch_body                              { $$ = $1; $$->body = $2; }
    ;

for_header:         FOR_TOKEN '(' for_init_stmt ';' for_expr ';' for_expr ')' { $$ = new ForNode($1, $3, $5, $7, NULL); }
    ;

for_init_stmt:      /* empty */                                         { $$ = NULL; }
    |               var_decl                                            { $$ = $1; }
    |               expression                                          { $$ = $1; }
    ;

for_expr:           /* empty */                                         { $$ = NULL; }
    |               expression                                          { $$ = $1; }
    ;

function:           function_header stmt_block          { $$ = $1; $$->body = $2; }
    ;

function_header:    type ident '(' param_list ')'       { $$ = new FunctionNode($1, $2, *$4, NULL); delete $4; }
    ;

param_list:         /* empty */                         { $$ = new VarList(); }
    |               var_decl                            { $$ = new VarList(); $$->push_back($1); }
    |               param_list_ext ',' var_decl         { $$ = $1; $$->push_back($3); }
    ;

param_list_ext:     var_decl                            { $$ = new VarList(); $$->push_back($1); }
    |               param_list_ext ',' var_decl         { $$ = $1; $$->push_back($3); }
    ;

function_call:      ident '(' arg_list ')'              { $$ = new FunctionCallNode($1, *$3); delete $3; }
    ;

arg_list:           /* empty */                         { $$ = new ExprList(); }
    |               expression                          { $$ = new ExprList(); $$->push_back($1); }
    |               arg_list_ext ',' expression         { $$ = $1; $$->push_back($3); }
    ;

arg_list_ext:       expression                          { $$ = new ExprList(); $$->push_back($1); }
    |               arg_list_ext ',' expression         { $$ = $1; $$->push_back($3); }
    ;

return_stmt:        RETURN_TOKEN expression                   { $$ = new ReturnStmtNode($1, $2); }
    |               RETURN_TOKEN                              { $$ = new ReturnStmtNode($1, NULL); }
    ;


enum_stmt:          ENUM_TOKEN enum_name '{' enum_elements '}'   { $$ = new EnumDeclarationNode($1,$2,*$4); }
    ;

enum_name:          /* empty */                         { $$ = NULL; }
    |               ident                               { $$=$1;  }
    ;
    
enum_elements:      /* empty */                              {$$ = new VarList();  }
    |               ident                                    {$$ = new VarList(); $$->push_back(new VarDeclarationNode(new TypeNode($1->loc, INT), $1)); }
    |               ident '=' value                     { $$ = new VarList(); $$->push_back(new VarDeclarationNode(new TypeNode($1->loc, INT), $1,$3));}
    |               enum_list_ext ',' ident                  {$$ = $1; $$->push_back(new VarDeclarationNode(new TypeNode($3->loc, INT), $3)); }
    |               enum_list_ext ',' ident '=' value   {$$ = $1; $$->push_back(new VarDeclarationNode(new TypeNode($3->loc, INT), $3,$5)); }
    ;

enum_list_ext:      ident                                    {$$ = new VarList(); $$->push_back(new VarDeclarationNode(new TypeNode($1->loc, INT), $1)); }
    |               ident '=' expression                     { $$ = new VarList(); $$->push_back(new VarDeclarationNode(new TypeNode($1->loc, INT), $1,$3)); }
    |               enum_list_ext ',' ident                  { $$ = $1; $$->push_back(new VarDeclarationNode(new TypeNode($3->loc, INT), $3)); }
    |               enum_list_ext ',' ident '=' value   {$$ = $1; $$->push_back(new VarDeclarationNode(new TypeNode($3->loc, INT), $3,$5));   }
    ;
    
type:               TYPE_INT_TOKEN        { $$ = new TypeNode($1, INT); }
    |               TYPE_FLOAT_TOKEN      { $$ = new TypeNode($1, FLOAT); }
    |               TYPE_CHAR_TOKEN       { $$ = new TypeNode($1, CHAR); }
    |               TYPE_BOOL_TOKEN       { $$ = new TypeNode($1, BOOL); }
    |               TYPE_VOID_TOKEN       { $$ = new TypeNode($1, VOID); }
    ;

value:              INTEGER_TOKEN         { $$ = new ValueNode($1.loc, INT, $1.value); delete $1.value; }
    |               FLOAT_TOKEN           { $$ = new ValueNode($1.loc, FLOAT, $1.value); delete $1.value; }
    |               CHAR_TOKEN            { $$ = new ValueNode($1.loc, CHAR, $1.value); delete $1.value; }
    |               BOOL_TOKEN            { $$ = new ValueNode($1.loc, BOOL, $1.value); delete $1.value; }
    ;

ident:              IDENTIFIER_TOKEN      { $$ = new IdentifierNode($1.loc, $1.value); delete $1.value; }
    ;

%%

void yyerror(const char* s) {
    printf( "%s\n", s);
}