#
# Parte del nucle dependiente de la arquitectura
#
# Subsitema init dependiente de la arquitectura

# Subsistema init
INIDIR 			= init/
INIT			= $(INIDIR)$(INITF)
INTSRC		   += $(INIDIR)

# Subsistema kernel
KERNDIR			= kernel/
KERNEL			= $(KERNDIR)$(KERNELF) 
KERNSRC 	   += $(KERNDIR)

ARCHIVES=$(INIT) $(KERNEL)

$(ARCHF): $(ARCHIVES)  
	$(LD) -r -o $(ARCHF) $(ARCHIVES)	

$(INIT): $(INTSRC) $(HDRSRC)
	$(MAKE) -C $(INIDIR)
	
$(KERNEL): $(KERNSRC) $(HDRSRC)
	$(MAKE) -C $(KERNDIR)	

clean:
	$(MAKE) clean -C $(INIDIR) 
	$(MAKE) clean -C $(KERNDIR)	
