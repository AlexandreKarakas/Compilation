#ifndef AST_H_
#define AST_H_

/* ----- NODE TYPES ----- */

typedef enum Node_type{
    CONST_NODE, ID_NODE, OPER_NODE
} Node_type;

typedef struct {
    int value;
} Const_node;

typedef struct {
    char* name;
} ID_node;

typedef struct {
    int type;
    int nops;
    struct Node* childs[4];
} Oper_node;

typedef struct Node Node;
struct Node{
  Node_type type; // Type du noeud (ex : IF)

  union {
    Const_node cst;
    ID_node id;
    Oper_node oper;
  };
};

Node* newOperation(int, int, ...);
Node* newConst(int);
Node* newIdent(char*);

#endif /* AST_H_ */
