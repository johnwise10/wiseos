#
# Autor: Juan Sabio
# Makefile para la compilación del kernel
#

# Archivos del kernel
ARCHIVES= $(ARCHCC) $(ARCHAS)
ARCHAS = entry.o
ARCASP = entry.asm
ARCHCC = irq.o i8259.o traps.o


$(KERNELF): $(ARCHIVES) 
	$(LD) -r -o $(KERNELF) $(ARCHIVES)

$(ARCHAS): %.o: %.asm
	$(AS) $< -o $@

$(ARCASP):%.asm: %.S $(HDRSRC)
	$(CPP) -D__KERNEL__ $(INCLUDE) $< -o $@

$(ARCHCC): %.o: %.c $(HDRSRC)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:	
	$(RM) *.o *.asm
