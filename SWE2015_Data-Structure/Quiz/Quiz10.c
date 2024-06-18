#include <stdio.h>
#include <string.h>

int strnchar(char* s, char p);

int main() {
    char* string = "Hello this is answer of Quiz 10";
    char p = 's';
    printf("String: %s\nChar: %c\nOccurrences: %d\n", string, p, strnchar(string, p));

    return 0;
}

int strnchar(char* s, char p) {
    int result = 0;
    
    for (int i = 0 ; i < strlen(s) ; i++) {
        if (p == s[i]) result++;
    }
    
    return result;
}