#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pmatch (char* string, char* pat, int* failure);
void fail (char* pat, int* failure);

int main() {
    char* myString = "asdfgkqwerjdoqiotepwowrepqwor";
    char* myPattern = "pwowre";
    int* myFailure = (int*) malloc(sizeof(int) * strlen(myPattern));
    
    fail(myPattern, myFailure);
    printf("String: %s\nPattern: %s\nStarting index: %d\n", myString, myPattern, pmatch(myString, myPattern, myFailure));

    return 0;
}

int pmatch (char* string, char* pat, int* failure) {
    int i = 0; int j = 0;
    int lens = strlen(string); int lenp = strlen(pat);
    
    for ( ; i < lens && j < lenp ; ) {
        if (string[i] == pat[j]) { i++; j++; }
        else if (j == 0) i++;
        else j = failure[j - 1] + 1;
    }
    return (j == lenp ? i - lenp : -1);
}

void fail (char *pat, int* failure) {
    int i, j;
    int n = strlen(pat);
    failure[0] = -1;
    for (j = 1 ; j < n ; j++){
        i = failure[j - 1];
        while (pat[j] != pat[i + 1] && i >= 0)
            i = failure[i];
        if (pat[j] == pat[i + 1]) failure[j] = i + 1;
        else failure[j] = -1;
    }
}
