#include <timer.h>
#include <console.h>
#include <idt.h>
#include <panic.h>
#include <printk.h>

void init_all()
{
	init_cursor();
	idt_init();
	timer_init();
}

int kernel_main()
{
	init_all();
	log("kernel init done: id=%ld",123456);
	assert(1==2);
	asm volatile ("sti");
	while(1);
}
