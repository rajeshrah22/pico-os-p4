#include <stdarg.h>
#include <stddef.h>
#include <string.h>

#include <rt.h>
#include <svcall.h>

#define PRINT_BUFFER_SIZE	16

#define ssize_t	signed long
#define ULONG(x) ((unsigned long)(x))

ssize_t write(const void* buf, size_t count);

void print(const char* restrict fmt, ...) {
	char buffer[PRINT_BUFFER_SIZE];
	
	va_list args;

	const char* str = fmt;
	size_t count = 0;
	int i;
	
	char c;

	va_start(args, fmt);

	while((c = *fmt++)) {
		if(c == '%') {
			if(count > 0) {
				//write(str, count);
				__syscall2(__NR_write, ULONG(str), count);
			}
			
			switch(*fmt++) {
				case 'x':
					i = va_arg(args, int);
					itoa(buffer, i);
					write(buffer, strlen(buffer));
					break;
				case 's':
					str = va_arg(args, const char*);
					write(str, strlen(str));
					break;
				default:
					break;
			}
	
			count = 0;
			str = fmt;
		} else {
			count++;
		}
	}

	if(count > 0) {
		write(str, count);
	}
}
