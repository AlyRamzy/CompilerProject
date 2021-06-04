%{
#include "nodes.h"
#include "parser.hpp"
#include <stdio.h>
using namespace std;

void saveLoc();
void tokenize();
void advanceCursor();

Location curLoc = {1,0,0};
%}

DIGIT               [0-9]
INTEGER             ([1-9][0-9]*)|0 
EXP                 [eE][-+]?{INTEGER}
FLOAT               {INTEGER}\.{INTEGER}{EXP}?|{INTEGER}{EXP}
LETTER              [a-zA-Z_]
IDENTIFIER          {LETTER}({LETTER}|{DIGIT})*

%%

\n                                  curLoc.lineNum++; curLoc.pos = 0;
\r                                  ;
\t                                  curLoc.pos += 4;
" "                                 curLoc.pos++;

"int"                         saveLoc(); return TYPE_INT_TOKEN;   
"float"                       saveLoc(); return TYPE_FLOAT_TOKEN; 
"char"                        saveLoc(); return TYPE_CHAR_TOKEN;  
"bool"                        saveLoc(); return TYPE_BOOL_TOKEN;  
"void"                        saveLoc(); return TYPE_VOID_TOKEN;  

"const"                       saveLoc(); return CONST_TOKEN;       
"if"                          saveLoc(); return IF_TOKEN;           
"else"                        saveLoc(); return ELSE_TOKEN;        
"switch"                      saveLoc(); return SWITCH_TOKEN;      
"case"                        saveLoc(); return CASE_TOKEN;        
"default"                     saveLoc(); return DEFAULT_TOKEN;     
"for"                         saveLoc(); return FOR_TOKEN;         
"while"                       saveLoc(); return WHILE_TOKEN;       
"repeat"                      saveLoc(); return REPEAT_TOKEN;      
"until"                       saveLoc(); return UNTIL_TOKEN;       
"break"                       saveLoc(); return BREAK_TOKEN;       
"continue"                    saveLoc(); return CONTINUE_TOKEN;    
"return"                      saveLoc(); return RETURN_TOKEN;      
"enum"                        saveLoc(); return ENUM_TOKEN;
        
"=="                          saveLoc(); return EQ_TOKEN;           
"!="                          saveLoc(); return NEQ_TOKEN;       
">="                          saveLoc(); return GTE_TOKEN;   
"<="                          saveLoc(); return LTE_TOKEN;                 
"&&"                          saveLoc(); return LOGICAL_AND_TOKEN;     
"||"                          saveLoc(); return LOGICAL_OR_TOKEN;      
[-+*/%&|^~!<>=(){}[\],:;]     saveLoc(); return yytext[0];       

{INTEGER}                     tokenize(); return INTEGER_TOKEN;        
{FLOAT}                       tokenize(); return FLOAT_TOKEN;          
(\'.\')                       tokenize(); return CHAR_TOKEN;           
"true"                        tokenize(); return BOOL_TOKEN;           
"false"                       tokenize(); return BOOL_TOKEN;           
{IDENTIFIER}                  tokenize(); return IDENTIFIER_TOKEN;     

%%

// Subroutines
void advanceCursor(){
    curLoc.pos += yyleng;
}

void saveLoc() {
    curLoc.len = yyleng;

    yylval.location = curLoc;
    yylval.location.pos++;
    


    advanceCursor();
}

void tokenize() {
    curLoc.len = yyleng;

    yylval.token.value = strdup(yytext);
    yylval.token.loc = curLoc;
    yylval.token.loc.pos++;
  

    advanceCursor();
}

int yywrap() {
    return 1;
}
