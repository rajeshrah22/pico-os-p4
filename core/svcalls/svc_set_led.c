#include <ioregs.h>
#include <syscall_list.h>

int svc_set_led(unsigned int state) {
	if(state) {
		SIO.gpio_oe_set = (1u << 25);
	} else {
		SIO.gpio_oe_clr = (1u << 25);
	}
	return 0;
}
