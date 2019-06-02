[bits 32]
section .text
global _start
extern kernel_main

_start:

	mov esp, 0xc0400000	;内核空间顶部

	mov ebp, 0

	call kernel_main

stop:

	hlt

	jmp stop
