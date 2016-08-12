#include <wiseos/page.h>
#include <wiseos/memory.h>
#include <wiseos/types.h>
#include <asm/multiboot.h>
#include <wiseos/kernel.h>

/* Check if the bit BIT in FLAGS is set.  */
#define CHECK_FLAG(flags,bit)	((flags) & (1 << (bit)))
void show_mboot_info(multiboot_info_t *mbi){
 
  /* Print out the flags.  */
  printk ("flags = 0x%x\n", (unsigned) mbi->flags);

  /* Are mem_* valid?  */
  if (CHECK_FLAG (mbi->flags, 0))
    printk ("mem_lower = %uKB, mem_upper = %uKB\n",
	    (unsigned) mbi->mem_lower, (unsigned) mbi->mem_upper);

  /* Is boot_device valid?  */
  if (CHECK_FLAG (mbi->flags, 1))
    printk ("boot_device = 0x%x\n", (unsigned) mbi->boot_device);
  
  /* Is the command line passed?  */
  if (CHECK_FLAG (mbi->flags, 2))
    printk ("cmdline = %s\n", (char *) mbi->cmdline);

  /* Are mods_* valid?  */
  if (CHECK_FLAG (mbi->flags, 3))
    {
      module_t *mod;
      int i;
      
      printk ("mods_count = %d, mods_addr = 0x%x\n",
	      (int) mbi->mods_count, (int) mbi->mods_addr);
      for (i = 0, mod = (module_t *) mbi->mods_addr;
	   i < mbi->mods_count;
	   i++, mod += sizeof (module_t))
	printk (" mod_start = 0x%x, mod_end = 0x%x, string = %s\n",
		(unsigned) mod->mod_start,
		(unsigned) mod->mod_end,
		(char *) mod->string);
    }

  /* Bits 4 and 5 are mutually exclusive!  */
  if (CHECK_FLAG (mbi->flags, 4) && CHECK_FLAG (mbi->flags, 5))
    {
      printk ("Both bits 4 and 5 are set.\n");
      return;
    }

  /* Is the symbol table of a.out valid?  */
  if (CHECK_FLAG (mbi->flags, 4))
    {
      aout_symbol_table_t *aout_sym = &(mbi->u.aout_sym);
      
      printk ("aout_symbol_table: tabsize = 0x%0x, "
	      "strsize = 0x%x, addr = 0x%x\n",
	      (unsigned) aout_sym->tabsize,
	      (unsigned) aout_sym->strsize,
	      (unsigned) aout_sym->addr);
    }

}
void mem_init(u32 addr){
  multiboot_info_t * mbi;
  // Fijamos la direccion de la structura de informacion Multiboot. 
  mbi = (multiboot_info_t *) addr;  

  show_mboot_info(mbi);
  
  // Comprobamos si la tabla de cabecera ELF es valida
  if (CHECK_FLAG (mbi->flags, 5)){
    // Comprobamos si el mmap es valido ?
    if (CHECK_FLAG (mbi->flags, 6)){
      mem_init_hw((u32)mbi->mmap_addr,(u32)mbi->mmap_length,(u32)&mbi->u.elf_sec);
    }else{
     printk ("Invalid mmap_*: 0x%x\n", (unsigned)mbi->mmap_addr);
     panic("Halted");
    }
  }else{
     printk ("Section header table of ELF invalid: 0x%x\n", (u32)&mbi->u.elf_sec);
     panic("Halted");
  }
   // Inciamos la gestion de la memoria virtual
   kmalloc_init(0x60000, 0x70000);
  
}

