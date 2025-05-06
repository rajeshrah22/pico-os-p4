.syntax unified
.thumb
.cpu cortex-m0plus
.section .vector_table, "ax"

.macro __vector_X number
	.word __vector_\number
.endm

.altmacro
__vector_table:
	.word __ram_end		// 0 - Reset stack pointer
	.word __reset		// 1 - Reset
	.set i, 2
	.rept 48 - 2
		__vector_X %i
		.set i, i+1
	.endr
