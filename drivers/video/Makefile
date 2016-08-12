#
# Autor: Juan Sabio
# Makefile para la compilación del modulo video
#
# Dependencias del modulo
DEPENDENCIES=console/*.c console/*.h ../../include/wiseos/kernel.h ../../include/wiseos/console.h \
	    ../../include/asm/io.h ../../include/asm/system.h

# Driver para consola
CONSOLEF=console.o
CONSOLE=console/$(CONSOLEF)

# Exportamos los nombres de los drivers a generar
export CONSOLEF

# Archivos del modulo
ARCHIVES=console/console.o

$(VIDEOF): $(ARCHIVES) $(DEPENDENCIES)
	$(LD) -r -o $(VIDEOF) $(ARCHIVES)	

$(CONSOLE): $(DEPENDENCIES)
	$(MAKE) -C console

clean:	
	$(RM) *.o
	$(MAKE) clean -C console
	
