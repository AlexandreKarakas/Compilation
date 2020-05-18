
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

struct Si {
  struct ExpressionA *exp;
  struct Commande * cmd;
};

struct SiSinon {
  struct Expression *exp;
  struct Commande *cmd1;
  struct Commande *cmd2;
};

struct TantQue {
  struct Expression *exp;
  struct Commande *cmd;
};

struct Faire{
  struct Commande *cmd;
  struct Expression *exp;
};

struct Pour{
  struct Expression *exp1;
  struct Expression *exp2;
  struct Expression *exp3;
  struct Commande *cmd;
};

struct Ecrire{
  struct Expression *exp;
};

typedef struct Programme Programme;
struct Programme {
  struct Commande *cmd;
  Programme *suivant;
};