#ifndef SYSCALL_LIST_H__
#define SYSCALL_LIST_H__

#if defined(__ASSEMBLER__)
.word svc_nil
.word svc_write
.word svc_read
.word svc_execve
.word svc_button
.word svc_set_led
.word svc_getpid
.word svc_setring
#else
#include <stddef.h>

int svc_nil(void);
int svc_write(const void* data, size_t len);
int svc_read(void* data, size_t len);
int svc_execve(void* initial_sp);
unsigned int svc_button(void);
int svc_set_led(unsigned int state);
int svc_getpid(void);
int svc_set_ring(unsigned* data, size_t len);
#endif

#endif
