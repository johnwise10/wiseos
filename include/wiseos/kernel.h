/*
 * 'Kernel.h' Contiene los prototipos del algunas funciones usadas 
 * Frecuente.
 */
volatile void panic(const char * str);
void console_init(void);
int printk(const char * fmt, ...);
