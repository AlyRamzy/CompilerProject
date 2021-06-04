/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */


#include<iostream>
#include<string>

#include"parse_tree/parse_tree.h"
using namespace std;

extern int yylex();
extern Location curLoc;

void yyerror(const char* s);

StatementNode* programRoot = NULL;

#line 82 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
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
#line 17 "parser.y" /* yacc.c:355  */

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

    StmtList*                   stmtList;
    ExprList*                   exprList;
    VarList*                    varList;

    Token token;
    Location location;

#line 218 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 235 "parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  77
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   890

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  183

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,     2,     2,    37,    38,     2,
      46,    47,    35,    34,    52,    33,     2,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    53,    54,
      43,    45,    44,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    50,     2,    51,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,    39,    49,    41,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    55,    56,
      57
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   137,   137,   138,   141,   142,   143,   144,   147,   148,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   171,   172,   177,
     178,   179,   180,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   212,   213,
     216,   219,   220,   224,   227,   230,   233,   236,   237,   238,
     241,   242,   245,   248,   251,   252,   253,   256,   257,   260,
     263,   264,   265,   268,   269,   272,   273,   277,   280,   281,
     284,   285,   286,   287,   288,   291,   292,   293,   294,   297,
     298,   299,   300,   301,   304,   305,   306,   307,   310
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYPE_INT_TOKEN", "TYPE_FLOAT_TOKEN",
  "TYPE_CHAR_TOKEN", "TYPE_BOOL_TOKEN", "TYPE_VOID_TOKEN", "CONST_TOKEN",
  "IF_TOKEN", "ELSE_TOKEN", "SWITCH_TOKEN", "CASE_TOKEN", "DEFAULT_TOKEN",
  "FOR_TOKEN", "WHILE_TOKEN", "REPEAT_TOKEN", "UNTIL_TOKEN", "BREAK_TOKEN",
  "CONTINUE_TOKEN", "RETURN_TOKEN", "ENUM_TOKEN", "LOGICAL_AND_TOKEN",
  "LOGICAL_OR_TOKEN", "EQ_TOKEN", "NEQ_TOKEN", "GTE_TOKEN", "LTE_TOKEN",
  "INTEGER_TOKEN", "FLOAT_TOKEN", "CHAR_TOKEN", "BOOL_TOKEN",
  "IDENTIFIER_TOKEN", "'-'", "'+'", "'*'", "'/'", "'%'", "'&'", "'|'",
  "'^'", "'~'", "'!'", "'<'", "'>'", "'='", "'('", "')'", "'{'", "'}'",
  "'['", "']'", "','", "':'", "';'", "U_PLUS_TOKEN", "U_MINUS_TOKEN",
  "IF_UNMAT", "$accept", "program", "stmt_list", "stmt_block", "stmt",
  "branch_body", "var_decl", "expression", "if_stmt", "switch_stmt",
  "case_stmt", "while_stmt", "repeat_until_stmt", "for_stmt", "for_header",
  "for_init_stmt", "for_expr", "function", "function_header", "param_list",
  "param_list_ext", "function_call", "arg_list", "arg_list_ext",
  "return_stmt", "enum_stmt", "enum_name", "enum_elements",
  "enum_list_ext", "type", "value", "ident", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,    45,    43,    42,    47,    37,    38,   124,
      94,   126,    33,    60,    62,    61,    40,    41,   123,   125,
      91,    93,    44,    58,    59,   288,   289,   290
};
# endif

#define YYPACT_NINF -51

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-51)))

#define YYTABLE_NINF -99

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     168,   -41,   -51,   -51,   -51,   -51,   -51,    16,   -43,   -37,
      -4,   -48,   -35,   -14,   376,    -1,     1,    -4,     8,   -51,
     -51,   -51,   -51,   -51,    -4,    -4,    -4,    -4,    -4,   272,
     -51,    58,   220,   -51,   -51,     2,   472,   -51,   -51,   -51,
     -51,     5,   -51,   376,   -51,    13,   -51,    35,    42,     8,
     -51,   -11,   -51,   -51,   -51,     8,    -4,    -4,   495,   428,
     447,    -4,   -51,   -51,    45,   -51,   -51,   740,    22,   -51,
     -51,   -51,   -51,   -51,   610,   -51,   324,   -51,   -51,   -51,
     -51,    -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,
      -4,    -4,    -4,    -4,    -4,    -4,    -4,   -51,   -51,   -51,
     -51,   -51,   -51,     3,    -4,    -4,    52,   636,   662,   428,
     -51,   -51,   740,    46,     8,   688,    53,     8,   -51,   -51,
     784,   763,   846,   846,    77,    77,    56,    56,   -51,   -51,
     -51,   841,   805,   826,    77,    77,    -4,    61,   740,   518,
      55,    51,    -4,   376,   376,   -51,    -4,    63,   376,    -4,
      57,    64,    -9,   740,    65,    68,    66,   -51,    -4,   740,
     109,   -51,   740,    67,   -51,   714,   -51,     8,    -4,   -51,
      61,   541,   376,    -4,   -51,     0,   564,    70,   -51,    76,
      -4,   -51,   587
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    99,   100,   101,   102,   103,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    86,    88,   104,
     105,   106,   107,   108,     0,     0,     0,     0,     0,     0,
      10,     0,     0,     5,     4,     0,     0,    15,    16,    17,
      18,     0,    20,     0,    21,     0,    57,     0,     0,     0,
      55,    56,    25,    26,    24,     0,     0,     0,     0,     0,
      67,     0,    28,    27,     0,    11,    12,    85,     0,    89,
      51,    50,    52,    53,     0,     8,     0,     1,     7,     6,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    13,    19,    65,
      72,    22,    23,    29,     0,    80,    30,     0,     0,     0,
      62,    68,    69,     0,     0,     0,     0,    90,    54,     9,
      42,    43,    48,    49,    45,    47,    35,    34,    36,    37,
      38,    39,    40,    41,    46,    44,     0,    74,    33,    81,
       0,     0,     0,     0,     0,    61,    70,    29,     0,     0,
       0,     0,    91,    31,    75,     0,     0,    79,     0,    32,
      58,    60,    71,     0,    63,     0,    87,     0,     0,    73,
       0,    82,     0,    70,    64,    93,    92,    76,    59,     0,
       0,    66,    94
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -51,   -51,    95,    12,    31,   -39,   -50,   -10,   -51,   -51,
     -51,   -51,   -51,   -51,   -51,   -51,   -46,   -51,   -51,   -51,
     -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,    -6,
     -51,   -16
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    31,    32,    62,    63,    64,    35,    36,    37,    38,
      39,    40,    41,    42,    43,   113,   163,    44,    45,   155,
     156,    46,   140,   141,    47,    48,    68,   150,   151,    49,
      50,    51
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      58,    55,    69,    56,    99,    59,    52,    67,    53,    57,
     111,    60,    33,    54,    70,    71,    72,    73,    74,     2,
       3,     4,     5,     6,    19,    20,    21,    22,    23,    24,
      25,    34,    61,   103,   104,   105,   168,    26,    27,   106,
      23,    33,    28,   -95,    78,   180,   107,   108,   136,   137,
     112,   115,   -97,    65,   114,    66,    80,   100,    77,    98,
      34,    29,   116,    79,     2,     3,     4,     5,     6,     7,
     117,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   154,    78,   101,
     110,    89,    90,    91,   138,   139,   102,   142,   147,   149,
     146,   152,   157,   158,   160,   161,   166,    79,   136,   164,
      87,    88,    89,    90,    91,   169,   167,   -77,   170,   172,
     177,   173,   -78,   181,    76,     0,   153,   179,     0,     0,
       0,   114,   159,   178,     0,     0,   162,     0,     0,   165,
     145,     0,     0,     0,     0,     0,     0,     0,   171,     0,
       0,   175,     0,     0,     0,     0,     0,     0,   176,     0,
       0,     0,     0,   162,   114,     0,     0,     0,    -2,     1,
     182,     2,     3,     4,     5,     6,     7,     8,     0,     9,
      10,    11,    12,    13,    14,     0,    15,    16,    17,    18,
       0,     0,     0,     0,     0,     0,    19,    20,    21,    22,
      23,    24,    25,     0,     0,     0,     0,     0,     0,    26,
      27,     0,     0,     0,    28,     0,    29,     0,     0,     0,
      -3,     1,    30,     2,     3,     4,     5,     6,     7,     8,
       0,     9,    10,    11,    12,    13,    14,     0,    15,    16,
      17,    18,     0,     0,     0,     0,     0,     0,    19,    20,
      21,    22,    23,    24,    25,     0,     0,     0,     0,     0,
       0,    26,    27,     0,     0,     0,    28,     0,    29,     0,
       0,     0,     0,     1,    30,     2,     3,     4,     5,     6,
       7,     8,     0,     9,    10,    11,    12,    13,    14,     0,
      15,    16,    17,    18,     0,     0,     0,     0,     0,     0,
      19,    20,    21,    22,    23,    24,    25,     0,     0,     0,
       0,     0,     0,    26,    27,     0,     0,     0,    28,     0,
      29,    75,     0,     0,     0,     1,    30,     2,     3,     4,
       5,     6,     7,     8,     0,     9,    10,    11,    12,    13,
      14,     0,    15,    16,    17,    18,     0,     0,     0,     0,
       0,     0,    19,    20,    21,    22,    23,    24,    25,     0,
       0,     0,     0,     0,     0,    26,    27,     0,     0,     0,
      28,     0,    29,   119,     0,     0,     0,     1,    30,     2,
       3,     4,     5,     6,     7,     8,     0,     9,    10,    11,
      12,    13,    14,     0,    15,    16,    17,    18,     0,     0,
       0,     0,     0,     0,    19,    20,    21,    22,    23,    24,
      25,     0,     0,     0,     0,     0,     0,    26,    27,     0,
       0,     0,    28,     0,    29,     0,     0,     0,     0,     1,
      30,     2,     3,     4,     5,     6,     7,     8,     0,     9,
      10,    11,    12,    13,    14,     0,    15,    16,    17,    18,
       2,     3,     4,     5,     6,     7,    19,    20,    21,    22,
      23,    24,    25,     0,     0,     0,     0,     0,     0,    26,
      27,     0,     0,     0,    28,    19,    20,    21,    22,    23,
      24,    25,    30,     0,     0,     0,     0,     0,    26,    27,
       0,     0,     0,    28,    81,    82,    83,    84,    85,    86,
       0,     0,     0,     0,     0,    87,    88,    89,    90,    91,
      92,    93,    94,     0,     0,    95,    96,    81,    82,    83,
      84,    85,    86,     0,     0,     0,    97,     0,    87,    88,
      89,    90,    91,    92,    93,    94,     0,     0,    95,    96,
      81,    82,    83,    84,    85,    86,     0,     0,   109,     0,
       0,    87,    88,    89,    90,    91,    92,    93,    94,     0,
       0,    95,    96,    81,    82,    83,    84,    85,    86,     0,
     -83,     0,     0,     0,    87,    88,    89,    90,    91,    92,
      93,    94,     0,     0,    95,    96,    81,    82,    83,    84,
      85,    86,     0,   -84,     0,     0,     0,    87,    88,    89,
      90,    91,    92,    93,    94,     0,     0,    95,    96,    81,
      82,    83,    84,    85,    86,     0,   -96,     0,     0,     0,
      87,    88,    89,    90,    91,    92,    93,    94,     0,     0,
      95,    96,    81,    82,    83,    84,    85,    86,     0,   -98,
       0,     0,     0,    87,    88,    89,    90,    91,    92,    93,
      94,     0,     0,    95,    96,     0,     0,   118,    81,    82,
      83,    84,    85,    86,     0,     0,     0,     0,     0,    87,
      88,    89,    90,    91,    92,    93,    94,     0,     0,    95,
      96,     0,     0,   143,    81,    82,    83,    84,    85,    86,
       0,     0,     0,     0,     0,    87,    88,    89,    90,    91,
      92,    93,    94,     0,     0,    95,    96,     0,     0,   144,
      81,    82,    83,    84,    85,    86,     0,     0,     0,     0,
       0,    87,    88,    89,    90,    91,    92,    93,    94,     0,
       0,    95,    96,     0,     0,   148,    81,    82,    83,    84,
      85,    86,     0,     0,     0,     0,     0,    87,    88,    89,
      90,    91,    92,    93,    94,     0,     0,    95,    96,     0,
       0,   174,    81,    82,    83,    84,    85,    86,     0,     0,
       0,     0,     0,    87,    88,    89,    90,    91,    92,    93,
      94,     0,     0,    95,    96,    81,     0,    83,    84,    85,
      86,     0,     0,     0,     0,     0,    87,    88,    89,    90,
      91,    92,    93,    94,     0,     0,    95,    96,    83,    84,
      85,    86,     0,     0,     0,     0,     0,    87,    88,    89,
      90,    91,    92,    93,    94,     0,     0,    95,    96,    83,
      84,    85,    86,     0,     0,     0,     0,     0,    87,    88,
      89,    90,    91,    92,     0,    94,     0,     0,    95,    96,
      83,    84,    85,    86,     0,     0,     0,     0,     0,    87,
      88,    89,    90,    91,    92,    83,    84,    85,    86,    95,
      96,     0,    85,    86,    87,    88,    89,    90,    91,    87,
      88,    89,    90,    91,    95,    96,     0,     0,     0,    95,
      96
};

static const yytype_int16 yycheck[] =
{
      10,     7,    18,    46,    43,    53,    47,    17,    49,    46,
      60,    46,     0,    54,    24,    25,    26,    27,    28,     3,
       4,     5,     6,     7,    28,    29,    30,    31,    32,    33,
      34,     0,    46,    49,    45,    46,    45,    41,    42,    55,
      32,    29,    46,    52,    32,    45,    56,    57,    45,    46,
      60,    61,    52,    54,    60,    54,    54,    45,     0,    54,
      29,    48,    17,    32,     3,     4,     5,     6,     7,     8,
      48,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,   137,    76,    54,
      59,    35,    36,    37,   104,   105,    54,    45,   114,    46,
      54,   117,    47,    52,   143,   144,    49,    76,    45,   148,
      33,    34,    35,    36,    37,    47,    52,    52,    52,    10,
     170,    54,    52,    47,    29,    -1,   136,   173,    -1,    -1,
      -1,   137,   142,   172,    -1,    -1,   146,    -1,    -1,   149,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   158,    -1,
      -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,   168,    -1,
      -1,    -1,    -1,   173,   170,    -1,    -1,    -1,     0,     1,
     180,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    -1,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    46,    -1,    48,    -1,    -1,    -1,
       0,     1,    54,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    -1,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    46,    -1,    48,    -1,
      -1,    -1,    -1,     1,    54,     3,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    -1,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    46,    -1,
      48,    49,    -1,    -1,    -1,     1,    54,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    -1,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      46,    -1,    48,    49,    -1,    -1,    -1,     1,    54,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    -1,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    46,    -1,    48,    -1,    -1,    -1,    -1,     1,
      54,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    -1,    18,    19,    20,    21,
       3,     4,     5,     6,     7,     8,    28,    29,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    46,    28,    29,    30,    31,    32,
      33,    34,    54,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    46,    22,    23,    24,    25,    26,    27,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    -1,    -1,    43,    44,    22,    23,    24,
      25,    26,    27,    -1,    -1,    -1,    54,    -1,    33,    34,
      35,    36,    37,    38,    39,    40,    -1,    -1,    43,    44,
      22,    23,    24,    25,    26,    27,    -1,    -1,    53,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    -1,
      -1,    43,    44,    22,    23,    24,    25,    26,    27,    -1,
      52,    -1,    -1,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    -1,    43,    44,    22,    23,    24,    25,
      26,    27,    -1,    52,    -1,    -1,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    -1,    -1,    43,    44,    22,
      23,    24,    25,    26,    27,    -1,    52,    -1,    -1,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    -1,    -1,
      43,    44,    22,    23,    24,    25,    26,    27,    -1,    52,
      -1,    -1,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    -1,    43,    44,    -1,    -1,    47,    22,    23,
      24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    -1,    43,
      44,    -1,    -1,    47,    22,    23,    24,    25,    26,    27,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    -1,    -1,    43,    44,    -1,    -1,    47,
      22,    23,    24,    25,    26,    27,    -1,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    -1,
      -1,    43,    44,    -1,    -1,    47,    22,    23,    24,    25,
      26,    27,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    -1,    -1,    43,    44,    -1,
      -1,    47,    22,    23,    24,    25,    26,    27,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    -1,    43,    44,    22,    -1,    24,    25,    26,
      27,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,
      37,    38,    39,    40,    -1,    -1,    43,    44,    24,    25,
      26,    27,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    -1,    -1,    43,    44,    24,
      25,    26,    27,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    36,    37,    38,    -1,    40,    -1,    -1,    43,    44,
      24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    37,    38,    24,    25,    26,    27,    43,
      44,    -1,    26,    27,    33,    34,    35,    36,    37,    33,
      34,    35,    36,    37,    43,    44,    -1,    -1,    -1,    43,
      44
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,     8,     9,    11,
      12,    13,    14,    15,    16,    18,    19,    20,    21,    28,
      29,    30,    31,    32,    33,    34,    41,    42,    46,    48,
      54,    59,    60,    61,    62,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    75,    76,    79,    82,    83,    87,
      88,    89,    47,    49,    54,    87,    46,    46,    65,    53,
      46,    46,    61,    62,    63,    54,    54,    65,    84,    89,
      65,    65,    65,    65,    65,    49,    60,     0,    61,    62,
      54,    22,    23,    24,    25,    26,    27,    33,    34,    35,
      36,    37,    38,    39,    40,    43,    44,    54,    54,    63,
      61,    54,    54,    89,    45,    46,    89,    65,    65,    53,
      62,    64,    65,    73,    87,    65,    17,    48,    47,    49,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    45,    46,    65,    65,
      80,    81,    45,    47,    47,    62,    54,    89,    47,    46,
      85,    86,    89,    65,    64,    77,    78,    47,    52,    65,
      63,    63,    65,    74,    63,    65,    49,    52,    45,    47,
      52,    65,    10,    54,    47,    89,    65,    64,    63,    74,
      45,    47,    65
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    58,    59,    59,    60,    60,    60,    60,    61,    61,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    63,    63,    64,
      64,    64,    64,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    66,    66,
      67,    68,    68,    69,    70,    71,    72,    73,    73,    73,
      74,    74,    75,    76,    77,    77,    77,    78,    78,    79,
      80,    80,    80,    81,    81,    82,    82,    83,    84,    84,
      85,    85,    85,    85,    85,    86,    86,    86,    86,    87,
      87,    87,    87,    87,    88,    88,    88,    88,    89
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     1,     2,     2,     2,     3,
       1,     2,     2,     2,     2,     1,     1,     1,     1,     2,
       1,     1,     2,     2,     2,     2,     2,     1,     1,     2,
       3,     4,     5,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     2,     3,     1,     1,     1,     5,     7,
       5,     4,     3,     5,     6,     2,     8,     0,     1,     1,
       0,     1,     2,     5,     0,     1,     3,     1,     3,     4,
       0,     1,     3,     1,     3,     2,     1,     5,     0,     1,
       0,     1,     3,     3,     5,     1,     3,     3,     5,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 59: /* program  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).blockNode) != NULL) {
        delete ((*yyvaluep).blockNode);
        ((*yyvaluep).blockNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1347 "parser.cpp" /* yacc.c:1257  */
        break;

    case 60: /* stmt_list  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).stmtList) != NULL) {
        delete ((*yyvaluep).stmtList);
        ((*yyvaluep).stmtList) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1361 "parser.cpp" /* yacc.c:1257  */
        break;

    case 61: /* stmt_block  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).blockNode) != NULL) {
        delete ((*yyvaluep).blockNode);
        ((*yyvaluep).blockNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1375 "parser.cpp" /* yacc.c:1257  */
        break;

    case 62: /* stmt  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).stmtNode) != NULL) {
        delete ((*yyvaluep).stmtNode);
        ((*yyvaluep).stmtNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1389 "parser.cpp" /* yacc.c:1257  */
        break;

    case 63: /* branch_body  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).stmtNode) != NULL) {
        delete ((*yyvaluep).stmtNode);
        ((*yyvaluep).stmtNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1403 "parser.cpp" /* yacc.c:1257  */
        break;

    case 64: /* var_decl  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).varDeclNode) != NULL) {
        delete ((*yyvaluep).varDeclNode);
        ((*yyvaluep).varDeclNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1417 "parser.cpp" /* yacc.c:1257  */
        break;

    case 65: /* expression  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).exprNode) != NULL) {
        delete ((*yyvaluep).exprNode);
        ((*yyvaluep).exprNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1431 "parser.cpp" /* yacc.c:1257  */
        break;

    case 66: /* if_stmt  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).ifNode) != NULL) {
        delete ((*yyvaluep).ifNode);
        ((*yyvaluep).ifNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1445 "parser.cpp" /* yacc.c:1257  */
        break;

    case 67: /* switch_stmt  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).switchNode) != NULL) {
        delete ((*yyvaluep).switchNode);
        ((*yyvaluep).switchNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1459 "parser.cpp" /* yacc.c:1257  */
        break;

    case 68: /* case_stmt  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).caseStmtNode) != NULL) {
        delete ((*yyvaluep).caseStmtNode);
        ((*yyvaluep).caseStmtNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1473 "parser.cpp" /* yacc.c:1257  */
        break;

    case 69: /* while_stmt  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).whileNode) != NULL) {
        delete ((*yyvaluep).whileNode);
        ((*yyvaluep).whileNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1487 "parser.cpp" /* yacc.c:1257  */
        break;

    case 70: /* repeat_until_stmt  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).repeatUntilNode) != NULL) {
        delete ((*yyvaluep).repeatUntilNode);
        ((*yyvaluep).repeatUntilNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1501 "parser.cpp" /* yacc.c:1257  */
        break;

    case 71: /* for_stmt  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).forNode) != NULL) {
        delete ((*yyvaluep).forNode);
        ((*yyvaluep).forNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1515 "parser.cpp" /* yacc.c:1257  */
        break;

    case 72: /* for_header  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).forNode) != NULL) {
        delete ((*yyvaluep).forNode);
        ((*yyvaluep).forNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1529 "parser.cpp" /* yacc.c:1257  */
        break;

    case 73: /* for_init_stmt  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).stmtNode) != NULL) {
        delete ((*yyvaluep).stmtNode);
        ((*yyvaluep).stmtNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1543 "parser.cpp" /* yacc.c:1257  */
        break;

    case 74: /* for_expr  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).exprNode) != NULL) {
        delete ((*yyvaluep).exprNode);
        ((*yyvaluep).exprNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1557 "parser.cpp" /* yacc.c:1257  */
        break;

    case 75: /* function  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).functionNode) != NULL) {
        delete ((*yyvaluep).functionNode);
        ((*yyvaluep).functionNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1571 "parser.cpp" /* yacc.c:1257  */
        break;

    case 76: /* function_header  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).functionNode) != NULL) {
        delete ((*yyvaluep).functionNode);
        ((*yyvaluep).functionNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1585 "parser.cpp" /* yacc.c:1257  */
        break;

    case 77: /* param_list  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).varList) != NULL) {
        delete ((*yyvaluep).varList);
        ((*yyvaluep).varList) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1599 "parser.cpp" /* yacc.c:1257  */
        break;

    case 78: /* param_list_ext  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).varList) != NULL) {
        delete ((*yyvaluep).varList);
        ((*yyvaluep).varList) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1613 "parser.cpp" /* yacc.c:1257  */
        break;

    case 79: /* function_call  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).functionCallNode) != NULL) {
        delete ((*yyvaluep).functionCallNode);
        ((*yyvaluep).functionCallNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1627 "parser.cpp" /* yacc.c:1257  */
        break;

    case 80: /* arg_list  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).exprList) != NULL) {
        delete ((*yyvaluep).exprList);
        ((*yyvaluep).exprList) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1641 "parser.cpp" /* yacc.c:1257  */
        break;

    case 81: /* arg_list_ext  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).exprList) != NULL) {
        delete ((*yyvaluep).exprList);
        ((*yyvaluep).exprList) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1655 "parser.cpp" /* yacc.c:1257  */
        break;

    case 82: /* return_stmt  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).returnStmtNode) != NULL) {
        delete ((*yyvaluep).returnStmtNode);
        ((*yyvaluep).returnStmtNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1669 "parser.cpp" /* yacc.c:1257  */
        break;

    case 87: /* type  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).typeNode) != NULL) {
        delete ((*yyvaluep).typeNode);
        ((*yyvaluep).typeNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1683 "parser.cpp" /* yacc.c:1257  */
        break;

    case 88: /* value  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).valueNode) != NULL) {
        delete ((*yyvaluep).valueNode);
        ((*yyvaluep).valueNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1697 "parser.cpp" /* yacc.c:1257  */
        break;

    case 89: /* ident  */
#line 103 "parser.y" /* yacc.c:1257  */
      {
    if (((*yyvaluep).identifierNode) != NULL) {
        delete ((*yyvaluep).identifierNode);
        ((*yyvaluep).identifierNode) = NULL;
        // printf(">> DESTRUCTOR\n");
    } else {
        // printf(">> DESTRUCTOR NULL\n");
    }
}
#line 1711 "parser.cpp" /* yacc.c:1257  */
        break;


      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 137 "parser.y" /* yacc.c:1646  */
    { (yyval.blockNode) = NULL; programRoot = new BlockNode(); }
#line 1975 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 138 "parser.y" /* yacc.c:1646  */
    { (yyval.blockNode) = NULL; programRoot = new BlockNode((*(yyvsp[0].stmtList))[0]->loc, *(yyvsp[0].stmtList)); delete (yyvsp[0].stmtList); }
#line 1981 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 141 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtList) = new StmtList(); (yyval.stmtList)->push_back((yyvsp[0].stmtNode)); }
#line 1987 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 142 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtList) = new StmtList(); (yyval.stmtList)->push_back((yyvsp[0].blockNode)); }
#line 1993 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 143 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtList) = (yyvsp[-1].stmtList); (yyval.stmtList)->push_back((yyvsp[0].stmtNode)); }
#line 1999 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 144 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtList) = (yyvsp[-1].stmtList); (yyval.stmtList)->push_back((yyvsp[0].blockNode)); }
#line 2005 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 147 "parser.y" /* yacc.c:1646  */
    { (yyval.blockNode) = new BlockNode((yyvsp[-1].location)); }
#line 2011 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 148 "parser.y" /* yacc.c:1646  */
    { (yyval.blockNode) = new BlockNode((yyvsp[-2].location), *(yyvsp[-1].stmtList)); delete (yyvsp[-1].stmtList); }
#line 2017 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 151 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = new StatementNode((yyvsp[0].location)); }
#line 2023 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 152 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = new BreakStmtNode((yyvsp[-1].location)); }
#line 2029 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 153 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = new ContinueStmtNode((yyvsp[-1].location)); }
#line 2035 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 154 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = new ExprContainerNode((yyvsp[-1].exprNode)->loc, (yyvsp[-1].exprNode)); }
#line 2041 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 155 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = (yyvsp[-1].varDeclNode); }
#line 2047 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 156 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = (yyvsp[0].ifNode); }
#line 2053 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 157 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = (yyvsp[0].switchNode); }
#line 2059 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 158 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = (yyvsp[0].caseStmtNode); }
#line 2065 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 159 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = (yyvsp[0].whileNode); }
#line 2071 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 160 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = (yyvsp[-1].repeatUntilNode); }
#line 2077 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 161 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = (yyvsp[0].forNode); }
#line 2083 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 162 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = (yyvsp[0].functionNode); }
#line 2089 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 163 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = (yyvsp[-1].returnStmtNode); }
#line 2095 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 164 "parser.y" /* yacc.c:1646  */
    {  }
#line 2101 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 165 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = new ErrorNode(curLoc, "invalid syntax"); yyerrok; }
#line 2107 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 166 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = new ErrorNode(curLoc, "invalid syntax"); yyerrok; }
#line 2113 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 167 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = new ErrorNode(curLoc, "invalid syntax"); yyerrok; }
#line 2119 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 171 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = (yyvsp[0].stmtNode); }
#line 2125 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 172 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = (yyvsp[0].blockNode); }
#line 2131 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 177 "parser.y" /* yacc.c:1646  */
    { (yyval.varDeclNode) = new VarDeclarationNode((yyvsp[-1].typeNode), (yyvsp[0].identifierNode)); }
#line 2137 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 178 "parser.y" /* yacc.c:1646  */
    { (yyval.varDeclNode) = new VarDeclarationNode((yyvsp[-1].typeNode), (yyvsp[0].identifierNode), NULL, true); }
#line 2143 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 179 "parser.y" /* yacc.c:1646  */
    { (yyval.varDeclNode) = new VarDeclarationNode((yyvsp[-3].typeNode), (yyvsp[-2].identifierNode), (yyvsp[0].exprNode)); }
#line 2149 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 180 "parser.y" /* yacc.c:1646  */
    { (yyval.varDeclNode) = new VarDeclarationNode((yyvsp[-3].typeNode), (yyvsp[-2].identifierNode), (yyvsp[0].exprNode), true); }
#line 2155 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 184 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new AssignOprNode((yyvsp[-1].location), (yyvsp[-2].identifierNode), (yyvsp[0].exprNode)); }
#line 2161 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 185 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new BinaryOprNode((yyvsp[-1].location), ADD, (yyvsp[-2].exprNode), (yyvsp[0].exprNode)); }
#line 2167 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 186 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new BinaryOprNode((yyvsp[-1].location), SUB, (yyvsp[-2].exprNode), (yyvsp[0].exprNode)); }
#line 2173 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 187 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new BinaryOprNode((yyvsp[-1].location), MUL, (yyvsp[-2].exprNode), (yyvsp[0].exprNode)); }
#line 2179 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 188 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new BinaryOprNode((yyvsp[-1].location), DIV, (yyvsp[-2].exprNode), (yyvsp[0].exprNode)); }
#line 2185 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 189 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new BinaryOprNode((yyvsp[-1].location), MOD, (yyvsp[-2].exprNode), (yyvsp[0].exprNode)); }
#line 2191 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 190 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new BinaryOprNode((yyvsp[-1].location), AND, (yyvsp[-2].exprNode), (yyvsp[0].exprNode)); }
#line 2197 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 191 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new BinaryOprNode((yyvsp[-1].location), OR, (yyvsp[-2].exprNode), (yyvsp[0].exprNode)); }
#line 2203 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 192 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new BinaryOprNode((yyvsp[-1].location), XOR, (yyvsp[-2].exprNode), (yyvsp[0].exprNode)); }
#line 2209 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 193 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new BinaryOprNode((yyvsp[-1].location), LOGICAL_AND, (yyvsp[-2].exprNode), (yyvsp[0].exprNode)); }
#line 2215 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 194 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new BinaryOprNode((yyvsp[-1].location), LOGICAL_OR, (yyvsp[-2].exprNode), (yyvsp[0].exprNode)); }
#line 2221 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 195 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new BinaryOprNode((yyvsp[-1].location), GT, (yyvsp[-2].exprNode), (yyvsp[0].exprNode)); }
#line 2227 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 196 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new BinaryOprNode((yyvsp[-1].location), GTE, (yyvsp[-2].exprNode), (yyvsp[0].exprNode)); }
#line 2233 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 197 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new BinaryOprNode((yyvsp[-1].location), LT, (yyvsp[-2].exprNode), (yyvsp[0].exprNode)); }
#line 2239 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 198 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new BinaryOprNode((yyvsp[-1].location), LTE, (yyvsp[-2].exprNode), (yyvsp[0].exprNode)); }
#line 2245 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 199 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new BinaryOprNode((yyvsp[-1].location), EQ, (yyvsp[-2].exprNode), (yyvsp[0].exprNode)); }
#line 2251 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 200 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new BinaryOprNode((yyvsp[-1].location), NEQ, (yyvsp[-2].exprNode), (yyvsp[0].exprNode)); }
#line 2257 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 201 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new UnaryOprNode((yyvsp[-1].location), U_PLUS, (yyvsp[0].exprNode)); }
#line 2263 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 202 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new UnaryOprNode((yyvsp[-1].location), U_MINUS, (yyvsp[0].exprNode)); }
#line 2269 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 203 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new UnaryOprNode((yyvsp[-1].location), NOT, (yyvsp[0].exprNode)); }
#line 2275 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 204 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new UnaryOprNode((yyvsp[-1].location), LOGICAL_NOT, (yyvsp[0].exprNode)); }
#line 2281 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 205 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = new ExprContainerNode((yyvsp[-2].location), (yyvsp[-1].exprNode)); }
#line 2287 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 206 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = (yyvsp[0].valueNode); }
#line 2293 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 207 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = (yyvsp[0].identifierNode); }
#line 2299 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 208 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = (yyvsp[0].functionCallNode); }
#line 2305 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 212 "parser.y" /* yacc.c:1646  */
    { (yyval.ifNode) = new IfNode((yyvsp[-4].location), (yyvsp[-2].exprNode), (yyvsp[0].stmtNode)); }
#line 2311 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 213 "parser.y" /* yacc.c:1646  */
    { (yyval.ifNode) = new IfNode((yyvsp[-6].location), (yyvsp[-4].exprNode), (yyvsp[-2].stmtNode), (yyvsp[0].stmtNode)); }
#line 2317 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 216 "parser.y" /* yacc.c:1646  */
    { (yyval.switchNode) = new SwitchNode((yyvsp[-4].location), (yyvsp[-2].exprNode), (yyvsp[0].stmtNode)); }
#line 2323 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 219 "parser.y" /* yacc.c:1646  */
    { (yyval.caseStmtNode) = new CaseLabelNode((yyvsp[-3].location), (yyvsp[-2].exprNode), (yyvsp[0].stmtNode)); }
#line 2329 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 220 "parser.y" /* yacc.c:1646  */
    { (yyval.caseStmtNode) = new CaseLabelNode((yyvsp[-2].location), NULL, (yyvsp[0].stmtNode)); }
#line 2335 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 224 "parser.y" /* yacc.c:1646  */
    { (yyval.whileNode) = new WhileNode((yyvsp[-4].location), (yyvsp[-2].exprNode), (yyvsp[0].stmtNode)); }
#line 2341 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 227 "parser.y" /* yacc.c:1646  */
    { (yyval.repeatUntilNode) = new RepeatUntilNode((yyvsp[-5].location), (yyvsp[-1].exprNode), (yyvsp[-4].stmtNode)); }
#line 2347 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 230 "parser.y" /* yacc.c:1646  */
    { (yyval.forNode) = (yyvsp[-1].forNode); (yyval.forNode)->body = (yyvsp[0].stmtNode); }
#line 2353 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 233 "parser.y" /* yacc.c:1646  */
    { (yyval.forNode) = new ForNode((yyvsp[-7].location), (yyvsp[-5].stmtNode), (yyvsp[-3].exprNode), (yyvsp[-1].exprNode), NULL); }
#line 2359 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 236 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = NULL; }
#line 2365 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 237 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = (yyvsp[0].varDeclNode); }
#line 2371 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 238 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtNode) = (yyvsp[0].exprNode); }
#line 2377 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 241 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = NULL; }
#line 2383 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 242 "parser.y" /* yacc.c:1646  */
    { (yyval.exprNode) = (yyvsp[0].exprNode); }
#line 2389 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 245 "parser.y" /* yacc.c:1646  */
    { (yyval.functionNode) = (yyvsp[-1].functionNode); (yyval.functionNode)->body = (yyvsp[0].blockNode); }
#line 2395 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 248 "parser.y" /* yacc.c:1646  */
    { (yyval.functionNode) = new FunctionNode((yyvsp[-4].typeNode), (yyvsp[-3].identifierNode), *(yyvsp[-1].varList), NULL); delete (yyvsp[-1].varList); }
#line 2401 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 251 "parser.y" /* yacc.c:1646  */
    { (yyval.varList) = new VarList(); }
#line 2407 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 252 "parser.y" /* yacc.c:1646  */
    { (yyval.varList) = new VarList(); (yyval.varList)->push_back((yyvsp[0].varDeclNode)); }
#line 2413 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 253 "parser.y" /* yacc.c:1646  */
    { (yyval.varList) = (yyvsp[-2].varList); (yyval.varList)->push_back((yyvsp[0].varDeclNode)); }
#line 2419 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 256 "parser.y" /* yacc.c:1646  */
    { (yyval.varList) = new VarList(); (yyval.varList)->push_back((yyvsp[0].varDeclNode)); }
#line 2425 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 257 "parser.y" /* yacc.c:1646  */
    { (yyval.varList) = (yyvsp[-2].varList); (yyval.varList)->push_back((yyvsp[0].varDeclNode)); }
#line 2431 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 260 "parser.y" /* yacc.c:1646  */
    { (yyval.functionCallNode) = new FunctionCallNode((yyvsp[-3].identifierNode), *(yyvsp[-1].exprList)); delete (yyvsp[-1].exprList); }
#line 2437 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 263 "parser.y" /* yacc.c:1646  */
    { (yyval.exprList) = new ExprList(); }
#line 2443 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 264 "parser.y" /* yacc.c:1646  */
    { (yyval.exprList) = new ExprList(); (yyval.exprList)->push_back((yyvsp[0].exprNode)); }
#line 2449 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 265 "parser.y" /* yacc.c:1646  */
    { (yyval.exprList) = (yyvsp[-2].exprList); (yyval.exprList)->push_back((yyvsp[0].exprNode)); }
#line 2455 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 268 "parser.y" /* yacc.c:1646  */
    { (yyval.exprList) = new ExprList(); (yyval.exprList)->push_back((yyvsp[0].exprNode)); }
#line 2461 "parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 269 "parser.y" /* yacc.c:1646  */
    { (yyval.exprList) = (yyvsp[-2].exprList); (yyval.exprList)->push_back((yyvsp[0].exprNode)); }
#line 2467 "parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 272 "parser.y" /* yacc.c:1646  */
    { (yyval.returnStmtNode) = new ReturnStmtNode((yyvsp[-1].location), (yyvsp[0].exprNode)); }
#line 2473 "parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 273 "parser.y" /* yacc.c:1646  */
    { (yyval.returnStmtNode) = new ReturnStmtNode((yyvsp[0].location), NULL); }
#line 2479 "parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 277 "parser.y" /* yacc.c:1646  */
    {  }
#line 2485 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 280 "parser.y" /* yacc.c:1646  */
    {  }
#line 2491 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 281 "parser.y" /* yacc.c:1646  */
    {  }
#line 2497 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 284 "parser.y" /* yacc.c:1646  */
    {  }
#line 2503 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 285 "parser.y" /* yacc.c:1646  */
    {  }
#line 2509 "parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 286 "parser.y" /* yacc.c:1646  */
    {  }
#line 2515 "parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 287 "parser.y" /* yacc.c:1646  */
    {  }
#line 2521 "parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 288 "parser.y" /* yacc.c:1646  */
    {  }
#line 2527 "parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 291 "parser.y" /* yacc.c:1646  */
    {  }
#line 2533 "parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 292 "parser.y" /* yacc.c:1646  */
    {  }
#line 2539 "parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 293 "parser.y" /* yacc.c:1646  */
    {  }
#line 2545 "parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 294 "parser.y" /* yacc.c:1646  */
    {  }
#line 2551 "parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 297 "parser.y" /* yacc.c:1646  */
    { (yyval.typeNode) = new TypeNode((yyvsp[0].location), INT); }
#line 2557 "parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 298 "parser.y" /* yacc.c:1646  */
    { (yyval.typeNode) = new TypeNode((yyvsp[0].location), FLOAT); }
#line 2563 "parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 299 "parser.y" /* yacc.c:1646  */
    { (yyval.typeNode) = new TypeNode((yyvsp[0].location), CHAR); }
#line 2569 "parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 300 "parser.y" /* yacc.c:1646  */
    { (yyval.typeNode) = new TypeNode((yyvsp[0].location), BOOL); }
#line 2575 "parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 301 "parser.y" /* yacc.c:1646  */
    { (yyval.typeNode) = new TypeNode((yyvsp[0].location), VOID); }
#line 2581 "parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 304 "parser.y" /* yacc.c:1646  */
    { (yyval.valueNode) = new ValueNode((yyvsp[0].token).loc, INT, (yyvsp[0].token).value); delete (yyvsp[0].token).value; }
#line 2587 "parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 305 "parser.y" /* yacc.c:1646  */
    { (yyval.valueNode) = new ValueNode((yyvsp[0].token).loc, FLOAT, (yyvsp[0].token).value); delete (yyvsp[0].token).value; }
#line 2593 "parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 306 "parser.y" /* yacc.c:1646  */
    { (yyval.valueNode) = new ValueNode((yyvsp[0].token).loc, CHAR, (yyvsp[0].token).value); delete (yyvsp[0].token).value; }
#line 2599 "parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 307 "parser.y" /* yacc.c:1646  */
    { (yyval.valueNode) = new ValueNode((yyvsp[0].token).loc, BOOL, (yyvsp[0].token).value); delete (yyvsp[0].token).value; }
#line 2605 "parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 310 "parser.y" /* yacc.c:1646  */
    { (yyval.identifierNode) = new IdentifierNode((yyvsp[0].token).loc, (yyvsp[0].token).value); delete (yyvsp[0].token).value; }
#line 2611 "parser.cpp" /* yacc.c:1646  */
    break;


#line 2615 "parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 313 "parser.y" /* yacc.c:1906  */


void yyerror(const char* s) {
    printf( "%s\n", s);
}
