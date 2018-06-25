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
#line 1 "parser.ypp" /* yacc.c:339  */


//User Declarations

#include "output.hpp"
#include "bp.hpp"
#include "parser.hpp"
#include <stdio.h>

int yylex();
void yyerror(const char*);

extern int yylineno;    //line number from lex for Errors

//Global Variables

std::stack<SymbolTable> TableStack;
std::stack<int> OffsetStack;
std::stack<Register> registerStack;

RetType* expectedRet;        ////current fun expected return type for checking
Id* currentFunName;            //current fun name
Formals* currentFunParams;   //current fun params for type checking

bool isAprintFunc;           //special case for the print function
bool isAprintiFunc;           //special case for the printi function*
int whileScopes;             //current number of while scopes 
int derivesNum;

using namespace output;


#line 99 "parser.tab.cpp" /* yacc.c:339  */

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
   by #include "parser.tab.hpp".  */
#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
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
    VOID = 258,
    INT = 259,
    BYTE = 260,
    B = 261,
    BOOL = 262,
    AND = 263,
    OR = 264,
    NOT = 265,
    TRUE = 266,
    FALSE = 267,
    RETURN = 268,
    WHILE = 269,
    BREAK = 270,
    SC = 271,
    COMMA = 272,
    LPAREN = 273,
    RPAREN = 274,
    ELSE = 275,
    IF = 276,
    LBRACE = 277,
    RBRACE = 278,
    LBRACK = 279,
    RBRACK = 280,
    ASSIGN = 281,
    RELOP = 282,
    PLUS = 283,
    MINUS = 284,
    MUL = 285,
    DIV = 286,
    ID = 287,
    NUM = 288,
    STRING = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 185 "parser.tab.cpp" /* yacc.c:358  */

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   232

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  130

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    74,    74,    79,    87,    89,    97,   104,   110,   116,
     120,   126,   132,   138,   139,   142,   143,   144,   147,   148,
     151,   156,   161,   168,   175,   183,   191,   196,   201,   206,
     216,   232,   238,   242,   247,   255,   264,   272,   277,   283,
     292,   301,   306,   317,   327,   334,   338,   348,   365,   366,
     367,   370,   371,   372,   373,   374,   375,   376,   377,   378,
     379,   380,   381,   382,   383,   384,   387,   393,   399
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VOID", "INT", "BYTE", "B", "BOOL",
  "AND", "OR", "NOT", "TRUE", "FALSE", "RETURN", "WHILE", "BREAK", "SC",
  "COMMA", "LPAREN", "RPAREN", "ELSE", "IF", "LBRACE", "RBRACE", "LBRACK",
  "RBRACK", "ASSIGN", "RELOP", "PLUS", "MINUS", "MUL", "DIV", "ID", "NUM",
  "STRING", "$accept", "Program", "Funcs", "FuncDecl", "RetType",
  "UpdateCurrentFunName", "AddFuncScope", "OpenFunScope", "Formals",
  "FormalsList", "FormalDecl", "Statements", "Statement", "AddNewScope",
  "ExitScope", "MARKER_M_IF", "MARKER_N_IF", "MARKER_M_WHILE",
  "MARKER_N_WHILE", "checkExpType", "checkArrayIndexType", "AddWhileScope",
  "FuncName", "Call", "ExpList", "Type", "Exp", "MARKER_M_EXP", YY_NULLPTR
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
     285,   286,   287,   288,   289
};
# endif

#define YYPACT_NINF -96

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-96)))

#define YYTABLE_NINF -44

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-44)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     117,   -96,   -96,   -96,   -96,    14,   -96,   117,    -6,   -96,
     -96,   -96,   -96,     9,     3,   -96,   -96,    16,     2,    18,
       3,    19,   -96,   -96,     5,    35,    -4,    91,    33,   -96,
       7,   -96,    47,    48,   -96,   -13,    46,   -96,    52,    57,
      45,   -96,   107,   -96,   -96,   -96,   107,   -12,    81,   -96,
     -96,   118,    73,   -96,   107,    91,   107,   107,    66,   -96,
     -96,    97,   -96,    59,   131,   124,   -96,   -96,   -96,   -96,
     -96,   107,   107,   107,   107,   107,   -96,   -96,   148,    67,
     155,   165,   107,   -96,    78,   180,   -96,    69,   107,   -96,
     107,   107,   201,   106,    24,    72,   -96,   107,   -96,   -96,
     -96,   -96,   -96,   190,   -96,   107,    -1,   196,   141,   131,
     -96,    91,   -96,   -96,    75,    94,   -96,   -96,   -96,    95,
     -96,    91,   108,   -96,   -96,   -96,   -96,   -96,    91,   -96
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     6,    48,    49,    50,     0,     2,     3,     0,     7,
       1,     4,     8,     0,    11,     9,    12,    13,     0,     0,
       0,    15,    10,    14,     0,     0,     0,     0,     0,    16,
       0,    41,     0,     0,    21,    43,     0,    18,     0,     0,
       0,    17,     0,    58,    59,    29,     0,    53,    55,    57,
      54,     0,     0,    42,     0,     0,     0,     0,     0,     5,
      19,     0,    28,     0,    60,     0,    52,    56,    68,    68,
      30,     0,     0,     0,     0,     0,    37,    33,     0,     0,
       0,     0,     0,    45,     0,    46,    22,     0,     0,    51,
       0,     0,    65,    61,    62,    63,    64,     0,    21,    39,
      20,    40,    26,     0,    44,     0,     0,     0,    66,    67,
      21,     0,    27,    47,     0,     0,    23,    38,    32,     0,
      24,     0,    31,    25,    36,    34,    33,    21,     0,    35
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -96,   -96,   135,   -96,   -96,   -96,   -96,   -96,   -96,   145,
     -96,    83,   -35,   -95,   -96,    40,   -96,   -96,   -96,    17,
     140,   -96,   -96,   -27,    39,    22,   -26,   121
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    13,    19,    25,    15,    16,
      17,    36,    37,    55,   122,    98,   126,    97,   121,    77,
      58,    52,    38,    50,    84,    40,    78,    90
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      39,    60,    28,   111,    51,   114,   -43,     2,     3,    39,
       4,    56,    56,    57,    10,   117,    64,    42,    43,    44,
      65,    29,     9,    45,   115,    46,    12,    14,    39,     9,
      80,    81,   128,    20,    21,    85,    18,    22,    26,    47,
      48,    49,    18,    24,    60,    92,    93,    94,    95,    96,
       2,     3,    39,     4,    74,    75,   103,    27,    41,    30,
      31,    32,   107,    53,   108,   109,    54,    33,    34,    59,
      61,     2,     3,    62,     4,    86,   118,    63,    35,    85,
      30,    31,    32,    87,    39,    88,   124,    67,    33,    34,
     100,    76,    82,   129,    39,     2,     3,   104,     4,    35,
     119,    39,   106,    75,    30,    31,    32,    42,    43,    44,
     120,   123,    33,    34,   110,    46,    83,    42,    43,    44,
       1,     2,     3,    35,     4,    46,    68,    69,   125,    47,
      48,    49,    68,    69,    70,    73,    74,    75,    79,    47,
      48,    49,    11,    89,   113,    71,    72,    73,    74,    75,
      69,    71,    72,    73,    74,    75,    68,    69,    71,    72,
      73,    74,    75,    68,    69,    23,   127,    99,    71,    72,
      73,    74,    75,    68,    69,    71,    72,    73,    74,    75,
     101,   102,    71,    72,    73,    74,    75,    66,    68,    69,
      91,     0,    71,    72,    73,    74,    75,   105,    68,    69,
       0,     0,     0,     0,    68,    69,   112,    71,    72,    73,
      74,    75,   116,     0,     0,     0,     0,    71,    72,    73,
      74,    75,     0,    71,    72,    73,    74,    75,   -44,    72,
      73,    74,    75
};

static const yytype_int16 yycheck[] =
{
      27,    36,     6,    98,    30,     6,    18,     4,     5,    36,
       7,    24,    24,    26,     0,   110,    42,    10,    11,    12,
      46,    25,     0,    16,    25,    18,    32,    18,    55,     7,
      56,    57,   127,    17,    32,    61,    14,    19,    33,    32,
      33,    34,    20,    24,    79,    71,    72,    73,    74,    75,
       4,     5,    79,     7,    30,    31,    82,    22,    25,    13,
      14,    15,    88,    16,    90,    91,    18,    21,    22,    23,
      18,     4,     5,    16,     7,    16,   111,    32,    32,   105,
      13,    14,    15,    24,   111,    26,   121,     6,    21,    22,
      23,    18,    26,   128,   121,     4,     5,    19,     7,    32,
      25,   128,    33,    31,    13,    14,    15,    10,    11,    12,
      16,    16,    21,    22,    97,    18,    19,    10,    11,    12,
       3,     4,     5,    32,     7,    18,     8,     9,    20,    32,
      33,    34,     8,     9,    16,    29,    30,    31,    55,    32,
      33,    34,     7,    19,   105,    27,    28,    29,    30,    31,
       9,    27,    28,    29,    30,    31,     8,     9,    27,    28,
      29,    30,    31,     8,     9,    20,   126,    19,    27,    28,
      29,    30,    31,     8,     9,    27,    28,    29,    30,    31,
      25,    16,    27,    28,    29,    30,    31,    47,     8,     9,
      69,    -1,    27,    28,    29,    30,    31,    17,     8,     9,
      -1,    -1,    -1,    -1,     8,     9,    16,    27,    28,    29,
      30,    31,    16,    -1,    -1,    -1,    -1,    27,    28,    29,
      30,    31,    -1,    27,    28,    29,    30,    31,    27,    28,
      29,    30,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     7,    36,    37,    38,    39,    60,
       0,    37,    32,    40,    18,    43,    44,    45,    60,    41,
      17,    32,    19,    44,    24,    42,    33,    22,     6,    25,
      13,    14,    15,    21,    22,    32,    46,    47,    57,    58,
      60,    25,    10,    11,    12,    16,    18,    32,    33,    34,
      58,    61,    56,    16,    18,    48,    24,    26,    55,    23,
      47,    18,    16,    32,    61,    61,    55,     6,     8,     9,
      16,    27,    28,    29,    30,    31,    18,    54,    61,    46,
      61,    61,    26,    19,    59,    61,    16,    24,    26,    19,
      62,    62,    61,    61,    61,    61,    61,    52,    50,    19,
      23,    25,    16,    61,    19,    17,    33,    61,    61,    61,
      54,    48,    16,    59,     6,    25,    16,    48,    47,    25,
      16,    53,    49,    16,    47,    20,    51,    50,    48,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    39,    39,    40,    41,
      42,    43,    43,    44,    44,    45,    45,    45,    46,    46,
      47,    48,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    49,    50,    51,    47,    47,    52,    53,    54,
      55,    56,    47,    57,    58,    58,    59,    59,    60,    60,
      60,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    62
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,    10,     1,     1,     1,     0,
       0,     0,     1,     1,     3,     2,     5,     6,     1,     2,
       4,     0,     3,     5,     6,     7,     4,     5,     2,     2,
       3,     7,     0,     0,     0,    12,     8,     0,     0,     2,
       3,     0,     2,     1,     4,     3,     1,     3,     1,     1,
       1,     3,     2,     1,     1,     1,     2,     1,     1,     1,
       2,     3,     3,     3,     3,     3,     4,     4,     0
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
  YYUSE (yytype);
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
#line 74 "parser.ypp" /* yacc.c:1646  */
    {
    checkMain();
    finishScope(TableStack,OffsetStack);
}
#line 1371 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 79 "parser.ypp" /* yacc.c:1646  */
    {
     (yyval) = new Funcs();
     if(derivesNum == 0 && yychar != 0){
        errorSyn(yylineno); 
        exit(0);
     }
}
#line 1383 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 87 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Funcs((Funcs*)(yyvsp[0]), (Func*)(yyvsp[-1]));  }
#line 1389 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 89 "parser.ypp" /* yacc.c:1646  */
    {
	//TODO create new label for function
    derivesNum--;
    Func* func = new Func((RetType*)(yyvsp[-9]), (Id*)(yyvsp[-8]), (Formals*)(yyvsp[-6]), (Statements*)(yyvsp[-1]));
    (yyval) = func;
    finishScope(TableStack,OffsetStack);}
#line 1400 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 97 "parser.ypp" /* yacc.c:1646  */
    {
    RetType* type = new RetType((Void*)(yyvsp[0]));
    expectedRet = type;      //updates the expected return type to VOID
    (yyval) = type;}
#line 1409 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 104 "parser.ypp" /* yacc.c:1646  */
    {
    RetType* type = new RetType((Type*)(yyvsp[0]));
    expectedRet =type;      //updates the expected return type accord.
    (yyval) = type;}
#line 1418 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 110 "parser.ypp" /* yacc.c:1646  */
    {
    derivesNum++;
    currentFunName = (Id*)(yyvsp[0]);
    (yyval) = (yyvsp[0]);
}
#line 1428 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 116 "parser.ypp" /* yacc.c:1646  */
    { //also creates fun name label
    addFuncToScope(TableStack, OffsetStack, expectedRet, currentFunName, currentFunParams, yylineno); 
}
#line 1436 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 120 "parser.ypp" /* yacc.c:1646  */
    {
    saveFramePointer();
    addNewScope(TableStack, OffsetStack);    //opens a new scope for function
    addFuncSymScope(TableStack, OffsetStack, currentFunParams, yylineno); 
}
#line 1446 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 126 "parser.ypp" /* yacc.c:1646  */
    {
    Formals* params = new Formals();
    currentFunParams = params; //no parameters for the current func
    (yyval) = params;}
#line 1455 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 132 "parser.ypp" /* yacc.c:1646  */
    {
    Formals* params = new Formals((FormalsList*)(yyvsp[0]));
    currentFunParams = params;
    (yyval) = params;}
#line 1464 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 138 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new FormalsList((FormalDecl*)(yyvsp[0])); }
#line 1470 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 139 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new FormalsList((FormalsList*)(yyvsp[0]), (FormalDecl*)(yyvsp[-2])); }
#line 1476 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 142 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new FormalDecl((Type*)(yyvsp[-1]), (Id*)(yyvsp[0])); }
#line 1482 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 143 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new FormalDecl((Type*)(yyvsp[-4]), (Id*)(yyvsp[-3]) ,(Num*)(yyvsp[-1])); }
#line 1488 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 144 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new FormalDecl((Type*)(yyvsp[-5]), (Id*)(yyvsp[-4]) ,(Num*)(yyvsp[-2]), (b*)(yyvsp[-1])); }
#line 1494 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 147 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Statements( (Statement*)(yyvsp[0])); }
#line 1500 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 148 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Statements( (Statements*)(yyvsp[-1]), (Statement*)(yyvsp[0])); }
#line 1506 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 151 "parser.ypp" /* yacc.c:1646  */
    {
    (yyval) = new Statement( (Statements*)(yyvsp[-1]));
    finishScope(TableStack,OffsetStack);}
#line 1514 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 156 "parser.ypp" /* yacc.c:1646  */
    {
    addNewScope(TableStack, OffsetStack);}
#line 1521 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 161 "parser.ypp" /* yacc.c:1646  */
    {
    (yyval) = new Statement( (Type*) (yyvsp[-2]), (Id*)(yyvsp[-1]));
	string temp = ( (Type*) (yyvsp[-2]))->type;
    newVarScope(TableStack, OffsetStack, temp, (Id*) (yyvsp[-1]), yylineno,1);}
#line 1530 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 168 "parser.ypp" /* yacc.c:1646  */
    {
    (yyval) = new Statement( (Type*) (yyvsp[-4]), (Id*)(yyvsp[-3]), (Exp*)(yyvsp[-1]));
	string temp = ( (Type*) (yyvsp[-4]))->type;
    newVarScope(TableStack, OffsetStack, temp, (Id*) (yyvsp[-3]), yylineno,1);}
#line 1539 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 175 "parser.ypp" /* yacc.c:1646  */
    {
    string temp = ( (Type*)(yyvsp[-5]))->type;
    int val=( (Num*)(yyvsp[-2]))->value;
    (yyval) = new Statement( (Type*)(yyvsp[-5]), (Id*)(yyvsp[-4]), (Num*)(yyvsp[-2]));
    newVarScope(TableStack, OffsetStack, makeArrayType(temp,val), (Id*) (yyvsp[-4]), yylineno,val);}
#line 1549 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 183 "parser.ypp" /* yacc.c:1646  */
    {
        string temp = ( (Type*)(yyvsp[-6]))->type;
        int val=( (Num*)(yyvsp[-3]))->value;
        (yyval) = new Statement( (Type*)(yyvsp[-6]), (Id*)(yyvsp[-5]), (Num*)(yyvsp[-3]), (b*)(yyvsp[-2]));
        newVarScope(TableStack, OffsetStack, makeArrayType(temp,val), (Id*) (yyvsp[-5]), yylineno,val);}
#line 1559 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 191 "parser.ypp" /* yacc.c:1646  */
    {
    (yyval) = new Statement( (Id*)(yyvsp[-3]), (Exp*)(yyvsp[-1]));}
#line 1566 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 196 "parser.ypp" /* yacc.c:1646  */
    {
    (yyval) = new Statement( (Id*)(yyvsp[-4]), (Exp*)(yyvsp[-3]), (Exp*)(yyvsp[-1]));}
#line 1573 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 201 "parser.ypp" /* yacc.c:1646  */
    {
    (yyval) = new Statement( (Call*)(yyvsp[-1]));}
#line 1580 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 206 "parser.ypp" /* yacc.c:1646  */
    {
    if(expectedRet->type == "VOID"){ //is a void func
        (yyval) = new Statement();
    }else{
        errorMismatch(yylineno);
        exit(0);
    }
}
#line 1593 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 216 "parser.ypp" /* yacc.c:1646  */
    {
    if(expectedRet->type == "VOID"){
        errorMismatch(yylineno);
        exit(0);
    }
    if(expectedRet->type != ( (Exp*)(yyvsp[-1]))->type){
        if((expectedRet->type == "INT" && ((Exp*)(yyvsp[-1]))->type == "BYTE") ) { //allowed cast from byte to int
        }else{
            errorMismatch(yylineno);
            exit(0);
        }
    }
    (yyval) = new Statement((Return*)(yyvsp[-2]),(Exp*)(yyvsp[-1]));
}
#line 1612 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 232 "parser.ypp" /* yacc.c:1646  */
    {
    ((Statement*)(yyvsp[-1]))->bp.quad = ((Statement*)(yyvsp[-3]))->bp.quad;
    (yyval) = new Statement( (Exp*)(yyvsp[-4]), (Statement*)(yyvsp[-1]));}
#line 1620 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 238 "parser.ypp" /* yacc.c:1646  */
    {
    finishScope(TableStack,OffsetStack);}
#line 1627 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 242 "parser.ypp" /* yacc.c:1646  */
    {
    (yyval) = new Statement(); //empty statement for quad
    ((Statement*)(yyval))->bp.quad = CodeBuffer::instance().genLabel();
}
#line 1636 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 247 "parser.ypp" /* yacc.c:1646  */
    {
    (yyval) = new Statement(); //empty statement for quad
    ((Statement*)(yyval))->bp.quad = CodeBuffer::instance().genLabel();
    ((Statement*)(yyval))->bp.nextList = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
}
#line 1646 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 255 "parser.ypp" /* yacc.c:1646  */
    {
    ((Statement*)(yyvsp[-6]))->bp.quad = ((Statement*)(yyvsp[-8]))->bp.quad;
    ((Statement*)(yyvsp[0]))->bp.quad = ((Statement*)(yyvsp[-2]))->bp.quad;
    (yyval) = new Statement( (Exp*)(yyvsp[-9]), (Statement*)(yyvsp[-6]),(Statement*)(yyvsp[-3]), (Statement*)(yyvsp[0]));
    finishScope(TableStack,OffsetStack);
    delete (yyvsp[-3]); //delete N MARKER
}
#line 1658 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 264 "parser.ypp" /* yacc.c:1646  */
    {
    ((Exp*)(yyvsp[-3]))->bp.quad=((Exp*)(yyvsp[-4]))->bp.quad;
    ((Statement*)(yyvsp[0]))->bp.quad=((Statement*)(yyvsp[-1]))->bp.quad;
    (yyval) = new Statement( (Exp*)(yyvsp[-3]), (Statement*)(yyvsp[0]));
    finishScope(TableStack,OffsetStack);
    whileScopes--; }
#line 1669 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 272 "parser.ypp" /* yacc.c:1646  */
    {
    (yyval) = new Exp(); //empty statement for quad
    ((Exp*)(yyval))->bp.quad = CodeBuffer::instance().genLabel();
}
#line 1678 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 277 "parser.ypp" /* yacc.c:1646  */
    {
    (yyval) = new Statement(); //empty statement for quad
    ((Statement*)(yyval))->bp.quad = CodeBuffer::instance().genLabel();
}
#line 1687 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 283 "parser.ypp" /* yacc.c:1646  */
    {
    if( ((Exp*)(yyvsp[-1]))->type != "BOOL"){
        errorMismatch(yylineno);
        exit(0);
    }
    (yyval) = (yyvsp[-1]);}
#line 1698 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 292 "parser.ypp" /* yacc.c:1646  */
    {
    if( (((Exp*)(yyvsp[-1]))->type != "INT") && (((Exp*)(yyvsp[-1]))->type != "BYTE")){
        errorMismatch(yylineno);
        exit(0);
    }
    (yyval) = (yyvsp[-1]);}
#line 1709 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 301 "parser.ypp" /* yacc.c:1646  */
    {
    whileScopes++;}
#line 1716 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 306 "parser.ypp" /* yacc.c:1646  */
    {
    if(whileScopes == 0){        //checks if it's in atleast one while scope
        errorUnexpectedBreak(yylineno);
        exit(0);
    }else{
        (yyval) = new Statement();
    }
    ((Statement*)(yyval))->bp.breakList = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j ")); //leave for backPatch
}
#line 1730 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 317 "parser.ypp" /* yacc.c:1646  */
    {
    if( ((Id*)(yyvsp[0]))->name == "print"){   //checks if the func is *print* for special case (- can accept string after it
        isAprintFunc = true;                
    }else if(((Id*)(yyvsp[0]))->name == "printi"){  
        isAprintiFunc = true;                
    }
    (yyval) = (yyvsp[0]);
}
#line 1743 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 327 "parser.ypp" /* yacc.c:1646  */
    {
    (yyval) = new Call( (Id*)(yyvsp[-3]), (ExpList*)(yyvsp[-1]));
    isAprintFunc = false; 
    isAprintiFunc = false;  //back to default status
}
#line 1753 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 334 "parser.ypp" /* yacc.c:1646  */
    {
    (yyval) = new Call( (Id*)(yyvsp[-2]));}
#line 1760 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 338 "parser.ypp" /* yacc.c:1646  */
    {
    if(isAprintiFunc && (((Exp*)(yyvsp[0]))->type != "INT" &&  ((Exp*)(yyvsp[0]))->type != "BYTE")){
        std::vector<std::string> vec;
        vec.push_back("INT");
        errorPrototypeMismatch(yylineno, "printi", vec);
		exit(0);
    }
    (yyval) = new ExpList( (Exp*)(yyvsp[0])); 
}
#line 1774 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 348 "parser.ypp" /* yacc.c:1646  */
    {
    if(isAprintiFunc || isAprintFunc){  //those funcs cannot except more than *one* param
        std::vector<std::string> vec;
        string funcName;
        if(isAprintiFunc){
            vec.push_back("INT");
            funcName = "printi";
        }else{
            vec.push_back("STRING");
            funcName = "print";
        }
        errorPrototypeMismatch(yylineno, funcName, vec);
		exit(0);
    }
    (yyval) = new ExpList( (Exp*)(yyvsp[-2]), (ExpList*)(yyvsp[0])); 
}
#line 1795 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 365 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Type("INT"); }
#line 1801 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 366 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Type("BYTE"); }
#line 1807 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 367 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Type("BOOL"); }
#line 1813 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 370 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Exp( (Exp*)(yyvsp[-1])); }
#line 1819 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 371 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Exp( (Id*)(yyvsp[-1]), (Exp*)(yyvsp[0])); }
#line 1825 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 372 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Exp( (Id*)(yyvsp[0])); }
#line 1831 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 373 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Exp( (Call*)(yyvsp[0])); }
#line 1837 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 374 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Exp( (Num*)(yyvsp[0])); }
#line 1843 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 375 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Exp( (Num*)(yyvsp[-1]), (b*)(yyvsp[0])); }
#line 1849 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 376 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Exp( (String*)(yyvsp[0]),isAprintFunc,isAprintiFunc ); }
#line 1855 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 377 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Exp("TRUE"); }
#line 1861 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 378 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Exp("FALSE"); }
#line 1867 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 379 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Exp("NOT", (Exp*)(yyvsp[0])); }
#line 1873 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 380 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Exp( (Exp*)(yyvsp[-2]) ,(Exp*)(yyvsp[0]), "BINOP", "+"); }
#line 1879 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 381 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Exp( (Exp*)(yyvsp[-2]) ,(Exp*)(yyvsp[0]), "BINOP", "-"); }
#line 1885 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 382 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Exp( (Exp*)(yyvsp[-2]) ,(Exp*)(yyvsp[0]), "BINOP", "*"); }
#line 1891 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 383 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Exp( (Exp*)(yyvsp[-2]) ,(Exp*)(yyvsp[0]), "BINOP", "/"); }
#line 1897 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 384 "parser.ypp" /* yacc.c:1646  */
    { (yyval) = new Exp((Exp*)(yyvsp[-2]) ,(Exp*)(yyvsp[0]),(Relop*)(yyvsp[-1]));  //relop sent as the last var   
}
#line 1904 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 387 "parser.ypp" /* yacc.c:1646  */
    { //added marker here **
    ((Exp*)(yyvsp[0]))->bp.quad = ((Exp*)(yyvsp[-1]))->bp.quad;
    (yyval) = new Exp( (Exp*)(yyvsp[-3]) ,(Exp*)(yyvsp[0]), "LOGOP","AND"); 
    delete (yyvsp[-1]);
}
#line 1914 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 393 "parser.ypp" /* yacc.c:1646  */
    { //added marker here **
    ((Exp*)(yyvsp[0]))->bp.quad = ((Exp*)(yyvsp[-1]))->bp.quad;
    (yyval) = new Exp( (Exp*)(yyvsp[-3]) ,(Exp*)(yyvsp[0]), "LOGOP","OR"); 
    delete (yyvsp[-1]);
}
#line 1924 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 399 "parser.ypp" /* yacc.c:1646  */
    {
    (yyval) = new Exp(); //new exp for quad
    ((Exp*)(yyval))->bp.quad = CodeBuffer::instance().genLabel();
}
#line 1933 "parser.tab.cpp" /* yacc.c:1646  */
    break;


#line 1937 "parser.tab.cpp" /* yacc.c:1646  */
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
#line 404 "parser.ypp" /* yacc.c:1906  */


//User Routines

void yyerror(const char*) {
    errorSyn(yylineno); //Syntax Error
    exit(0);
}

int main(){
    whileScopes=0;
    derivesNum=0;
    isAprintFunc=false;
    isAprintiFunc = false;
    StacksInit(TableStack, OffsetStack);
    RegistersInit(registerStack);    //------new func added for registers init.
    return yyparse();
}
