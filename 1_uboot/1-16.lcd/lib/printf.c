#include "vsprintf.h"
unsigned char outbuf[1024];
unsigned char inbuf[1024];

int printf(const char *fmt, ...)
{
	int i;
	va_list args;
	va_start(args, fmt);
	vsprintf((char *)outbuf, fmt, args);
	va_end();
	
	for(i=0;i < strlen((char *)outbuf);i++)
	{
		putc(outbuf[i]);
	}
	return i;
}

int scanf(const char *fmt, ...)
{
	int i = 0;
	unsigned char ch;
	va_list args;
	while(1)
	{
		ch = getc();
		if((ch==0x0d) || (ch==0x0a))
		{
			putc('\n');
			break;
		}
		else
		{
			inbuf[i++] = ch;
		}
	}
	va_start(args, fmt);
	vsscanf((char *)inbuf, fmt, args);
	va_end();
	return i;
}