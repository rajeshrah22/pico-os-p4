	.syntax unified
	.thumb
	.cpu cortex-m0plus

	.section .text.__reset
	.type __reset, %function
	.global __reset
__reset:
	/* copy data */
	ldr r0, =__data_start
	ldr r1, =__data_end
	ldr r2, =__data_load_start
1:	cmp r0, r1
	beq 1f
	ldr r3, [r2]
	str r3, [r0]
	adds r2, #4
	adds r0, #4
	b 1b
	/* clear bss */
1:	ldr r0, =__bss_start
	ldr r1, =__bss_end
	eors r2, r2
1:	cmp r0, r1
	beq 1f
	str r2, [r0]
	adds r0, #4
	b 1b
	/* constructors array */
1:	ldr r4, =__ctors_start
	ldr r5, =__ctors_end
1:	cmp r4, r5
	beq 1f
	ldr r6, [r4]
	blx r6
	adds r4, #4
	b 1b
	/* call kmain */
1:	bl kmain
	/* destructors array */
	ldr r4, =__dtors_start
	ldr r5, =__dtors_end
1:	cmp r4, r5
	beq 1f
	ldr r6, [r4]
	blx r6
	adds r4, #4
	b 1b
	/* idle loop */
1:	wfe
	b 1b
.size __reset, . - __reset

	.section .text.__bad_interrupt
	.type __bad_interrupt, %function
	.global __bad_interrupt
__bad_interrupt:
1:	wfe
	b 1b
.size __bad_interrupt, . - __bad_interrupt

.macro __vector_X number
	.weak __vector_\number
	.set __vector_\number, __bad_interrupt
.endm

.altmacro
.set i, 2
.rept 48 - 2
	__vector_X %i
	.set i, i+1
.endr
