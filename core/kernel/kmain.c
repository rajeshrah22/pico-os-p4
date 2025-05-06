#include <mpu.h>
#include <printk.h>
#include <shpr.h>
#include <systick.h>
#include <task.h>

void* kernel_stack;

int kmain(void) {
	printk("\f  Booting kernel\n\r");

#if 1
#	warning "Set up the MPU if you are in the Graduate class"
#	warning "otherwise change the 1 above to a 0"
	mpu_setup_supervisor();
	mpu_setup_periph();
	printk("[ ] Supervisor memory map set\n\r");
	mpu_enable();
	mpu_fault_enable();
	printk("    MPU enabled\n\r");
#endif
//	gpio_init();
//	printk("[ ] GPIO driver initialized\n\r");
//	
	init_scheduler();
//
	create_task(get_task_header(0), 0);
	create_task(get_task_header(1), 1);
//
	systick_init();
//
//	mpu_setup_user(current);
//	printk("[ ] Ready  to launch user tasks\n\r\n\n");
	systick_init();
	exec(current->sp);

	while(1) {
		__asm__("wfe");
	}
}
