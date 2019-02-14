#ifndef __DUMP_TRACE_H__
#define __DUMP_TRACE_H__

#include <string>
#include <stack>
extern std::stack<std::string> call_list;
void dump_trace(int Signal);
int regist_signal_handler();

#endif
