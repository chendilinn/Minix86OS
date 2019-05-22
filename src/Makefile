#!Makefile
# patsubst 处理所有在 C_SOURCES 字列中的字（一列文件名），如果它的 结尾是 '.c'，就用 '.o' 把 '.c' 取代
C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))
H_SOURCES = $(shell find . -name "*.h")

CC = gcc
LD = ld
ASM = nasm

C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib
ASM_FLAGS = -f elf -g -F stabs

all:kernel.img update

kernel.img:$(S_OBJECTS) $(C_OBJECTS)
	@echo "$(LD)\t$@\t<= $(S_OBJECTS) $(C_OBJECTS)"
	@$(LD) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o $@

# The automatic variable `$<' is just the first prerequisite
%.o:%.c $(H_SOURCES)
	@echo "$(CC)\t$@\t<= $<"
	@$(CC) $(C_FLAGS) $< -o $@

.s.o:
	@echo "$(ASM)\t$@\t<= $<"
	@$(ASM) $(ASM_FLAGS) $<

.PHONY:clean
clean:
	$(RM) $(S_OBJECTS) $(C_OBJECTS) kernel.img

.PHONY:update
update:
	sudo kpartx -av disk.img
	@sleep 0.3
	sudo mount /dev/mapper/loop0p1 /mnt/kernel/
	sudo cp kernel.img /mnt/kernel/
	sudo umount /mnt/kernel
	@sleep 0.3
	sudo kpartx -d disk.img

.PHONY:mount
mount:
	sudo kpartx -av disk.img
	@sleep 0.3
	sudo mount /dev/mapper/loop0p1 /mnt/kernel/

.PHONY:umount
umount:
	sudo umount /mnt/kernel
	@sleep 0.3
	sudo kpartx -d disk.img

.PHONY:bochs
bochs:
	bochs -f scripts/bochsrc.txt

.PHONY:qemu
qemu:
	qemu -hda disk.img
