#include <asm/multiboot.h>
#include <wiseos/kernel.h>
#include <wiseos/tty.h>
#include <wiseos/init.h>

 
//   Proceso inicial nulo del kernel     
void init();

void __init cmain (unsigned long magic, unsigned long addr)
{

  //tty_init();
  console_init();
  // Comprobamos si hemos arrancado con un Multiboot Boot loader. 
  if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
      printk ("Invalid magic number: 0x%x\n", (unsigned) magic);
      return;
    }
  
 
	printk("Hello World WiseOS\n");



  


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
