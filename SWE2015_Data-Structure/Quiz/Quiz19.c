// delete 함수의 구현은 86번째 줄부터 구현되어 있습니다.
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
    int data;
    listPointer link;
} listNode;

void insert(listPointer* first, listPointer x, int data);
void delete(listPointer* first, listPointer x);

void main() {
    // variable initialization
    listPointer linkedList, node, cursor, cursor2;
    linkedList = (listPointer) malloc(sizeof(listNode));
    node = (listPointer) malloc(sizeof(listNode));
    cursor = linkedList; // cursor to move
    
    linkedList->data = 300; linkedList->link = NULL;
    node->data = 250; node->link = NULL;
    linkedList->link = node;
    
    // insert & print all stack
    for(int i = 1; i <= 10 ; i++) {
        printf("added %3d: ", i);
        insert(&linkedList, linkedList, i);
        
        cursor = linkedList;
        while (cursor) {
            printf("%d -> ", cursor->data);
            cursor = cursor->link;
        }
        printf("NULL\n");
    }
    cursor = linkedList;
    printf("\nAfter insert:\n");
    while (cursor) {
        printf("%d -> ", cursor->data);
        cursor = cursor->link;
    }
    printf("NULL\n\n");

    //delete & print all stack
    //delete(NULL, cursor); // 이 줄을 실행하면 빈 리스트를 넣었을 때의 결과를 볼 수 있음
    for(int i = 1; i <= 10 ; i++) {
        //cursor2 = linkedList->link; // 삭제할 노드의 위치를 지정하는 변수; 여기서는 2번째 값을 계속 지우는 것으로 설정함
        cursor2 = linkedList; // 위의 줄 말고 이 줄을 실행하면 맨 앞의 값을 계속 지우는 것으로 설정됨
        printf("deleted %3d: ", cursor2->data);
        delete(&linkedList, cursor2);
        
        cursor = linkedList;
        while (cursor) {
            printf("%d -> ", cursor->data);
            cursor = cursor->link;
        }
        printf("NULL\n");
    }
    
    cursor = linkedList;
    printf("\nAfter delete:\n");
    while (cursor) {
        printf("%d -> ", cursor->data);
        cursor = cursor->link;
    }
    printf("NULL\n");
}


void insert(listPointer* first, listPointer x, int data){
    listPointer temp;
    temp = (listPointer) malloc(sizeof(listNode));
    temp->data = data;
    if (*first) {
        temp->link = x->link;
        x->link = temp;
    }
    else {
        temp->link = NULL;
        *first = temp;
    }
}

void delete(listPointer* first, listPointer x) {
    listPointer temp, trail;
    if (!first) { // 아예 빈 linked list가 들어왔을 때
        fprintf(stderr, "Linked list is empty, cannot delete element");
        exit(EXIT_FAILURE);
    } else if (!((*first)->link)) { // 들어온 linked list가 하나의 값만을 가지고 있을때, Null포인터 반환
        temp = *first;
        *first = NULL;
        free(temp);
    } else {
        if (x == *first) {// 맨 앞의 값을 지우려고 할 때
            temp = *first;
            *first = (*first)->link;
            free(temp);
        } else { // 나머지 일반적인 경우
            trail = *first;
            while (trail->link != x) { // trail의 다음 list가 x이면 루프에서 탈출; 기존 함수의 trail 값을 찾는 과정
                trail = trail->link;
            }
            trail->link = x->link;
            free(x);
        }
    }
}