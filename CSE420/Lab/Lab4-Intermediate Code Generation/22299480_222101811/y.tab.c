/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "22299480_222101811.y"


#include "symbol_table.h"
#include "ast.h"
#include "three_addr_code.h"
#include <iostream>
#include <fstream>
#include <string>

/* Define the type for all grammar symbols */
#define YYSTYPE symbol_info*

extern FILE *yyin;
int yyparse(void);
int yylex(void);
extern YYSTYPE yylval;

symbol_table *symtbl = new symbol_table();
ProgramNode* ast_root = new ProgramNode();

int lines = 1;
int errors = 0;
ofstream outlog, outerror, outcode;

string varlist=""; //for variable declarartion list
vector<string>paramlist; //for parameter list fot func dec and func def
vector<string>paramname; //for func def	
vector<string>arglist; //to store types of function argument

int is_func = 0; //is compound statement in function definition

string ret_type, func_name, func_ret_type;

void yyerror(char *s)
{
	outlog<<"At line "<<lines<<" "<<s<<endl<<endl;
	outerror<<"At line "<<lines<<" "<<s<<endl<<endl;
	errors++;
	
	varlist = "";
	paramlist.clear();
	paramname.clear();
	arglist.clear();
	is_func = 0;
	ret_type = "";
	func_name = "";
	func_ret_type = "";
}


/* Line 371 of yacc.c  */
#line 119 "y.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     CHAR = 260,
     FOR = 261,
     WHILE = 262,
     DO = 263,
     BREAK = 264,
     INT = 265,
     FLOAT = 266,
     DOUBLE = 267,
     VOID = 268,
     RETURN = 269,
     SWITCH = 270,
     CASE = 271,
     DEFAULT = 272,
     CONTINUE = 273,
     PRINTLN = 274,
     ADDOP = 275,
     MULOP = 276,
     INCOP = 277,
     DECOP = 278,
     RELOP = 279,
     ASSIGNOP = 280,
     LOGICOP = 281,
     NOT = 282,
     LPAREN = 283,
     RPAREN = 284,
     LCURL = 285,
     RCURL = 286,
     LTHIRD = 287,
     RTHIRD = 288,
     COMMA = 289,
     SEMICOLON = 290,
     CONST_INT = 291,
     CONST_FLOAT = 292,
     ID = 293,
     LOWER_THAN_ELSE = 294
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define CHAR 260
#define FOR 261
#define WHILE 262
#define DO 263
#define BREAK 264
#define INT 265
#define FLOAT 266
#define DOUBLE 267
#define VOID 268
#define RETURN 269
#define SWITCH 270
#define CASE 271
#define DEFAULT 272
#define CONTINUE 273
#define PRINTLN 274
#define ADDOP 275
#define MULOP 276
#define INCOP 277
#define DECOP 278
#define RELOP 279
#define ASSIGNOP 280
#define LOGICOP 281
#define NOT 282
#define LPAREN 283
#define RPAREN 284
#define LCURL 285
#define RCURL 286
#define LTHIRD 287
#define RTHIRD 288
#define COMMA 289
#define SEMICOLON 290
#define CONST_INT 291
#define CONST_FLOAT 292
#define ID 293
#define LOWER_THAN_ELSE 294



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 263 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   178

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNRULES -- Number of states.  */
#define YYNSTATES  122

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    24,
      31,    32,    37,    41,    44,    46,    51,    55,    56,    60,
      62,    64,    66,    68,    72,    79,    81,    86,    88,    90,
      93,    95,    98,   100,   102,   104,   106,   114,   120,   128,
     134,   140,   144,   146,   149,   151,   156,   158,   162,   164,
     168,   170,   174,   176,   180,   182,   186,   189,   192,   194,
     196,   201,   205,   207,   209,   212,   215,   217,   218,   222
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      41,     0,    -1,    42,    -1,    42,    43,    -1,    43,    -1,
      49,    -1,    44,    -1,     1,    -1,    50,    52,    28,    46,
      29,    45,    47,    -1,    50,    52,    28,    29,    45,    47,
      -1,    -1,    46,    34,    50,    38,    -1,    46,    34,    50,
      -1,    50,    38,    -1,    50,    -1,    30,    48,    53,    31,
      -1,    30,    48,    31,    -1,    -1,    50,    51,    35,    -1,
      10,    -1,    11,    -1,    13,    -1,     5,    -1,    51,    34,
      52,    -1,    51,    34,    52,    32,    36,    33,    -1,    52,
      -1,    52,    32,    36,    33,    -1,    38,    -1,    54,    -1,
      53,    54,    -1,     1,    -1,    53,     1,    -1,    49,    -1,
      44,    -1,    55,    -1,    47,    -1,     6,    28,    55,    55,
      57,    29,    54,    -1,     3,    28,    57,    29,    54,    -1,
       3,    28,    57,    29,    54,     4,    54,    -1,     7,    28,
      57,    29,    54,    -1,    19,    28,    52,    29,    35,    -1,
      14,    57,    35,    -1,    35,    -1,    57,    35,    -1,    52,
      -1,    52,    32,    57,    33,    -1,    58,    -1,    56,    25,
      58,    -1,    59,    -1,    59,    26,    59,    -1,    60,    -1,
      60,    24,    60,    -1,    61,    -1,    60,    20,    61,    -1,
      62,    -1,    61,    21,    62,    -1,    20,    62,    -1,    27,
      62,    -1,    63,    -1,    56,    -1,    52,    28,    64,    29,
      -1,    28,    57,    29,    -1,    36,    -1,    37,    -1,    56,
      22,    -1,    56,    23,    -1,    65,    -1,    -1,    65,    34,
      58,    -1,    58,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    60,    60,    73,    95,   111,   119,   127,   133,   165,
     193,   239,   256,   266,   276,   288,   301,   317,   341,   411,
     419,   427,   435,   445,   455,   466,   474,   484,   492,   506,
     520,   526,   533,   541,   549,   557,   565,   581,   595,   610,
     624,   646,   659,   670,   683,   728,   770,   779,   819,   828,
     863,   872,   907,   917,   957,   967,  1042,  1067,  1092,  1112,
    1121,  1195,  1204,  1216,  1228,  1244,  1262,  1270,  1281,  1304
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "CHAR", "FOR", "WHILE",
  "DO", "BREAK", "INT", "FLOAT", "DOUBLE", "VOID", "RETURN", "SWITCH",
  "CASE", "DEFAULT", "CONTINUE", "PRINTLN", "ADDOP", "MULOP", "INCOP",
  "DECOP", "RELOP", "ASSIGNOP", "LOGICOP", "NOT", "LPAREN", "RPAREN",
  "LCURL", "RCURL", "LTHIRD", "RTHIRD", "COMMA", "SEMICOLON", "CONST_INT",
  "CONST_FLOAT", "ID", "LOWER_THAN_ELSE", "$accept", "start", "program",
  "unit", "func_definition", "enter_func", "param_list",
  "compound_statement", "enter_scope_variables", "variable_decl",
  "type_specifier", "declaration_list", "id_name", "statements",
  "statement", "expression_statement", "variable", "expression",
  "logic_expression", "rel_expression", "simple_expression", "term",
  "unary_expression", "factor", "argument_list", "arguments", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    44,    44,
      45,    46,    46,    46,    46,    47,    47,    48,    49,    50,
      50,    50,    50,    51,    51,    51,    51,    52,    53,    53,
      53,    53,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    55,    55,    56,    56,    57,    57,    58,    58,
      59,    59,    60,    60,    61,    61,    62,    62,    62,    63,
      63,    63,    63,    63,    63,    63,    64,    64,    65,    65
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     7,     6,
       0,     4,     3,     2,     1,     4,     3,     0,     3,     1,
       1,     1,     1,     3,     6,     1,     4,     1,     1,     2,
       1,     2,     1,     1,     1,     1,     7,     5,     7,     5,
       5,     3,     1,     2,     1,     4,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     2,     2,     1,     1,
       4,     3,     1,     1,     2,     2,     1,     0,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,    22,    19,    20,    21,     0,     0,     4,     6,
       5,     0,     1,     3,    27,     0,    25,     0,    18,     0,
       0,    23,    10,     0,    14,     0,     0,     0,    10,     0,
      13,    26,     0,    17,     9,     0,    12,    24,     0,     8,
      11,    30,     0,     0,     0,     0,     0,     0,     0,     0,
      16,    42,    62,    63,    33,    35,    32,    44,     0,    28,
      34,    59,     0,    46,    48,    50,    52,    54,    58,     0,
       0,     0,     0,     0,    59,    56,    57,     0,    67,     0,
      31,    15,    29,    64,    65,     0,    43,     0,     0,     0,
       0,     0,     0,     0,    41,     0,    61,    69,     0,    66,
       0,    47,    49,    53,    51,    55,     0,     0,     0,     0,
      60,     0,    45,    37,     0,    39,    40,    68,     0,     0,
      38,    36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     6,     7,     8,    54,    27,    23,    55,    38,    56,
      11,    15,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    98,    99
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -73
static const yytype_int16 yypact[] =
{
      13,   -73,   -73,   -73,   -73,   -73,    20,    44,   -73,   -73,
     -73,    -2,   -73,   -73,   -73,    12,    28,    -2,   -73,     6,
      -3,    16,   -73,    41,    30,    45,    59,    70,   -73,    48,
     -73,   -73,    73,   -73,   -73,    70,    75,   -73,    66,   -73,
     -73,   -73,    80,    88,    93,    92,    94,    92,    92,    92,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,    55,   104,   -73,
     -73,   133,    90,   -73,   100,    64,   106,   -73,   -73,    92,
      54,    92,    98,    -2,    76,   -73,   -73,   107,    92,    92,
     -73,   -73,   -73,   -73,   -73,    92,   -73,    92,    92,    92,
      92,   108,    54,   109,   -73,   115,   -73,   -73,   119,   118,
     116,   -73,   -73,   106,   137,   -73,   140,    92,   140,   126,
     -73,    92,   -73,   158,   134,   -73,   -73,   -73,   140,   140,
     -73,   -73
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -73,   -73,   -73,   157,    21,   138,   -73,    -5,   -73,    25,
     -14,   -73,    -7,   -73,   -56,   -58,   -47,   -42,   -72,    78,
      82,    81,   -39,   -73,   -73,   -73
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int8 yytable[] =
{
      74,    74,    82,    72,    16,    24,    97,    77,    75,    76,
      21,     2,    92,   101,     1,    36,     3,     4,     2,     5,
      12,     9,    34,     3,     4,    10,     5,    91,     9,    93,
      39,    74,    10,    25,   107,    22,    14,   100,    74,   117,
      74,    74,    74,    74,    -2,     1,    17,    18,    26,     2,
     113,   105,   115,     2,     3,     4,    19,     5,     3,     4,
      20,     5,   120,   121,    74,   114,    95,    41,    30,    42,
      28,     2,    43,    44,    47,    29,     3,     4,    31,     5,
      45,    48,    49,    78,    88,    46,    47,    79,    89,    51,
      52,    53,    14,    48,    49,    32,    33,    50,    83,    84,
      33,    51,    52,    53,    14,    80,    37,    42,    69,     2,
      43,    44,    47,    40,     3,     4,    70,     5,    45,    48,
      49,    71,    73,    46,    47,    86,    87,    90,    52,    53,
      14,    48,    49,    94,    33,    81,    96,   106,   108,    51,
      52,    53,    14,    42,   109,     2,    43,    44,   110,   112,
       3,     4,   111,     5,    45,    83,    84,    88,    85,    46,
      47,   116,   118,   119,    13,   102,    35,    48,    49,   103,
      33,   104,     0,     0,     0,    51,    52,    53,    14
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-73)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      47,    48,    58,    45,    11,    19,    78,    49,    47,    48,
      17,     5,    70,    85,     1,    29,    10,    11,     5,    13,
       0,     0,    27,    10,    11,     0,    13,    69,     7,    71,
      35,    78,     7,    36,    92,    29,    38,    79,    85,   111,
      87,    88,    89,    90,     0,     1,    34,    35,    32,     5,
     106,    90,   108,     5,    10,    11,    28,    13,    10,    11,
      32,    13,   118,   119,   111,   107,    73,     1,    38,     3,
      29,     5,     6,     7,    20,    34,    10,    11,    33,    13,
      14,    27,    28,    28,    20,    19,    20,    32,    24,    35,
      36,    37,    38,    27,    28,    36,    30,    31,    22,    23,
      30,    35,    36,    37,    38,     1,    33,     3,    28,     5,
       6,     7,    20,    38,    10,    11,    28,    13,    14,    27,
      28,    28,    28,    19,    20,    35,    26,    21,    36,    37,
      38,    27,    28,    35,    30,    31,    29,    29,    29,    35,
      36,    37,    38,     3,    29,     5,     6,     7,    29,    33,
      10,    11,    34,    13,    14,    22,    23,    20,    25,    19,
      20,    35,     4,    29,     7,    87,    28,    27,    28,    88,
      30,    89,    -1,    -1,    -1,    35,    36,    37,    38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     5,    10,    11,    13,    41,    42,    43,    44,
      49,    50,     0,    43,    38,    51,    52,    34,    35,    28,
      32,    52,    29,    46,    50,    36,    32,    45,    29,    34,
      38,    33,    36,    30,    47,    45,    50,    33,    48,    47,
      38,     1,     3,     6,     7,    14,    19,    20,    27,    28,
      31,    35,    36,    37,    44,    47,    49,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    28,
      28,    28,    57,    28,    56,    62,    62,    57,    28,    32,
       1,    31,    54,    22,    23,    25,    35,    26,    20,    24,
      21,    57,    55,    57,    35,    52,    29,    58,    64,    65,
      57,    58,    59,    61,    60,    62,    29,    55,    29,    29,
      29,    34,    33,    54,    57,    54,    35,    58,     4,    29,
      54,    54
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
      yychar = YYLEX;
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
     `$$ = $1'.

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
/* Line 1792 of yacc.c  */
#line 61 "22299480_222101811.y"
    {
		outlog<<"At line no: "<<lines<<" start : program "<<endl<<endl;
		outlog<<"Symbol Table"<<endl<<endl;
		
		symtbl->Print_all_scope(outlog);
		
		(yyval) = (yyvsp[(1) - (1)]);
		// Root of AST is the program node
		ast_root = (ProgramNode*)(yyvsp[(1) - (1)])->get_ast_node();
	}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 74 "22299480_222101811.y"
    {
		outlog<<"At line no: "<<lines<<" program : program unit "<<endl<<endl;
		outlog<<(yyvsp[(1) - (2)])->getname()+"\n"+(yyvsp[(2) - (2)])->getname()<<endl<<endl;
		
		(yyval) = new symbol_info((yyvsp[(1) - (2)])->getname()+"\n"+(yyvsp[(2) - (2)])->getname(),"program");
		
		// Create/update AST node for program
		ProgramNode* prog;
		if((yyvsp[(1) - (2)])->get_ast_node()) {
			prog = (ProgramNode*)(yyvsp[(1) - (2)])->get_ast_node();
		} else {
			prog = new ProgramNode();
		}
		
		// Add the unit to the program
		if((yyvsp[(2) - (2)])->get_ast_node()) {
			prog->add_unit((yyvsp[(2) - (2)])->get_ast_node());
		}
		
		(yyval)->set_ast_node(prog);
	}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 96 "22299480_222101811.y"
    {
		outlog<<"At line no: "<<lines<<" program : unit "<<endl<<endl;
		outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
		
		(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"program");
		
		// Create AST node for program with a single unit
		ProgramNode* prog = new ProgramNode();
		if((yyvsp[(1) - (1)])->get_ast_node()) {
			prog->add_unit((yyvsp[(1) - (1)])->get_ast_node());
		}
		(yyval)->set_ast_node(prog);
	}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 112 "22299480_222101811.y"
    {
		outlog<<"At line no: "<<lines<<" unit : variable_decl "<<endl<<endl;
		outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
		
		(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"unit");
		(yyval)->set_ast_node((yyvsp[(1) - (1)])->get_ast_node());
	 }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 120 "22299480_222101811.y"
    {
		outlog<<"At line no: "<<lines<<" unit : func_definition "<<endl<<endl;
		outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
		
		(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"unit");
		(yyval)->set_ast_node((yyvsp[(1) - (1)])->get_ast_node());
	 }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 128 "22299480_222101811.y"
    {
	 	(yyval) = new symbol_info("","unit");
	 }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 134 "22299480_222101811.y"
    {	
			outlog<<"At line no: "<<lines<<" func_definition : type_specifier ID LPAREN param_list RPAREN compound_statement "<<endl<<endl;
			outlog<<(yyvsp[(1) - (7)])->getname()<<" "<<(yyvsp[(2) - (7)])->getname()<<"("+(yyvsp[(4) - (7)])->getname()+")\n"<<(yyvsp[(7) - (7)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (7)])->getname()+" "+(yyvsp[(2) - (7)])->getname()+"("+(yyvsp[(4) - (7)])->getname()+")\n"+(yyvsp[(7) - (7)])->getname(),"func_def");	
			
			// Create AST node for function definition
			FuncDeclNode* func = new FuncDeclNode((yyvsp[(1) - (7)])->getname(), (yyvsp[(2) - (7)])->getname());
			
			// Add parameters
			for(int i = 0; i < paramlist.size(); i++) {
				if(paramname[i] != "_null_") {
					func->add_param(paramlist[i], paramname[i]);
				}
			}
			
			// Set body
			if((yyvsp[(7) - (7)])->get_ast_node()) {
				func->set_body((BlockNode*)(yyvsp[(7) - (7)])->get_ast_node());
			}
			
			(yyval)->set_ast_node(func);
			
			if(symtbl->getID()!=1)
			{
				symtbl->Remove_from_table((yyvsp[(2) - (7)])->getname());
			}
			
			paramlist.clear();
			paramname.clear();	
		}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 166 "22299480_222101811.y"
    {
			
			outlog<<"At line no: "<<lines<<" func_definition : type_specifier ID LPAREN RPAREN compound_statement "<<endl<<endl;
			outlog<<(yyvsp[(1) - (6)])->getname()<<" "<<(yyvsp[(2) - (6)])->getname()<<"()\n"<<(yyvsp[(6) - (6)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (6)])->getname()+" "+(yyvsp[(2) - (6)])->getname()+"()\n"+(yyvsp[(6) - (6)])->getname(),"func_def");	
			
			// Create AST node for function definition
			FuncDeclNode* func = new FuncDeclNode((yyvsp[(1) - (6)])->getname(), (yyvsp[(2) - (6)])->getname());
			
			// Set body
			if((yyvsp[(6) - (6)])->get_ast_node()) {
				func->set_body((BlockNode*)(yyvsp[(6) - (6)])->get_ast_node());
			}
			
			(yyval)->set_ast_node(func);
			
			if(symtbl->getID()!=1)
			{
				symtbl->Remove_from_table((yyvsp[(2) - (6)])->getname());
			}
			
			paramlist.clear();
			paramname.clear();	
		}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 193 "22299480_222101811.y"
    {
				//if(symtbl->getID()!="1") goto end2; //not in global scope , doesnt work because if not inserted lots of errors come in compound statement
				
				is_func=1;//compound statement is coming in function definition. enter parameter variables.
				
				if(paramlist.size()!=0) //check parameters
				{
					for(int i = 0; i < paramlist.size();i++)
					{
						if(paramname[i]=="_null_")
						{
							outerror<<"At line no: "<<lines<<" Parameter "<<i+1<<"'s name not given in function definition of "<<func_name<<endl<<endl;
							outlog<<"At line no: "<<lines<<" Parameter "<<i+1<<"'s name not given in function definition of "<<func_name<<endl<<endl;
							errors++;
						}
					}
				}
				
				//check if function already present and do error checking
				if(symtbl->Insert_in_table(func_name,"ID"))
				{
					(symtbl->Lookup_in_table(func_name))->setvartype(func_ret_type);
					(symtbl->Lookup_in_table(func_name))->setidtype("func_def");
					(symtbl->Lookup_in_table(func_name))->setparamlist(paramlist);//initialize parameters
					(symtbl->Lookup_in_table(func_name))->setparamname(paramname);
				}
				else
				{
					outerror<<"At line no: "<<lines<<" Multiple declaration of function "<<func_name<<endl<<endl;
					outlog<<"At line no: "<<lines<<" Multiple declaration of function "<<func_name<<endl<<endl;
					errors++;
					// (symtbl->Lookup_in_table(func_name))->setidtype("func_def");
				}
					
				if((symtbl->Lookup_in_table(func_name))->getvartype() != func_ret_type)
				{
					outerror<<"At line no: "<<lines<<" Return type mismatch of function "<<func_name<<endl<<endl;
					outlog<<"At line no: "<<lines<<" Return type mismatch of function "<<func_name<<endl<<endl;
					errors++;
				}
				
				//end2:
				//;
            }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 240 "22299480_222101811.y"
    {
			outlog<<"At line no: "<<lines<<" param_list : param_list COMMA type_specifier ID "<<endl<<endl;
			outlog<<(yyvsp[(1) - (4)])->getname()+","+(yyvsp[(3) - (4)])->getname()+" "+(yyvsp[(4) - (4)])->getname()<<endl<<endl;
					
			(yyval) = new symbol_info((yyvsp[(1) - (4)])->getname()+","+(yyvsp[(3) - (4)])->getname()+" "+(yyvsp[(4) - (4)])->getname(),"param_list");
			
			if(count(paramname.begin(),paramname.end(),(yyvsp[(4) - (4)])->getname()))
			{
				outerror<<"At line no: "<<lines<<" Multiple declaration of variable "<<(yyvsp[(4) - (4)])->getname()<<" in parameter of "<<func_name<<endl<<endl;
				outlog<<"At line no: "<<lines<<" Multiple declaration of variable "<<(yyvsp[(4) - (4)])->getname()<<" in parameter of "<<func_name<<endl<<endl;
				errors++;
			}
			
			paramlist.push_back((yyvsp[(3) - (4)])->getname());
			paramname.push_back((yyvsp[(4) - (4)])->getname());
		}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 257 "22299480_222101811.y"
    {
			outlog<<"At line no: "<<lines<<" param_list : param_list COMMA type_specifier "<<endl<<endl;
			outlog<<(yyvsp[(1) - (3)])->getname()+","+(yyvsp[(3) - (3)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (3)])->getname()+","+(yyvsp[(3) - (3)])->getname(),"param_list");
			
			paramlist.push_back((yyvsp[(3) - (3)])->getname());
			paramname.push_back("_null_");
		}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 267 "22299480_222101811.y"
    {
			outlog<<"At line no: "<<lines<<" param_list : type_specifier ID "<<endl<<endl;
			outlog<<(yyvsp[(1) - (2)])->getname()<<" "<<(yyvsp[(2) - (2)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (2)])->getname()+" "+(yyvsp[(2) - (2)])->getname(),"param_list");
			
			paramlist.push_back((yyvsp[(1) - (2)])->getname());
			paramname.push_back((yyvsp[(2) - (2)])->getname());
		}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 277 "22299480_222101811.y"
    {
			outlog<<"At line no: "<<lines<<" param_list : type_specifier "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"param_list");
			
			paramlist.push_back((yyvsp[(1) - (1)])->getname());
			paramname.push_back("_null_");
		}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 289 "22299480_222101811.y"
    { 
 		    	outlog<<"At line no: "<<lines<<" compound_statement : LCURL statements RCURL "<<endl<<endl;
				outlog<<"{\n"+(yyvsp[(3) - (4)])->getname()+"\n}"<<endl<<endl;
				
				(yyval) = new symbol_info("{\n"+(yyvsp[(3) - (4)])->getname()+"\n}","comp_stmnt");
				
				// Set AST node for compound statement
				(yyval)->set_ast_node((yyvsp[(3) - (4)])->get_ast_node());
				
				symtbl->Print_all_scope(outlog);
			    symtbl->exit_scope(outlog);
 		    }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 302 "22299480_222101811.y"
    { 
 		    	outlog<<"At line no: "<<lines<<" compound_statement : LCURL RCURL "<<endl<<endl;
				outlog<<"{\n}"<<endl<<endl;
				
				(yyval) = new symbol_info("{\n}","comp_stmnt");
				
				// Create empty block node
				BlockNode* block = new BlockNode();
				(yyval)->set_ast_node(block);
				
				symtbl->Print_all_scope(outlog);
			    symtbl->exit_scope(outlog);
 		    }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 317 "22299480_222101811.y"
    {
				symtbl->enter_scope(outlog);
				
				if(is_func == 1)
				{
					if(paramname.size()!=0)
					{
						for(int i = 0; i < paramname.size(); i++)
						{
							if(paramname[i]!="_null_")
							{
								symtbl->Insert_in_table(paramname[i],"ID");
								(symtbl->Lookup_in_table(paramname[i]))->setidtype("var");
								(symtbl->Lookup_in_table(paramname[i]))->setvartype(paramlist[i]);
							}
							
						}
					}
					is_func=0; //variable entered.if more compound statements come in func efinitions, don't enter the function variables.
				}
				
			}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 342 "22299480_222101811.y"
    {
			outlog<<"At line no: "<<lines<<" variable_decl : type_specifier declaration_list SEMICOLON "<<endl<<endl;
			outlog<<(yyvsp[(1) - (3)])->getname()<<" "<<varlist<<";"<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (3)])->getname()+" "+varlist+";","var_dec");
			
			if((yyvsp[(1) - (3)])->getname()=="void")
			{
				outerror<<"At line no: "<<lines<<" variable type can not be void "<<endl<<endl;
				outlog<<"At line no: "<<lines<<" variable type can not be void "<<endl<<endl;
				errors++;
				(yyvsp[(1) - (3)]) = new symbol_info("error","type"); //variable is declared void so pass error instead
			}
			
			// Create AST node for variable declaration
			DeclNode* declNode = new DeclNode((yyvsp[(1) - (3)])->getname());
			
			// Parse the varlist to add variables to the declaration node
			stringstream _varlist(varlist);
			string varname;
			
			while(getline(_varlist,varname,','))
			{
				if(varname.find("[") == string::npos) // normal variable
				{
					declNode->add_var(varname, 0);
					
					if(symtbl->Insert_in_table(varname,"ID"))
					{
						(symtbl->Lookup_in_table(varname))->setvartype((yyvsp[(1) - (3)])->getname());
						(symtbl->Lookup_in_table(varname))->setidtype("var");
					}
					else
					{
						outerror<<"At line no: "<<lines<<" Multiple declaration of variable "<<varname<<endl<<endl;
						outlog<<"At line no: "<<lines<<" Multiple declaration of variable "<<varname<<endl<<endl;
						errors++;
					}
				}
				else // array
				{
					stringstream _varname(varname);
					string name, size;
					
					getline(_varname,name,'['); // get array name
					getline(_varname,size,']'); // get array size
					
					declNode->add_var(name, stoi(size));
					
					if(symtbl->Insert_in_table(name,"ID"))
					{
						(symtbl->Lookup_in_table(name))->setvartype((yyvsp[(1) - (3)])->getname());
						(symtbl->Lookup_in_table(name))->setidtype("array");
						(symtbl->Lookup_in_table(name))->setarraysize(stoi(size));
					}
					else
					{
						outerror<<"At line no: "<<lines<<" Multiple declaration of variable "<<name<<endl<<endl;
						outlog<<"At line no: "<<lines<<" Multiple declaration of variable "<<name<<endl<<endl;
						errors++;
					}
				}
			}
			
			(yyval)->set_ast_node(declNode);
			varlist = "";
		 }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 412 "22299480_222101811.y"
    {
			outlog<<"At line no: "<<lines<<" type_specifier : INT "<<endl<<endl;
			outlog<<"int"<<endl<<endl;
			
			(yyval) = new symbol_info("int","type");
			ret_type = "int";
	    }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 420 "22299480_222101811.y"
    {
			outlog<<"At line no: "<<lines<<" type_specifier : FLOAT "<<endl<<endl;
			outlog<<"float"<<endl<<endl;
			
			(yyval) = new symbol_info("float","type");
			ret_type = "float";
	    }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 428 "22299480_222101811.y"
    {
			outlog<<"At line no: "<<lines<<" type_specifier : VOID "<<endl<<endl;
			outlog<<"void"<<endl<<endl;
			
			(yyval) = new symbol_info("void","type");
			ret_type = "void";
	    }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 436 "22299480_222101811.y"
    {
			outlog<<"At line no: "<<lines<<" type_specifier : CHAR "<<endl<<endl;
			outlog<<"char"<<endl<<endl;
			
			(yyval) = new symbol_info("char","type");
			ret_type = "char";
	    }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 446 "22299480_222101811.y"
    {
 		  	string name = (yyvsp[(3) - (3)])->getname();
 		  	outlog<<"At line no: "<<lines<<" declaration_list : declaration_list COMMA ID "<<endl<<endl;
 		  	
 		  	varlist=varlist+","+name;
 		  	
			outlog<<varlist<<endl<<endl;
			
 		  }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 456 "22299480_222101811.y"
    {
 		  	string name = (yyvsp[(3) - (6)])->getname();
 		  	string size = (yyvsp[(5) - (6)])->getname();
 		  	outlog<<"At line no: "<<lines<<" declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD "<<endl<<endl;
 		  	
 		  	varlist=varlist+","+name+"["+size+"]";
 		  	
			outlog<<varlist<<endl<<endl;
			
 		  }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 467 "22299480_222101811.y"
    {
 		  	string name = (yyvsp[(1) - (1)])->getname();
 		  	outlog<<"At line no: "<<lines<<" declaration_list : ID "<<endl<<endl;
			outlog<<name<<endl<<endl;
			
			varlist+=name;
 		  }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 475 "22299480_222101811.y"
    {
 		  	string name = (yyvsp[(1) - (4)])->getname();
 		  	string size = (yyvsp[(3) - (4)])->getname();
 		  	outlog<<"At line no: "<<lines<<" declaration_list : ID LTHIRD CONST_INT RTHIRD "<<endl<<endl;
			outlog<<name+"["+size+"]"<<endl<<endl;
			
			varlist=varlist+name+"["+size+"]";
 		  }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 485 "22299480_222101811.y"
    {
		   	(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"ID");
		   	func_name = (yyvsp[(1) - (1)])->getname();
		   	func_ret_type = ret_type;
		  }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 493 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" statements : statement "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"stmnts");
			
			// Create block for statements
			BlockNode* block = new BlockNode();
			if((yyvsp[(1) - (1)])->get_ast_node()) {
				block->add_statement((StmtNode*)(yyvsp[(1) - (1)])->get_ast_node());
			}
			(yyval)->set_ast_node(block);
	   }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 507 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" statements : statements statement "<<endl<<endl;
			outlog<<(yyvsp[(1) - (2)])->getname()<<"\n"<<(yyvsp[(2) - (2)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (2)])->getname()+"\n"+(yyvsp[(2) - (2)])->getname(),"stmnts");
			
			// Update block with new statement
			BlockNode* block = (BlockNode*)(yyvsp[(1) - (2)])->get_ast_node();
			if((yyvsp[(2) - (2)])->get_ast_node()) {
				block->add_statement((StmtNode*)(yyvsp[(2) - (2)])->get_ast_node());
			}
			(yyval)->set_ast_node(block);
	   }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 521 "22299480_222101811.y"
    {
	  		(yyval) = new symbol_info("","stmnts");
			BlockNode* block = new BlockNode();
			(yyval)->set_ast_node(block);
	   }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 527 "22299480_222101811.y"
    {
	   		(yyval) = new symbol_info((yyvsp[(1) - (2)])->getname(),"stmnts");
			(yyval)->set_ast_node((yyvsp[(1) - (2)])->get_ast_node());
	   }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 534 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : variable_decl "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"stmnt");
			(yyval)->set_ast_node((yyvsp[(1) - (1)])->get_ast_node());
	  }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 542 "22299480_222101811.y"
    {
	  		outlog<<"At line no: "<<lines<<" Function definition must be in the global scope "<<endl<<endl;
	  		outerror<<"At line no: "<<lines<<" Function definition must be in the global scope "<<endl<<endl;
	  		errors++;
	  		(yyval) = new symbol_info("","stmnt");
	  		
	  }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 550 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : expression_statement "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"stmnt");
			(yyval)->set_ast_node((yyvsp[(1) - (1)])->get_ast_node());
	  }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 558 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : compound_statement "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"stmnt");
			(yyval)->set_ast_node((yyvsp[(1) - (1)])->get_ast_node());
	  }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 566 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement "<<endl<<endl;
			outlog<<"for("<<(yyvsp[(3) - (7)])->getname()<<(yyvsp[(4) - (7)])->getname()<<(yyvsp[(5) - (7)])->getname()<<")\n"<<(yyvsp[(7) - (7)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info("for("+(yyvsp[(3) - (7)])->getname()+(yyvsp[(4) - (7)])->getname()+(yyvsp[(5) - (7)])->getname()+")\n"+(yyvsp[(7) - (7)])->getname(),"stmnt");
			
			// Create AST node for for loop
			ForNode* forNode = new ForNode(
				(ExprNode*)(yyvsp[(3) - (7)])->get_ast_node(),
				(ExprNode*)(yyvsp[(4) - (7)])->get_ast_node(),
				(ExprNode*)(yyvsp[(5) - (7)])->get_ast_node(),
				(StmtNode*)(yyvsp[(7) - (7)])->get_ast_node()
			);
			(yyval)->set_ast_node(forNode);
	  }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 582 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : IF LPAREN expression RPAREN statement "<<endl<<endl;
			outlog<<"if("<<(yyvsp[(3) - (5)])->getname()<<")\n"<<(yyvsp[(5) - (5)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info("if("+(yyvsp[(3) - (5)])->getname()+")\n"+(yyvsp[(5) - (5)])->getname(),"stmnt");
			
			// Create AST node for if statement (without else)
			IfNode* ifNode = new IfNode(
				(ExprNode*)(yyvsp[(3) - (5)])->get_ast_node(),
				(StmtNode*)(yyvsp[(5) - (5)])->get_ast_node()
			);
			(yyval)->set_ast_node(ifNode);
	  }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 596 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : IF LPAREN expression RPAREN statement ELSE statement "<<endl<<endl;
			outlog<<"if("<<(yyvsp[(3) - (7)])->getname()<<")\n"<<(yyvsp[(5) - (7)])->getname()<<"\nelse\n"<<(yyvsp[(7) - (7)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info("if("+(yyvsp[(3) - (7)])->getname()+")\n"+(yyvsp[(5) - (7)])->getname()+"\nelse\n"+(yyvsp[(7) - (7)])->getname(),"stmnt");
			
			// Create AST node for if-else statement
			IfNode* ifNode = new IfNode(
				(ExprNode*)(yyvsp[(3) - (7)])->get_ast_node(),
				(StmtNode*)(yyvsp[(5) - (7)])->get_ast_node(),
				(StmtNode*)(yyvsp[(7) - (7)])->get_ast_node()
			);
			(yyval)->set_ast_node(ifNode);
	  }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 611 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : WHILE LPAREN expression RPAREN statement "<<endl<<endl;
			outlog<<"while("<<(yyvsp[(3) - (5)])->getname()<<")\n"<<(yyvsp[(5) - (5)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info("while("+(yyvsp[(3) - (5)])->getname()+")\n"+(yyvsp[(5) - (5)])->getname(),"stmnt");
			
			// Create AST node for while loop
			WhileNode* whileNode = new WhileNode(
				(ExprNode*)(yyvsp[(3) - (5)])->get_ast_node(),
				(StmtNode*)(yyvsp[(5) - (5)])->get_ast_node()
			);
			(yyval)->set_ast_node(whileNode);
	  }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 625 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : PRINTLN LPAREN ID RPAREN SEMICOLON "<<endl<<endl;
			outlog<<"printf("<<(yyvsp[(3) - (5)])->getname()<<");"<<endl<<endl; 
			
			if(symtbl->Lookup_in_table((yyvsp[(3) - (5)])->getname()) == NULL)
			{
				outerror<<"At line no: "<<lines<<" Undeclared variable "<<(yyvsp[(3) - (5)])->getname()<<endl<<endl;
				outlog<<"At line no: "<<lines<<" Undeclared variable "<<(yyvsp[(3) - (5)])->getname()<<endl<<endl;
				errors++;
			}
			
			(yyval) = new symbol_info("printf("+(yyvsp[(3) - (5)])->getname()+");","stmnt");
			
			// Could add a PrintNode to AST if needed
			// For now, create a basic expression statement
			VarNode* var = new VarNode((yyvsp[(3) - (5)])->getname(), 
			                         symtbl->Lookup_in_table((yyvsp[(3) - (5)])->getname()) ? 
			                         symtbl->Lookup_in_table((yyvsp[(3) - (5)])->getname())->getvartype() : "error");
			ExprStmtNode* printNode = new ExprStmtNode(var);
			(yyval)->set_ast_node(printNode);
	  }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 647 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : RETURN expression SEMICOLON "<<endl<<endl;
			outlog<<"return "<<(yyvsp[(2) - (3)])->getname()<<";"<<endl<<endl;
			
			(yyval) = new symbol_info("return "+(yyvsp[(2) - (3)])->getname()+";","stmnt");
			
			// Create AST node for return statement
			ReturnNode* returnNode = new ReturnNode((ExprNode*)(yyvsp[(2) - (3)])->get_ast_node());
			(yyval)->set_ast_node(returnNode);
	  }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 660 "22299480_222101811.y"
    {
				outlog<<"At line no: "<<lines<<" expression_statement : SEMICOLON "<<endl<<endl;
				outlog<<";"<<endl<<endl;
				
				(yyval) = new symbol_info(";","expr_stmt");
				
				// Create empty expression statement
				ExprStmtNode* exprStmt = new ExprStmtNode(nullptr);
				(yyval)->set_ast_node(exprStmt);
	        }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 671 "22299480_222101811.y"
    {
				outlog<<"At line no: "<<lines<<" expression_statement : expression SEMICOLON "<<endl<<endl;
				outlog<<(yyvsp[(1) - (2)])->getname()<<";"<<endl<<endl;
				
				(yyval) = new symbol_info((yyvsp[(1) - (2)])->getname()+";","expr_stmt");
				
				// Create expression statement from expression
				ExprStmtNode* exprStmt = new ExprStmtNode((ExprNode*)(yyvsp[(1) - (2)])->get_ast_node());
				(yyval)->set_ast_node(exprStmt);
	        }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 684 "22299480_222101811.y"
    {
	    outlog<<"At line no: "<<lines<<" variable : ID "<<endl<<endl;
		outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
			
		(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"varbl");
		
		if(symtbl->Lookup_in_table((yyvsp[(1) - (1)])->getname()) == NULL)
		{
			outerror<<"At line no: "<<lines<<" Undeclared variable "<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
			outlog<<"At line no: "<<lines<<" Undeclared variable "<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
			errors++;
			
			(yyval)->setvartype("error");; //not found set error type
		}
		else if((symtbl->Lookup_in_table((yyvsp[(1) - (1)])->getname()))->getidtype() != "var") //variable is not a normal variable
		{
			if((symtbl->Lookup_in_table((yyvsp[(1) - (1)])->getname()))->getidtype() == "array")
			{
				outerror<<"At line no: "<<lines<<" variable is of array type : "<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
				outlog<<"At line no: "<<lines<<" variable is of array type : "<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
				errors++;
			}
			else if((symtbl->Lookup_in_table((yyvsp[(1) - (1)])->getname()))->getidtype() == "func_def") 
			{
				outerror<<"At line no: "<<lines<<" variable is of function type : "<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
				outlog<<"At line no: "<<lines<<" variable is of function type : "<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
				errors++;
			}
			else if((symtbl->Lookup_in_table((yyvsp[(1) - (1)])->getname()))->getidtype() == "func_dec") 
			{
				outerror<<"At line no: "<<lines<<" variable is of function type : "<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
				outlog<<"At line no: "<<lines<<" variable is of function type : "<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
				errors++;
			}
			
			
			(yyval)->setvartype("error");; //doesnt match set error type
		}
		else (yyval)->setvartype((symtbl->Lookup_in_table((yyvsp[(1) - (1)])->getname()))->getvartype());  //set variable type as id type
		
		// Create AST node for variable
		VarNode* varNode = new VarNode((yyvsp[(1) - (1)])->getname(), (yyval)->getvartype());
		(yyval)->set_ast_node(varNode);
	 }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 729 "22299480_222101811.y"
    {
	 	outlog<<"At line no: "<<lines<<" variable : ID LTHIRD expression RTHIRD "<<endl<<endl;
		outlog<<(yyvsp[(1) - (4)])->getname()<<"["<<(yyvsp[(3) - (4)])->getname()<<"]"<<endl<<endl;
		
		(yyval) = new symbol_info((yyvsp[(1) - (4)])->getname()+"["+(yyvsp[(3) - (4)])->getname()+"]","varbl");
		
		if(symtbl->Lookup_in_table((yyvsp[(1) - (4)])->getname()) == NULL)
		{
			outerror<<"At line no: "<<lines<<" Undeclared variable "<<(yyvsp[(1) - (4)])->getname()<<endl<<endl;
			outlog<<"At line no: "<<lines<<" Undeclared variable "<<(yyvsp[(1) - (4)])->getname()<<endl<<endl;
			errors++;
			
			(yyval)->setvartype("error");; //not found set error type
		}
		else if((symtbl->Lookup_in_table((yyvsp[(1) - (4)])->getname()))->getidtype() != "array") //variable is not an array
		{
			outerror<<"At line no: "<<lines<<" variable is not of array type : "<<(yyvsp[(1) - (4)])->getname()<<endl<<endl;
			outlog<<"At line no: "<<lines<<" variable is not of array type : "<<(yyvsp[(1) - (4)])->getname()<<endl<<endl;
			errors++;
			
			(yyval)->setvartype("error");; //doesnt match set error type
		}
		else if((yyvsp[(3) - (4)])->getvartype()!="int") // get type of expression of array index
		{
			outerror<<"At line no: "<<lines<<" array index is not of integer type : "<<(yyvsp[(1) - (4)])->getname()<<endl<<endl;
			outlog<<"At line no: "<<lines<<" array index is not of integer type : "<<(yyvsp[(1) - (4)])->getname()<<endl<<endl;
			errors++;
			
			(yyval)->setvartype("error");
		}
		else
		{
			(yyval)->setvartype((symtbl->Lookup_in_table((yyvsp[(1) - (4)])->getname()))->getvartype());
		}
		
		// Create AST node for array access
		VarNode* varNode = new VarNode((yyvsp[(1) - (4)])->getname(), (yyval)->getvartype(), (ExprNode*)(yyvsp[(3) - (4)])->get_ast_node());
		(yyval)->set_ast_node(varNode);
	 }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 771 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" expression : logic_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"expr");
			(yyval)->setvartype((yyvsp[(1) - (1)])->getvartype());
			(yyval)->set_ast_node((yyvsp[(1) - (1)])->get_ast_node());
	   }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 780 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" expression : variable ASSIGNOP logic_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (3)])->getname()<<"="<<(yyvsp[(3) - (3)])->getname()<<endl<<endl;

			(yyval) = new symbol_info((yyvsp[(1) - (3)])->getname()+"="+(yyvsp[(3) - (3)])->getname(),"expr");
			(yyval)->setvartype((yyvsp[(1) - (3)])->getvartype());
			
			if((yyvsp[(1) - (3)])->getvartype() == "void" || (yyvsp[(3) - (3)])->getvartype() == "void") //if any of them is a void
			{
				outerror<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				outlog<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				errors++;
				
				(yyval)->setvartype("error");
			}
			else if((yyvsp[(1) - (3)])->getvartype() == "int" && (yyvsp[(3) - (3)])->getvartype() == "float") // assignment of float into int
			{
				outerror<<"At line no: "<<lines<<" Warning: Assignment of float value into variable of integer type "<<endl<<endl;
				outlog<<"At line no: "<<lines<<" Warning: Assignment of float value into variable of integer type "<<endl<<endl;
				errors++;
				
				(yyval)->setvartype("int");
			}
			
			if((yyvsp[(1) - (3)])->getvartype() == "error" || (yyvsp[(3) - (3)])->getvartype() == "error") //if any of them is a error
			{
				(yyval)->setvartype("error");
			}
			
			// Create AST node for assignment
			AssignNode* assignNode = new AssignNode(
				(VarNode*)(yyvsp[(1) - (3)])->get_ast_node(),
				(ExprNode*)(yyvsp[(3) - (3)])->get_ast_node(),
				(yyval)->getvartype()
			);
			(yyval)->set_ast_node(assignNode);
	   }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 820 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" logic_expression : rel_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"lgc_expr");
			(yyval)->setvartype((yyvsp[(1) - (1)])->getvartype());
			(yyval)->set_ast_node((yyvsp[(1) - (1)])->get_ast_node());
	     }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 829 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" logic_expression : rel_expression LOGICOP rel_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (3)])->getname()<<(yyvsp[(2) - (3)])->getname()<<(yyvsp[(3) - (3)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (3)])->getname()+(yyvsp[(2) - (3)])->getname()+(yyvsp[(3) - (3)])->getname(),"lgc_expr");
			(yyval)->setvartype("int");
			
			//do type checking of both side of logicop
			
			if((yyvsp[(1) - (3)])->getvartype() == "void" || (yyvsp[(3) - (3)])->getvartype() == "void") //if any of them is a void
			{
				outerror<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				outlog<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				errors++;
				
				(yyval)->setvartype("error");
			}
			
			if((yyvsp[(1) - (3)])->getvartype() == "error" || (yyvsp[(3) - (3)])->getvartype() == "error") //if any of them is a error
			{
				(yyval)->setvartype("error");
			}
			
			// Create AST node for logical operation
			BinaryOpNode* logicNode = new BinaryOpNode(
				(yyvsp[(2) - (3)])->getname(),
				(ExprNode*)(yyvsp[(1) - (3)])->get_ast_node(),
				(ExprNode*)(yyvsp[(3) - (3)])->get_ast_node(),
				(yyval)->getvartype()
			);
			(yyval)->set_ast_node(logicNode);
	     }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 864 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" rel_expression : simple_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"rel_expr");
			(yyval)->setvartype((yyvsp[(1) - (1)])->getvartype());
			(yyval)->set_ast_node((yyvsp[(1) - (1)])->get_ast_node());
	    }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 873 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" rel_expression : simple_expression RELOP simple_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (3)])->getname()<<(yyvsp[(2) - (3)])->getname()<<(yyvsp[(3) - (3)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (3)])->getname()+(yyvsp[(2) - (3)])->getname()+(yyvsp[(3) - (3)])->getname(),"rel_expr");
			(yyval)->setvartype("int");
			
			//do type checking of both side of relop
			
			if((yyvsp[(1) - (3)])->getvartype() == "void" || (yyvsp[(3) - (3)])->getvartype() == "void") //if any of them is a void
			{
				outerror<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				outlog<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				errors++;
				
				(yyval)->setvartype("error");
			}
			
			if((yyvsp[(1) - (3)])->getvartype() == "error" || (yyvsp[(3) - (3)])->getvartype() == "error") //if any of them is a error
			{
				(yyval)->setvartype("error");
			}
			
			// Create AST node for relational operation
			BinaryOpNode* relNode = new BinaryOpNode(
				(yyvsp[(2) - (3)])->getname(),
				(ExprNode*)(yyvsp[(1) - (3)])->get_ast_node(),
				(ExprNode*)(yyvsp[(3) - (3)])->get_ast_node(),
				(yyval)->getvartype()
			);
			(yyval)->set_ast_node(relNode);
	    }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 908 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" simple_expression : term "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"simp_expr");
			(yyval)->setvartype((yyvsp[(1) - (1)])->getvartype());
			(yyval)->set_ast_node((yyvsp[(1) - (1)])->get_ast_node());
			
	      }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 918 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" simple_expression : simple_expression ADDOP term "<<endl<<endl;
			outlog<<(yyvsp[(1) - (3)])->getname()<<(yyvsp[(2) - (3)])->getname()<<(yyvsp[(3) - (3)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (3)])->getname()+(yyvsp[(2) - (3)])->getname()+(yyvsp[(3) - (3)])->getname(),"simp_expr");
			(yyval)->setvartype((yyvsp[(1) - (3)])->getvartype());
			
			//do type checking of both side of addop
			
			if((yyvsp[(1) - (3)])->getvartype() == "void" || (yyvsp[(3) - (3)])->getvartype() == "void") //if any of them is a void
			{
				outerror<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				outlog<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				errors++;
				
				(yyval)->setvartype("error");
			}
			else if((yyvsp[(1) - (3)])->getvartype() == "float" || (yyvsp[(3) - (3)])->getvartype() == "float") //if any of them is a float
			{
				(yyval)->setvartype("float");
			}
			else (yyval)->setvartype("int");
			
			if((yyvsp[(1) - (3)])->getvartype() == "error" || (yyvsp[(3) - (3)])->getvartype() == "error") //if any of them is a error
			{
				(yyval)->setvartype("error");
			}
			
			// Create AST node for addition/subtraction
			BinaryOpNode* addopNode = new BinaryOpNode(
				(yyvsp[(2) - (3)])->getname(),
				(ExprNode*)(yyvsp[(1) - (3)])->get_ast_node(),
				(ExprNode*)(yyvsp[(3) - (3)])->get_ast_node(),
				(yyval)->getvartype()
			);
			(yyval)->set_ast_node(addopNode);
	      }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 958 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" term : unary_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"term");
			(yyval)->setvartype((yyvsp[(1) - (1)])->getvartype());
			(yyval)->set_ast_node((yyvsp[(1) - (1)])->get_ast_node());
			
	 }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 968 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" term : term MULOP unary_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (3)])->getname()<<(yyvsp[(2) - (3)])->getname()<<(yyvsp[(3) - (3)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (3)])->getname()+(yyvsp[(2) - (3)])->getname()+(yyvsp[(3) - (3)])->getname(),"term");
			(yyval)->setvartype((yyvsp[(1) - (3)])->getvartype());
			
			//do type checking of both side of mulop
			if((yyvsp[(1) - (3)])->getvartype() == "void" || (yyvsp[(3) - (3)])->getvartype() == "void") //if any of them is a void
			{
				outerror<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				outlog<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				errors++;
				
				(yyval)->setvartype("error");
			}
			else if((yyvsp[(1) - (3)])->getvartype() == "float" || (yyvsp[(3) - (3)])->getvartype() == "float") //if any of them is a float
			{
				(yyval)->setvartype("float");
			}
			else (yyval)->setvartype("int");
			
			//check if both int for modulous
			if((yyvsp[(2) - (3)])->getname() == "%")
			{
				if((yyvsp[(1) - (3)])->getvartype() == "int" && (yyvsp[(3) - (3)])->getvartype() == "int")
				{
					if((yyvsp[(3) - (3)])->getname()=="0")
					{
						outerror<<"At line no: "<<lines<<" Modulus by 0 "<<endl<<endl;
						outlog<<"At line no: "<<lines<<" Modulus by 0 "<<endl<<endl;
						errors++;
						
						(yyval)->setvartype("error");
					}
					else (yyval)->setvartype("int");
				}
				else if((yyvsp[(1) - (3)])->getvartype() == "float" || (yyvsp[(3) - (3)])->getvartype() == "float")
				{
					outerror<<"At line no: "<<lines<<" Modulus operator on non integer type "<<endl<<endl;
					outlog<<"At line no: "<<lines<<" Modulus operator on non integer type "<<endl<<endl;
					errors++;
					
					(yyval)->setvartype("error");
				}
			}
			
			if((yyvsp[(2) - (3)])->getname() == "/") //divide by 0
			{
				if((yyvsp[(3) - (3)])->getname()=="0")
				{
					outerror<<"At line no: "<<lines<<" Divide by 0 "<<endl<<endl;
					outlog<<"At line no: "<<lines<<" Divide by 0 "<<endl<<endl;
					errors++;
					
					(yyval)->setvartype("error");
				}
			}
			if((yyvsp[(1) - (3)])->getvartype() == "error" || (yyvsp[(3) - (3)])->getvartype() == "error") //if any of them is a error
			{
				(yyval)->setvartype("error");
			}
			
			// Create AST node for multiplication/division/modulus
			BinaryOpNode* mulopNode = new BinaryOpNode(
				(yyvsp[(2) - (3)])->getname(),
				(ExprNode*)(yyvsp[(1) - (3)])->get_ast_node(),
				(ExprNode*)(yyvsp[(3) - (3)])->get_ast_node(),
				(yyval)->getvartype()
			);
			(yyval)->set_ast_node(mulopNode);
	 }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 1043 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" unary_expression : ADDOP unary_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (2)])->getname()<<(yyvsp[(2) - (2)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (2)])->getname()+(yyvsp[(2) - (2)])->getname(),"un_expr");
			(yyval)->setvartype((yyvsp[(2) - (2)])->getvartype());
			
			if((yyvsp[(2) - (2)])->getvartype()=="void")
			{
				outerror<<"At line no: "<<lines<<" operation on void type : "<<(yyvsp[(2) - (2)])->getname()<<endl<<endl;
				outlog<<"At line no: "<<lines<<" operation on void type : "<<(yyvsp[(2) - (2)])->getname()<<endl<<endl;
				errors++;
				
				(yyval)->setvartype("error");
			}
			
			// Create AST node for unary plus/minus
			UnaryOpNode* unaryNode = new UnaryOpNode(
				(yyvsp[(1) - (2)])->getname(),
				(ExprNode*)(yyvsp[(2) - (2)])->get_ast_node(),
				(yyval)->getvartype()
			);
			(yyval)->set_ast_node(unaryNode);
	     }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 1068 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" unary_expression : NOT unary_expression "<<endl<<endl;
			outlog<<"!"<<(yyvsp[(2) - (2)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info("!"+(yyvsp[(2) - (2)])->getname(),"un_expr");
			(yyval)->setvartype("int");
			
			if((yyvsp[(2) - (2)])->getvartype()=="void")
			{
				outerror<<"At line no: "<<lines<<" operation on void type : "<<(yyvsp[(2) - (2)])->getname()<<endl<<endl;
				outlog<<"At line no: "<<lines<<" operation on void type : "<<(yyvsp[(2) - (2)])->getname()<<endl<<endl;
				errors++;
				
				(yyval)->setvartype("error");
			}
			
			// Create AST node for logical NOT
			UnaryOpNode* notNode = new UnaryOpNode(
				"!",
				(ExprNode*)(yyvsp[(2) - (2)])->get_ast_node(),
				(yyval)->getvartype()
			);
			(yyval)->set_ast_node(notNode);
	     }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 1093 "22299480_222101811.y"
    {
	    	outlog<<"At line no: "<<lines<<" unary_expression : factor "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"un_expr");
			(yyval)->setvartype((yyvsp[(1) - (1)])->getvartype());
			(yyval)->set_ast_node((yyvsp[(1) - (1)])->get_ast_node());
			
			//outlog<<$1->getvartype()<<endl;
	     }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 1113 "22299480_222101811.y"
    {
	    outlog<<"At line no: "<<lines<<" factor : variable "<<endl<<endl;
		outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
			
		(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"fctr");
		(yyval)->setvartype((yyvsp[(1) - (1)])->getvartype());
		(yyval)->set_ast_node((yyvsp[(1) - (1)])->get_ast_node());
	}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 1122 "22299480_222101811.y"
    {
	    outlog<<"At line no: "<<lines<<" factor : ID LPAREN argument_list RPAREN "<<endl<<endl;
	    outlog<<(yyvsp[(1) - (4)])->getname()<<"("<<(yyvsp[(3) - (4)])->getname()<<")"<<endl<<endl;
	
	    (yyval) = new symbol_info((yyvsp[(1) - (4)])->getname()+"("+(yyvsp[(3) - (4)])->getname()+")","fctr");
	    (yyval)->setvartype("error");
	
	    int flag = 0;
	
	    // Type checking (existing code)
	    if(symtbl->Lookup_in_table((yyvsp[(1) - (4)])->getname())==NULL) //undeclared function
	    {
	        outerror<<"At line no: "<<lines<<" Undeclared function: "<<(yyvsp[(1) - (4)])->getname()<<endl<<endl;
	        outlog<<"At line no: "<<lines<<" Undeclared function: "<<(yyvsp[(1) - (4)])->getname()<<endl<<endl;
	        errors++;
	    }
	    else
	    {
	        if((symtbl->Lookup_in_table((yyvsp[(1) - (4)])->getname()))->getidtype()=="func_dec") //declared but not defined
	        {
	            outerror<<"At line no: "<<lines<<" Undefined function: "<<(yyvsp[(1) - (4)])->getname()<<endl<<endl;
	            outlog<<"At line no: "<<lines<<" Undefined function: "<<(yyvsp[(1) - (4)])->getname()<<endl<<endl;
	            errors++;
	        }
	        else if((symtbl->Lookup_in_table((yyvsp[(1) - (4)])->getname()))->getidtype()=="func_def")
	        {
	            vector<string> templist = (symtbl->Lookup_in_table((yyvsp[(1) - (4)])->getname()))->getparamlist();
	
	            if(arglist.size()!=templist.size()) //number of prameters don't match
	            {
	                outerror<<"At line no: "<<lines<<" Inconsistencies in number of arguments in function call: "<<(yyvsp[(1) - (4)])->getname()<<endl<<endl;
	                outlog<<"At line no: "<<lines<<" Inconsistencies in number of arguments in function call: "<<(yyvsp[(1) - (4)])->getname()<<endl<<endl;
	                errors++;
	            }
	            else if(templist.size()!=0)
	            {
	                for(int i = 0; i < templist.size(); i++)
	                {
	                    if(arglist[i]!=templist[i])
	                    {
	                        if(arglist[i] == "int" && templist[i] == "float") {}
	                        else if(arglist[i]!="error")
	                        {
	                            flag = 1;
	                            outerror<<"At line no: "<<lines<<" "<<"argument "<<i+1<<" type mismatch in function call: "<<(yyvsp[(1) - (4)])->getname()<<endl<<endl;
	                            outlog<<"At line no: "<<lines<<" "<<"argument "<<i+1<<" type mismatch in function call: "<<(yyvsp[(1) - (4)])->getname()<<endl<<endl;
	                            errors++;
	                        }
	                    }
	                }                   
	            }
	            if(!flag) (yyval)->setvartype((symtbl->Lookup_in_table((yyvsp[(1) - (4)])->getname()))->getvartype());
	        }
	    }
	
	    // Create function call node
	    FuncCallNode* funcCall = new FuncCallNode((yyvsp[(1) - (4)])->getname(), (yyval)->getvartype());
	
	    // Get arguments from the ArgumentsNode if it exists
	    if ((yyvsp[(3) - (4)])->get_ast_node()) {
	        ArgumentsNode* argsNode = dynamic_cast<ArgumentsNode*>((yyvsp[(3) - (4)])->get_ast_node());
	        if (argsNode) {
	            // Add each argument to the function call
	            for (auto arg : argsNode->get_arguments()) {
	                funcCall->add_argument(arg);
	            }
	        }
	    }
	
	    (yyval)->set_ast_node(funcCall);
	
	    arglist.clear();
	}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 1196 "22299480_222101811.y"
    {
	   	outlog<<"At line no: "<<lines<<" factor : LPAREN expression RPAREN "<<endl<<endl;
		outlog<<"("<<(yyvsp[(2) - (3)])->getname()<<")"<<endl<<endl;
		
		(yyval) = new symbol_info("("+(yyvsp[(2) - (3)])->getname()+")","fctr");
		(yyval)->setvartype((yyvsp[(2) - (3)])->getvartype());
		(yyval)->set_ast_node((yyvsp[(2) - (3)])->get_ast_node()); // Pass through the expression AST
	}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 1205 "22299480_222101811.y"
    {
	    outlog<<"At line no: "<<lines<<" factor : CONST_INT "<<endl<<endl;
		outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
			
		(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"fctr");
		(yyval)->setvartype("int");
		
		// Create AST node for integer constant
		ConstNode* intNode = new ConstNode((yyvsp[(1) - (1)])->getname(), "int");
		(yyval)->set_ast_node(intNode);
	}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 1217 "22299480_222101811.y"
    {
	    outlog<<"At line no: "<<lines<<" factor : CONST_FLOAT "<<endl<<endl;
		outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
			
		(yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"fctr");
		(yyval)->setvartype("float");
		
		// Create AST node for float constant
		ConstNode* floatNode = new ConstNode((yyvsp[(1) - (1)])->getname(), "float");
		(yyval)->set_ast_node(floatNode);
	}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 1229 "22299480_222101811.y"
    {
	    outlog<<"At line no: "<<lines<<" factor : variable INCOP "<<endl<<endl;
		outlog<<(yyvsp[(1) - (2)])->getname()<<"++"<<endl<<endl;
			
		(yyval) = new symbol_info((yyvsp[(1) - (2)])->getname()+"++","fctr");
		(yyval)->setvartype((yyvsp[(1) - (2)])->getvartype());
		
		// Create AST nodes for increment
		// For x++, equivalent to (x = x + 1)
		VarNode* varNode = (VarNode*)(yyvsp[(1) - (2)])->get_ast_node();
		ConstNode* oneNode = new ConstNode("1", "int");
		BinaryOpNode* addNode = new BinaryOpNode("+", varNode, oneNode, (yyvsp[(1) - (2)])->getvartype());
		AssignNode* assignNode = new AssignNode(varNode, addNode, (yyvsp[(1) - (2)])->getvartype());
		(yyval)->set_ast_node(assignNode);
	}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 1245 "22299480_222101811.y"
    {
	    outlog<<"At line no: "<<lines<<" factor : variable DECOP "<<endl<<endl;
		outlog<<(yyvsp[(1) - (2)])->getname()<<"--"<<endl<<endl;
			
		(yyval) = new symbol_info((yyvsp[(1) - (2)])->getname()+"--","fctr");
		(yyval)->setvartype((yyvsp[(1) - (2)])->getvartype());
		
		// Create AST nodes for decrement
		// For x--, equivalent to (x = x - 1)
		VarNode* varNode = (VarNode*)(yyvsp[(1) - (2)])->get_ast_node();
		ConstNode* oneNode = new ConstNode("1", "int");
		BinaryOpNode* subNode = new BinaryOpNode("-", varNode, oneNode, (yyvsp[(1) - (2)])->getvartype());
		AssignNode* assignNode = new AssignNode(varNode, subNode, (yyvsp[(1) - (2)])->getvartype());
		(yyval)->set_ast_node(assignNode);
	}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 1263 "22299480_222101811.y"
    {
                    outlog<<"At line no: "<<lines<<" argument_list : arguments "<<endl<<endl;
                    outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
                        
                    (yyval) = (yyvsp[(1) - (1)]); // Pass through the arguments node
              }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 1270 "22299480_222101811.y"
    {
                    outlog<<"At line no: "<<lines<<" argument_list :  "<<endl<<endl;
                    outlog<<""<<endl<<endl;
                        
                    (yyval) = new symbol_info("","arg_list");
                    // Create empty arguments node
                    ArgumentsNode* args = new ArgumentsNode();
                    (yyval)->set_ast_node(args);
              }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 1282 "22299480_222101811.y"
    {
                outlog<<"At line no: "<<lines<<" arguments : arguments COMMA logic_expression "<<endl<<endl;
                outlog<<(yyvsp[(1) - (3)])->getname()<<","<<(yyvsp[(3) - (3)])->getname()<<endl<<endl;
                        
                (yyval) = new symbol_info((yyvsp[(1) - (3)])->getname()+","+(yyvsp[(3) - (3)])->getname(),"arg");
                
                // Get existing arguments node or create new one
                ArgumentsNode* args;
                if ((yyvsp[(1) - (3)])->get_ast_node()) {
                    args = dynamic_cast<ArgumentsNode*>((yyvsp[(1) - (3)])->get_ast_node());
                } else {
                    args = new ArgumentsNode();
                }
                
                // Add the new argument
                if ((yyvsp[(3) - (3)])->get_ast_node()) {
                    args->add_argument(dynamic_cast<ExprNode*>((yyvsp[(3) - (3)])->get_ast_node()));
                }
                
                (yyval)->set_ast_node(args);
                arglist.push_back((yyvsp[(3) - (3)])->getvartype());
          }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 1305 "22299480_222101811.y"
    {
                outlog<<"At line no: "<<lines<<" arguments : logic_expression "<<endl<<endl;
                outlog<<(yyvsp[(1) - (1)])->getname()<<endl<<endl;
                        
                (yyval) = new symbol_info((yyvsp[(1) - (1)])->getname(),"arg");
                
                // Create a new arguments node with single argument
                ArgumentsNode* args = new ArgumentsNode();
                if ((yyvsp[(1) - (1)])->get_ast_node()) {  // FIXED: Changed from $3 to $1
                    args->add_argument(dynamic_cast<ExprNode*>((yyvsp[(1) - (1)])->get_ast_node()));
                }
                
                (yyval)->set_ast_node(args);
                arglist.push_back((yyvsp[(1) - (1)])->getvartype());
          }
    break;


/* Line 1792 of yacc.c  */
#line 3055 "y.tab.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 1323 "22299480_222101811.y"


int main(int argc, char *argv[])
{
	if(argc != 2) 
	{
		cout<<"Please input file name"<<endl;
		return 0;
	}
	yyin = fopen(argv[1], "r");
	outlog.open("log.txt", ios::trunc);
	outerror.open("error.txt", ios::trunc);
	outcode.open("code.txt", ios::trunc);
	
	if(yyin == NULL)
	{
		cout<<"Couldn't open file"<<endl;
		return 0;
	}
	
	// First pass: Parse the input and build AST
	cout << "==== Pass 1: Parsing input and building AST ====" << endl;
	outlog << "==== Pass 1: Parsing input and building AST ====" << endl;
	
	symtbl->enter_scope(outlog);
	yyparse();
	
	outlog << endl << "Symbol Table after first pass:" << endl;
	symtbl->Print_all_scope(outlog);
	
	// Only proceed to second pass if no errors
	if (errors == 0 && ast_root) {
		cout << "==== Pass 2: Generating Three-Address Code from AST ====" << endl;
		outlog << endl << "==== Pass 2: Generating Three-Address Code from AST ====" << endl;
		
		// Generate three-address code (second pass)
		outlog << "Generating Three-Address Code..." << endl;
		ThreeAddrCodeGenerator tacGen(ast_root, outcode);
		tacGen.generate();
		
		outlog << "Three-Address Code Generation Complete" << endl;
		cout << "Three-Address Code Generation Complete. Output written to code.txt" << endl;
	} else {
		cout << "Three-Address Code generation skipped due to errors" << endl;
		outlog << endl << "Three-Address Code generation skipped due to errors" << endl;
		outcode << "// Three-Address Code generation failed due to errors" << endl;
	}
	
	outlog<<endl<<"Total lines: "<<lines<<endl;
	outlog<<"Total errors: "<<errors<<endl;
	outerror<<"Total errors: "<<errors<<endl;
	
	outlog.close();
	outerror.close();
	outcode.close();
	
	fclose(yyin);
	
	return 0;
}