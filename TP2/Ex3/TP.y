
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

struct Commande* newCommand(char *sym, struct ExpressionA* left, struct ExpressionA* middle, struct ExpressionA* right, int val, char *ident){
  struct Commande* cmd = (struct Commande*)malloc(sizeof(struct Commande));
  if(cmd){
    strcpy(cmd->exp->sym, sym);
    cmd->exp->left = left;
    cmd->exp->middle = middle;
    cmd->exp->right = right;
    cmd->exp->val = val;
    strcpy(cmd->exp->id, ident);
  }
  return cmd;
}

struct ExpressionA* commande (struct Commande * a){
  return a->exp;
}

Programme * newProgramme(char * sym, struct ExpressionA* left, struct ExpressionA* middle, struct ExpressionA* right, int val, char* ident){
  Programme * prg =(Programme *)malloc(sizeof( Programme *));
  prg->cmd = newCommand(sym, left, middle, right, val, ident);
  prg->suivant = NULL;
}
%}

%parse-param {struct ExpressionA* ast}

%union {
  struct ExpressionA* expA;
  int num;
  int bl;
  char *id;
}

%type <expA> expression
%type <expA> commande

%token <num> NOMBRE
%token <bl> BOOLEEN
%token <infE> EST_INFERIEUR_OU_EGAL_A
%token <eq> EST_EGAL_A
%token <id> IDENT
%token <supE> EST_SUPERIEUR_OU_EGAL_A
%token <and> ET
%token <or> OU
%token <diff> EST_DIFFERENT_DE
%token <pow> PUISSANCE
%token <expA> SI
%token <sinon> SINON
%token <expA> TANT_QUE
%token <expA> POUR
%token <expA> FAIRE
%token <expA> ECRIRE
%token <comment> COMMENTAIRE_UNILIGNE
%token <comment> DEB_COMMENTAIRE_MULTILIGNE
%token <comment> FIN_COMMENTAIRE_MULTILIGNE


%right '?' ':'
%left OU
%left ET
%left EST_EGAL_A                  EST_DIFFERENT_DE
%left EST_SUPERIEUR_OU_EGAL_A     EST_INFERIEUR_OU_EGAL_A
%left '+' '-'
%left '*' '/'
%right '='
%nonassoc MOINSU

%%

resultat:   expression           {*ast = *$1;}

programme :
   commande
  | commande programme
  ;

commande :
   ';'
  |'{' programme '}'
  | expression ';'                                                    {$$ = newExpression("exp", $1, NULL, NULL);}
  | SI '(' expression ')' commande                                    {$$ = newCommand("Si", $3, NULL, commande(newCommand("Si", $5, NULL, NULL,NULL,NULL)));}
  | SI '(' expression ')'commande SINON commande                      {$$ = newCommand("SiSinon", $3, commande($5), commande($7), NULL, NULL);}
  | TANT_QUE '(' expression ')' commande
  | FAIRE commande TANT_QUE '(' expression ')'
  | POUR '(' expression ';' expression ';' expression ')' commande
  | ECRIRE '(' expression ')' ';'
  ;

expression:
   expression '+' expression                        {$$ = newExpression("+",$1,$3,0);}
  | expression '-' expression                       {$$ = newExpression("-",$1,$3,0);}
  | expression '?' expression ':' expression        {$$ = newExpression1("?:", $1, $3, $5, 0);}
  | expression EST_EGAL_A expression                {$$ = newExpression("===",$1,$3,0);}
  | expression EST_INFERIEUR_OU_EGAL_A expression   {$$ = newExpression("<=",$1,$3,0);}
  | expression EST_SUPERIEUR_OU_EGAL_A expression   {$$ = newExpression(">=",$1,$3,0);}
  | expression ET expression                        {$$ = newExpression("&&",$1,$3,0);}
  | expression EST_DIFFERENT_DE expression          {$$ = newExpression("!==",$1,$3,0);}
  | expression '*' expression                       {$$ = newExpression("*",$1,$3,0);}
  | expression '/' expression                       {$$ = newExpression("/",$1,$3,0);}
  | expression '%' expression                       {$$ = newExpression("%",$1,$3,0);}
  | expression '>' expression                       {$$ = newExpression(">", $1,$3,0);}
  | '(' expression ')'                              {$$ = $2;}
  | '-' expression %prec MOINSU                     {$$ = newExpression("-",newExpression("0",NULL,NULL,0),$2,0);}
  | IDENT '=' expression                            {$$ = newExpression("=",newExpression2("id", NULL, NULL, NULL, NULL, $1),$3,0);}
  | NOMBRE                                          {$$ = newExpression("0",NULL,NULL,$1);}
  | BOOLEEN                                         {if ($$ == 1) $$ = newExpression("Vrai",NULL,NULL,$1); else $$ = newExpression("Faux", NULL, NULL, $1);}
  | IDENT                                           {$$ = newExpression2("id", NULL, NULL, NULL, NULL, $1);}
  ;

%%

#include <stdio.h>
#include <stdlib.h>

int yyerror(void){
  fprintf(stderr, "erreur de syntaxe\n");
  return 1;
}
