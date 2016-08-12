#
# Autor: Juan Sabio
# Makefile que Genera la libreria del kernel que contiene funciones 
# y estructuras utiles para la ejecución de los procesos del kernel
#

# Dependecias de libkc.a
DEPENDECIES=../include/stack.h ../include/queue.h ../include/asm/string.h ../include/stdarg.h \
	    ../include/wiseos/ptrace.h

# Archivos necesarios para libreria del kernel 
ARCHIVES=queue.o stack.o string.o vsprintf.o debug.o

$(LIBKCF): $(ARCHIVES)
	$(AR) $(ARFLAGS) $(LIBKCF) $(ARCHIVES)

$(ARCHIVES): %.o: %.c $(DEPENDECIES)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean: 
	$(RM) *.o libkc.a
