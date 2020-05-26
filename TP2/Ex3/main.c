#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

FILE* output;

int yyparse();
void search(Node*);

int main(int argc, char* argv[])
{
    extern FILE* yyin;
    if(argc > 1){
        if(!(yyin = fopen(argv[1], "r"))){
            fprintf(stderr, "Impossible d'ouvrir le fichier depuis lequel lire l'expression à parser!\n");
            exit(1);
        }
    } else{
        yyin = stdin;
    }

    Node* ast = (Node*) malloc(sizeof(Node));
    yyparse(ast);

    // Si le fichier donné en lecture n'a pas pu être ouvert, on quitte le programme
    if(!(output = fopen("code.jsm", "w"))){
        fprintf(stderr, "Impossible d'ouvrir le fichier donné en lecture\n");
        exit(1);
    }

    search(ast);
    fprintf(output, "Halt\n");
    fclose(output);

    return EXIT_SUCCESS;


/*

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
	print2D(ast);*/
}

void search(Node* ast){
    if(!ast) return;
    switch (ast->type) {
        case CONST_NODE:

    }
    fprintf(output, "TEST\n");
}
/*
void parcours(struct ExpressionA* ast){
	int taille = 0;

  if (strncmp(ast->sym, "<=", 2) == 0){
			parcours(ast->left);
			parcours(ast->right);
			fprintf(fichier, "LowEqR\n");
	}

	else if (strncmp(ast->sym, "===", 3) == 0){
			parcours(ast->left);
			parcours(ast->right);
			fprintf(fichier, "Equal\n");
	}

  else if (strncmp(ast->sym, "+", 1) == 0){
			parcours(ast->left);
			parcours(ast->right);
			fprintf(fichier, "AddiRe\n");
	}

	else if (strncmp(ast->sym, "-", 1) == 0){
			parcours(ast->left);
			parcours(ast->right);
			fprintf(fichier, "SubsRe\n");
	}

	else if (strncmp(ast->sym, "/", 1) == 0){
			parcours(ast->left);
			parcours(ast->right);
			fprintf(fichier, "DiviRe\n");
	}

	else if (strncmp(ast->sym, "*", 1) == 0){
			parcours(ast->left);
			parcours(ast->right);
			fprintf(fichier, "MultiRe\n");
	}

	else if (strncmp(ast->sym, "%", 1)== 0){
			parcours(ast->left);
			parcours(ast->right);
			fprintf(fichier, "Modulo\n");
	}

	else if (strncmp(ast->sym,"?:", 2) == 0){
			taille =  ast->middle->taille;
			parcours(ast->left);
			fprintf(fichier, "ConJmp %d\n", taille+1);
			taille = ast->right->taille;
			parcours(ast->middle);
			fprintf(fichier, "Jump %d\n", taille);
			parcours(ast->right);
	}

	else if (strncmp(ast->sym, "=", 1) == 0){
			parcours(ast->right);
			fprintf(fichier, "SetVar ");
			parcours(ast->left);
	}
*/
/*else if (strncmp(ast->sym, "&&", 2) == 0){
        parcours(ast->left);
        parcours(ast->right);
        fprintf(fichier, "MultiRe\n");
}*/
/*
	else if (strncmp(ast->sym, "!==", 3) == 0){
			parcours(ast->left);
			parcours(ast->right);
			fprintf(fichier, "NotEq\n");
	}

	else if (strncmp(ast->sym, ">=", 2) == 0){
			parcours(ast->left);
			parcours(ast->right);
			fprintf(fichier, "GreEqR\n");
	}

  else{
			if (strncmp(ast->sym, "0", 1) == 0 || strncmp(ast->sym, "Vrai", 4) == 0 || strncmp(ast->sym, "Faux", 4) == 0)
				fprintf(fichier, "CstRe %d\n",  ast->val);
			else if (strncmp(ast->sym, "id", 2) == 0)
				fprintf(fichier, "%s\n", ast->id);
  }

}

struct ExpressionA* parcours_taille(struct ExpressionA* ast){
	struct ExpressionA* ast1;
	struct ExpressionA* ast2;
	struct ExpressionA* ast3;

	if (!ast)
		return ast;

  	if (strncmp(ast->sym, "<=",2) == 0 || strncmp(ast->sym, "===", 3) == 0 || strncmp(ast->sym, "+", 1) == 0 || strncmp(ast->sym, "-", 1) == 0 || strncmp(ast->sym, "/", 1) == 0 || strncmp(ast->sym, "*", 1) == 0 || strncmp(ast->sym, "%", 1)== 0 ||
	  strncmp(ast->sym, ">=", 2) == 0 || strncmp(ast->sym, "!==", 3) == 0 || strncmp(ast->sym, "=", 1) == 0) {
		ast1 = parcours_taille(ast->left);
		ast2 = parcours_taille(ast->right);
		ast->taille = ast1->taille + ast2->taille + 1;
		ast->left = ast1;
		ast->right = ast2;
	}
	else if (strncmp(ast->sym,"?:", 2) == 0){
		ast1 = parcours_taille(ast->left);
		ast2 = parcours_taille(ast->right);
		ast3 = parcours_taille(ast->middle);
		ast->taille = ast1->taille + ast2->taille + ast3->taille + 2;
		ast->left = ast1;
		ast->right = ast2;
		ast->middle = ast3;
	}
    else{
		ast->taille = 1;
  	}
	return ast;
}*/
