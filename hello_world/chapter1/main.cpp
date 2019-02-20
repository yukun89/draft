#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "func.h"
int global_b = 1;
const int global_c = 1;
int global_d[10];
static int global_e[10];

int main(){
    static char *p = "Begin printf ";
    int *ip = (int *)malloc(4);
    *ip = 1;
    global_b = func(*ip);
    printf("%s the value of func is %d\n", p, func(1));
    return global_b + global_c;
}
