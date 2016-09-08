#define pGPBCON (volatile unsigned long *)0x56000010
#define pGPBDAT (volatile unsigned long *)0x56000014

#define GPB5_OUT (0x01 << (5*2))
#define GPB6_OUT (0x01 << (6*2))
#define GPB7_OUT (0x01 << (7*2))
#define GPB8_OUT (0x01 << (8*2))

void led_init()
{
	*pGPBCON |= (GPB5_OUT | GPB6_OUT | GPB7_OUT | GPB8_OUT);
	*pGPBDAT = 0x7ff;
}

void led_on()
{
//	*pGPBDAT = 0x75f;
	*pGPBDAT = 0x6bf;
}

void led_off()
{
	*pGPBDAT = 0x7ff;
}