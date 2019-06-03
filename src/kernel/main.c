#include <timer.h>
#include <console.h>
#include <idt.h>
#include <panic.h>
#include <printk.h>
#include <memory.h>

char a[1024];
char b[1024];

void init_all()
{
	init_cursor();
	idt_init();
	timer_init();
}

int kernel_main()
{
	init_all();
	mem_init();
	//asm volatile ("sti");
	while(1);
}
