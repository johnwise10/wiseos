#ifndef _WISEOS_CONSOLE_H
#define _WISEOS_CONSOLE_H 1
#include <wiseos/types.h>

#define  NUM_VIDEO_DRIVERS 10

struct consw {
//	struct module *owner;
	int	(*con_startup)(void);
	void	(*con_init)(int);
	void	(*con_putc)(int);
	void 	(*con_clear)(void);
	void    (*con_scroll)(int);
	void 	(*con_origin)(void);
	void 	(*con_gotoxy)(unsigned int,unsigned int);
};


typedef struct console_t{
	char name[16];
	struct consw *con_driver;
}console_t;
#endif
