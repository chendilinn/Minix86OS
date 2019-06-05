section .text
global ards_buf
global ards_num
extern init_page
extern show_mem
extern load_kernel
extern test_virtual_mem

KERNEL_ADDR equ 0x200000 ;kernel.elf加载的物理地址
PAGE_DIR_TABLE equ 0x400000
KERNEL_SECT equ 200      ;kernel.elf在硬盘中的起始扇区
KERNEL_SIZE equ 200     ;kernel.elf的大小,扇区(512byte)为单位 200*512 = 100kb

[bits 16]

_start:
	mov ax,cs	;get mem
    mov ds,ax
    mov es,ax
    xor ebx,ebx			;获取物理内存布局
    mov edx,0x534d4150
    mov di,ards_buf_	;将内存布局结构放入ards_buf_处
get_mem_loop:
    mov eax,0x0000e820
    mov ecx,0
    int 0x15
    jc get_mem_failed
    add di,cx
    inc byte [ards_num_]
    cmp ebx,0
    jnz get_mem_loop
    jmp get_mem_ok

get_mem_failed:
	mov byte [gs:0x00],'M'
	mov byte [gs:0x02],'E'
	;jmp $

get_mem_ok:

	in al,0x92 		;打开A20
	or al,0x02
	out 0x92,al

	lgdt [gdt_ptr]	;加载gdt

	cli

	mov eax,cr0
	or eax,0x01
	mov cr0,eax

	;jmp $

	jmp dword 0x0008:flush

[bits 32]
flush:

	;jmp $

	mov ax,0x0010
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov ax,0x0018
	mov ss,ax
	mov esp,0x7c00
	mov ebp,0
	mov ax,0x0020
	mov gs,ax

	call show_mem			;显示内存布局信息
	call read_kernel_to_mem	;将kerler.elf读入物理内存0x300000(3M)处
	call init_page			;初始化页表

	sgdt [gdt_ptr]			;开启分页

	mov eax,PAGE_DIR_TABLE
	mov cr3,eax

	mov eax,cr0
	or eax,0x80000000
	mov cr0,eax

	mov ebx,[gdt_ptr + 2]

	lgdt [gdt_ptr]

	;call test_virtual_mem	;测试分页是否成功
	call load_kernel		;此时kernel已经复制到物理0x300000(3M)处,load_kernel解析kernel.elf到0x100000处

	jmp 0x0008:0xc0100000	;转到kernel

read_kernel_to_mem:
    mov dx,0x1f2
    mov al,KERNEL_SIZE  ;LOADER_SIZE个扇区数
    out dx,al

    mov dx,0x1f3
    mov al,KERNEL_SECT
    out dx,al           ;LAB addr 0~7

    inc dx
    mov al,0x00         ;LAB addr 8~15
    out dx,al

    inc dx
    mov al,0x00         ;LAB addr 16~23
    out dx,al

    inc dx
    mov al,0xe0         ;LAB模式，主硬盘，LAB addr 24~27
    out dx,al

    mov dx,0x1f7        ;请求读
    mov al,0x20
    out dx,al

    mov dx,0x1f7
waits:
    in al,dx
    and al,0x88
    cmp al,0x08
    jnz waits

    mov ecx,200*256  ;一次性两字节
    mov dx,0x1f0
    mov ebx,KERNEL_ADDR	;加载地址(3M)
readw:
    in ax,dx
    mov [ebx],ax
    add ebx,2
    loop readw
    ret

align 16

ards_buf:
	dd ards_buf_
ards_num:
	dd ards_num_

ards_buf_:
	times 200 db 0
ards_num_:
	db 0

align 16
gdt_base:
	dq 0x0000000000000000	;0号描述符，空
	dq 0x00cf98000000ffff	;code segment,0~4G,0x0008
	dq 0x00cf92000000ffff	;data segment,0~4G,0x0010
	dq 0x0040960000000000	;stack segment,0~4G,0x0018
	dq 0x00c0920b80000007	;vedio segment,32k,0x0020
gdt_end:
	times 60 dq 0	;保留60个GDT位置
gdt_ptr:
	dw gdt_end-gdt_base-1
	dd gdt_base
