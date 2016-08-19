#ifndef __ASM_LINKAGE_H
#define __ASM_LINKAGE_H

// Offset para iniciar el nucleo en la direccion 0xC0000000
// 0x00100000 + 0xBFF00000 = 0xC0000000
#define PAGE_OFFSET	0x00000000 
// El tamaño de la sección setup con direcciones  fisicias 
// iguales a las virtuales 0x100000
#define SECTION_SETUP_SIZE 0x100

#define asmlinkage CPP_ASMLINKAGE __attribute__((regparm(0)))
#define FASTCALL(x)	x __attribute__((regparm(3)))
#define fastcall	__attribute__((regparm(3)))

#define prevent_tail_call(ret) __asm__ ("" : "=r" (ret) : "0" (ret))

#ifdef CONFIG_X86_ALIGNMENT_16
#define __ALIGN .align 16,0x90
#define __ALIGN_STR ".align 16,0x90"
#endif
#endif
