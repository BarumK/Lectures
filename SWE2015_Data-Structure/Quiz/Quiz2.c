#include <stdio.h>

void main (void) {
    int x, y, z;
    printf("input integer x, y, z: ");
    scanf("%d %d %d", &x, &y, &z);
    
    if (x > y) {
        if (z > x)
            printf("%d %d %d", y, x, z);
        else if (y > z)
            printf("%d %d %d", z, y, x);
        else // z는 x와 y 사이에 존재
            printf("%d %d %d", y, z, x);
    }
    else{ // y > x
        if (z > y)
            printf("%d %d %d", x, y, z);
        else if (x > z)
            printf("%d %d %d", z, x, y);
        else // z는 x와 y 사이에 존재
            printf("%d %d %d", x, z, y);
    }
}