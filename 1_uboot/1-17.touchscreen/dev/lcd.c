#define GPCCON    (*(volatile unsigned long *)0x56000020)
#define GPDCON    (*(volatile unsigned long *)0x56000030)
#define GPGCON    (*(volatile unsigned long *)0x56000060)
#define LCDCON1   (*(volatile unsigned long *)0x4D000000)
#define LCDCON2   (*(volatile unsigned long *)0x4D000004)
#define LCDCON3   (*(volatile unsigned long *)0x4D000008)
#define LCDCON4   (*(volatile unsigned long *)0x4D00000c)
#define LCDCON5   (*(volatile unsigned long *)0x4D000010)
#define LCDSADDR1 (*(volatile unsigned long *)0x4D000014)
#define LCDSADDR2 (*(volatile unsigned long *)0x4D000018)
#define LCDSADDR3 (*(volatile unsigned long *)0x4D00001C)
#define TPAL      (*(volatile unsigned long *)0x4D000050)

#define CLKVAL  4
#define VBPD    1
#define VFPD    1
#define VSPW    9
#define HBPD    1
#define HFPD    1
#define HSPW    40
#define LINEVAL 271
#define HOZVAL  479

#define U32 unsigned int
#define U16 unsigned short
#define U8  unsigned char

extern U8 bmp[107048];

unsigned short LCDBUFFER[272][480];

void lcd_port_init()
{
	GPCCON = 0xaaaaaaaa;
	GPDCON = 0xaaaaaaaa;
}

void lcd_control_init()
{
	LCDCON1	= ((CLKVAL<<8)|(0x3<<5)|(0xc<<1)|(0<<0));
	LCDCON2 = ((VBPD<<24)|(LINEVAL<<14)|(VFPD<<6)|(VSPW<<0));
	LCDCON3 = ((HBPD<<19)|(HOZVAL<<8)  |(HFPD<<0));
	LCDCON4 = (HSPW<<0);
	LCDCON5 = ((0x1<<11)|(1<<9)|(1<<8));
	
	LCDSADDR1 =(((U32)LCDBUFFER>>1)&0x3fffffff);
	LCDSADDR2 =(((U32)LCDBUFFER+272*480*2>>1)&0x1fffff);
	LCDSADDR3 =(480);
	
	TPAL = 0;
}



void lcd_init()
{
	lcd_port_init();
	lcd_control_init();
	
	GPGCON |=(0x3<<8);
	LCDCON1 |= (1<<0);
	LCDCON5 |= (1<<3);
}

void print_point(U32 x, U32 y, U32 color)
{
	U32 red, green, blue;
	red   = ((color>>19)&0x1f);
	green = ((color>>10)&0x3f);
	blue  = ((color>>3)&0x1f);
	LCDBUFFER[y][x] = (unsigned short)((red<<11)|(green<<5)|(blue<<0));
}

void print_line(U32 y, U32 color)
{
	int i;
	for(i=0;i<480;i++)
		print_point(i,y,color);
}

void print_picture(U16 x0, U16 y0, U16 wide, U16 high, const U8 *bmp)
{
	U16 x, y, c;
	U32 p = 0;
	for(y = y0; y < y0+high; y++)
	{
		for (x = x0; x < x0+wide; x++)
		{
			c = (bmp[p] | (bmp[p+1]<<8));
			if((x<480)&&(y<272))
				LCDBUFFER[y][x] = c;
			p = p + 2;
		}
	}
}



void clearSrc(U32 color)
{
	TPAL = (1<<24)|(color&0xffffff);	
}

void lcd_test()
{
	print_line(10, 0xff0000);
	
	print_picture(0,0,240,223,bmp);
	
//	clearSrc(0xff0000);
}
