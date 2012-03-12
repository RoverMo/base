#ifndef _START_H
#define _START_H


#define ARM_MOD_SVC	0x13
#define SRAM_BASE	0x0000
#define SRAM_SIZE	0x00001000
#define STACK_BASE	(SRAM_SIZE + SRAM_BASE)

#define IRQ_MASK	(1<<7)
#define FIRQ_MASK	(1<<6)

#endif
