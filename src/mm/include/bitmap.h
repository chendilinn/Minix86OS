#ifndef _BITMAP_H
#define _BITMAP_H

#include <types.h>

#define BITMAP_MASK 1
typedef struct bitmap{
	uint32_t btmp_bytes_len;
	uint8_t* bits;
}bitmap;

void bitmap_init();
int bitmap_scan_test(bitmap *btmp, uint32_t bit);
int bitmap_scan(bitmap *btmp, uint32_t cnt);
void bitmap_set(bitmap *btmp, uint32_t bit, uint8_t value);

#endif