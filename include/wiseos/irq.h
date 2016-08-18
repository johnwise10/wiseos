#ifndef _WISEOS_IRQ_H
#define _WISEOS_IRQ_H

#include <asm/irq.h>
#include <wiseos/interrupt.h>

#define NR_IRQS	256
#define IRQ_DISABLED 0
#define IRQ_ENABLED  1

struct irq_chip {
	const char	*name;
	unsigned int	(*startup)(unsigned int irq);
	void		(*shutdown)(unsigned int irq);
	void		(*enable)(unsigned int irq);
	void		(*disable)(unsigned int irq);

	void		(*ack)(unsigned int irq);
	void		(*mask)(unsigned int irq);
	void		(*mask_ack)(unsigned int irq);
	void		(*unmask)(unsigned int irq);
	void		(*eoi)(unsigned int irq);

	void		(*end)(unsigned int irq);
//	void		(*set_affinity)(unsigned int irq, cpumask_t dest);
	int		(*retrigger)(unsigned int irq);
	int		(*set_type)(unsigned int irq, unsigned int flow_type);
	int		(*set_wake)(unsigned int irq, unsigned int on);
};

struct irq_desc {
	struct irq_chip		*chip;
	struct irqaction	*action;	/* IRQ action list */
	unsigned int		status;		/* IRQ status */
	unsigned int		depth;		/* nested irq disables */
};

extern struct irq_desc irq_desc[NR_IRQS];

int request_irq(int irq, struct irqaction * action);
void free_irq(int irq);
#endif
