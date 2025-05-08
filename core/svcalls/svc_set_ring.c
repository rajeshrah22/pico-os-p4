#include <stddef.h>

#include <pio.h>

extern unsigned pio_data[16];

int svc_setring(unsigned* data, size_t count) {
	int i = 0;
	/* need to check if DMA is active. */

	if (count > 16)
		return -2;

	while (i < count) {
		pio_data[i] = data[i] << 8;
		i++;
	}

	return i;
}
