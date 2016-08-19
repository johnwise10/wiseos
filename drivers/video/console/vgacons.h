#include<wiseos/types.h>

#define SCREEN_START 0x000B8000
#define SCREEN_END   0x000C0000
#define LINES 25
#define COLUMNS 80
#define NPAR 16

#define SCROLL_UP 	1
#define SCROLL_DOWN	2

typedef struct vgacons{
	u32 origin;
	u32 scr_end;
	u32 pos;
	u32 pos_x;
	u32 pos_y;
	u32 top;
	u32 bottom;
	u32 lines;
	u32 columns;
	u32 state;
	u32 npar;
	u32 par[NPAR];
	u32 ques;
	u8  attr;
} vgacons;
