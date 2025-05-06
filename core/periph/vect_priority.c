#include <shpr.h>

void setup_vect_priority(void) {
	SHPR1 = (1U << 4);
	SHPR2 = (2U << 4) << 24;
	SHPR3 = (3U << 4) << 24;
}
