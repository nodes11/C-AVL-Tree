#include "Header.h"

int main(int argc, const char * argv[]) {
    AvlTree *AVL = (AvlTree *)malloc(sizeof(AvlTree));
    
    int i = 0;
    
    srand((unsigned int)NULL);
    
    //Add 1000 random values to the tree
    for (i = 0; i < 1000; i++){
        addNode(rand()%5000, AVL);
        while(isBalanced(AVL->root) == FALSE){
            AVL -> root = BalanceTree(AVL->root);
        }
    }
    
    printf("%d",getHeight(AVL->root));
    
    return 0;
}

/*********************AVL Tree Functions**************************/

//Will create and add a node to the tree
void addNode(int value, AvlTree *AVL){
    Node *newNode = makeNode(value);
    Boolean isSet = FALSE;
    Node *temp = AVL->root;
    
    if (newNode != NULL){
        //If there is nothing in the tree (BASE CASE)
        if (AVL->root == NULL){
            AVL->root = newNode;
            AVL->treeSize++;
        }
        else{
            //Otherwise traverse the tree until we find an opening
            while (isSet == FALSE){
                //If the new node is less than the current parent, then we will traverse left
                if (newNode->value < temp->value){
                    //If the parent's leftchild is NULL, we will set it equal to the new node, otherwise move left
                    if (temp->leftChild != NULL){
                        temp = temp->leftChild;
                    }
                    else{
                        temp->leftChild = newNode;
                        isSet = TRUE;
                        AVL->treeSize++;
                    }
                }
                else{
                    if (temp->rightChild == NULL){
                        temp->rightChild = newNode;
                        isSet = TRUE;
                        AVL->treeSize++;
                    }
                    else{
                        temp = temp->rightChild;
                    }
                    
                }
            }
        }
    }
}
Node *makeNode(int value){
    Node *newNode = (Node *)malloc(sizeof(Node));
    
    if (newNode != NULL){
        newNode->value=value;
        newNode->rightChild = NULL;
        newNode->leftChild = NULL;
    }
    
    return newNode;
}

Node *BalanceTree(Node *root){
    //If the tree is empty
    if (root == NULL){
        return NULL;
    }
    
    if (getBalanceFactor(root) > 1){
        if (getBalanceFactor(root->leftChild) > 0){
            root = rightShift(root->rightChild);
            root = leftShift(root);
        }
        else{
            root = leftShift(root);
        }

    }
    else if (getBalanceFactor(root) < -1){
        if (getBalanceFactor(root->leftChild) > 0){
            root = leftShift(root->rightChild);
            root = rightShift(root);
        }
        else{
            root = rightShift(root);
        }
    }
    else{
        root->leftChild = BalanceTree(root->leftChild);
        root->rightChild = BalanceTree(root->rightChild);
    }
    
    return root;
}

//Will determine if the tree is balanced
Boolean isBalanced(Node *root){
    if ((getBalanceFactor(root) < 2 && getBalanceFactor(root) > -2) || root == NULL){
        return TRUE;
    }
    
    return FALSE;
}

//Will return the difference in height between the right hand side and the left hand side of the tree
int getBalanceFactor(Node *root){
    int right = 0,
    left = 0;
    
    if (root != NULL){
        right = getHeight(root->rightChild);
        left = getHeight(root->leftChild);
    }
    
    return right - left;
}

//Will return the height of the tree
int getHeight(Node *root){
    if (root == NULL){
        return 0;
    }
    
    int heightR = getHeight(root->rightChild);
    int heightL = getHeight(root->leftChild);
    
    //Add 1 because height starts at 1
    if (heightR > heightL){
        return heightR + 1;
    }
    else{
        return heightL + 1;
    }
}

//Will shift tree to rebalance
Node *rightShift(Node *root){
    Node *currentRoot = root;
    Node *newRoot = root->leftChild;
    
    currentRoot->leftChild = newRoot->rightChild;
    newRoot->rightChild = currentRoot;
    
    return newRoot;
}
Node *leftShift(Node *root){
    Node *currentRoot = root;
    Node *newRoot = root->rightChild;
    
    currentRoot->rightChild = newRoot->leftChild;
    newRoot->leftChild = currentRoot;
    
    return newRoot;
}

//Will check to see if value exists
Boolean findNode(int value, AvlTree *AVL){
    Node *temp = AVL->root;
    
    while(temp!=NULL){
        //If the new node is less than the current parent, then we will traverse left
        if (value < temp->value){
            temp = temp->rightChild;
        }
        else if (value > temp->value){
            temp = temp->rightChild;
        }
        else{
            return TRUE;
        }
    }
    
    return FALSE;
}

//Tree Traversals
void inOrderTraversal(Node *root){
    if(root != NULL){
        inOrderTraversal(root->leftChild);
        printf("%d ", root->value);
        inOrderTraversal(root->rightChild);
    }
}
void preOrderTraversal(Node *root){
    if(root != NULL){
        printf("%d ", root->value);
        preOrderTraversal(root->leftChild);
        preOrderTraversal(root->rightChild);
    }
}
void postOrderTraversal(Node *root){
    if(root != NULL){
        postOrderTraversal(root->leftChild);
        postOrderTraversal(root->rightChild);
        printf("%d ", root->value);
    }
}