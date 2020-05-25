#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "ast.h"

Node* newOperation(int, int, ...);
Node* newConst(int);
Node* newIdent(char*);

Node* newOperation(int type, int nops, ...){
  Node* node;
  va_list ap;

  if(!(node = (Node*) malloc(sizeof(Node)))) return NULL;

  node->type = type;

  node->value = (union Value*) malloc(sizeof(union Value));
  va_start(ap, nops);
  for(int i=0;i<nops;i++){
    node->childs[i] = va_arg(ap, Node*);
  }
  va_end(ap);

  return node;
}

Node* newConst(int n){
  Node* node;
  if(!(node = (Node*) malloc(sizeof(Node)))) return NULL;

  node->type = 0;

  node->value = (union Value*) malloc(sizeof(union Value));
  node->value->iVal = n;

  return node;
}

Node* newIdent(char* id){
  Node* node;
  if(!(node = (Node*) malloc(sizeof(Node)))) return NULL;

  node->type = 1;

  node->value = (union Value*) malloc(sizeof(union Value));
  node->value->sVal = id;

  return node;
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
