#include <mpu.h>

	.syntax unified
	.thumb

	.section .text.mpu_set_region
	.globl mpu_set_region
	.type mpu_set_region, %function
mpu_set_region:
	push {r4, lr}
	ldr r4, =MPU_RNR
	stm r4!, {r0-r2}
	pop {r4, pc}
.size mpu_set_region, . - mpu_set_region


	.section .text.mpu_disable
	.globl mpu_disable
	.type mpu_disable, %function
mpu_disable:
	dmb
	movs r0, #0
	b 1f
	.globl mpu_enable
	.type mpu_enable, %function
mpu_enable:
	movs r0, #1
1:	ldr r1, =MPU_CTRL
	str r0, [r1]
	dsb
	isb
	bx lr

	.section .text.mpu_init
	.globl mpu_init
	.type mpu_init, %function
mpu_init:
	push {lr}
	bl mpu_disable
	movs r3, #4
	ldr r4, =mpu_setup_table
1:	ldmia r4!, {r0-r2}
	bl mpu_set_region
	subs r3, #1
	bne 1b
	bl mpu_enable
1:	pop {pc}

