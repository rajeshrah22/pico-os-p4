#include <stddef.h>

#include <syscall_list.h>
#include <uart.h>

int svc_read(void* data, size_t len) {
	char *str = (char *)data;
	int c;
	int i = 0;

	while(i < len) {
		c = uart_getc();
		if (c == -1)
			break;
		str[i] = (char)c;
		i++;
	}

	return i;
}
