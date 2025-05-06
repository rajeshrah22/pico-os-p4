#ifndef RESETS_H
#define RESETS_H

#include <stdint.h>
#include "rp2040-map.h"

#define RESETS_USBCTRL (24)
#define RESETS_UART1 (23)
#define RESETS_UART0 (22)
#define RESETS_TIMER (21)
#define RESETS_TBMAN (20)
#define RESETS_SYSINFO (19)
#define RESETS_SYSCFG (18)
#define RESETS_SPI1 (17)
#define RESETS_SPI0 (16)
#define RESETS_RTC (15)
#define RESETS_PWM (14)
#define RESETS_PLL_USB (13)
#define RESETS_PLL_SYS (12)
#define RESETS_PIO1 (11)
#define RESETS_PIO0 (10)
#define RESETS_PADS_QSPI (9)
#define RESETS_PADS_BANK0 (8)
#define RESETS_JTAG (7)
#define RESETS_IO_QSPI (6)
#define RESETS_IO_BANK0 (5)
#define RESETS_I2C1 (4)
#define RESETS_I2C0 (3)
#define RESETS_DMA (2)
#define RESETS_BUSCTRL (1)
#define RESETS_ADC (0)

static inline void set_power(uint8_t reset_num, uint8_t reset_val) {

	if (reset_val)
		PSM_BASE[0] |= 1 << reset_num;
	else
		PSM_BASE[1] |= 1 << reset_num;

	while( !( PSM_BASE[2] &  (1 << reset_num)) );
}

/* 1 is device is in reset. 0 is not in reset. */
static inline void set_reset(uint8_t reset_num, uint8_t reset_val) {

	if (reset_val) {
		RESETS_BASE[0] |= 1 << reset_num;
		while( RESETS_BASE[2] &  (1 << reset_num) );
	} else {
		RESETS_BASE[0] &= ~(1 << reset_num);
		while( !(RESETS_BASE[2] &  (1 << reset_num)) );
	}

}

#endif // RESETS_H
