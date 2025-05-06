#ifndef RCC_H__
#define RCC_H__

#ifndef __ASSEMBLER__
extern volatile unsigned int RCC_AHB1ENR;
extern volatile unsigned int RCC_APB2ENR;
#endif

#define RCC_AHB1ENR_GPIODEN	(1U << 3)
#define RCC_AHB1ENR_GPIOAEN	(1U << 0)
#define RCC_AHB1ENR_GPIOCEN	(1U << 2)

#define RCC_APB2ENR_USART6EN	(1U << 5)
#endif
