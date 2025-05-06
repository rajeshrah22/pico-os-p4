#ifndef RT_H__
#define RT_H__

#include <stddef.h>

void bad_write(unsigned int* address, unsigned int data);
unsigned int get_button(void);
void set_led(unsigned int state);
void delay(unsigned int n);
void print(const char* restrict fmt, ...);
int getpid(void);
int getc(void);
int set_led_ring(const unsigned* ptr, size_t count);
char* itoa(char* buffer, int number);

#endif
