# 
# Autor: Juan Sabio
# Makefile para el enlace entre grub y el kernel
#

# Dependencias de boot.S
DEPENDECIES=../../../include/asm/multiboot.h ../../../include/asm/system.h \
	    ../../../include/wiseos/linkage.h ../../../include/wiseos/config.h \
            ../../../include/asm/segment.h ../../../include/asm/page.h

ARCHAS = boot.o
ARCHCC = head.o
ARCASP = boot.asm

ARCHIVES=$(ARCHAS) $(ARCHCC)

$(INITF): $(ARCHIVES)
	$(LD) -r -o $(INITF) $(ARCHIVES)

$(ARCHAS): %.o: %.asm
	$(AS) $< -o $@

$(ARCASP):%.asm: %.S $(DEPENDECIES)
	$(CPP) -D__KERNEL__ $(INCLUDE) $< -o $@

$(ARCHCC): %.o: %.c $(DEPENDECIES)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	$(RM) *.o *.asm 

	

	
