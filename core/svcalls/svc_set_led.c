#include <ioregs.h>
#include <syscall_list.h>

int svc_set_led(unsigned int state) {
#	warning "must complete this function"
	if(state) {
		/* set LED on GP25 to high */
	} else {
		/* set LED on GP25 to low */
	}
	return 0;
}
