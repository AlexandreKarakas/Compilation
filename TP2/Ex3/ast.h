/* ----- NODE TYPES ----- */

typedef enum Node_type{
  BASIC_NODE,
  // Déclarations
  DECL_NODE,
  CONST_NODE,
  // Commandes
  STATEMENTS,
  IF_NODE,
  FOR_NODE,
  WHILE_NODE,
  DOWHILE_NODE,
  ASSIGN_NODE,
  SIMPLE_NODE,
  INCR_NODE,
  FUNCALL_NODE,
  // Expressions
  ARITHM_NODE,
  BOOL_NODE,
  REL_NODE,
  EQU_NODE,
  REF_NODE,
  // Fonctions
  FUNDECL_NODE,
  RETURN_NODE
} Node_type;

typedef struct Node Node;
struct Node{
  //enum Node_type type; // Type du noeud (ex : IF)
  int type;
  int height; // Taille du noeud
  Node* childs[4]; // Liste des noeuds enfants

  union Value{
    char* sVal; // A string value
    char cVal; // A char value
    int iVal; // An integer value
  } *value;
};
