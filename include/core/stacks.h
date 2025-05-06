#ifndef STACKS_H__
#define STACKS_H__

#if defined(__ASSEMBLER__)

.macro switch_to_user rtemp
	mrs \rtemp, control
	orr \rtemp, \rtemp, #(1 << 1)
	msr control, \rtemp
.endm

.macro switch_to_system rtemp
	mrs \rtemp, control
	bfc \rtemp, #1, #1
	msr control, \rtemp
.endm

#else
#define GET_INIT_STACK(x) \
		((void*)(((unsigned int)((x)->init_sp)) - 64))

void* init_user_stack(void* sp, void* pc);
void* get_current_sp(void);
void return_to_user(void* sp);

#endif

#endif
