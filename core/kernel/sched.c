#include <stddef.h>

#include <mpu.h>
#include <printk.h>
#include <stacks.h>
#include <task.h>

struct task_struct* current, * next;
struct task_struct task_list[TASK_MAX];

void init_scheduler(void) {
	for(size_t i = 0; i < TASK_MAX; i++) {
		task_list[i].task_state = TASK_STOPPED;
	}
	current = &task_list[0];
	next = &task_list[1];
	printk("[ ] RR Scheduler Initialized\n\r");
}

/* simple RR scheduler */
#define is_max_task(x)		((x) == (TASK_MAX - 1))
void* schedule(void) {
	static size_t scheduled_task;

	// size_t i = is_max_task(scheduled_task) ? 0 : (scheduled_task + 1);
	size_t i = (scheduled_task+ 1) % TASK_MAX;
	for( ;
			(i != scheduled_task) &&
				!(task_list[i].task_state == TASK_RUNNABLE ||
				task_list[i].task_state == TASK_INIT);
			i = (i + 1) % TASK_MAX) {

	}
	scheduled_task = i;
	next = &task_list[i];

	switch(next->task_state) {
		case TASK_INIT:
			next->task_state = TASK_RUNNABLE;
			/* fallthrough */
		case TASK_RUNNABLE:

			current->sp = get_current_sp();
			current = next;
			mpu_setup_user(current);

			break;
		case TASK_STOPPED:
			/* fallthrough */
		case TASK_TRAP:
			/* fallthrough */
		case TASK_IO_WAIT:
			/* fallthrough */
		case TASK_ERR:
			/* fallthrough */
			break;
		default:
			;
	}

	return current->sp;
}

