#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define LEN 4
#define EXEFILE "bt"
size_t main_addr = 0x7f0000000000;
int backtrace_m()
{
       int i = 0;
       size_t rbp = 0;
       size_t rip = 0;
       char cmd[64];
	   void *addrbuffer;
       __asm__ __volatile__("mov %%rbp, %0" \
              :"=g"(rbp)
              :
			  :"memory"
       );
 
       for(i = 0; i < 16; i++)
       {
              rip  = (size_t)((size_t*)rbp + 1);//rip pointer.
              rip = *(size_t*)rip;//rip value
			  if (rip > main_addr)
				  break;
              rbp = *(size_t*)rbp;//rbp vlaue
              addrbuffer = (void*)rip;
 
              fprintf(stderr, "%p -> ", addrbuffer);
              memset(cmd, 0, sizeof(cmd));
              sprintf(cmd, "addr2line %p -e ", addrbuffer);
              strncat(cmd, EXEFILE, strlen(EXEFILE));
              system(cmd);
       }
 
       return 4;
}
 
static void test2(void)
{
       int i = 0;
       backtrace_m();
       return;
}
 
static void test1(void)
{
       test2();
}
 
static void test(void)
{
       test1();
}
 
int main(int argc, char *argv[])
{
       test();
       return 0;
}
