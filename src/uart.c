#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "uart.h"
#include "resets.h"
#include "rp2040-map.h"
#include "interrupt.h"

#define CLK_PERI_HZ 10000000

#define UART_UARTCR 12
#define UART_UARTCR_UARTEN_BITS		0x00000001
#define UART_UARTCR_TXE_BITS		0x00000100
#define UART_UARTCR_RXE_BITS		0x00000200

#define UART_UARTFR 6
#define UART_UARTFR_TXFF_BITS		0x00000020
#define UART_UARTFR_RXFE_BITS		0x00000010
#define UART_UARTFR_BSY_BITS		0x00000008

#define UART_UARTIBRD 9
#define UART_UARTFBRD 10

#define UART_LCR_H 11
#define UART_WLEN_8		(0x3)
#define UART_WLEN_7		(0x2)
#define UART_WLEN_6		(0x1)
#define UART_WLEN_5		(0x0)
#define UART_LCR_H_WLEN_OFFSET	(5)
#define UART_LCR_H_FEN_OFFSET	(4)

#define UART_UARTIFLS	13
#define UART_IFLS_TX_HALF_BITS	(0x2)
#define UART_IFLS_RX_HALF_BITS	(0x2 << 3)

#define UARTIMSC 14
#define UART_RX_INT_EN_OFFSET (4)
#define UART_TX_INT_EN_OFFSET (5)

#define UART_UARTRIS	(15)

#define UARTICR		(0x11)

#define BAUD 115200
#define F_PERIPH 12000000ULL

#define UARTBAUDRATE_DIV \
	((8u * (F_PERIPH) / (BAUD)) + 1)

#define UARTIBRD_PRE_VALUE ( (UARTBAUDRATE_DIV) >> (7) )

#define UARTIBRD_VALUE ( ( (UARTIBRD_PRE_VALUE) == 0) ? 1 : \
			( (UARTIBRD_PRE_VALUE) >= 65535 ? 65535 : \
				(UARTIBRD_PRE_VALUE) ) )

#define UARTFBRD_VALUE ( ( ((UARTIBRD_PRE_VALUE) == 0 \
			|| (UARTIBRD_PRE_VALUE) >= 65535) \
		? 0 : (((UARTBAUDRATE_DIV) & 0x7f) >> 1) ) )

#define TX_BUF_SIZE	256
#define TX_BUF_MASK (TX_BUF_SIZE - 1)

#define RX_BUF_SIZE	256
#define RX_BUF_MASK (RX_BUF_SIZE - 1)

struct circ_buf {
	uint8_t data[TX_BUF_SIZE];
	uint16_t inptr;
	uint16_t outptr;
};

struct circ_buf tx_ring;
struct circ_buf rx_ring;

static void uart_tx(void);
static void uart_rx(void);

void uart_init(void) {
	UART0_BASE[UART_UARTIBRD] = UARTIBRD_VALUE;
	UART0_BASE[UART_UARTFBRD] = UARTFBRD_VALUE;

	UART0_BASE[UART_LCR_H] = (UART_WLEN_8 << UART_LCR_H_WLEN_OFFSET)
				 | (1u << UART_LCR_H_FEN_OFFSET);
	UART0_BASE[UART_UARTCR] = UART_UARTCR_UARTEN_BITS
				  | UART_UARTCR_TXE_BITS
				  | UART_UARTCR_RXE_BITS;
}

static inline void setup_nvic_uart() {
	*NVIC_ISER |= 1u << NVIC_BIT(UART0_vect);
}

void uart_rx_int_en(void) {
	setup_nvic_uart();
	UART0_BASE[UARTIMSC] |= (1u << UART_RX_INT_EN_OFFSET);
}

void uart_tx_rx_int_en(void) {
	setup_nvic_uart();

	UART0_BASE[UART_UARTIFLS] |= UART_IFLS_TX_HALF_BITS;
	UART0_BASE[UART_UARTIFLS] |= UART_IFLS_RX_HALF_BITS;
	UART0_BASE[UARTIMSC] |= (1u << UART_TX_INT_EN_OFFSET);
	UART0_BASE[UARTIMSC] |= (1u << UART_RX_INT_EN_OFFSET);
}

static inline void uart_tx_int_clear(void) {
		UART0_BASE[UARTICR] = 1<<5;
}

static inline void uart_rx_int_clear(void) {
		UART0_BASE[UARTICR] = 1<<4;
}

static inline void uart_send(char c) {
	do {} while (UART0_BASE[UART_UARTFR] & UART_UARTFR_TXFF_BITS);
	*((uint8_t *)UART0_BASE) = c;
}

static inline int uart_send_nopoll(char c) {
	if (UART0_BASE[UART_UARTFR] & UART_UARTFR_TXFF_BITS)
		return -1;

	*((uint8_t *)UART0_BASE) = c;

	return 0;
}

static int uart_getc(void) {
	if (UART0_BASE[UART_UARTFR] & UART_UARTFR_RXFE_BITS)
		return -1;

	return *((uint8_t *)UART0_BASE);
}

int uart_putc(int c) {
	return uart_async_write((const char *)&c, 1);
}

int uart_puts(const char *str) {
	return uart_async_write(str, strlen(str));
}

/* tx circ buffer producer */
int uart_async_write(const char *str, uint16_t len) {
	uint8_t i = 0;
	uint16_t next;

	while (i < len) {
		next = (tx_ring.inptr + 1) & TX_BUF_MASK;
		if (next == tx_ring.outptr)
			break;

		tx_ring.data[tx_ring.inptr] = str[i];
		tx_ring.inptr = next;
		i++;
	}

	uart_tx();

	return i + 1;
}

/* rx circ buffer consumer */
int uart_async_read(char *dest, uint16_t len) {
	uint8_t i = 0;

	while (i < len && rx_ring.inptr != rx_ring.outptr) {
		dest[i] = rx_ring.data[rx_ring.outptr];
		rx_ring.outptr = (rx_ring.outptr + 1) & TX_BUF_MASK;
		i++;
	}

	return i + 1;
}

/* tx circ buffer consumer */
static void uart_tx(void) {
	while (tx_ring.outptr != tx_ring.inptr) {
		uint8_t c = tx_ring.data[tx_ring.outptr];
		int res = uart_send_nopoll(c);
		if (res == -1)
			break;

		tx_ring.outptr = (tx_ring.outptr + 1) & TX_BUF_MASK;
	}
}

/* rx circ buffer producer */
static void uart_rx(void) {
	int c;
	uint16_t next;

	while (1) {
		next = (rx_ring.inptr + 1) & RX_BUF_MASK;
		if (next == rx_ring.outptr)
			break;

		c = uart_getc();
		if (c == -1)
			break;

		rx_ring.data[rx_ring.inptr] = c;
		rx_ring.inptr = next;
	}
}

ISR(UART0_vect) {
	uint16_t int_status = UART0_BASE[UART_UARTRIS];

	if (int_status & (1u << 5)) {  /* tx int */
		uart_tx();
		// clear interrupt here.
		uart_tx_int_clear();
	} else if (int_status & (1u << 4)) {  /* rx int */
		uart_rx();
		// clear interrupt here.
		uart_rx_int_clear();
	}
}
