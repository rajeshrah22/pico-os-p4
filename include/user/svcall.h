#ifndef SVCALL_H__
#define SVCALL_H__


#define __NR_nil		0
#define __NR_write		1
#define __NR_read		2
#define __NR_execve		3
#define __NR_get_button	4
#define __NR_set_led	5
#define __NR_getpid		6
#define __NR_set_ring	7

#ifndef __ASSEMBLER__
#include <stddef.h>

static inline unsigned __syscall2(
			unsigned nr,
			unsigned long r0,
			unsigned long r1) {

	__asm__ volatile (
		"movs r12, %[nr]"	"\n"
		"movs r0, %[r0]"	"\n"
		"movs r1, %[r1]"	"\n"
		"svc #0"
		:	[r0]"+r"(r0)
		:	[nr]"r"(nr), [r1]"r"(r1)
		: "r0", "r1", "r12", "memory"
	);

	return r0;
}

static inline unsigned __syscall1(
			unsigned nr,
			unsigned long r0) {

	__asm__ volatile(
		"movs r12, %[nr]"	"\n"
		"movs r0, %[r0]"	"\n"
		"svc #0"
		:	[r0]"+r"(r0)
		:	[nr]"r"(nr)
		: "r0", "r12", "memory"
	);

	return r0;
		
}

#if 0
/* XXX: these macros are defined for ARMv-6M */

#define __syscall2(nr, r0, r1) ({\
		register unsigned long r_0 asm("r0") = (unsigned long)r0; \
		register unsigned long r_1 asm("r1") = (unsigned long)r1; \
		__asm__ ( \
				"movs r4, #" #nr	"\n" \
				"movs r12, r4"	"\n" \
				"svc #0"			"\n" \
			: \
			: "r"(r_0), "r"(r_1) \
			: "r4", "r12", "memory" \
		); \
		r_0; })

#define __syscall1(nr, r0) ({ \
		register unsigned long r_0 asm("r0") = (unsigned long)r0; \
		__asm__ ( \
				"movs r4, #" #nr	"\n" \
				"movs r12, r4"		"\n" \
				"svc #0"			"\n" \
			: \
			: "r"(r_0) \
			: "r4", "r12", "memory" \
		); \
		r_0; })

#define syscall2(nr, r0, r1) \
		__syscall2(nr, r0, r1)

#define syscall1(nr, r0) \
		__syscall1(nr, r0)

#endif

#else

.macro _svc name
	movs r4, #\name
	mov r12, r4
	svc #0
.endm

#define svc(name) _svc(__NR_##name)

.macro decl_svcall name
	.section .text.__sys_\name
	.globl __sys_\name
	.type __sys_\name\(), %function
__sys_\name:
.endm

#endif

#endif
