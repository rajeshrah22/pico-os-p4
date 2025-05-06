#ifndef SPI_H__
#define SPI_H__

extern struct {
/* 000 */	volatile unsigned cr0;
/* 004 */	volatile unsigned cr1;
/* 008 */	volatile unsigned dr;
/* 00c */	volatile unsigned sr;
/* 010 */	volatile unsigned cpsr;
/* 014 */	volatile unsigned imsc;
/* 018 */	volatile unsigned ris;
/* 01c */	volatile unsigned mis;
/* 020 */	volatile unsigned icr;
/* 024 */	volatile unsigned dmarcr;
} SPI0, SPI1;

#define SPI_cr1_sse		(1)

#define SPI_scr_offset	(8)
#define SPI_scr_mask	((0xff) << (SPI_scr_offset))

#define SPI_dss_4bit	(0b0011)
#define SPI_dss_5bit	(0b0100)
#define SPI_dss_6bit	(0b0101)
#define SPI_dss_7bit	(0b0110)
#define SPI_dss_8bit	(0b0111)
#define SPI_dss_9bit	(0b1000)
#define SPI_dss_10bit	(0b1001)
#define SPI_dss_11bit	(0b1010)
#define SPI_dss_12bit	(0b1011)
#define SPI_dss_13bit	(0b1100)
#define SPI_dss_14bit	(0b1101)
#define SPI_dss_15bit	(0b1110)
#define SPI_dss_16bit	(0b1111)

#define SPI_sr_tnf		(1)
#define SPI_sr_tfe		(0)

#endif	/* SPI_H__ */
