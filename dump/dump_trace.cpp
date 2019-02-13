#include <iostream>
#include <cstdio>
#include <execinfo.h>
#include <signal.h>
#include <cstdlib>
#include <string>
#include "lstack.h"


Lstack<std::string> call_list(40);

void dump_trace(int Signal)
{
/* #define SELF_TRACE 1 */
#ifndef SELF_TRACE
    const int len = 200;
    void* buffer[len];
    printf("dump_trace\n");
    int nptrs = ::backtrace(buffer, len);
    printf("backtrace\n");
    char** buffer_array = ::backtrace_symbols(buffer, nptrs);
    printf("sig:%d nptrs:%d\n", Signal, nptrs);
    if (buffer_array) {
        for (int i = 0; i < nptrs; ++i) {
            printf("line=%d||trace_back=%s||\n", i, buffer_array[i]);
        }
        free(buffer_array);
    }
#else
	std::string content;
	int index = 0;
	while (!call_list.empty()) {
        content = call_list.top();
        call_list.pop();
		std::cout << "frame_" << index << ": "<< content << std::endl;
		index ++;
	}
#endif
    exit(0);
}

int regist_signal_handler()
{
	signal(SIGSEGV, dump_trace); // 11 Core  Invalid memory reference
	signal(SIGABRT, dump_trace); // 6  Core  Abort signal from abort(3)
	signal(SIGILL, dump_trace);  // 4  Core  Illegal Instruction
	signal(SIGFPE, dump_trace);  // 8  Core  Floating point exception
	return 0;
}


#define DUMP(func, call_site) \
	printf("%s: func = %p, called at = %p\n", __FUNCTION__, func, call_site)


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
	/* DUMP(this_func, call_site); */
	char buffer[64] = {0};
	int len = snprintf(buffer, 60, "%p call %p", this_func, call_site);
	std::string content = std::string(buffer);
	call_list.push(content);
	return ;
}

void __cyg_profile_func_exit(void *this_func, void *call_site)
{
	/* DUMP(this_func, call_site); */
	return ;
}
