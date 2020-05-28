#include <stdlib.h>
#include <stdarg.h>
#include "ast.h"

Node* newAST(Node* command, Node* program){
    Node* node;
    if(!(node = (Node*) malloc(sizeof(Node)))) return NULL;

    node->type = ROOT_NODE;
    node->root.command = command;
    node->root.program = program;

    return node;
}

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
  node->cst.valueType = INT_VALUE;
  node->cst.iValue = n;

  return node;
}

Node* newString(char* string){
    Node* node;
    if(!(node = (Node*) malloc(sizeof(Node)))) return NULL;

    node->type = CONST_NODE;
    node->cst.valueType = STRING_VALUE;
    node->cst.sValue = string;

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
Node* newFunc(int nops, ){
    Node* node;
    if(!(node = (Node*) malloc(sizeof(Node)))) return NULL;

    node->type =
}*/