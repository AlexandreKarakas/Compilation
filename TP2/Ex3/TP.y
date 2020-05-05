
%{
#include "AST.c"

struct ExpressionA* newExpression (char sym, struct ExpressionA* left, struct ExpressionA* middle, struct ExpressionA* right,int val ) {
  struct ExpressionA* rez = (struct  ExpressionA*)malloc( sizeof( struct  ExpressionA ) );
  if(rez)
    {
      rez->sym   = sym;
      rez->left  = left;
      rez->middle = middle;
      rez->right = right;
      rez->val   = val;
    }
  return rez;
}

struct Commande* newCommand(char sym, struct ExpressionA* left, struct ExpressionA* middle, struct ExpressionA* right, int val ){
  struct Commande* cmd = (struct Commande*)malloc(sizeof(struct Commande));
  if(cmd){
    cmd->exp.sym = sym;
    cmd->exp.left = left;
    cmd->exp.middle = middle;
    cmd->exp.right = right;
    cmd->exp.val = val;
  }
  return cmd;
}

%}

%parse-param {struct ExpressionA* ast}

%union {
  struct ExpressionA* expA;
  int num;
  int bl;
}

%type <expA> expression

%token <num> NOMBRE
%token <bl> BOOLEAN
%token <supE> supEgal
%token <eq> Equals
%token <id> IDENT

%right Equals supEgal
%left '+' '-'
%left '*' '/'
%left '?' ':' 
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
   expression '+' expression    {$$ = newExpression('+',$1,NULL,$3,0);}
  | expression '-' expression    {$$ = newExpression('-',$1,NULL,$3,0);}
  | expression '?' expression ':' expression {$$ = newExpression('?', $1, $3, $5, 0);}
  | expression Equals expression {$$ = newExpression('=',$1,NULL,$3,0);}
  | expression supEgal expression{$$ = newExpression('s',$1,NULL,$3,0);}
  | expression '*' expression    {$$ = newExpression('*',$1,NULL,$3,0);}
  | expression '/' expression    {$$ = newExpression('/',$1,NULL,$3,0);}
  | expression '%' expression    {$$ = newExpression('%',$1,NULL,$3,0);}
  | '(' expression ')'           {$$ = $2;}
  | '-' expression %prec MOINSU  {$$ = newExpression('-',$2,NULL,NULL,0);}
  | NOMBRE                       {$$ = newExpression('0',NULL,NULL,NULL,$1);}
  | BOOLEAN                      {if ($1 == 1) $$ = newExpression('V',NULL,NULL,NULL,$1); else $$ = newExpression('F', NULL,NULL, NULL, $1);}
  ;

%%

#include <stdio.h>
#include <stdlib.h>

int yyerror(void)
{ fprintf(stderr, "erreur de syntaxe\n"); return 1;}

