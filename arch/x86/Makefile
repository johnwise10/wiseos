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

# Subsistema de Memoria
MMDIR 			= mm/
MM				= $(MMDIR)$(MMF)
MMSRC		   += $(MMDIR)


ARCHIVES=$(INIT) $(KERNEL) $(MM)

$(ARCHF): $(ARCHIVES)  
	$(LD) -r -o $(ARCHF) $(ARCHIVES)	

$(INIT): $(INTSRC) $(HDRSRC)
	$(MAKE) -C $(INIDIR)
	
$(KERNEL): $(KERNSRC) $(HDRSRC)
	$(MAKE) -C $(KERNDIR)	
	
$(MM): $(MMSRC) $(HDRSRC)
	$(MAKE) -C $(MMDIR)		

clean:
	$(MAKE) clean -C $(INIDIR) 
	$(MAKE) clean -C $(KERNDIR)	
	$(MAKE) clean -C $(MMDIR)
	$(RM)   *.o
