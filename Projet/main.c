#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "parser.tab.h"

FILE* output;

void search(Node*);
void search_oper(Node*);
//int getSize(Node*);
Node* setSizeForEachNode(Node*);

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

    setSizeForEachNode(ast);
    search(ast);
    fprintf(output, "Halt\n");
    fclose(output);

    return EXIT_SUCCESS;
}
/*
void declareArgs(Node* ast){
    if(!ast) return;
    switch (ast->type) {
        case ROOT_NODE:
            search(ast->root.command);
            search(ast->root.program);
            break;
        case OPER_NODE:
            if(ast->oper.type == FONCTION){
                fprintf(output, "Lambda %d\n", ast->oper.childs);
                fprintf(output, "DclArg %s\n", ast->oper.childs[0]->id.name);
                //fprintf(output, "SetVar %s\n", ast->oper.childs[1]->);
            }
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
}*/

void search(Node* ast){
    if(!ast) return;
    switch (ast->type) {
        case ROOT_NODE:
            search(ast->root.command);
            search(ast->root.program);
            break;
        case OPER_NODE:
            search_oper(ast);
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

void search_oper(Node* node1){
    Oper_node node = node1->oper;

    switch (node.type) {
        /*case BREAK:
            fprintf(output, "Jump %d\n", node1->height);
            break;
        */
        case FONCTION:
            fprintf(output, "Lambda %d\n", node.childs[2]->height);
            search(node.childs[2]);
            break;
        case SI:
            search(node.childs[0]);
            fprintf(output, "ConJmp %d\n", node.childs[1]->height-1);
            search(node.childs[1]);
        break;
        case SINON:
        case '?':
            search(node.childs[0]);
            fprintf(output, "ConJmp %d\n", node.childs[1]->height);
            search(node.childs[1]);
            fprintf(output, "Jump %d\n", node.childs[2]->height-1);
            search(node.childs[2]);
        break;
        case TANT_QUE:
            search(node.childs[0]);
            fprintf(output, "ConJmp %d\n", node.childs[1]->height);
            search(node.childs[1]);
            fprintf(output, "Jump -%d\n", node.childs[0]->height+node.childs[1]->height+1);
        break;
        case FAIRE:
            search(node.childs[0]);
            search(node.childs[1]);
            fprintf(output, "ConJmp %d\n", 1);
            fprintf(output, "Jump -%d\n", node.childs[0]->height+node.childs[1]->height+1);
        break;
        case POUR:
            search(node.childs[0]);
            search(node.childs[1]);
            fprintf(output, "ConJmp %d\n", node.childs[2]->height+node.childs[3]->height-1);
            search(node.childs[2]);
            search(node.childs[3]);
            fprintf(output, "Jump -%d\n", node1->height-node.childs[0]->height);
            break;
        case ECRIRE:
            search(node.childs[0]);
            fprintf(output, "Print\n");
        break;
        case UNAIRE: // Il s'agit du "-" unaire ici
            search(node.childs[0]);
            fprintf(output, "NegaRe\n");
        break;
        case IDENT:
            search(node.childs[1]);
            fprintf(output, "SetVar %s\n", node.childs[0]->id.name);
        break;
        default:
            search(node.childs[0]);
            search(node.childs[1]);
            switch (node.type) {
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
/*
int getSize(Node* node){
    if(node->type == OPER_NODE){
        int res = 0, nops = node->oper.nops;
        for(int i=0; i < nops; i++)
            res += getSize(node->oper.childs[i]);
        return res+nops-1;
    } else{
        return 1;
    }
}*/

Node* setSizeForEachNode(Node* node){
    if(!node) return node;
    int res=0;
    switch (node->type) {
        case ROOT_NODE:
            setSizeForEachNode(node->root.command);
            setSizeForEachNode(node->root.program);
            node->height = 0;
            break;
        case ID_NODE:
        case CONST_NODE:
            node->height = 1;
            break;
        case OPER_NODE:
            for(int i=0; i<node->oper.nops; i++){
                setSizeForEachNode(node->oper.childs[i]);
                res += node->oper.childs[i]->height;
            }
            node->height = res+1;
            break;
    }
    return node;
}