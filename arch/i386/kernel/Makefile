#
# Autor: Juan Sabio
# Makefile para la compilación del kernel
#

# Dependencias del kernel
DEPENDECIES=../../../include/asm/i8259.h ../../../include/wiseos/interrupt.h \
            ../../../include/asm/io_ports.h ../../../include/asm/io.h ../../../include/asm/irq.h \
            ../../../include/wiseos/irq.h ../../../include/asm/system.h ../../../include/wiseos/types.h \
            ../../../include/wiseos/spinlock.h ../../../include/asm/segment.h ../../../include/wiseos/config.h \
            ../../../include/wiseos/linkage.h ../../../include/wiseos/ptrace.h ../../../include/wiseos/init.h \
	    ../../../include/wiseos/interrupt.h ../../../include/types.h

# Archivos del kernel
ARCHIVES= $(ARCHCC) $(ARCHAS)
ARCHAS = entry.o
ARCASP = entry.asm
ARCHCC = irq.o i8259.o traps.o


$(KERNELF): $(ARCHIVES) 
	$(LD) -r -o $(KERNELF) $(ARCHIVES)

$(ARCHAS): %.o: %.asm
	$(AS) $< -o $@

$(ARCASP):%.asm: %.S $(DEPENDECIES)
	$(CPP) -D__KERNEL__ $(INCLUDE) $< -o $@

$(ARCHCC): %.o: %.c $(DEPENDECIES)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:	
	$(RM) *.o *.asm