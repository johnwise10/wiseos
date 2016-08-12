#ifndef __WISEOS_SPINLOCK_TYPES_H
#define __WISEOS_SPINLOCK_TYPES_H

/*
 * include/wiseos/spinlock_types.h - generic spinlock type definitions
 *                                  and initializers
 *
 * portions Copyright 2005, Red Hat, Inc., Ingo Molnar
 * Released under the General Public License (GPL).
 */

//#include <linux/lockdep.h>

#include <asm/spinlock_types.h>

typedef struct {
	raw_spinlock_t raw_lock;
	unsigned int break_lock;
} spinlock_t;

#define SPINLOCK_MAGIC		0xdead4ead

typedef struct {
	raw_rwlock_t raw_lock;
	unsigned int break_lock;
} rwlock_t;

#define RWLOCK_MAGIC		0xdeaf1eed

#define SPINLOCK_OWNER_INIT	((void *)-1L)

# define SPIN_DEP_MAP_INIT(lockname)



# define RW_DEP_MAP_INIT(lockname)

#define __SPIN_LOCK_UNLOCKED(lockname) \
	(spinlock_t)	{	.raw_lock = __RAW_SPIN_LOCK_UNLOCKED,	\
				SPIN_DEP_MAP_INIT(lockname) }
#define __RW_LOCK_UNLOCKED(lockname) \
	(rwlock_t)	{	.raw_lock = __RAW_RW_LOCK_UNLOCKED,	\
				RW_DEP_MAP_INIT(lockname) }

/*
 * SPIN_LOCK_UNLOCKED and RW_LOCK_UNLOCKED defeat lockdep state tracking and
 * are hence deprecated.
 * Please use DEFINE_SPINLOCK()/DEFINE_RWLOCK() or
 * __SPIN_LOCK_UNLOCKED()/__RW_LOCK_UNLOCKED() as appropriate.
 */
#define SPIN_LOCK_UNLOCKED	__SPIN_LOCK_UNLOCKED(old_style_spin_init)
#define RW_LOCK_UNLOCKED	__RW_LOCK_UNLOCKED(old_style_rw_init)

#define DEFINE_SPINLOCK(x)	spinlock_t x = __SPIN_LOCK_UNLOCKED(x)
#define DEFINE_RWLOCK(x)	rwlock_t x = __RW_LOCK_UNLOCKED(x)

#endif /* __WISEOS_SPINLOCK_TYPES_H */
