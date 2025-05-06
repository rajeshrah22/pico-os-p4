#include <stddef.h>

#include "rp2040-map.h"
#include "pio.h"

static const unsigned short pio_program[] = {
	0x6321u, //  0: out    x, 1            side 0 [3]
	0x1223u, //  1: jmp    !x, 3           side 1 [2]
	0x1200u, //  2: jmp    0               side 1 [2]
	0xa242u, //  3: nop                    side 0 [2]
};

#define IO_BANK0_PIO_FN	(6)

void pio_init(void) {
	struct pio *pio0 = (struct pio *)PIO0_BASE;

	/* set pin as output */
	pio0->sm[0].pinctrl =
				(1u << PIO_SM_SET_COUNT_OFFSET)		/* use one pin for set count */
			|	(10u << PIO_SM_SET_BASE_OFFSET)		/* set pin 10 as the base */
		;
	pio0->sm[0].instr = 0xe081;	/* set PINDIR 1 */

	/* set sideset configuration */
	pio0->sm[0].pinctrl =
				(1u << PIO_SM_SIDESET_COUNT_OFFSET)	/* use one sideset bit */
			|	(10u << PIO_SM_SIDESET_BASE_OFFSET)	/* set pin 10 as the base */
		;

	/* execution control */
	pio0->sm[0].execctrl =
				(3u << PIO_SM_EXECCTRL_WRAP_TOP_OFFSET)
			|	(0u << PIO_SM_EXECCTRL_WRAP_BOTTOM_OFFSET)
		;

	
	/* clear FIFOs */
	pio0->sm[0].shiftctrl |=
				(1u << PIO_SM_SHIFTCTRL_FJOIN_RX);
	pio0->sm[0].shiftctrl &=
				~(1u << PIO_SM_SHIFTCTRL_FJOIN_RX);
	/* make TX FIFO wider by stealing the RX portion */
	pio0->sm[0].shiftctrl |=
				(1u << PIO_SM_SHIFTCTRL_FJOIN_TX);

	/* set autoshift behavior! */
	pio0->sm[0].shiftctrl |=
				(1u << PIO_SM_SHIFTCTRL_AUTOPULL);

	/* TODO: set clock divider for FSM0 */
	pio0->sm[0].clkdiv = (19u << 16) | (132u << 7);

	pio0->ctrl = 0;
	pio0->ctrl = (PIO_CTRL_RESTART0);
	pio0->ctrl = (PIO_CTRL_CLKDIV_RESTART0);
	pio0->sm[0].instr = 0;	/* jump to start */
}

void pio_start(void) {
	struct pio *pio0 = (struct pio *)PIO0_BASE;

	for(size_t i = 0; i < sizeof(pio_program) / sizeof(pio_program[0]); i++) {
		pio0->instr_mem[i] = pio_program[i];
	}
	pio0->ctrl = PIO_CTRL_SM_ENABLE0;
}
