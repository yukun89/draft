#include <stdio.h>
#include "func.h"

class MyClass{
    public:
        MyClass(){
            a_ = -1;
        };
        int a_;
};

MyClass the;
int a = 1;

int main(){
    func();
    printf("the value of the.a is %d, a is %d\n", the.a_, a);
}
