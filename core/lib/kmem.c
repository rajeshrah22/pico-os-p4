#include <stddef.h>

#include <kmem.h>

void* memcpy(void* dest, const void* src, size_t n) {
	char* tgt = (char*)dest;
	const char* s = (const char*)src;
	while(n--) {
		*tgt++ = *s++;
	}
	return dest;
}
