/*  
 * En modo-kernel no podemos usar printf. Para hacer un printf se debe
 * usar el fs.
 */
#include <stdarg.h>
#include <stddef.h>

#include <wiseos/kernel.h>
#include <wiseos/console.h>

extern console_t console;

static char buf[1024];

int printk(const char *fmt, ...)
{
	va_list args;
	int i;
	
	va_start(args, fmt);
	i=vsprintf(buf,fmt,args);
	va_end(args);

	for(i=0;buf[i]!=0;i++)
	 console.con_driver->con_putc((int)buf[i]);
	
	return i;
}
