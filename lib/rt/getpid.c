#include <rt.h>

extern int __sys_getpid(void);

int getpid(void) {
	return __sys_getpid();
}
