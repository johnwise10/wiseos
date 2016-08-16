# 
# Autor: Juan Sabio
# Makefile para el enlace entre grub y el kernel
#

# Dependencias de boot.S
DEPENDECIES=../../../include/asm/multiboot.h 

ARCHAS = boot.o
ARCASP = boot.asm

ARCHIVES=$(ARCHAS) $(ARCHCC)

$(INITF): $(ARCHIVES)
	$(LD) -r -o $(INITF) $(ARCHIVES)

$(ARCHAS): %.o: %.asm
	$(AS) $< -o $@

$(ARCASP):%.asm: %.S $(DEPENDECIES)
	$(CPP) -D__KERNEL__ $(INCLUDE) $< -o $@

clean:
	$(RM) *.o *.asm 

	

	
