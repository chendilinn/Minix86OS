#!Makefile
# patsubst 处理所有在 C_SOURCES 字列中的字（一列文件名），如果它的 结尾是 '.c'，就用 '.o' 把 '.c' 取代
C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
HEAD_SOURCES = $(shell find boot -name "*.s")
HEAD_BINARY = $(patsubst %.s, %.bin, $(HEAD_SOURCES))
H_SOURCES = $(shell find . -name "*.h")
ROOT_DIR = $(shell pwd)

MAKE = make
CC = gcc
LD = ld
ASM = nasm

C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib
ASM_FLAGS = -f elf -g -F stabs

disk.img:head.bin
	dd if=boot/head.bin of=disk.img conv=notrunc

head.bin:
	$(MAKE) -C boot

%.o:%.c
	@echo "$(CC)\t$@\t<= $<"
	@$(CC) $(C_FLAGS) $< -o $@

%.bin:%.s
	@echo "$(ASM)\t$@\t<= $<"
	@$(ASM) $< -o $@

.PHONY:clean
clean:
	rm -f boot/*.bin

.PHONY:bochs
bochs:
	bochs -f scripts/bochsrc

.PHONY:qemu
qemu:
	qemu-system-i386 -hda disk.img
