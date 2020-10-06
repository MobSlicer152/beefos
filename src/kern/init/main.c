#include "beefos/kabrt.h"
#include <beefos/kprintf.h>
#include <beefos/kstring.h>
#include <beefos/macro.h>
#include <beefos/mmap.h>
#include <beefos/tty.h>
#include <beefos/types.h>
#include <beefos/vga.h>

#include <grub/types.h>
#include <multiboot.h>

void _main(struct multiboot_info *mbt, uint magic)
{
	size_t i, j;
	struct mmap_ent *entry;

	tty_reset();

	mbt->flags |= 1 << 5;

	entry = (struct mmap_ent *)mbt->mmap_addr;
	i = 0;

	while (entry < (struct mmap_ent *)mbt->mmap_addr + mbt->mmap_length) { /* The start plus the length will be the end address */
		/* Assign each field to the data at the address pointed to by mmap_addr +/- <offset> */		
		entry->size = *(u32 *)mbt->mmap_addr - 4;
		entry->base_addr = CONCAT_INTS(*(u32 *)mbt->mmap_addr, *(u32 *)mbt->mmap_addr + 4, u32, u64);
		entry->len = CONCAT_INTS(*(u32 *)mbt->mmap_addr + 8, *(u32 *)mbt->mmap_addr + 12, u32, u64);
		entry->type = *(u32 *)mbt->mmap_addr + 16;

		kprintf("Entry %d details:\nsize: %d\nbase_addr: %p\nlen: %d\ntype: %d\n\n", i, entry->size, entry->base_addr, entry->len, entry->type);

		j = 0;
		while (j < 1000)
			j++;

		i++;
		/* Go to the next entry */
		entry = (struct mmap_ent *)((uint)entry + entry->size + sizeof entry->size);
	}

	/* tty_setcolor(vga_entry_color(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_YELLOW));

	kprintf("This is an intentionally long sentence that takes up a lot of space so that it wraps to the next line\n\n");

	for (i = 0; i < 80; i++) {
		tty_putchar_at(' ', vga_entry_color(i / 4, i / 4), i, i / 4 + 4);
	} */
}
