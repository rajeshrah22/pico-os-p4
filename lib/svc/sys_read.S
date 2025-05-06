#include <svcall.h>
	.syntax unified
	.thumb

decl_svcall read
	svc(read)
	bx lr
