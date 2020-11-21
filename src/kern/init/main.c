#include <beefos/kabrt.h>
#include <beefos/kprintf.h>
#include <beefos/kstring.h>
#include <beefos/macro.h>
#include <beefos/tty.h>
#include <beefos/types.h>
#include <beefos/vga.h>

#include <grub/types.h>
#include <multiboot.h>

void _main(struct multiboot_info *mbt, uint magic)
{
	size_t mem_size;
	size_t i;
	struct multiboot_mmap_entry *entry;

	tty_reset();

	if (!(mbt->flags & 1) || !(mbt->flags & (1 << 5))) {
		kprintf("Failed to get memory map!\n");
		kabort();
	}

	mem_size = (mbt->mem_lower + mbt->mem_upper) / 1024;

	/* Now we can print out the amount of memory we have available */
	kprintf("Total memory reported: %dMiB", mem_size);

	kprintf("This is an intentionally long sentence that takes up a lot of space so that it wraps to the next line\n\n");

	for (i = 0; i < 80; i++)
		tty_putchar_at(' ', vga_entry_color(i / 4, i / 4), i, i / 4 + 4);
}
