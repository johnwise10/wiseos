#
# Autor: Juan Sabio
# Makefile para la compilación del modulo console
#

# Dependencias del modulo
DEPENDENCIES=../../../include/wiseos/kernel.h ../../../include/wiseos/console.h \
	    ../../../include/asm/io.h  ./*.h $(INCLUDEDIR)/asm/system.h

# Archivos del modulo
ARCHIVES=vgacons.o

$(CONSOLEF):$(ARCHIVES)
	$(LD) -r -o $(CONSOLEF) $(ARCHIVES)

$(ARCHIVES): %.o: %.c $(DEPENDENCIES)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:	
	$(RM) *.o
