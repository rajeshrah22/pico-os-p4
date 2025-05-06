#include <stacks.h>

	.syntax unified

	.section .text.init_user_stack
	.globl init_user_stack
	.type init_user_stack, %function
	/* void* init_user_stack(void* sp, void* pc);
	/* r0: initial stack pointer - 8 byte aligned
	 * r1: initial program counter, entry point
	 */
init_user_stack:
	/* stack frame for interrupts:
	 * xPSR				(0x00000000)
	 * ReturnAddress	(0xffffffff)
	 * lr				(r1 -- entry point)
	 * r12				(0x00000000)
	 * r3				(0x00000000)
	 * r2				(0x00000000)
	 * r1				(0x00000000)
	 * r0				(0x00000000)
	 * dropping to user involves loading all registers from the user stack. The
	 * initial user stack contains a ``return from interrupt block'' which
	 * takes us into the entry point of the program, as well as the initial
	 * value of the other integer registers.
	 */
	/* set up user stack pointer */
	/* msr psp, r0 */

	/* switch to user stack */
	/* switch_to_user r0 */

	/* start populating stack */
#if __ARM_ARCH == 7
	mov r3, #(1 << 24)	/* xPSR.T must be set */
#elif __ARM_ARCH == 6
	ldr r3, =(1 << 24)	/* xPSR.T must be set */
#else
#	error "architecture not supported"
#endif
	mov r2, r1
	movs r1, #0
	/* xpsr, returnaddress, lr */
#if __ARM_ARCH == 7
	stmdb r0!, {r1-r3}
#elif __ARM_ARCH == 6
	subs r0, r0, #0xc
	stmia r0!, {r1-r3}
	subs r0, r0, #0xc
#else
#	error "architecture not supported"
#endif

	/* r12 - r0, then r4 - r11 */
	movs r1, #13
	eors r2, r2
1:
#if __ARM_ARCH == 7
	str r2, [r0, #-4]!
#elif __ARM_ARCH == 6
	str r2, [r0]
	subs r0, r0, #4
#else
#	error "architecture not supported"
#endif
	subs r1, r1, #1
	bne 1b

	/* set the process stack pointer to r0 */
	msr psp, r0

	/* and return */
	bx lr

	.section .text.entry_from_user
	.globl entry_from_user
	.type entry_from_user, %function
entry_from_user:
	/* r0 contains the stack pointer for the thread */
#if __ARM_ARCH == 7
	stmdb r0!, {r4-r11}
#elif __ARM_ARCH == 6
#	warning "save r4 to r11 into the process stack"
#else
#	error "architecture not supported"
#endif
	msr psp, r0
	bx lr

#if 0
	.section .text.entry_from_kernel
	.globl entry_from_kernel
	.type entry_from_kernel, %function
entry_from_kernel:
	stmia r0!, {r4-r11}
	sub r0, r0, #32
	msr msp, r0
	bx lr
#endif

	.section .text.return_to_user
	.globl return_to_user
	.type return_to_user, %function
return_to_user:
	/* r0 contains the stack pointer for the thread */
#if __ARM_ARCH == 7
	/* load general purpose registers */
	ldmia r0!, {r4-r11}
#elif __ARM_ARCH == 6
#	warning "restore registers r4 to r11 from the process stack"
#else
#	error "architecture not supported"
#endif
	/* set up stack pointer */
	msr psp, r0
	/* and return */
	bx lr

#if 0
	.section .text.return_to_kernel
	.globl return_to_kernel
	.type return_to_kernel, %function
return_to_kernel:
	ldmia r0!, {r4-r11}
	add r0, r0, #32
	msr msp, r0
	bx lr
#endif

	.section .text.get_current_sp
	.globl get_current_sp
	.type get_current_sp, %function
get_current_sp:
	mrs r0, psp
	bx lr
