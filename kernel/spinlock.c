//#include <wiseos/kernel.h>
#include <wiseos/spinlock.h>
#include <wiseos/interrupt.h>

/* Se implementaran los spinlocks mas adelante*/
int __lockfunc _spin_trylock(spinlock_t *lock){
       //spin_is_locked(spin);
//       printk("spinlock\n");
       return 0;
}

unsigned long __lockfunc _spin_lock_irqsave(spinlock_t *lock)
{
	unsigned long flags;

	local_irq_save(flags);
	/*preempt_disable();
	spin_acquire(&lock->dep_map, 0, 0, _RET_IP_);
	/*
	 * On lockdep we dont want the hand-coded irq-enable of
	 * _raw_spin_lock_flags() code, because lockdep assumes
	 * that interrupts are not re-enabled during lock-acquire:
	 */
//#ifdef CONFIG_PROVE_LOCKING
//	_raw_spin_lock(lock);
//#else
//	_raw_spin_lock_flags(lock, &flags);
//#endif 
	return flags;
}

void __lockfunc _spin_unlock_irqrestore(spinlock_t *lock, unsigned long flags)
{
	//spin_release(&lock->dep_map, 1, _RET_IP_);
	//_raw_spin_unlock(lock);
	local_irq_restore(flags);
	//preempt_enable();
}
