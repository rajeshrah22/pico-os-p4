#include <stddef.h>
#include <syscall_list.h>

int svc_write(const void* data, size_t len) {
	const char* d = (const char*)data;
	(void)len;
	(void)d;

#	warning "implement this function"

	return 0;
}

