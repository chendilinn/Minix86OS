section .text
[extern loader_main]

[bits 16]

_start:

	jmp loader_start

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

loader_start:

	in al,0x92 		;打开A20
	or al,0x02
	out 0x92,al

	lgdt [gdt_ptr]	;加载gdt

	cli

	mov byte [gs:0x00],'B'

	mov eax,cr0
	or eax,0x01
	mov cr0,eax

	jmp dword 0x0008:flush

[bits 32]
flush:

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

	call loader_main

	jmp $


