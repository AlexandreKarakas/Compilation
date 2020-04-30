/*fichier calc.c */


#include <stdio.h>
#include <stdlib.h>
#include "AST.c"

int noeud = 0;
float parcours(struct ExpressionA* ast);
struct ExpressionA* parcours_taille(struct ExpressionA* ast);

int main(void)
{
  struct ExpressionA* ast = (struct  ExpressionA*)malloc( sizeof( struct  ExpressionA ) );
  ast->taille = 0;
  float val;
  yyparse(ast);
  val = parcours(ast);
  fprintf(stderr, "resultats: %d \n", ast->taille);

}
float parcours(struct ExpressionA* ast){
	if (!ast) 
		return 0;
  switch (ast->sym)
  {
    case 's' : return parcours(ast->left) <= parcours(ast->right);
    case '=' : parcours(ast->left) == parcours(ast->right);
    case '+' : return parcours(ast->left) + parcours(ast->right);
    case '-' : return parcours(ast->left) - parcours(ast->right);
    case '/' : return parcours(ast->left) / parcours(ast->right);
    case '*' : return parcours(ast->left) * parcours(ast->right);
    case '%' : return (float)(((int)parcours(ast->left)) % ((int)parcours(ast->right)));
    default : ast->val;
  }
  return 0;
}

struct ExpressionA* parcours_taille(struct ExpressionA* ast){
	if (!ast) 
		return ast;
  switch (ast->sym)
  {
    case 's' : return parcours(ast->left) <= parcours(ast->right);
    case '=' : parcours(ast->left) == parcours(ast->right);
    case '+' : return parcours(ast->left) + parcours(ast->right);
    case '-' : return parcours(ast->left) - parcours(ast->right);
    case '/' : return parcours(ast->left) / parcours(ast->right);
    case '*' : return parcours(ast->left) * parcours(ast->right);
    case '%' : return (float)(((int)parcours(ast->left)) % ((int)parcours(ast->right)));
    default : ast->val;
  }
  return 0;
}
