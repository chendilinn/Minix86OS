SECTIONS
{
	. = 0x7e00;

	.text :
	{
		*(.text)
		. = ALIGN(4096);
	}
	.data :
	{
		*(.data)
		*(.rodata)
		. = ALIGN(4096);
	}
	.bss :
	{
		*(.bss)
		. = ALIGN(4096);
	}

	/DISCARD/ : { *(.stab) *(.stabstr) *(.comment) *(.eh_frame) }
}

