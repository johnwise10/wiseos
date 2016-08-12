#
# Autor: Juan Sabio
# Makefile para la compilación del kernel
#

# Dependencias del kernel
DEPENDECIES= ../../../include/wiseos/page.h

# Archivos del kernel
ARCHIVES=init.o

$(MMF): $(ARCHIVES) 
	$(LD) -r -o $(MMF) $(ARCHIVES)

$(ARCHIVES): %.o: %.c $(DEPENDECIES)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:	
	$(RM) *.o
