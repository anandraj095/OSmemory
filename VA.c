#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argcv[]) {
    printf("Location of code : %p\n", main);
    printf("Location of heap1 : %p\n", malloc(100e6));
    printf("Location of heap2 : %p\n", malloc(100e6));
    int x = 3; int y = 4;
    printf("Location of stack : %p, %p\n", &x, &y);

    return x;
}