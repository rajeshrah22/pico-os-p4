#include <interrupt.h>
#include <mpu.h>
#include <mpu_perms.h>
#include <printk.h>
#include <sysctrl.h>
#include <stacks.h>
#include <task.h>

/*
 *	Regions:
 *	1 - base no-access region  -- lower priority
 *	2 - Kernel code
 *	3 - Kernel data
 *	4 - peripherals
 *	5 - user text
 *	6 - user data
 */

void mpu_setup_user(struct task_struct* proc) {
#if 0
#	warning "Graduate students must implement this function"
#	warning "otherwise change the 1 above to a 0"
#endif

	/* disable the MPU */
	MPU.ctrl &= ~(MPU_REG_ENABLE);
	/* set the region for the task being scheduled */
	/* start with .text then .data */
	MPU.rnr = 5;
	MPU.rbar = (proc->text_start << 8);
	MPU.rasr = MPU_ATTRIB_UCODE | MPU_REG_SIZE_16K;

	MPU.rnr = 6;
	MPU.rbar = (proc->text_start << 8);
	MPU.rasr = MPU_ATTRIB_UDATA | MPU_REG_SiZE_16K;

	/* enable the MPU again */
	MPU.ctrl |= MPU_REG_ENABLE;
}

void mpu_setup_supervisor(void) {
	/* supervisor has access to all of flash */
#if 0
#	warning "Graduate students must implement this function"
#	warning "otherwise change the 1 above to a 0"
#endif
	/* set the region for the .text section of the supervisor to be all of the
	 * supervisor flash */
	/* the supervisor should have access to all of SRAM */
	/* yes, technically we could do some SMEP/SMAP thing here, but that is
	 * overkill for this assignment :) */
	MPU.ctrl &= ~(MPU_REG_ENABLE);
	MPU.rnr = 2;
	MPU.rbar = 0x10000000 << 8;  /* Kernel Base */
	MPU.rasr = MPU_ATTRIB_SCODE | MPU_REG_SIZE_16K;

	MPU.rnr = 6;
	MPU.rbar = (proc->text_start << 8);
	MPU.rasr = MPU_ATTRIB_UDATA | MPU_REG_SiZE_16K;

	/* enable the MPU again */
	MPU.ctrl |= MPU_REG_ENABLE;
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
