BITS 64
DEFAULT REL

SECTION .text

; Reverse a word
GLOBAL reverse_word
reverse_word:
	xor eax, eax
	mov ax, cx
	xchg al, ah
	ret

; Reverse a doubleword
GLOBAL reverse_dword
reverse_dword:
	call reverse_word
	xor edx, edx
	mov dx, ax
	shr ecx, 16
	call reverse_word
	shl edx, 16
	or eax, edx
	ret
	
; Reverse a quadword
GLOBAL reverse_qword
reverse_qword:
	call reverse_dword
	xor edx, edx
	mov edx, eax
	shr rcx, 32
	call reverse_dword
	shl rdx, 32
	or rax, rdx
	ret
