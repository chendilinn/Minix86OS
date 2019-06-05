#ifndef INCLUDE_TYPES_H_
#define INCLUDE_TYPES_H_

typedef signed int 			int32_t;
typedef signed short 		int16_t;
typedef signed char 		int8_t;
typedef signed long long 	int64_t;
typedef unsigned int 		uint32_t;
typedef unsigned short 		uint16_t;
typedef unsigned char 		uint8_t;
typedef unsigned long long 	uint64_t;

#define NULL 0

#define PAGE_DIR_TABLE 0x400000
#define PG_US_U	0x04
#define PG_US_S	0x00
#define PG_RW_R	0x00
#define PG_RW_W	0x02
#define PG_P_1	0x01
#define PG_P_0	0x01

#endif