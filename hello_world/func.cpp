#include<stdio.h>
int b;
int bb = 1;
int bar(int i) {
   return i;
}
void func() {
    printf("In func %d\n", bar(1));
    return;
}
