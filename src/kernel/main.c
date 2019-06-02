#include <timer.h>
#include <console.h>
#include <interrupt.h>
#include <printk.h>

void init_all()
{
	init_cursor();
	printk("I am kernel! \n");
	idt_init();
	timer_init();
}

int kernel_main()
{
	init_all();
	asm volatile ("sti");
	while(1);
}