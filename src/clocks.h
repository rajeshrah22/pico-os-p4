#ifndef CLOCKS_H
#define CLOCKS_H

struct clocks {
/* 000 */	volatile unsigned clk_gpout0_ctrl;
/* 004 */	volatile unsigned clk_gpout0_div;
/* 008 */	volatile unsigned clk_gpout0_selected;
/* 00c */	volatile unsigned clk_gpout1_ctrl;
/* 010 */	volatile unsigned clk_gpout1_div;
/* 014 */	volatile unsigned clk_gpout1_selected;
/* 018 */	volatile unsigned clk_gpout2_ctrl;
/* 01c */	volatile unsigned clk_gpout2_div;
/* 020 */	volatile unsigned clk_gpout2_selected;
/* 024 */	volatile unsigned clk_gpout3_ctrl;
/* 028 */	volatile unsigned clk_gpout3_div;
/* 02c */	volatile unsigned clk_gpout3_selected;
/* 030 */	volatile unsigned clk_ref_ctrl;
/* 034 */	volatile unsigned clk_ref_div;
/* 038 */	volatile unsigned clk_ref_selected;
/* 03c */	volatile unsigned clk_sys_ctrl;
/* 040 */	volatile unsigned clk_sys_div;
/* 044 */	volatile unsigned clk_sys_selected;
/* 048 */	volatile unsigned clk_peri_ctrl;
/* 04c */	volatile unsigned __reserved_1;		/* ??? */
/* 050 */	volatile unsigned clk_peri_selected;
/* 054 */	volatile unsigned clk_usb_ctrl;
/* 058 */	volatile unsigned clk_usb_div;
/* 05c */	volatile unsigned clk_usb_selected;
/* 060 */	volatile unsigned clk_adc_ctrl;
/* 064 */	volatile unsigned clk_adc_div;
/* 068 */	volatile unsigned clk_adc_selected;
/* 06c */	volatile unsigned clk_rtc_ctrl;
/* 070 */	volatile unsigned clk_rtc_div;
/* 074 */	volatile unsigned clk_rtc_selected;
/* 078 */	volatile unsigned clk_sys_resus_ctrl;
/* 07c */	volatile unsigned clk_sys_resus_status;
/* 080 */	volatile unsigned fc0_ref_khz;
/* 084 */	volatile unsigned fc0_min_khz;
/* 088 */	volatile unsigned fc0_max_khz;
/* 08c */	volatile unsigned fc0_delay;
/* 090 */	volatile unsigned fc0_interval;
/* 094 */	volatile unsigned fc0_src;
/* 098 */	volatile unsigned fc0_status;
/* 09c */	volatile unsigned fc0_result;
/* 0a0 */	volatile unsigned wake_en0;
/* 0a4 */	volatile unsigned wake_en1;
/* 0a8 */	volatile unsigned sleep_en0;
/* 0ac */	volatile unsigned sleep_en1;
/* 0b0 */	volatile unsigned enabled0;
/* 0b4 */	volatile unsigned enabled1;
/* 0b8 */	volatile unsigned intr;
/* 0bc */	volatile unsigned inte;
/* 0c0 */	volatile unsigned intf;
/* 0c4 */	volatile unsigned ints;
};

struct pll {
	volatile unsigned cs;
	volatile unsigned pwr;
	volatile unsigned fbdiv_int;
	volatile unsigned prim;
};

#include <stdint.h>
#include "rp2040-map.h"
#include "helpers.h"

#define XOSC_CTRL	(0)
#define XOSC_STATUS	(1)

#define XOSC_EN		((0xfabu) << (12))
#define XOSC_DIS	((0xd1eu) << (12))
#define XOSC_1_15MHz	((0xaa0u))
#define XOSC_STABLE	(31)
#define XOSC_ENABLED	(12)

#define CLOCKS_CTRL_ENABLED	28
#define CLOCKS_CTRL_ENABLE	11

#define CLOCKS_SYS_CTRL	15
#define CLOCKS_SYS_CTRL_SRC_AUX 1
#define CLOCKS_SYS_CTRL_SRC_REF 0

#define CLOCKS_PERIF_CTRL	18
#define CLOCKS_CTRL_XOSC_SRC	4
#define CLOCKS_CTRL_SRC_SHIFT	5

#define CLOCKS_RTC_CTRL		27
#define CLOCKS_RTC_CTRL_XOSC_SRC 3

#define CLOCKS_RTC_DIV		28

#define PLL_CS_REG		0
#define PLL_CS_LOCK_SHIFT	31

#define PLL_PWR_REG		1
#define PLL_PWR_PD_SHIFT	0
#define PLL_PWR_POSTDIVPD_SHIFT	3
#define PLL_PWR_VCOPD_SHIFT	5

#define PLL_FBDIV_INT_REG	2

#define PLL_PRIM_REG		3
#define PLL_PRIM_PDIV1_SHIFT	16
#define PLL_PRIM_PDIV2_SHIFT	12

static inline void init_xosc(void) {
	XOSC_BASE[XOSC_CTRL] = XOSC_EN | XOSC_1_15MHz;
	loop_until_bit_is_set(XOSC_BASE[XOSC_STATUS], XOSC_STABLE);
}

static inline void set_perif_clock_xosc(void) {
	// Set XOSC as the source of the perif clock
	//CLOCKS_BASE[18] &= ~BIT(CLOCKS_CTRL_ENABLE);
	//loop_until_bit_is_clear(CLOCKS_BASE[18], CLOCKS_CTRL_ENABLED);
	//for (volatile int i = 0; i < 1000; i++)
	//	nop();
	CLOCKS_BASE[CLOCKS_PERIF_CTRL] = CLOCKS_CTRL_XOSC_SRC << CLOCKS_CTRL_SRC_SHIFT;
	CLOCKS_BASE[CLOCKS_PERIF_CTRL] |= 1 << CLOCKS_CTRL_ENABLE;
	//loop_until_bit_is_set(CLOCKS_BASE[18], CLOCKS_CTRL_ENABLED);
}

static inline void set_rtc_clock_xosc(void) {
	// Set XOSC as the source of the perif clock
	//CLOCKS_BASE[18] &= ~BIT(CLOCKS_CTRL_ENABLE);
	//loop_until_bit_is_clear(CLOCKS_BASE[18], CLOCKS_CTRL_ENABLED);
	//for (volatile int i = 0; i < 1000; i++)
	//	nop();
	CLOCKS_BASE[CLOCKS_RTC_CTRL] = CLOCKS_RTC_CTRL_XOSC_SRC << CLOCKS_CTRL_SRC_SHIFT;
	CLOCKS_BASE[CLOCKS_RTC_CTRL] |= 1 << CLOCKS_CTRL_ENABLE;
	//loop_until_bit_is_set(CLOCKS_BASE[18], CLOCKS_CTRL_ENABLED);
}

static inline void set_sys_clock_pll_sys(void) {
	// Set the system clock to use the PLL_SYS
	CLOCKS_BASE[CLOCKS_SYS_CTRL] = CLOCKS_SYS_CTRL_SRC_AUX;
}

static inline void set_usb_pll(void) {
	PLL_USB_BASE[PLL_CS_REG] = 1; // REFDIV = 1
	PLL_USB_BASE[PLL_FBDIV_INT_REG] = 100; // 12MHz*4 = 1200MHz

	// Power up the PLL
	PLL_USB_BASE[PLL_PWR_REG] &= NBIT(PLL_PWR_PD_SHIFT) & NBIT(PLL_PWR_VCOPD_SHIFT);

	// Wait for PLL to lock
	loop_until_bit_is_set(PLL_USB_BASE[PLL_CS_REG], PLL_CS_LOCK_SHIFT);

	// 1200MHz / (5 * 5) = 48MHz
	PLL_USB_BASE[PLL_PRIM_REG] = (5 << PLL_PRIM_PDIV1_SHIFT) | (5 << PLL_PRIM_PDIV2_SHIFT);

	// Enable PLL output
	PLL_USB_BASE[PLL_PWR_REG] &= NBIT(PLL_PWR_POSTDIVPD_SHIFT);
}

static inline void set_sys_pll(void) {
	PLL_SYS_BASE[PLL_CS_REG] = 1; // REFDIV = 1
	PLL_SYS_BASE[PLL_FBDIV_INT_REG] = 125; // 12MHz*4 = 1200MHz

	// Power up the PLL
	PLL_SYS_BASE[PLL_PWR_REG] &= NBIT(PLL_PWR_PD_SHIFT) & NBIT(PLL_PWR_VCOPD_SHIFT);

	// Wait for PLL to lock
	loop_until_bit_is_set(PLL_SYS_BASE[PLL_CS_REG], PLL_CS_LOCK_SHIFT);

	// 1200MHz / (5 * 5) = 48MHz
	PLL_SYS_BASE[PLL_PRIM_REG] = (5 << PLL_PRIM_PDIV1_SHIFT) | (2 << PLL_PRIM_PDIV2_SHIFT);

	// Enable PLL output
	PLL_SYS_BASE[PLL_PWR_REG] &= NBIT(PLL_PWR_POSTDIVPD_SHIFT);
}

#endif // CLOCKS_H
