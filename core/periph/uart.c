#include <stddef.h>
/* ssize_t is defined here for some reason? */
#include <stdio.h>

#include <bitmanip.h>
#include <interrupt.h>
#include <ioregs.h>
#include <uart.h>

/* must be a power of 2 */
#define RB_SIZE 64

#define BAUD 115200
/* this should match your configuration */
#define F_PERIPH 120000000ULL

static struct {
	size_t head;
	size_t tail;
	size_t count;
	unsigned char store[RB_SIZE];
} tx_buffer, rx_buffer;

__attribute__((constructor))
void uart_init(void) {
	#include <uart-baud.h>
	UART0.uartibrd = UARTIBRD_VALUE;
	UART0.uartfbrd = UARTFBRD_VALUE;

	UART0.uartlcr_h =
			(UART_WLEN_8 << UART_LCR_H_WLEN_OFFSET)
		;

	UART0.uartcr =	(1u << UART_CR_UARTEN)
				|	(1u << UART_CR_TXE)
				|	(1u << UART_CR_RXE)
				;

	UART0.uartimsc =
				(1u << UART_IMSC_TXIM)
			|	(1u << UART_IMSC_RXIM)
			;
}

int uart_putc(int c) {
	if(tx_buffer.count == RB_SIZE) {
		return -1;
	}
	tx_buffer.store[tx_buffer.head++] = ((unsigned char)c) & 0xffu;
	tx_buffer.head &= (RB_SIZE - 1);
	tx_buffer.count++;
	return c;
}

ssize_t uart_write(const void* m, size_t n) {
	const char* p = (const char*)m;
	ssize_t ret = 0;
	while(n--) {
		if(uart_putc(*p) < 0) {
			return ret;
		}
		ret += 1;
	}
	return ret;
}

void uart_puts(const char* str) {
	while(*str) {
		uart_putc(*str++);
	}
	/* we added data to the ring buffer, trigger the interrupt */
	NVIC_ISPR = (1u << NVIC_BIT(UART0_vect));
}


int uart_getc(void) {
	int ret;
	if(!rx_buffer.count) {
		return -1;
	}

	ret = rx_buffer.store[rx_buffer.tail++];
	rx_buffer.tail &= (RB_SIZE - 1);
	rx_buffer.count--;

	return ret;
}

ISR(UART0_vect) {
	/* the RP2040 groups all UART interrupts in the same channel */
	if(UART0.uartris & (1u << UART_RIS_RXRIS)) {
		/* receive path */
		unsigned rx_char = UART0.uartdr;
		if(rx_buffer.count == RB_SIZE) {
			/* no room, bail out */
			return;
		}
		if(rx_char & ~(0xff)) {
			/* bad data, discard */
			return;
		}
	
		rx_buffer.store[rx_buffer.head++] = rx_char & 0xff;
		rx_buffer.head &= (RB_SIZE - 1);
		rx_buffer.count++;
	}

	/* transmitter */
	UART0.uarticr = (1u << UART_ICR_TXICR);
	/* this should really be a deferred task */
	while(tx_buffer.count && bit_is_clear(UART0.uartfr, UART_FR_TXFF)) {
		UART0.uartdr = tx_buffer.store[tx_buffer.tail++];
		tx_buffer.tail &= (RB_SIZE - 1);
		tx_buffer.count--;
	}

	return;
}
