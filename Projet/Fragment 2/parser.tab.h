/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    NOMBRE = 258,
    BOOLEEN = 259,
    IDENT = 260,
    STRING = 261,
    BREAK = 262,
    EST_INFERIEUR_OU_EGAL_A = 263,
    EST_EGAL_A = 264,
    EST_SUPERIEUR_OU_EGAL_A = 265,
    ET = 266,
    OU = 267,
    EST_DIFFERENT_DE = 268,
    PUISSANCE = 269,
    TYPEOF = 270,
    PLUS_EGAL = 271,
    FOIS_EGAL = 272,
    MOINS_EGAL = 273,
    DIV_EGAL = 274,
    MOD_EGAL = 275,
    PUISSANCE_EGAL = 276,
    SI = 277,
    SINON = 278,
    TANT_QUE = 279,
    POUR = 280,
    FAIRE = 281,
    ECRIRE = 282,
    RETOURNER = 283,
    FONCTION = 284,
    VAR = 285,
    SANS_SINON = 286,
    ASSIGNE = 287,
    BINAIRE = 288,
    PLUS = 289,
    UNAIRE = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 15 "parser.y"

  Node* nodePtr;

  int iVal;
  float fVal;
  char cVal;
  char* sVal;

  int bool;
  int operator;
  char *id;

#line 106 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (Node* root);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
