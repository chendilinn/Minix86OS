#include <memory.h>
#include <printk.h>

#define PG_SIZE 4096

#define MEM_BITMAP_BASE 0xc0300000

#define K_HEAP_START 0xc0800000 //kernel virtual start address

#define PDE_IDX(addr) ((addr & 0xffc00000) >> 22)
#define PTE_IDX(addr) ((addr & 0x003ff000) >> 12)

mm_pool kernel_pool, user_pool;      // 生成内核内存池和用户内存池
virtual_addr kernel_vaddr;	 // 此结构是用来给内核分配虚拟地址

/*初始化内存池*/
static void mem_pool_init(uint32_t all_mem) {
   uint32_t used_mem = 0x800000;	  // 0x400000为低端4M内存
   uint32_t free_mem = all_mem - used_mem;
   uint16_t all_free_pages = free_mem / PG_SIZE;		  // 1页为4k,不管总内存是不是4k的倍数,
   uint16_t kernel_free_pages = all_free_pages / 2;
   uint16_t user_free_pages = all_free_pages - kernel_free_pages;

   uint32_t kbm_length = kernel_free_pages / 8;			  // Kernel BitMap的长度,位图中的一位表示一页,以字节为单位
   uint32_t ubm_length = user_free_pages / 8;			  // User BitMap的长度.

   uint32_t kp_start = used_mem;				  // Kernel Pool start,内核内存池的起始地址
   uint32_t up_start = kp_start + kernel_free_pages * PG_SIZE;	  // User Pool start,用户内存池的起始地址

   kernel_pool.phy_addr_start = kp_start;
   user_pool.phy_addr_start   = up_start;

   kernel_pool.pool_size = kernel_free_pages * PG_SIZE;
   user_pool.pool_size	 = user_free_pages * PG_SIZE;

   kernel_pool.pool_bitmap.btmp_bytes_len = kbm_length;
   user_pool.pool_bitmap.btmp_bytes_len	  = ubm_length;

   kernel_pool.pool_bitmap.bits = (void*)MEM_BITMAP_BASE;

   user_pool.pool_bitmap.bits = (void*)(MEM_BITMAP_BASE + kbm_length);

   bitmap_init(&kernel_pool.pool_bitmap);
   bitmap_init(&user_pool.pool_bitmap);

   kernel_vaddr.vaddr_bitmap.btmp_bytes_len = kbm_length;
   kernel_vaddr.vaddr_bitmap.bits = (void*)(MEM_BITMAP_BASE + kbm_length + ubm_length);
   kernel_vaddr.vaddr_start = K_HEAP_START;

   bitmap_init(&kernel_vaddr.vaddr_bitmap);

   printk("kernel_pool_bitmap_start:0x%x ", (int)kernel_pool.pool_bitmap.bits);
   printk("kernel_pool_phy_addr_start:0x%x\n", kernel_pool.phy_addr_start);
   printk("user_pool_bitmap_start:0x%x ", (int)user_pool.pool_bitmap.bits);
   printk("user_pool_phy_addr_start:0x%x\n", user_pool.phy_addr_start);
   printk("kernel_vaddr.vaddr_bitmap.bits:0x%x ", (int)kernel_vaddr.vaddr_bitmap.bits);
   printk("kernel_vaddr.vaddr_start:0x%x\n", kernel_vaddr.vaddr_start);
}

static void *vaddr_get(pool_flags pf, uint32_t pg_cnt)
{
   int vaddr_start = 0, bit_idx_start = -1;
   uint32_t cnt = 0;
   if(pf == PF_KERNEL) { //Kernel application virtual address
      bit_idx_start = bitmap_scan(&kernel_vaddr.vaddr_bitmap, pg_cnt);
      if(-1 == bit_idx_start) {
         return NULL;
      }
      while(cnt < pg_cnt) {
         bitmap_set(&kernel_vaddr.vaddr_bitmap, bit_idx_start + cnt, 1);
         cnt++;
      }
   }
   else {
      //User application virtual address
   }
   vaddr_start = kernel_vaddr.vaddr_start + bit_idx_start*PG_SIZE;
   return (void *)vaddr_start;
}

uint32_t *pte_ptr(uint32_t vaddr) {
   //((vaddr & 0xffc00000) >> 10)用于索引页目录项,PTE_IDX(vaddr) * 4用于索引页表项 0x12345678
   //0001001000 1101000101 678 //0xffc048d04
   uint32_t *pte = (uint32_t *)(0xffc00000 + ((vaddr & 0xffc00000) >> 10) + PTE_IDX(vaddr) * 4);
   return pte;
}

uint32_t *pde_ptr(uint32_t vaddr) {

}

static void *palloc(mm_pool *m_pool) {

}

void mem_init() {
   uint32_t mem_bytes_total = 30*1024*1024; //30M
   mem_pool_init(mem_bytes_total);
}
