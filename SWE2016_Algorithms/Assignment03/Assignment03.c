#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node* nodePointer;
typedef struct node{
    char character;
    int frequency;
    int leaf;
    nodePointer left, right; // for tree
    nodePointer next; // for linked list
} node;

nodePointer makeNode(char character, int frequency, nodePointer left, nodePointer right);
char* TreeToString(nodePointer root);
void encoding(nodePointer root, char** arr, char* str, int depth);
void freeTree(nodePointer root);

int main() {
    // variables
    int count, num, freq, len, depth;
    int hash[128] = {0};
    char character;
    char* encode[128];
    nodePointer list, tree, temp, temp2;
    nodePointer* nodes;
    nodePointer* queue;

    // open file
    FILE* inputFile = fopen("hw3_input.txt", "r");
    FILE* outputFile1 = fopen("hw3_output1.txt", "w");
    FILE* outputFile2 = fopen("hw3_output2.txt", "w");   

    // read from input file
    while ((character = fgetc(inputFile)) != EOF) hash[character] += 1;

    // preprocessing for making tree
    count = 0;
    for (int i = 0; i < 128; i++) {
        if (hash[i]) count++;
    }

    num = 0;
    nodes = (nodePointer*) malloc(sizeof(nodePointer) * count);
    for (int i = 0; i < 128; i++) {
        if (hash[i] > 0) nodes[num++] = makeNode(i, hash[i], NULL, NULL);
    }
    
    // sort nodes by frequency in ascending order
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (nodes[j]->frequency > nodes[j + 1]->frequency) {
                temp = nodes[j];
                nodes[j] = nodes[j + 1];
                nodes[j + 1] = temp;
            }
        }
    }
    
    // make linked list
    for (int i = 0; i < count - 1; i++) {
        nodes[i]->next = nodes[i + 1];
    }
    list = nodes[0];

    /*
    // print for checking linked list
    temp = list;
    while (temp) {
        printf("%c %d\n", temp->character, temp->frequency);
        temp = temp->next;
    }
    */

    // make tree
    while(list->next) {
        freq = list->frequency + (list->next)->frequency;
        temp = makeNode(0, freq, list, list->next);
        temp->leaf = 0;

        list = list->next;
        temp2 = list;
        while (temp2->next) {
            if (temp2->next->frequency < temp->frequency) temp2 = temp2->next;
            else break;
        }
        temp->next = temp2->next;
        temp2->next = temp;
        list = list->next;
        
        /*
        // print for checking tree 1
        temp2 = list;
        while (temp2) {
            printf("%c %d -> ", temp2->character, temp2->frequency);
            temp2 = temp2->next;
        }
        printf("\n");
        */
    }
    tree = list;

    /*
    // print for checking tree 2
    num = 0;
    queue = (nodePointer*) malloc(sizeof(nodePointer) * count);
    queue[num++] = tree;
    while (num) {
        if (queue[0]->leaf) printf("%c(%d) //// ", queue[0]->character, queue[0]->frequency);
        else printf("**** //// ");
        if (queue[0]->left) queue[num++] = queue[0]->left;
        if (queue[0]->right) queue[num++] = queue[0]->right;
        for (int i = 0; i < num - 1; i++) queue[i] = queue[i + 1];
        num--;
    }
    */

    // find max depth of tree(root is depth 0)
    char* treeString = TreeToString(tree);
    num = 0;
    depth = 0;
    len = strlen(treeString);
    for (int i = 0; i < len; i++) {
        if (treeString[i] == '(') num++;
        else if (treeString[i] == ')') num--;
        if (depth < num) depth = num;
    }
    //printf("%s\n", treeString);
    //printf("%d\n", depth);

    // encoding
    for (int i = 0; i < 128; i++) {
        encode[i] = (char*) malloc(sizeof(char) * (depth + 1));
        encode[i][0] = '\0';
    }
    encoding(tree, encode, "", depth);
    
    // print hw3_output2
    for (int i = 0; i < 128; i++) {
        if (strlen(encode[i])) fprintf(outputFile2, "%c: %s\n", i, encode[i]);
    }

    fseek(inputFile, 0, SEEK_SET);
    while ((character = fgetc(inputFile)) != EOF) fprintf(outputFile2, "%c", character);
    fprintf(outputFile2, "\n");
    
    // print hw3_output1
    fprintf(outputFile1, "%s\n", treeString);
    fseek(inputFile, 0, SEEK_SET);
    while ((character = fgetc(inputFile)) != EOF) fprintf(outputFile1, "%s", encode[character]);
    fprintf(outputFile1, "\n");

    // memory deallocation
    for (int i = 0; i < 128; i++) free(encode[i]);
    freeTree(tree);
    free(treeString);
    free(nodes);

    // close file
    fclose(inputFile);
    fclose(outputFile1);
    fclose(outputFile2);
}

// functions
nodePointer makeNode(char character, int frequency, nodePointer left, nodePointer right) {
    nodePointer temp;
    temp = (nodePointer) malloc(sizeof(node));
    temp->character = character;
    temp->frequency = frequency;
    temp->leaf = 1;
    temp->left = left;
    temp->right = right;
    temp->next = NULL;
    return temp;
}

char* TreeToString(nodePointer root) {
    if (!root) {
        char* emptyString = (char*)malloc(1);
        emptyString[0] = '\0';
        return emptyString;
    }

    char* leftStr = TreeToString(root->left);
    char* rightStr = TreeToString(root->right);

    int size = strlen(leftStr) + strlen(rightStr) + 4; // for '(', ',', ')', '\0'
    char* result = (char*) malloc(size);

    if (root->leaf) snprintf(result, size, "%c", root->character);
    else snprintf(result, size, "(%s,%s)", leftStr, rightStr);

    free(leftStr);
    free(rightStr);

    return result;
}

void encoding(nodePointer root, char** arr, char* str, int depth) {
    if (root->leaf) {
        strcpy(arr[root->character], str);
    }
    else {
        char* left = (char*) malloc(sizeof(char) * (depth + 1));
        char* right = (char*) malloc(sizeof(char) * (depth + 1));

        strcpy(left, str);
        strcpy(right, str);

        strcat(left, "0");
        strcat(right, "1");

        encoding(root->left, arr, left, depth);
        encoding(root->right, arr, right, depth);

        free(left);
        free(right);
    }
}

void freeTree(nodePointer root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}