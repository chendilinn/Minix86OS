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

	int i;
	for (i = 28; i >= 0; i -= 4) {
		tmp = (n >> i) & 0xF;
		if (tmp == 0 && noZeroes != 0) {
			console_putc(tmp+'0');
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
	console_puts("Memory distribution:\n");
	for(int i=0; i<num; i++) {
		console_puts("base: 0x");console_puthex(p_mem->base_addr_low);
		console_puts(" size:0x");console_puthex(p_mem->length_low);console_puts("(");console_putdec(p_mem->length_low/1024);console_puts("Kb)");
		console_puts(" type:");console_putdec(p_mem->type);console_puts("\n");
		p_mem++;
	}
}

void init_page()
{
	//clear PDE
	uint32_t *page_dir_table = (uint32_t *)PAGE_DIR_TABLE;
	for(int i=0; i<4096; i++) {
		page_dir_table[i] = 0;
	}
	//create PDE
	page_dir_table[0] = (PAGE_DIR_TABLE+0x1000) | PG_US_U | PG_RW_W | PG_P; //virtuala address 0x0~0x3fffff(4M) --- Physical address 0x0~0x3fffff(4M)

	page_dir_table[768] = (PAGE_DIR_TABLE+0x1000) | PG_US_U | PG_RW_W | PG_P; //virtuala address 0xc0000000~0xc03fffff(4M) --- Physical address 0x0~0x3fffff(4M)

	page_dir_table[1023] = PAGE_DIR_TABLE | PG_US_U | PG_RW_W | PG_P;//The last one, point to self(PDE)

	//create PTE
	uint32_t *page_table = (uint32_t *)(PAGE_DIR_TABLE+0x1000);
	uint32_t page_tmp = PG_US_U | PG_RW_W | PG_P;
	for(int i=0; i<256; i++) {	//low 1M/4k = 256
		page_table[i] = page_tmp;
		page_tmp += 4096;
	}

	// //create other kernel PDE
	// page_tmp = (PAGE_DIR_TABLE+0x2000) | PG_US_U | PG_RW_W | PG_P;
	// for(int i=769; i<1023; i++) {	//
	// 	page_dir_table[i] = page_tmp;
	// 	page_tmp += 4096;
	// }
}

void test_virtual_mem()
{
	uint16_t *virtual = (uint16_t *)0xc00b8000;
	virtual[0] = 0x0735; //'5'
	virtual[1] = 0x0734; //'4'
	virtual[2] = 0x0733; //'3'
	virtual[3] = 0x0732; //'2'
	virtual[4] = 0x0731; //'1'
}

void loader_main()
{
	show_mem();
	init_page();
}
