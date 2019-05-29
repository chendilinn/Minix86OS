#ifndef LOADERC_H_
#define LOADERC_H_

typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned char uint8_t;
typedef char int8_t;

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
