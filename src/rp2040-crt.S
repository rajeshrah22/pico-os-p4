.syntax unified
.thumb
.cpu cortex-m0plus
.section .text, "ax"
.global __reset
.global __bad_interrupt
.global main

	.type _set, %function
_set:
	cmp	r0, r1
	blt	._set_loop
	bx	lr
._set_loop:
	stmia	r0!, {r2}
	cmp	r0, r1
	bls	._set_loop
	bx	lr

	.type _copy, %function
_copy:
	cmp	r0, r1
	blt	._copy_loop
	bx	lr
._copy_loop:
	ldmia	r2!, {r3}
	stmia	r0!, {r3}
	cmp	r0, r1
	bls	._copy_loop
	bx	lr

	.type _run_calls, %function
_run_calls:
	push	{lr}
	cmp	r0, r1
	blt	._run_calls_loop
	pop	{pc}
._run_calls_loop:
	ldmia	r0!, {r2}
	push	{r0, r1}
	blx	r2
	pop	{r0, r1}
	cmp	r0, r1
	bls	._run_calls_loop
	pop	{pc}

	.type __reset, %function
__reset:
	ldr	r0, =__data_start
	ldr	r1, =__data_end
	ldr	r2, =__data_load_start
	bl	_copy
	ldr	r0, =__bss_start
	ldr	r1, =__bss_end
	movs	r2, #0
	bl	_set
	ldr	r0, =__ctors_start
	ldr	r1, =__ctors_end
	bl	_run_calls
	bl	main
	ldr	r0, =__dtors_start
	ldr	r1, =__dtors_end
	bl	_run_calls
halt:
	wfe
	b	halt

	.type __bad_interrupt, %function
__bad_interrupt:
	wfe
	b	__bad_interrupt

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
