#ifndef _ASM_IRQFLAGS_H
#define _ASM_IRQFLAGS_H

#define local_irq_save(flags) flags = native_save_fl()
#define local_irq_restore(flags) native_restore_fl(flags);

static inline unsigned long native_save_fl(void)
{
	unsigned long f;
	asm volatile("pushfl ; popl %0":"=g" (f): /* no input */);
	return f;
}

static inline void native_restore_fl(unsigned long f)
{
	asm volatile("pushl %0 ; popfl": /* no output */
			     :"g" (f)
			     :"memory", "cc");
}

static inline void native_irq_disable(void)
{
	asm volatile("cli": : :"memory");
}

static inline void native_irq_enable(void)
{
	asm volatile("sti": : :"memory");
}

static inline void native_safe_halt(void)
{
	asm volatile("sti; hlt": : :"memory");
}

static inline void native_halt(void)
{
	asm volatile("hlt": : :"memory");
}

static inline void raw_local_irq_enable(void)
{
	native_irq_enable();
}
#endif
