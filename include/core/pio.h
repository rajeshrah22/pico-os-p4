#ifndef PIO_H__
#define PIO_H__

extern struct {
/* 000 */	volatile unsigned ctrl;
/* 004 */	volatile unsigned fstat;
/* 008 */	volatile unsigned fdebug;
/* 00c */	volatile unsigned flevel;
/* 010 */	volatile unsigned txf[4];
/* 020 */	volatile unsigned rxf[4];
/* 030 */	volatile unsigned smirq;
/* 034 */	volatile unsigned irq_force;
/* 038 */	volatile unsigned input_sync_bypass;
/* 03c */	volatile unsigned dbg_padout;
/* 040 */	volatile unsigned dbg_padoe;
/* 044 */	volatile unsigned dbg_cfginfo;
/* 048 */	volatile unsigned instr_mem[32];
	struct {
/* 0c8 + 24n */		volatile unsigned clkdiv;
/* 0cc + 24n */		volatile unsigned execctrl;
/* 0d0 + 24n */		volatile unsigned shiftctrl;
/* 0d4 + 24n */		volatile unsigned addr;
/* 0d8 + 24n */		volatile unsigned instr;
/* 0dc + 24n */		volatile unsigned pinctrl;
	} sm[4];
/* 128 */	volatile unsigned intr;
	struct {
/* 12c + 12n */		volatile unsigned inte;
/* 130 + 12n */		volatile unsigned intf;
/* 134 + 12n */		volatile unsigned ints;
	} irq[2];
} PIO0, PIO1;

#define PIO_FSTAT_TXFULL0	(16)
#define PIO_FSTAT_TXFULL1	(17)
#define PIO_FSTAT_TXFULL2	(18)
#define PIO_FSTAT_TXFULL3	(19)

/* control registers bitfields */
#define PIO_CTRL_RESTART0			((1) << (4))
#define PIO_CTRL_RESTART1			((1) << (5))
#define PIO_CTRL_RESTART2			((1) << (6))
#define PIO_CTRL_RESTART3			((1) << (7))
#define PIO_CTRL_CLKDIV_RESTART0	((1) << (8))
#define PIO_CTRL_CLKDIV_RESTART1	((1) << (9))
#define PIO_CTRL_CLKDIV_RESTART2	((1) << (10))
#define PIO_CTRL_CLKDIV_RESTART3	((1) << (11))

#define PIO_CTRL_SM_ENABLE0	((1) << (0))
#define PIO_CTRL_SM_ENABLE1	((1) << (1))
#define PIO_CTRL_SM_ENABLE2	((1) << (2))
#define PIO_CTRL_SM_ENABLE3	((1) << (3))


/* state machine bitfields */
#define PIO_SM_SET_COUNT_OFFSET	(26)
#define PIO_SM_SET_BASE_OFFSET	(5)

#define PIO_SM_SHIFTCTRL_FJOIN_RX	(31)
#define PIO_SM_SHIFTCTRL_FJOIN_TX	(30)
#define PIO_SM_SHIFTCTRL_AUTOPULL	(17)
#define PIO_SM_SHIFTCTRL_PULL_THRESH_OFFSET	(25)


#define PIO_SM_EXECCTRL_WRAP_TOP_OFFSET		(12)
#define PIO_SM_EXECCTRL_WRAP_BOTTOM_OFFSET	(7)

#define PIO_SM_SIDESET_COUNT_OFFSET	(29)
#define PIO_SM_SIDESET_BASE_OFFSET	(10)

#endif
