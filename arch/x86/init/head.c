#include <asm/system.h>
#include <asm/page.h>

idtr_t idt_descr;
gdtr_t gdt_descr;

idt_descr_t idt[IDT_ENTRIES];

gdt_descr_t gdt[GDT_ENTRIES]={
  {0,0,0,0,0,0}, 			/* Descriptor nulo */
  {0xFFFF,0x0000,0x00,0x9A,0xCF,0x00},  // 0x08 Kernel Code Segment
  {0xFFFF,0x0000,0x00,0x92,0xCF,0x00},  // 0x10 Kernel Data Segment
//  {0xFFFF,0x0000,0x00,0xFA,0xCB,0xC0}, // 0x18 User Code Segment
//  {0xFFFF,0x0000,0x00,0xF2,0xCB,0xC0}, // 0x20 User Data Segment
  {0,0,0,0,0,0},
};

void setup_desc_gdt(unsigned long gdtBaseAddr, int entries){
  gdt_descr.limite = entries*sizeof(gdt_descr_t) -1;
  gdt_descr.base.low = gdtBaseAddr & 0xffff;
  gdt_descr.base.high= gdtBaseAddr >> 16;	
}

void setup_desc_idt(unsigned long idtBaseAddr, int entries){
  idt_descr.limite = entries*sizeof(idt_descr_t) -1;
  idt_descr.base.low = idtBaseAddr & 0xffff;
  idt_descr.base.high= idtBaseAddr >> 16;	
}

void setup_descriptors(void){

  setup_desc_gdt((unsigned long )gdt,GDT_ENTRIES);
  setup_desc_idt((unsigned long )idt,IDT_ENTRIES);
 
  setup_gdt();
  setup_idt();
}


