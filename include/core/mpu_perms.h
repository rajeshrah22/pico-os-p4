#ifndef MPU_PERMS_H__
#define MPU_PERMS_H__

#define MPU_TEX(x)			((x) << 19)
#define MPU_S(x)			((x) << 18)
#define MPU_C(x)			((x) << 17)
#define MPU_B(x)			((x) << 16)

#define MPU_REG_ENABLE		1U
#define MPU_REG_SIZE_32B	(4 << 1)
#define MPU_REG_SIZE_16K	(13 << 1)
#define MPU_REG_SIZE_32K	(14 << 1)
#define MPU_REG_SIZE_128K	(16 << 1)
#define MPU_REG_SIZE_1M		(19 << 1)
#define MPU_REG_SIZE_256M	(27 << 1)
#define MPU_REG_SIZE_512M	(28 << 1)
#define MPU_REG_SIZE_1G		(29 << 1)
#define MPU_REG_SIZE_2G		(30 << 1)

#define MPU_AP_RWNA			(0b001U << 24)
#define MPU_AP_RONA			(0b101U << 24)
#define MPU_AP_RWRW			(0b011U	<< 24)
#define MPU_AP_RORO			(0b110U << 24)

#define MPU_REG_CODE		(MPU_TEX(0b000) | MPU_C(1))
#define MPU_REG_SRAM		(MPU_TEX(0b000) | MPU_C(1) | MPU_S(1))
#define MPU_REG_PERIPH		(MPU_TEX(0b000) | MPU_B(1) | MPU_S(1))

#define MPU_ATTRIB_UCODE	(MPU_REG_CODE | MPU_AP_RORO | MPU_REG_ENABLE)
#define MPU_ATTRIB_UDATA	(MPU_REG_SRAM | MPU_AP_RWRW | MPU_REG_ENABLE)

#define MPU_ATTRIB_SCODE	(MPU_REG_CODE | MPU_AP_RONA | MPU_REG_ENABLE)
#define MPU_ATTRIB_SDATA	(MPU_REG_SRAM | MPU_AP_RWNA | MPU_REG_ENABLE)

#define ATTRIB_PERIPH_AREA1	(MPU_REG_PERIPH | MPU_AP_RWNA | \
								MPU_REG_SIZE_1G | MPU_REG_ENABLE)
#define ATTRIB_PERIPH_AREA2	(MPU_REG_PERIPH | MPU_AP_RWNA | \
								MPU_REG_SIZE_2G | MPU_REG_ENABLE)

#endif
