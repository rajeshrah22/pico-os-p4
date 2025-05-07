#include <stddef.h>
#include <syscall_list.h>
#include <uart.h>

/* I'm assuming svc_write writes to uart like a console */

int svc_write(const void* data, size_t len) {
	const char* d = (const char*)data;
	int ret;

	ret = uart_write(d, len);

	return ret;
}

