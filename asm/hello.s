.text
.global main

main:
	mov r5, lr
	ldr r0, L1
	bl puts
	mov pc, r5

L1:
	.word str

str:
	.asciz "HELLO"
