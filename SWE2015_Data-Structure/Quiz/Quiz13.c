#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

// type definition
typedef struct { int key; } element;

// function definition
void push (element item, element* stack, int* top);
element pop(element* stack, int* top);
void stackFull();
element stackEmpty();

int main() {
    // initialize
    element stack1[MAX_STACK_SIZE], stack2[MAX_STACK_SIZE];
    int top1 = -1, top2 = -1;
    element e, f, g, h;
    
    // Stack 생성 후 랜덤 정수 값 넣기기
    for (int i = 0 ; i < 10 ; i++) {
        e.key = (rand() % 1000) + 1; // 0 안되게 설정, 1 ~ 1000
        push(e, stack1, &top1);
    }
    
    // 다른 Stack에 넣어서 순서 뒤집기기
    for (int i = 0 ; i < 10 ; i++) {
        f = pop(stack1, &top1);
        push(f, stack2, &top2);
    }

    // 뒤집은 Stack을 순차적으로 pop하여 원래 Stack의 print out in the order of first-in-first-out 구현
    for (int i = 0 ; i < 10 ; i++) {
        g = pop(stack2, &top2);
        printf("#%d element: %d\n", i, g.key);
    }

    return 0;
}



// functions
void push (element item, element* stack, int* top) {
    if (*top >= MAX_STACK_SIZE - 1) {
        stackFull();
        return;
    }
    stack[++(*top)] = item;
}

element pop(element* stack, int *top) {
    if (*top == -1)
        return stackEmpty();
    return stack[(*top)--];
}

void stackFull() {
    fprintf(stderr, "Stack is full, cannot add element");
    exit(EXIT_FAILURE);
}

element stackEmpty() {
    fprintf(stderr, "Stack is empty, cannot pop element");
    exit(EXIT_FAILURE);
}