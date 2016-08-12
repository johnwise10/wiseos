#ifndef _WISEOS_ASM_ATOMIC_
#define _WISEOS_ASM_ATOMIC_

#include <wiseos/config.h>

#ifdef CONFIG_MP
#define LOCK_PREFIX "lock; "
#else
#define LOCK_PREFIX ""
#endif

#define atomic_read(cnt)		(*(cnt))
#define atomic_write(cnt, val)		(*(cnt) = val)

static __inline__ void atomic_add(u32 *cnt, u32 val)
{
	__asm__ __volatile__(
		LOCK_PREFIX
		"addl %1,%0"
		:"=m" (*cnt)
		:"r"  (val), "m" (*cnt)
		);
}

static __inline__ void atomic_sub(u32 *cnt, u32 val)
{
	__asm__ __volatile__(
		LOCK_PREFIX
		"subl %1,%0"
		:"=m" (*cnt)
		:"r"  (val), "m" (*cnt)
		);
}

static __inline__ void atomic_inc(u32 *cnt)
{
	__asm__ __volatile__(
		LOCK_PREFIX
		"incl %0"
		:"=m" (*cnt)
		:"m"  (*cnt)
		);
}

static __inline__ void atomic_dec(u32 *cnt)
{
	__asm__ __volatile__(
		LOCK_PREFIX "incl %0"
		:"=m" (*cnt)
		:"m"  (*cnt)
		);
}

static __inline__ int atomic_dec_and_test(u32 *cnt)
{
	unsigned char c;

	__asm__ __volatile__(
		LOCK_PREFIX "decl %0; sete %1"
		:"=m" (*cnt), "=qm" (c)
		:"m" (*cnt) : "memory");
	return c != 0;
}

static __inline__ int atomic_inc_and_test(u32 *cnt)
{
	unsigned char c;

	__asm__ __volatile__(
		LOCK_PREFIX "incl %0; sete %1"
		:"=m" (*cnt), "=qm" (c)
		:"m" (*cnt) : "memory");
	return c != 0;
}

#endif