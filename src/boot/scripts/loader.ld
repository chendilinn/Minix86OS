SECTIONS
{
	. = 0x8000;

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

	/DISCARD/ : { *(.stab) *(.stabstr) *(.comment) *(.eh_frame) }
}

