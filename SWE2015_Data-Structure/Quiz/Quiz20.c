// addq 함수의 구현은 44번째 줄부터 구현되어 있습니다.
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE 10

// type definition
typedef struct { 
    int key;
} element;
typedef struct queue* queuePointer;
typedef struct queue {
    element data;
    queuePointer link;
}queue;

// function definition
void addq (int i, element item);
element deleteq (int i);
element queueEmpty();

// global variables
queuePointer front[MAX_QUEUE];

int main() {
    // initialization
    for (int i = 0 ; i < MAX_QUEUE ; i++) {
        front[i] = NULL;
    }
    
    // 여기서는 front[0]만 사용하겠습니다
    element a;
    for (int i = 0 ; i < 10 ; i++) {
        a.key = rand() % 1000 + 1;
        printf("Added %5d\n", a.key);
        addq(0, a);
    }
    for (int i = 0 ; i < 10 ; i++) {
        printf("Deleted %5d\n", deleteq(0).key);
    }
}


void addq (int i, element item) {
    queuePointer temp, cursor;
    temp = (queuePointer) malloc(sizeof(queue));
    temp->data = item; temp->link = NULL;

    cursor = front[i]; // cursor가 기존의 rear 역할을 해 줄 것임
    
    while(front[i] && cursor->link) { // 끝을 찾기 위한 과정; 시작점이 NULL이거나 cursor의 link가 Null이면 루프 탈출
        cursor = cursor->link;
    }

    if (front[i])
        cursor->link = temp;
    else 
        front[i] = temp; 
    cursor = temp;
}

element deleteq (int i) {
    queuePointer temp = front[i];
    element item;
    if (!temp)
        return queueEmpty();
    item = temp->data;
    front[i] = temp->link;
    free(temp);
    return item;
}

element queueEmpty() {
    fprintf(stderr, "Queue is empty");
    exit(EXIT_FAILURE);
}