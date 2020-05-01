/*fichier calc.c */


#include <stdio.h>
#include <stdlib.h>
#include "AST.c"


void parcours(struct ExpressionA* ast);
struct ExpressionA* parcours_taille(struct ExpressionA* ast);

int main(void)
{
	struct ExpressionA* ast = (struct  ExpressionA*)malloc( sizeof( struct  ExpressionA ) );
	ast->taille = 0;
	float val;
	yyparse(ast);
	ast = parcours_taille(ast);
	parcours(ast);
	FILE* fichier = fopen("code.jsm", "a");
	
	fprintf(stderr, "resultats: %d \n", ast->taille);
	fprintf(fichier, "Halt\n");
	fclose(fichier);

}
void parcours(struct ExpressionA* ast){
  	FILE* fichier = fopen("code.jsm", "a");
	if (fichier != NULL){
    	if (!ast) 
		  	return 0;
    	switch (ast->sym)
    	{
      		case 's' :  
			  parcours(ast->left) ; parcours(ast->right);
			  fprintf(fichier, "LowEqR\n");
			  break;
      		case '=' : 
			  parcours(ast->left); parcours(ast->right);
			  fprintf(fichier, "Equal\n");
			  break;
      		case '+' : 
			  parcours(ast->left); parcours(ast->right);
			  fprintf(fichier, "AddiRe\n");
			  break;
      		case '-' : 
			  parcours(ast->left) ; parcours(ast->right);
			  fprintf(fichier, "SubiRe\n");
			  break;
      		case '/' : 
			  parcours(ast->left) ; parcours(ast->right); 
			  fprintf(fichier, "DiviRe\n");
			  break;
      		case '*' : 
			  parcours(ast->left) ; parcours(ast->right); 
			  fprintf(fichier, "MultiRe\n");
			  break;
      		case '%' : 
			  parcours(ast->left) ; parcours(ast->right); 
			  fprintf(fichier, "Modulo\n");
			  break;
      		default : fprintf(fichier, "CstRe %d\n",  ast->val); 
    	}
		
  	}
  	else{
  		printf("Erreur de fichier\n");
  	}
	fclose(fichier);
}

struct ExpressionA* parcours_taille(struct ExpressionA* ast){
	struct ExpressionA* ast1;
	struct ExpressionA* ast2;
	if (!ast) 
		return ast;
  	switch (ast->sym)
  	{
		case 's' : 
			ast1 = parcours_taille(ast->left);  
			ast2 = parcours_taille(ast->right);
			ast->taille = ast1->taille + ast2->taille + 1;
			ast->left = ast1;
			ast->right = ast2;
			return ast;
		case '=' : 
			ast1 = parcours_taille(ast->left);  
			ast2 = parcours_taille(ast->right);
			ast->taille = ast1->taille + ast2->taille + 1;
			ast->left = ast1;
			ast->right = ast2;
			return ast;
    	case '+' : 
			ast1 = parcours_taille(ast->left); 
			ast2 = parcours_taille(ast->right);
			ast->taille = ast1->taille + ast2->taille + 1;
			ast->left = ast1;
			ast->right = ast2;
			return ast;
    	case '-' : 
			ast1 = parcours_taille(ast->left);
			ast2 = parcours_taille(ast->right);
			ast->taille = ast1->taille + ast2->taille + 1;
			ast->left = ast1;
			ast->right = ast2; 
			return ast;
    	case '/' : 
			ast1 = parcours_taille(ast->left);  
			ast2 = parcours_taille(ast->right);
			ast->taille = ast1->taille + ast2->taille + 1;
			ast->left = ast1;
			ast->right = ast2; 
			return ast;
    	case '*' : 
			ast1 = parcours_taille(ast->left);
			ast2 = parcours_taille(ast->right);
			ast->taille = ast1->taille + ast2->taille + 1;
			ast->left = ast1;
			ast->right = ast2; 
			return ast;
    	case '%' : 
			ast1 = parcours_taille(ast->left);
			ast2 = parcours_taille(ast->right);
			ast->taille = ast1->taille + ast2->taille + 1;
			ast->left = ast1;
			ast->right = ast2;
			return ast;
    	default : ast->taille = 1; return ast;
  	}
}


