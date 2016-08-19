#include<wiseos/tty.h>
#include<wiseos/console.h>
#include<wiseos/kernel.h>

void tty_init(void)
{
	console_init();
	printk("Iniciando Consola tty...OK\n"); 
	
	//rs_init(); Serial.c puerto rs232 
	//con_init(); console.c pantalla 2.6.22 - mdacon.c
}
