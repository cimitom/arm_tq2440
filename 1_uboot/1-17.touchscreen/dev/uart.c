#define ULCON0   (*(volatile unsigned char *)0x50000000)
#define UCON0    (*(volatile unsigned char *)0x50000004)
#define UTRSTAT0 (*(volatile unsigned char *)0x50000010)
#define UTXH0    (*(volatile unsigned char *)0x50000020)
#define URXH0    (*(volatile unsigned char *)0x50000024)
#define UBRDIV0  (*(volatile unsigned long *)0x50000028)
#define GPHCON   (*(volatile unsigned long *)0x56000070)

#define PCLK 50000000
#define BUAD 115200

void uart_init(void)
{
	//配置GPIO口，查表得TXD0=GPH2,RXD0=GPH3
	GPHCON &= ~((0x3<<4)|(0x3<<6));
	GPHCON |= ((0x2<<4)|(0x2<<6));
	
	//配置ULCON0
	ULCON0 = 0x03;
	
	//配置UCON0
	UCON0 = 0x09;
	
	//设置波特率
	UBRDIV0 = (int)(PCLK/(BUAD*16)-1);
}

void putc(unsigned char ch)
{
	while(!(UTRSTAT0 & (1<<2)));
	UTXH0 = ch;
}

unsigned char getc(void)
{
	unsigned char ret;
	while(!(UTRSTAT0 & (1<<0)));
	ret = URXH0;
	if((ret == 0x0d) || (ret == 0x0a))
	{
		putc(0x0d);
		putc(0x0a);
	}
	else
	{
		putc(ret);
	}
	return ret;
}