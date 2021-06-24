.syntax unified
.thumb

.section .rodata
initVector:
	.word _STACK
	.word _reset_handler
	.word _NMI_handler
	.word _hardfault_handler
