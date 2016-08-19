#include <wiseos/interrupt.h>
#include <wiseos/irq.h>
#include <asm/system.h>


int handle_irq_event(int irq, struct irqaction * action){
//   	printk("irq:0x%x\n",irq);

/*	if (irq == 0x01){
		keyboard();
		disable_8259A_irq(0);
	 }
	else if (irq == 0x00){
		printk("b");
	}*/		
	int i;
	do{
	  action->handler(1,&i);
	}while(action->next);
  return 0;
}

int request_irq(int irq, struct irqaction * action){
	irq_desc[irq].chip->enable(irq);
	irq_desc[irq].action = action;
	irq_desc[irq].status = IRQ_ENABLED;
	irq_desc[irq].depth  = 1;
	return 0;
}

void free_irq(int irq){

}