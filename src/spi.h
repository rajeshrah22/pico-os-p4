#ifndef SPI_H
#define SPI_H

#include <stddef.h>
#include <stdint.h>


void init_spi(uint8_t mode);
uint16_t spi_transfer(uint16_t data);

size_t spi_fill_tx_fifo(const uint16_t* data, size_t len);
void spi_set_callback(void (*callback)(void));
void spi_asign_tx_int(int enable);

#endif // SPI_H
