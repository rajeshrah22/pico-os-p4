#ifndef MPU_H__
#define MPU_H__

#if defined (__ASSEMBLER__)

#define MPU_TYPE	((MPU) + 0x00)
#define MPU_CTRL	((MPU) + 0x04)
#define MPU_RNR		((MPU) + 0x08)
#define MPU_RBAR	((MPU) + 0x0c)
#define MPU_RASR	((MPU) + 0x10)

#else
#include <task.h>

extern struct {
	volatile unsigned type;
	volatile unsigned ctrl;
	volatile unsigned rnr;
	volatile unsigned rbar;
	volatile unsigned rasr;
} MPU;

void mpu_enable(void);
void mpu_disable(void);
void mpu_set_region(unsigned int reg, void* start, unsigned int perms);
void mpu_setup_user(struct task_struct* proc);
void mpu_setup_supervisor(void);
void mpu_setup_periph(void);
void mpu_fault_enable(void);

#endif

#define MEMFAULTENA		(1U << 16)

#endif	/* MPU_H__ */
