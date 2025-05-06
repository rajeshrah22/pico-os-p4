#include <stdint.h>

#include "i2c.h"
#include "helpers.h"
#include "gpio.h"
#include "tm1637.h"
#include "resets.h"

#define I2C_READ_BIT_SHIFT (0)

#define TM1637_CMD1		(0x40) // 0x40 data command
#define TM1637_CMD2		(0xC0) // 0xC0 address command
#define TM1637_CMD3		(0x80) // 0x80 display control command

#define TM1637_CMD3_UNKOWN	BIT(4)
#define TM1637_CMD3_DSP_ON	BIT(3) // 0x08 display on

static inline void fix_i2c_SCL(void) {
	set_pinfunc(5, GPIO_FUNC_SIO); /* SCL, PICO PIN 7 */
	SIO_BASE[9] |= 1 << 5; // OE_SET
	delay(10000);
	set_pinfunc(5, GPIO_FUNC_I2C); /* SCL, PICO PIN 7 */
}

static inline uint8_t reverse8(uint8_t b) {
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;

	return b;
}

static void set_command(uint8_t cmd, bool send) {
	cmd = reverse8(cmd);

	i2c_init(cmd & NBIT(I2C_READ_BIT_SHIFT));

	if (!send)
		return;

	if (!(cmd & BIT(I2C_READ_BIT_SHIFT))) {
		i2c_write_stop(0x00);
		return;
	}

	i2c_read_stop();
	delay(10000);

	fix_i2c_SCL();

	set_reset(RESETS_I2C0, 1);
	delay(10000);
	set_reset(RESETS_I2C0, 0);

	return;
}

void tm1637_init(void) {
	set_command(TM1637_CMD3 | TM1637_CMD3_DSP_ON | TM1637_CMD3_UNKOWN | 0x7, true);
	set_command(TM1637_CMD1, false);

	tm1637_write_segments((uint8_t[6]){0});

	/* shift so first byte is first digit */
	i2c_write_stop(0x00);
	i2c_write_stop(0x00);
	i2c_write_stop(0x00);
	i2c_write_stop(0x00);
}

void tm1637_write_segments(uint8_t data[6]) {

	for (int i = 0; i < 5; i++)
		i2c_write(data[i]);

	i2c_write_stop(data[5]);
}

static uint8_t to_7seg(uint8_t val) {
	static const uint8_t segmap[16] = {
		0xFC, 0x60, 0xDA, 0xF2,
		0x66, 0xB6, 0xBE, 0xE0,
		0xFE, 0xF6, 0xEE, 0x3E,
		0x9C, 0x7A, 0x9E, 0x8E
	};

	return segmap[val & 0x0F];
}

void tm1637_write_bch(uint16_t val) {
	uint8_t data[6] = {0};

	for (int i = 0; i < 5; i++) {
		data[i] = to_7seg(val & 0x0F);
		val >>= 4;
	}

	tm1637_write_segments(data);
}
