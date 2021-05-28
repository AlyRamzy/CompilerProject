%{
#include "utils.h"
#include <stdio.h>
using namespace std;

extern int yylex();
extern Location curLoc;

void yyerror(const char* s);
%}

%union {
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
%token <location> INC
%token <location> DEC
%token <location> SHL
%token <location> SHR
%token <location> LOGICAL_AND
%token <location> LOGICAL_OR
%token <location> EQUAL
%token <location> NOT_EQUAL
%token <location> GREATER_EQUAL
%token <location> LESS_EQUAL

// Values
%token <token> INTEGER
%token <token> FLOAT
%token <token> CHAR
%token <token> BOOL
%token <token> IDENTIFIER

%type <location>  '-' '+' '*' '/' '%' '&' '|' '^' '~' '!' '<' '>' '=' '(' ')' '{' '}' '[' ']' ',' ':' ';'

%right      '='
%left       LOGICAL_OR
%left       LOGICAL_AND
%left       '|'
%left       '^'
%left       '&'
%left       EQUAL NOT_EQUAL
%left       LESS_EQUAL GREATER_EQUAL '<' '>'
%left       SHR SHL
%left       '-' '+'
%left       '*' '/' '%'
%right      '!' '~'
%right      U_PLUS U_MINUS
%right      PRE_INC PRE_DEC
%left       SUF_INC SUF_DEC

%nonassoc   IF_UNMAT
%nonassoc   ELSE

%%

program:            /* empty */                 {  }
    |               stmt_list                   {  }
    ;

stmt_list:          stmt                        {  }
    |               stmt_block                  {  }
    |               stmt_list stmt              {  }
    |               stmt_list stmt_block        {  }
    ;

stmt_block:         '{' '}'                     {  }
    |               '{' stmt_list '}'           {  }
    ;

stmt:               ';'                         {  }
    |               BREAK ';'                   {  }
    |               CONTINUE ';'                {  }
    |               expression ';'              {  }
    |               var_decl ';'                {  }
    |               if_stmt                     {  }
    |               switch_stmt                 {  }
    |               case_stmt                   {  }
    |               while_stmt                  {  }
    |               repeat_until_stmt ';'       {  }
    |               for_stmt                    {  }
    |               function                    {  }
    |               return_stmt ';'             {  }
    |               enum_stmt ';'               {  }
    ;

branch_body:        stmt                        {  }
    |               stmt_block                  {  }
    ;



var_decl:           type ident                              {  }
    |               CONST type ident                        {  }
    |               type ident '=' expression               {  }
    |               CONST type ident '=' expression         {  }
    ;


expression:         expr_typ_1
    |               expr_typ_2
    |               expr_typ_3
    ;

expr_typ_1:         expression '=' expression               {  }
    |               expression '+' expression               {  }
    |               expression '-' expression               {  }
    |               expression '*' expression               {  }
    |               expression '/' expression               {  }
    |               expression '%' expression               {  }
    |               expression '&' expression               {  }
    |               expression '|' expression               {  }
    |               expression '^' expression               {  }
    |               expression SHL expression               {  }
    |               expression SHR expression               {  }
    |               expression LOGICAL_AND expression       {  }
    |               expression LOGICAL_OR expression        {  }
    |               expression '>' expression               {  }
    |               expression GREATER_EQUAL expression     {  }
    |               expression '<' expression               {  }
    |               expression LESS_EQUAL expression        {  }
    |               expression EQUAL expression             {  }
    |               expression NOT_EQUAL expression         {  }
    |               '+' expression %prec U_PLUS             {  }
    |               '-' expression %prec U_MINUS            {  }
    |               '~' expression                          {  }
    |               '!' expression                          {  }
    ;

expr_typ_2:         INC expr_typ_3 %prec PRE_INC                {  }
    |               DEC expr_typ_3 %prec PRE_DEC                {  }
    |               expr_typ_3 INC %prec SUF_INC                {  }
    |               expr_typ_3 DEC %prec SUF_DEC                {  }
    ;

expr_typ_3:         '(' expression ')'                      {  }
    |               value                                   {  }
    |               ident                                   {  }
    |               function_call                           {  }
    ;


if_stmt:            unmatched_if_stmt
    |               matched_if_stmt
    ;

unmatched_if_stmt:  IF '(' expression ')' branch_body %prec IF_UNMAT    {  }
    ;

matched_if_stmt:    IF '(' expression ')' branch_body ELSE branch_body  {  }
    ;


switch_stmt:        SWITCH '(' expression ')' branch_body   {  }
    ;

case_stmt:          CASE expression ':' stmt                {  }
    |               DEFAULT ':' stmt                        {  }
    ;


while_stmt:         WHILE '(' expression ')' branch_body                {  }
    ;

repeat_until_stmt:  REPEAT branch_body UNTIL '(' expression ')'         {  }
    ;

for_stmt:           for_header branch_body                              {  }
    ;

for_header:         FOR '(' for_init_stmt ';' for_expr ';' for_expr ')' {  }
    ;

for_init_stmt:      /* empty */                                         {  }
    |               var_decl                                            {  }
    |               expression                                          {  }
    ;

for_expr:           /* empty */                                         {  }
    |               expression                                          {  }
    ;


function:           function_header stmt_block          {  }
    ;

function_header:    type ident '(' param_list ')'       {  }
    ;

param_list:         /* empty */                         {  }
    |               var_decl                            {  }
    |               param_list_ext ',' var_decl         {  }
    ;

param_list_ext:     var_decl                            {  }
    |               param_list_ext ',' var_decl         {  }
    ;

function_call:      ident '(' arg_list ')'              {  }
    ;

arg_list:           /* empty */                         {  }
    |               expression                          {  }
    |               arg_list_ext ',' expression         {  }
    ;

arg_list_ext:       expression                          {  }
    |               arg_list_ext ',' expression         {  }
    ;

return_stmt:        RETURN expression                   {  }
    |               RETURN                              {  }
    ;


enum_stmt:          ENUM enum_name '{' enum_elements '}'   {  }
    ;

enum_elements:  /* empty */                                  {  }
    |               ident                                    {  }
    |               ident '=' expression                     {  }
    |               enum_list_ext ',' ident                  {  }
    |               enum_list_ext ',' ident '=' expression   {  }
    ;
enum_name:          /* empty */                         {  }
    |               ident                               {  }
    ;
enum_list_ext:      /* empty */                              {  }
    |               ident                                    {  }
    |               ident '=' expression                     {  }
    |               enum_list_ext ',' ident                  {  }
    |               enum_list_ext ',' ident '=' expression   {  }
    ;
type:               TYPE_INT        {  }
    |               TYPE_FLOAT      {  }
    |               TYPE_CHAR       {  }
    |               TYPE_BOOL       {  }
    |               TYPE_VOID       {  }
    ;

value:              INTEGER         {  }
    |               FLOAT           {  }
    |               CHAR            {  }
    |               BOOL            {  }
    ;

ident:              IDENTIFIER      {  }
    ;

%%

void yyerror(const char* s) {
    printf( "%s\n", s);
}