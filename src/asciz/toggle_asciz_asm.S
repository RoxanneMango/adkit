	.cpu cortex-m3				@ This assembly is for the ARM cortex-M3 processor
	.global	toggle_asciz_asm	@ Declare the toggle_asciz_asm co-routine
.section .text					@ start of code
toggle_asciz_asm:
	push	{lr}				@ Store context of link register
	cmp r0, #65					@ compare char value of ASCII value of 'A'
	bge george					@ if ( r0 >= 'A') { goto george } 
return:
	pop	{pc}					@ YEET the program counter
george:
	cmp r0, #90					@ r0 <= 'Z' ?
	ble to_lower				@ if(r0 <= 'Z') { goto to_lower }
	cmp r0, #97					@ r0 >= 'a' ?
	bge larry					@ if(r0 >= 'a') { goto larry }
	b return					@ else { goto return }
to_lower:
	add r0, #32					@ make lower_case
	b return					@ goto return
larry:
	cmp r0, #122				@ r0 <= 'z' ?
	ble to_upper				@ if(r0 <= 'z') { goto to_upper }
	b return					@ else { goto return }
to_upper:
	sub r0, #32					@ make upper_case
	b return					@ goto return