#include <bitmanip.h>
#include <clocks.h>
#include <resets.h>

__attribute__((constructor(101)))
void resets_init(void) {
	/* lift system PLL out of reset */
//	RESETS.reset &= ~(1u << RESETS_pll_sys);
//	loop_until_bit_is_set(RESETS.reset_done, RESETS_pll_sys);

	/* lift IO bank 0 out of reset */
	RESETS.reset &= ~(1 << RESETS_io_bank0);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_io_bank0);

	/* lift PIO0 out of reset */
	RESETS.reset &= ~(1 << RESETS_pio0);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_pio0);

	/* lift DMA out of reset */
	RESETS.reset &= ~(1 << RESETS_dma);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_dma);
}

__attribute__((constructor(102)))
void clocking_init(void) {
	/* enable the oscillator */
	XOSC.ctrl = XOSC_enable | XOSC_freq_range_1_15MHz;
	loop_until_bit_is_set(XOSC.status, XOSC_stable);

	/* enable the system PLL (120 MHz) */
	PLL_SYS.cs = 1;		/* program the reference clock divider */
	PLL_SYS.fbdiv_int = 120;	/* then the feedback divider */
	PLL_SYS.pwr &= ~(
				(1u << PLL_pwr_pd)		/* turn on main power */
			|	(1u << PLL_pwr_vcopd));	/* and VCO */
	loop_until_bit_is_set(PLL_SYS.cs, PLL_lock);	/* wait for VCO lock */

	PLL_SYS.prim =						/* set up postdividers */
					(6 << PLL_postdiv1_offset)
				|	(2 << PLL_postdiv2_offset);
	PLL_SYS.pwr &= ~(1u << PLL_pwr_postdivpd);	/* turn the postdividers */

	/* set the peripheral clock to the system PLL */
	CLOCKS.clk_peri_ctrl =
			(1u << CLOCKS_enable)
		|	(CLOCKS_PERI_clk_clksrc_pll_sys);	

	/* set the system clock to the system PLL */
	CLOCKS.clk_sys_ctrl = 0;
	loop_until_bit_is_set(CLOCKS.clk_sys_selected, 0);
	CLOCKS.clk_sys_ctrl = (CLOCKS_SYS_CTRL_CLKSRC_PLL_SYS);
	CLOCKS.clk_sys_ctrl |= CLOCKS_SYS_CTRL_CLKSRC_CLK_SYS_AUX;
	loop_until_bit_is_set(CLOCKS.clk_sys_selected, 1);
}

__attribute__((constructor(103)))
void resets_finish(void) {
	/* take SPI0 out of reset */
	RESETS.reset &= ~(1u << RESETS_spi0);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_spi0);
}
