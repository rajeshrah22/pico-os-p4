#include <stdarg.h>
#include <stddef.h>
/* ssize_t is there? */
#include <stdio.h>

#include <printk.h>
#include <syscall_list.h>

ssize_t uart_puts(const char*);
int uart_putc(int);

#define PRINTK_BUFFER_SIZE	16

char* hitoa(char* buffer, int number);

void printk(const char* restrict fmt, ...) {
	char buffer[PRINTK_BUFFER_SIZE];
	const char* str;
	int n;
	char c;

	va_list args;
	va_start(args, fmt);

	while((c = *fmt++)) {
		if(c == '%') {
			switch((c = *fmt++)) {
				case 'x':
					n = va_arg(args, int);
					hitoa(buffer, n);
					uart_puts(buffer);
					break;
				case 's':
					str = va_arg(args, const char*);
					uart_puts(str);
					break;
				default:
					break;
			}
		} else {
			uart_putc(c);
		}
	}
	va_end(args);
}

char* hitoa(char* buffer, int number) {
	size_t i = 0, s = 0;
	char c;

	if(!number) {
		buffer[0] = '0';
		buffer[1] = '\0';
		return buffer;
	}

	while(number) {
		c = number & 0xf;
		buffer[i++] = (c > 9 ? 'a' : '0') + c;
		number >>= 4;
	}
	buffer[i--] = '\0';

	while(s < i) {
		c = buffer[s];
		buffer[s++] = buffer[i];
		buffer[i--] = c;
	}

	return buffer;
}
