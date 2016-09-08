OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
	. = 0x30008000;
	
	. = ALIGN(4);
	.text :
	{
		start.o(.text)
		*(.text)
	}
	
	. = ALIGN(4);
	.data :
	{
		*(.data)
	}
	
	bss_start = .;
	. = ALIGN(4);
	.bss :
	{
		*(.bss)
	}
	bss_end = .;
}