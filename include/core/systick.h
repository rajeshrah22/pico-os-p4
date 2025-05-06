#ifndef SYSTICK_H__
#define SYSTICK_H__

#define SYST_ENABLE	(1 << 0)
#define SYST_TICKINT	(1 << 1)
#define SYST_CLKSOURCE	(1 << 2)
#define SYST_COUNTFLAG	(1 << 16)

/* F_CPU = 12MHz, 80000ticks */
#define SYST_TOP	(0x1d4c0)

#ifndef __ASSEMBLER__
extern struct {
	volatile unsigned csr;
	volatile unsigned rvr;
	volatile unsigned cvr;
	volatile unsigned calib;
} SYSTICK;


void systick_init(void);

#endif

#endif
