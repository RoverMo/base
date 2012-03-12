	.text
	.globl main

main:
	mov r4, lr
	mov r5, #10
	mov r0, #'a'

loop:
	bl putchar
	add r0, r0, #1
	subs r5, r5, #1
	bne loop

	mov r0, #'\n'
	bl putchar

	mov pc, r4
