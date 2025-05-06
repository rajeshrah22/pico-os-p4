#include <syscall_list.h>

int svc_nil(void) {
	/* if you got here you broke it */
	__asm__ volatile("bkpt");
	return -1;
}
