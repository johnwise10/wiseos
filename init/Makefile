#
# Autor: Juan Sabio
# Makefile para el proceso de inicio del kernel
#

# Archivos del proceso de inicio
ARCHIVES=main.o

$(INITF):$(ARCHIVES)
	$(LD) -r -o $(INITF) $(ARCHIVES)

$(ARCHIVES): %.o: %.c $(HDRSRC)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	$(RM) *.o



