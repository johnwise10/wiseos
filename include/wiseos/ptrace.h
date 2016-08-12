#ifndef _WISEOS_PTRACE_H
#define _WISEOS_PTRACE_H
#include<asm/ptrace.h>
void show_regs(struct pt_regs *);
void debug(void);
#endif
