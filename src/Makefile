#!Makefile
# patsubst 处理所有在 C_SOURCES 字列中的字（一列文件名），如果它的 结尾是 '.c'，就用 '.o' 把 '.c' 取代
C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
HEAD_SOURCES = $(shell find boot -name "*.s")
HEAD_BINARY = $(patsubst %.s, %.bin, $(HEAD_SOURCES))
H_SOURCES = $(shell find . -name "*.h")

CC = gcc
LD = ld
ASM = nasm

C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib
ASM_FLAGS = -f elf -g -F stabs

all:$(HEAD_BINARY) updateImg

updateImg:$(HEAD_BINARY)
	@dd if=boot/bootsect.bin of=disk.img conv=notrunc
	@dd if=boot/loader.bin of=disk.img seek=1 conv=notrunc

%.o:%.c
	@echo "$(CC)\t$@\t<= $<"
	@$(CC) $(C_FLAGS) $< -o $@

%.bin:%.s
	@echo "$(ASM)\t$@\t<= $<"
	@$(ASM) $< -o $@

.PHONY:clean
clean:
	rm -f $(HEAD_BINARY)

.PHONY:bochs
bochs:
	bochs -f scripts/bochsrc

.PHONY:qemu
qemu:
	qemu-system-i386 -hda disk.img
