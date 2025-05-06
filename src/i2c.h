#ifndef I2C_H
#define I2C_H

#include <stdint.h>

void i2c_init(uint16_t addr);

void i2c_write(uint8_t data);
void i2c_write_stop(uint8_t data);
uint8_t i2c_read(void);
uint8_t i2c_read_stop(void);

#endif  // I2C_H
