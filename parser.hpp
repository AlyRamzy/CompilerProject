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
    TYPE_INT = 258,
    TYPE_FLOAT = 259,
    TYPE_CHAR = 260,
    TYPE_BOOL = 261,
    TYPE_VOID = 262,
    CONST = 263,
    IF = 264,
    ELSE = 265,
    SWITCH = 266,
    CASE = 267,
    DEFAULT = 268,
    FOR = 269,
    WHILE = 270,
    REPEAT = 271,
    UNTIL = 272,
    BREAK = 273,
    CONTINUE = 274,
    RETURN = 275,
    ENUM = 276,
    LOGICAL_AND = 277,
    LOGICAL_OR = 278,
    EQ = 279,
    NEQ = 280,
    GTE = 281,
    LTE = 282,
    INTEGER = 283,
    FLOAT = 284,
    CHAR = 285,
    BOOL = 286,
    IDENTIFIER = 287,
    U_PLUS = 288,
    U_MINUS = 289,
    IF_UNMAT = 290
  };
#endif
/* Tokens.  */
#define TYPE_INT 258
#define TYPE_FLOAT 259
#define TYPE_CHAR 260
#define TYPE_BOOL 261
#define TYPE_VOID 262
#define CONST 263
#define IF 264
#define ELSE 265
#define SWITCH 266
#define CASE 267
#define DEFAULT 268
#define FOR 269
#define WHILE 270
#define REPEAT 271
#define UNTIL 272
#define BREAK 273
#define CONTINUE 274
#define RETURN 275
#define ENUM 276
#define LOGICAL_AND 277
#define LOGICAL_OR 278
#define EQ 279
#define NEQ 280
#define GTE 281
#define LTE 282
#define INTEGER 283
#define FLOAT 284
#define CHAR 285
#define BOOL 286
#define IDENTIFIER 287
#define U_PLUS 288
#define U_MINUS 289
#define IF_UNMAT 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 12 "parser.y" /* yacc.c:1909  */

    Token token;
    Location location;

#line 129 "parser.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
