// 슬라이드의 경우 출력되는 count의 값은 6입니다.
// count의 개수는 결국 클래스의 개수와 동일하기에, 0 = 4, 3 = 1, 6 = 10, 7 = 4, 6 = 8을 넣었을 경우
// New class:     0    4    7
// New class:     1    3
// New class:     2
// New class:     5
// New class:     6    8   10
// New class:     9
// 의 총 6가지 클래스로 분류됩니다. 따라서 count의 값은 6입니다.
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 100


typedef struct node *nodePointer;
typedef struct node {
    int data; 
    nodePointer link;
} node;

void main (void) { 
    short int out[MAX_SIZE]; 
    nodePointer seq[MAX_SIZE];
    nodePointer x, y, top; int i, j, n;

    printf("Enter the size (<= %d) ", MAX_SIZE);
    scanf("%d", &n);
    for (i = 0; i < n ; i++) { 
        out[i] = TRUE;
        seq[i] = NULL; 
    }
    printf("Enter a pair of numbers (-1 -1 to quit): ");
    scanf("%d %d", &i, &j);

    /* phase 1: input the equivalence class */
    while (i >= 0) {
        x = (nodePointer) malloc(sizeof(*x));
        x->data = j; x->link = seq[i]; seq[i] = x;
        x = (nodePointer) malloc(sizeof(*x));
        x->data = i; x->link = seq[j]; seq[j] = x;
        printf("Enter a pair of numbers (-1 -1 to quit): ");
        scanf("%d %d", &i, &j);
    }

    /* phase 2: print out the equivalent classes */
    int count = 0;
    for (i = 0; i < n; i++) {
        if (out[i]) {
            count++;
            printf("\nNew class: %5d", i);
            out[i] = FALSE; x = seq[i]; top = NULL;
            for (;;) {
                while (x) {
                    j = x->data;
                    if (out[j]) {
                        printf("%5d", j); out[j] = FALSE;
                        y = x->link; x->link = top; top = x; x = y;
                    }
                    else x = x->link;
                }
                if (!top) break;
                x = seq[top->data];
                top = top->link;
            }
        }
    }
    printf("\nCount: %d\n", count);
}
