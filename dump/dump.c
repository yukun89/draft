/* #include <cstdio> */
/* #include <string> */
#include <stdio.h>

#define DUMP(func, call) \
	printf("%s: func = %p, called by = %p\n", __FUNCTION__, func, call)

void __attribute__((no_instrument_function))
__cyg_profile_func_enter(void *this_func, void *call_site)
{
	/* DUMP(this_func, call_site); */
	char buffer[32] = {0};
	int len = snprintf(buffer, 20, "%p", call_site);
	/* std::string content = std::string(buffer); */
}

void __attribute__((no_instrument_function))
__cyg_profile_func_exit(void *this_func, void *call_site)
{
	/* DUMP(this_func, call_site); */
}
