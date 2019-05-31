C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))

CC = gcc
LD = ld

C_FLAGS = -c -Wall -m32 -fno-pic -nostdinc -fno-builtin -fno-stack-protector -I include
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib

kernel.elf:$(C_OBJECTS)
	@echo "$(LD)\t$@\t<= $^"
	@$(LD) $(LD_FLAGS) $^ -o $@

%.o:%.c
	@echo "$(CC)\t$@\t<= $^"
	@$(CC) $(C_FLAGS) $< -o $@

.PHONY:clean
clean:
	rm -f *.o *.elf