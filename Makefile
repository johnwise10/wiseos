#
# Autor: Juan Sabio
# Makefile para WiseOS.
#

# Variables que se usarán para la compilación del kernel
TOPDIR := $(shell pwd)
AR=ar
AS=as --32
INCLUDE=-I $(TOPDIR)/include
BINARY=-s --oformat binary
CFLAGS = -Wall -nostdlib -nostartfiles -nodefaultlibs
ARFLAGS = rcs
LDFLAGS = -cref -s -x -M 
LIB=-L $(TOPDIR)/lib
LD=ld -m elf_i386
CC=gcc -m32
CPP=$(CC) -E
OBJ=objcopy -O
ELF=elf32-i386 
RM=rm

# Nombre de la imagen del kernel
IMAGE=wsImage
WSOBJ=wiseos.o

# Arquitectura a compilar
MACHINE=i386

# Datos depedientes del kernel a compilar 
ARCH=arch/$(MACHINE)

# Subsistema init
INITF=init.o
INIT=init/$(INITF)

# Subsistema memoria
MMF=mm.o
MM=mm/$(MMF)

# Subsistema kernel
KERNELF=kernel.o
KERNEL=kernel/$(KERNELF) 

# Subsistema drivers
DRIVERSF=modules.o
DRIVERS=drivers/$(DRIVERSF)

# Libreria del sistema
LIBKCF=libkc.a
LIBKC=lib/$(LIBKCF)

# Depencias de la imagen del kernel
ARCHIVES=$(ARCH)/$(INIT) $(INIT) $(ARCH)/$(MM) $(MM) $(ARCH)/$(KERNEL) $(KERNEL) $(DRIVERS)

# Dependecias de los modulos del kernel
MODSRC=drivers/char/*.c include/wiseos/tty.h include/wiseos/kernel.h drivers/video/console/*.c \
       drivers/video/console/*.h

# Dependecias para la libreria del kernel
LIBSRC=lib/*.c include/stack.h include/queue.h include/asm/string.h include/stdarg.h include/wiseos/ptrace.h

# Dependecias del kernel
KERNSRC=kernel/*.c include/wiseos/tty.h include/stdarg.h include/stddef.h include/wiseos/kernel.h

# Dependencias Para el programa de inicio del kernel
INITSRC=init/*.c include/asm/multiboot.h include/wiseos/tty.h

# Dependencias Para el subsistema de memoria del kernel
MMSRC=mm/*.c include/wiseos/page.h 

# Dependencias Para el enlace entre grub y el kernel dependientes de la arquitectura
INITARCH=$(ARCH)/init/*.S $(ARCH)/init/*.c include/asm/system.h include/asm/multiboot.h \
	 include/wiseos/linkage.h include/wiseos/config.h include/asm/segment.h  \
	 include/asm/page.h

MMARCH=$(ARCH)/mm/*.c include/wiseos/page.h 

# Dependencias para la parte depediente del kernel
KERNARCH=$(ARCH)/kernel/*.c $(ARCH)/kernel/*.S include/asm/i8259.h include/wiseos/interrupt.h \
         include/asm/io_ports.h include/asm/io.h include/asm/irq.h include/wiseos/irq.h include/asm/system.h \
         include/wiseos/types.h include/wiseos/spinlock.h include/asm/segment.h include/wiseos/config.h \
	 include/wiseos/linkage.h include/wiseos/ptrace.h include/wiseos/init.h include/wiseos/interrupt.h \
	 include/types.h
 
export AS INCLUDE BINARY LD CC CPP CFLAGS RM AR ARFLAGS INIT INITF MM MMF KERNEL KERNELF DRIVERS DRIVERSF LIBKC LIBKCF

all: $(IMAGE)

$(IMAGE): $(WSOBJ)
	$(OBJ) $(ELF) $(WSOBJ) $(IMAGE)

$(WSOBJ):$(ARCHIVES) $(LIBKC)
	$(LD) -T link.ld -o $(WSOBJ) $(ARCHIVES) $(LIB) -lkc $(LDFLAGS) > System.map

$(ARCH)/$(INIT): $(INITARCH)
	$(MAKE) -C $(ARCH)

$(INIT): $(INITSRC)
	$(MAKE) -C init

$(ARCH)/$(MM):$(MMARCH)
	$(MAKE) -C $(ARCH)	

$(ARCH)/$(KERNEL): $(KERNARCH)
	$(MAKE) -C $(ARCH)

$(MM):$(MMSRC)
	$(MAKE) -C mm

$(KERNEL): $(KERNSRC)
	$(MAKE) -C kernel

$(LIBKC): $(LIBSRC) 
	$(MAKE) -C lib 

$(DRIVERS): $(MODSRC)
	$(MAKE) -C drivers

clean:  
	$(MAKE) clean -C $(ARCH)
	$(MAKE) clean -C init
	$(MAKE) clean -C mm
	$(MAKE) clean -C lib
	$(MAKE) clean -C kernel
	$(MAKE) clean -C drivers
	$(RM) *.o wsImage *.map

	
