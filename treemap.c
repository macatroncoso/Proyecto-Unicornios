#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;
typedef struct TreeMap TreeMap;

int isEqual(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * minimum(TreeNode * x){
    if (x == NULL) return NULL;

    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}

TreeNode * maximum(TreeNode * exe){ //This function return node with higher value from right

    while (exe->right != NULL)
    {
     exe = exe->right;
    }
    return exe;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->key = key;
    new->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    if (new == NULL) return NULL;
    new->root = new->current = NULL;
    new->lower_than = lower_than;
    return new;
}

void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if (tree == NULL) return;

    TreeNode * aux = tree->root;
    TreeNode * parent = NULL;

    while (aux != NULL) {
        parent = aux;
        if (tree->lower_than(key,aux->key)) {
            aux = aux->left;
        } else if (tree->lower_than(aux->key,key)) {
            aux = aux->right;
        } else if (isEqual(tree, key, aux->key)){
            aux = aux->right;
        } else {
        return;
        }
    }

    TreeNode * new = createTreeNode(key, value);

    new->parent = parent;

    if (parent == NULL) {
        tree->root = new;
    } else if (tree->lower_than(key,parent->key)) {
        parent->left = new;
    } else {
        parent->right = new;
    }
    tree->current = new;
}

void removeNode(TreeMap * tree, TreeNode* node) {
    //nodo hoja
    if(node->right==NULL && node->left==NULL){
        TreeNode* parent=node->parent;
        if(parent == NULL) tree->root=NULL;
        else if(parent->left==node) parent->left=NULL;
        else if(parent->right==node) parent->right=NULL;
    }else if(node->right!=NULL && node->left!=NULL){ //2 hijos
        TreeNode* aux = node->right;
        aux  = minimum(aux);
        node->key=aux->key;
        node->value=aux->value;
        removeNode(tree, aux);
        return;
    }else{ // 1 hijo
        TreeNode* parent=node->parent;
        TreeNode* child = node->right;
        if(child==NULL) child = node->left;
        child->parent = parent;
        if(parent == NULL) tree->root=child;
        else if(parent->left==node) parent->left=child;
        else if(parent->right==node) parent->right=child;
    }

    free(node);
    return;

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}


void * searchTreeMap(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL;

    TreeNode * aux = tree->root;

    while (aux != NULL) {
        if (tree->lower_than(key, aux->key)) {
            aux = aux->left;
        } else if (tree->lower_than(aux->key, key)) {
            aux = aux->right;
        }else break;
    }

    tree->current = aux;

    if (aux == NULL) return NULL;

    return (void *)aux->value;
}


void * upperBound(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL;

    TreeNode * aux = tree->root;
    TreeNode * ub_node = NULL;

    while (aux != NULL) {
        if( (ub_node==NULL || tree->lower_than(aux->key, ub_node->key)) &&
           !tree->lower_than(aux->key,key))
           ub_node=aux;

        if (tree->lower_than(key, aux->key)) {
            aux = aux->left;
        } else if (tree->lower_than(aux->key, key)) {
            aux = aux->right;
        }else break;
    }

    tree->current = ub_node;

    if (ub_node == NULL) return NULL;

    return ub_node->value;
}

void * firstTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->root == NULL) return NULL;

    TreeNode * aux = tree->root;

    tree->current = minimum(aux);

    if (tree->current == NULL) return NULL;

    return tree->current->value;
}

void * nextTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->root == NULL || tree->current == NULL) return NULL;

    if (tree->current->right != NULL) {
        TreeNode * aux = tree->current->right;

        tree->current = minimum(aux);

        return tree->current->value;
    }

    TreeNode * aux = tree->current->parent;

    while (aux != NULL && tree->current == aux->right) {
        tree->current = aux;
        aux = aux->parent;
    }

    tree->current = aux;

    if (aux == NULL) return NULL;

    return aux->value;
}

void * backTreeMap(TreeMap * tree){ //Go to the previous node with high value, next higher value after current


    if (tree == NULL || tree->root == NULL || tree->current == NULL) return NULL; //This check if there is info in map

    if (tree->current->left != NULL){   //Check if there's a current node son(left)
        TreeNode * aux= tree->current->left;

        tree->current= maximum(aux); //refresh current

        return tree->current->value; //return the maximum value in left branch
    }

    TreeNode * aux = tree->current->parent; //Aux gets the parent value

    while (aux != NULL && tree->current == aux->left){
        tree->current = aux;
        aux= aux->parent;
    }
    tree->current = aux; //refresh current to work in other functions
    if (aux == NULL ) return NULL;

    return aux->value; //Return the value found


}

void * lastTreeMap(TreeMap * tree) { //This function return the higher value (key) from tree.
    if (tree == NULL || tree->root == NULL) return NULL; //Check if there's info in tree and if root exist

    TreeNode * aux = tree->root; //Aux to save root

    tree->current = maximum(aux); //Current gets the function value

    if (tree->current == NULL) return NULL;

    return tree->current->value;
}

void imprimemeEnOrden(TreeNode * node){ //el nodo tiene que ser la raiz del arbol
     if (node == NULL) return;

     imprimemeEnOrden(node->left);

     printf("Anio: %d \t Nombre pelicula: %s \n", node->key, node->value);

     imprimemeEnOrden(node->right);
}
