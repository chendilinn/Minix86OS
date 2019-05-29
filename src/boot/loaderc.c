#include "loaderc.h"

static uint16_t *video_memory = (uint16_t *)0xb8000;
static uint16_t pos_x = 1; //不初始化为0是因为，为0的全局变量在bss段中，链接为二进制文件时，bss段就没了
static uint16_t pos_y = 1;

void console_putc(char c)
{
	if (c == '\n') {
		pos_x = 1;
		pos_y++;
	} else if (c >= ' ') {
		video_memory[(pos_y-1)*80 + (pos_x-1)] = 0x0700 | c;
		pos_x++;
	}
}

void console_puthex(uint32_t n)
{
	int tmp;
	char noZeroes = 1;

	//console_puts("0x");

	int i;
	for (i = 28; i >= 0; i -= 4) {
		tmp = (n >> i) & 0xF;
		if (tmp == 0 && noZeroes != 0) {
		      continue;
		}
		noZeroes = 0;
		if (tmp >= 0xA) {
		      console_putc(tmp-0xA+'a');
		} else {
		      console_putc(tmp+'0');
		}
	}
}

void console_putdec(uint32_t n)
{
	if (n == 0) {
		console_putc('0');
		return;
	}

	uint32_t acc = n;
	char c[32];
	int i = 0;
	while (acc > 0) {
		c[i] = '0' + acc % 10;
		acc /= 10;
		i++;
	}
	c[i] = 0;

	char c2[32];
	c2[i--] = 0;

	int j = 0;
	while(i >= 0) {
	      c2[i--] = c[j++];
	}

	console_puts(c2);
}

void console_puts(char *str)
{
	while(*str) {
		console_putc(*str++);
	}
}

void show_mem()
{
	ards_t *p_mem = (ards_t *)ards_buf;
	uint8_t num = *((uint8_t *)ards_num);
	console_puts("memory map:\n");
	for(int i=0; i<num; i++) {
		console_puts("base: 0x");
		console_puthex(p_mem->base_addr_high);
		console_puthex(p_mem->base_addr_low);
		console_puts(" size:0x");
		console_puthex(p_mem->length_high);
		console_puthex(p_mem->length_low);
		console_puts(" type:");
		console_putdec(p_mem->type);
		console_puts("\n");
		p_mem++;
	}
}

void loader_main()
{
	//console_puts("start loader\n");
	show_mem();
	//console_putc('5');

	// ards_t *p_mem = (ards_t *)ards_buf;
	// uint32_t a = (uint32_t)p_mem;
	// uint8_t num = *((uint8_t *)ards_num);
	// console_puthex(ards_buf);
	// console_putc('\n');
	// console_puthex(ards_num);
}
