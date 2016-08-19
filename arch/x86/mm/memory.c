#include <asm/page.h>
#include <asm/system.h>
#include <asm/multiboot.h>
#include <wiseos/ptrace.h>
#include <wiseos/linkage.h>
#include <asm/memory.h>
#include <wiseos/kernel.h>
#include <types.h>
	
kmem_t mmap_os;
//page_t  *mem_map;

void mem_init_hw(u32 mmap_addr, u32 mmap_length, u32 elf_sec_addr){
  /*addr_t  addr, base, length;
  int i;
  page_idx_t idx;
  memory_map_t *mmap; 
  elf_section_header_table_t *elf_sec = (elf_section_header_table_t *)elf_sec_addr;
  mmap_os.mem_map = (u32)elf_sec->addr + (u32)PAGE_OFFSET;
  
  // Seleccionamos el mapeo de memoria y los guardamos
  for (mmap = (memory_map_t *)mmap_addr;
           (unsigned long) mmap < mmap_addr + mmap_length;
	   mmap = (memory_map_t *) ((unsigned long) mmap
				    + mmap->size + sizeof (mmap->size))){
	if (mmap->type == 1)
	  add_range_memory(mmap->base_addr_low,mmap->length_low,0);
	else
	  add_range_memory(mmap->base_addr_low,mmap->length_low,1);	
  }
  
  mmap_os.length = mmap_os.length + VIDEO_MEM_LENGTH;
  mmap_os.base = 0;
  mmap_os.end = mmap_os.base + mmap_os.length;
  mmap_os.pages = mmap_os.length / PAGE_SIZE;
  
  // Mapeamos la memoria de video?
  add_range_memory(VIDEO_MEM_INIT,VIDEO_MEM_LENGTH,1);

  base = 0x100000;
  length = elf_sec->addr-base;
  length = length + (mmap_os.pages*4);
  add_range_memory(base,length,1);


  idx = get_page_idx (0x116000);
   i=idx.tbl_idx;
   printk("0x%x\n",&mmap_os.mem_map[3840]);
   
  printk("%d\n",idx.dir_idx);
  printk("%d\n",idx.tbl_idx);
  printk("mem_map[%d], vaddr: 0x%x, age: 0x%x, dirty: 0x%x, reserved: 0x%x \n",
  	 i,mmap_os.mem_map[i].vaddr, mmap_os.mem_map[i].age,mmap_os.mem_map[i].dirty,mmap_os.mem_map[i].reserved);  
  printk("i:%d\n",i);*/
  //mmap_os.mem_map[1].vaddr = 0xD00000;
  //mmap_os.mem_map[1].age = 0;
  //mmap_os.mem_map[1].dirty = 0;
  //mmap_os.mem_map[1].reserved = 0;
  /*for(i=0;i<10;i++){
  printk("mem_map[%d], vaddr: 0x%x, age: 0x%x, dirty: 0x%x, reserved: 0x%x \n",
  	 i,mmap_os.mem_map[i].vaddr, mmap_os.mem_map[i].age,mmap_os.mem_map[i].dirty,mmap_os.mem_map[i].reserved);
  }   */  
/*
  printk("base: 0x%x\n", mmap_os.base);
  printk("end: 0x%x\n",  mmap_os.end);
  printk("length: 0x%x\n",mmap_os.length);
  printk("pages: %d\n", mmap_os.pages);  */
	    
 /* memory_map_t *mmap; 
  int i,p;    
  mmap_t *item;
  mmap_t *prev;
  
 elf_section_header_table_t *elf_sec = (elf_section_header_table_t *)elf_sec_addr;
 mmap_os.mmap = (u32)elf_sec->addr + (u32)PAGE_OFFSET;
 item = mmap_os.mmap;
 prev = NULL;
 i=p=0;
 printk ("elf_sec: num = %u, size = 0x%x,"
          " addr = 0x%x, shndx = 0x%x\n", // addr - 0x100000 = tamaño kernel
	  (unsigned) elf_sec->num, (unsigned) elf_sec->size,
	  (unsigned) elf_sec->addr, (unsigned) elf_sec->shndx);  
	    
 mmap_os.base = mmap_os.length = 0;	      
  // Seleccionamos el mapeo de memoria y los guardamos
  for (mmap = (memory_map_t *)mmap_addr;
           (unsigned long) mmap < mmap_addr + mmap_length;
	   mmap = (memory_map_t *) ((unsigned long) mmap
				    + mmap->size + sizeof (mmap->size))){				    

    if (mmap->type == 1){
      if (mmap->base_addr_low < HIGH_MEM){
      	// Mapeo de Low Mem
        item->base=mmap->base_addr_low;
    	item->end =mmap->base_addr_low + mmap->length_low;
    	item->length = mmap->length_low;
        item->vaddr = 0;
    	item->pages = item->length / PAGE_SIZE;
    	item->next = NULL;
    	item->mtype = LWMEM;
    	mmap_os.length = mmap_os.length + item->length;
    	p=p+item->pages;
      }else{
      	// Mapeo del Kernel
        item->base = mmap->base_addr_low;
        item->end  = elf_sec->addr +PAGE_SIZE;
    	item->length = item->end - item->base;
    	item->vaddr = 0xC0000000;
    	item->pages = item->length / PAGE_SIZE;	
    	item->mtype = KLMEM;
    	item->next = NULL;
      	mmap_os.length = mmap_os.length + item->length;
      	p=p+item->pages;
      	
      	prev->next = item;
	prev = item;
	item = new_item(item,&i); 
	
	// HEAP
    	item->base =  prev->end;
    	item->end  = item->base + (mmap->length_low/8);
    	item->length = (mmap->length_low/8);
    	item->vaddr = 0xD0000000;
    	item->pages = item->length / PAGE_SIZE;  
        item->mtype = KHEAP;
    	item->next  = NULL;
    	mmap_os.length = mmap_os.length + item->length;
    	p=p+item->pages;
    	
      	prev->next = item;
	prev = item;
	item = new_item(item,&i); 
    	  
        // Free
        item->base = prev->end;
        item->end  = mmap->base_addr_low + mmap->length_low;
    	item->length = item->end - prev->end;
    	item->vaddr = 0;
    	item->pages = item->length / PAGE_SIZE;
    	item->mtype = FRMEM;
    	item->next  = NULL;    
    	mmap_os.length = mmap_os.length + item->length;	
    	p=p+item->pages;	
      }   
    }else{
      if (mmap->base_addr_low < HIGH_MEM){
      	item->base = mmap->base_addr_low;
      	item->end  = mmap->base_addr_low + mmap->length_low;
      	item->length = mmap->length_low;
      	item->vaddr = 0;
      	item->pages = item->length / PAGE_SIZE;
      	item->next = NULL;
      	item->mtype = BSMEM;
      	mmap_os.length = mmap_os.length + item->length;
      	p=p+item->pages;
      	if (item->end == VIDEO_MEM_INIT){
      	  prev->next = item;
	  prev = item;
	  item = new_item(item,&i);
      	  item->base = prev->end;
      	  item->end  = item->base + VIDEO_MEM_LENGTH;
      	  item->length = VIDEO_MEM_LENGTH;
      	  item->vaddr = 0;
      	  item->pages = item->length / PAGE_SIZE;
      	  item->next = NULL;
      	  item->mtype = VDMEM;	  
      	  mmap_os.length = mmap_os.length + item->length;
      	  p=p+item->pages;
	}
      }else{
        item->base = mmap->base_addr_low;
      	item->end  = mmap->base_addr_low + mmap->length_low;
      	item->length = mmap->length_low;
      	item->vaddr = 0;
      	item->pages = item->length / PAGE_SIZE;
      	item->next = NULL;
      	item->mtype = RVMEM;
      	mmap_os.length = mmap_os.length + item->length;
      	p=p+item->pages;
      }
    }
    if ( prev != NULL ){ 
        prev->next = item;
    }
    prev = item;
    item = new_item(item,&i);
  }
  	
 	mmap_os.end = mmap_os.base + mmap_os.length;
  	mmap_os.pages = mmap_os.length / PAGE_SIZE;
  	
	  printk("base: 0x%x\n", mmap_os.base);
	  printk("end: 0x%x\n",  mmap_os.end);
	  printk("length: 0x%x\n",mmap_os.length);
	  printk("pages: %d\n", mmap_os.pages);  
	  printk("pages: %d\n",p);	
  	item = mmap_os.mmap;
 	while(item!=NULL){
	  printk("base: 0x%x, ", item->base);
	  printk("end: 0x%x, ",  item->end);
	  printk("length: 0x%x, ",item->length);
	  printk("vaddr: 0x%x, ", item->vaddr);
	  printk("pages: %d\n", item->pages);
	  item = item->next;
	}*/

   //page_off();
   // Fijamos en la entrada 0 la tabla de paginas 1  
//   pdir[768] = TABLE_KCODE_ADDR;
//   pdir[768] = pdir[768] | 3;  // indicamos que la tabla esta activa	
//   832 es la entrada del kernel keap
//  pgdir[832] = PAGE_TKHEAP_ADDR;
//  pgdir[832] = pgdir[832] | 3;
// Iniciamos la tabla 3 es el kernel keap
 /* for (i=0; i<512;i++){
  	pgt3[i] = kmem.kheap.base + PAGE_SIZE*i;
  	pgt3[i] = pgt3[i] | 3; 
  }
   // Inicializamos la tabla de paginas 1
  for(i=kmem.klmem.pages+1;i<NUM_PAGE_TABLE_ENTRIES;i++)
    	pgt2[i] = 0;

   for(i=256;i<NUM_PAGE_TABLE_ENTRIES;i++)
    	pgt1[i] = 0;  */	
    	
      	
   // Mapeamos los primeros 4 megabytes de memoria 1:1  
/*   for(i=0;i<NUM_PAGE_TABLE_ENTRIES;i++){
    pgt2[i] = 0x100000 + PAGE_SIZE*i;
    pgt2[i] = pgt2[i] | 3;
   }  */
   /*page_on();
   setup_desc_gdt((unsigned long )gdt,GDT_ENTRIES);
   setup_gdt(); */
  /* page_idx_t idx;
   idx=get_page_idx (0xD03FF023);
   printk("dir_idx:%d\n",idx.dir_idx);
   printk("tbl_idx:%d\n",idx.tbl_idx);*/
}


void add_range_memory(addr_t base, addr_t length, u8 reserved){
  addr_t addr;
  
  if (base != 0xFFFC0000)
  	mmap_os.length = mmap_os.length + length; 
  
  for (addr=base;
       addr<(base+length) && (length>PAGE_SIZE);
       addr=addr+PAGE_SIZE){  
    if ((base> HIGH_MEM)&& addr==0)
      break;        
    mmap_os.mem_map[MAP_NR(addr)].vaddr = PAGE_SIZE*MAP_NR(addr);
    mmap_os.mem_map[MAP_NR(addr)].age = 0;
    mmap_os.mem_map[MAP_NR(addr)].dirty = 0;
    mmap_os.mem_map[MAP_NR(addr)].reserved = reserved;
  }
}
//! Devuelve en la estructura la posicion dentro del DIR de paginas, y dentro de la Tabla
page_idx_t get_page_idx (addr_t address)
{	
  page_idx_t idx;
  idx.dir_idx = address / ( PAGE_SIZE * NUM_PAGE_DIR_ENTRIES);
  idx.tbl_idx = (address % ( PAGE_SIZE * NUM_PAGE_TABLE_ENTRIES)) / PAGE_SIZE;
  return idx;
}
