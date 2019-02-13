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

void fun(int n)
{
    printf("The %d step begin.\n", n);
    int a[10];
    for (int i = 0; i< n; i++) {
        a[i] = i;
    }
    if (n < 20) {
        fun(n +1);
    }
    printf("The %d step end\n", n);
    return ;
}

int main()
{
	printf("server start\n");
	regist_signal_handler();
	int a = 4, b = 5;
	/* printf("result: %d\n", do_calc(a, b)); */
    fun(8);
	return 0;
}
