	.arch armv6zk
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"sys_call.c"
	.section	.rodata
	.align	2
.LC0:
	.ascii	"/dev/sda6\000"
	.align	2
.LC1:
	.ascii	"open failed\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	ldr	r0, .L4
	mov	r1, #0
	bl	open
	mov	r3, r0
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	bge	.L2
	ldr	r0, .L4+4
	bl	perror
.L2:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L5:
	.align	2
.L4:
	.word	.LC0
	.word	.LC1
	.size	main, .-main
	.ident	"GCC: (http://www.maxwit.com, MaxWit Training) 4.4.4"
	.section	.note.GNU-stack,"",%progbits
