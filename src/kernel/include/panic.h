#ifndef _PANIC_H
#define _PANIC_H
#include <printk.h>

#define panic(format, ...) \
{ \
    printk("******Kernel panic:******\n%s %d\n" format "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    while(1); \
}

#define assert(condition) \
		if(!(condition)) { \
			panic(#condition); \
		}

#ifdef NDEBUG
	#define log(format, ...) ((void)0)
#else
	#define log(format, ...) \
	{ \
	    printk("%s\t%d\t%s\t" format "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
	}
#endif

#endif
