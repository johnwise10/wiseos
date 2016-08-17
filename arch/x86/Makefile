#
# Parte del nucle dependiente de la arquitectura
#
# Subsitema init dependiente de la arquitectura

# Subsistema init
INIDIR 			= init/
INIT			= $(INIDIR)$(INITF)
INTSRC		   += $(INIDIR)

ARCHIVES=$(INIT) 

ALL:$(ARCHIVES)

$(INIT): $(INTSRC) $(HDRSRC)
	$(MAKE) -C $(INIDIR)

clean:
	$(MAKE) clean -C  $(INIDIR) 
