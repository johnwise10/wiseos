#
# Autor: Juan Sabio
# Makefile para la compilación del kernel
#

# Archivos del kernel
ARCHIVES=memory.o

$(MMF): $(ARCHIVES) 
	$(LD) -r -o $(MMF) $(ARCHIVES)

$(ARCHIVES): %.o: %.c $(HDRSRC)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:	
	$(RM) *.o
