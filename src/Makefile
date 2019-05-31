BOOT = boot/
KERNEL = kernel/

MAKE = make

all:head.bin kernel.elf diskImg

diskImg:
	dd if=$(BOOT)/head.bin of=disk.img conv=notrunc
	dd if=$(KERNEL)/kernel.elf of=disk.img bs=512 seek=200 count=200 conv=notrunc

head.bin:
	$(MAKE) -C boot

kernel.elf:
	$(MAKE) -C kernel

.PHONY:clean
clean:
	cd $(BOOT) && $(MAKE) clean
	cd $(KERNEL) && $(MAKE) clean

.PHONY:bochs
bochs:
	bochs -f scripts/bochsrc

.PHONY:qemu
qemu:
	qemu-system-i386 -hda disk.img

.PHONY:debug
debug:
	qemu-system-i386 -hda disk.img -s -S &
	sleep 1
	gdb -x scripts/gdbinit
