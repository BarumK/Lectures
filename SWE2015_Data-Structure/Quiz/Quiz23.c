#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
    int data; 
    listPointer link;
} listNode;

listPointer getNode(void);
void retNode(listPointer node);
void printNode(listPointer node);
int popNodeValue(listPointer node);
listPointer invertedCopyList(listPointer ptr);

listPointer avail = NULL;


void main(void) {
    listPointer node1, node2, temp1, temp2;

    node1 = getNode(); node1->data = 361; node1->link = NULL; temp1 = node1;
    temp2 = getNode(); temp2->data = 122; temp2->link = node1; node1 = temp2;
    temp2 = getNode(); temp2->data = 151; temp2->link = node1; node1 = temp2;
    temp2 = getNode(); temp2->data = 812; temp2->link = node1; node1 = temp2;
    temp2 = getNode(); temp2->data = 322; temp2->link = node1; node1 = temp2;
    temp2 = getNode(); temp2->data = 156; temp2->link = node1; node1 = temp2;

    node2 = invertedCopyList(node1);

    printf("node1: "); printNode(node1);
    printf("node2: "); printNode(node2);
}

listPointer getNode(void) {
    listPointer node;
    if (avail) {
        node = avail;
        avail = avail->link;
    }
    else node = (listPointer) malloc(sizeof(*node));
    return node;
}

void retNode(listPointer node) {
    node->link = avail;
    avail = node;
}

void printNode(listPointer node) {
    listPointer temp = node;
    if (!temp) printf("Node is empty\n");
    else {
        printf("%d", temp->data);
        temp = temp->link;
        while (temp) {
            printf(" -> %d", temp->data);
            temp = temp->link;
        }
        printf("\n");
    }
}

int popNodeValue(listPointer node) {
    listPointer temp = node;
    if (!temp) {
        fprintf(stderr, "Node is empty, cannot pop values");
        exit(EXIT_FAILURE);
    }
    else return node->data;
}

listPointer invertedCopyList(listPointer ptr) {
    listPointer temp, node;
    if (!ptr) {
        fprintf(stderr, "Node is empty");
        exit(EXIT_FAILURE);
    }
    else {
        node = NULL;
        while(ptr) {
            temp = getNode(); temp->data = popNodeValue(ptr); temp->link = node; node = temp;
            ptr = ptr->link;
        }
    }
    return node;
}