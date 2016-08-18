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

.text

multiboot_entry:
	 /* Initialize the stack pointer. */
	 movl    $(stack + STACK_SIZE), %esp
	 
	 /* Reset EFLAGS. */
	 pushl   $0
	 popf

	 /* Push the pointer to the Multiboot information structure. */
	 pushl   %ebx
	 /* Push the magic value. */
	 pushl   %eax

	 // Fijamos la IDT y La GDT
	 call EXT_C(setup_descriptors)

	 /* Now enter the C main function... */
	 call    EXT_C(cmain)

	 /* Halt. */
	 pushl   $halt_message
	 call    EXT_C(printk)

loop:   hlt
	 jmp     loop

halt_message:
	 .asciz  "Halted."

	 /* Our stack area. */
	 .comm   stack, STACK_SIZE
	 

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
