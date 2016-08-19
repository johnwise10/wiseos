#
# Autor: Juan Sabio
# Makefile para la compilación del modulo video
#

# Driver para consola
CONSOLEDIR=console/
CONSOLEF=console.o
CONSOLE=$(CONSOLEDIR)$(CONSOLEF)


# Exportamos los nombres de los drivers a generar
export CONSOLEF

# Archivos del modulo
ARCHIVES=$(CONSOLE)

$(VIDEOF): $(ARCHIVES) 
	$(LD) -r -o $(VIDEOF) $(ARCHIVES)	

$(CONSOLE): $(CONSOLEDIR) $(HDRSRC)
	$(MAKE) -C $(CONSOLEDIR)

clean:	
	$(RM) *.o
	$(MAKE) clean -C $(CONSOLEDIR)
	
