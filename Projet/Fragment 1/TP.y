%define parse.error verbose

%{
#include "AST.c"
#include <string.h>

int yyerror(const char*);
extern int yylineno;



%}

%parse-param {struct Programme* ast}

%union {
  struct Node* nodePtr;
  int num;
  int bool;
  char *id;
}

%type <expA> expression
%type <expA> commande
%type programme

%token <num> NOMBRE
%token <bool> BOOLEEN
%token <operator> EST_INFERIEUR_OU_EGAL_A
%token <operator> EST_EGAL_A
%token <operator> EST_SUPERIEUR_OU_EGAL_A
%token <operator> ET
%token <operator> OU
%token <operator> EST_DIFFERENT_DE
%token <operator> PUISSANCE
%token <operator> TYPEOF
%token <expA> IDENT
%token <expA> SI
%token <expA> SINON
%token <expA> TANT_QUE
%token <expA> POUR
%token <expA> FAIRE
%token <expA> ECRIRE

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

programme :
    commande
  | commande programme
  ;

commande :
   ';'
  |'{' programme '}'
  | expression ';'
  | SI '(' expression ')' commande                                    {$$ = newSi($3,$5);}
  | SI '(' expression ')' commande SINON commande                     {$$ = newSiSinon($3,$5,$7);}
  | TANT_QUE '(' expression ')' commande                              {$$ = newTantQue($3,$5);}
  | FAIRE commande TANT_QUE '(' expression ')'                        {$$ = newFaireTq($2,$5);}
  | POUR '(' expression ';' expression ';' expression ')' commande    {$$ = newPour($3,$5,$7,$9);}
  | ECRIRE '(' expression ')' ';'                                     {$$ = newEcrire($3);}
  ;

expression:
    NOMBRE                                          {$$ = newExpression("0",NULL,NULL,$1);}
  | BOOLEEN                                         {if ($$ == 1) $$ = newExpression("Vrai",NULL,NULL,$1); else $$ = newExpression("Faux", NULL, NULL, $1);}
  | IDENT                                           {$$ = newExpression2("id", NULL, NULL, NULL, NULL, $1);}
  | '(' expression ')'                              {$$ = $2;}
  | op_unaire expression %prec UNAIRE
  | expression op_binaire expression
  | expression '?' expression ':' expression        {$$ = newExpression1("?:",$1,$3,$5,0);}
  | '-' expression %prec MOINSU                     {$$ = newExpression("-",newExpression("0",NULL,NULL,0),$2,0);}
  | IDENT '=' expression                            {$$ = newExpression("=",newExpression2("id", NULL, NULL, NULL, NULL, $1),$3,0);}
  ;

op_unaire: '-' | '!' | TYPEOF;

op_binaire: '+' | '-' | '*' | '/' | '%' | EST_EGAL_A | '>' | '<' | EST_DIFFERENT_DE | ET | OU | PUISSANCE | EST_SUPERIEUR_OU_EGAL_A | EST_INFERIEUR_OU_EGAL_A;

assigne: '=';


%%

#include <string.h>

int yyerror(const char *s){
  extern int yylineno;
  fprintf(stderr, "Erreur de syntaxe ligne %d : %s\n", yylineno, s);
  return 0;
}
