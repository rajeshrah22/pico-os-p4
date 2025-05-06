#include <interrupt.h>
#include <mpu.h>
#include <mpu_perms.h>
#include <printk.h>
#include <sysctrl.h>
#include <stacks.h>
#include <task.h>

void mpu_setup_user(struct task_struct* proc) {
#if 1
#	warning "Graduate students must implement this function"
#	warning "otherwise change the 1 above to a 0"
#endif

	/* disable the MPU */
	/* set the region for the task being scheduled */
	/* start with .text then .data */
	/* enable the MPU again */
}

void mpu_setup_supervisor(void) {
	/* supervisor has access to all of flash */
#if 1
#	warning "Graduate students must implement this function"
#	warning "otherwise change the 1 above to a 0"
#endif
	/* set the region for the .text section of the supervisor to be all of the
	 * supervisor flash */
	/* the supervisor should have access to all of SRAM */
	/* yes, technically we could do some SMEP/SMAP thing here, but that is
	 * overkill for this assignment :) */
}

void mpu_setup_periph(void) {
#if 1
#	warning "Graduate students must implement this function"
#	warning "otherwise change the 1 above to a 0"
#endif
	/* all peripheral space should be only accessible to the supervisor */
}


void mpu_fault_enable(void) {
	SYSCTRL.shcsr |= MEMFAULTENA;
}

ISR(mpu_fault) {
	int pid = current->ppid;
	printk(	"\n\r[!] MPU access violation in pid %d\n\r"
			"    Relaunching task\n\r", pid);
	create_task(get_task_header(pid-1), pid-1);
	return_to_user(get_current_sp());
}
