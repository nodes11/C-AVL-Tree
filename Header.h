#ifndef C_AVL_Header_h
#define C_AVL_Header_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node{
    struct node *rightChild;
    struct node *leftChild;
    
    int value;
}Node;

typedef struct avlTree{
    Node *root;
    int treeSize;
}AvlTree;

typedef enum boolean{
    TRUE, FALSE
}Boolean;

//AVL methods
void addNode(int value, AvlTree *AVL);
Node *makeNode(int value);
Node *BalanceTree(Node *root);
int getHeight(Node *root);
Boolean isBalanced(Node *root);
int getBalanceFactor(Node *root);
Node *rightShift(Node *root);
Node *leftShift(Node *root);



//Will check for value
Boolean findNode(int value, AvlTree *AVL);

//Tree traversals
void inOrderTraversal(Node *root);
void preOrderTraversal(Node *root);
void postOrderTraversal(Node *root);


#endif
