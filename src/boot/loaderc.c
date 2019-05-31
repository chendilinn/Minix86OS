#include "printf.h"
#include "type.h"

void show_mem()
{
	init_cursor();
	ards_t *p_mem = (ards_t *)ards_buf;
	uint8_t num = *((uint8_t *)ards_num);
	printf("Memory distribution:\n");
	for(int i=0; i<num; i++) {
		if(1 == p_mem->type) {
			printf("base:0x%08x length:%08x(%dKb) available\n", p_mem->base_addr_low, p_mem->length_low, p_mem->length_low/1024, p_mem->type);
		}
		else {
			printf("base:0x%08x length:%08x(%dKb) Unavailable\n", p_mem->base_addr_low, p_mem->length_low, p_mem->length_low/1024, p_mem->type);
		}
		p_mem++;
	}
}

void init_page()
{
	//clear PDE
	printf("Initialize page table...\n");
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
	for(int i=0; i<1024; i++) {	//low 4M/4k = 1024
		page_table[i] = page_tmp;
		page_tmp += 4096;
	}

	// //create other kernel PDE
	// page_tmp = (PAGE_DIR_TABLE+0x2000) | PG_US_U | PG_RW_W | PG_P;
	// for(int i=769; i<1023; i++) {	//
	// 	page_dir_table[i] = page_tmp;
	// 	page_tmp += 4096;
	// }
	printf("Initialize page table completion\n");
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

void memcpy(uint8_t *src,uint8_t *dst,uint32_t size)
{
	while(size) {
		*dst++ = *src++;
		size--;
	}
}

void load_kernel()
{
	printf("Loading...\n");
	Elf32_Ehdr *pHeader = (Elf32_Ehdr *)KERNEL_ADDR;
	if(ET_EXEC != pHeader->e_type) {
		printf("Kernel is not an executable!");
		while(1);
	}

	uint16_t wPhSize = pHeader->e_phentsize; //一个程序表的大小，一般为20
	uint32_t dwPhOff = pHeader->e_phoff;	//第一个程序表的偏移
	uint16_t wPhnum = pHeader->e_phnum;		//程序表的个数
	for(uint16_t i=0; i<wPhnum; i++) {
		Elf32_Phdr *pPheader = (Elf32_Phdr *)(dwPhOff+KERNEL_ADDR);
		if(PT_LOAD != pPheader->p_type) {
			dwPhOff += wPhSize;
			continue;
		}
		uint8_t *pSrc = (uint8_t *)(pPheader->p_offset+KERNEL_ADDR);
		uint8_t *pDst = (uint8_t *)pPheader->p_vaddr;
		uint32_t dwSize = pPheader->p_filesz;
		memcpy(pSrc,pDst,dwSize);
		dwPhOff += wPhSize;
	}
	printf("The kernel is loaded and jumped into the kernel.\n");
}