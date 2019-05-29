CC = gcc
LD = ld
ASM = nasm

C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector
LD_FLAGS = -T loader.ld -m elf_i386 --oformat binary -nostdlib
ASM_FLAGS = -f elf

head.bin:bootsect.bin loader.bin
	@echo "target\t$@\t<= $^"
	@cat bootsect.bin loader.bin > head.bin

loader.bin:loaders.o loaderc.o loader.ld
	@echo "$(LD)\t$@\t<= $^"
	@$(LD) $(LD_FLAGS) $^ -o $@

bootsect.bin:bootsect.s
	@echo "$(ASM)\t$@\t<= $^"
	@$(ASM) $< -o $@

loaders.o:loaders.s
	@echo "$(ASM)\t$@\t<= $^"
	@$(ASM) $(ASM_FLAGS) $< -o $@

loaderc.o:loaderc.c
	@echo "$(CC)\t$@\t<= $^"
	@$(CC) $(C_FLAGS) $< -o $@
