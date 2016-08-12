#
# Autor: Juan Sabio
# Makefile para la compilación del kernel
#

# Dependencias del kernel
DEPENDECIES=../include/wiseos/tty.h ../include/stdarg.h  ../include/stddef.h ../include/wiseos/kernel.h

# Archivos del kernel
ARCHIVES=printk.o panic.o console.o signal.o spinlock.o softirq.o

$(KERNELF): $(ARCHIVES) 
	$(LD) -r -o $(KERNELF) $(ARCHIVES)

$(ARCHIVES): %.o: %.c $(DEPENDECIES)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:	
	$(RM) *.o
