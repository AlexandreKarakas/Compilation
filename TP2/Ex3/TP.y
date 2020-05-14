
%{
#include "AST.c"
#include <string.h>

struct ExpressionA* newExpression (char *sym, struct ExpressionA* left, struct ExpressionA* middle, struct ExpressionA* right,int val ) {
  struct ExpressionA* rez = (struct  ExpressionA*)malloc( sizeof( struct  ExpressionA ) );
  if(rez)
    {
      strcpy(rez->sym, sym);
      rez->left  = left;
      rez->middle = middle;
      rez->right = right;
      rez->val   = val;
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
    strcpy(cmd->exp.sym, sym);
    cmd->exp.left = left;
    cmd->exp.middle = middle;
    cmd->exp.right = right;
    cmd->exp.val = val;
    strcpy(cmd->exp.id, ident);
  }
  return cmd;
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

%token <num> NOMBRE
%token <bl> BOOLEAN
%token <infE> infEgal
%token <eq> Equals
%token <id> IDENT
%token <supE> supEgal
%token <and> Et
%token <or> Ou
%token <diff> Diff
%token <pow> pow


%left '+' '-'
%left '*' '/'
%right '?' ':' 
%precedence Equals supEgal
%nonassoc MOINSU

%%

resultat:   expression           {*ast = *$1;}

programme :
   commande
  | commande programme

commande :
   ;
  | expression;
  | IDENT '=' expression; 

expression:  
   expression '+' expression    {$$ = newExpression("+",$1,NULL,$3,0);}
  | expression '-' expression    {$$ = newExpression("-_op",$1,NULL,$3,0);}
  | expression '?' expression ':' expression {$$ = newExpression("?:", $1, $3, $5, 0);}
  | expression Equals expression {$$ = newExpression("===",$1,NULL,$3,0);}
  | expression infEgal expression{$$ = newExpression("<=",$1,NULL,$3,0);}
  | expression supEgal expression{$$ = newExpression(">=",$1,NULL,$3,0);}
  | expression Et expression     {$$ = newExpression("&&",$1,NULL,$3,0);}
  | expression Diff expression   {$$ = newExpression("!==",$1,NULL,$3,0);}
  | expression '*' expression    {$$ = newExpression("*",$1,NULL,$3,0);}
  | expression '/' expression    {$$ = newExpression("/",$1,NULL,$3,0);}
  | expression '%' expression    {$$ = newExpression("%",$1,NULL,$3,0);}
  | expression '>' expression    {$$ = newExpression(">", $1,NULL,$3,0);}
  | '(' expression ')'           {$$ = $2;}
  | '-' expression %prec MOINSU  {$$ = newExpression("-_unaire",$2,NULL,NULL,0);}
  | IDENT '=' expression         {$$ = newExpression("=",newExpression2("id", NULL, NULL, NULL, NULL, $1), NULL,$3,0);}
  | NOMBRE                       {$$ = newExpression("0",NULL,NULL,NULL,$1);}
  | BOOLEAN                      {if ($1 == 1) $$ = newExpression("Vrai",NULL,NULL,NULL,$1); else $$ = newExpression("Faux", NULL,NULL, NULL, $1);}
  | IDENT                        {$$ = newExpression2("id", NULL, NULL, NULL, NULL, $1);}
  ;

%%

#include <stdio.h>
#include <stdlib.h>

int yyerror(void)
{ fprintf(stderr, "erreur de syntaxe\n"); return 1;}

