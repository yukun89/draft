#include <iostream>
#include <cstdio>
#include <execinfo.h>
#include <signal.h>
#include <cstdlib>
#include <string>
#include "lstack.h"


Lstack<std::string> call_list(10);

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
	/* std::string content; */
	/* int index = 0; */
	/* while (call_list.pop(content) ) { */
	/* 	std::cout << "frame" << index << ":"<< content << std::endl; */
	/* 	index ++; */
	/* } */
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


#define DUMP(func, call) \
	printf("%s: func = %p, called by = %p\n", __FUNCTION__, func, call)


#ifdef __cplusplus
extern "C" {
#endif

void __attribute__((no_instrument_function))
__cyg_profile_func_enter(void *this_func, void *call_site);

void __attribute__((no_instrument_function))
__cyg_profile_func_exit(void *this_func, void *call_site);

#ifdef __cplusplus
};
#endif

void __cyg_profile_func_enter(void *this_func, void *call_site)
{
	DUMP(this_func, call_site);
	char buffer[32] = {0};
	int len = snprintf(buffer, 20, "%p", call_site);
	std::string content = std::string(buffer);
	/* call_list.push(content); */
	return ;
}

void __cyg_profile_func_exit(void *this_func, void *call_site)
{
	DUMP(this_func, call_site);
	return ;
}
