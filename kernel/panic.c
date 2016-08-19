
/*
 * Esta función es usada para mensajes del kernel ( incluyendo mm y fs)
 * e indica un problema critico.
 */
#include <wiseos/kernel.h>

volatile void panic(const char * s)
{
  printk("Kernel panic: %s\n\r",s);
  for(;;){
    __asm__ __volatile(
      "hlt"
    );
  }
}
