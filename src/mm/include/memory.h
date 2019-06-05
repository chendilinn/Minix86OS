#ifndef _MEMORY_H
#define _MEMORY_H
#include <types.h>
#include <bitmap.h>

/* 用于虚拟地址管理 */
typedef struct virtual_addr {
   bitmap vaddr_bitmap; // 虚拟地址用到的位图结构
   uint32_t vaddr_start;       // 虚拟地址起始地址
}virtual_addr;

/* 内存池结构,生成两个实例用于管理内核内存池和用户内存池 */
typedef struct mm_pool {
   bitmap pool_bitmap;	 // 本内存池用到的位图结构,用于管理物理内存
   uint32_t phy_addr_start;	 // 本内存池所管理物理内存的起始地址
   uint32_t pool_size;		 // 本内存池字节容量
}mm_pool;

enum pool_flags {
	PF_KERNEL = 0,
	PF_USER,
}

extern mm_pool kernel_pool, user_pool;
void mem_init(void);

#endif
