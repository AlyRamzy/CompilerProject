%{
#include "utils.h"
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
FLOAT               {INTEGER}\.{INTEGER}
EXP                 [eE][-+]?{INTEGER}
REAL                {INTEGER}{EXP}|{FLOAT}{EXP}?
LETTER              [a-zA-Z_]
IDENTIFIER          {LETTER}({LETTER}|{DIGIT})*

%%

\n                                  curLoc.lineNum++; curLoc.pos = 0;
\r                                  ;
\t                                  curLoc.pos += 4;
" "                                 curLoc.pos++;

"int"                         saveLoc(); return TYPE_INT;   
"float"                       saveLoc(); return TYPE_FLOAT; 
"char"                        saveLoc(); return TYPE_CHAR;  
"bool"                        saveLoc(); return TYPE_BOOL;  
"void"                        saveLoc(); return TYPE_VOID;  

"const"                       saveLoc(); return CONST;       
"if"                          saveLoc(); return IF;           
"else"                        saveLoc(); return ELSE;        
"switch"                      saveLoc(); return SWITCH;      
"case"                        saveLoc(); return CASE;        
"default"                     saveLoc(); return DEFAULT;     
"for"                         saveLoc(); return FOR;         
"while"                       saveLoc(); return WHILE;       
"repeat"                      saveLoc(); return REPEAT;      
"until"                       saveLoc(); return UNTIL;       
"break"                       saveLoc(); return BREAK;       
"continue"                    saveLoc(); return CONTINUE;    
"return"                      saveLoc(); return RETURN;      
"enum"                        saveLoc(); return ENUM;

"++"                          saveLoc(); return INC;             
"--"                          saveLoc(); return DEC;             
"=="                          saveLoc(); return EQUAL;           
"!="                          saveLoc(); return NOT_EQUAL;       
">="                          saveLoc(); return GREATER_EQUAL;   
"<="                          saveLoc(); return LESS_EQUAL;      
"<<"                          saveLoc(); return SHL;             
">>"                          saveLoc(); return SHR;             
"&&"                          saveLoc(); return LOGICAL_AND;     
"||"                          saveLoc(); return LOGICAL_OR;      
[-+*/%&|^~!<>=(){}[\],:;]     saveLoc(); return yytext[0];       

{INTEGER}                     tokenize(); return INTEGER;        
{REAL}                        tokenize(); return FLOAT;          
(\'.\')                       tokenize(); return CHAR;           
"true"                        tokenize(); return BOOL;           
"false"                       tokenize(); return BOOL;           
{IDENTIFIER}                  tokenize(); return IDENTIFIER;     

%%

// Subroutines
void advanceCursor(){
    curLoc.pos += yyleng;
}

void saveLoc() {
    curLoc.len = yyleng;

    yylval.location = curLoc;
    yylval.location.pos++;
    
    printf( "%s\t", yytext);

    advanceCursor();
}

void tokenize() {
    curLoc.len = yyleng;

    yylval.token.value = strdup(yytext);
    yylval.token.loc = curLoc;
    yylval.token.loc.pos++;
    printf( "%s\t", yytext);

    advanceCursor();
}

int yywrap() {
    return 1;
}
