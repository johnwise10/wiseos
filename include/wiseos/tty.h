/*
 * Autor: Juan Sabio
 * Definicion de algunas estructuras usadas en tty_io.c y algunas definiciones
 */
#ifndef _TTY_H
#define _TTY_H

typedef struct tty {
          char name[16];
          void (*write)(struct tty_struct * tty);
          
	} tty;
	
typedef struct tty_driver{
        	
        };	
void tty_init(void);

#endif


