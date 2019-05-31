#ifndef TYPE_H_
#define TYPE_H_

typedef signed int 		int32_t;
typedef signed short 	int16_t;
typedef signed char 	int8_t;
typedef unsigned int 	uint32_t;
typedef unsigned short 	uint16_t;
typedef unsigned char 	uint8_t;

/*页属性*/
#define PAGE_DIR_TABLE 0x10000
#define PG_US_U	0x04
#define PG_US_S	0x00
#define PG_RW_R	0x00
#define PG_RW_W	0x02
#define PG_P	0x01

/*物理内存布局数据结构*/
typedef struct ards_t{
	uint32_t base_addr_low;
	uint32_t base_addr_high;
	uint32_t length_low;
	uint32_t length_high;
	uint32_t type;
} __attribute__((packed)) ards_t;

extern ards_t *ards_buf;
extern uint8_t *ards_num;

/*elf文件数据结构*/
#define KERNEL_ADDR 0x300000
typedef unsigned short 	Elf32_Half;
typedef unsigned int 	Elf32_Word;
typedef unsigned int 	Elf32_Addr;
typedef unsigned int 	Elf32_Off;

#define ET_EXEC 2  //可执行文件？
#define EM_386	3  //Intel 80386?
typedef struct Elf32_Ehdr{
	unsigned char e_ident[16];
	Elf32_Half	  e_type;
	Elf32_Half	  e_machine;
	Elf32_Word	  e_version;
	Elf32_Addr	  e_entry;
	Elf32_Off	  e_phoff;
	Elf32_Off	  e_shoff;
	Elf32_Word	  e_flags;
	Elf32_Half	  e_ehsize;
	Elf32_Half	  e_phentsize;
	Elf32_Half	  e_phnum;
	Elf32_Half	  e_shentsize;
	Elf32_Half	  e_shnum;
	Elf32_Half	  e_shstrndx;
} __attribute__((packed)) Elf32_Ehdr;

//段类型
#define PT_NULL 0 //忽略
#define PT_LOAD 1 //可加载程序段?
typedef struct Elf32_Phdr{
	Elf32_Word	  p_type;
	Elf32_Off	  p_offset;
	Elf32_Addr	  p_vaddr;
	Elf32_Addr	  p_paddr;
	Elf32_Word	  p_filesz;
	Elf32_Word	  p_memsz;
	Elf32_Word	  p_flags;
	Elf32_Word	  p_align;
} __attribute__((packed)) Elf32_Phdr;

#endif