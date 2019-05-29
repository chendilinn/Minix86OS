section bootsect vstart=0x7c00
LOADER_ADDR equ 0x7e00 ;loader.bin加载的物理地址
LOADER_SECT equ 1      ;loader.bin在硬盘中的起始扇区
LOADER_SIZE equ 120    ;loader.bin的大小,扇区(512byte)为单位 120*512 = 60Kb
start:
    mov ax,cs
    mov ds,ax
    mov es,ax
    mov ss,ax
    mov fs,ax
    mov sp,0x7c00
    mov ax,0xb800
    mov gs,ax       ;gs=vedio memory

    mov ax,0x0600
    mov bx,0x0700
    mov cx,0x0000
    mov dx,0x18f4
    int 0x10        ;清屏

    ;加载loader到LOADER_ADDR
    mov dx,0x1f2
    mov al,LOADER_SIZE  ;LOADER_SIZE个扇区数
    out dx,al

    mov dx,0x1f3
    mov al,LOADER_SECT
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

    mov cx,LOADER_SIZE*256  ;一次性两字节
    mov dx,0x1f0
    mov ax,LOADER_ADDR/16
    mov ds,ax
    mov bx,0
readw:
    in ax,dx
    mov [bx],ax
    add bx,2
    loop readw

    mov ax,LOADER_ADDR
    jmp ax          ;ip=cx=LOADER_ADDR
    times 510-($-$$) db 0
    db 0x55,0xaa
