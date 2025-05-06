	.syntax unified
	.thumb
	.cpu cortex-m0plus

	.section .vector_table, "a"
	.global __vector_table
__vector_table:
	.word __ram_end
	.word __reset
	.word __vector_2
	.word __vector_3
.rept 7
	.word __bad_interrupt
.endr
	.word __vector_11
	.word __bad_interrupt
	.word __bad_interrupt
	.word __vector_14
	.word __vector_15

.macro vector_entry vect
	.word __vector_\vect
.endm

.altmacro
.rept 32
	vector_entry %(16+\+)
.endr
.size __vector_table, . - __vector_table
