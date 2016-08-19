#include<wiseos/console.h>
#include<wiseos/kernel.h>
#include<asm/io.h>
#include<asm/system.h>
#include "vgacons.h"

static const char *vgacon_startup(void);
static void vgacons_init(int mode);

static vgacons crtl_cons={
	SCREEN_START, 			// Origin
	SCREEN_START+LINES*COLUMNS*2,   // scr_end 
	SCREEN_START,			// pos
	0,				// pos_x
	0,				// pos_y
	0,				// top
	LINES,				// bottom
	LINES,				// lines
	COLUMNS,			// Columns
	0,				// state
	0,				// NPAR
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // PAR
	0,				// ques
	0x07,				// attr
};


static void vgacons_gotoxy(unsigned int new_x,unsigned int new_y)
{
	if (new_x>=crtl_cons.columns || new_y>=crtl_cons.lines)
		return;
	crtl_cons.pos_x=new_x;
	crtl_cons.pos_y=new_y;
	crtl_cons.pos=crtl_cons.origin+((crtl_cons.pos_y*crtl_cons.columns \
					+crtl_cons.pos_x)<<1);
}
static void vgacons_origin(void)
{
	cli();
	outb_p(12,0x3d4);
	outb_p(0xff&((crtl_cons.origin-SCREEN_START)>>9),0x3d5);
	outb_p(13,0x3d4);
	outb_p(0xff&((crtl_cons.origin-SCREEN_START)>>1),0x3d5);
	sti();
}	

static void vgacons_scroll(u32 dir){
  int i,n;
  u16 *video;
  n= ((crtl_cons.lines -1) * crtl_cons.columns);
  switch(dir){
    case SCROLL_UP:
      /* Move lines 1..NUMROWS-1 up one position. */
      for (video = (u16*)crtl_cons.origin, i = 0; i < n; ++i) {
       *video = *(video + crtl_cons.columns);
	++video;
      }

      /* Limpiamos la ultima linea. */
      for (video = (u16*)crtl_cons.origin + n, i = 0; i < crtl_cons.columns; ++i)
        *video++ = 0;
    break;
    case SCROLL_DOWN:
      for(video=(u16*)crtl_cons.origin + n +1,i=0; i<n;++i){
        *video = *(video - crtl_cons.columns);
	--video;
      }
     /* Limpiamos la primera linea */
     for (video = (u16*)crtl_cons.origin, i = 0; i < crtl_cons.columns; ++i)
       *video++ = 0;
     break;	
  };

}

static void vgacons_putc (int c)
{
  u16 *video;
  if (c == '\n' || c == '\r')
    {
    newline:
      crtl_cons.pos_x = 0;
      crtl_cons.pos_y++;
      if (crtl_cons.pos_y >= crtl_cons.lines){
        crtl_cons.pos_y--;
	vgacons_scroll(SCROLL_UP);
      }
        return;
    }
  
   video = crtl_cons.origin + ((crtl_cons.pos_x + crtl_cons.pos_y*crtl_cons.columns)*2);
  *video = ((crtl_cons.attr<<8)| c&0xFF);
  
  crtl_cons.pos_x++;

  if (crtl_cons.pos_x >= crtl_cons.columns)
    goto newline; 
  }

static void vgacons_clear (void)
{
  int i;
  u16 *video;
  video = (u16*)crtl_cons.origin;
  
  for (i = 0; i < crtl_cons.columns * crtl_cons.lines; i++)
    *(video + i) = 0;

  crtl_cons.pos_x = 0;
  crtl_cons.pos_y = 0;
}

static int vgacons_startup(void){
	return 1;
}


const struct consw vga_con = {
//	.owner =		THIS_MODULE,
	.con_startup =		vgacons_startup,
	.con_init    = 		vgacons_init,
	.con_putc    = 		vgacons_putc,
	.con_clear   = 		vgacons_clear,
	.con_scroll  = 		vgacons_scroll,
	.con_origin  = 		vgacons_origin,
	.con_gotoxy  = 		vgacons_gotoxy,
};



static void vgacons_init(int mode){
  int i,j;
  vgacons_clear();
  printk("Iniciando Consola...\n");
  printk("Hola a todos\n");

 
 /*for(i=0;i<25;i++){
   for(j=0;j<2000000;j++);
   printk("%d\n",i);
   }*/
   
}
