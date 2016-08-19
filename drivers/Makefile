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

# Driver tty
CHARDIR		    = char/
CHARF			= char.o
CHAR			= $(CHARDIR)$(CHARF)
CHARSRC 	   += $(CHARDIR)

ARCHIVES += $(VIDEO) $(CHAR) 

export VIDEOF CHARF

$(DRIVERSF): $(ARCHIVES)  
	$(LD) -r -o $(DRIVERSF) $(ARCHIVES)	

$(VIDEO): $(VIDEOSRC) $(HDRSRC)
	$(MAKE) -C $(VIDEODIR)
	
$(CHAR): $(CHARSRC) $(HDRSRC)
	$(MAKE) -C $(CHARDIR)	
	
clean:
	$(RM) *.o
	$(MAKE) clean -C $(VIDEODIR)
	
