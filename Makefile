#
# Autor: Juan Sabio
# Makefile para WiseOS.
#

# Variables que se usarán para la compilación del kernel
TOPDIR := $(shell pwd)
CROSS=i686-elf-
AR=$(CROSS)ar
AS=$(CROSS)as
INCLUDE=-I $(TOPDIR)/include
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

# Dependencias Para el enlace entre grub y el kernel dependientes de la arquitectura
INITARCH=$(ARCH)/init/*.S include/asm/multiboot.h

# Dependencias Para el programa de inicio del kernel
INITSRC=init/*.c include/asm/multiboot.h 

# Depencias de la imagen del kernel
ARCHIVES=$(ARCH)/$(INIT) $(INIT) 

export AS INCLUDE LD CC CPP CFLAGS RM AR ARFLAGS INIT INITF 

all: $(IMAGE)

$(IMAGE):$(ARCHIVES) 
	$(LD) -T link.ld -o $(IMAGE) $(ARCHIVES) $(LDFLAGS) > System.map

$(ARCH)/$(INIT): $(INITARCH)
	$(MAKE) -C $(ARCH)

$(INIT): $(INITSRC)
	$(MAKE) -C init
	

clean:  
	$(MAKE) clean -C $(ARCH)
	$(MAKE) clean -C init
	$(RM)   wsImage *.map
