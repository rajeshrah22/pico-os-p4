#include <kmath.h>

#include <printk.h>
#include <sched.h>
#include <stacks.h>
#include <task.h>

extern struct task_struct task_list[TASK_MAX];

unsigned int compute_region_size(void* start, void* end);

int create_task(const struct task_header* header, int task) {
	unsigned int region_size;

	if(task >= TASK_MAX) {
		printk("[!] create_task(): task does not fit in run queue!\n\r");
		return -1;
	}

	if(header->magic[0] != MAGIC_HI) {
		printk("[!] create_task(): invalid magic number!\n\r");
		return -1;
	}

	if(header->magic[1] != MAGIC_LO) {
		printk("[!] create_task(): invalid magic number!\n\r");
		return -1;
	}
	

	task_list[task].sp = init_user_stack(header->init_sp, header->entry);

	task_list[task].ppid = task + 1;
	task_list[task].task_state = TASK_INIT;
	task_list[task].sp = GET_INIT_STACK(header);
	task_list[task].text_start = header->text_start;
	task_list[task].data_start = header->data_start;
			
	task_list[task].text_region_size = compute_region_size(
			header->text_start,
			header->text_end
		) << 1;
	task_list[task].data_region_size = compute_region_size(
			header->data_start,
			header->data_end
		) << 1;
	
	printk(	"[ ] create_task(): created new task:\n\r"
			"    pid: %d\n\r"
			"    .text_size: %d B\n\r"
			"    .data_size: %d B\n\r",
			task_list[task].ppid,
			1 << ((task_list[task].text_region_size >> 1) + 1),
			1 << ((task_list[task].data_region_size >> 1) + 1)
		);

	return 0;
}

const struct task_header* get_task_header(int n) {
	const static struct task_header* process_list[] = {
			DECLARE_TASK(0x08020000),
			DECLARE_TASK(0x08040000)
		};
	if(n >= sizeof(process_list)/sizeof(process_list[0])) {
		return (const struct task_header*)NULL;
	}
	return process_list[n];
}
	
unsigned int compute_region_size(void* start, void* end) {
	unsigned int region_size = (unsigned int)end - (unsigned int)start;

	if(!(region_size & (region_size - 1))) {
		return flog2(region_size) - 1;
	}
	return flog2(region_size);
}

