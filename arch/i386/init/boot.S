/* boot.S - bootstrap the kernel */
/* Copyright (C) Juan Sabio Carvajal
 */

#define ASM	1	
#define __ASSEMBLY__

#include <wiseos/config.h>
#include <asm/multiboot.h>
#include <asm/segment.h>
#include <wiseos/linkage.h>

	// La sección setup se carga en la dirección 0x00100000 tanto logica como 
        // Física aprovechamos esta sección para iniciar la paginación y continuar
        // En la sección .text que es donde se encuentra el nucleo del SO, en la 
        // dirección 0xC0000000 aunque realmente este en la dirección fisica 0x100000 
	.section .setup

ENTRY(start)
	jmp	multiboot_entry

	// Alineacion del límite a 32 bits
	.align	4
	
	// Multiboot header.  
multiboot_header:
	// Número mágico
	.long	MULTIBOOT_HEADER_MAGIC
	// flags 
	.long	MULTIBOOT_HEADER_FLAGS
	// checksum 
	.long	-(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

multiboot_entry:
	// Iniciamos el puntero de PILA  
	movl	$(stack + STACK_SIZE), %esp

	// Reseteamos EFLAGS
	pushl	$0
	popf

	// Guardamos el puntero a de la "Multiboot information structure"
	movl %ebx,mbi
       
        // Guardamos el valor Magico
	movl %eax,mva

	// Activamos la paginación 
	xorl %eax,%eax
	movl $EXT_C(pgt1-PAGE_OFFSET),%edi  // Iniciamos la tabla de paginas 1  
					    // Mapeo 1:1 de memoria fisica y logica
	movl $0x007,%eax		    // PRESENT+RW+USER 
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
	movl %cr0,%eax
	orl $0x80000000,%eax
	movl %eax,%cr0			    // Activamos la paginación
	jmp 1f			            // Limpiamos la cola de instrucciones
1:
	movl $1f,%eax
	jmp *%eax			    // nos aseguramos de que el EIP se relocalize

// Datos para inicializar el nucleo de forma adecuada
mbi: 	.long  0x00000000
mva: 	.long  0x00000000

.org SECTION_SETUP_SIZE // Vamos al final de la seccion setup

//	Aqui empieza el codigo en la dirección logica 0xC0000000
.text
1:	
	// Iniciamos el puntero de PILA  
	movl	$(stack + STACK_SIZE), %esp	
	
	// Fijamos la IDT y La GDT
	call EXT_C(setup_descriptors)
	
	// Ponemos el puntero de "Multiboot information structure" en la pila.  
	movl (mbi),%ebx	
	pushl %ebx

	// Ponemos el "magic value" en la pila. 
	movl (mva),%eax
	pushl %eax

	// Iniciamos el kernel en cmain
	call	EXT_C(cmain)	

	// Parada de la maquina. No deberia llegar nunca aqui.
	pushl	$halt_message
	call	EXT_C(printk)
loop:	hlt
	jmp	loop

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
	iret				# happened

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

	.long 0x00102007 // Entrada 0 apuntando a la pagina 1
	.fill 768-1,4,0
	/* default: 767 entries */
	.long 0x00103007 // Entrada 768 apuntado a pagina 2 direccion 0XC0000000
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
	.asciz	"Halted."

.bss
	.comm	stack, STACK_SIZE
	// Area de pila del kernel











	

