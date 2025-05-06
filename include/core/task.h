#ifndef TASK_H__
#define TASK_H__

#define MAGIC_HI	0x54414c46
#define MAGIC_LO	0xff4e4942

struct task_header {
	unsigned int magic[2];
	void* entry;
	void* init_sp;
	void* text_start;
	void* text_end;
	void* data_start;
	void* data_end;
};

#ifdef __KERNEL

#define TASK_MAX	4

#define DECLARE_TASK(x) \
	((const struct task_header*)(x))

enum task_state {
	TASK_INIT = 0,
	TASK_RUNNABLE,
	TASK_STOPPED,
	TASK_TRAP,
	TASK_IO_WAIT,
	TASK_ERR
};

enum cpu_state {
	KERN_MODE = 0,
	USER_MODE
};

struct task_struct {
	unsigned int ppid;
	enum task_state task_state;
	void* sp;
	void* text_start;
	unsigned int text_region_size;
	void* data_start;
	unsigned int data_region_size;
};

extern struct task_struct* current, * next;

const struct task_header* get_task_header(int n);
int create_task(const struct task_header* header, int task);
void init_scheduler(void);
void exec(void* sp);
int get_free_pid(void);
struct task_struct* allocate_task(
			const struct task_struct* task,
			const void* entry,
			int pid
		);


#else

extern void startup(void);
extern unsigned int __ro_section_start;
extern unsigned int __ro_section_end;
extern unsigned int __data_start;
extern unsigned int __ram_end;

#define APPLICATION(a) \
	__attribute__((section(".app_header"))) \
	struct task_header __header = { \
		.magic = {MAGIC_HI, MAGIC_LO}, \
		.entry = startup, \
		.init_sp = (void*)&__ram_end, \
		.text_start = (void*)&__ro_section_start, \
		.text_end = (void*)&__ro_section_end, \
		.data_start = (void*)&__data_start, \
		.data_end = (void*)&__ram_end \
	}

#endif	/* __KERNEL */

#endif	/* TASK_H__ */
