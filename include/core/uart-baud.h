#ifndef UART_BAUD_H__
#define UART_BAUD_H__

#ifndef F_PERIPH
#error "F_PERIPH not defined"
#endif

#ifndef BAUD
#error "BAUD not defined"
#endif

#define UARTBAUDRATE_DIV \
	((8u * (F_PERIPH) / (BAUD)) + 1)

#define UARTIBRD_PRE_VALUE ( (UARTBAUDRATE_DIV) >> (7) )

#define UARTIBRD_VALUE ( ( (UARTIBRD_PRE_VALUE) == 0) ? 1 : \
							( (UARTIBRD_PRE_VALUE) >= 65535 ? 65535 : \
								(UARTIBRD_PRE_VALUE) ) )

#define UARTFBRD_VALUE ( ( ((UARTIBRD_PRE_VALUE) == 0 \
								|| (UARTIBRD_PRE_VALUE) >= 65535) \
							? 0 : (((UARTBAUDRATE_DIV) & 0x7f) >> 1) ) )

#endif	/* UART_BAUD_H__ */
