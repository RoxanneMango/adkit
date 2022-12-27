	.cpu cortex-m3				@ This assembly is for the ARM cortex-M3 processor
	.global	print_asciz_asm		@ Declare the print_asciz_asm co-routine
.section .text					@ Start program code
print_asciz_asm:
	push	{lr}				@ Store context of link register
	sub sp, sp, #4				@ Grow the stack for pushing contents of r0
	str	r0, [sp]				@ Store context of char_pointer
loop:
	ldr	r0, [sp]				@ Restore context of char_pointer
	ldrb	r0, [r0]			@ dereference char_pointer in r0
	cmp	r0, #0					@ Compare whether it's \0 or not
	beq	exit					@ If it is, goto exit
toggle:
	bl toggle_asciz_asm			@ call toggle_asciz_asm subroutine with r0 as parameter
print:
	bl	putchar				 	@ Call putchar(char) function from arm-none-eabi-gcc <stdio.h>
	ldr	r0, [sp]				@ Restore context of char_pointer
	add	r0, r0, #1				@ ++char_pointer
	str	r0, [sp]				@ Store the updated char_pointer
	b loop						@ goto start loop
exit:
	add sp, sp, #4				@ Shrink stack back to what it was
	pop	{pc}					@ YEET the program counter