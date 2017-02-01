/* A Bison parser, made by GNU Bison 1.875b.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
#define yyparse MMS_parse
#define yylex   MMS_lex
#define yyerror MMS_error
#define yylval  MMS_lval
#define yychar  MMS_char
#define yydebug MMS_debug
#define yynerrs MMS_nerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TEXTUAL_ID = 258,
     NUMERIC_ID = 259,
     QUOTED_STRING = 260,
     TOK_ContainerContents = 261,
     TOK_DialogForm = 262,
     TOK_MainDataContDef = 263,
     TOK_TaskItem = 264,
     TOK_Consts = 265,
     TOK_SbCnts = 266,
     TOK_GenJrnlFldDef = 267,
     TOK_DocSelRefObj = 268,
     TOK_DocNumDef = 269,
     TOK_Documents = 270,
     TOK_DocumentStreams = 271,
     TOK_Registers = 272,
     TOK_ReportList = 273,
     TOK_Journalisters = 274,
     TOK_EnumList = 275,
     TOK_CalcJournals = 276,
     TOK_Calendars = 277,
     TOK_CalcAlgorithms = 278,
     TOK_RecalcRules = 279,
     TOK_Groups = 280,
     TOK_Buh = 281,
     TOK_AccParams = 282,
     TOK_Plans = 283,
     TOK_Accounts = 284,
     TOK_ProvParams = 285,
     TOK_OperParams = 286,
     TOK_SbKind = 287,
     TOK_TypOpersDef = 288,
     TOK_CorrProvsDef = 289,
     TOK_ProvHardFldDef = 290,
     TOK_OperJournal = 291,
     TOK_FormList = 292
   };
#endif
#define TEXTUAL_ID 258
#define NUMERIC_ID 259
#define QUOTED_STRING 260
#define TOK_ContainerContents 261
#define TOK_DialogForm 262
#define TOK_MainDataContDef 263
#define TOK_TaskItem 264
#define TOK_Consts 265
#define TOK_SbCnts 266
#define TOK_GenJrnlFldDef 267
#define TOK_DocSelRefObj 268
#define TOK_DocNumDef 269
#define TOK_Documents 270
#define TOK_DocumentStreams 271
#define TOK_Registers 272
#define TOK_ReportList 273
#define TOK_Journalisters 274
#define TOK_EnumList 275
#define TOK_CalcJournals 276
#define TOK_Calendars 277
#define TOK_CalcAlgorithms 278
#define TOK_RecalcRules 279
#define TOK_Groups 280
#define TOK_Buh 281
#define TOK_AccParams 282
#define TOK_Plans 283
#define TOK_Accounts 284
#define TOK_ProvParams 285
#define TOK_OperParams 286
#define TOK_SbKind 287
#define TOK_TypOpersDef 288
#define TOK_CorrProvsDef 289
#define TOK_ProvHardFldDef 290
#define TOK_OperJournal 291
#define TOK_FormList 292




/* Copy the first part of user declarations.  */
#line 2 "..\\MainMetadataStream.y"

	#include <stdio.h>
	#include "MMS.h"
	
	#define YYSTYPE MMS_StackValue

	int MMS_lex(YYSTYPE *lvalp, FILE *File);
	void MMS_error (FILE *File, CMMSObject** ParserResult, char const * ErrString);


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 180 "..\\MainMetadataStream.tab.cpp"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   334

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  31
/* YYNRULES -- Number of rules. */
#define YYNRULES  100
/* YYNRULES -- Number of states. */
#define YYNSTATES  323

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
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
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     7,    13,    17,    23,    30,    32,    35,
      37,    41,    46,    50,    57,    64,    68,    78,    83,    88,
      92,    98,   103,   108,   113,   117,   123,   128,   132,   138,
     142,   148,   152,   158,   163,   167,   173,   178,   182,   188,
     193,   198,   202,   210,   212,   216,   228,   230,   234,   246,
     248,   252,   270,   274,   280,   284,   290,   292,   293,   297,
     307,   309,   310,   314,   326,   328,   329,   333,   345,   347,
     348,   352,   364,   366,   370,   372,   377,   381,   387,   392,
     397,   402,   407,   412,   417,   422,   424,   428,   444,   458,
     462,   468,   470,   474,   497,   498,   500,   503,   505,   509,
     511
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      42,     0,    -1,    38,    44,    39,    -1,    38,     6,    40,
      44,    39,    -1,    38,     6,    39,    -1,    38,     7,    40,
      44,    39,    -1,    38,     7,    40,    44,    39,    43,    -1,
       1,    -1,    43,     1,    -1,    45,    -1,    44,    40,    45,
      -1,    38,     3,    69,    39,    -1,    38,     4,    39,    -1,
      38,     4,    40,     5,    69,    39,    -1,    38,     4,    40,
      45,    69,    39,    -1,    38,    69,    39,    -1,    38,     8,
      40,     5,    40,     5,    40,     5,    39,    -1,    38,     9,
      69,    39,    -1,    38,    10,    69,    39,    -1,    38,    11,
      39,    -1,    38,    11,    40,    46,    39,    -1,    38,    12,
      69,    39,    -1,    38,    13,    69,    39,    -1,    38,    14,
      69,    39,    -1,    38,    15,    39,    -1,    38,    15,    40,
      48,    39,    -1,    38,    17,    69,    39,    -1,    38,    16,
      39,    -1,    38,    16,    40,    50,    39,    -1,    38,    18,
      39,    -1,    38,    18,    40,    54,    39,    -1,    38,    19,
      39,    -1,    38,    19,    40,    56,    39,    -1,    38,    20,
      69,    39,    -1,    38,    21,    39,    -1,    38,    21,    40,
      58,    39,    -1,    38,    22,    69,    39,    -1,    38,    23,
      39,    -1,    38,    23,    40,    60,    39,    -1,    38,    24,
      69,    39,    -1,    38,    25,    69,    39,    -1,    38,    26,
      39,    -1,    38,    26,    40,    38,    62,    39,    39,    -1,
      47,    -1,    46,    40,    47,    -1,    38,     4,    40,     5,
      40,     5,    40,     5,    40,    69,    39,    -1,    49,    -1,
      48,    40,    49,    -1,    38,     4,    40,     5,    40,     5,
      40,     5,    40,    69,    39,    -1,    51,    -1,    50,    40,
      51,    -1,    38,     4,    40,     5,    40,     5,    40,     5,
      40,     5,    40,     5,    40,    52,    40,    53,    39,    -1,
      38,    17,    39,    -1,    38,    17,    40,    69,    39,    -1,
      38,    15,    39,    -1,    38,    15,    40,    69,    39,    -1,
      55,    -1,    -1,    54,    40,    55,    -1,    38,     4,    40,
       5,    40,     5,    40,     5,    39,    -1,    57,    -1,    -1,
      56,    40,    57,    -1,    38,     4,    40,     5,    40,     5,
      40,     5,    40,    69,    39,    -1,    59,    -1,    -1,    58,
      40,    59,    -1,    38,     4,    40,     5,    40,     5,    40,
       5,    40,    69,    39,    -1,    61,    -1,    -1,    60,    40,
      61,    -1,    38,     4,    40,     5,    40,     5,    40,     5,
      40,    69,    39,    -1,     4,    -1,    62,    40,    63,    -1,
      71,    -1,    38,    27,    69,    39,    -1,    38,    28,    39,
      -1,    38,    28,    40,    64,    39,    -1,    38,    30,    69,
      39,    -1,    38,    31,    69,    39,    -1,    38,    32,    69,
      39,    -1,    38,    33,    69,    39,    -1,    38,    34,    69,
      39,    -1,    38,    35,    69,    39,    -1,    38,    36,    69,
      39,    -1,    65,    -1,    64,    40,    65,    -1,    38,     4,
      40,     5,    40,     5,    40,     5,    40,     5,    40,     5,
      40,    66,    39,    -1,    38,     4,    40,     5,    40,     5,
      40,     5,    40,     5,    40,    66,    39,    -1,    38,    29,
      39,    -1,    38,    29,    40,    67,    39,    -1,    68,    -1,
      67,    40,    68,    -1,    38,     4,    40,     5,    40,     5,
      40,     5,    40,     5,    40,     5,    40,     5,    40,     5,
      40,     5,    40,     5,    69,    39,    -1,    -1,    70,    -1,
      40,    70,    -1,    71,    -1,    70,    40,    71,    -1,     5,
      -1,    45,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,    61,    61,    67,    71,    75,    81,    89,    90,    92,
      97,   103,   109,   114,   119,   127,   141,   146,   153,   159,
     163,   169,   175,   181,   187,   191,   197,   203,   208,   214,
     218,   224,   228,   234,   240,   244,   250,   256,   260,   266,
     272,   278,   283,   293,   298,   304,   318,   323,   329,   343,
     348,   354,   362,   367,   374,   379,   390,   395,   395,   401,
     414,   419,   419,   425,   439,   444,   444,   450,   464,   469,
     469,   475,   489,   493,   502,   506,   511,   517,   522,   527,
     532,   537,   542,   547,   552,   561,   566,   573,   579,   585,
     590,   600,   605,   611,   625,   626,   627,   629,   634,   640,
     644
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TEXTUAL_ID", "NUMERIC_ID", 
  "QUOTED_STRING", "TOK_ContainerContents", "TOK_DialogForm", 
  "TOK_MainDataContDef", "TOK_TaskItem", "TOK_Consts", "TOK_SbCnts", 
  "TOK_GenJrnlFldDef", "TOK_DocSelRefObj", "TOK_DocNumDef", 
  "TOK_Documents", "TOK_DocumentStreams", "TOK_Registers", 
  "TOK_ReportList", "TOK_Journalisters", "TOK_EnumList", 
  "TOK_CalcJournals", "TOK_Calendars", "TOK_CalcAlgorithms", 
  "TOK_RecalcRules", "TOK_Groups", "TOK_Buh", "TOK_AccParams", 
  "TOK_Plans", "TOK_Accounts", "TOK_ProvParams", "TOK_OperParams", 
  "TOK_SbKind", "TOK_TypOpersDef", "TOK_CorrProvsDef", 
  "TOK_ProvHardFldDef", "TOK_OperJournal", "TOK_FormList", "'{'", "'}'", 
  "','", "$accept", "mms", "may_be_errors", "object_list", "object", 
  "sbcnts_list", "subconto", "doc_list", "document", "doc_stream_list", 
  "doc_stream", "ds_reg_props", "ds_doc_props", "report_list", "report", 
  "journal_list", "journal", "calcjournal_list", "calcjournal", 
  "calcalg_list", "calcalg", "buh_params", "buh_object", "AccPlanList", 
  "AccPlan", "AccList", "Accounts", "Account", "properties", "prop_list", 
  "property", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   123,   125,
      44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    41,    42,    42,    42,    42,    42,    43,    43,    44,
      44,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    46,    46,    47,    48,    48,    49,    50,
      50,    51,    52,    52,    53,    53,    54,    54,    54,    55,
      56,    56,    56,    57,    58,    58,    58,    59,    60,    60,
      60,    61,    62,    62,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    64,    64,    65,    65,    66,
      66,    67,    67,    68,    69,    69,    69,    70,    70,    71,
      71
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     3,     5,     3,     5,     6,     1,     2,     1,
       3,     4,     3,     6,     6,     3,     9,     4,     4,     3,
       5,     4,     4,     4,     3,     5,     4,     3,     5,     3,
       5,     3,     5,     4,     3,     5,     4,     3,     5,     4,
       4,     3,     7,     1,     3,    11,     1,     3,    11,     1,
       3,    17,     3,     5,     3,     5,     1,     0,     3,     9,
       1,     0,     3,    11,     1,     0,     3,    11,     1,     0,
       3,    11,     1,     3,     1,     4,     3,     5,     4,     4,
       4,     4,     4,     4,     4,     1,     3,    15,    13,     3,
       5,     1,     3,    22,     0,     1,     2,     1,     3,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     0,    94,     0,     9,     1,     4,
       0,     0,    94,     0,    99,     0,    94,    94,     0,    94,
      94,    94,     0,     0,    94,     0,     0,    94,     0,    94,
       0,    94,    94,     0,     0,   100,     0,    95,    97,     2,
       0,     0,     0,     0,    12,     0,     0,     0,     0,    19,
       0,     0,     0,     0,    24,     0,    27,     0,     0,    29,
      57,    31,    61,     0,    34,    65,     0,    37,    69,     0,
       0,    41,     0,    96,    15,     0,    10,     3,     0,    11,
      94,    94,     0,    17,    18,     0,     0,    43,    21,    22,
      23,     0,     0,    46,     0,     0,    49,    26,     0,     0,
      56,     0,     0,    60,    33,     0,     0,    64,    36,     0,
       0,    68,    39,    40,     0,    98,     7,     0,     0,     0,
       0,     0,    20,     0,     0,    25,     0,     0,    28,     0,
       0,    30,     0,     0,    32,     0,     0,    35,     0,     0,
      38,     0,    72,     0,     8,    13,    14,     0,     0,    44,
       0,    47,     0,    50,     0,    58,     0,    62,     0,    66,
       0,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    42,    94,    73,    74,     0,     0,     0,     0,
       0,     0,     0,     0,    94,     0,    94,    94,    94,    94,
      94,    94,    94,    16,     0,     0,     0,     0,     0,     0,
       0,     0,    76,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    75,     0,
       0,    85,    78,    79,    80,    81,    82,    83,    84,     0,
       0,     0,     0,     0,     0,     0,     0,    77,     0,    94,
      94,     0,    59,    94,    94,    94,     0,    86,     0,     0,
       0,     0,     0,     0,     0,    45,    48,     0,    63,    67,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    52,    94,     0,     0,     0,     0,     0,    51,
       0,    53,    54,    94,     0,     0,     0,     0,     0,     0,
      88,    55,     0,    89,     0,    87,     0,     0,    91,     0,
      90,     0,     0,    92,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      94,     0,    93
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     2,   117,     6,    35,    86,    87,    92,    93,    95,
      96,   267,   275,    99,   100,   102,   103,   106,   107,   110,
     111,   143,   174,   220,   221,   286,   297,   298,    36,    37,
      38
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -75
static const short yypact[] =
{
     -32,    73,    14,   -37,   -22,    21,   -29,   -75,   -75,   -75,
     -10,   -10,    11,    23,   -75,    13,    11,    11,    25,    11,
      11,    11,    27,    31,    11,    33,    35,    11,    37,    11,
      84,    11,    11,    86,    16,   -75,    19,    38,   -75,   -75,
     -10,    88,    90,    49,   -75,    22,    77,    80,   124,   -75,
      46,   125,   126,   127,   -75,    83,   -75,   129,   130,   -75,
     132,   -75,   133,   134,   -75,   143,   144,   -75,   146,   147,
     148,   -75,   150,    38,   -75,    16,   -75,   -75,    55,   -75,
      11,    11,   128,   -75,   -75,   178,    92,   -75,   -75,   -75,
     -75,   181,    94,   -75,   185,    96,   -75,   -75,   186,    98,
     -75,   187,   100,   -75,   -75,   188,   102,   -75,   -75,   189,
     104,   -75,   -75,   -75,   190,   -75,   -75,   145,   156,   157,
     192,   158,   -75,    46,   159,   -75,    83,   160,   -75,   129,
     161,   -75,   132,   162,   -75,   133,   163,   -75,   143,   164,
     -75,   146,   -75,   108,   -75,   -75,   -75,   165,   201,   -75,
     202,   -75,   203,   -75,   204,   -75,   205,   -75,   206,   -75,
     207,   -75,   174,    43,   209,   175,   176,   177,   179,   180,
     182,   183,   -75,    82,   -75,   -75,   191,   213,   216,   219,
     220,   221,   224,   229,    11,   110,    11,    11,    11,    11,
      11,    11,    11,   -75,   195,   196,   197,   198,   199,   200,
     208,   210,   -75,   212,   214,   215,   217,   218,   223,   225,
     226,   236,   237,   238,   239,   240,   241,   242,   -75,   247,
     112,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   227,
     228,   230,   233,   234,   235,   243,   244,   -75,   212,    11,
      11,   250,   -75,    11,    11,    11,   253,   -75,   246,   248,
     249,   251,   252,   254,   255,   -75,   -75,   258,   -75,   -75,
     -75,   261,   256,   257,   222,   264,   259,   260,   262,   114,
     263,   268,   -75,    11,   265,   266,   267,   270,   116,   -75,
      45,   -75,   -75,    11,   271,   269,   273,   274,   272,   118,
     -75,   -75,   275,   -75,   277,   -75,   278,   120,   -75,   276,
     -75,   277,   281,   -75,   279,   283,   280,   287,   282,   289,
     284,   294,   285,   298,   286,   299,   288,   301,   290,   312,
      11,   292,   -75
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
     -75,   -75,   -75,   151,    12,   -75,   136,   -75,   152,   -75,
     123,   -75,   -75,   -75,   149,   -75,   142,   -75,   141,   -75,
     193,   -75,   -75,   -75,    85,    30,   -75,    20,   -12,   293,
     -74
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -7
static const short yytable[] =
{
      43,   115,     9,    10,    47,    48,     1,    51,    52,    53,
      39,    40,    58,     7,     8,    63,    14,    66,    11,    69,
      70,    14,     7,     7,    12,    13,    14,    80,     5,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    14,     5,
     284,    34,    76,    46,     5,    -5,   116,    81,    74,     5,
       5,    34,    44,    45,    49,    50,    54,    55,   118,   119,
      56,    57,    59,    60,    61,    62,    64,    65,    75,     3,
       4,   173,    82,   285,    85,    12,    13,    14,    79,   175,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,   184,
     185,     5,   186,   187,   188,   189,   190,   191,   192,    83,
       5,    91,    34,    67,    68,    71,    72,    77,    40,    78,
      40,   122,   123,   125,   126,   128,   129,   131,   132,   134,
     135,   137,   138,   140,   141,    -6,   144,   162,   163,   202,
     203,   237,   238,   272,   273,   282,   283,   293,   294,   300,
     301,    41,    42,    84,    88,    89,    90,    94,   120,    97,
      98,   101,   201,   104,   204,   205,   206,   207,   208,   209,
     210,   105,   121,   108,   109,   124,   112,   113,   114,   127,
     130,   133,   136,   139,   142,   145,   146,   147,   148,   150,
     152,   154,   156,   158,   160,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   176,   177,   178,   179,   194,   180,
     181,   195,   182,   183,   196,   197,   198,   248,   249,   199,
     193,   251,   252,   253,   200,   211,   212,   213,   214,   215,
     216,   229,   230,   231,   232,   233,   234,   235,   217,   218,
     219,   236,   153,   222,   223,   250,   224,   225,   254,   149,
     266,   277,   226,   262,   227,   228,   263,   239,   240,   268,
     241,   287,   242,   276,   243,   244,   269,   157,   151,   159,
     278,   155,   299,   245,   246,   255,   304,   256,   306,   257,
     258,   259,   308,   260,   310,   261,   264,   265,   289,   312,
     270,   274,   271,   314,   316,   279,   318,   280,   321,   281,
     285,   288,   290,   291,   295,   296,   302,   320,   292,   305,
     307,   303,   309,   247,   311,   313,   315,    73,   317,     0,
     319,   322,     0,     0,   161
};

static const short yycheck[] =
{
      12,    75,    39,    40,    16,    17,    38,    19,    20,    21,
      39,    40,    24,     1,     0,    27,     5,    29,    40,    31,
      32,     5,    10,    11,     3,     4,     5,     5,    38,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,     5,    38,
       5,    40,    40,    40,    38,     0,     1,    45,    39,    38,
      38,    40,    39,    40,    39,    40,    39,    40,    80,    81,
      39,    40,    39,    40,    39,    40,    39,    40,    40,     6,
       7,    38,     5,    38,    38,     3,     4,     5,    39,   163,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    38,    30,    31,    32,    33,    34,    35,    36,    39,
      38,    38,    40,    39,    40,    39,    40,    39,    40,    39,
      40,    39,    40,    39,    40,    39,    40,    39,    40,    39,
      40,    39,    40,    39,    40,     0,     1,    39,    40,    39,
      40,    39,    40,    39,    40,    39,    40,    39,    40,    39,
      40,    10,    11,    39,    39,    39,    39,    38,    40,    39,
      38,    38,   184,    39,   186,   187,   188,   189,   190,   191,
     192,    38,     4,    39,    38,     4,    39,    39,    38,     4,
       4,     4,     4,     4,     4,    39,    39,     5,    40,    40,
      40,    40,    40,    40,    40,    40,     5,     5,     5,     5,
       5,     5,     5,    39,     5,    40,    40,    40,     5,    40,
      40,     5,    40,    40,     5,     5,     5,   239,   240,     5,
      39,   243,   244,   245,     5,    40,    40,    40,    40,    40,
      40,     5,     5,     5,     5,     5,     5,     5,    40,    39,
      38,     4,   129,    39,    39,     5,    39,    39,     5,   123,
      38,   273,    39,     5,    39,    39,     5,    40,    40,     5,
      40,   283,    39,     5,    40,    40,    17,   135,   126,   138,
      15,   132,     4,    40,    40,    39,     5,    39,     5,    40,
      39,    39,     5,    39,     5,    40,    40,    40,    29,     5,
      40,    38,    40,     5,     5,    39,     5,    40,   320,    39,
      38,    40,    39,    39,    39,    38,    40,     5,   288,    40,
      40,   301,    40,   238,    40,    40,    40,    34,    40,    -1,
      40,    39,    -1,    -1,   141
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    38,    42,     6,     7,    38,    44,    45,     0,    39,
      40,    40,     3,     4,     5,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    40,    45,    69,    70,    71,    39,
      40,    44,    44,    69,    39,    40,    40,    69,    69,    39,
      40,    69,    69,    69,    39,    40,    39,    40,    69,    39,
      40,    39,    40,    69,    39,    40,    69,    39,    40,    69,
      69,    39,    40,    70,    39,    40,    45,    39,    39,    39,
       5,    45,     5,    39,    39,    38,    46,    47,    39,    39,
      39,    38,    48,    49,    38,    50,    51,    39,    38,    54,
      55,    38,    56,    57,    39,    38,    58,    59,    39,    38,
      60,    61,    39,    39,    38,    71,     1,    43,    69,    69,
      40,     4,    39,    40,     4,    39,    40,     4,    39,    40,
       4,    39,    40,     4,    39,    40,     4,    39,    40,     4,
      39,    40,     4,    62,     1,    39,    39,     5,    40,    47,
      40,    49,    40,    51,    40,    55,    40,    57,    40,    59,
      40,    61,    39,    40,    40,     5,     5,     5,     5,     5,
       5,     5,    39,    38,    63,    71,     5,    40,    40,    40,
      40,    40,    40,    40,    27,    28,    30,    31,    32,    33,
      34,    35,    36,    39,     5,     5,     5,     5,     5,     5,
       5,    69,    39,    40,    69,    69,    69,    69,    69,    69,
      69,    40,    40,    40,    40,    40,    40,    40,    39,    38,
      64,    65,    39,    39,    39,    39,    39,    39,    39,     5,
       5,     5,     5,     5,     5,     5,     4,    39,    40,    40,
      40,    40,    39,    40,    40,    40,    40,    65,    69,    69,
       5,    69,    69,    69,     5,    39,    39,    40,    39,    39,
      39,    40,     5,     5,    40,    40,    38,    52,     5,    17,
      40,    40,    39,    40,    38,    53,     5,    69,    15,    39,
      40,    39,    39,    40,     5,    38,    66,    69,    40,    29,
      39,    39,    66,    39,    40,    39,    38,    67,    68,     4,
      39,    40,    40,    68,     5,    40,     5,    40,     5,    40,
       5,    40,     5,    40,     5,    40,     5,    40,     5,    40,
       5,    69,    39
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror (File, ParserResult, "syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, File)
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
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (FILE *File, CMMSObject** ParserResult);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (FILE *File, CMMSObject** ParserResult)
#else
int
yyparse (File, ParserResult)
    FILE *File;
    CMMSObject** ParserResult;
#endif
#endif
{
  /* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
#line 62 "..\\MainMetadataStream.y"
    {
	CMMS* pMMS = new CMMS(yyvsp[-1].pList);
	*ParserResult = (CMMSObject*)pMMS;
	delete yyvsp[-1].pList;
;}
    break;

  case 3:
#line 68 "..\\MainMetadataStream.y"
    {
	*ParserResult = (CMMSObject*)yyvsp[-1].pList;
;}
    break;

  case 4:
#line 72 "..\\MainMetadataStream.y"
    {
	*ParserResult = (CMMSObject*)new CMMSNodeList();
;}
    break;

  case 5:
#line 76 "..\\MainMetadataStream.y"
    {
	*ParserResult = (CMMSObject*) new CMMSObjectWithProps(yyvsp[-3].String, CString(""), yyvsp[-1].pList);
	(*ParserResult)->ID_Type = CMMSObject::IDT_OnlyTextual;
	delete yyvsp[-1].pList;
;}
    break;

  case 6:
#line 82 "..\\MainMetadataStream.y"
    {
	*ParserResult = (CMMSObject*) new CMMSObjectWithProps(yyvsp[-4].String, CString(""), yyvsp[-2].pList);
	(*ParserResult)->ID_Type = CMMSObject::IDT_OnlyTextual;
	delete yyvsp[-2].pList;
	fprintf(stderr, "\t(thrash after end of dialog form)\n");
;}
    break;

  case 9:
#line 93 "..\\MainMetadataStream.y"
    {
	yyval.pList = new CMMSNodeList;
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 10:
#line 98 "..\\MainMetadataStream.y"
    {
	yyval = yyvsp[-2];
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 11:
#line 104 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSObjectWithProps(yyvsp[-2].String, CString(""), yyvsp[-1].pList);
	yyval.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
	if( yyvsp[-1].pList!= NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 12:
#line 110 "..\\MainMetadataStream.y"
    {
	yyval.pNode = new CMMSObject(CString(), yyvsp[-1].String);
	yyval.pNode->ID_Type = CMMSObject::IDT_OnlyNumeric;
;}
    break;

  case 13:
#line 115 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSObjectWithProps(yyvsp[-2].String, yyvsp[-4].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 14:
#line 120 "..\\MainMetadataStream.y"
    {
	if( yyvsp[-1].pList == NULL ) yyvsp[-1].pList = new CMMSNodeList;
	yyvsp[-1].pList->AddHead(yyvsp[-2].pNode);
	yyval.pNode = (CMMSObject*) new CMMSObjectWithProps(CString(""), yyvsp[-4].String, yyvsp[-1].pList);
	yyval.pNode->ID_Type = CMMSObject::IDT_OnlyNumeric;
	delete yyvsp[-1].pList;
;}
    break;

  case 15:
#line 128 "..\\MainMetadataStream.y"
    {
	if( yyvsp[-1].pList == NULL )
		yyval.pNode = (CMMSObject*)new CMMSObject;
	else
	{
		yyval.pNode = (CMMSObject*) new CMMSObjectWithProps(yyvsp[-1].pList);
		delete yyvsp[-1].pList;
	}
;}
    break;

  case 16:
#line 142 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSDescr(yyvsp[-7].String, yyvsp[-5].String, yyvsp[-3].String, yyvsp[-1].String);
;}
    break;

  case 17:
#line 147 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_TaskItem, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
	yyval.pNode->GetPropByNum(0)->Type = MMS_TaskItemDescr;
;}
    break;

  case 18:
#line 154 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_Consts, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 19:
#line 160 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSSbCnts(yyvsp[-1].String, NULL);
;}
    break;

  case 20:
#line 164 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSSbCnts(yyvsp[-3].String, yyvsp[-1].pList);
	delete yyvsp[-1].pList;
;}
    break;

  case 21:
#line 170 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_GenJrnlFldDef, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 22:
#line 176 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_DocSelRefObj, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 23:
#line 182 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_DocNumDef, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 24:
#line 188 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSDocuments(yyvsp[-1].String, NULL);
;}
    break;

  case 25:
#line 192 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSDocuments(yyvsp[-3].String, yyvsp[-1].pList);
	delete yyvsp[-1].pList;
;}
    break;

  case 26:
#line 198 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSRegisters(MMS_Registers, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 27:
#line 204 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_DocumentStreams, yyvsp[-1].String, NULL);
	yyval.pNode->Type = MMS_DocumentStreams;
;}
    break;

  case 28:
#line 209 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_DocumentStreams, yyvsp[-3].String, yyvsp[-1].pList);
	delete yyvsp[-1].pList;
;}
    break;

  case 29:
#line 215 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSReportList(yyvsp[-1].String, NULL);
;}
    break;

  case 30:
#line 219 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSReportList(yyvsp[-3].String, yyvsp[-1].pList);
	delete yyvsp[-1].pList;
;}
    break;

  case 31:
#line 225 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSJournalisters(yyvsp[-1].String, NULL);
;}
    break;

  case 32:
#line 229 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSJournalisters(yyvsp[-3].String, yyvsp[-1].pList);
	delete yyvsp[-1].pList;
;}
    break;

  case 33:
#line 235 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSEnums(MMS_EnumList, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 34:
#line 241 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSCalcJournals(yyvsp[-1].String, NULL);
;}
    break;

  case 35:
#line 245 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSCalcJournals(yyvsp[-3].String, yyvsp[-1].pList);
	delete yyvsp[-1].pList;
;}
    break;

  case 36:
#line 251 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_Calendars, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 37:
#line 257 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSCaclAlgorithms(yyvsp[-1].String, NULL);
;}
    break;

  case 38:
#line 261 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSCaclAlgorithms(yyvsp[-3].String, yyvsp[-1].pList);
	delete yyvsp[-1].pList;
;}
    break;

  case 39:
#line 267 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_RecalcRules, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 40:
#line 273 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_Groups, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 41:
#line 279 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSObject(yyvsp[-1].String, yyvsp[-1].String);
	yyval.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
;}
    break;

  case 42:
#line 284 "..\\MainMetadataStream.y"
    {
	yyval.pNode = yyvsp[-2].pNode;
	yyval.pNode->sID = yyvsp[-5].String;
;}
    break;

  case 43:
#line 294 "..\\MainMetadataStream.y"
    {
	yyval.pList = new CMMSNodeList;
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 44:
#line 299 "..\\MainMetadataStream.y"
    {
	yyval = yyvsp[-2];
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 45:
#line 305 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSSbCnt(
		yyvsp[-7].String, 
		yyvsp[-9].String, 
		yyvsp[-5].String, 
		yyvsp[-3].String,
		yyvsp[-1].pList);
	delete yyvsp[-1].pList;
;}
    break;

  case 46:
#line 319 "..\\MainMetadataStream.y"
    {
	yyval.pList = new CMMSNodeList;
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 47:
#line 324 "..\\MainMetadataStream.y"
    {
	yyval = yyvsp[-2];
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 48:
#line 330 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSDocument(
		yyvsp[-7].String, 
		yyvsp[-9].String, 
		yyvsp[-5].String, 
		yyvsp[-3].String,
		yyvsp[-1].pList);
	delete yyvsp[-1].pList;
;}
    break;

  case 49:
#line 344 "..\\MainMetadataStream.y"
    {
	yyval.pList = new CMMSNodeList;
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 50:
#line 349 "..\\MainMetadataStream.y"
    {
	yyval = yyvsp[-2];
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 51:
#line 355 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSDocStream(yyvsp[-13].String, yyvsp[-15].String, 
		yyvsp[-11].String, yyvsp[-9].String, 
		yyvsp[-7].String, yyvsp[-5].String,
		yyvsp[-3].pNode, yyvsp[-1].pNode);
;}
    break;

  case 52:
#line 363 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSObjectWithProps(yyvsp[-1].String, yyvsp[-1].String);
	yyval.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
;}
    break;

  case 53:
#line 368 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSObjectWithProps(yyvsp[-3].String, yyvsp[-3].String, yyvsp[-1].pList);
	yyval.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
	delete yyvsp[-1].pList;
;}
    break;

  case 54:
#line 375 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSObjectWithProps(yyvsp[-1].String, yyvsp[-1].String);
	yyval.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
;}
    break;

  case 55:
#line 380 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSObjectWithProps(yyvsp[-3].String, yyvsp[-3].String, yyvsp[-1].pList);
	yyval.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
	delete yyvsp[-1].pList;
;}
    break;

  case 56:
#line 391 "..\\MainMetadataStream.y"
    {
	yyval.pList = new CMMSNodeList;
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 58:
#line 396 "..\\MainMetadataStream.y"
    {
	yyval = yyvsp[-2];
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 59:
#line 402 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSReport(
		yyvsp[-5].String, 
		yyvsp[-7].String, 
		yyvsp[-3].String, 
		yyvsp[-1].String);
;}
    break;

  case 60:
#line 415 "..\\MainMetadataStream.y"
    {
	yyval.pList = new CMMSNodeList;
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 62:
#line 420 "..\\MainMetadataStream.y"
    {
	yyval = yyvsp[-2];
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 63:
#line 426 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSJournalister(
		yyvsp[-7].String, 
		yyvsp[-9].String, 
		yyvsp[-5].String, 
		yyvsp[-3].String,
		yyvsp[-1].pList);
	delete yyvsp[-1].pList;
;}
    break;

  case 64:
#line 440 "..\\MainMetadataStream.y"
    {
	yyval.pList = new CMMSNodeList;
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 66:
#line 445 "..\\MainMetadataStream.y"
    {
	yyval = yyvsp[-2];
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 67:
#line 451 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSCalcJournal(
		yyvsp[-7].String, 
		yyvsp[-9].String, 
		yyvsp[-5].String, 
		yyvsp[-3].String,
		yyvsp[-1].pList);
	delete yyvsp[-1].pList;
;}
    break;

  case 68:
#line 465 "..\\MainMetadataStream.y"
    {
	yyval.pList = new CMMSNodeList;
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 70:
#line 470 "..\\MainMetadataStream.y"
    {
	yyval = yyvsp[-2];
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 71:
#line 476 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSCaclAlgorithm(
		yyvsp[-7].String, 
		yyvsp[-9].String, 
		yyvsp[-5].String, 
		yyvsp[-3].String,
		yyvsp[-1].pList);
	delete yyvsp[-1].pList;
;}
    break;

  case 72:
#line 490 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSBuh(CString("Buh"), yyvsp[0].String);
;}
    break;

  case 73:
#line 494 "..\\MainMetadataStream.y"
    {
	yyval.pNode = yyvsp[-2].pNode;
	yyvsp[-2].pNode->AddProperty(yyvsp[0].pNode);
;}
    break;

  case 74:
#line 503 "..\\MainMetadataStream.y"
    {
	yyval.pNode = yyvsp[0].pNode;
;}
    break;

  case 75:
#line 507 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_AccParams, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 76:
#line 512 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSObjectWithProps(yyvsp[-1].String, CString(), NULL);
	yyval.pNode->Type = MMS_Plans;
	yyval.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
;}
    break;

  case 77:
#line 518 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSAccountPlans(yyvsp[-3].String, yyvsp[-1].pList);
	delete yyvsp[-1].pList;
;}
    break;

  case 78:
#line 523 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_ProvParams, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 79:
#line 528 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_OperParams, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 80:
#line 533 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_SbKind, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 81:
#line 538 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_TypOpersDef, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 82:
#line 543 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_CorrProvsDef, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 83:
#line 548 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_ProvHardFldDef, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 84:
#line 553 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_OperJournal, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 85:
#line 562 "..\\MainMetadataStream.y"
    {
	yyval.pList = new CMMSNodeList;
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 86:
#line 567 "..\\MainMetadataStream.y"
    {
	yyval.pList = yyvsp[-2].pList;
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 87:
#line 574 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSAccountPlan(yyvsp[-11].String, yyvsp[-13].String, yyvsp[-9].String, yyvsp[-7].String, 
		yyvsp[-5].String, yyvsp[-3].String, yyvsp[-1].pNode);
;}
    break;

  case 88:
#line 580 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSAccountPlan(yyvsp[-9].String, yyvsp[-11].String, yyvsp[-7].String, yyvsp[-5].String, 
		CString(""), yyvsp[-3].String, yyvsp[-1].pNode);
;}
    break;

  case 89:
#line 586 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSObjectWithProps(yyvsp[-1].String, CString(), NULL);
	yyval.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
;}
    break;

  case 90:
#line 591 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSObjectWithProps(yyvsp[-3].String, CString(), yyvsp[-1].pList);
	yyval.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 91:
#line 601 "..\\MainMetadataStream.y"
    {
	yyval.pList = new CMMSNodeList();
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 92:
#line 606 "..\\MainMetadataStream.y"
    {
	yyval.pList = yyvsp[-2].pList;
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 93:
#line 614 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSAccount(yyvsp[-18].String, yyvsp[-20].String, yyvsp[-16].String, yyvsp[-14].String,
		yyvsp[-12].String, yyvsp[-10].String, yyvsp[-8].String, 
		yyvsp[-6].String, yyvsp[-4].String, yyvsp[-2].String, yyvsp[-1].pList);
	if( yyvsp[-1].pList != NULL ) delete yyvsp[-1].pList;
;}
    break;

  case 94:
#line 625 "..\\MainMetadataStream.y"
    {yyval.pList = NULL;;}
    break;

  case 95:
#line 626 "..\\MainMetadataStream.y"
    {yyval.pList = yyvsp[0].pList;;}
    break;

  case 96:
#line 627 "..\\MainMetadataStream.y"
    {yyval.pList = yyvsp[0].pList;;}
    break;

  case 97:
#line 630 "..\\MainMetadataStream.y"
    {
	yyval.pList = new CMMSNodeList;
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 98:
#line 635 "..\\MainMetadataStream.y"
    {
	yyval = yyvsp[-2];
	yyval.pList->AddNode(yyvsp[0].pNode);
;}
    break;

  case 99:
#line 641 "..\\MainMetadataStream.y"
    {
	yyval.pNode = (CMMSObject*) new CMMSNode(MMS_Property, yyvsp[0].String, CString());
;}
    break;

  case 100:
#line 645 "..\\MainMetadataStream.y"
    {
	yyval = yyvsp[0];
;}
    break;


    }

/* Line 999 of yacc.c.  */
#line 2097 "..\\MainMetadataStream.tab.cpp"

  yyvsp -= yylen;
  yyssp -= yylen;


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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (File, ParserResult, yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror (File, ParserResult, "syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (File, ParserResult, "syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror (File, ParserResult, "parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 649 "..\\MainMetadataStream.y"



/* The lexical analyzer returns quoted string (without quotes) or single token.
   It skips all blanks and tabs, and returns 0 for end-of-input. 
*/

typedef struct YYLTYPE
{
	int first_line;
	int first_column;
	int last_line;
	int last_column;
} YYLTYPE;

static YYLTYPE location = {1, 1, 1, 1};
static int MMS_PropNum = 1;
static bool NoIDs = false; //В некоторых случаях нам не нужны идентификаторы в объектах

static struct{
	char* strID;
	int intID;
} MapPairs[] = {
	{"Container.Contents", TOK_ContainerContents},
	{"Dialogs", TOK_DialogForm},
	{"MainDataContDef", TOK_MainDataContDef},
	{"TaskItem", TOK_TaskItem},
	{"Consts", TOK_Consts},
	{"SbCnts", TOK_SbCnts},
	{"GenJrnlFldDef", TOK_GenJrnlFldDef},
	{"DocSelRefObj", TOK_DocSelRefObj},
	{"DocNumDef", TOK_DocNumDef},
	{"Documents", TOK_Documents},
	{"Document Streams", TOK_DocumentStreams},
	{"Registers", TOK_Registers},
	{"ReportList", TOK_ReportList},
	{"Journalisters", TOK_Journalisters},
	{"EnumList", TOK_EnumList},
	{"CJ", TOK_CalcJournals},
	{"Calendars", TOK_Calendars},
	{"Algorithms", TOK_CalcAlgorithms},
	{"RecalcRules", TOK_RecalcRules},
	{"Groups", TOK_Groups},
	{"CalcVars", TOK_ReportList},
	{"Buh", TOK_Buh},
	{"AccParams", TOK_AccParams},
	{"Plans", TOK_Plans},
	{"Accounts", TOK_Accounts},
	{"ProvParams", TOK_ProvParams},
	{"OperParams", TOK_OperParams},
	//{"Form", TOK_FormList},
	{"SbKind", TOK_SbKind},
	{"TypOpersDef", TOK_TypOpersDef},
	{"CorrProvsDef", TOK_CorrProvsDef},
	{"ProvHardFldDef", TOK_ProvHardFldDef},
	{"OperJournal", TOK_OperJournal},
	{NULL, 0}};
static CMapStringToOb Map;

static CString ParsedObject; //для сообщений об ошибках

void MMS_InitParser(CString& aParsedObject, bool ParseWitnNoIDs)
{
	ParsedObject = aParsedObject;
	NoIDs = ParseWitnNoIDs;

	location.first_line = 1;
	location.first_column = 1;
	location.last_line = 1;
	location.last_column = 1;

	if( Map.GetCount() == 0 )
	{
		for( int i = 0; MapPairs[i].strID != NULL; i++ )
			Map.SetAt(MapPairs[i].strID, (CObject*)MapPairs[i].intID);
	}
}

int GetTokenType(CString& token)
{
	char *ptr;
	CObject* token_id;

	if( MMS_PropNum > 0 ) return QUOTED_STRING;

	ptr = (LPSTR)(LPCSTR)token;
	if( Map.Lookup(ptr, token_id) ) return (int)token_id;

	if( NoIDs ) return QUOTED_STRING;

	size_t len = token.GetLength();
	if( len == 0 ) return TEXTUAL_ID;
	if( token[0] == '0' ) return TEXTUAL_ID; //числовые идентификаторы с 0 не начинаются.
	if( strspn(token, "0123456789") == len ) return NUMERIC_ID;
	return TEXTUAL_ID;
}

bool SkipSpaces(FILE* File, YYLTYPE *llocp)
{
	while( !feof(File) )
	{
		int c = fgetc(File);
		
		if( c == '\n' )
		{
			llocp->first_line++;
			llocp->first_column = 1;
			continue;
		}
		if( c != ' ' && c != '\t' && c != '\n' && c != '\r' )
		{
			ungetc(c, File);
			return true;
		}
		if( c != '\r')
		{
			llocp->first_column++;
		}
	}
	return false;
}

int MMS_lex (YYSTYPE *lvalp, FILE *File)
{
	char c;

	if( feof(File) ) return 0;
	if( !SkipSpaces(File, &location) ) return 0;

	c = fgetc(File);
	location.first_column++;

	if( c != '"' )
	{
		if( c == '{' )
			MMS_PropNum = 0;
		else
			MMS_PropNum++;
		return c;
	}
	
	CString& token = lvalp->String;
	token = "";
	int state = 0; // 0 - внутри строки; 1 - попалась кавычка
	while( !feof(File) ) 
	{
		c = fgetc(File);

		switch( state )
		{
		case 0:
			if( c == '"' )
				state = 1;
			else
				token += c;
			break;
		case 1:
			if( c == '"' )
			{
				token += "\"\""; // оставим двойную кавычку как есть - не будем менять на одну
				state = 0;
			}
			else
			{
				ungetc(c, File);
				int tok_t = GetTokenType(token);
				MMS_PropNum++;
				return tok_t;
			}
		}

		location.first_column++;
	}
		
	return 0;
}


// Called by yyparse on error.
void MMS_error (FILE *File, CMMSObject** ParserResult, char const *s)
{
	printf ("%s: %s - Line %i Column %i\n", ParsedObject, s, location.first_line, location.first_column);
}



