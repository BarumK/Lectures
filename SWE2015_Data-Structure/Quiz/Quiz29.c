#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
    int data;
    treePointer leftChild, rightChild;
} node;

int treeAdd(treePointer tree);

int main()
{
    treePointer root = (treePointer) malloc(sizeof(node));
    treePointer node2 = (treePointer) malloc(sizeof(node));
    treePointer node3 = (treePointer) malloc(sizeof(node));
    treePointer node4 = (treePointer) malloc(sizeof(node));

    root->data = 1;
    node2->data = 2;
    node3->data = 3;
    node4->data = 4;

    root->leftChild = node2;
    root->rightChild = node3;
    node2->leftChild = NULL;
    node2->rightChild = node4;
    node3->leftChild = NULL;
    node3->rightChild = NULL;
    node4->leftChild = NULL;
    node4->rightChild = NULL;
    
    printf("Binary Tree Structure:\n");
    printf("    1\n   / \\\n  2   3\n   \\\n    4\n");
    printf("Sum: %d\n", treeAdd(root));
    
    return 0;
}


int treeAdd(treePointer tree) {
    int left, right;
    if (tree) {
        left = treeAdd(tree->leftChild);
        right = treeAdd(tree->rightChild);
        return left + right + tree->data;
    }
    return 0;
}