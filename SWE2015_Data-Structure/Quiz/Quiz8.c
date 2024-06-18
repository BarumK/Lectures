#include <stdio.h>
#define MAX_COL 9

typedef struct {
    int row, col, value;
} term;

void fastTranspose(term a[], term b[]);

int main() {
    printf("Before Transpose:\n");
    term a[9];
    a[0].row = 6, a[0].col = 6, a[0].value = 8;
    a[1].row = 0, a[1].col = 0, a[1].value = 15;
    a[2].row = 0, a[2].col = 3, a[2].value = 22;
    a[3].row = 0, a[3].col = 5, a[3].value = -15;
    a[4].row = 1, a[4].col = 1, a[4].value = 11;
    a[5].row = 1, a[5].col = 2, a[5].value = 3;
    a[6].row = 2, a[6].col = 3, a[6].value = -6;
    a[7].row = 4, a[7].col = 0, a[7].value = 91;
    a[8].row = 5, a[8].col = 2, a[8].value = 28;
    for(int i = 0; i < 9; i++) printf("a[%d]: %d %d %d\n", i, a[i].row, a[i].col, a[i].value);
    
    printf("\nAfter Transpose:\n");
    term b[9];
    fastTranspose(a, b);
    for(int i = 0; i < 9; i++) printf("b[%d]: %d %d %d\n", i, b[i].row, b[i].col, b[i].value);
    
    return 0;
}

void fastTranspose(term a[], term b[]) {
    int startingPos[MAX_COL];
    int i, j, numCols = a[0].col, numTerms = a[0].value; // col만 따는 이유: col이 전치행렬의 row이기 때문에 기존 행렬의 row는 따놓지 않음
    b[0].row = numCols; b[0].col = a[0].row; b[0].value = numTerms; // b[0] initialization
    if (numTerms > 0) { // non-zero matrix일때만 진행
        // 여기서부터 바꾼 부분입니다
        
        for(i = 0 ; i < numCols ; i++) startingPos[i] = 1;
        for(i = 1 ; i <= numTerms ; i++) {
            for(j = a[i].col + 1 ; j < numCols ; j++) startingPos[j]++;
        }
        
        // 여기까지 바꾼 부분입니다
        
        for(i = 1 ; i <= numTerms ; i++) {
            j = startingPos[a[i].col];
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
            startingPos[a[i].col]++;
        }
    }
}
