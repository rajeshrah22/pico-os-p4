#include <svcall.h>

	.syntax unified
	.thumb

decl_svcall get_button
	push {r4, lr}
	svc(get_button)
	pop {r4, pc}
