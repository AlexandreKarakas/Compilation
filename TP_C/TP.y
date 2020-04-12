
%{
#include "AST.c"

struct ExpressionA* newExpression (char sym, struct ExpressionA* left, struct ExpressionA* right,int val ) {
  struct ExpressionA* rez = (struct  ExpressionA*)malloc( sizeof( struct  ExpressionA ) );
  if(rez)
    {
      rez->sym   = sym;
      rez->left  = left;
      rez->right = right;
      rez->val   = val;
    }
  return rez;
}

%}

%parse-param {struct ExpressionA* ast}

%union {
  struct ExpressionA* expA;
  int num;
}

%type <expA> expression
%type <expA> terme
%type <expA> facteur

%token <num> NOMBRE
%token <flt> FLOAT

%%
resultat:   expression           {*ast = *$1;}
expression: 
    expression '+' terme         {$$ = newExpression('+',$1,$3,0);}
  | expression '-' terme         {$$ = newExpression('-',$1,$3,0);}
  | terme                        {$$ = $1;}
  ;
terme: 
    terme '*' facteur            {$$ = newExpression('*',$1,$3,0);}
  | terme '/' facteur            {$$ = newExpression('/',$1,$3,0);}
  | facteur                      {$$ = $1;}
  ;
facteur: 
    '(' expression ')'           {$$ = $2;}
  | '-' facteur                  {$$ = newExpression('-',$2,NULL,0);}
  | NOMBRE                       {$$ = newExpression('0',NULL,NULL,$1);}
  ;
%%

#include <stdio.h>
#include <stdlib.h>

int yyerror(void)
{ fprintf(stderr, "erreur de syntaxe\n"); return 1;}

