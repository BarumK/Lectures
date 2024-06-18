#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 101

void stringremove(char* s, int i, int j);

int main() {
    char n[MAX_SIZE] = "This is Homework Quiz 9 in Data Structure";
    stringremove(n, 7, 9);
    printf("%s\n", n);
    
    return 0;
}

void stringremove(char* s, int i, int j) { // s의 i번째 index부터 j개의 항목 삭제
    char temp[MAX_SIZE];
    memset(temp, 0, sizeof(temp));
    
    if (i < 0 || i > strlen(s)) { // error 방지
        fprintf(stderr, "position is out bounds\n");
        exit(1);
    }
    
    if (strlen(s) && j) { // s가 빈 string이 아니고 j가 0이 아니면 자르기 실행
        strncpy(temp, s, i); // i번째 index 전까지는 그대로 붙이고
        strcat(temp, s+i+j); // i + j번째의 index 뒷부분으로 바로 건너뛰어 뒷부분 붙이고
        strcpy(s, temp); // 그 temp를 원래 string에 덮어쓰기
    }
}