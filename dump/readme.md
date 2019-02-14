## option 1 使用backtrace进行函数调用栈的追踪
* 注释掉 `dump_trace.cpp` 中的`SELF_TRACE`宏定义
* 使用`make -f Makefile.simple`编译程序

## option 2 用户自己定义函数调用栈
* 打开 `dump_trace.cpp` 中的`SELF_TRACE`宏定义
* 使用`make `编译程序
