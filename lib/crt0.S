	.syntax unified

	.section .text.startup
	.globl startup
	.type startup, %function
startup:
	/* copy .data */
	ldr r0, =__data_start
	ldr r1, =__data_end
	ldr r2, =__data_rom_start
1:	cmp r0, r1
#if __ARM_ARCH == 7
	itt lt
	ldrlt r3, [r2], #4
	strlt r3, [r0], #4
	blt 1b
#elif __ARM_ARCH == 6
	beq 1f
	ldr r3, [r2]
	str r3, [r0]
	adds r2, #4
	adds r0, #4
	b 1b
#else
#	error "architecture not supported"
#endif

	/* clear .bss */
1:	eors r0, r0, r0
	ldr r1, =__bss_start
	ldr r2, =__bss_end
1:	cmp r1, r2
#if __ARM_ARCH == 7
	it lt
	strlt r0, [r1], #4
	blt 1b
#elif __ARM_ARCH == 6
	beq 1f
	str r0, [r1]
	adds r1, #4
	b 1b
#else
#	error "architecture not supported"
#endif
1:	bl main

1:	wfe
	b 1b
