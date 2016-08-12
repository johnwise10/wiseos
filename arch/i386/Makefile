#
# Parte del nucle dependiente de la arquitectura
#
# Subsitema init dependiente de la arquitectura
ARCHIVES=$(INIT) $(KERNEL) $(MM)

# Dependencias Para el enlace entre grub y el kernel dependientes de la arquitectura
INITARCH= init/*.c init/*.S ../../include/asm/system.h ../../include/asm/multiboot.h \
	  ../../include/wiseos/linkage.h ../../include/wiseos/config.h \
          ../../include/asm/segment.h ../../include/asm/page.h

# Dependencias para la parte depediente del kernel
KERNARCH=kernel/*.c kernel/*.S ../../include/asm/i8259.h ../../include/wiseos/interrupt.h \
        ../../include/asm/io_ports.h ../../include/asm/io.h ../../include/asm/irq.h \
        ../../include/wiseos/irq.h ../../include/asm/system.h ../../include/wiseos/types.h \
        ../../include/wiseos/spinlock.h ../../include/asm/segment.h ../../include/wiseos/config.h \
	../../include/wiseos/linkage.h ../../include/wiseos/ptrace.h ../../include/wiseos/init.h \
	../../include/wiseos/interrupt.h ../../include/types.h

MMARCH=mm/*.c ../../include/wiseos/page.h

ALL:$(ARCHIVES)

$(INIT): $(INITARCH)
	$(MAKE) -C init

$(KERNEL):$(KERNARCH)
	$(MAKE) -C kernel

$(MM):$(MMARCH)
	$(MAKE) -C mm

clean:
	$(MAKE) clean -C  init 
	$(MAKE) clean -C  mm 
	$(MAKE) clean -C  kernel