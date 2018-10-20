#include <stdio.h>

int gvar;
int gvar2=1;
extern void foo();

int main() {
    foo();
    printf("gvar is %d\n", gvar);
    printf("gavr2 is %d\n", gvar2);
    return 0;
}
