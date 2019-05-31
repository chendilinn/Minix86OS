//char buf[512];

int kernel_main()
{
	while(1) {
		asm volatile ("hlt");
	}
	return 0;
}