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

extern unsigned int __data_start;

void mpu_setup_user(struct task_struct* proc) {
#if 0
#	warning "Graduate students must implement this function"
#	warning "otherwise change the 1 above to a 0"
#endif

	/* disable the MPU */
	mpu_disable();

	/* set the region for the task being scheduled */
	/* start with .text then .data */
	mpu_set_region(5, proc->text_start, MPU_ATTRIB_UCODE | MPU_REG_SIZE_16K);
	mpu_set_region(6, proc->data_start, MPU_ATTRIB_UDATA | MPU_REG_SIZE_16K);

	/* enable the MPU again */
	mpu_enable();
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
	mpu_disable();

	mpu_set_region(2, 0x10000000, MPU_ATTRIB_SCODE | MPU_REG_SIZE_2M);
	mpu_set_region(3, __data_start, MPU_ATTRIB_SDATA | MPU_REG_SIZE_2M);

	/* enable the MPU again */
	mpu_enable();
}

void mpu_setup_periph(void) {
#if 0
#	warning "Graduate students must implement this function"
#	warning "otherwise change the 1 above to a 0"
#endif
	mpu_disable();
	mpu_set_region(4, 0x40000000, ATTRIB_PERIPH_AREA1);
	mpu_enable();
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
