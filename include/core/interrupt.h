#ifndef INTERRUPT_H__
#define INTERRUPT_H__

#define SVCALL_vect		11
#define PENDSV_vect		14
#define SYSTICK_vect	15
#define SPI0_vect	34
#define SPI1_vect	35
#define UART0_vect	36
#define UART1_vect	37

#if defined(__ASSEMBLER__)

.macro ISR x
	.section .text.__vector_\x, "ax"
	.global __vector_\x
	.type __vector_\x, %function
__vector_\x:
.endm

.macro endisr x
	.size __vector_\x, . - __vector_\x
.endm

#else

#define ISR_(x)	\
		void __vector_ ## x (void); \
		void __vector_ ## x (void)
#define ISR(x) ISR_(x)


#define NVIC_BIT(x)	((x) - (16))

extern volatile unsigned NVIC_ISER;
extern volatile unsigned NVIC_ICER;
extern volatile unsigned NVIC_ISPR;
extern volatile unsigned NVIC_ICPR;
extern volatile unsigned NVIC_IPR[8];

#endif

#endif
