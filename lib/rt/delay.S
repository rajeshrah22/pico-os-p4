	.syntax unified
	.thumb

	.section .text.delay
	.globl delay
	.type delay, %function
delay:
1:	subs r0, r0, #1
	bne 1b
	bx lr
