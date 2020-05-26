%define parse.error verbose

%{
#include "ast.c"
#include <string.h>

int yylex();
int yyerror(Node*, const char*);
extern int yylineno;
int yyparse();
%}

%parse-param {Node* root}

%union {
  Node* nodePtr;

  int num;
  int operator;
  int bool;
  char *id;
}

%type <nodePtr> expression commande programme
%type <operator> op_unaire
%type <operator> assigne
%type <nodePtr> affect_expr
%type <nodePtr> expressions
%type <nodePtr> arguments

%token <num> NOMBRE
%token <bool> BOOLEEN
%token <id> IDENT

%token <operator> '!'
%token <operator> '%'
%token <operator> '>'
%token <operator> '<'
%token <operator> EST_INFERIEUR_OU_EGAL_A
%token <operator> EST_EGAL_A
%token <operator> EST_SUPERIEUR_OU_EGAL_A
%token <operator> '+' '-'
%token <operator> '*' '/'
%token <operator> ET
%token <operator> OU
%token <operator> EST_DIFFERENT_DE
%token <operator> PUISSANCE
%token <operator> TYPEOF

%token SI
%token SINON
%token TANT_QUE
%token POUR
%token FAIRE
%token ECRIRE
%token RETOURNER
%token FONCTION
%token BREAK
%token VAR

%nonassoc SANS_SINON
%nonassoc SINON
%right '='
%right '?' ':'
%left OU
%left ET
%left EST_EGAL_A                  EST_DIFFERENT_DE
%left EST_SUPERIEUR_OU_EGAL_A     EST_INFERIEUR_OU_EGAL_A
%left '+' '-'
%left '*' '/'
%nonassoc UNAIRE

%%

programme:
    commande            {*root = *$$;}
  | commande programme
  ;

commande:
   ';'                                                                {$$ = newOperation(';',0);}
  |'{' programme '}'                                                  {$$ = $2;}
  | affect_expr ';'
  | FONCTION IDENT '(' arguments ')' '{' programme '}'
  | expression ';'                                                    {$$ = $1;}
  | VAR IDENT '(' arguments ')' '{' programme '}'
  | SI '(' expression ')' commande    %prec SANS_SINON                {$$ = newOperation(SI,2,$3,$5);}
  | SI '(' expression ')' commande SINON commande                     {$$ = newOperation(SINON,3,$3,$5,$7);}
  | BREAK
  | TANT_QUE '(' expression ')' commande                              {$$ = newOperation(TANT_QUE,2,$3,$5);}
  | FAIRE commande TANT_QUE '(' expression ')'                        {$$ = newOperation(FAIRE,2,$2,$5);}
  | RETOURNER '(' expression ')' ';'
  | POUR '(' expression ';' expression ';' expression ')' commande    {$$ = newOperation(POUR,4,$3,$5,$7,$9);}
  | ECRIRE '(' expression ')' ';'                                     {$$ = newOperation(ECRIRE,1,$3);}
  ;


affect_expr: 
  expression
  | VAR IDENT '=' expression
  | VAR IDENT
  ;

expression:
    NOMBRE                                                            {$$ = newConst($1);}
  | BOOLEEN                                                           {$$ = newConst($1);}
  | IDENT                                                             {$$ = newIdent($1);}
  | '(' expression ')'                                                {$$ = $2;}
  | op_unaire expression %prec UNAIRE                                 {$$ = newOperation($1,1,$2);}
  | expression '+' expression                                         {$$ = newOperation($2,2,$1,$3);}
  | expression '-' expression                                         {$$ = newOperation($2,2,$1,$3);}
  | expression '*' expression                                         {$$ = newOperation($2,2,$1,$3);}
  | expression '/' expression                                         {$$ = newOperation($2,2,$1,$3);}
  | expression '%' expression                                         {$$ = newOperation($2,2,$1,$3);}
  | expression EST_EGAL_A expression                                  {$$ = newOperation($2,2,$1,$3);}
  | expression '>' expression                                         {$$ = newOperation($2,2,$1,$3);}
  | expression '<' expression                                         {$$ = newOperation($2,2,$1,$3);}
  | expression EST_DIFFERENT_DE expression                            {$$ = newOperation($2,2,$1,$3);}
  | expression ET expression                                          {$$ = newOperation($2,2,$1,$3);}
  | expression OU expression                                          {$$ = newOperation($2,2,$1,$3);}
  | expression PUISSANCE expression                                   {$$ = newOperation($2,2,$1,$3);}
  | expression EST_SUPERIEUR_OU_EGAL_A expression                     {$$ = newOperation($2,2,$1,$3);}
  | expression EST_INFERIEUR_OU_EGAL_A expression                     {$$ = newOperation($2,2,$1,$3);}
  | expression '?' expression ':' expression                          {$$ = newOperation('?',3,$1,$3,$5);}
  | IDENT assigne expression                                          {$$ = newOperation(IDENT,2,$1,$3);}
  ;

expressions:

  | expression ',' expressions
  ;

op_unaire:
    '-'								{$$ = UNAIRE;}
  | '!'								{$$ = '!';}
  | TYPEOF								{$$ = TYPEOF;}
  ;

assigne: 
    '='								{$$ = '=';}
  ;

arguments:
  | IDENT
  | IDENT ',' arguments
  | IDENT '=' expression
  | IDENT '=' expression ',' arguments
  ;

%%

#include <string.h>

int yyerror(Node* root, const char *s){
  extern int yylineno;
  fprintf(stderr, "Erreur de syntaxe ligne %d : %s\n", yylineno, s);
  return 0;
}
