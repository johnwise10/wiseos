#
# Autor: Juan Sabio
# Makefile para los modulos del kernel
#
VIDEOF=video.o
VIDEO=video/$(VIDEOF)
CHARF=char.o
CHAR=char/$(CHARF)

ARCHIVES=$(CHAR) $(VIDEO)


#Depencias para el modulo tty del kernel
CHRSRC=char/*.c  ../include/wiseos/tty.h ../include/wiseos/kernel.h  ../include/wiseos/console.h

#Dependendicas  para el modulo video del kernel
VIDEOSRC=video/console/*.c video/console/*.h  ../include/wiseos/kernel.h  ../include/wiseos/console.h \
	 ../include/asm/io.h ../include/asm/system.h

export VIDEOF CHARF 

$(DRIVERSF): $(ARCHIVES) 
	$(LD) -r -o $(DRIVERSF) $(ARCHIVES)	

$(CHAR):$(CHRSRC)
	$(MAKE) -C char

$(VIDEO): $(VIDEOSRC)
	$(MAKE) -C video
clean:
	$(RM) *.o
	$(MAKE) clean -C char
	$(MAKE) clean -C video
	