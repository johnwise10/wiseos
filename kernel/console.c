#include<wiseos/console.h>
#include<wiseos/kernel.h>

console_t console;

extern const struct consw vga_con;

struct consw * cons_driver[NUM_VIDEO_DRIVERS]={
		{&vga_con},
	};

void console_init(void){
  int i=0;
  for(i=0;cons_driver[i]->con_startup()==0;i++);
  
  console.con_driver=cons_driver[i];
  console.con_driver->con_init(1);
  
}
