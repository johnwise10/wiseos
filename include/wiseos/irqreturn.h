#ifndef _WISEOS_IRQRETURN_H
#define _WISEOS_IRQRETURN_H

typedef int irqreturn_t;

#define IRQ_NONE	(0)
#define IRQ_HANDLED	(1)
#define IRQ_RETVAL(x)	((x) != 0)	
#endif