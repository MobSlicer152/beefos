#include <beefos/kprintf.h>
#include <beefos/kstring.h>
#include <beefos/mmap.h>
#include <beefos/tty.h>
#include <beefos/types.h>
#include <beefos/vga.h>

#include <grub/types.h>
#include <multiboot.h>

void _main(struct multiboot_info *mbt, uint magic)
{
	size_t i;
	struct mmap_ent *entry;

	entry = mbt->mmap_addr;

	/* Fill in the memory map once I figure out how */
	while (entry < mbt->mmap_addr + mbt->mmap_length) { /* The start plus the length will be the end address */
		/* TODO: actually fill in the entries */

		/* Go to the next entry */
		entry = (struct mmap_ent *)((uint)entry + entry->size + sizeof(entry->size));
	}

	tty_reset();

	tty_setcolor(vga_entry_color(VGA_COLOR_BROWN, VGA_COLOR_YELLOW));

	kprintf("This is an intentionally long sentence that takes up a lot of space so that it wraps to the next line\n\n");

	for (i = 0; i < 80; i++) {
		tty_putchar_at(' ', vga_entry_color(i / 4, i / 4), i, i / 4 + 4);
	}
}
