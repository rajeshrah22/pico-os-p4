#include <rt.h>
#include <svcall.h>


#define ULONG(x)	((unsigned long)(x))
int set_led_ring(const unsigned* buffer, size_t count) {
	return __syscall2(__NR_set_ring, ULONG(buffer), count);
}
