#ifndef SYSCTRL_H__
#define SYSCTRL_H__

extern struct {
	const unsigned cpuid;
	volatile unsigned icsr;
	volatile unsigned vtor;
	volatile unsigned aircr;
	volatile unsigned scr;
	volatile unsigned ccr;
#if __ARM_ARCH == 7
	volatile unsigned shpr1;
#elif __ARM_ARCH == 6
	const unsigned __reserved;
#else
#	error "architecture not supported
#endif
	volatile unsigned shpr2;
	volatile unsigned shpr3;
	volatile unsigned shcsr;
} SYSCTRL;

#endif
