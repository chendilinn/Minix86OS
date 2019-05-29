#include "loaderc.h"

static uint16_t *video_memory = (uint16_t *)0xb8000;
static uint16_t pos_x = 0; //equ 0 can use bss seg,
static uint16_t pos_y = 0;

void console_putc(char c)
{
	if (c == '\n') {
		pos_x = 0;
		pos_y++;
	} else if (c >= ' ') {
		video_memory[pos_y*80 + pos_x] = 0x0700 | c;
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
	ards_t *p_mem = ards_buf;
	ards_t *p_mem1 = (ards_t *)0x1234;
	uint8_t num = *ards_num;
	//console_puthex((uint32_t)p_mem1);
	console_puts("\nmemory map:\n");
	for(int i=0; i<num; i++) {
		console_puts("base: 0x");
		console_puthex(p_mem->base_addr_high);
		console_puthex(p_mem->base_addr_low);
		console_puts(" size:0x");
		console_puthex(p_mem->base_addr_high);
		console_puthex(p_mem->base_addr_low);
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
}
