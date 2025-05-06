#ifndef ASM_MACROS_H__
#define ASM_MACROS_H__

#ifdef __ASSEMBLER__

.macro declfn fn_name
	.section .text.\fn_name
	.global \fn_name
	.type \fn_name, %function
\fn_name :
.endm

.macro endfn fn_name
	.size \fn_name, . - \fn_name
.endm

#endif

#endif
