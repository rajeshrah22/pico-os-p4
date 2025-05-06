#include <stddef.h>

#include <ioregs.h>
#include <pio.h>

static const unsigned short pio_program[] = {
		0x6321u, //  0: out    x, 1            side 0 [3]
		0x1223u, //  1: jmp    !x, 3           side 1 [2]
		0x1200u, //  2: jmp    0               side 1 [2]
		0xa242u, //  3: nop                    side 0 [2]
	};


#define IO_BANK0_PIO_FN	(6)

__attribute__((constructor(104)))
void pio_init(void) {
	IO_BANK0.io[10].ctrl = IO_BANK0_PIO_FN;

	/* set pin as output */
	PIO0.sm[0].pinctrl =
				(1u << PIO_SM_SET_COUNT_OFFSET)		/* use one pin for set count */
			|	(10u << PIO_SM_SET_BASE_OFFSET)		/* set pin 10 as the base */
		;
	PIO0.sm[0].instr = 0xe081;	/* set PINDIR 1 */

	/* set sideset configuration */
	PIO0.sm[0].pinctrl =
				(1u << PIO_SM_SIDESET_COUNT_OFFSET)	/* use one sideset bit */
			|	(10u << PIO_SM_SIDESET_BASE_OFFSET)	/* set pin 10 as the base */
		;

	/* execution control */
	PIO0.sm[0].execctrl =
				(3u << PIO_SM_EXECCTRL_WRAP_TOP_OFFSET)
			|	(0u << PIO_SM_EXECCTRL_WRAP_BOTTOM_OFFSET)
		;

	
	/* clear FIFOs */
	PIO0.sm[0].shiftctrl |=
				(1u << PIO_SM_SHIFTCTRL_FJOIN_RX);
	PIO0.sm[0].shiftctrl &=
				~(1u << PIO_SM_SHIFTCTRL_FJOIN_RX);
	/* make TX FIFO wider by stealing the RX portion */
	PIO0.sm[0].shiftctrl |=
				(1u << PIO_SM_SHIFTCTRL_FJOIN_TX);

	/* set autoshift behavior! */
	PIO0.sm[0].shiftctrl |=
				(1u << PIO_SM_SHIFTCTRL_AUTOPULL)	/* autoshift behavior */
			|	(24u << PIO_SM_SHIFTCTRL_PULL_THRESH_OFFSET);

	/* TODO: set clock divider for FSM0 */
#	warning "set clock divider for FSM0"
	/* the system clock is being fed from the pll_sys, which is outputting a
 	 * 120 MHz clock; compute your divider so that 10 FSM ticks take 1.25
 	 * microseconds */

	PIO0.ctrl = 0;
	PIO0.ctrl = (PIO_CTRL_RESTART0);
	PIO0.ctrl = (PIO_CTRL_CLKDIV_RESTART0);
	PIO0.sm[0].instr = 0;	/* jump to start */

}

void pio_start(void) {
	for(size_t i = 0; i < sizeof(pio_program) / sizeof(pio_program[0]); i++) {
		PIO0.instr_mem[i] = pio_program[i];
	}
	PIO0.ctrl = PIO_CTRL_SM_ENABLE0;
}
