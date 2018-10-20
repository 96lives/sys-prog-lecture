#include <stdio.h>
double gvar = 5;

int foo() {
    printf("foo has been called! gvar is %lf\n", gvar);
    gvar = 32143241533;
    printf("foo has been called! gvar is %lf\n", gvar);
}
