#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "rp2040-map.h"
#include "helpers.h"
#include "gpio.h"
#include "resets.h"
#include "clocks.h"
#include "uart.h"

#define LED_PIN (25)

static inline void set_uart0_pinmux(void);

int main(void) {
	init_xosc();
	set_perif_clock_xosc();

	set_reset(RESETS_PLL_SYS, 0);
	set_sys_pll();

	set_sys_clock_pll_sys();

	set_reset(RESETS_IO_BANK0, 0);
	set_reset(RESETS_UART0, 0);

	set_uart0_pinmux();

	set_pinfunc(LED_PIN, 5);

	SIO_BASE[9] = 1 << LED_PIN; // OE_SET

	uart_init();
	uart_tx_rx_int_en();

	while(1) {
		delay(10000000);
		SIO_BASE[7] = 1 << LED_PIN; // OUT_XOR
	}

	return 0;
}

static inline void set_uart0_pinmux(void) {
	set_pinfunc(0, GPIO_FUNC_UART); /* TX, PICO PIN 1 */
	set_pinfunc(1, GPIO_FUNC_UART); /* RX, PICO PIN 2 */
}
