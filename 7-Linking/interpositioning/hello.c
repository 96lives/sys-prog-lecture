#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

int main() {
    free(malloc(10));
    printf("hello, world\n");
    exit(0);
}
