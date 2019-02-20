#include"func.h"
int func(int a) {
    return a + global_b + global_c;
}

int bar(int a) {
    return a + global_b + global_c;
}
