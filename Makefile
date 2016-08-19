#
# Autor: Juan Sabio
# Makefile para WiseOS.
#
# Variables que se usarán para la compilación del kernel
TOPDIR 		   := $(shell pwd)

# Arquitectura a compilar
MACHINE        := $(shell uname -m | sed -e s/i.86/x86/ -e s/x86_64/x86/)
            
# Directorios include
INCLUDEDIR 	    = $(TOPDIR)/include
INCLUDEDIRARC   = $(TOPDIR)/arch/$(MACHINE)/include


# Herramientas de compilación
CROSS_COMPILE	= i686-elf-
AS				= $(CROSS_COMPILE)as
LD				= $(CROSS_COMPILE)ld 
CC				= $(CROSS_COMPILE)gcc
CPP				= $(CC) -E
AR				= $(CROSS_COMPILE)ar
NM              = $(CROSS_COMPILE)nm
STRIP           = $(CROSS_COMPILE)strip
OBJCOPY         = $(CROSS_COMPILE)objcopy
OBJDUMP         = $(CROSS_COMPILE)objdump


# Flags de configuración
INCLUDE			= -I $(INCLUDEDIR) -I $(INCLUDEDIRARC)
CFLAGS 			= -std=gnu99 -ffreestanding -O2 -Wall 
ARFLAGS 		= rcs
LDFLAGS 		= -cref -s -x -M 
LIB				= -L $(TOPDIR)/lib

# Comandos de Sistema Operativo
RM				= rm

# Nombre de la imagen del kernel
IMAGE			= wsImage

# Subsistema init
INIDIR 			= init/
INITF			= init.o
INIT			= $(INIDIR)$(INITF)
INTSRC		   += $(INIDIR)

# Subsistema de Memoria
MMDIR 			= mm/
MMF				= mm.o
MM				= $(MMDIR)$(MMF)
MMSRC		   += $(MMDIR)

# Dependecias del kernel
KERNDIR			= kernel/
KERNELF			= kernel.o
KERNEL			= $(KERNDIR)$(KERNELF) 
KERNSRC 	   += $(KERNDIR)

# Libreria del sistema
LIBDIR			= lib/
LIBKCF			= libkc.a
LIBKC			= $(LIBDIR)$(LIBKCF)
LIBSRC 		   += $(LIBDIR)

# Subsistema drivers
DRIDIR 			= drivers/
DRIVERSF		= modules.o
DRIVERS			= $(DRIDIR)$(DRIVERSF)
DRVSRC 		   += $(DRIDIR)
DRVSRC 		   += $(DRIDIR)/video
DRVSRC 		   += $(DRIDIR)/video/console

# Datos depedientes de la arquitectura a compilar
ARCHDIR			= arch/$(MACHINE)/
ARCHF		    = arch.o
ARCH		    = $(ARCHDIR)$(ARCHF)
ARCHSRC	       += $(ARCHDIR	)

# Dependencias de includes       
HDRSRC= $(INCLUDEDIR)/asm/*.h  $(INCLUDEDIR)/wiseos/*.h   \
        $(INCLUDEDIRARC)/asm/*.h  $(INCLUDEDIR)/*.h
        
        
# Depencias de la imagen del kernel
ARCHIVES=$(ARCH) $(INIT) $(MM) $(KERNEL) $(DRIVERS)
    

export INCLUDEDIR INCLUDEDIRARC AS LD CC CPP AR NM STRIP OBJCOPY \
       OBJDUMP INCLUDE CFLAGS ARFLAGS LDFLAGS LIB HDRSRC INITF \
       LIBKCF KERNELF DRIVERSF ARCHF MMF

all: $(IMAGE)

$(IMAGE):$(ARCHIVES) $(LIBKC)
	$(LD) -T link.ld -o $(IMAGE) $(ARCHIVES) $(LIB) -lkc $(LDFLAGS) > System.map

$(ARCH): $(ARCHSRC) $(HDRSRC)
	$(MAKE) -C $(ARCHDIR)

$(INIT): $(INTSRC) $(HDRSRC)
	$(MAKE) -C $(INIDIR)
	
$(MM): $(MMSRC) $(HDRSRC)
	$(MAKE) -C $(MMDIR)	

$(KERNEL): $(KERNSRC) $(HDRSRC)
	$(MAKE) -C $(KERNDIR)
		
$(LIBKC): $(LIBSRC) $(HDRSRC)
	$(MAKE) -C $(LIBDIR)

$(DRIVERS): $(DRVSRC) $(HDRSRC)
	$(MAKE) -C $(DRIDIR)

clean:  
	$(MAKE) clean -C $(ARCHDIR)
	$(MAKE) clean -C $(INIDIR)
	$(MAKE) clean -C $(MMDIR)
	$(MAKE) clean -C $(KERNDIR)
	$(MAKE) clean -C $(LIBDIR)
	$(MAKE) clean -C $(DRIDIR)
	$(RM)   wsImage *.map
