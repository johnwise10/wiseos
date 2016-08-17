#
# Autor: Juan Sabio
# Makefile para la compilación del kernel
#

# Archivos del kernel
ARCHIVES=printk.o panic.o console.o 

$(KERNELF): $(ARCHIVES) 
	$(LD) -r -o $(KERNELF) $(ARCHIVES)

$(ARCHIVES): %.o: %.c $(HDRSRC)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:	
	$(RM) *.o
