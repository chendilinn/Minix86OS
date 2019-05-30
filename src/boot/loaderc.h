#ifndef LOADERC_H_
#define LOADERC_H_

#define PAGE_DIR_TABLE 0x10000
#define PG_US_U	0x04
#define PG_US_S	0x00
#define PG_RW_R	0x00
#define PG_RW_W	0x02
#define PG_P	0x01

typedef signed int 		int32_t;
typedef signed short 	int16_t;
typedef signed char 	int8_t;
typedef unsigned int 	uint32_t;
typedef unsigned short 	uint16_t;
typedef unsigned char 	uint8_t;

typedef
struct ards_t{
	uint32_t base_addr_low;
	uint32_t base_addr_high;
	uint32_t length_low;
	uint32_t length_high;
	uint32_t type;
} __attribute__((packed)) ards_t;

extern ards_t *ards_buf;
extern uint8_t *ards_num;

void console_putc(char c);
void console_puthex(uint32_t n);
void console_putdec(uint32_t n);
void console_puts(char *str);
void show_mem();

#endif
