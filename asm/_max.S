	.globl _max

_max:
	stmfd sp!, {lr}

	ldr r2, [r0]
	mov r4, #1

again:
	cmp r1, r4
	bge end
	ldr r3, [r0, #4]!
	cmp r2, r3
	blt again
	mov r2, r3
	add r4, r4, #1
	b again

end:
	mov r0, r2

	ldmfd sp!, {pc}
