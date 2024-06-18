// erase 함수의 구현은 86번째 줄부터 구현되어 있습니다.
#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x, y) (((x) < (y)) ? -1 : (((x) == (y)) ? 0 : 1))

// type definition
typedef struct polyNode* polyPointer;
typedef struct polyNode {
    float coef;
    int expon;
    polyPointer link;
} polyNode;

//function definition
polyPointer padd(polyPointer a, polyPointer b);
void attach(float coefficient, int exponent, polyPointer* ptr);
void erase(polyPointer* ptr);


int main() {
    polyPointer a, b, aRear, bRear, result, cursor;
    a = (polyPointer) malloc(sizeof(polyNode)); b = (polyPointer) malloc(sizeof(polyNode));
    aRear = a; bRear = b;
    
    attach(3, 14, &aRear); attach(2, 8, &aRear); attach(1, 0, &aRear);
    attach(8, 14, &bRear); attach(-3, 10, &bRear); attach(10, 6, &bRear);

    result = padd(a, b);
    cursor = result;
    cursor = cursor->link; // 맨 앞 dummy node 제거
    while(cursor) {
        printf("coefficient:%5.1f, exponent:%3d\n", cursor->coef, cursor->expon);
        cursor = cursor->link;
    }

    /*
    result = padd(a, b);
    cursor = result;
    while(cursor) {
        printf("coefficient:%3d, exponent:%3d\n", cursor->coef, cursor->expon);
        cursor = cursor->link;
    }
    */
    
    return 0;
}


// functions
polyPointer padd(polyPointer a, polyPointer b) {
    
    polyPointer c, rear, temp;
    float sum;
    rear = (polyPointer) malloc(sizeof(polyNode));
    c = rear;
    while(a && b) {
        switch (COMPARE(a->expon, b->expon)) {
            case -1: /* a->expon < b->expon */
                attach(b->coef, b->expon, &rear);
                b = b->link;
                break;
            case 0: /* a->expon = b->expon */
                sum = a->coef + b->coef;
                if (sum) attach(sum, a->expon, &rear);
                a = a->link; b = b->link;
                break;
            case 1: /* a->expon > a->expon */
                attach(a->coef, a->expon, &rear);
                a = a->link;
        }
    }
    
    /* copy the rest of list a and list b */
    for (; a ; a = a->link) attach(a->coef, a->expon, &rear);
    for (; b ; b = b->link) attach(b->coef, b->expon, &rear);
    rear->link = NULL;

    /* delete the useless initial node */
    temp = c; c = c->link; free(temp);

    return c;
}

void attach(float coefficient, int exponent, polyPointer* ptr) {
    polyPointer temp;
    temp = (polyPointer) malloc(sizeof(polyNode));

    temp->coef = coefficient;
    temp->expon = exponent;
    temp->link = NULL;

    (*ptr)->link = temp;
    *ptr = temp;
}

void erase(polyPointer* ptr) {
    polyPointer temp;
    for(; *ptr ;) {
        temp = *ptr;
        *ptr = (*ptr)->link;
        free(temp);
    }
}
