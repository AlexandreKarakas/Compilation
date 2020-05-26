#include <stdlib.h>
#include <stdarg.h>
#include "ast.h"

Node* newOperation(int type, int nops, ...){
  Node* node;
  va_list ap;

  if(!(node = (Node*) malloc(sizeof(Node)))) return NULL;

  node->type = OPER_NODE;
  node->oper.type = type;
  node->oper.nops = nops;

  va_start(ap, nops);
  for(int i=0;i<nops;i++){
    node->oper.childs[i] = va_arg(ap, Node*);
  }
  va_end(ap);

  return node;
}

Node* newConst(int n){
  Node* node;
  if(!(node = (Node*) malloc(sizeof(Node)))) return NULL;

  node->type = CONST_NODE;
  node->cst.value = n;

  return node;
}

Node* newIdent(char* id){
  Node* node;
  if(!(node = (Node*) malloc(sizeof(Node)))) return NULL;

  node->type = ID_NODE;
  node->id.name = id;

  return node;
}










/*
struct ExpressionA {
  struct ExpressionA* left;    // null si nombre
  struct ExpressionA* middle;  // null si nombre
  struct ExpressionA* right;   // null si nombre ou neg
  char sym[6];                 // '+', '-', '/' ou '*' , quelconque si terme
  int val;                     // quelconque si <> nombre
  char id[24];
  int taille;                  // taille du noeud
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
*/