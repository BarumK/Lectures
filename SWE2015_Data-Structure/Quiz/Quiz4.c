#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int** make2dArray(int row, int* length) {
    int** x;

    x = (int **) malloc(sizeof(int*) * row);
    for(int i = 0; i < row ; i++) {
        x[i] = (int *) malloc(sizeof(int) * length[i]);
        for(int j = 0 ; j < length[i] ; j++) {
            x[i][j] = rand() % 1000;
            printf("%d ", x[i][j]);
        }
        printf("\n");
    }

    return x;
}

void main (void) {
    int** my2dArray;
    int* length;
    int row;
    srand(time(NULL));

    scanf("%d", &row);
    length = (int*) malloc(sizeof(int) * row);
    for(int i = 0 ; i < row ; i++) {
        length[i] = rand() % 10 + 1; // 0은 나오지 않게끔
    }

    my2dArray = make2dArray(row, length);
}