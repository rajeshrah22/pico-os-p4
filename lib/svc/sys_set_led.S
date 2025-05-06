#include <svcall.h>

	.syntax unified
	.thumb

decl_svcall set_led
	svc(set_led)
	bx lr
