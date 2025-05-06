#include <svcall.h>
	.syntax unified
	.thumb

decl_svcall write
	push {r4, lr}
	svc(write)
	pop {r4, pc}
