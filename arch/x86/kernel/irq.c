#include <wiseos/ptrace.h>
#include <wiseos/interrupt.h>
#include <wiseos/irq.h>
#include <asm/system.h>
#include <wiseos/init.h>
#include <asm/io.h>
#include <types.h>

#define BI(x,y) \
	BUILD_IRQ(x##y)

#define BUILD_16_IRQS(x) \
	BI(x,0) BI(x,1) BI(x,2) BI(x,3) \
	BI(x,4) BI(x,5) BI(x,6) BI(x,7) \
	BI(x,8) BI(x,9) BI(x,a) BI(x,b) \
	BI(x,c) BI(x,d) BI(x,e) BI(x,f)
	
				      BUILD_16_IRQS(0x2) BUILD_16_IRQS(0x3)
BUILD_16_IRQS(0x4) BUILD_16_IRQS(0x5) BUILD_16_IRQS(0x6) BUILD_16_IRQS(0x7)
BUILD_16_IRQS(0x8) BUILD_16_IRQS(0x9) BUILD_16_IRQS(0xa) BUILD_16_IRQS(0xb)
BUILD_16_IRQS(0xc) BUILD_16_IRQS(0xd) BUILD_16_IRQS(0xe) BUILD_16_IRQS(0xf)	

#undef BUILD_16_IRQS
#undef BI


#define IRQ(x,y) \
	IRQ##x##y##_interrupt

#define IRQLIST_16(x) \
	IRQ(x,0), IRQ(x,1), IRQ(x,2), IRQ(x,3), \
	IRQ(x,4), IRQ(x,5), IRQ(x,6), IRQ(x,7), \
	IRQ(x,8), IRQ(x,9), IRQ(x,a), IRQ(x,b), \
	IRQ(x,c), IRQ(x,d), IRQ(x,e), IRQ(x,f)

/* for the irq vectors */

static void (*interrupt[NR_VECTORS - FIRST_EXTERNAL_VECTOR])(void) = {
					  IRQLIST_16(0x2), IRQLIST_16(0x3),
	IRQLIST_16(0x4), IRQLIST_16(0x5), IRQLIST_16(0x6), IRQLIST_16(0x7),
	IRQLIST_16(0x8), IRQLIST_16(0x9), IRQLIST_16(0xa), IRQLIST_16(0xb),
	IRQLIST_16(0xc), IRQLIST_16(0xd), IRQLIST_16(0xe), IRQLIST_16(0xf)
};
#undef IRQ
#undef IRQLIST_16

extern struct irq_chip i8259A_chip;

struct irq_desc irq_desc[NR_IRQS];

void __init init_ISA_irqs (void);

void __init init_IRQ(void){
	int i;
	
	init_ISA_irqs ();

	for (i = 0; i < (NR_VECTORS - FIRST_EXTERNAL_VECTOR); i++) {
		int vector = FIRST_EXTERNAL_VECTOR + i;
		if (vector != IA32_SYSCALL_VECTOR)
			set_intr_gate(vector, interrupt[i]);
	}
}


void do_IRQ(struct pt_regs regs, int n_idt_entry){

	int irq = n_idt_entry - FIRST_EXTERNAL_VECTOR;
	
	if (irq_desc[irq].status == IRQ_ENABLED){
		handle_irq_event(irq,irq_desc[irq].action);
	}	
}

void __init init_ISA_irqs (void)
{
	int i;
	init_8259A(0);

	for (i = 0; i < NR_IRQS; i++) {
		irq_desc[i].status = IRQ_DISABLED;
		irq_desc[i].action = NULL;
		irq_desc[i].depth = 1;
		if (i < 16) {
			/*
			 * 16 old-style INTA-cycle interrupts:
			 */
			 irq_desc[i].chip = &i8259A_chip;
			//set_irq_chip_and_handler_name(i, &i8259A_chip,
			//			      handle_level_irq, "XT");
		} else {
			/*
			 * 'high' PCI IRQs filled in on demand
			 */
			irq_desc[i].chip = NULL;
		}
	}
}




