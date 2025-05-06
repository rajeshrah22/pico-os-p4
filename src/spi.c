#include "spi.h"

#include <stddef.h>
#include <stdint.h>
#include "rp2040-map.h"
#include "helpers.h"
#include "interrupt.h"

#define SPI_CTRL0_REG 0x00
#define SPI_CTRL1_REG 0x01
#define SPI_DATA_REG 0x02
#define SPI_STATUS_REG 0x03
#define SPI_CLK_DIV_REG 0x04

#define SPI_STATUS_BUSY_SHIFT 4
#define SPI_STATUS_TX_NOT_FULL_SHIFT 1

#define SPI_CTRL0_MODE_SHIFT 6
#define SPI_CTRL0_DATA_SIZE_8 0x07
#define SPI_CTRL0_DATA_SIZE_16 0x0F

#define SPI_CTRL1_SSE_EN 0x2

#define SPI_SSPIMSC 5
#define SPI_SSPIMSC_TXIM 0x2

#define CLK_PERI_HZ 12000000
#define TARGET_HZ 120000

#define SSPCLK CLK_PERI_HZ

#define CPSDVSR (SSPCLK / TARGET_HZ)

static void (*spi_callback)(void) = NULL;

void init_spi(uint8_t mode) {

	mode |= mode << 2;
	mode >>= 1;

	SPI0_BASE[SPI_CTRL0_REG] = (mode & 0x3) << SPI_CTRL0_MODE_SHIFT | SPI_CTRL0_DATA_SIZE_16;
	SPI0_BASE[SPI_CLK_DIV_REG] = CPSDVSR;

	SPI0_BASE[SPI_CTRL1_REG] |= SPI_CTRL1_SSE_EN;
}

void spi_asign_tx_int(int enable) {
	if(enable)
		SPI0_BASE[SPI_SSPIMSC] |= SPI_SSPIMSC_TXIM;
	else
		SPI0_BASE[SPI_SSPIMSC] &= ~SPI_SSPIMSC_TXIM;
}

uint16_t spi_transfer(uint16_t data) {
	SPI0_BASE[SPI_DATA_REG] = data;
	loop_until_bit_is_clear(SPI0_BASE[SPI_STATUS_REG], SPI_STATUS_BUSY_SHIFT);
	return SPI0_BASE[SPI_DATA_REG];
}

size_t spi_fill_tx_fifo(const uint16_t* data, size_t len) {
	size_t count = 0;

	while((SPI0_BASE[SPI_STATUS_REG] & (1 << SPI_STATUS_TX_NOT_FULL_SHIFT)) && count < len) {
		SPI0_BASE[SPI_DATA_REG] = data[count++];
	}

	return count;
}

void spi_set_callback(void (*callback)(void)) {
	spi_callback = callback;
}

ISR(SPI0_vect) {
	if(spi_callback) {
		spi_callback();
	}
}
