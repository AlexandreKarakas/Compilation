/*fichier calc.c */


#include <stdio.h>
#include <stdlib.h>
#include "AST.c"

float parcours(struct ExpressionA* ast);

int main(void)
{
  struct ExpressionA* ast = (struct  ExpressionA*)malloc( sizeof( struct  ExpressionA ) );
  float val;
  yyparse(ast);
  val = parcours(ast);
  fprintf(stderr, "val: %lf \n", val );
}


float parcours(struct ExpressionA* ast){
	if (!ast) 
		return 0;
  switch (ast->sym)
  {
    case '+' : return parcours(ast->left) + parcours(ast->right);
    case '-' : return parcours(ast->left) - parcours(ast->right);
    case '/' : return parcours(ast->left) / parcours(ast->right);
    case '*' : return parcours(ast->left) * parcours(ast->right);
    case '%' : return (float)(((int)parcours(ast->left)) % ((int)parcours(ast->right)));
    default : return ast->val;
  }
  return 0;
}
