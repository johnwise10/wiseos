#ifndef _ASM_TRAP_H
#define _ASM_TRAP_H
#define TRAP_NAME2(nr) nr##_interrupt(void)
#define TRAP_NAME(nr) TRAP_NAME2(TRAP##nr)

#define BUILD_TRAP(nr) \
 void TRAP_NAME(nr); \
__asm__( \
"\n.p2align\n" \
"TRAP" #nr "_interrupt:\n\t" \
	"push $(" #nr ") ; " \
	"jmp common_trap");
	

#define NR_TRAPS 32
#endif	/*_ASM_TRAP_H */
