#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>
#include <stdint.h>
#include "rp2040-map.h"

#define GPIO_FUNC_SPI 1
#define GPIO_FUNC_UART 2
#define GPIO_FUNC_I2C 3
#define GPIO_FUNC_PWM 4
#define GPIO_FUNC_SIO 5
#define GPIO_FUNC_PIO0 6
#define GPIO_FUNC_PIO1 7
#define GPIO_FUNC_CLOCK 8
#define GPIO_FUNC_USB 9

#define PADS_BANK_GPIO_PUE_SHIFT 3
#define PADS_BANK_GPIO_PDE_SHIFT 2

static inline void set_pinfunc(uint8_t pin, uint8_t func) {
	IO_BANK0_BASE[1 + (pin * 2)] = func;
}

static inline void set_pullup(uint8_t pin, bool enable) {
	if (enable) {
		PADS_BANK0_BASE[1 + pin] |= BIT(PADS_BANK_GPIO_PUE_SHIFT);
	} else {
		PADS_BANK0_BASE[1 + pin] &= NBIT(PADS_BANK_GPIO_PUE_SHIFT);
	}
}

static inline void set_pulldown(uint8_t pin, bool enable) {
	if (enable) {
		PADS_BANK0_BASE[1 + pin] |= BIT(PADS_BANK_GPIO_PDE_SHIFT);
	} else {
		PADS_BANK0_BASE[1 + pin] &= NBIT(PADS_BANK_GPIO_PDE_SHIFT);
	}
}

#endif // GPIO_H
