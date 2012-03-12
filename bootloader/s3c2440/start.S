#include "start.h"

.global MW2440Entry

MW2440Entry:

HandleReset:
	msr cpsr,#(ARM_MOD_SVC | IRQ_MASK | FIRQ_MASK)
	mov r13, #STACK_BASE
	bl main
	b Hang

handleUndefine:
	b Hang
handleSwi:
	b Hang
handleIAbt:
	b Hang
handleDAbt:
	b Hang
handleReserved:
	b Hang
handleIrQ:
	b Hang
handleFiq:
	b Hang
Hang:
	b Hang	
