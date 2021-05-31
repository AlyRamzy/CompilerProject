/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TYPE_INT_TOKEN = 258,
    TYPE_FLOAT_TOKEN = 259,
    TYPE_CHAR_TOKEN = 260,
    TYPE_BOOL_TOKEN = 261,
    TYPE_VOID_TOKEN = 262,
    CONST_TOKEN = 263,
    IF_TOKEN = 264,
    ELSE_TOKEN = 265,
    SWITCH_TOKEN = 266,
    CASE_TOKEN = 267,
    DEFAULT_TOKEN = 268,
    FOR_TOKEN = 269,
    WHILE_TOKEN = 270,
    REPEAT_TOKEN = 271,
    UNTIL_TOKEN = 272,
    BREAK_TOKEN = 273,
    CONTINUE_TOKEN = 274,
    RETURN_TOKEN = 275,
    ENUM_TOKEN = 276,
    LOGICAL_AND_TOKEN = 277,
    LOGICAL_OR_TOKEN = 278,
    EQ_TOKEN = 279,
    NEQ_TOKEN = 280,
    GTE_TOKEN = 281,
    LTE_TOKEN = 282,
    INTEGER_TOKEN = 283,
    FLOAT_TOKEN = 284,
    CHAR_TOKEN = 285,
    BOOL_TOKEN = 286,
    IDENTIFIER_TOKEN = 287,
    U_PLUS_TOKEN = 288,
    U_MINUS_TOKEN = 289,
    IF_UNMAT = 290
  };
#endif
/* Tokens.  */
#define TYPE_INT_TOKEN 258
#define TYPE_FLOAT_TOKEN 259
#define TYPE_CHAR_TOKEN 260
#define TYPE_BOOL_TOKEN 261
#define TYPE_VOID_TOKEN 262
#define CONST_TOKEN 263
#define IF_TOKEN 264
#define ELSE_TOKEN 265
#define SWITCH_TOKEN 266
#define CASE_TOKEN 267
#define DEFAULT_TOKEN 268
#define FOR_TOKEN 269
#define WHILE_TOKEN 270
#define REPEAT_TOKEN 271
#define UNTIL_TOKEN 272
#define BREAK_TOKEN 273
#define CONTINUE_TOKEN 274
#define RETURN_TOKEN 275
#define ENUM_TOKEN 276
#define LOGICAL_AND_TOKEN 277
#define LOGICAL_OR_TOKEN 278
#define EQ_TOKEN 279
#define NEQ_TOKEN 280
#define GTE_TOKEN 281
#define LTE_TOKEN 282
#define INTEGER_TOKEN 283
#define FLOAT_TOKEN 284
#define CHAR_TOKEN 285
#define BOOL_TOKEN 286
#define IDENTIFIER_TOKEN 287
#define U_PLUS_TOKEN 288
#define U_MINUS_TOKEN 289
#define IF_UNMAT 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "parser.y" /* yacc.c:1909  */

    BlockNode*                  blockNode;
    StatementNode*              stmtNode;
    VarDeclarationNode*         varDeclNode;
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

#line 150 "parser.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
