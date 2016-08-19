#
# Autor: Juan Sabio
# Makefile para la compilación del modulo tty
#

# Archivos del modulo
ARCHIVES=tty_io.o keyboard.o

$(CHARF): $(ARCHIVES) 
	$(LD) -r -o $(CHARF) $(ARCHIVES)

$(ARCHIVES): %.o: %.c $(HDRSRC)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:	
	$(RM) *.o
