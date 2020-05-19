%define parse.error verbose
%{
#include "AST.c"
#include <string.h>

struct ExpressionA* newExpression1 (char *sym, struct ExpressionA* left, struct ExpressionA* middle, struct ExpressionA* right, int val ) {
  struct ExpressionA* rez = (struct  ExpressionA*)malloc( sizeof( struct  ExpressionA ) );
  if(rez)
    {
      strcpy(rez->sym, sym);
      rez->left = left;
      rez->middle = middle;
      rez->right = right;
      rez->val = val;
    }
  return rez;
}

struct ExpressionA* newExpression (char *sym, struct ExpressionA* left, struct ExpressionA* right, int val ) {
  struct ExpressionA* rez = (struct  ExpressionA*)malloc( sizeof( struct  ExpressionA ) );
  if(rez)
    {
      strcpy(rez->sym, sym);
      rez->left = left;
      rez->middle = NULL;
      rez->right = right;
      rez->val = val;
    }
  return rez;
}

struct ExpressionA* newExpression2 (char *sym, struct ExpressionA* left, struct ExpressionA* middle, struct ExpressionA* right,int val, char *ident) {
  struct ExpressionA* rez = (struct  ExpressionA*)malloc( sizeof( struct  ExpressionA ) );
  if(rez)
    {
      strcpy(rez->sym, sym);
      rez->left  = left;
      rez->middle = middle;
      rez->right = right;
      rez->val   = val;
      strcpy(rez->id, ident);
    }
  return rez;
}

struct Si*  newSi(struct ExpressionA * exp, struct Commande * cmd){
  struct Si *si =(struct Si*)malloc(sizeof(struct Si));
  if (si){
    si->exp = exp;
    si->cmd = cmd;
  }
  return si;
}

struct SiSinon * newSiSinon(struct ExpressionA * exp, struct Commande* cmd1, struct Commande *cmd2){
  struct SiSinon* siSinon = (struct SiSinon *)malloc(sizeof(struct SiSinon));
  if (siSinon){
    siSinon->exp = exp;
    siSinon->cmd1 = cmd1;
    siSinon->cmd2 = cmd2;
  }
  return siSinon;
}

struct TantQue* newTantQue(struct ExpressionA* exp, struct Commande* cmd){
  struct TantQue* tantQue = (struct TantQue *) malloc(sizeof(struct TantQue));
  if(tantQue){
    tantQue->exp = exp;
    tantQue->cmd = cmd;
  }
  return tantQue;
}

struct FaireTq* newFaireTq(struct ExpressionA* exp, struct Commande* cmd){
  struct FaireTq* faireTq = (struct FaireTq *) malloc(sizeof(struct FaireTq));
  if(faireTq){
    faireTq->exp = exp;
    faireTq->cmd = cmd;
  }
  return faireTq;
}

struct Pour* newPour(struct ExpressionA* exp1, struct ExpressionA* exp2, struct ExpressionA* exp3, struct Commande* cmd){
  struct Pour* pour = (struct Pour *) malloc(sizeof(struct Pour));
  if(pour){
    pour->exp1 = exp1;
    pour->exp2 = exp2;
    pour->exp3 = exp3;
    pour->cmd = cmd;
  }
  return pour;
}

struct Ecrire* newEcrire(struct ExpressionA* exp){
  struct Ecrire* ecrire = (struct Ecrire *) malloc(sizeof(struct Ecrire));
  if(ecrire){
    ecrire->exp = exp;
  }
  return ecrire;
}

%}

%parse-param {struct ExpressionA* ast}

%union {
  struct ExpressionA* expA;
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
%token <expA> IDENT
%token <expA> SI
%token <expA> SINON
%token <expA> TANT_QUE
%token <expA> POUR
%token <expA> FAIRE
%token <expA> ECRIRE
%token <expA> COMMENTAIRE_UNILIGNE
%token <expA> DEB_COMMENTAIRE_MULTILIGNE
%token <expA> FIN_COMMENTAIRE_MULTILIGNE

%right '='
%right '?' ':'
%left OU
%left ET
%left EST_EGAL_A                  EST_DIFFERENT_DE
%left EST_SUPERIEUR_OU_EGAL_A     EST_INFERIEUR_OU_EGAL_A
%left '+' '-'
%left '*' '/'
%nonassoc MOINSU

%%

resultat:   expression           {*ast = *$1;}

programme :
    commande
  | commande programme
  | error { printf("Erreur in programme\n");}
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
  | error { printf("Erreur in commande\n");}
  ;

expression:
    expression '+' expression                       {$$ = newExpression("+",$1,$3,0);}
  | expression '-' expression                       {$$ = newExpression("-",$1,$3,0);}
  | expression '?' expression ':' expression        {$$ = newExpression1("?:",$1,$3,$5,0);}
  | expression EST_EGAL_A expression                {$$ = newExpression("===",$1,$3,0);}
  | expression EST_DIFFERENT_DE expression          {$$ = newExpression("!==",$1,$3,0);}
  | expression EST_INFERIEUR_OU_EGAL_A expression   {$$ = newExpression("<=",$1,$3,0);}
  | expression EST_SUPERIEUR_OU_EGAL_A expression   {$$ = newExpression(">=",$1,$3,0);}
  | expression ET expression                        {$$ = newExpression("&&",$1,$3,0);}
  | expression OU expression                        {$$ = newExpression("||",$1,$3,0);}
  | expression PUISSANCE expression                 {$$ = newExpression("**",$1,$3,0);}
  | expression '*' expression                       {$$ = newExpression("*",$1,$3,0);}
  | expression '/' expression                       {$$ = newExpression("/",$1,$3,0);}
  | expression '%' expression                       {$$ = newExpression("%",$1,$3,0);}
  | expression '>' expression                       {$$ = newExpression(">",$1,$3,0);}
  | expression '<' expression                       {$$ = newExpression("<",$1,$3,0);}
  | '(' expression ')'                              {$$ = $2;}
  | '-' expression %prec MOINSU                     {$$ = newExpression("-",newExpression("0",NULL,NULL,0),$2,0);}
  | IDENT '=' expression                            {$$ = newExpression("=",newExpression2("id", NULL, NULL, NULL, NULL, $1),$3,0);}
  | NOMBRE                                          {$$ = newExpression("0",NULL,NULL,$1);}
  | BOOLEEN                                         {if ($$ == 1) $$ = newExpression("Vrai",NULL,NULL,$1); else $$ = newExpression("Faux", NULL, NULL, $1);}
  | IDENT                                           {$$ = newExpression2("id", NULL, NULL, NULL, NULL, $1);}
  | error { printf("Erreur in expression\n");}
  ;

%%

#include <stdio.h>
#include <stdlib.h>

int yyerror(char const *s){
  fprintf(stderr, "Errno: %s\n", s);
  return 1;
}
