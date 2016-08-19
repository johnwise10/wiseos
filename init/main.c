#include <asm/multiboot.h>
#include <wiseos/kernel.h>
#include <wiseos/tty.h>
#include <wiseos/init.h>
#include <wiseos/interrupt.h>

//   Proceso inicial nulo del kernel     
void init();

//void show_multiboot_info (unsigned long magic, unsigned long addr);

void __init cmain (unsigned long magic, unsigned long addr)
{
	
  int_disable();
  tty_init();
  //console_init();
  // Comprobamos si hemos arrancado con un Multiboot Boot loader. 
  if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
      printk ("Invalid magic number: 0x%x\n", (unsigned) magic);
      return;
    }
  
 // show_multiboot_info(magic,addr);
  
  mem_init((u32)addr); 
  
  trap_init();
  init_IRQ();
  init_keyboard();
  
  printk("Hello World WiseOS\n");
  
  printk("0x%x\n",cmain);
  
  /*printk("0x%x\n",pgdir[0]);

  printk("0x%x\n",pgdir[768]);
  
  printk("0x%x\n",pgt1[256]);
  printk("0x%x\n",pgt2[4]);
  printk("0x%x\n",cmain);
  printk("0x%x\n",&pgdir);
  printk("0x%x\n",&pgt3);  */

  int_enable();
  init();
  panic("Error Fatal..");
}    

void init(){
  for(;;){
    __asm__ __volatile(
      "movl $0xFFFFFFFF,%ecx\n"
      "hlt\n"
      "repnz"
    );
  }
}

