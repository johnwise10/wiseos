#ifndef _WISEOS_ASM_IRQ_H_
#define _WISEOS_ASM_IRQ_H_

#define IRQ_NAME2(nr) nr##_interrupt(void)
#define IRQ_NAME(nr) IRQ_NAME2(IRQ##nr)

#define BUILD_IRQ(nr) \
 void IRQ_NAME(nr); \
__asm__( \
"\n.p2align\n" \
"IRQ" #nr "_interrupt:\n\t" \
	"push $(" #nr ") ; " \
	"jmp common_interrupt");
	

#define NR_VECTORS 256
#define FIRST_EXTERNAL_VECTOR 0x20
#define IA32_SYSCALL_VECTOR   0x80
	
#endif


