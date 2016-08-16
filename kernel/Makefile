#
# Autor: Juan Sabio
# Makefile para la compilación del kernel
#

# Dependencias del kernel
DEPENDECIES=$(INCLUDEDIR)/wiseos/tty.h $(INCLUDEDIR)/stdarg.h $(INCLUDEDIR)/stddef.h \
            $(INCLUDEDIR)/wiseos/kernel.h $(INCLUDEDIR)/wiseos/console.h

# Archivos del kernel
ARCHIVES=printk.o panic.o console.o 

$(KERNELF): $(ARCHIVES) 
	$(LD) -r -o $(KERNELF) $(ARCHIVES)

$(ARCHIVES): %.o: %.c $(DEPENDECIES)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:	
	$(RM) *.o
