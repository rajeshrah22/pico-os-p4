#ifndef RTC_H
#define RTC_H

#include <stdint.h>

void rtc_init(void);

void rtc_set_second(uint8_t second);
void rtc_set_minute(uint8_t minute);
void rtc_set_hour(uint8_t hour);
void rtc_set_day_of_week(uint8_t dotw);
void rtc_set_day(uint8_t day);
void rtc_set_month(uint8_t month);
void rtc_set_year(uint16_t year);

uint8_t rtc_get_second(void);
uint8_t rtc_get_minute(void);
uint8_t rtc_get_hour(void);
uint8_t rtc_get_day_of_week(void);
uint8_t rtc_get_day(void);
uint8_t rtc_get_month(void);
uint16_t rtc_get_year(void);

#endif // RTC_H
