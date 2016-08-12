#include <asm/io.h>
#include <wiseos/irq.h>
#include <wiseos/interrupt.h>
#include <types.h>

#include "keyboard.h"

struct irqaction keyb;

static const char s_scanTableNoShift[] = {
    KEY_UNKNOWN, ASCII_ESC, '1', '2',   /* 0x00 - 0x03 */
    '3', '4', '5', '6',                 /* 0x04 - 0x07 */
    '7', '8', '9', '0',                 /* 0x08 - 0x0B */
    '-', '=', ASCII_BS, '\t',           /* 0x0C - 0x0F */
    'q', 'w', 'e', 'r',                 /* 0x10 - 0x13 */
    't', 'y', 'u', 'i',                 /* 0x14 - 0x17 */
    'o', 'p', '[', ']',                 /* 0x18 - 0x1B */
    '\r', KEY_LCTRL, 'a', 's',          /* 0x1C - 0x1F */
    'd', 'f', 'g', 'h',                 /* 0x20 - 0x23 */
    'j', 'k', 'l', ';',                 /* 0x24 - 0x27 */
    '\'', '`', KEY_LSHIFT, '\\',        /* 0x28 - 0x2B */
    'z', 'x', 'c', 'v',                 /* 0x2C - 0x2F */
    'b', 'n', 'm', ',',                 /* 0x30 - 0x33 */
    '.', '/', KEY_RSHIFT, KEY_PRINTSCRN, /* 0x34 - 0x37 */
    KEY_LALT, ' ', KEY_CAPSLOCK, KEY_F1, /* 0x38 - 0x3B */
    KEY_F2, KEY_F3, KEY_F4, KEY_F5,     /* 0x3C - 0x3F */
    KEY_F6, KEY_F7, KEY_F8, KEY_F9,     /* 0x40 - 0x43 */
    KEY_F10, KEY_NUMLOCK, KEY_SCRLOCK, KEY_KPHOME,  /* 0x44 - 0x47 */
    KEY_KPUP, KEY_KPPGUP, KEY_KPMINUS, KEY_KPLEFT,  /* 0x48 - 0x4B */
    KEY_KPCENTER, KEY_KPRIGHT, KEY_KPPLUS, KEY_KPEND,  /* 0x4C - 0x4F */
    KEY_KPDOWN, KEY_KPPGDN, KEY_KPINSERT, KEY_KPDEL,  /* 0x50 - 0x53 */
    KEY_SYSREQ, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,  /* 0x54 - 0x57 */
};

irqreturn_t keyboard(int aux, void * ptr){
	char car;
	outb(0xAD,0x64);
	car=inb(0x60);
	if (!(car&0x80))
		printk("%c",s_scanTableNoShift[car]);
	outb(0xAE,0x64);	
}

void init_keyboard(void){

	keyb.handler = &keyboard;
	keyb.flags = 0;
	keyb.name = "keyboard 0.1";
	keyb.next = NULL;
	request_irq(1,&keyb);
	outb(0xAE,0x64);
}