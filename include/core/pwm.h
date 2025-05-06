#ifndef PWM_H__
#define PWM_H__

extern struct {
	struct {
		volatile unsigned csr;	/* +00 */
		volatile unsigned div;	/* +04 */
		volatile unsigned ctr;	/* +08 */
		volatile unsigned cc;	/* +0c */
		volatile unsigned top;	/* +10 */
	} CH[8];
	volatile unsigned en;
	volatile unsigned intr;
	volatile unsigned inte;
	volatile unsigned intf;
	volatile unsigned ints;
} PWM;

#define PWM_CSR_EN	(0)
#define PWM_CSR_PH_CORRECT	(1)
#define PWM_CSR_A_INV		(2)
#define PWM_CSR_B_INV		(3)
#define PWM_CSR_DIVMODE_OFFSET	(4)
#define PWM_CSR_DIVMODE_MASK	(3)
#define PWM_CSR_DIVMODE_DIV		(0)
#define PWM_CSR_DIVMODE_LEVEL	(1)
#define PWM_CSR_DIVMODE_RISE	(2)
#define PWM_CSR_DIVMODE_FALL	(3)
#define PWM_CSR_PH_RET	(6)
#define PWM_CSR_PH_ADV	(7)

#define PWM_DIV_FRAC_OFFSET	(0)
#define PWM_DIV_FRAC_MASK	(0xf)
#define PWM_DIV_INT_OFFSET	(4)
#define PWM_DIV_INT_MASK	()

#define PWM_CC_A_OFFSET	(0)
#define PWM_CC_B_OFFSET	(16)
#define PWM_CC_MASK		(0xffff)

#define PWM_EN_CH0	(0)
#define PWM_EN_CH1	(1)
#define PWM_EN_CH2	(2)
#define PWM_EN_CH3	(3)
#define PWM_EN_CH4	(4)
#define PWM_EN_CH5	(5)
#define PWM_EN_CH6	(6)
#define PWM_EN_CH7	(7)

#endif	/* PWM_H__ */
