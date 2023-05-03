/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    COMMA = 258,                   /* COMMA  */
    SINGLE_QUOTES = 259,           /* SINGLE_QUOTES  */
    SEMI_COLON = 260,              /* SEMI_COLON  */
    EQUALS = 261,                  /* EQUALS  */
    BRACKET_OPEN = 262,            /* BRACKET_OPEN  */
    BRACKET_CLOSE = 263,           /* BRACKET_CLOSE  */
    CURLY_BRACE_OPEN = 264,        /* CURLY_BRACE_OPEN  */
    CURLY_BRACE_CLOSE = 265,       /* CURLY_BRACE_CLOSE  */
    BIG_BRACKET_OPEN = 266,        /* BIG_BRACKET_OPEN  */
    BIG_BRACKET_CLOSE = 267,       /* BIG_BRACKET_CLOSE  */
    CHARACTER_VALUE = 268,         /* CHARACTER_VALUE  */
    INTEGER_VALUE = 269,           /* INTEGER_VALUE  */
    FLOAT_VALUE = 270,             /* FLOAT_VALUE  */
    STRING_VALUE = 271,            /* STRING_VALUE  */
    INT = 272,                     /* INT  */
    FLOAT = 273,                   /* FLOAT  */
    STRING = 274,                  /* STRING  */
    DATA_TYPE = 275,               /* DATA_TYPE  */
    IDENTIFIER = 276,              /* IDENTIFIER  */
    ARRAY_IDENTIFIER = 277,        /* ARRAY_IDENTIFIER  */
    STRUCT = 278,                  /* STRUCT  */
    PRINT = 279,                   /* PRINT  */
    CARET = 280,                   /* CARET  */
    WHILE = 281,                   /* WHILE  */
    IF = 282,                      /* IF  */
    PLUS = 283,                    /* PLUS  */
    MINUS = 284,                   /* MINUS  */
    MUL = 285,                     /* MUL  */
    DIV = 286,                     /* DIV  */
    GE = 287,                      /* GE  */
    LE = 288,                      /* LE  */
    EQ = 289,                      /* EQ  */
    NE = 290,                      /* NE  */
    GT = 291,                      /* GT  */
    LT = 292,                      /* LT  */
    MOD = 293,                     /* MOD  */
    PRINTLN = 294,                 /* PRINTLN  */
    IFX = 295,                     /* IFX  */
    ELSE = 296,                    /* ELSE  */
    left = 297                     /* left  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define COMMA 258
#define SINGLE_QUOTES 259
#define SEMI_COLON 260
#define EQUALS 261
#define BRACKET_OPEN 262
#define BRACKET_CLOSE 263
#define CURLY_BRACE_OPEN 264
#define CURLY_BRACE_CLOSE 265
#define BIG_BRACKET_OPEN 266
#define BIG_BRACKET_CLOSE 267
#define CHARACTER_VALUE 268
#define INTEGER_VALUE 269
#define FLOAT_VALUE 270
#define STRING_VALUE 271
#define INT 272
#define FLOAT 273
#define STRING 274
#define DATA_TYPE 275
#define IDENTIFIER 276
#define ARRAY_IDENTIFIER 277
#define STRUCT 278
#define PRINT 279
#define CARET 280
#define WHILE 281
#define IF 282
#define PLUS 283
#define MINUS 284
#define MUL 285
#define DIV 286
#define GE 287
#define LE 288
#define EQ 289
#define NE 290
#define GT 291
#define LT 292
#define MOD 293
#define PRINTLN 294
#define IFX 295
#define ELSE 296
#define left 297

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 58 "syntax2.y"

  int intVal;
  char* dataType;
  char* strVal;
  float floatVal;
  char charVal;

#line 159 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
