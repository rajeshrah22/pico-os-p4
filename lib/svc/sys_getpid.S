#include <svcall.h>

	.syntax unified
	.thumb

decl_svcall getpid
	svc(getpid)
	bx lr
