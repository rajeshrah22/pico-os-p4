#ifndef UART_H__
#define UART_H__

extern struct {
/* 000 */	volatile unsigned uartdr;
/* 004 */	volatile unsigned uartrsr;
/* 000 */	unsigned __padding_1[0x14/4 - 1];	/* padding of 0x14 */
/* 018 */	volatile unsigned uartfr;
/* 000 */	unsigned __padding_2[1];			/* padding of 4 */
/* 020 */	volatile unsigned uartilpr;
/* 024 */	volatile unsigned uartibrd;
/* 028 */	volatile unsigned uartfbrd;
/* 02c */	volatile unsigned uartlcr_h;
/* 030 */	volatile unsigned uartcr;
/* 034 */	volatile unsigned uartifls;
/* 038 */	volatile unsigned uartimsc;
/* 03c */	volatile unsigned uartris;
/* 040 */	volatile unsigned uartmis;
/* 044 */	volatile unsigned uarticr;
/* 048 */	volatile unsigned uartdmacr;
} UART0, UART1;

#define UART_WLEN_8		(0x3)
#define UART_WLEN_7		(0x2)
#define UART_WLEN_6		(0x1)
#define UART_WLEN_5		(0x0)
#define UART_LCR_H_WLEN_OFFSET	(5)
#define UART_LCR_H_WLEN_MASK		((0x3) << (5))
#define UART_LCR_H_FEN	(4)

#define UART_FR_BUSY	(3)
#define UART_FR_TXFF	(5)


#define UART_CR_UARTEN		(0)
#define UART_CR_TXE			(8)
#define UART_CR_RXE			(9)

#define UART_IMSC_RTIM		(6)
#define UART_IMSC_TXIM		(5)
#define UART_IMSC_RXIM		(4)

#define UART_RIS_TXRIS	(5)
#define UART_RIS_RXRIS	(4)

#define UART_ICR_TXICR	(5)
#define UART_ICR_RXICR	(4)

#endif
