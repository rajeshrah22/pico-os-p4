#include <syscall_list.h>
#include <task.h>

int svc_getpid(void) {
	return current->ppid;
}
