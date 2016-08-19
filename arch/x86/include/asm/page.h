#ifndef _ASM_PAGE_H
#define _ASM_PAGE_H

#include <asm/types.h>

#define PAGE_SHIFT			12

#define NUM_PAGE_TABLE_ENTRIES	1024
#define NUM_PAGE_DIR_ENTRIES	NUM_PAGE_TABLE_ENTRIES

#define PAGE_DIRECTORY_SIZE	0x1000
#define PAGE_TABLE_SIZE		PAGE_DIRECTORY_SIZE
#define PAGE_SIZE		PAGE_DIRECTORY_SIZE

/* Direcciones Físicas del directorio de paginas y 2 tablas de paginas */
#define PAGE_DRTORY_ADDR	 0x00101000
#define PAGE_TLWMEM_ADDR	(PAGE_DRTORY_ADDR + PAGE_TABLE_SIZE)
#define PAGE_TKCODE_ADDR	(PAGE_TLWMEM_ADDR + PAGE_TABLE_SIZE)
#define PAGE_TKHEAP_ADDR	(PAGE_TKCODE_ADDR + PAGE_TABLE_SIZE)

//! Atributos de Pagina
#define PAGE_DIRTY	0x40
#define PAGE_ACCESSED	0x20
#define PAGE_USER	0x04
#define PAGE_RW		0x02
#define PAGE_PRESENT	0x01

typedef int t_pgdir[NUM_PAGE_DIR_ENTRIES];
typedef int t_ptbl[NUM_PAGE_DIR_ENTRIES];

extern t_pgdir pgdir; // Directorio de Páginas
extern t_ptbl  pgt1;  // Pagina 1 para mapear 1:1 y el primer megabyte de memoria
extern t_ptbl  pgt2;  // Pagina 2 para mapear el kernel en 0xC0000000
extern t_ptbl  pgt3;  // Pagina 3 para mapear el kernel heap en 0xD0000000


// Estructura que indica el indice del directorio y de tabla  
// en que se mapea una dirección lógica
typedef struct page_idx_t{
	u16 dir_idx; // Indice del directorio de páginas
	u16 tbl_idx; // Indice de la tabla de páginas
} page_idx_t;

/* Carga CR3 */
#define load_cr3(x) __asm__ ("movl %0, %%cr3" : : "r" (x) )

/* Desactiva/Activa la paginacion */
#define page_off() __asm__ ("mov %cr0, %eax; and $0x7fffffff, %eax; mov %eax, %cr0")
#define page_on()  __asm__ ("mov %cr0, %eax; or $0x80000000, %eax; mov %eax, %cr0")

typedef struct page_t{
	unsigned vaddr:24,
		 age:6,
		 dirty:1,
		 reserved:1;
} page_t;


page_idx_t get_page_idx (addr_t address);
#endif

