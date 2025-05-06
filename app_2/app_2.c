#include <stddef.h>

#include <rt.h>
#include <task.h>

void main(void) {
	int pid = getpid();
	print("[%x] Blink red LED\n\r", pid);
	while(1) {
		set_led(1);
		delay(1 << 22);
		set_led(0);
		delay(1 << 22);
	}
}

APPLICATION("app_2");
