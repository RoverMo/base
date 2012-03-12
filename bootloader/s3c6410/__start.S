#include "start.h"

	.globl _start

_start:
	ldr	r4, clk_base

	mov	r5, #0xE1
	add	r5, r5, #0x01
	str r5, [r4, #APLL_LOCK]
	str r5, [r4, #MPLL_LOCK]
	str r5, [r4, #EPLL_LOCK]

	ldr r5, apll_val
	str r5, [r4, #APLL_CON]

	ldr r5, =(1 << 31 | 266 << 16 | 3 << 8 | 2)
	str r5, [r4, #MPLL_CON]

	ldr r5, =(1 << 31 | 32 << 16 | 1 << 8 | 2)
	str r5, [r4, #EPLL_CON0]
	mov r5, #0
	str r5, [r4, #EPLL_CON1]

	@ mov r5, #(1 << 13)
	mov r5, #7
	str r5, [r4, #CLK_SRC]

	ldr r5, =(1 << 8 | 3 << 12)
	str r5, [r4, #CLK_DIV0]

	ldr r5, [r4, #OTHERS]
	bic r5, #(1 << 6)
	str r5, [r4, #OTHERS]

	ldr r4, gpio_base

	mov r5, #0x2200
	add r5, r5, #0x22
	str r5, [r4, #GPACON]

	ldr r4, uart_base

	mov r5, #3
	str r5, [r4, #ULCON0]

	ldr r5, =(3 << 10 | 1 << 2 | 1)
	str r5, [r4, #UCON0]

	mov r5, #51
	str r5, [r4, #UBRDIV0]

	mov r5, #0x80
	str r5, [r4, #UDIVSLOT0]

uart_send:
	ldr r6, [r4, #UTRSTAT0]
	and r6, r6, #(1 << 2)
	cmp r6, #0
	bne uart_send
	mov r5, #'A'
	strb r5, [r4, #UTXH0]
	bne uart_send

end:
	b	end

gpio_base:
	.word GPIO_BASE

uart_base:
	.word UART_BASE

clk_base:
	.word CLK_BASE

apll_val:
	.word 1 << 31 | 333 << 16 | 33 << 8 | 1
