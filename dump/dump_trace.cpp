#include <iostream>
#include <cstdio>
#include <execinfo.h>
#include <signal.h>
#include <cstdlib>

void dump_trace(int Signal)
{
    const int len = 200;
    void* buffer[len];
    int nptrs = ::backtrace(buffer, len);
    char** buffer_array = ::backtrace_symbols(buffer, nptrs);
    printf("sig:%d nptrs:%d\n", Signal, nptrs);
    if (buffer_array) {
        for (int i = 0; i < nptrs; ++i) {
            printf("line=%d||trace_back=%s||\n", i, buffer_array[i]);
        }
        free(buffer_array);
    }
    exit(1);
}

int regist_signal_handler()
{
	signal(SIGHUP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGTERM, SIG_IGN);

	// Dump traceback when crash.
	signal(SIGSEGV, dump_trace); // 11 Core  Invalid memory reference
	signal(SIGABRT, dump_trace); // 6  Core  Abort signal from abort(3)
	signal(SIGILL, dump_trace);  // 4  Core  Illegal Instruction
	signal(SIGFPE, dump_trace);  // 8  Core  Floating point exception
	return 0;
}


