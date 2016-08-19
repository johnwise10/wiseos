#ifndef _WISEOS_SPINLOCK_H
#define _WISEOS_SPINLOCK_H

#include<wiseos/linkage.h>

#define __lockfunc fastcall __attribute__((section(".spinlock.text")))

#include<wiseos/spinlock_types.h>
#include<asm/spinlock.h>
#define spin_is_locked(lock)	__raw_spin_is_locked(&(lock)->raw_lock)

#define spin_lock_irqsave(lock, flags)	flags = _spin_lock_irqsave(lock)

#define spin_unlock_irqrestore(lock, flags) \
					_spin_unlock_irqrestore(lock, flags)

#endif /* _WISEOS_SPINLOCK_H */

