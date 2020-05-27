#ifndef AST_H_
#define AST_H_

/* ----- NODE TYPES ----- */

typedef enum Node_type {
    CONST_NODE, ID_NODE, OPER_NODE, ROOT_NODE
} Node_type;

typedef enum Value_type {
    STRING_VALUE, INT_VALUE
} Value_type;

typedef struct {
    Value_type valueType;

    union{
        int iValue;
        char* sValue;
    };
} Const_node;

typedef struct {
    char* name;
} ID_node;

typedef struct {
    int type;
    int nops;
    struct Node* childs[4];
} Oper_node;

typedef struct {
    struct Node* command;
    struct Node* program;
} Root_node;

typedef struct Node Node;
struct Node {
  Node_type type; // Type du noeud (ex : IF)

  union {
    Root_node root;
    Const_node cst;
    ID_node id;
    Oper_node oper;
  };
};

Node* newRoot(Node*, Root_node*);
Node* newOperation(int, int, ...);
Node* newConst(int);
Node* newString(char*);
Node* newIdent(char*);

#endif /* AST_H_ */
