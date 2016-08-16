#
# Autor: Juan Sabio
# Makefile para los modulos del kernel
#
VIDEOF=video.o
VIDEO=video/$(VIDEOF)


ARCHIVES= $(VIDEO)


#Depencias para el modulo tty del kernel
CHRSRC=char/*.c  $(INCLUDEDIR)/wiseos/tty.h $(INCLUDEDIR)/wiseos/kernel.h  \
                 $(INCLUDEDIR)/console.h

#Dependendicas  para el modulo video del kernel
VIDEOSRC=video/console/*.c video/console/*.h  $(INCLUDEDIR)/wiseos/kernel.h  $(INCLUDEDIR)/wiseos/console.h \
	 $(INCLUDEDIR)/asm/io.h  $(INCLUDEDIR)/asm/system.h

export VIDEOF 

$(DRIVERSF): $(ARCHIVES) 
	$(LD) -r -o $(DRIVERSF) $(ARCHIVES)	

$(VIDEO): $(VIDEOSRC)
	$(MAKE) -C video
	
clean:
	$(RM) *.o
	$(MAKE) clean -C video
	
