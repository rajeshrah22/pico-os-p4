#include <stdio.h>
#include <stddef.h>

#include <svcall.h>

#define ULONG(x)	((unsigned long)(x))
ssize_t write(const void* buffer, size_t count) {
	return __syscall2(__NR_write, ULONG(buffer), count);
}
