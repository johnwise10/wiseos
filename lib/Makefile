#
# Autor: Juan Sabio
# Makefile que Genera la libreria del kernel que contiene funciones 
# y estructuras utiles para la ejecución de los procesos del kernel
#

# Archivos necesarios para libreria del kernel 
ARCHIVES=debug.o queue.o stack.o string.o vsprintf.o

$(LIBKCF): $(ARCHIVES)
	$(AR) $(ARFLAGS) $(LIBKCF) $(ARCHIVES)

$(ARCHIVES): %.o: %.c $(HDRSRC)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean: 
	$(RM) *.o $(LIBKCF)
