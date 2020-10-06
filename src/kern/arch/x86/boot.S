# Constants for the multiboot header
.set ALIGN, 1<<0		# Align loaded modules on page boundaries
.set MEMINFO, 1<<1		# Provide a memory map
.set FLAGS, ALIGN | MEMINFO	# Multiboot 'flag' field
.set MAGIC, 0x1BADB002		# Magic number to help the bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS)	# Checksum of above

# Multiboot header, in its own section
.section .multiboot

.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Allocate a 16 KiB stack for the main thread
.section .bss

.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point
.section .text

.global _start
.type _start, @function
_start:
	# Have the stack pointer point to, well, the stack
	movl $stack_top, %esp

	# Call global constructors
	call _init

	# Enter the main kernel, giving it the multiboot_info struct as an argument
	push %ebx
	call _main

	# Hang if the kernel returns or kabort gets called
	cli
1:	hlt
	jmp 1b

# Get the size of _start
.size _start, . - _start

.global _panic
.type _panic, @function
_panic:
	cli
	jmp 1b
