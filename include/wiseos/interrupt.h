#ifndef _WISEOS_INTERRUPT_H
#define _WISEOS_INTERRUPT_H
#include <asm/system.h>
#include <asm/irqflags.h>
#include <wiseos/irqreturn.h>

typedef irqreturn_t (*irq_handler_t)(int, void *);

struct irqaction {
	irq_handler_t handler;
	unsigned long flags;
	const char *name;
	struct irqaction *next;
};

int handle_irq_event(int irq, struct irqaction * action);

void init_IRQ(void);

#define int_enable() sti();
#define int_disable() cli();

#endif
