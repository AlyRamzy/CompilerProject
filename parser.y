%{
#include "utils.h"
#include <stdio.h>
#include "../parse_tree/parse_tree.h"

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
    MultiVarDeclarationNode*    multiVarDeclNode;
    IfNode*                     ifNode;
    SwitchNode*                 switchNode;
    CaseLabelNode*              caseStmtNode;
    WhileNode*                  whileNode;
    DoWhileNode*                doWhileNode;
    ForNode*                    forNode;
    FunctionNode*               functionNode;
    FunctionCallNode*           functionCallNode;
    ReturnStmtNode*             returnStmtNode;
    ExpressionNode*             exprNode;
    TypeNode*                   typeNode;
    ValueNode*                  valueNode;
    IdentifierNode*             identifierNode;

    StmtList*                   stmtList;
    ExprList*                   exprList;
    VarList*                    varList;

    Token token;
    Location location;
}

// Data types
%token <location> TYPE_INT
%token <location> TYPE_FLOAT
%token <location> TYPE_CHAR
%token <location> TYPE_BOOL
%token <location> TYPE_VOID

// Keywords
%token <location> CONST
%token <location> IF
%token <location> ELSE
%token <location> SWITCH
%token <location> CASE
%token <location> DEFAULT
%token <location> FOR
%token <location> WHILE
%token <location> REPEAT
%token <location> UNTIL
%token <location> BREAK
%token <location> CONTINUE
%token <location> RETURN
%token <location> ENUM

// Operators
%token <location> LOGICAL_AND
%token <location> LOGICAL_OR
%token <location> EQ
%token <location> NEQ
%token <location> GTE
%token <location> LTE

// Values
%token <token> INTEGER
%token <token> FLOAT
%token <token> CHAR
%token <token> BOOL
%token <token> IDENTIFIER

%type <blockNode>           program stmt_block
%type <stmtNode>            stmt branch_body for_init_stmt
%type <stmtList>            stmt_list
%type <varDeclNode>         var_decl
%type <multiVarDeclNode>    multi_var_decl
%type <ifNode>              if_stmt unmatched_if_stmt matched_if_stmt
%type <switchNode>          switch_stmt
%type <caseStmtNode>        case_stmt
%type <whileNode>           while_stmt
%type <doWhileNode>         do_while_stmt
%type <forNode>             for_stmt for_header
%type <functionNode>        function function_header
%type <functionCallNode>    function_call
%type <returnStmtNode>      return_stmt
%type <varList>             param_list param_list_ext
%type <exprList>            arg_list arg_list_ext
%type <exprNode>            expression expr_1 expr_2 expr_3 for_expr
%type <typeNode>            type
%type <valueNode>           value
%type <identifierNode>      ident

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
<blockNode> <stmtNode> <varDeclNode> <multiVarDeclNode>
<ifNode> <switchNode> <caseStmtNode>
<whileNode> <doWhileNode> <forNode>
<functionNode> <functionCallNode> <returnStmtNode>
<stmtList> <varList> <exprList>
<exprNode> <typeNode> <valueNode> <identifierNode>

%right      '='
%left       LOGICAL_OR
%left       LOGICAL_AND
%left       '|'
%left       '^'
%left       '&'
%left       EQ NEQ
%left       LTE GTE '<' '>'
%left       '-' '+'
%left       '*' '/' '%'
%right      '!' '~'
%right      U_PLUS U_MINUS

%nonassoc   IF_UNMAT
%nonassoc   ELSE

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
    |               BREAK ';'                   { $$ = new BreakStmtNode($<location>1); }
    |               CONTINUE ';'                { $$ = new ContinueStmtNode($<location>1); }
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
    |               error ';'                   { $$ = new ErrorNode(curLoc, "invalid syntax"); yyerrok; }
    |               error ')'                   { $$ = new ErrorNode(curLoc, "invalid syntax"); yyerrok; }
    |               error '}'                   { $$ = new ErrorNode(curLoc, "invalid syntax"); yyerrok; }
    ;
    ;

branch_body:        stmt                        { $$ = $1; }
    |               stmt_block                  { $$ = $1; }
    ;



var_decl:           type ident                              { $$ = new VarDeclarationNode($1, $2); }
    |               CONST type ident                        { $$ = new VarDeclarationNode($2, $3, NULL, true); }
    |               type ident '=' expression               { $$ = new VarDeclarationNode($1, $2, $4); }
    |               CONST type ident '=' expression         { $$ = new VarDeclarationNode($2, $3, $5, true); }
    ;


expression:         ident '=' expression                    { $$ = new AssignOprNode($2, $1, $3); }
    |               expression '+' expression               { $$ = new BinaryOprNode($2, OPR_ADD, $1, $3); }
    |               expression '-' expression               { $$ = new BinaryOprNode($2, OPR_SUB, $1, $3); }
    |               expression '*' expression               { $$ = new BinaryOprNode($2, OPR_MUL, $1, $3); }
    |               expression '/' expression               { $$ = new BinaryOprNode($2, OPR_DIV, $1, $3); }
    |               expression '%' expression               { $$ = new BinaryOprNode($2, OPR_MOD, $1, $3); }
    |               expression '&' expression               { $$ = new BinaryOprNode($2, OPR_AND, $1, $3); }
    |               expression '|' expression               { $$ = new BinaryOprNode($2, OPR_OR, $1, $3); }
    |               expression '^' expression               { $$ = new BinaryOprNode($2, OPR_XOR, $1, $3); }
    |               expression LOGICAL_AND expression       { $$ = new BinaryOprNode($2, OPR_LOGICAL_AND, $1, $3); }
    |               expression LOGICAL_OR expression        { $$ = new BinaryOprNode($2, OPR_LOGICAL_OR, $1, $3); }
    |               expression '>' expression               { $$ = new BinaryOprNode($2, OPR_GREATER, $1, $3); }
    |               expression GTE expression               { $$ = new BinaryOprNode($2, OPR_GREATER_EQUAL, $1, $3); }
    |               expression '<' expression               { $$ = new BinaryOprNode($2, OPR_LESS, $1, $3); }
    |               expression LTE expression               { $$ = new BinaryOprNode($2, OPR_LESS_EQUAL, $1, $3); }
    |               expression EQ expression                { $$ = new BinaryOprNode($2, OPR_EQUAL, $1, $3); }
    |               expression NEQ expression               { $$ = new BinaryOprNode($2, OPR_NOT_EQUAL, $1, $3); }
    |               '+' expression %prec U_PLUS             { $$ = new UnaryOprNode($1, OPR_U_PLUS, $2); }
    |               '-' expression %prec U_MINUM            { $$ = new UnaryOprNode($1, OPR_U_MINUS, $2); }
    |               '~' expression                          { $$ = new UnaryOprNode($1, OPR_NOT, $2); }
    |               '!' expression                          { $$ = new UnaryOprNode($1, OPR_LOGICAL_NOT, $2); }
    |               '(' expression ')'                      { $$ = new ExprContainerNode($1, $2); }
    |               value                                   { $$ = $1; }
    |               ident                                   { $$ = $1; }
    |               function_call                           { $$ = $1; }
    ;


if_stmt:            IF '(' expression ')' branch_body %prec IF_UNMAT    { $$ = new IfNode($1, $3, $5); }
    |               IF '(' expression ')' branch_body ELSE branch_body  { $$ = new IfNode($1, $3, $5, $7); }
    ;

switch_stmt:        SWITCH '(' expression ')' branch_body   { $$ = new SwitchNode($1, $3, $5); }
    ;

case_stmt:          CASE expression ':' stmt                { $$ = new CaseLabelNode($1, $2, $4); }
    |               DEFAULT ':' stmt                        { $$ = new CaseLabelNode($1, NULL, $3); }
    ;


while_stmt:         WHILE '(' expression ')' branch_body                { $$ = new WhileNode($1, $3, $5); }
    ;

repeat_until_stmt:  REPEAT branch_body UNTIL '(' expression ')'         { $$ = new DoWhileNode($1, $5, $2); }
    ;

for_stmt:           for_header branch_body                              { $$ = $1; $$->body = $2; }
    ;

for_header:         FOR '(' for_init_stmt ';' for_expr ';' for_expr ')' { $$ = new ForNode($1, $3, $5, $7, NULL); }
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

return_stmt:        RETURN expression                   { $$ = new ReturnStmtNode($1, $2); }
    |               RETURN                              { $ = new ReturnStmtNode($1, NULL); }
    ;


enum_stmt:          ENUM enum_name '{' enum_elements '}'   {  }
    ;

enum_name:          /* empty */                         {  }
    |               ident                               {  }
    ;
    
enum_elements:      /* empty */                              {  }
    |               ident                                    {  }
    |               ident '=' expression                     {  }
    |               enum_list_ext ',' ident                  {  }
    |               enum_list_ext ',' ident '=' expression   {  }
    ;

enum_list_ext:      ident                                    {  }
    |               ident '=' expression                     {  }
    |               enum_list_ext ',' ident                  {  }
    |               enum_list_ext ',' ident '=' expression   {  }
    ;
    
type:               TYPE_INT        { $$ = new TypeNode($1, DTYPE_INT); }
    |               TYPE_FLOAT      { $$ = new TypeNode($1, DTYPE_FLOAT); }
    |               TYPE_CHAR       { $$ = new TypeNode($1, DTYPE_CHAR); }
    |               TYPE_BOOL       { $$ = new TypeNode($1, DTYPE_BOOL); }
    |               TYPE_VOID       { $$ = new TypeNode($1, DTYPE_VOID); }
    ;

value:              INTEGER         { $$ = new ValueNode($1.loc, DTYPE_INT, $1.value); delete $1.value; }
    |               FLOAT           { $$ = new ValueNode($1.loc, DTYPE_FLOAT, $1.value); delete $1.value; }
    |               CHAR            { $$ = new ValueNode($1.loc, DTYPE_CHAR, $1.value); delete $1.value; }
    |               BOOL            { $$ = new ValueNode($1.loc, DTYPE_BOOL, $1.value); delete $1.value; }
    ;

ident:              IDENTIFIER      { $$ = new IdentifierNode($1.loc, $1.value); delete $1.value; }
    ;

%%

void yyerror(const char* s) {
    printf( "%s\n", s);
}