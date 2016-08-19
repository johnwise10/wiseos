#ifndef _ASM_MEMORY_H
#define _ASM_MEMORY_H

#include <asm/page.h>

#define MAP_NR(addr) ((addr) >> PAGE_SHIFT)

#define HIGH_MEM 0x00100000

#define VIDEO_MEM_INIT 0xA0000
#define VIDEO_MEM_LENGTH 0x48000

// Definición de las areas de memoria reservadas
#define LWMEM 0  // Memoria Baja
#define BSMEM 1  // Memoria Bios
#define VDMEM 2  // Memoria de Video
#define KLMEM 3  // Mapeo del Kernel
#define KHEAP 4  // Memoria de HEAP 
#define FRMEM 5  // Memoria libre
#define RVMEM 6  // Memoria Reservada


/*
typedef struct mmap_t{
	u32 base;    // Dirección Base
	u32 end;     // Dirección Fin
	u32 length;  // longitud
	u32 vaddr;   // Direccion virtual base
	u32 pages;   // Número de paginas del segmento
	u8  mtype;   // Tipo de memoria 
	void *next;
}mmap_t;

typedef struct kmem_t{
	mmap_t *mmap;
	u32 base;
	u32 end;
	u32 length;
	u32 pages;
}kmem_t;*/

typedef struct kmem_t{
	page_t  *mem_map;
	u32 base;
	u32 end;
	u32 length;
	u32 pages;
}kmem_t;

void add_range_memory(addr_t, addr_t, u8);
//mmap_t * new_item(mmap_t *, int *);

#endif
