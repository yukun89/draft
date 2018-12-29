#include <iostream>
#include <cstdio>
#include <execinfo.h>
#include <signal.h>
#include <cstdlib>
class Base{

public:
void a()
{
   char *p = nullptr;
	*p=0;
}

void b(){
	a();
}
};

void DumpTraceback(int Signal)
{
    const int len = 200;
    void* buffer[len];
    int nptrs = ::backtrace(buffer, len);
    char** strings = ::backtrace_symbols(buffer, nptrs);
    printf("sig:%d nptrs:%d\n", Signal, nptrs);
    if (strings) {
        for (int i = 0; i < nptrs; ++i) {
            printf("line=%d||trace_back=%s||\n", i, strings[i]);
        }
        free(strings);
    }
    exit(1);
}

    int SigHandle()
{
	//signal(SIGINT, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	//signal(SIG_DATA_LOAD, SIG_IGN);

	// Dump traceback when crash.
	// Core signal's default action is to terminate the process and dump core.
	//signal(SIGBUS, DumpTraceback);  // 10 Core  Bus error (bad memory access)
	signal(SIGSEGV, DumpTraceback); // 11 Core  Invalid memory reference
	signal(SIGABRT, DumpTraceback); // 6  Core  Abort signal from abort(3)
	signal(SIGILL, DumpTraceback);  // 4  Core  Illegal Instruction
	signal(SIGFPE, DumpTraceback);  // 8  Core  Floating point exception
	return 0;
}

int main()

{
    Base test;
	SigHandle();
   test.b();
    return 0;
}

