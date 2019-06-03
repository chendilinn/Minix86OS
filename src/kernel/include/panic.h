#ifndef _PANIC_H
#define _PANIC_H

#define log(format, ...) \
{ \
    printk("%s %d " format "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
}

#define panic(format, ...) \
{ \
    printk("******Kernel panic:******\n%s %d\n" format "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    while(1); \
}

#ifdef NDEBUG
	#define assert(condition) ((void)0)
#else
	#define assert(condition) \
	if(!(condition)) { \
		panic(#condition); \
	}
#endif

#endif
