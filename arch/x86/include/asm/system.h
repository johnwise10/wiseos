#ifndef _SYSTEM_H
#define _SYSTEM_H
#include<wiseos/types.h>

#define sti() __asm__ __volatile__("sti"::)
#define cli() __asm__ __volatile__("cli"::)
#define nop() __asm__ __volatile__("nop"::)

#define iret() __asm__ __volatile__("iret"::)

#define _set_gate(gate_addr,type,dpl,addr) \
__asm__ __volatile__("movw %%dx,%%ax\n\t" \
	"movw %0,%%dx\n\t" \
	"movl %%eax,%1\n\t" \
	"movl %%edx,%2" \
	: \
	: "i" ((short) (0x8000+(dpl<<13)+(type<<8))), \
	"o" (*((char *) (gate_addr))), \
	"o" (*(4+(char *) (gate_addr))), \
	"d" ((char *) (addr)),"a" (0x00080000))

#define set_intr_gate(n,addr) \
	_set_gate(&idt[n],14,0,addr)

#define set_trap_gate(n,addr) \
	_set_gate(&idt[n],15,0,addr)

#define set_system_gate(n,addr) \
	_set_gate(&idt[n],15,3,addr)

#define IDT_ENTRIES	256
#define GDT_ENTRIES	256

void setup_gdt();
void setup_idt();
void setup_desc_gdt(unsigned long, int);
void setup_desc_idt(unsigned long, int);


typedef struct gdtr_t {
	u16 limite;
	struct base {
		u16 low;
		u16 high;
	}base;
} gdtr_t;

typedef gdtr_t idtr_t;

typedef struct idt_descr_t{
   u16 offset_1; // offset bits 0..15
   u16 selector; // a code segment selector in GDT or LDT
   u8  zero;      // unused, set to 0
   u8  type_attr; // type and attributes, see below
   u16 offset_2; // offset bits 16..31
}idt_descr_t;

typedef struct gdt_descr_t {
	u16 limite1;			// Limite 0:15
	u16 base1;				// Base 0:15
	u8  base2;				// Base 16:23
	u8  atr1;				// P, DPL(2bits),S, Tipo(4bits)
	u8  atr2;				// G, D/B, 0, AVL, Limite 16:19 (4bits) 
	u8  base3;				// Base  24:31
} gdt_descr_t;

extern idt_descr_t idt[IDT_ENTRIES];
extern gdt_descr_t gdt[GDT_ENTRIES];
extern idtr_t idt_descr;
extern gdtr_t gdt_descr;
#endif

