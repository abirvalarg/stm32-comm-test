.syntax unified
.thumb

.macro	HANDLER name
	.equ \name, _default_handler
	.weak \name
.endm

HANDLER _reset_handler
HANDLER _NMI_handler
HANDLER _hardfault_handler
HANDLER _TIM6_DAC_handler
HANDLER _TIM7_handler

.section .text

.global _reset_handler
.thumb_func
.align 2
_reset_handler:
	// initialize .data
	ldr r0, =_DATA_START
	ldr r1, =_DATA_VAL_START
	ldr r2, =_DATA_END

0:
	cmp r0, r2
	beq 1f
	ldrb r3, [r1], 1
	strb r3, [r0], 1
	b 0b
1:

	// initialize .bss
	ldr r0, =_BSS_START
	ldr r1, =_BSS_END
	ldrb r3, =0x00

0:
	cmp r0, r1
	beq 1f
	strb r3, [r0], 1
	b 0b
1:

	bl start
0:
	b.n 0b

.global _default_handler
.weak _default_handler
.thumb_func
.align 2, 0x46c0
_default_handler:
	b.n _default_handler
	nop

.global _TIM6_DAC_handler
.thumb_func
_TIM6_DAC_handler:
	push {lr}

	/*
	ldr r0, =LED2
	ldr r1, =1
	bl GPIO_Pin_write
	*/

	ldr r0, =TIM6
	bl _timer_handler

	pop {lr}
	bx lr

.global _TIM7_handler
.thumb_func
_TIM7_handler:
	push {lr}

	/*
	ldr r0, =LED2
	ldr r1, =0
	bl GPIO_Pin_write
	*/

	ldr r0, =TIM7
	bl _timer_handler

	pop {lr}
	bx lr

.global _timer_handler
.thumb_func
.align 2
_timer_handler:
	push {r0, r1, r4, lr}

	mov r4, r0
	bl Timer_reset_int
	cmp r0, 0
	beq 0f
	
	ldr r1, [r4, 3 * 4]
	ldr r1, [r1]
	cmp r1, 0
	beq 0f
	mov r0, r4
	blx r1

0:
	pop {r0, r1, r4, lr}
	bx lr
	nop.n
