#ifndef IOREGS_H__
#define IOREGS_H__

extern struct {
/* 000 */	volatile unsigned cpuid;
/* 004 */	volatile unsigned gpio_in;
/* 008 */	volatile unsigned gpio_hi_in;
/* 00c */	volatile unsigned __padding_0__;
/* 010 */	volatile unsigned gpio_out;
/* 014 */	volatile unsigned gpio_out_set;
/* 018 */	volatile unsigned gpio_out_clr;
/* 01c */	volatile unsigned gpio_out_xor;
/* 020 */	volatile unsigned gpio_oe;
/* 024 */	volatile unsigned gpio_oe_set;
/* 028 */	volatile unsigned gpio_oe_clr;
/* 02c */	volatile unsigned gpio_oe_xor;
} SIO;

extern struct {
	struct {
		volatile unsigned status;
		volatile unsigned ctrl;
	} io[30];
	volatile unsigned intr[4];
} IO_BANK0;

extern struct {
	volatile unsigned voltage_select;
	volatile unsigned gpio[30];
	volatile unsigned SWCLK;
	volatile unsigned SWD;
} PADS_BANK0;


#define LED_PIN		(25)


#endif
