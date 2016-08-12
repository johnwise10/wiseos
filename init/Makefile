#
# Autor: Juan Sabio
# Makefile para el proceso de inicio del kernel
#

# Dependecias del proceso de inicio
DEPENDECIES=../include/asm/multiboot.h ../include/wiseos/tty.h

# Archivos del proceso de inicio
ARCHIVES=main.o

$(INITF):$(ARCHIVES)
	$(LD) -r -o $(INITF) $(ARCHIVES)

$(ARCHIVES): %.o: %.c $(DEPENDECIES)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	$(RM) *.o 

	

	
