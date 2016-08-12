#ifndef __ASM_SPINLOCK_H
#define __ASM_SPINLOCK_H

#define CLI_STRING	"cli"
#define STI_STRING	"sti"
#define CLI_STI_CLOBBERS
#define CLI_STI_INPUT_ARGS

/*
 * Your basic SMP spinlocks, allowing only a single CPU anywhere
 *
 * Simple spin lock operations.  There are two variants, one clears IRQ's
 * on the local processor, one does not.
 *
 * We make no fairness assumptions. They have a cost.
 *
 * (the type definitions are in asm/spinlock_types.h)
 */

static inline int __raw_spin_is_locked(raw_spinlock_t *x)
{
	return *(volatile signed char *)(&(x)->slock) <= 0;
}



#endif /* __ASM_SPINLOCK_H */

