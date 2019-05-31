ENTRY(kernel_main)
SECTIONS
{
	. = 0xc0100000;

	.text :
	{
		*(.text)
		. = ALIGN(16);
	}
	.data :
	{
		*(.data)
		*(.rodata)
		. = ALIGN(16);
	}
	.bss :
	{
		*(.bss)
		. = ALIGN(16);
	}
	.stab :
	{
		*(.stab)
		. = ALIGN(16);
	}
	.stabstr :
	{
		*(.stabstr)
	 	. = ALIGN(16);
	}
	/DISCARD/ : { *(.comment) *(.eh_frame) }
}

