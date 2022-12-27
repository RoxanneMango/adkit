	@ https://www.youtube.com/watch?v=wqzLoXjFT34
	.cpu cortex-m3				@ This assembly is for the ARM cortex-M3 processor
	.global	application			@ Declare the application co-routine
.section .text					@ Start program code
application:
	push	{lr}				@ Store context of link register
	bl print_asciz_asm			@ call print_asciz_asm function, passing r0 as implicit char_pointer
	pop {pc}					@ YEET program counter