
#include<stdlib.h>



struct ExpressionA {
  char sym;                    /* '+', '-', '/' ou '*' , quelconque si terme*/
  struct ExpressionA* left;    /* null si nombre */
  struct ExpressionA* middle;  /* null si nombre */
  struct ExpressionA* right;   /* null si nombre ou neg */
  int val;                     /* quelconque si <> nombre */
  int taille;                  /* taille du noeud */
};


struct Commande {
  struct ExpressionA exp;
};

struct Programme {
  struct Commande *cmd;
};