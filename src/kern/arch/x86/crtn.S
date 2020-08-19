.section .init
	# gcc will put crtend's .init section here
	popl %ebp
	ret

.section .fini
	# gcc will put crtend's .fini section here
	popl %ebp
	ret
