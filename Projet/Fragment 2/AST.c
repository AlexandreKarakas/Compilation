#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef struct Node Node;
struct Node{
  char type[]; // Type du noeud (ex : IF) (ptet rajouter un enum pour programme/commande/expression)
  int height; // Taille du noeud
  Node* childNodes; // Liste des noeuds enfants

  union value{
    char* sVal; // A string value
    char cVal; // A char value
    int iVal; // An integer value
  };
};

Node* newNode(char* type, union value* value, ...);



Node* newNode(char** type, union value* value, ...){
  Node* node;
  va_list ap;
  size_t i, nodeSize;

  node = (Node*) malloc(sizeof(Node));
  if(!node) return NULL;

  node->type = malloc(strlen(*type)+1);
  strcpy(node->type, *type);


}











struct ExpressionA {
  struct ExpressionA* left;    /* null si nombre */
  struct ExpressionA* middle;  /* null si nombre */
  struct ExpressionA* right;   /* null si nombre ou neg */
  char sym[6];                 /* '+', '-', '/' ou '*' , quelconque si terme*/
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
  struct ExpressionA *exp;
  struct Commande *cmd1;
  struct Commande *cmd2;
};

struct TantQue {
  struct ExpressionA *exp;
  struct Commande *cmd;
};

struct FaireTq{
  struct Commande *cmd;
  struct ExpressionA *exp;
};

struct Pour{
  struct ExpressionA *exp1;
  struct ExpressionA *exp2;
  struct ExpressionA *exp3;
  struct Commande *cmd;
};

struct Ecrire{
  struct ExpressionA *exp;
};

typedef struct Programme Programme;
struct Programme {
  struct Commande *cmd;
  Programme *suivant;
};
