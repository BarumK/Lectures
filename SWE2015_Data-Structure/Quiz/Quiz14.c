/*
문제 해결 방식
1. element라는 구조체에 두 가지 int 변수 선언: key와 value
    key는 queue가 가득 찼는지와 비어있는지를 확인할 변수로써, 
        처음 초기값이거나 dequeue 한 이력이 있는 경우, 이 두 가지 경우(즉 현재 queue가 존재하지 않는 칸)에는 -1로 세팅하고
        그렇지 않은 경우(즉 현재 queue가 존재하는 칸의 경우)에는 1로 세팅한다.
    value는 실제 담을 값을 저장한다.

2. front와 rear의 역할은 기존 방식과 동일하다.

3. enqueue함수 사용시:
    queue가 꽉 찬 상태가 아니면 rear을 1 증가시키고
    (최댓값을 넘어가면 다시 0으로 이동하는 것도 기존 방식과 동일)
    queue[rear]값에 새로운 element를 집어넣는다.
    이 때 집어넣는 element의 key 값은 1이다.

4. dequeue함수 사용시:
    queue가 빈 queue가 아니면 front를 1 증가시키고
    (최댓값을 넘어가면 다시 0으로 이동하는 것도 기존 방식과 동일)
    queue[front].key가 기존에 1일 텐데 이를 -1로 바꿔주고
    queue[front]값을 리턴한다.

5. full & empty queue 확인 기준
    full: (rear == front) && (queue[rear].key == 1)이 참일 경우 full
    empty: (rear == front) && (queue[rear].key == -1)이 참일 경우 empty
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 10 // 이 값을 변경하면 최대 queue의 크기 조절 가능

// type definition
typedef struct {
    int key; // 판단에 사용될 변수
    int value; // 실제 담을 값
} element;

// function definition
void addq(element item, element* queue, int* front, int* rear);
element deleteq(element* queue, int* front, int* rear);
void queueFull();
element queueEmpty();

// main
int main() {
    // initialize
    element queue[MAX_QUEUE_SIZE];
    for (int i = 0 ; i < MAX_QUEUE_SIZE ; i++) { queue[i].key = -1; } // 처음엔 전부 비어있는 queue이기에 전부 key값을 -1로 초기화
    int rear = 0, front = 0;
    
    // actual use of queue
    element e, f;
    e.key = 1; // 새로 add하는 key값은 무조건 1이어야 함
    //f = deleteq(queue, &front, &rear); // 이 줄 실행하면 빈 queue에서 에러 발생하는 거 확인 가능함
    for (int i = 0 ; i < MAX_QUEUE_SIZE ; i++) { // queue 전부 채우기
        e.value = rand() % 100 + 1; // 추가하는 랜덤 값의 범위 제한
        addq(e, queue, &front, &rear);
        printf("add #%d - added %d, front: %d, rear: %d\n", (i + 1), e.value, front, rear);
    }
    //addq(e, queue, &front, &rear); // 이 줄 실행하면 꽉 찬 queue에서 에러 발생하는 거 확인 가능함
    for (int i = 0 ; i < MAX_QUEUE_SIZE ; i++) { // queue 전부 비우기
        f = deleteq(queue, &front, &rear);
        printf("delete #%d - deleted %d, front: %d, rear: %d\n", (i + 1), f.value, front, rear);
    }
    //f = deleteq(queue, &front, &rear); // 이 줄 실행하면 빈 queue에서 에러 발생하는 거 확인 가능함

    return 0;
}


// functions
void addq(element item, element* queue, int* front, int* rear) {
    if ((*front == *rear) && (queue[*rear].key == 1))
        return queueFull();
    *rear = (*rear + 1) % MAX_QUEUE_SIZE;
    queue[*rear] = item;
}

element deleteq(element* queue, int* front, int* rear) {
    if ((*front == *rear) && (queue[*rear].key == -1)) 
        return queueEmpty();
    *front = (*front + 1) % MAX_QUEUE_SIZE;
    queue[*front].key = -1;
    return queue[*front];
}

void queueFull() {
    fprintf(stderr, "Queue is full, cannot add element");
    exit(EXIT_FAILURE);
}

element queueEmpty() {
    fprintf(stderr, "Queue is empty, cannot pop element");
    exit(EXIT_FAILURE);
}