#ifndef _START_H
#define _START_H

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

#endif
