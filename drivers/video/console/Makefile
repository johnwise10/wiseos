#
# Autor: Juan Sabio
# Makefile para la compilación del modulo console
#

# Archivos del modulo
ARCHIVES=vgacons.o

$(CONSOLEF):$(ARCHIVES)
	$(LD) -r -o $(CONSOLEF) $(ARCHIVES)

$(ARCHIVES): %.o: %.c $(HDRSRC)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:	
	$(RM) *.o
