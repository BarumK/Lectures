#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(x, y) ((x >= y) ? (x) : (y))

char* lcs(char** str, int num);

int main() {
    // variables
    int num, lcslen, len, ATGClen, total, temp, temp2, temp3;
    int* maxPoint;
    int** points;
    char dollar[5];
    char* lcsResult;
    char** ATGC;

    // open file
    FILE* inputFile = fopen("hw2_input.txt", "r");
    FILE* outputFile = fopen("hw2_output.txt", "w");

    // read file
    fscanf(inputFile, "%d", &num);
    fscanf(inputFile, "%s", dollar);
    
    ATGC = (char**)malloc(sizeof(char*) * num);
    for (int i = 0; i < num; i++) {
        ATGC[i] = (char*)malloc(sizeof(char) * 121);
        fscanf(inputFile, "%s", ATGC[i]);
        //printf("%s\n", ATGC[i]);
    }

    // find lcs
    lcsResult = (char*)malloc(sizeof(char) * 121);
    lcsResult = lcs(ATGC, num);
    lcslen = strlen(lcsResult);
    //printf("LCS: %s\n", lcsResult);
    //printf("%d\n", lcslen);

    if (lcslen) {
        // find lcs points
        points = (int**)malloc(sizeof(int*) * num);
        for (int i = 0; i < num; i++) {
            points[i] = (int*)malloc(sizeof(int) * lcslen);
            ATGClen = strlen(ATGC[i]);
            for (int j = 0, temp = 0; (j < ATGClen) && (temp < lcslen); j++) {
                if (ATGC[i][j] == lcsResult[temp]) {
                    points[i][temp++] = j;
                    //printf("%d ", points[i][temp - 1]);
                }
            }
            //printf("\n");
        }

        // find maxPoint
        maxPoint = (int*)malloc(sizeof(int) * lcslen);
        for (int i = 0; i < lcslen; i++) maxPoint[i] = 0;
        for (int i = 0; i < lcslen; i++) {
            for (int j = 0; j < num; j++) {
                if (i == 0) maxPoint[i] = MAX(maxPoint[i], points[j][i]);
                else maxPoint[i] = MAX(maxPoint[i], (points[j][i] - points[j][i - 1] + maxPoint[i - 1]));
            }
            //printf("%d ", maxPoint[i]);
        }
        //printf("\n");

        // find total length for each line
        total = maxPoint[lcslen - 1];
        for (int i = 0; i < num; i++) {
            total = MAX(total, (maxPoint[lcslen - 1] + strlen(ATGC[i]) - points[i][lcslen - 1]));
        }

        // write result
        for (int i = 0; i < num; i++) {
            len = strlen(ATGC[i]);
            for (int j = 0, temp2 = 0, temp3 = 0; j < len; ) {
                if (temp2 == 0) {
                    for (int k = 0; k < points[i][temp2]; k++, j++, temp3++) fprintf(outputFile, "%c", ATGC[i][k]);
                    for ( ; temp3 < maxPoint[temp2]; temp3++) fprintf(outputFile, "-");
                    temp2++;
                }
                else if (temp2 == lcslen) {
                    for (int k = points[i][temp2 - 1]; j < len; k++, j++, temp3++) fprintf(outputFile, "%c", ATGC[i][k]);
                    for ( ; temp3 < total; temp3++) fprintf(outputFile, "-");
                }
                else {
                    for (int k = points[i][temp2 - 1]; k < points[i][temp2]; k++, j++, temp3++) fprintf(outputFile, "%c", ATGC[i][k]);
                    for ( ; temp3 < maxPoint[temp2]; temp3++) fprintf(outputFile, "-");
                    temp2++;
                }
            }
            fprintf(outputFile, "\n");
        }
        for (int i = 0, temp2 = 0; i <= maxPoint[lcslen - 1]; i++) {
            if (i == maxPoint[temp2]) {
                fprintf(outputFile, "*");
                temp2++;
            }
            else fprintf(outputFile, " ");
        }
        fprintf(outputFile, "\n");
    }

    // memory deallocation
    free(lcsResult);
    free(maxPoint);
    for (int i = 0; i < num; i++) free(points[i]);
    free(points);
    for (int i = 0; i < num; i++) free(ATGC[i]);
    free(ATGC);

    // close file
    fclose(inputFile);
    fclose(outputFile);
}


// functions
char* lcs(char** str, int num) {
    int num1, num2, num3, num4, num5;
    int maxLen, stackSize;
    char* LCS;
    char* stack;

    if (num == 2) {
        num1 = strlen(str[0]);
        num2 = strlen(str[1]);

        // memory allocation & initialization
        int** arr = (int**)malloc(sizeof(int*) * (num1 + 1));
        for (int i = 0; i <= num1; i++) {
            arr[i] = (int*)malloc(sizeof(int) * (num2 + 1));
            for (int j = 0; j <= num2; j++) {
                arr[i][j] = 0;
            }
        }

        // finding maximal length of LCS
        for (int i = 1; i <= num1; i++) {
            for (int j = 1; j <= num2; j++) {
                if (str[0][i - 1] == str[1][j - 1]) arr[i][j] = arr[i - 1][j - 1] + 1;
                else arr[i][j] = MAX(arr[i - 1][j], arr[i][j - 1]);
            }
        }
        maxLen = arr[num1][num2];

        // find LCS
        LCS = (char*)malloc(sizeof(char) * (maxLen + 1));
        stack = (char*)malloc(sizeof(char) * maxLen);
        stackSize = 0;

        // backtracking
        int var1, var2, idx;
        var1 = num1;
        var2 = num2;
        while((var1 != 0) && (var2 != 0)) {
            if ((arr[var1][var2] == (arr[var1 - 1][var2 - 1] + 1)) && (str[0][var1 - 1] == str[1][var2 - 1])) {
                stack[stackSize++] = str[0][var1 - 1];
                var1--;
                var2--;
            }
            else if (MAX(arr[var1 - 1][var2], arr[var1][var2 - 1]) == arr[var1 - 1][var2]) {
                var1--;
            }
            else {
                var2--;
            }
        }
            
        // make result
        for (int i = 0; i < maxLen; i++) {
            LCS[i] = stack[--stackSize];
        }
        LCS[maxLen] = '\0';

        // memory deallocation
        for (int i = 0; i <= num1; i++) {
            free(arr[i]);
        }
        free(arr);
        free(stack);
    }
    else if (num == 3) {
        num1 = strlen(str[0]);
        num2 = strlen(str[1]);
        num3 = strlen(str[2]);

        // memory allocation & initialization
        int*** arr = (int***)malloc(sizeof(int**) * (num1 + 1));
        for (int i = 0; i <= num1; i++) {
            arr[i] = (int**)malloc(sizeof(int*) * (num2 + 1));
            for (int j = 0; j <= num2; j++) {
                arr[i][j] = (int*)malloc(sizeof(int) * (num3 + 1));
                for (int k = 0; k <= num3; k++) {
                    arr[i][j][k] = 0;
                }
            }
        }

        // finding maximal length of LCS
        for (int i = 1; i <= num1; i++) {
            for (int j = 1; j <= num2; j++) {
                for (int k = 1; k <= num3; k++) {
                    if ((str[0][i - 1] == str[1][j - 1]) && (str[1][j - 1] == str[2][k - 1])) arr[i][j][k] = arr[i - 1][j - 1][k - 1] + 1;
                    else arr[i][j][k] = MAX(MAX(arr[i - 1][j][k], arr[i][j - 1][k]), arr[i][j][k - 1]);
                }
            }
        }
        maxLen = arr[num1][num2][num3];

        // find LCS
        LCS = (char*)malloc(sizeof(char) * (maxLen + 1));
        stack = (char*)malloc(sizeof(char) * maxLen);
        stackSize = 0;

        // backtracking
        int var1, var2, var3, idx;
        var1 = num1;
        var2 = num2;
        var3 = num3;
        while((var1 != 0) && (var2 != 0) && (var3 != 0)) {
            if ((arr[var1][var2][var3] == (arr[var1 - 1][var2 - 1][var3 - 1] + 1)) && (str[0][var1 - 1] == str[1][var2 - 1]) && (str[1][var2 - 1] == str[2][var3 - 1])) {
                stack[stackSize++] = str[0][var1 - 1];
                var1--;
                var2--;
                var3--;
            }
            else if (MAX(MAX(arr[var1 - 1][var2][var3], arr[var1][var2 - 1][var3]), arr[var1][var2][var3 - 1]) == arr[var1 - 1][var2][var3]) {
                var1--;
            }
            else if (MAX(MAX(arr[var1 - 1][var2][var3], arr[var1][var2 - 1][var3]), arr[var1][var2][var3 - 1]) == arr[var1][var2 - 1][var3]) {
                var2--;
            }
            else {
                var3--;
            }
        }

        // make result
        for (int i = 0; i < maxLen; i++) {
            LCS[i] = stack[--stackSize];
        }
        LCS[maxLen] = '\0';

        // memory deallocation
        for (int i = 0; i <= num1; i++) {
            for (int j = 0; j <= num2; j++) {
                free(arr[i][j]);
            }
            free(arr[i]);
        }
        free(arr);
        free(stack);
    }
    else if (num == 4) {
        num1 = strlen(str[0]);
        num2 = strlen(str[1]);
        num3 = strlen(str[2]);
        num4 = strlen(str[3]);

        // memory allocation & initialization
        int**** arr = (int****)malloc(sizeof(int***) * (num1 + 1));
        for (int i = 0; i <= num1; i++) {
            arr[i] = (int***)malloc(sizeof(int**) * (num2 + 1));
            for (int j = 0; j <= num2; j++) {
                arr[i][j] = (int**)malloc(sizeof(int*) * (num3 + 1));
                for (int k = 0; k <= num3; k++) {
                    arr[i][j][k] = (int*)malloc(sizeof(int) * (num4 + 1));
                    for (int l = 0; l <= num4; l++) {
                        arr[i][j][k][l] = 0;
                    }
                }
            }
        }

        // finding maximal length of LCS
        for (int i = 1; i <= num1; i++) {
            for (int j = 1; j <= num2; j++) {
                for (int k = 1; k <= num3; k++) {
                    for (int l = 1; l <= num4; l++) {
                        if ((str[0][i - 1] == str[1][j - 1]) && (str[1][j - 1] == str[2][k - 1]) && (str[2][k - 1] == str[3][l - 1])) arr[i][j][k][l] = arr[i - 1][j - 1][k - 1][l - 1] + 1;
                        else arr[i][j][k][l] = MAX(MAX(arr[i - 1][j][k][l], arr[i][j - 1][k][l]), MAX(arr[i][j][k - 1][l], arr[i][j][k][l - 1]));
                    }
                }
            }
        }
        maxLen = arr[num1][num2][num3][num4];

        // find LCS
        LCS = (char*)malloc(sizeof(char) * (maxLen + 1));
        stack = (char*)malloc(sizeof(char) * maxLen);
        stackSize = 0;

        // backtracking
        int var1, var2, var3, var4, idx;
        var1 = num1;
        var2 = num2;
        var3 = num3;
        var4 = num4;
        while((var1 != 0) && (var2 != 0) && (var3 != 0) && (var4 != 0)) {
            if ((arr[var1][var2][var3][var4] == (arr[var1 - 1][var2 - 1][var3 - 1][var4 - 1] + 1)) && (str[0][var1 - 1] == str[1][var2 - 1]) && (str[1][var2 - 1] == str[2][var3 - 1]) && (str[2][var3 - 1] == str[3][var4 - 1])) {
                stack[stackSize++] = str[0][var1 - 1];
                var1--;
                var2--;
                var3--;
                var4--;
            }
            else if (MAX(MAX(arr[var1 - 1][var2][var3][var4], arr[var1][var2 - 1][var3][var4]), MAX(arr[var1][var2][var3 - 1][var4], arr[var1][var2][var3][var4 - 1])) == arr[var1 - 1][var2][var3][var4]) {
                var1--;
            }
            else if (MAX(MAX(arr[var1 - 1][var2][var3][var4], arr[var1][var2 - 1][var3][var4]), MAX(arr[var1][var2][var3 - 1][var4], arr[var1][var2][var3][var4 - 1])) == arr[var1][var2 - 1][var3][var4]) {
                var2--;
            }
            else if (MAX(MAX(arr[var1 - 1][var2][var3][var4], arr[var1][var2 - 1][var3][var4]), MAX(arr[var1][var2][var3 - 1][var4], arr[var1][var2][var3][var4 - 1])) == arr[var1][var2][var3 - 1][var4]) {
                var3--;
            }
            else {
                var4--;
            }
        }

        // make result
        for (int i = 0; i < maxLen; i++) {
            LCS[i] = stack[--stackSize];
        }
        LCS[maxLen] = '\0';

        // memory deallocation
        for (int i = 0; i <= num1; i++) {
            for (int j = 0; j <= num2; j++) {
                for (int k = 0; k <= num3; k++) {
                    free(arr[i][j][k]);
                }
                free(arr[i][j]);
            }
            free(arr[i]);
        }
        free(arr);
        free(stack);
    }
    else if (num == 5) {
        num1 = strlen(str[0]);
        num2 = strlen(str[1]);
        num3 = strlen(str[2]);
        num4 = strlen(str[3]);
        num5 = strlen(str[4]);

        // memory allocation & initialization
        int***** arr = (int*****)malloc(sizeof(int****) * (num1 + 1));
        for (int i = 0; i <= num1; i++) {
            arr[i] = (int****)malloc(sizeof(int***) * (num2 + 1));
            for (int j = 0; j <= num2; j++) {
                arr[i][j] = (int***)malloc(sizeof(int**) * (num3 + 1));
                for (int k = 0; k <= num3; k++) {
                    arr[i][j][k] = (int**)malloc(sizeof(int*) * (num4 + 1));
                    for (int l = 0; l <= num4; l++) {
                        arr[i][j][k][l] = (int*)malloc(sizeof(int) * (num5 + 1));
                        for(int m = 0; m <= num5; m++) {
                            arr[i][j][k][l][m] = 0;
                        }
                    }
                }
            }
        }

        // finding maximal length of LCS
        for (int i = 1; i <= num1; i++) {
            for (int j = 1; j <= num2; j++) {
                for (int k = 1; k <= num3; k++) {
                    for (int l = 1; l <= num4; l++) {
                        for (int m = 1; m <= num5; m++) {
                            if ((str[0][i - 1] == str[1][j - 1]) && (str[1][j - 1] == str[2][k - 1]) && (str[2][k - 1] == str[3][l - 1]) && (str[3][l - 1] == str[4][m - 1])) arr[i][j][k][l][m] = arr[i - 1][j - 1][k - 1][l - 1][m - 1] + 1;
                            else arr[i][j][k][l][m] = MAX(MAX(MAX(arr[i - 1][j][k][l][m], arr[i][j - 1][k][l][m]), MAX(arr[i][j][k - 1][l][m], arr[i][j][k][l - 1][m])), arr[i][j][k][l][m - 1]);
                        }
                    }
                }
            }
        }
        maxLen = arr[num1][num2][num3][num4][num5];

        // find LCS
        LCS = (char*)malloc(sizeof(char) * (maxLen + 1));
        stack = (char*)malloc(sizeof(char) * maxLen);
        stackSize = 0;

        // backtracking
        int var1, var2, var3, var4, var5, idx;
        var1 = num1;
        var2 = num2;
        var3 = num3;
        var4 = num4;
        var5 = num5;
        while((var1 != 0) && (var2 != 0) && (var3 != 0) && (var4 != 0) && (var5 != 0)) {
            if ((arr[var1][var2][var3][var4][var5] == (arr[var1 - 1][var2 - 1][var3 - 1][var4 - 1][var5 - 1] + 1)) && (str[0][var1 - 1] == str[1][var2 - 1]) && (str[1][var2 - 1] == str[2][var3 - 1]) && (str[2][var3 - 1] == str[3][var4 - 1]) && (str[3][var4 - 1] == str[4][var5 - 1])) {
                stack[stackSize++] = str[0][var1 - 1];
                var1--;
                var2--;
                var3--;
                var4--;
                var5--;
            }
            else if (MAX(MAX(MAX(arr[var1 - 1][var2][var3][var4][var5], arr[var1][var2 - 1][var3][var4][var5]), MAX(arr[var1][var2][var3 - 1][var4][var5], arr[var1][var2][var3][var4 - 1][var5])), arr[var1][var2][var3][var4][var5 - 1]) == arr[var1 - 1][var2][var3][var4][var5]) {
                var1--;
            }
            else if (MAX(MAX(MAX(arr[var1 - 1][var2][var3][var4][var5], arr[var1][var2 - 1][var3][var4][var5]), MAX(arr[var1][var2][var3 - 1][var4][var5], arr[var1][var2][var3][var4 - 1][var5])), arr[var1][var2][var3][var4][var5 - 1]) == arr[var1][var2 - 1][var3][var4][var5]) {
                var2--;
            }
            else if (MAX(MAX(MAX(arr[var1 - 1][var2][var3][var4][var5], arr[var1][var2 - 1][var3][var4][var5]), MAX(arr[var1][var2][var3 - 1][var4][var5], arr[var1][var2][var3][var4 - 1][var5])), arr[var1][var2][var3][var4][var5 - 1]) == arr[var1][var2][var3 - 1][var4][var5]) {
                var3--;
            }
            else if(MAX(MAX(MAX(arr[var1 - 1][var2][var3][var4][var5], arr[var1][var2 - 1][var3][var4][var5]), MAX(arr[var1][var2][var3 - 1][var4][var5], arr[var1][var2][var3][var4 - 1][var5])), arr[var1][var2][var3][var4][var5 - 1]) == arr[var1][var2][var3][var4 - 1][var5]) {
                var4--;
            }
            else {
                var5--;
            }
        }

        // make result
        for (int i = 0; i < maxLen; i++) {
            LCS[i] = stack[--stackSize];
        }
        LCS[maxLen] = '\0';

        // memory deallocation
        for (int i = 0; i <= num1; i++) {
            for (int j = 0; j <= num2; j++) {
                for (int k = 0; k <= num3; k++) {
                    for (int l = 0; l <= num4; l++) {
                        free(arr[i][j][k][l]);
                    }
                    free(arr[i][j][k]);
                }
                free(arr[i][j]);
            }
            free(arr[i]);
        }
        free(arr);
        free(stack);
    }
    else {
        return NULL;
    }

    return LCS;
}