#ifndef RESETS_H__
#define RESETS_H__

extern struct {
	volatile unsigned reset;
	volatile unsigned wdsel;
	volatile unsigned reset_done;
} RESETS;

/* RESETS */
#define RESETS_dma			(2)
#define RESETS_io_bank0		(5)
#define RESETS_pio0			(10)
#define RESETS_pio1			(11)
#define RESETS_pll_sys		(12)
#define RESETS_pwm			(14)
#define RESETS_spi0			(16)
#define RESETS_spi1			(17)
#define RESETS_uart0		(22)

#endif	/* RESETS_H__ */
