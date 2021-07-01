.syntax unified
.thumb

.section .rodata
initVector:
	.word _STACK
	.word _reset_handler
	.word _NMI_handler
	.word _hardfault_handler
.org 0x00000118
	.word _TIM6_DAC_handler
	.word _TIM7_handler
