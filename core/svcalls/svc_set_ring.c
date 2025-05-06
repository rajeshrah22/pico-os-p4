#include <stddef.h>

#include <pio.h>

extern unsigned pio_data[16];

int svc_setring(unsigned* data, size_t count) {
#	warning "function must be implemented\n" \
		"- if DMA is active for the PIO then return -1\n"	\
		"- if count is greater than 16 then return -2\n" \
		"- otherwise, copy from data into pio_data, setup DMA and fire away"
	/* notice: shift every piece of data by 8 bits to the left as you store it
	 * in the buffer! */
}
