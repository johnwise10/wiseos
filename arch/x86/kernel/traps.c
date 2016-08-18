#include <wiseos/ptrace.h>
#include <wiseos/init.h>
#include <wiseos/traps.h>
#include <asm/system.h>

#define BT(x,y) \
	BUILD_TRAP(x##y)

#define BUILD_16_TRAPS(x) \
	BT(x,0) BT(x,1) BT(x,2) BT(x,3) \
	BT(x,4) BT(x,5) BT(x,6) BT(x,7) \
	BT(x,8) BT(x,9) BT(x,a) BT(x,b) \
	BT(x,c) BT(x,d) BT(x,e) BT(x,f)
	
BUILD_16_TRAPS(0x0) BUILD_16_TRAPS(0x1)

#undef BUILD_16_TRAPS
#undef BT

#define TRAP(x,y) \
	TRAP##x##y##_interrupt

#define TRAPLIST_16(x) \
	TRAP(x,0), TRAP(x,1), TRAP(x,2), TRAP(x,3), \
	TRAP(x,4), TRAP(x,5), TRAP(x,6), TRAP(x,7), \
	TRAP(x,8), TRAP(x,9), TRAP(x,a), TRAP(x,b), \
	TRAP(x,c), TRAP(x,d), TRAP(x,e), TRAP(x,f)

/* for the irq vectors */

static void (*traps[NR_TRAPS])(void) = {
	TRAPLIST_16(0x0), TRAPLIST_16(0x1)
};
#undef TRAP
#undef TRAPLIST_16

char *trap_desc[NR_TRAPS]={
		"Division por cero", 			  //0x00
		"Exc. Debug", 				  //0x01
		"nmi(Error de Memoria)", 		  //0x02
		"INT3 de byte simple(debug)", 		  //0x03
		"Desbordamiento", 			  //0x04
		"Comprobación de límites",                //0x05
		"Código de operación invalido", 	  //0x06
		"Dispositivo no disponible", 		  //0x07
		"Doble Fallo", 				  //0x08
		"Invasion del segmento del coprocesador", //0x09
		"TSS no válido", 			  //0x0A
		"Segmento no presente", 		  //0x0B
		"Segmento de pila", 			  //0x0C
		"Protección general", 			  //0x0D
		"Excepciones de página", 		  //0x0E
		"Exc. Reservada", 			  //0x0F	
		"Error del coprocesador", 		  //0x10
		"Desconocida", //0x11
		"Desconocida", //0x12
		"Desconocida", //0x13
		"Desconocida", //0x14
		"Desconocida", //0x15
		"Desconocida", //0x16
		"Desconocida", //0x17
		"Desconocida", //0x18
		"Desconocida", //0x19
		"Desconocida", //0x1A
		"Desconocida", //0x1B
		"Desconocida", //0x1C
		"Desconocida", //0x1D
		"Desconocida", //0x1E
		"Desconocida"  //0x1F							
	};

void __init trap_init(void)
{
	int vector;
	for (vector = 0; vector < NR_TRAPS; vector++)
			set_trap_gate(vector, traps[vector]);
}

void do_trap(struct pt_regs reg, int trap){
	printk("Excepcion:0x%x\n",trap);
	printk("%s\n",trap_desc[trap]);
	for(;;);
}
