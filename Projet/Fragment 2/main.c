#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "parser.tab.h"

FILE* output;

void search(Node*);
void search_oper(Oper_node*);
int getSize(Node*);
Node * getSize2(Node *);
Oper_node * taille_oper(Oper_node *);

int main(int argc, char* argv[])
{
    extern FILE* yyin;
    if(argc > 1){
        if(!(yyin = fopen(argv[1], "r"))){
            fprintf(stderr, "Impossible d'ouvrir le fichier depuis lequel lire les expressions à parser!\n");
            exit(1);
        }
    } else{
        fprintf(stderr, "Merci de spécifier un fichier depuis lequel lire les expressions à parser.\n");
        exit(1);
    }

    Node* ast = (Node*) malloc(sizeof(Node));
    yyparse(ast);

    // Si le fichier donné en lecture n'a pas pu être ouvert, on quitte le programme
    if(!(output = fopen("code.jsm", "w"))){
        fprintf(stderr, "Impossible d'ouvrir le fichier donné en lecture\n");
        exit(1);
    }

    search(ast);
    fprintf(output, "Halt\n");
    fclose(output);

    return EXIT_SUCCESS;
}

void search(Node* ast){
    if(!ast) return;
    switch (ast->type) {
        case ROOT_NODE:
            search(ast->root.command);
            search(ast->root.program);
            break;
        case OPER_NODE:
            search_oper(&ast->oper);
            break;
        case CONST_NODE:
            if(ast->cst.valueType == INT_VALUE)
                fprintf(output, "CstRe %d\n",  ast->cst.iValue);
            else
                fprintf(output, "CstStr %s\n", ast->cst.sValue);
            break;
        case ID_NODE:
            fprintf(output, "GetVar %s\n", ast->id.name);
            break;
    }
}

void search_oper(Oper_node* node){
    switch (node->type) {
        case FONCTION :
            search(node->childs[0]);
            fprintf(output, "Lambda %d\n", getSize(node->childs[2]);
            search(node->childs[1]);
            search(node->childs[2]);
        break;
        case SI:
            search(node->childs[0]);
            fprintf(output, "ConJmp %d\n", getSize(node->childs[1]));
            search(node->childs[1]);
        break;
        case SINON:
        case '?':
            search(node->childs[0]);
            fprintf(output, "ConJmp %d\n", getSize(node->childs[1])+1);
            search(node->childs[1]);
            fprintf(output, "Jump %d\n", getSize(node->childs[2]));
            search(node->childs[2]);
        break;
        case TANT_QUE:
            search(node->childs[0]);
            fprintf(output, "ConJmp %d\n", getSize(node->childs[1]));
            search(node->childs[1]);
            fprintf(output, "Jump -%d\n", getSize(node->childs[0])+getSize(node->childs[1]));
        break;
        case FAIRE:
            search(node->childs[0]);
            search(node->childs[1]);
            fprintf(output, "ConJmp %d\n", 1);
            fprintf(output, "Jump -%d\n", getSize(node->childs[0])+getSize(node->childs[1])+1);
        break;
        case POUR:
            search(node->childs[0]);
            search(node->childs[1]);
            fprintf(output, "ConJmp %d\n", getSize(node->childs[2])+getSize(node->childs[3]));
            search(node->childs[2]);
            search(node->childs[3]);
            fprintf(output, "Jump -%d\n", getSize(node->childs[0])+getSize(node->childs[1])+getSize(node->childs[2])+getSize(node->childs[3])+1);
            break;
        case ECRIRE:
            search(node->childs[0]);
            fprintf(output, "Print\n");
        break;
        case UNAIRE: // Il s'agit du "-" unaire ici
            search(node->childs[0]);
            fprintf(output, "NegaRe\n");
        break;
        case IDENT:
            search(node->childs[1]);
            fprintf(output, "SetVar %s\n", node->childs[0]->id.name);
        break;
        default:
            search(node->childs[0]);
            search(node->childs[1]);
            switch (node->type) {
                case '+':
                    fprintf(output, "AddiRe\n");
                    break;
                case '-':
                    fprintf(output, "SubsRe\n");
                    break;
                case '*':
                    fprintf(output, "MultiRe\n");
                    break;
                case '/':
                    fprintf(output, "DiviRe\n");
                    break;
                case '%':
                    fprintf(output, "Modulo\n");
                    break;
                case EST_EGAL_A:
                    fprintf(output, "Equal\n");
                    break;
                case '>':
                    fprintf(output, "GreStR\n");
                    break;
                case '<':
                    fprintf(output, "LowStR\n");
                    break;
                case EST_DIFFERENT_DE:
                    fprintf(output, "NotEq\n");
                    break;
                /*case ET:
                    fprintf(output, "\n");
                    break;
                case OU:
                    fprintf(output, "\n");
                    break;
                case PUISSANCE:
                    fprintf(output, "\n");
                    break;*/
                case EST_SUPERIEUR_OU_EGAL_A:
                    fprintf(output, "GreEqR\n");
                    break;
                case EST_INFERIEUR_OU_EGAL_A:
                    fprintf(output, "LowEqR\n");
                    break;
            }
        break;
    }
}

int getSize(Node* node){
    if(node->type == OPER_NODE){
        int res = 0, nops = node->oper.nops;
        for(int i=0; i < nops; i++)
            res += getSize(node->oper.childs[i]);
        return res+nops-1;
    } else{
        return 1;
    }
}

Node * getSize2(Node* node){
    Node * node1;
    Node * node2;
    Oper_node node4;
    switch(node->type){
        case ROOT_NODE:
            node1 = getSize2(node->root.command);
            node2 = getSize2(node->root.program);
            node->taille = node1->taille + node2->taille;
            return node;
        case OPER_NODE:
            node4 = taille_oper(&node->oper);
            node->taille = node4->taille;
            return node;
        case CONST_NODE:
            node->cst.taille = 1;
            return node;
        case ID_NODE:
            node->cst.taille = 1;
            return node;
    }
}

Oper_node * taille_oper(Oper_node * node){
    Oper_node * node1;
    Oper_node * node2;
    Oper_node * node3;
    Oper_node * node4;
    switch (node->type) {
        case FONCTION :
            node1 = getSize2(node->childs[0]);
            node2 = getSize2(node->childs[1]);
            node3 = getSize2(node->childs[2]);
            node->taille = node1->taille + node2->taille + node3->taille;
            return node;
        case SI:
            node1 = getSize2(node->childs[0]);
            node2 = getSize2(node->childs[1]);
            node->taille = node1->taille + node2->taille;
            return node;
        case SINON:
        case '?':
            node1 = getSize2(node->childs[0]);
            node2 = getSize2(node->childs[1]);
            node3 = getSize2(node->childs[2]);
            node->taille = node1->taille + node2->taille + node3->taille;
            return node;
        case TANT_QUE:
            node1 = getSize2(node->childs[0]);
            node2 = getSize2(node->childs[1]);
            node->taille = node1->taille + node2->taille;
            return node;
        case FAIRE:
            node1 = getSize2(node->childs[0]);
            node2 = getSize2(node->childs[1]);
            node->taille = node1->taille + node2->taille;
            return node;
        case POUR:
            node1 = getSize2(node->childs[0]);
            node2 = getSize2(node->childs[1]);
            node3 = getSize2(node->childs[2]);
            node4 = getSize2(node->childs[3]);
            node->taille = node1->taille + node2->taille + node3->taille + node4->taille;
            return node;
        case ECRIRE:
            node1 = getSize2(node->childs[0]);
            node->taille = node1->taille;
            return node;
        case UNAIRE: // Il s'agit du "-" unaire ici
            node1 = getSize2(node->childs[0]);
            node->taille = node1->taille;
            return node;
        case IDENT:
            node1 = getSize2(node->childs[0]);
            node->taille = node1->taille;
            return node;
        default:
            node1 = getSize2(node->childs[0]);
            node2 = getSize2(node->childs[1]);
            node->taille = node1->taille + node2->taille;
            switch (node->type) {
                case '+':
                case '-':
                case '*':
                case '/':
                case '%':
                case EST_EGAL_A:
                case '>':
                case '<':
                case EST_DIFFERENT_DE:
                /*case ET:
                case OU:
                case PUISSANCE:*/
                case EST_SUPERIEUR_OU_EGAL_A:
                case EST_INFERIEUR_OU_EGAL_A:
                    node->taille = 1;
                    return node;
            }
        return node;
    }
}