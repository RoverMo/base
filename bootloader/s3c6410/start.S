#define CLK_BASE   0x7E00F000
#define APLL_LOCK       0x000
#define MPLL_LOCK       0x004
#define EPLL_LOCK       0x008
#define APLL_CON        0x00C
#define MPLL_CON        0x010
#define EPLL_CON0       0x014
#define EPLL_CON1       0x018
#define CLK_SRC         0x01C
#define CLK_DIV0        0x020
#define CLK_DIV2        0x028
#define MISC_CON        0x838
#define OTHERS          0x900

#define UART_BASE  0x7F005000
#define ULCON0          0x000
#define UCON0           0x004
#define UTRSTAT0        0x010
#define UTXH0           0x020
#define URXH0           0x024
#define UBRDIV0         0x028
#define UDIVSLOT0       0x02C

#define GPIO_BASE  0x7F008000
#define GPACON          0x000

#define NAND_BASE  0x70200000 
#define NFCONF          0x000
#define NFCONT          0x004
#define NFCMMD          0x008
#define NFADDR          0x00C
#define NFDATA          0x010
#define NFSTAT          0x028

	.globl _start

_start:
	ldr	r4, clk_base

	mov	r5, #0xE10
	add	r5, r5, #0x01
	str r5, [r4, #APLL_LOCK]
	str r5, [r4, #MPLL_LOCK]

	ldr r5, apll_val
	str r5, [r4, #APLL_CON]

	ldr r5, mpll_val
	str r5, [r4, #MPLL_CON]

	mov r5, #(1 << 13)
	orr r5, ,r5, #3
	str r5, [r4, #CLK_SRC]

	ldr r5, [r4, #CLK_DIV0]
	orr r5, r5, #(3 << 12)
	orr r5, r5, #(1 << 8 )
	orr r5, r5, #(1 << 4)
	str r5, [r4, #CLK_DIV0]

	mov r5, #(1 << 16)
	str r5, [r4, #CLK_DIV2]

	ldr r5, [r4, #OTHERS]
	bic r5, r5, #(1 << 6)
	str r5, [r4, #OTHERS]

	ldr r4, gpio_base

	mov r5, #0x2200
	add r5, r5, #0x22
	str r5, [r4, #GPACON]

	ldr r4, uart_base

	mov r5, #3
	str r5, [r4, #ULCON0]

	mov r5, #(3 << 10)
	orr r5, r5,  #(1 << 2 | 1)
	str r5, [r4, #UCON0]

	mov r5, #35
	str r5, [r4, #UBRDIV0]

	

uart_send:
	ldr r6, [r4, #UTRSTAT0]
	tst r6, #4
	beq uart_send
	strb pc, [r4, #UTXH0]
	b uart_send

msg:
	.asciz "hello rover\n"

end:
	b	end

gpio_base:
	.word GPIO_BASE

uart_base:
	.word UART_BASE

clk_base:
	.word CLK_BASE

apll_val:
	.word 1 << 31 | 333 << 16 | 3 << 8 | 1

mpll_val:
	.word 1 << 31 | 266 << 16 | 3 << 8 | 2
