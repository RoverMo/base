	.text
	.globl _puts

_puts:
	stmfd	sp!, {r4, r5, lr}
	mov		r4, #0
	mov		r5, r0

loop:
	ldrb	r0, [r5], #1
	bl		putchar
	add		r4, r4, #1
	cmp 	r0, #0
	bne		loop

end:
	mov r0, #'\n'
	bl	putchar
	mov r0, r4
	ldmfd sp!, {r4, r5, pc}
