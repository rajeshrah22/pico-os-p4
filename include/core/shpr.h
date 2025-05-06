#ifndef SHPR_H__
#define SHPR_H__

extern volatile unsigned int SHPR1;
extern volatile unsigned int SHPR2;
extern volatile unsigned int SHPR3;
extern volatile unsigned int SHCSR;

void setup_vect_priority(void);
#endif
