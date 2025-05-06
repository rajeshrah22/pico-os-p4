	.syntax unified
	.thumb

	.section .text.flog2
	.globl flog2
	.type flog2, %function
flog2:
#if __ARM_ARCH == 7
	clz r0, r0
	rsb r0, r0, #31
#elif __ARM_ARCH == 6
	movs r4, r0
	eors r0, r0
	ldr r5, =0x80000000
1:	tst r4, r5
	beq 1f
	adds r0, #1
	lsls r4, #1
	b 1b
1:	movs r4, #31
	subs r0, r4, r0
#else
#error "architecture not supported"
#endif
	bx lr
	
