/* boot.S - bootstrap the kernel */
/* Copyright (C) Juan Sabio Carvajal.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */

#define ASM_FILE        1
#include <asm/multiboot.h>
#include <asm/segment.h>
#include <wiseos/linkage.h>

	.section .text.multiboot

ENTRY(start)
	 jmp     multiboot_entry

	 /* Align 32 bits boundary. */
	 .align  4
	 	
	 /* Multiboot header. */
multiboot_header:
	 /* magic */
	 .long   MULTIBOOT_HEADER_MAGIC
	 /* flags */
	 .long   MULTIBOOT_HEADER_FLAGS
	 /* checksum */
	 .long   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
#ifndef __ELF__
	 /* header_addr */
	 .long   multiboot_header
	 /* load_addr */
	 .long   _start
	 /* load_end_addr */
	 .long   _edata
	 /* bss_end_addr */
	 .long   _end
	 /* entry_addr */
	 .long   multiboot_entry
#endif /* ! __ELF__ */

multiboot_entry:
	 /* Initialize the stack pointer. */
	 movl    $(stack-PAGE_OFFSET + STACK_SIZE), %esp
	 
	 /* Reset EFLAGS. */
	 pushl   $0
	 popf
	 
	// Guardamos el puntero a de la "Multiboot information structure"
	movl %ebx,mbi
       
    // Guardamos el valor Magico
	movl %eax,mva
	 	
	// Activamos la paginación 
	xorl %eax,%eax
	movl $EXT_C(pgt1-PAGE_OFFSET),%edi  // Iniciamos la tabla de paginas 1  
					                    // Mapeo 1:1 de memoria fisica y logica
	movl $0x007,%eax		            // PRESENT+RW+USER 
2:	stosl
	add $0x1000,%eax
	cmp $EXT_C(pgt2-PAGE_OFFSET),%edi  
				           
					
	jne 2b
	xorl %eax,%eax
	movl $EXT_C(pgt2-PAGE_OFFSET),%edi  // Iniciamos la tabla de paginas 2
					    // mapeando el kernel en la 
                                            // direccion logica : 0xC00000000
	movl $0x00100007,%eax		    // PRESENT+RW+USER 
3:	stosl
	add $0x1000,%eax
	cmp $(empty_zero_page-PAGE_OFFSET),%edi
	jne 3b
	
	movl $EXT_C(pgdir-PAGE_OFFSET),%eax
	movl %eax,%cr3			    // Fijamos la dirección fisica 
					          // del directorio de páginas
					    
    movl %cr4,%ecx
	orl  $0x0000010,%ecx
	movl %ecx,%cr4
				    
	movl %cr0,%eax
	orl $0x80000000,%eax
	movl %eax,%cr0			    // Activamos la paginación
	jmp 1f			            // Limpiamos la cola de instrucciones
1:
	movl $1f,%eax
	jmp *%eax	


// Datos para inicializar el nucleo de forma adecuada
mbi: 	.long  0x00000000
mva: 	.long  0x00000000

.org SECTION_SETUP_SIZE // Vamos al final de la seccion setup

//	Aqui empieza el codigo en la dirección logica 0xC0000000
.text	 	
1:
	// Iniciamos el puntero de PILA  
	movl	$(stack + STACK_SIZE), %esp	
	
	// Ponemos el puntero de "Multiboot information structure" en la pila.  
	movl (mbi),%ebx	
	pushl %ebx

	// Ponemos el "magic value" en la pila. 
	movl (mva),%eax
	pushl %eax
	 	
	 // Fijamos la IDT y La GDT
	 call EXT_C(setup_descriptors)

	 /* Now enter the C main function... */
	 call    EXT_C(cmain)

	 /* Halt. */
	 pushl   $halt_message
	 call    EXT_C(printk)

loop:   hlt
	 jmp     loop
	 
	 
//	Aqui empieza el codigo en la dirección logica 0xC0000000
.org SECTION_SETUP_SIZE

.text	 

// Carga la tabla global de descriptores (GDT)
ENTRY(EXT_C(setup_gdt))
	lgdt EXT_C(gdt_descr)
reloadSegments:
	movw $KERNEL_DS,%ax
   	movw %ax,%ds
    movw %ax,%es
   	movw %ax,%fs
   	movw %ax,%ss
	ljmp   $KERNEL_CS,$here
here:
   ret

// Este es el manejador de interrupciones por defecto
ignore_int:
	incb 0xb8000+160		# put something on the screen
	movb $2,0xb8000+161		# so that we know something
	iret					# happened

// setup_idt
// Inicializa la tabla idt con 256 entradas apuntando
// a ignore_int. Luego se Lee el descriptor de la idt
// Hay macros para instalar un manejador nuevo en la idt
// y reemplazar el ignore_int inicial

ENTRY(EXT_C(setup_idt))
	lea ignore_int,%edx
	movl $0x000080000,%eax
	movw %dx,%ax		/* selector = 0x0010 = cs */
	movw $0x8E00,%dx	/* interrupt gate - dpl=0, present */
	lea idt,%edi
	mov $256,%ecx
rp_sidt:
	movl %eax,(%edi)
	movl %edx,4(%edi)
	addl $8,%edi
	dec %ecx
	jne rp_sidt
	lidt idt_descr
	ret	 
	
.data	
// Entrada del directorio de paginas
.org 0x1000-SECTION_SETUP_SIZE
ENTRY(EXT_C(pgdir))

	.long 0x102083 // Entrada 0 apuntando a la pagina 1
	.fill 768-1,4,0
	/* default: 767 entries */
	.long 0x103083 // Entrada 768 apuntado a pagina 2 direccion 0XC0000000
	/* default: 254 entries */
	.fill 256-1,4,0

// Pagina 1 para el mapeo 1:1 de las direcciones fisicas
.org 0x2000-SECTION_SETUP_SIZE
ENTRY(EXT_C(pgt1))
.fill 1024-1,4,0
// Pagina 2 para el mapeo del kernel en 0xC0000000
.org 0x3000-SECTION_SETUP_SIZE
ENTRY(EXT_C(pgt2))
.fill 1024-1,4,0
// Tabla para los datos no inicializados del nucleo
.org 0x4000-SECTION_SETUP_SIZE
ENTRY(EXT_C(pgt3))
.fill 1024-1,4,0
// Pagina Nula
.org 0x5000-SECTION_SETUP_SIZE
ENTRY(empty_zero_page)
halt_message:
	 .asciz  "Halted."

.bss
	 /* Our stack area. */
	 .comm   stack, STACK_SIZE
