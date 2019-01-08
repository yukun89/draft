#include "lstack.h"
#include "dump_trace.h"
#include <cstdio>

int do_multi(int a, int b)
{
	int *p = NULL;
	a = *p;
	return a * b;
}
 
 
int do_calc(int a, int b)
{
	return do_multi(a, b);
}

int main()
{
	printf("server start\n");
	regist_signal_handler();
	int a = 4, b = 5;
	printf("result: %d\n", do_calc(a, b));
	return 0;
}
