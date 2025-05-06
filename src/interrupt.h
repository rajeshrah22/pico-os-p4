#include "rp2040-map.h"

#ifndef INTERRUPT_H__
#define INTERRUPT_H__

#define ISR_(x)	\
		void __vector_ ## x (void); \
		void __vector_ ## x (void)

#define ISR(x) ISR_(x)

#define TIMER0_vect	16
#define SPI0_vect	34
#define SPI1_vect	35
#define UART0_vect	36
#define UART1_vect	37
#define ADC_Vect	38

#define NVIC_BIT(x)	((x) - (16))

#define NVIC_ISER ((volatile uint32_t *)((uint32_t)PPB_BASE + 0xe100u))
#define NVIC_ICER  ((volatile uint32_t *)((uint32_t)PPB_BASE + 0xe180u))
#define NVIC_ISPR  ((volatile uint32_t *)((uint32_t)PPB_BASE + 0xe200u))
#define NVIC_ICPR  ((volatile uint32_t *)((uint32_t)PPB_BASE + 0xe280u))
#define NVIC_IPR ((volatile uint32_t *)((uint32_t)PPB_BASE + 0xe400u))

#endif
