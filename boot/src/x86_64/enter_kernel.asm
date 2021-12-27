BITS 64
DEFAULT REL

SECTION .text

; Jumps to the kernel's entry point
GLOBAL enter_kernel
enter_kernel:
	; Get the bottom address of the stack
	add rdx, r8

	; Load the new stack into RSP
	mov rsp, rdx

	; Jump to the kernel
	xchg rcx, r9
	jmp r9
