/*fichier calc.c */


#include <stdio.h>
#include <stdlib.h>
#include "AST.c"
FILE* fichier;

void parcours(struct ExpressionA* ast);
struct ExpressionA* parcours_taille(struct ExpressionA* ast);

int main(void)
{
	struct ExpressionA* ast = (struct  ExpressionA*)malloc( sizeof( struct  ExpressionA ) );
	ast->taille = 0;
	yyparse(ast);
	ast = parcours_taille(ast);
	if((fichier = fopen("code.jsm", "w")) == NULL){
		fprintf(stderr, "Impossible d'ouvrir le fichier donné en lecture\n");
		exit(1);
	}
	if((fichier = fopen("code.jsm", "a")) != NULL){
		parcours(ast);
		fprintf(fichier, "Halt\n");
		fclose(fichier);
	}
	print2D(ast);
}

void print2DUtil(struct ExpressionA* root, int space){
	if(root == NULL) return;

	space += 10;

	print2DUtil(root->right, space);

	printf("\n");
	for(int i=10; i<space; i++)
		printf(" ");
	if(root->sym == '0')	printf("%d", root->val);
	else printf("%c", root->sym);

	if(root->middle != NULL) {
		print2DUtil(root->middle, space-1);

	}
			printf("\n");

	print2DUtil(root->left, space);
}

void print2D(struct ExpressionA* root){
	print2DUtil(root, 0);
}

void parcours(struct ExpressionA* ast){
	int taille = 0;
	if (fichier != NULL){
    	if (!ast){
				return;
			}
    	switch (ast->sym)
    	{
      	case 's' :
					parcours(ast->left);
					parcours(ast->right);
					fprintf(fichier, "LowEqR\n");
					break;
      	case '=' :
					parcours(ast->left);
					parcours(ast->right);
					fprintf(fichier, "Equal\n");
					break;
      	case '+' :
					parcours(ast->left);
					parcours(ast->right);
					fprintf(fichier, "AddiRe\n");
					break;
      	case '-' :
					parcours(ast->left);
					parcours(ast->right);
					fprintf(fichier, "SubsRe\n");
					break;
      	case '/' :
					parcours(ast->left);
					parcours(ast->right);
					fprintf(fichier, "DiviRe\n");
					break;
      	case '*' :
					parcours(ast->left);
					parcours(ast->right);
					fprintf(fichier, "MultiRe\n");
					break;
      	case '%' :
					parcours(ast->left);
					parcours(ast->right);
					fprintf(fichier, "Modulo\n");
					break;
				case '?' :
					taille =  ast->middle->taille;
					parcours(ast->left);
					fprintf(fichier, "ConJmp %d\n", taille+1);
					taille = ast->right->taille;
					parcours(ast->middle);
					fprintf(fichier, "Jump %d\n", taille);
					parcours(ast->right);
					break;
      	default :
					fprintf(fichier, "CstRe %d\n",  ast->val);
					break;
    	}

  	}
  	else{
  		printf("Erreur de fichier\n");
  	}
}

struct ExpressionA* parcours_taille(struct ExpressionA* ast){
	struct ExpressionA* ast1;
	struct ExpressionA* ast2;
	struct ExpressionA* ast3;

	if (!ast)
		return ast;

  switch (ast->sym) {
		case 's' :
		case '=' :
		case '+' :
		case '-' :
		case '/' :
		case '*' :
		case '%' :
			ast1 = parcours_taille(ast->left);
			ast2 = parcours_taille(ast->right);
			ast->taille = ast1->taille + ast2->taille + 1;
			ast->left = ast1;
			ast->right = ast2;
			return ast;
		case '?' :
			ast1 = parcours_taille(ast->left);
			ast2 = parcours_taille(ast->right);
			ast3 = parcours_taille(ast->middle);
			ast->taille = ast1->taille + ast2->taille + ast3->taille + 2;
			ast->left = ast1;
			ast->right = ast2;
			ast->middle = ast3;
			return ast;
    default :
			ast->taille = 1;
			return ast;
  	}
}
