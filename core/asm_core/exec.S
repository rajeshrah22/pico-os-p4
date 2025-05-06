	.syntax unified

	.section .text.exec
	.globl exec
	.type exec, %function
exec:
	svc #4
/*
	ldmia r0!, {r4-r11}
	eor r1, r1, r1
	eor r2, r2, r2
	eor r3, r3, r3
	eor r12, r12, r12
	ldr lr, [r0, #24]
	msr apsr_nzcvqg, r1
	add r0, r0, #32
	msr psp, r0
	mrs r0, control
	orr r0, r0, #3
	msr control, r0
	eor r0, r0
	bx lr
*/
	.section .text.svc_execve
	.globl svc_execve
	.type svc_execve, %function
svc_execve:
	/* At this point, the stack contains r4, r5, lr, and the stack frame for
	 * the interrupt. Our r0 should be the stack pointer for the user stack. */
	ldr r1, [sp, #8]
	movs r2, #0xc
	orrs r1, r2
	mov lr, r1
	mrs r1, control
	movs r2, #3
	orrs r1, r2
	msr control, r1
	b return_to_user
