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

  int iVal;
  float fVal;
  char cVal;
  char* sVal;

  int bool;
  int operator;
  char *id;
}

%type <nodePtr> expression commande programme
%type <nodePtr> operation_binaire
%type <operator> op_unaire
%type <operator> assigne
%type <nodePtr> affect_expr
%type <nodePtr> expressions
%type <nodePtr> arguments

%token <iVal> NOMBRE
%token <bool> BOOLEEN
%token <sVal> IDENT
%token <sVal> STRING

%token <operator> '+' '-'
%token <operator> '*' '/'
%token <operator> '!'
%token <operator> '%'
%token <operator> '>'
%token <operator> '<'
%token <operator> EST_INFERIEUR_OU_EGAL_A
%token <operator> EST_EGAL_A
%token <operator> EST_SUPERIEUR_OU_EGAL_A
%token <operator> ET
%token <operator> OU
%token <operator> EST_DIFFERENT_DE
%token <operator> PUISSANCE
%token <operator> TYPEOF

%token <operator> PLUS_EGAL
%token <operator> FOIS_EGAL
%token <operator> MOINS_EGAL
%token <operator> DIV_EGAL
%token <operator> MOD_EGAL
%token <operator> PUISSANCE_EGAL

%token SI
%token SINON
%token TANT_QUE
%token POUR
%token FAIRE
%token ECRIRE
%token RETOURNER
%token FONCTION
%token VAR

%nonassoc SANS_SINON
%nonassoc SINON

%left ','
%right ASSIGNE
%right '?' ':'
%left OU
%left ET
%left EST_EGAL_A                  EST_DIFFERENT_DE
%left EST_SUPERIEUR_OU_EGAL_A     EST_INFERIEUR_OU_EGAL_A
%left PLUS
%left '+' '-'
%left '*' '/' '%'
%right TYPEOF	'!' UNAIRE

%%

resultat:
    programme                                                         {*root = *$1;}
  ;

programme:
    commande                                                          {$$ = newAST($1,NULL);}
  | commande programme                                                {$$ = newAST($1,$2);}
  ;

commande:
   ';'                                                                {$$ = newOperation(';',0);}
  |'{' programme '}'                                                  {$$ = $2;}
  | affect_expr ';'                                                   {$$ = $1;}
  | FONCTION IDENT '(' arguments ')' '{' programme '}'                {$$ = newOperation(FONCTION,3,$2,$4,$7);}
  | SI '(' expression ')' commande    %prec SANS_SINON                {$$ = newOperation(SI,2,$3,$5);}
  | SI '(' expression ')' commande SINON commande                     {$$ = newOperation(SINON,3,$3,$5,$7);}
  | BREAK                                                             {$$ = newIdent($1);}
  | TANT_QUE '(' expression ')' commande                              {$$ = newOperation(TANT_QUE,2,$3,$5);}
  | FAIRE commande TANT_QUE '(' expression ')'                        {$$ = newOperation(FAIRE,2,$2,$5);}
  | RETOURNER '(' expression ')' ';'                                  {$$ = newOperation(RETOURNER,1,$3);}
  | POUR '(' affect_expr ';' expression ';' expression ')' commande   {$$ = newOperation(POUR,4,$3,$5,$7,$9);}
/*| ECRIRE '(' expression ')' ';'                                     {$$ = newOperation(ECRIRE,1,$3);}*/
  ;

affect_expr:
    expression                                                        {$$ = $1;}
  | VAR IDENT '=' expression                                          {$$ = newOperation(VAR,2,newIdent($2),$4);}
  | VAR IDENT                                                         {$$ = newOperation(VAR,1,newIdent($2));}
  ;

expression:
    NOMBRE                                                            {$$ = newConst($1);}
  | BOOLEEN                                                           {$$ = newConst($1);}
  | STRING                                                            {$$ = newString($1);}
  | IDENT                                                             {$$ = newIdent($1);}
  | '(' expression ')'                                                {$$ = $2;}
  | IDENT '(' expressions ')'                                         {$$ = newOperation($1,1,$3);}
  | op_unaire expression %prec UNAIRE                                 {$$ = newOperation($1,1,$2);}
  | operation_binaire                	                                {$$ = $1;}
  | expression '?' expression ':' expression                          {$$ = newOperation('?',3,$1,$3,$5);}
  | IDENT assigne expression   %prec ASSIGNE                          {$$ = newOperation(IDENT,2,newIdent($1),$3);}
  ;

expressions:
  /* Rien */
  | expression ',' expressions
  ;

op_unaire:
    '-'								                                                {$$ = UNAIRE;}
  | '!'								                                                {$$ = '!';}
  | TYPEOF								                                            {$$ = TYPEOF;}
  ;

operation_binaire:
    expression '+' expression                                         {$$ = newOperation('+',2,$1,$3);}
  | expression '-' expression                                         {$$ = newOperation('-',2,$1,$3);}
  | expression '*' expression                                         {$$ = newOperation('*',2,$1,$3);}
  | expression '/' expression                                         {$$ = newOperation('/',2,$1,$3);}
  | expression '%' expression                                         {$$ = newOperation('%',2,$1,$3);}
  | expression EST_EGAL_A expression                                  {$$ = newOperation(EST_EGAL_A,2,$1,$3);}
  | expression '>' expression                                         {$$ = newOperation('>',2,$1,$3);}
  | expression '<' expression                                         {$$ = newOperation('<',2,$1,$3);}
  | expression EST_DIFFERENT_DE expression                            {$$ = newOperation(EST_DIFFERENT_DE,2,$1,$3);}
  | expression ET expression                                          {$$ = newOperation(ET,2,$1,$3);}
  | expression OU expression                                          {$$ = newOperation(OU,2,$1,$3);}
  | expression PUISSANCE expression                                   {$$ = newOperation(PUISSANCE,2,$1,$3);}
  | expression EST_SUPERIEUR_OU_EGAL_A expression                     {$$ = newOperation(EST_SUPERIEUR_OU_EGAL_A,2,$1,$3);}
  | expression EST_INFERIEUR_OU_EGAL_A expression                     {$$ = newOperation(EST_INFERIEUR_OU_EGAL_A,2,$1,$3);}
  ;

assigne:
    '='								                                                {$$ = '=';}
  | PLUS_EGAL                                                         {$$ = PLUS_EGAL;}
  | FOIS_EGAL                                                         {$$ = FOIS_EGAL;}
  | MOINS_EGAL                                                        {$$ = MOINS_EGAL;}
  | DIV_EGAL                                                          {$$ = DIV_EGAL;}
  | MOD_EGAL                                                          {$$ = MOD_EGAL;}
  | PUISSANCE_EGAL                                                    {$$ = PUISSANCE_EGAL;}
  ;

  ;

arguments:
  /* Rien */
  | IDENT                                                             {$$ = newIdent($1);}
  | IDENT ',' arguments                                               {$$ = newOperation(',',2,$1,$3);}
  | IDENT '=' expression                                              {$$ = newOperation('=',2,$1,$3);}
  | IDENT '=' expression ',' arguments                                {$$ = newOperation(',',3,$1,$3,$5);}
  ;


%%

#include <string.h>

int yyerror(Node* root, const char *s){
  extern int yylineno;
  fprintf(stderr, "Erreur de syntaxe ligne %d : %s\n", yylineno, s);
  return 0;
}
