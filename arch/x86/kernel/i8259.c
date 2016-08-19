//#include<asm/irq.h>
#include<wiseos/irq.h>
#include<asm/i8259.h>
#include<asm/io.h>
#include<asm/io_ports.h>
#include<wiseos/spinlock.h>
#include<wiseos/types.h>
//#include <asm/i8259.h>

static int i8259A_auto_eoi;
spinlock_t		i8259A_lock;

/*
 * This contains the irq mask for both 8259A irq controllers,
 */
unsigned int cached_irq_mask = 0xFFFF;

static void mask_and_ack_8259A(unsigned int irq);

struct irq_chip i8259A_chip = {
	.name		= "XT-PIC",
	.mask		= disable_8259A_irq,
	.disable	= disable_8259A_irq,
	.enable		= enable_8259A_irq,
	.unmask		= enable_8259A_irq,
	.mask_ack	= mask_and_ack_8259A,
};


void disable_8259A_irq(unsigned int irq)
{
	unsigned int mask = 1 << irq;
	unsigned long flags;

	spin_lock_irqsave(&i8259A_lock, flags);
	cached_irq_mask |= mask;
	if (irq & 8)
		outb(cached_slave_mask, PIC_SLAVE_IMR);
	else
		outb(cached_master_mask, PIC_MASTER_IMR);
	spin_unlock_irqrestore(&i8259A_lock, flags);
}

void enable_8259A_irq(unsigned int irq)
{
	unsigned int mask = ~(1 << irq);
	unsigned long flags;

	spin_lock_irqsave(&i8259A_lock, flags);
	cached_irq_mask &= mask;
	if (irq & 8)
		outb(cached_slave_mask, PIC_SLAVE_IMR);
	else
		outb(cached_master_mask, PIC_MASTER_IMR);
	spin_unlock_irqrestore(&i8259A_lock, flags);
}

/*
 * Careful! The 8259A is a fragile beast, it pretty
 * much _has_ to be done exactly like this (mask it
 * first, _then_ send the EOI, and the order of EOI
 * to the two 8259s is important!
 */
static void mask_and_ack_8259A(unsigned int irq)
{

}


void init_8259A(int auto_eoi){

  
  unsigned long flags;	
  spin_lock_irqsave(&i8259A_lock, flags);
  
  i8259A_auto_eoi = auto_eoi;
  
  outb(0xFF, PIC_MASTER_IMR);	/* Enmascaramos todas las irq del 8259A-1 */
  outb(0xFF, PIC_SLAVE_IMR);	/* Enmascaramos todas las irq del 8259A-2 */
  
  /* Configuramos el PIC 8259 Maestro */
  outb_p(0x11, PIC_MASTER_CMD);	    /* ICW1:  Iniciamos la configuracion del 8259A-1 */
  outb_p(0x20 + 0, PIC_MASTER_IMR); /* ICW2: 8259A-1 IR0-7 mapeadas en 0x20-0x27 */
  outb_p(1U << PIC_CASCADE_IR, PIC_MASTER_IMR); /* ICW3: 8259A-1 (El Maestro) tiene un esclavo en IR2 */
  
  /* ICW4 */
  if (auto_eoi)	/* Si programamos el EOI de forma automatica */
    outb_p(MASTER_ICW4_DEFAULT | PIC_ICW4_AEOI, PIC_MASTER_IMR);
  else		/* Si programamos el EOI de forma normal */
    outb_p(MASTER_ICW4_DEFAULT, PIC_MASTER_IMR);
  
  /* Configuramos el PIC 8259 Esclavo */ 
  outb_p(0x11, PIC_SLAVE_CMD);		 /* ICW1: Iniciamos la configuracion del 8259A-2  */
  outb_p(0x20 + 8, PIC_SLAVE_IMR);	 /* ICW2: 8259A-2 IR0-7 mapped to 0x28-0x2f */
  outb_p(PIC_CASCADE_IR, PIC_SLAVE_IMR); /* ICW3: 8259A-2  es un eclavo del maestro IR2  */
  outb_p(SLAVE_ICW4_DEFAULT, PIC_SLAVE_IMR); /* ICW4 */
 if (auto_eoi)
		/*
		 * In AEOI mode we just have to mask the interrupt
		 * when acking.
		 */
		i8259A_chip.mask_ack = disable_8259A_irq;
	else
		i8259A_chip.mask_ack = mask_and_ack_8259A; 
		  
  outb(0xFF, PIC_MASTER_IMR);	/* Enmascaramos todas las irq del 8259A-1 */
  outb(0xFF, PIC_SLAVE_IMR);	/* Enmascaramos todas las irq del 8259A-2 */		  
  spin_unlock_irqrestore(&i8259A_lock, flags); 
}

static unsigned int startup_8259A_irq(unsigned int irq)
{ 
  enable_8259A_irq(irq);
  return 0; /* never anything pending */
}


