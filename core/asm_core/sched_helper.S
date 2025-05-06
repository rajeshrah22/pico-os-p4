#include <interrupt.h>
#include <stacks.h>

	.syntax unified

ISR SYSTICK_vect
	push {lr}
	/* get current stack */
	mrs r0, psp
	bl entry_from_user
	bl schedule
	bl return_to_user

	pop {pc}





	.section .text.do_context_switch, "ax"
	.globl do_context_switch
	.type do_context_switch, %function
do_context_switch:
	/* current: current process
	 * next: next process to be scheduled
	 */
	
	bx lr
	.size do_context_switch, . - do_context_switch
