#include <stdint.h>

#include "rp2040-map.h"
#include "helpers.h"
#include "i2c.h"

#define IC_CON_SLV_DIS_BITS		BIT(6)
#define IC_CON_MSTR_MODE_EN_BITS	(0x1)
#define IC_CON_RESTART_EN_SHIFT		(5)
#define IC_CON_SPEED_SHIFT		(1)

#define IC_CON_SPEED_STD_BITS		(0x1)
#define IC_STATUS_TFNF_SHIFT		(0x1)
#define IC_ENABLE_ENABLE_BITS		(0x1)
#define IC_DATA_CMD_CMD_SHIFT		(8)
#define IC_DATA_CMD_STOP_SHIFT		(9)
#define IC_RAW_INTR_STAT_TX_ABRT_BITS 	BIT(6)

#define I2C_IC_CON		(0x00)
#define I2C_IC_TAR		(0x01)
#define I2C_IC_DATA_CMD		(0x4)
#define I2C_IC_SS_SCL_HCNT	(0x5)
#define I2C_IC_SS_SCL_LCNT	(0x6)
#define I2C_IC_RAW_INTR_STAT	(0xD)
#define I2C_IC_ENABLE		(0x1B)
#define I2C_IC_STATUS		(0x1C)
#define I2C_IC_RXFLR		(0x1E)

void i2c_init(uint16_t addr) {
	I2C0_BASE[I2C_IC_ENABLE] &= ~IC_ENABLE_ENABLE_BITS;

	I2C0_BASE[I2C_IC_CON] = IC_CON_SLV_DIS_BITS |
				IC_CON_MSTR_MODE_EN_BITS |
				(IC_CON_SPEED_STD_BITS << IC_CON_SPEED_SHIFT);

	I2C0_BASE[I2C_IC_TAR] = addr;

	I2C0_BASE[I2C_IC_SS_SCL_HCNT] = 1280*20;
	I2C0_BASE[I2C_IC_SS_SCL_LCNT] = 1504*20;
	I2C0_BASE[I2C_IC_ENABLE] = IC_ENABLE_ENABLE_BITS;
}

void i2c_write(uint8_t data) {
	loop_until_bit_is_set(I2C0_BASE[I2C_IC_STATUS], IC_STATUS_TFNF_SHIFT);
	I2C0_BASE[I2C_IC_DATA_CMD] = data;
}

void i2c_write_stop(uint8_t data) {
	loop_until_bit_is_set(I2C0_BASE[I2C_IC_STATUS], IC_STATUS_TFNF_SHIFT);
	I2C0_BASE[I2C_IC_DATA_CMD] = data | BIT(IC_DATA_CMD_STOP_SHIFT);
}

uint8_t i2c_read(void) {
	loop_until_bit_is_set(I2C0_BASE[I2C_IC_STATUS], IC_STATUS_TFNF_SHIFT);
	I2C0_BASE[I2C_IC_DATA_CMD] = BIT(IC_DATA_CMD_CMD_SHIFT);

	while(!I2C0_BASE[I2C_IC_RXFLR]) {
		if(I2C0_BASE[I2C_IC_RAW_INTR_STAT] & IC_RAW_INTR_STAT_TX_ABRT_BITS)
			return 0;
	}

	return I2C0_BASE[I2C_IC_DATA_CMD];
}

uint8_t i2c_read_stop(void) {
	loop_until_bit_is_set(I2C0_BASE[I2C_IC_STATUS], IC_STATUS_TFNF_SHIFT);
	I2C0_BASE[I2C_IC_DATA_CMD] = BIT(IC_DATA_CMD_STOP_SHIFT) | BIT(IC_DATA_CMD_CMD_SHIFT);

	while(!I2C0_BASE[I2C_IC_RXFLR]) {
		if(I2C0_BASE[I2C_IC_RAW_INTR_STAT] & IC_RAW_INTR_STAT_TX_ABRT_BITS)
			return 0;
	}

	return I2C0_BASE[I2C_IC_DATA_CMD];
}
