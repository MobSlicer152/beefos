; Print a message from SI
bios_print:
	; Clear the direction flag
	cld

	bios_print_loop:
		; Load this character from SI into AL
		lodsb

		; Check if this is the end of the string
		or al, al
		jz bios_print_end

		; Print the character
		mov ah, 0x0E
		mov bh, 0x00
		int 0x10

		; Loop back to the start
		jmp SHORT bios_print_loop
	bios_print_end:
		ret
