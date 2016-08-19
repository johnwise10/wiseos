#include <wiseos/ptrace.h>

void show_regs(struct pt_regs * regs){
	printk("ebx:0x%x\n",regs->ebx);
	printk("ecx:0x%x\n",regs->ecx);
	printk("edx:0x%x\n",regs->edx);
	printk("esi:0x%x\n",regs->esi);
	printk("edi:0x%x\n",regs->edi);
	printk("ebp:0x%x\n",regs->ebp);
	printk("eax:0x%x\n",regs->eax);
	printk("ds:0x%x\n",regs->ds);
	printk("es:0x%x\n",regs->es);
	printk("fs:0x%x\n",regs->fs);
	printk("gs:0x%x\n",regs->gs);	
}
void debug_cpu(struct pt_regs regs){
	unsigned int esp;
	show_regs(&regs);
	__asm__ __volatile__(
		"movl %%esp,%%eax\n"
		"movl %%eax, %0" : "=g" (esp)
	);
	printk("esp:0x%x\n",esp);
}