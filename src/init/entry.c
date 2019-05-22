/*
 * =====================================================================================
 *
 *       Filename:  entry.c
 *
 *    Description:  hurlex 内核的入口函数
 *
 *        Version:  1.0
 *        Created:  2013年10月31日 13时31分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "console.h"
#include "debug.h"
#include "mm.h"

int kern_entry()
{
	init_debug();

	console_clear();

	show_memory_map();

	printk("cdkernel in memory start: 0x%08X\n", kern_start);
	printk("cdkernel in memory end:   0x%08X\n", kern_end);
	printk("cdkernel in memory used:   %d KB\n\n", (kern_end - kern_start) / 1024);

	return 0;
}

