# Constants for the multiboot header
.set ALIGN, 1<<0		# Align loaded modules on page boundaries
.set MEMINFO, 1<<1		# Provide a memory map
.set FLAGS, ALIGN | MEMINFO	# Multiboot 'flag' field
.set MAGIC, 0x1BADB002		# Magic number to help the bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS)	# Checksum of above

# Multiboot header
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Allocate a 16 KiB stack for the main thread
.section .bootstrap_stack, "aw", @nobits
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# Set up pages
.section .bss, "aw", @nobits
	.align 4096
boot_page_dir:
	.skip 4096
boot_page_tab1:
	.skip 4096

# The kernel entry point
.section .setup.text
.global _start
.type _start, @function
_start:
	# So this first section maps the kernel into high memory.

	# Map our pages
	movl $(boot_page_tab1 - 0xC0000000), %edi
	xor %esi, %esi
	movl $1023, %ecx

1:
	# Map the kernel
	cmpl $(_kernel_start - 0xC0000000), %esi
	jl 2f
	cmpl $(_kernel_end - 0xC0000000), %esi
	jge 3f

	movl %esi, %edx
	orl $3, %edx
	movl %edx, (%edi)

2:
	# Loop through our page entries
	addl $4096, %esi
	addl $4, %edi
	loop 1b

3:
	# Map VGA memory to 0xC03FF000
	movl $(0x000B8000 | 3), boot_page_tab1 - 0xC0000000 + 1023 * 4

	# Map the page table to the virtual addresses 0x00000000 and 0xC0000000
	movl $(boot_page_tab1 - 0xC0000003), boot_page_dir - 0xC0000000
	movl $(boot_page_tab1 - 0xC0000003), boot_page_dir - 0xC0000000 + 768 * 4

	# Put the address of the boot page directory in cr3
	movl $(boot_page_dir - 0xC0000000), %ecx
	movl %ecx, %cr3

	# Actually enable paging now
	movl %cr0, %ecx
	orl $0x80010000, %ecx
	movl %ecx, %cr0

	# Now jump to the next part of the setup code
	lea 4f, %ecx
	jmp *%ecx

.section .text
4:
	# Paging is enabled now

	# Unmap the identity mapping
	movl $0, boot_page_dir + 0
	movl %cr3, %ecx
	movl %ecx, %cr3

	# Have the stack pointer point to, well, the stack
	movl $stack_top, %esp

	# Code for GDT creation will go here eventually

	# Call global constructors
	call _init

	# Enter the main kernel, giving it the multiboot_info struct as an argument
	addl 0xC0000000, %ebx
	push %ebx
	call _main

	# Hang if the kernel returns or kabort gets called
	cli
1:	hlt
	jmp 1b

.global _panic
.type _panic, @function
_panic:
	cli
	jmp 1b
