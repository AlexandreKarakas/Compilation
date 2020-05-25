%define parse.error verbose

%{
#include "AST.c"
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
%type <operator> op_binaire
%type assigne

%token <num> NOMBRE
%token <bool> BOOLEEN
%token <id> IDENT

%token <operator> '+'
%token <operator> '-'
%token <operator> '!'
%token <operator> '*'
%token <operator> '/'
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

%token SI
%token SINON
%token TANT_QUE
%token POUR
%token FAIRE
%token ECRIRE

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

programme :
    commande            {*root = *$$;}
  | commande programme
  ;

commande :
   ';'                                                                {$$ = newOperation(';',0);}
  |'{' programme '}'                                                  {$$ = $2;}
  | expression ';'                                                    {$$ = $1;}
  | SI '(' expression ')' commande    %prec SANS_SINON                {$$ = newOperation(SI,2,$3,$5);}
  | SI '(' expression ')' commande SINON commande                     {$$ = newOperation(SI,3,$3,$5,$7);}
  | TANT_QUE '(' expression ')' commande                              {$$ = newOperation(TANT_QUE,2,$3,$5);}
  | FAIRE commande TANT_QUE '(' expression ')'                        {$$ = newOperation(FAIRE,2,$2,$5);}
  | POUR '(' expression ';' expression ';' expression ')' commande    {$$ = newOperation(POUR,4,$3,$5,$7,$9);}
  | ECRIRE '(' expression ')' ';'                                     {$$ = newOperation(ECRIRE,1,$3);}
  ;

expression:
    NOMBRE                                                            {$$ = newConst($1);}
  | BOOLEEN                                                           {$$ = newConst($1);}
  | IDENT                                                             {$$ = newIdent($1);}
  | '(' expression ')'                                                {$$ = $2;}
  | op_unaire expression %prec UNAIRE                                 {$$ = newOperation($1,1,$2);}
  | expression op_binaire expression                                  {$$ = newOperation($2,2,$1,$3);}
  | expression '?' expression ':' expression                          {$$ = newOperation('?',3,$1,$3,$5);}
  | IDENT assigne expression                                          {$$ = newOperation(IDENT,2,$1,$3);}
  ;

op_unaire: '-' | '!' | TYPEOF;

op_binaire: '+' | '-' | '*' | '/' | '%' | EST_EGAL_A | '>' | '<' | EST_DIFFERENT_DE | ET | OU | PUISSANCE | EST_SUPERIEUR_OU_EGAL_A | EST_INFERIEUR_OU_EGAL_A;

assigne: '=';


%%

#include <string.h>

int yyerror(Node* root, const char *s){
  extern int yylineno;
  fprintf(stderr, "Erreur de syntaxe ligne %d : %s\n", yylineno, s);
  return 0;
}
