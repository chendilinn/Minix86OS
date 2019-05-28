char *p = (char *)0xb8000;

void console_puts(char *str)
{
	while(*str != '0') {
		*p++ = *str++;
		*p++ = 0x07;
	}
}

void loader_main()
{
	console_puts("Loading kernel...");
}