#include <iostream>
#include <cstdio>
#include <execinfo.h>
#include <signal.h>
#include <cstdlib>
#include <vector>

struct CallInfo{
    void *caller_;
    void *point_;
    int cnt_;
    CallInfo() : caller_(NULL), point_(NULL), cnt_(0){}
    CallInfo(void *caller, void *point) : caller_(caller), point_(point), cnt_(1){}
    bool operator == (const CallInfo &x) const {
        return x.caller_ == caller_ && x.point_ == point_;
    }
};
class Stack {
    private:
    std::vector<CallInfo> call_list;
    int index_;
    size_t magic_number_;
    public:
    Stack(){
        index_ = 0;
        call_list.resize(256+1);
        magic_number_ = 0x123456780c0c0c0c;
    }
    CallInfo& Top() {
        if (magic_number_ == 0x123456780c0c0c0c) {
            return call_list[index_ - 1];
        } else {
            return call_list[0];
        }
    }

    void Push(const CallInfo &info) {
        if (magic_number_ == 0x123456780c0c0c0c) {
            if (index_  >=  call_list.size()) {
                printf("head stack overflow for too deep call stack with size of %d\n", index_);
                exit(-1);
            }
            if (info == Top()) {
                if (Top().cnt_ ++ >= 1024) {
                    printf("head stack overflow for recursive call\n");
                    exit(-2);
                }
            } else {
                call_list[index_++] = info;
            }
        }
    }
    void Pop() {
        if (magic_number_ == 0x123456780c0c0c0c) {
            if (--(Top().cnt_)  == 0) {
                index_ --;
            }
        }
    }
    bool Empty() {
        return magic_number_ == 0x123456780c0c0c0c && index_ == 0;
    }

};

Stack heap_stack;
int list_index = 0;
void dump_trace(int Signal)
{
#define SELF_TRACE 1
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
    int index = 0;
    printf("sig:%d \n", Signal);
    while (!heap_stack.Empty()) {
        const CallInfo &call_info = heap_stack.Top();
        heap_stack.Pop();
        printf("frame_%d: caller %p @ %p \n", index, call_info.caller_, call_info.point_);
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
    //DUMP(this_func, call_site);
    CallInfo info(this_func, call_site);
    heap_stack.Push(info);
    return ;
}

void __cyg_profile_func_exit(void *this_func, void *call_site)
{
    //DUMP(this_func, call_site);
    heap_stack.Pop();
    return ;
}
