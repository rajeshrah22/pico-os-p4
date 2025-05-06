#include <rt.h>
#include <svcall.h>

void set_led(unsigned int state) {
	__syscall1(__NR_set_led, state);
}
