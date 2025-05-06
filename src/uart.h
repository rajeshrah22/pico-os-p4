#ifndef _UART_H
#define _UART_H

#include <stdint.h>
#include "interrupt.h"

void uart_init(void);

int uart_putc(int c);
int uart_puts(const char *str);
int uart_async_write(const char *src, uint16_t len);
int uart_async_read(char *dest, uint16_t len);
void uart_rx_int_en(void);
void uart_tx_rx_int_en(void);

#endif /* _UART_H */
