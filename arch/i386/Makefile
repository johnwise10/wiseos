#
# Parte del nucle dependiente de la arquitectura
#
# Subsitema init dependiente de la arquitectura
ARCHIVES=$(INIT) 

# Dependencias Para el enlace entre grub y el kernel dependientes de la arquitectura
INITARCH=init/*.S $(INCLUDEDIR)/asm/multiboot.h $(INCLUDEDIR)/wiseos/linkage.h

ALL:$(ARCHIVES)

$(INIT): $(INITARCH)
	$(MAKE) -C init

clean:
	$(MAKE) clean -C  init 
