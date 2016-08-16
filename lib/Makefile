#
# Autor: Juan Sabio
# Makefile que Genera la libreria del kernel que contiene funciones 
# y estructuras utiles para la ejecución de los procesos del kernel
#

# Dependecias de libkc.a
DEPENDECIES= $(INCLUDEDIR)/stack.h $(INCLUDEDIR)/queue.h $(INCLUDEDIR)/asm/string.h \
             $(INCLUDEDIR)/stdarg.h $(INCLUDEDIR)/wiseos/ptrace.h

# Archivos necesarios para libreria del kernel 
ARCHIVES=debug.o queue.o stack.o string.o vsprintf.o

$(LIBKCF): $(ARCHIVES)
	$(AR) $(ARFLAGS) $(LIBKCF) $(ARCHIVES)

$(ARCHIVES): %.o: %.c $(DEPENDECIES)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean: 
	$(RM) *.o libkc.a
