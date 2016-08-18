# 
# Autor: Juan Sabio
# Makefile para el enlace entre grub y el kernel
#

ARCHAS = boot.o
ARCHCC = head.o
ARCASP = boot.asm

ARCHIVES=$(ARCHAS) $(ARCHCC)

$(INITF): $(ARCHIVES)
	$(LD) -r -o $(INITF) $(ARCHIVES)

$(ARCHAS): %.o: %.asm
	$(AS) $< -o $@

$(ARCASP):%.asm: %.S $(HDRSRC)
	$(CPP) -D__KERNEL__ $(INCLUDE) $< -o $@

$(ARCHCC): %.o: %.c $(HDRSRC)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@
	
clean:
	$(RM) *.o *.asm 

	

	
