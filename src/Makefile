C_SOURCES = $(shell find ./kernel -name "*.c")
S_SOURCES = $(shell find ./kernel -name "*.s")


C_SOURCES += $(shell find ./lib -name "*.c")
S_SOURCES += $(shell find ./lib -name "*.s")

C_SOURCES += $(shell find ./device -name "*.c")
S_SOURCES += $(shell find ./device -name "*.s")

S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))

CC = gcc
LD = ld
ASM = nasm

C_FLAGS = -c -Wall -m32 -fno-pic -nostdinc -fno-builtin -fno-stack-protector -I lib/include -I kernel/include -I device/include
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib
ASM_FLAGS = -f elf

MAKE = make

all:head.bin kernel.elf diskImg

diskImg:
	dd if=boot/head.bin of=disk.img conv=notrunc
	dd if=kernel.elf of=disk.img bs=512 seek=200 count=200 conv=notrunc

head.bin:
	$(MAKE) -C boot/

kernel.elf:$(S_OBJECTS) $(C_OBJECTS) scripts/kernel.ld
	@echo "$(LD)\t$@\t<= $(S_OBJECTS) $(C_OBJECTS)"
	@$(LD) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o $@

.c.o:
	@echo "$(CC)\t$@\t<= $^"
	@$(CC) $(C_FLAGS) $< -o $@

.s.o:
	@echo "$(ASM)\t$@\t<= $^"
	@$(ASM) $(ASM_FLAGS) $<

.PHONY:clean
clean:
	cd boot/ && $(MAKE) clean
	rm -f $(C_OBJECTS) $(S_OBJECTS) kernel.elf

.PHONY:bochs
bochs:
	bochs -f scripts/bochsrc

.PHONY:qemu
qemu:
	qemu-system-i386 -m 32 -hda disk.img

.PHONY:debug
debug:
	qemu-system-i386 -hda disk.img -s -S &
	sleep 1
	gdb -x scripts/gdbinit
