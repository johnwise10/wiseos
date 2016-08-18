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


# Datos depedientes de la arquitectura a compilar (Init)
ARCHDIR			= arch/$(MACHINE)
ARCHINIDIR 		= arch/$(MACHINE)/$(INIDIR)
ARCHINITF		= init.o
ARCHINIT		= $(ARCHINIDIR)$(ARCHINITF)
ARCHINTSRC	   += $(ARCHINIDIR)

# Datos depedientes de la arquitectura a compilar (Kernel)
ARCHKERNDIR 	= arch/$(MACHINE)/$(KERNDIR)
ARCHKERNF		= kernel.o
ARCHKERN		= $(ARCHKERNDIR)$(ARCHKERNF)


# Dependencias de includes       
HDRSRC= $(INCLUDEDIR)/asm/*.h  $(INCLUDEDIR)/wiseos/*.h   \
        $(INCLUDEDIRARC)/asm/*.h  $(INCLUDEDIR)/*.h
        
        
# Depencias de la imagen del kernel
ARCHIVES=$(ARCHINIT) $(ARCHKERN) $(INIT) $(KERNEL) $(DRIVERS)
    

export INCLUDEDIR INCLUDEDIRARC AS LD CC CPP AR NM STRIP OBJCOPY \
       OBJDUMP INCLUDE CFLAGS ARFLAGS LDFLAGS LIB HDRSRC INITF \
       LIBKCF KERNELF DRIVERSF 

all: $(IMAGE)

$(IMAGE):$(ARCHIVES) $(LIBKC)
	$(LD) -T link.ld -o $(IMAGE) $(ARCHIVES) $(LIB) -lkc $(LDFLAGS) > System.map

$(ARCHINIT): $(ARCHINTSRC) $(HDRSRC)
	$(MAKE) -C $(ARCHDIR)

$(INIT): $(INTSRC) $(HDRSRC)
	$(MAKE) -C $(INIDIR)

$(KERNEL): $(KERNSRC) $(HDRSRC)
	$(MAKE) -C $(KERNDIR)
		
$(LIBKC): $(LIBSRC) $(HDRSRC)
	$(MAKE) -C $(LIBDIR)

$(DRIVERS): $(DRVSRC) $(HDRSRC)
	$(MAKE) -C $(DRIDIR)

clean:  
	$(MAKE) clean -C $(ARCHDIR)
	$(MAKE) clean -C $(INIDIR)
	$(MAKE) clean -C $(KERNDIR)
	$(MAKE) clean -C $(LIBDIR)
	$(MAKE) clean -C $(DRIDIR)
	$(RM)   wsImage *.map
