	.global main

main:
	stmfd sp!, {r1-r7, lr}
	ldr r0, filename
	mov r7, #8
	mov r1, #0640
	add r1, r1, #4
	swi #0
	ldmfd sp!, {r1-r7, pc}

filename:
	.word name

name:
	.asciz "a.c"
