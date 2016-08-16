#ifndef _WISEOS_LINKAGE_H
#define _WISEOS_LINKAGE_H

#ifndef __ALIGN
#define __ALIGN		.align 4,0x90
#define __ALIGN_STR	".align 4,0x90"
#endif

#define ALIGN __ALIGN
#define ALIGN_STR __ALIGN_STR

#ifndef ENTRY
#define ENTRY(name) \
  .globl name; \
  ALIGN; \
  name:
#endif

/* C symbol format. HAVE_ASM_USCORE is defined by config.h  */
#ifdef HAVE_ASM_USCORE
# define EXT_C(sym)			_ ## sym
#else
# define EXT_C(sym)			sym
#endif

#endif
