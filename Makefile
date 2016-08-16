#
# Autor: Juan Sabio
# Makefile para WiseOS.
#

# Variables que se usarán para la compilación del kernel
TOPDIR := $(shell pwd)
CROSS=i686-elf-
AR=$(CROSS)ar
AS=$(CROSS)as
INCLUDEDIR =$(TOPDIR)/include
INCLUDE=-I $(INCLUDEDIR)
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
ARFLAGS = rcs
LDFLAGS = -cref -s -x -M 
LIB=-L $(TOPDIR)/lib
LD=$(CROSS)ld 
CC=$(CROSS)gcc
CPP=$(CC) -E
RM=rm

# Nombre de la imagen del kernel
IMAGE=wsImage

# Arquitectura a compilar
MACHINE=i386

# Datos depedientes del kernel a compilar 
ARCH=arch/$(MACHINE)

# Subsistema init
INITF=init.o
INIT=init/$(INITF)

# Subsistema kernel
KERNELF=kernel.o
KERNEL=kernel/$(KERNELF) 

# Libreria del sistema
LIBKCF=libkc.a
LIBKC=lib/$(LIBKCF)

# Subsistema drivers
DRIVERSF=modules.o
DRIVERS=drivers/$(DRIVERSF)

# Dependencias Para el enlace entre grub y el kernel dependientes de la arquitectura
INITARCH=$(ARCH)/init/*.S include/asm/multiboot.h

# Dependencias Para el programa de inicio del kernel
INITSRC=init/*.c include/asm/multiboot.h 

# Depencias de la imagen del kernel
ARCHIVES=$(ARCH)/$(INIT) $(INIT) $(KERNEL) $(DRIVERS)

# Dependecias del kernel
KERNSRC=kernel/*.c $(INCLUDEDIR)/wiseos/tty.h $(INCLUDEDIR)/stdarg.h $(INCLUDEDIR)/stddef.h \
        $(INCLUDEDIR)/wiseos/kernel.h

# Dependecias para la libreria del kernel
LIBSRC=lib/*.c lib/*.c $(INCLUDEDIR)/stack.h $(INCLUDEDIR)/queue.h $(INCLUDEDIR)/asm/string.h \
       $(INCLUDEDIR)/stdarg.h  $(INCLUDEDIR)/wiseos/ptrace.h
       
# Dependecias de los modulos del kernel
MODSRC=include/wiseos/tty.h include/wiseos/kernel.h drivers/video/console/*.c \
       drivers/video/console/*.h       

export AS INCLUDE INCLUDEDIR LD CC CPP CFLAGS RM AR ARFLAGS INIT INITF LIBKC LIBKCF KERNELF DRIVERSF

all: $(IMAGE)

$(IMAGE):$(ARCHIVES) $(LIBKC)
	$(LD) -T link.ld -o $(IMAGE) $(ARCHIVES) $(LIB) -lkc $(LDFLAGS) > System.map

$(ARCH)/$(INIT): $(INITARCH)
	$(MAKE) -C $(ARCH)

$(INIT): $(INITSRC)
	$(MAKE) -C init

$(KERNEL): $(KERNSRC)
	$(MAKE) -C kernel
		
$(LIBKC): $(LIBSRC) 
	$(MAKE) -C lib 	

$(DRIVERS): $(MODSRC)
	$(MAKE) -C drivers	

clean:  
	$(MAKE) clean -C $(ARCH)
	$(MAKE) clean -C init
	$(MAKE) clean -C kernel
	$(MAKE) clean -C lib
	$(MAKE) clean -C drivers
	$(RM)   wsImage *.map
