#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define HASH_SIZE 1000
#define MAX_LENGTH 1000

// 구조체 정의
typedef struct WordNode* WordNodePointer;
typedef struct WordNode {
    int hash[2];
    char* word[2];
    int frequency;
    WordNodePointer next;
} WordNode;

// 함수 선언
void getBigramResult(char* filename);
char* readLine(FILE* file);
int hash(char* word);
int hash2(char* word);
int hash3(char* word);
int hash4(char* word);
void lower(char* s);
int emptyString(char* s);
WordNodePointer getNode();
void insert(WordNodePointer* hashTable, char** lineSeparate, int len);
int sameNode(WordNodePointer a, WordNodePointer b);
int*** getArray(WordNodePointer* hashTable, int n);
WordNodePointer searchNode(WordNodePointer* hashTable, int n, int m);
void sortArr(int*** arr, int n);
int compare(const void* a, const void* b);
void freeHashTable(WordNodePointer* hashTable);

// 결과를 배열로 받으면 출력해주는 함수

int main() {
    int start_time = time(NULL);
    
    char* filename = "shakespeare.txt";
    getBigramResult(filename);
    
    int end_time = time(NULL);
    int result_time = end_time - start_time;
    
    printf("Total duration time: %3dmin %2dsec\n", (result_time / 60), (result_time % 60));
}

// 함수 정의 부분
void getBigramResult(char* filename) {
    // 파일 열기
    FILE* file = fopen(filename, "r");
    
    // 파일 열기에 실패하면
    if (file == NULL) {
        fprintf(stderr, "Cannot open file");
        exit(EXIT_FAILURE);
    }
    
    // 파일 열기에 성공하면
    printf("Successfully opened file \"%s\"\n", filename);
    
    // 변수 선언
    char* line; // 한 줄 읽은 것을 담을 배열
    char* ptr; // 한 단어를 분리한 결과를 담을 배열
    char* lineSeparate[MAX_LENGTH]; // 줄 단위로 분리한 단어들을 담은 배열을 저장하는 배열
    int* lineHash[MAX_LENGTH]; // 줄 단위로 분리한 단어들을 해시화해서 저장하는 배열
    int counter;

    // 해시 테이블 선언 및 초기화
    WordNodePointer hashTable[HASH_SIZE];
    WordNodePointer dummyNode;
    for(int i = 0 ; i < HASH_SIZE ; i++) {
        dummyNode = getNode();
        dummyNode->frequency = 0; // 더미노드의 frequency에는 빈도 대신에 여기에 달려있는 노드의 개수를 담을 예정
        hashTable[i] = dummyNode;
    }
    
    while(TRUE) { // 전체 루프 돌리기 위함용
    //for(int p = 0; p < 100; p++) { // 일부 루프만 돌리기 위함용
        // 다음 줄 읽어오기
        line = readLine(file);
        
        // 변수들 초기화
        counter = 0;
        memset(lineSeparate, 0, MAX_LENGTH);

    
        // 읽어온 줄이 있다면 작업 실행
        if (line && !emptyString(line)) {
            //printf("Line:%s\n", line); // 확인용
            
            // 라인을 다시 단어 단위로 자르기
            ptr = strtok(line, ".,;:!?\"<>{}()[] ");
            while (ptr != NULL){
                lower(ptr);
                //printf("%s\n", ptr); // 중간 확인용
                lineSeparate[counter++] = strdup(ptr);
                ptr = strtok(NULL, ".,;:!?\"<>{}()[] ");
            }
            
            // 링크드 리스트에 추가하기
            insert(hashTable, lineSeparate, counter);
        }
                
        // 마지막에 다다르면 반복문 탈출
        if(!line) break;
    }
    
    // 다 읽었으니 파일 닫기
    fclose(file);
    
    /*
    // 확인용
    for(int i = 0 ; i < HASH_SIZE ; i++) {
        printf("%d: %d\t", i, hashTable[i]->frequency);
    }
    
    int mmmm = 998;
    WordNodePointer temp = hashTable[mmmm];
    printf("\nhashTable[%d]: frequency %d\n", mmmm, temp->frequency);
    temp = temp->next;
    while(temp->next) {
        printf("(%s, %s): %d -> ", temp->word[0], temp->word[1], temp->frequency);
        temp = temp->next;
    }
    printf("NULL\n");
    */
    
    // 결과 분석용 배열 생성
    int n = 0;
    for (int i = 0 ; i < HASH_SIZE ; i++) {
        n = hashTable[i]->frequency ? hashTable[i]->frequency : n;
        /*
        if (hashTable[i]->frequency > n) {
            n = hashTable[i]->frequency;
        }
        */
    }
    int*** frequencies = getArray(hashTable, n);
    /*
    // 확인용
    for (int i = 0 ; i < HASH_SIZE ; i++) {
        for (int j = 0; j < n ; j++) {
            printf("[%d, %d, %d]\t", frequencies[i][j][0], frequencies[i][j][1], frequencies[i][j][2]);
        }
        printf("\n");
    }
    */
    
    // 정렬하기
    sortArr(frequencies, n);
    /*
    // 확인용
    for (int i = 0 ; i < HASH_SIZE ; i++) {
        for (int j = 0 ; j < n ; j++) {
            printf("[%d][%d][0]: %d, [%d][%d][1]: %d, [%d][%d][2]: %d\n",
                   i, j, frequencies[i][j][0], i, j, frequencies[i][j][1], i, j, frequencies[i][j][2]);
        }
    }
    */
    
    // 제일 빈도가 높은 n개 출력 
    int nums = 7;
    
    int a[HASH_SIZE];
    for (int i = 0 ; i < HASH_SIZE ; i++) {
        a[i] = 0;
    }

    int row, col, freq, temp;
    WordNodePointer topNode;
    freq = -1;
    for (int i = 0; i < nums ; i++) {
        for (int j = 0 ; j < HASH_SIZE ; j++){
            if (frequencies[j][a[j]][2] > freq) {
                row = frequencies[j][a[j]][0];
                col = frequencies[j][a[j]][1];
                freq = frequencies[j][a[j]][2];
                temp = j;
            }
        }
        topNode = searchNode(hashTable, row, col);
        printf("#%d: (%s, %s) -> %d times\n", (i + 1), topNode->word[0], topNode->word[1], topNode->frequency);
        a[temp] += 1;
        freq = -1;
    }

    // 메모리 해제
    freeHashTable(hashTable);
}

char* readLine(FILE* file) { // 완료
    char* line = (char*) malloc(sizeof(char) * MAX_LENGTH);

    if (!line) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    // 초기화
    memset(line, 0, MAX_LENGTH);

    // 파일에서 한 줄을 읽기
    if (fgets(line, MAX_LENGTH, file) == NULL) {
        free(line);  // 실패 시 할당된 메모리 해제
        return NULL;
    }

    // 문자열에서 '\n' 제거
    char* newlinePosition = strchr(line, '\n');
    if (newlinePosition) {
        *newlinePosition = '\0';
    }

    return line;
}

int hash(char* word) { // 완료
    int hashValue = 0;
    for (int i = 0; word[i] != '\0'; i++) hashValue += (int)word[i];
    return hashValue;
}

int hash2(char* word) { // 완료
    int hashValue = 0;
    int i = 0;
    for ( ; word[i] != '\0'; i++) hashValue += (int)word[i];
    if (i == 0) return 0;
    return hashValue / i;
 }

int hash3(char* word) { // 완료
    return (int)word[0];
}

int hash4(char* word) { // 완료
    int hashValue = 1;
    for (int i = 0; word[i] != '\0'; i++) hashValue += (int)word[i] + 9;
    return hashValue;
}

void lower(char* s) { // 완료
    int i;
    int len = strlen(s);
    for (i = 0; i < len; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] -= ('A' - 'a');
    }
}

int emptyString(char* s) { // 완료
    if (s[0] == '\0') return 1;
    else return 0;
}

WordNodePointer getNode() { // 완료
    WordNodePointer node;
    node = (WordNodePointer) malloc(sizeof(WordNode));
    node->hash[0] = -1;
    node->hash[1] = -1;
    node->word[1] = NULL;
    node->word[2] = NULL;
    node->next = NULL;
    node->frequency = 1;
    return node;
}

void insert(WordNodePointer* hashTable, char** lineSeparate, int counter) { // 완료
    // 변수 선언
    WordNodePointer node; // 새로 만들 노드
    int hashValue; // 그 노드의 해시값
    int exist; // 그 노드가 해시테이블에 동일한 값이 존재하는지 확인하기 위한 변수
    WordNodePointer temp; // 커서 역할을 하며 움직일 변수
    
    for(int i = 0; i < counter - 1; i++){
        node = getNode();
        node->word[0] = lineSeparate[i]; // strdup 사용하지 않고 그대로 저장
        node->word[1] = lineSeparate[i + 1];
        node->hash[0] = hash2(node->word[0]); ///////////////////////////////////////////////////////////////////////////////////////////
        node->hash[1] = hash2(node->word[1]); ///////////////////////////////////////////////////////////////////////////////////////////
        //printf("%s, %s\t", node->word[0], node->word[ 1]); // 중간 확인용
        hashValue = (node->hash[0] + node->hash[1]) % HASH_SIZE;
        //printf("%d\n", hashValue); // 중간 확인용
        
        // 해시테이블에 집어넣기 과정
        exist = FALSE;
        temp = hashTable[hashValue];
        
        //printf("hash: %d\t", hashValue); // 중간 확인용

        while(temp->next) {
            //printf("1111111111\n"); // 중간 확인용
            if (sameNode(temp, node)) { // 탐색 중간에 이미 같은 노드가 있다면
                temp->frequency += 1;
                exist = TRUE;
                free(node);
                break;
            }
            temp = temp->next;
        }
        if (!exist) { // 같은 노드가 없다면 추가해야함
            //printf("2222222222\n"); // 중간 확인용
            hashTable[hashValue]->frequency += 1;
            temp->next = node;
        }
    }
    //printf("\n--------------------\n"); // 중간 확인용
}

int sameNode(WordNodePointer a, WordNodePointer b) { // 완료
    if (a->hash[0] == b->hash[0])
        if (a->word[0] && b->word[0])
            return ((strcmp(a->word[0], b->word[0]) == 0) && ((strcmp(a->word[1], b->word[1]) == 0)));
        else
            return 0;
    else
        return 0;
}

int*** getArray(WordNodePointer* hashTable, int n) { // 완료
    WordNodePointer temp;
    int*** result = (int***) malloc(sizeof(int**) * HASH_SIZE);
    for (int i = 0 ; i < HASH_SIZE ; i++) {
        result[i] = (int**) malloc(sizeof(int*) * n);
        for (int j = 0 ; j < n ; j++) {
            result[i][j] = (int*) malloc(sizeof(int*) * 3);
            result[i][j][0] = i;
            result[i][j][1] = j;
            temp = searchNode(hashTable, i, j);
            result[i][j][2] = temp ? temp->frequency : -1;
        }
    }
    return result;
}

WordNodePointer searchNode(WordNodePointer* hashTable, int n, int m) { // 완료
    WordNodePointer node = hashTable[n];
    for (int i = 0 ; i < (m + 1) ; i++){
        if (node->next){
            node = node->next;
        }
        else return NULL;
    }
    return node;
}

void sortArr(int*** arr, int n) {
    for (int i = 0; i < HASH_SIZE; i++) {
        qsort(arr[i], n, sizeof(int*), compare);
    }
}

int compare(const void* a, const void* b) {
    return (*(int**)b)[2] - (*(int**)a)[2];
}

void freeHashTable(WordNodePointer* hashTable) {
    WordNodePointer temp1, temp2;
    for (int i = 0 ; i < HASH_SIZE ; i++) {
        temp1 = hashTable[i];
        //printf("search hashTable[%d]\n", i); // 중간 확인용
        while(temp1->next) {
            //printf("%d -> ", temp1->frequency); // 중간 확인용
            temp2 = temp1;
            temp1 = temp1->next;
            free(temp2);
        }
        free(temp1);
        //printf("NULL\n"); // 중간 확인용
    }
}