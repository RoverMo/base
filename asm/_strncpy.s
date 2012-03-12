	.text
	.global _strncpy 

_strncpy:
	stmfd sp!, {lr}

loop1:
	ldrb r3, [r1], #1
	strb r3, [r0], #1
	cmp r3, #0
	beq loop2
	subs r2, r2, #1
	bne loop1

	b end

loop2:
	mov r3, #0
	strb r3, [r0], #1
	subs r2, r2, #1
	bne loop2

end:
	ldmfd sp!, {pc}
