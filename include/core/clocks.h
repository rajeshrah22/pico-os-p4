#ifndef CLOCKS_H__
#define CLOCKS_H__

extern struct {
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
} CLOCKS;

#define CLOCKS_GPOUT_clksrc_pll_sys	((0) << (5))
#define CLOCKS_GPOUT_clksrc_gpin0	((1) << (5))
#define CLOCKS_GPOUT_clksrc_gpin1	((2) << (5))
#define CLOCKS_GPOUT_clksrc_pll_usb	((3) << (5))
#define CLOCKS_GPOUT_rosc_clksrc	((4) << (5))
#define CLOCKS_GPOUT_xosc_clksrc	((5) << (5))
#define CLOCKS_GPOUT_clk_sys		((6) << (5))
#define CLOCKS_GPOUT_clk_usb		((7) << (5))
#define CLOCKS_GPOUT_clk_adc		((8) << (5))
#define CLOCKS_GPOUT_clk_rtc		((9) << (5))
#define CLOCKS_GPOUT_clk_ref		((10) << (5))

#define CLOCKS_SYS_CTRL_SRC			(0)
#define CLOCKS_SYS_CTRL_AUXSRC_OFFSET	(5)
#define CLOCKS_SYS_CTRL_CLKSRC_CLK_SYS_AUX	(1)
#define CLOCKS_SYS_CTRL_CLKSRC_PLL_SYS	((0) << (5))
#define CLOCKS_SYS_CTRL_XOSC_CLKSRC		((3) << (5))

#define CLOCKS_PERI_clk_sys				((0) << (5))
#define CLOCKS_PERI_clk_clksrc_pll_sys	((1) << (5))
#define CLOCKS_PERI_clk_clksrc_pll_usb	((2) << (5))
#define CLOCKS_PERI_rosc_clksrc_ph		((3) << (5))
#define CLOCKS_PERI_xosc_clksrc			((4) << (5))
#define CLOCKS_PERI_clksrc_gpin0		((5) << (5))
#define CLOCKS_PERI_clksrc_gpin1		((6) << (5))

#define CLOCKS_kill					(10)
#define CLOCKS_enable				(11)

#ifdef __cplusplus
extern struct __xosc {
#else
extern struct {
#endif
	volatile unsigned ctrl;
	volatile unsigned status;
	volatile unsigned dormant;
	volatile unsigned startup;
	volatile unsigned count;
} XOSC;

#define XOSC_enable		((0xfabu) << (12))
#define XOSC_disable	((0xd1eu) << (12))
#define XOSC_freq_range_1_15MHz	((0xaa0u))
#define XOSC_stable		(31)
#define XOSC_enabled	(12)
#define XOSC_x4			(20)

extern struct {
	volatile unsigned cs;
	volatile unsigned pwr;
	volatile unsigned fbdiv_int;
	volatile unsigned prim;
} PLL_SYS, PLL_USB;

#define PLL_lock		(31)
#define PLL_bypass		(8)

#define PLL_pwr_pd		(0)
#define PLL_pwr_vcopd	(5)
#define PLL_pwr_postdivpd	(3)

#define PLL_postdiv1_offset	(16)
#define PLL_postdiv2_offset	(12)

#endif
