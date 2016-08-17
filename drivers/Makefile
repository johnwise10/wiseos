#
# Autor: Juan Sabio
# Makefile para los modulos del kernel
#

# Driver VGA video
VIDEODIR		= video/
VIDEOF			= video.o
VIDEO			= $(VIDEODIR)$(VIDEOF)
VIDEOSRC 	   += $(VIDEODIR)
VIDEOSRC       += $(VIDEODIR)/console


ARCHIVES += $(VIDEO)

export VIDEOF 

$(DRIVERSF): $(ARCHIVES)  
	$(LD) -r -o $(DRIVERSF) $(ARCHIVES)	

$(VIDEO): $(VIDEOSRC) $(HDRSRC)
	$(MAKE) -C $(VIDEODIR)
	
clean:
	$(RM) *.o
	$(MAKE) clean -C $(VIDEODIR)
	
