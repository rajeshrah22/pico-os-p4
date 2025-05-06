#include <stddef.h>

#include <rt.h>
#include <task.h>

void main(void) {
	const static unsigned strip_array[] = {
			0x00ff00,
			0x80ff00,
			0xffff00,
			0xff8000,
			0xff0000,
			0xff0080,
			0xff00ff,
			0x8000ff,
			0x0000ff,
			0x0080ff,
			0x00ffff,
			0x00ff80,
			0x000000,
			0x000000,
			0x00ff00,
			0x80ff00,
			0xffff00,
			0xff8000,
			0xff0000,
			0xff0080,
			0xff00ff,
			0x8000ff,
			0x0000ff,
			0x0080ff,
			0x00ffff,
			0x00ff80,
			0x000000
		};
	size_t offset = 0;

	while(1) {
		if(!set_led_ring(strip_array + offset, 16)) {
			offset += 1;
			offset &= 0xf;
		}

		delay(10000);
	}

}

APPLICATION("app_1");
