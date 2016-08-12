
#define __ASSEMBLY__
#include <wiseos/config.h>
#include <asm/segment.h>
#include <wiseos/linkage.h>

#define SAVE_ALL \
	cld; \
	push %gs; \
	push %fs; \
	push %es; \
	push %ds; \
	pushl %eax; \
	pushl %ebp; \
	pushl %edi; \
	pushl %esi; \
	pushl %edx; \
	pushl %ecx; \
	pushl %ebx; \

#define RESTORE_ALL \
	popl %ebx; \
	popl %ecx; \
	popl %edx; \
	popl %esi; \
	popl %edi; \
	popl %ebp; \
	popl %eax; \
	pop %ds; \
	pop %es; \
	pop %fs; \
	pop %gs; \
	

#define EOI \
	movb $0x20,%al; \
	outb %al,$0x20; \


ENTRY(common_interrupt)
	SAVE_ALL
	call EXT_C(do_IRQ)
	RESTORE_ALL
	addl $4,%esp
	EOI
	iret

ENTRY(common_trap)
	SAVE_ALL
	call EXT_C(do_trap)
	RESTORE_ALL
	addl $4,%esp
	iret

ENTRY(EXT_C(debug))
	SAVE_ALL
	call EXT_C(debug_cpu)
 	RESTORE_ALL
	ret
		
