#
# Autor: Juan Sabio
# Makefile para la compilación del modulo tty
#

# Dependencias del modulo
DEPENDECIES=../../include/wiseos/tty.h  ../../include/wiseos/kernel.h ../../include/wiseos/console.h

# Archivos del modulo
ARCHIVES=tty_io.o keyboard.o

$(CHARF): $(ARCHIVES) 
	$(LD) -r -o $(CHARF) $(ARCHIVES)

$(ARCHIVES): %.o: %.c $(DEPENDECIES)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:	
	$(RM) *.o