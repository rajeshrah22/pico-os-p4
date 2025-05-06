#include "rtc.h"

#include <stdint.h>
#include "rp2040-map.h"
#include "helpers.h"

#define CLKDIV_M1_REG 0x00
#define RTC_SETUP_0_REG 0x01
#define RTC_SETUP_1_REG 0x02
#define RTC_CTRL_REG 0x03
#define RTC_RTC_1_REG 0x06
#define RTC_RTC_0_REG 0x07

#define RTC_SETUP_0_YEAR_SHIFT 12
#define RTC_SETUP_0_MONTH_SHIFT 8
#define RTC_SETUP_0_DAY_SHIFT 0

#define RTC_SETUP_1_DOTW_SHIFT 24
#define RTC_SETUP_1_HOUR_SHIFT 16
#define RTC_SETUP_1_MIN_SHIFT 8
#define RTC_SETUP_1_SEC_SHIFT 0

#define RTC_CTRL_EN 0x01
#define RTC_CTRL_ACTIVE 0x02
#define RTC_CTRL_LOAD 0x04

void rtc_init(void) {
	RTC_BASE[CLKDIV_M1_REG] = 0x00; // Set clock divider to 1
	RTC_BASE[RTC_CTRL_REG] = RTC_CTRL_EN;
}

void rtc_set_second(uint8_t second) {
	uint32_t second_shift = (second << RTC_SETUP_1_SEC_SHIFT);

	RTC_BASE[RTC_CTRL_REG] &= ~RTC_CTRL_EN;
	loop_until_bit_is_clear(RTC_BASE[RTC_CTRL_REG], RTC_CTRL_ACTIVE);

	RTC_BASE[RTC_SETUP_1_REG] = assign_bitmask(RTC_BASE[RTC_SETUP_1_REG], (0x3F << RTC_SETUP_1_SEC_SHIFT), second_shift);

	RTC_BASE[RTC_CTRL_REG] |= RTC_CTRL_LOAD;
	RTC_BASE[RTC_CTRL_REG] |= RTC_CTRL_EN;

	loop_until_bit_is_set(RTC_BASE[RTC_CTRL_REG], RTC_CTRL_ACTIVE);
}

void rtc_set_minute(uint8_t minute) {
	uint32_t minute_shift = (minute << RTC_SETUP_1_MIN_SHIFT);

	RTC_BASE[RTC_CTRL_REG] &= ~RTC_CTRL_EN;
	loop_until_bit_is_clear(RTC_BASE[RTC_CTRL_REG], RTC_CTRL_ACTIVE);

	RTC_BASE[RTC_SETUP_1_REG] = assign_bitmask(RTC_BASE[RTC_SETUP_1_REG], (0x3F << RTC_SETUP_1_MIN_SHIFT), minute_shift);

	RTC_BASE[RTC_CTRL_REG] |= RTC_CTRL_LOAD;
	RTC_BASE[RTC_CTRL_REG] |= RTC_CTRL_EN;

	loop_until_bit_is_set(RTC_BASE[RTC_CTRL_REG], RTC_CTRL_ACTIVE);
}

void rtc_set_hour(uint8_t hour) {
	uint32_t hour_shift = (hour << RTC_SETUP_1_HOUR_SHIFT);

	RTC_BASE[RTC_CTRL_REG] &= ~RTC_CTRL_EN;
	loop_until_bit_is_clear(RTC_BASE[RTC_CTRL_REG], RTC_CTRL_ACTIVE);

	RTC_BASE[RTC_SETUP_1_REG] = assign_bitmask(RTC_BASE[RTC_SETUP_1_REG], (0x1F << RTC_SETUP_1_HOUR_SHIFT), hour_shift);

	RTC_BASE[RTC_CTRL_REG] |= RTC_CTRL_LOAD;
	RTC_BASE[RTC_CTRL_REG] |= RTC_CTRL_EN;

	loop_until_bit_is_set(RTC_BASE[RTC_CTRL_REG], RTC_CTRL_ACTIVE);
}

void rtc_set_day_of_week(uint8_t dotw) {
	uint32_t dotw_shift = (dotw << RTC_SETUP_1_DOTW_SHIFT);

	RTC_BASE[RTC_CTRL_REG] &= ~RTC_CTRL_EN;
	loop_until_bit_is_clear(RTC_BASE[RTC_CTRL_REG], RTC_CTRL_ACTIVE);

	RTC_BASE[RTC_SETUP_1_REG] = assign_bitmask(RTC_BASE[RTC_SETUP_1_REG], (0x07 << RTC_SETUP_1_DOTW_SHIFT), dotw_shift);

	RTC_BASE[RTC_CTRL_REG] |= RTC_CTRL_LOAD;
	RTC_BASE[RTC_CTRL_REG] |= RTC_CTRL_EN;

	loop_until_bit_is_set(RTC_BASE[RTC_CTRL_REG], RTC_CTRL_ACTIVE);
}

void rtc_set_day(uint8_t day) {
	uint32_t day_shift = (day << RTC_SETUP_0_DAY_SHIFT);

	RTC_BASE[RTC_CTRL_REG] &= ~RTC_CTRL_EN;
	loop_until_bit_is_clear(RTC_BASE[RTC_CTRL_REG], RTC_CTRL_ACTIVE);

	RTC_BASE[RTC_SETUP_0_REG] = assign_bitmask(RTC_BASE[RTC_SETUP_0_REG], (0x1F << RTC_SETUP_0_DAY_SHIFT), day_shift);

	RTC_BASE[RTC_CTRL_REG] |= RTC_CTRL_LOAD;
	RTC_BASE[RTC_CTRL_REG] |= RTC_CTRL_EN;

	loop_until_bit_is_set(RTC_BASE[RTC_CTRL_REG], RTC_CTRL_ACTIVE);
}

void rtc_set_month(uint8_t month) {
	uint32_t month_shift = (month << RTC_SETUP_0_MONTH_SHIFT);

	RTC_BASE[RTC_CTRL_REG] &= ~RTC_CTRL_EN;
	loop_until_bit_is_clear(RTC_BASE[RTC_CTRL_REG], RTC_CTRL_ACTIVE);

	RTC_BASE[RTC_SETUP_0_REG] = assign_bitmask(RTC_BASE[RTC_SETUP_0_REG], (0x0F << RTC_SETUP_0_MONTH_SHIFT), month_shift);

	RTC_BASE[RTC_CTRL_REG] |= RTC_CTRL_LOAD;
	RTC_BASE[RTC_CTRL_REG] |= RTC_CTRL_EN;

	loop_until_bit_is_set(RTC_BASE[RTC_CTRL_REG], RTC_CTRL_ACTIVE);
}

void rtc_set_year(uint16_t year) {
	uint32_t year_shift = (year << RTC_SETUP_0_YEAR_SHIFT);

	RTC_BASE[RTC_CTRL_REG] &= ~RTC_CTRL_EN;
	loop_until_bit_is_clear(RTC_BASE[RTC_CTRL_REG], RTC_CTRL_ACTIVE);

	RTC_BASE[RTC_SETUP_0_REG] = assign_bitmask(RTC_BASE[RTC_SETUP_0_REG], (0xFFF << RTC_SETUP_0_YEAR_SHIFT), year_shift);

	RTC_BASE[RTC_CTRL_REG] |= RTC_CTRL_LOAD;
	RTC_BASE[RTC_CTRL_REG] |= RTC_CTRL_EN;

	loop_until_bit_is_set(RTC_BASE[RTC_CTRL_REG], RTC_CTRL_ACTIVE);
}

static inline uint64_t rtc_get_rtc(void) {
	uint64_t rtc_0 = RTC_BASE[RTC_RTC_0_REG];
	uint64_t rtc_1 = RTC_BASE[RTC_RTC_1_REG];

	return (rtc_1 << 32) | rtc_0;
}

uint8_t rtc_get_second(void) {
	return (rtc_get_rtc() >> RTC_SETUP_1_SEC_SHIFT) & 0x3F;
}

uint8_t rtc_get_minute(void) {
	return (rtc_get_rtc() >> RTC_SETUP_1_MIN_SHIFT) & 0x3F;
}

uint8_t rtc_get_hour(void) {
	return (rtc_get_rtc() >> RTC_SETUP_1_HOUR_SHIFT) & 0x1F;
}

uint8_t rtc_get_day_of_week(void) {
	return (rtc_get_rtc() >> RTC_SETUP_1_DOTW_SHIFT) & 0x07;
}

uint8_t rtc_get_day(void) {
	return (rtc_get_rtc() >> (RTC_SETUP_0_DAY_SHIFT + 32)) & 0x1F;
}

uint8_t rtc_get_month(void) {
	return (rtc_get_rtc() >> (RTC_SETUP_0_MONTH_SHIFT + 32)) & 0x0F;
}

uint16_t rtc_get_year(void) {
	return (rtc_get_rtc() >> (RTC_SETUP_0_YEAR_SHIFT + 32)) & 0xFFF;
}
