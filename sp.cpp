#include <cstdio>
#include "asp.h"
unsigned long get_sp(void){
	__asm__("movl %esp,%eax");
}
int a = 100; 
namespace One{
class Str{
public:
	int run(){return 200;}
	int uniq_run(){};
};
}
using namespace Two;
using namespace One;
int main(){
	One::Str s;
	printf("%d\n", s.run());
	printf("0x%x\n",get_sp());
	return 0;
}

