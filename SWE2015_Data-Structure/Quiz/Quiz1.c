#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main (void) {
    int column = 6, row = 8;
    int** arr;

    arr = (int**) malloc(sizeof(int*) * column);
    for(int i = 0 ; i < column ; i++) {
        arr[i] = (int*) malloc(sizeof(int) * row);
    }

    for (int i = 0 ; i < column ; i++) {
        for (int j = 0 ; j < row ; j++) {
            arr[i][j] = rand() % 100;
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    for (int i = 0 ; i < column ; i++) {
        free(arr[i]);
    }
    free(arr);
}