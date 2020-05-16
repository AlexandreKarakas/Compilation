
#include<stdlib.h>



struct ExpressionA {
  char sym[6];                    /* '+', '-', '/' ou '*' , quelconque si terme*/
  struct ExpressionA* left;    /* null si nombre */
  struct ExpressionA* middle;  /* null si nombre */
  struct ExpressionA* right;   /* null si nombre ou neg */
  int val;                     /* quelconque si <> nombre */
  char id[24];
  int taille;                  /* taille du noeud */
};


struct Commande {
  struct ExpressionA *exp;
};

typedef struct Programme Programme;
struct Programme {
  struct Commande *cmd;
  Programme *suivant;
};