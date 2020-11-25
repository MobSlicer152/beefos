ENTRY (_start)

SECTIONS
{
	. = 1M;

	/* This has to be early in the file */
	.text BLOCK(4K) : ALIGN(4K) {
	        *(.multiboot)
	        *(.realmode_setup)
	}

	. += 0xC0000000;

	/* Add a symbol that indicates the start address of the kernel. */
	_kernel_start = .;

	.text ALIGN (4K) : AT (ADDR (.text) - 0xC0000000)
	{
		*(.text)
	}

	.rodata ALIGN (4K) : AT (ADDR (.rodata) - 0xC0000000)
	{
		*(.rodata)
	}

	.data ALIGN (4K) : AT (ADDR (.data) - 0xC0000000)
	{
		*(.data)
	}

	.bss ALIGN (4K) : AT (ADDR (.bss) - 0xC0000000)
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}

	/* Add a symbol that indicates the end address of the kernel. */
	_kernel_end = .;
}
