#ifndef TM1637_H
#define TM1637_H

#include <stdint.h>

void tm1637_init(void);
void tm1637_write_segments(uint8_t data[6]);
void tm1637_write_bch(uint16_t val);

#endif  // TM1637_H
