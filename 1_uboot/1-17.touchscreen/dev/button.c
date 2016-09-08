#define GPFCON (volatile unsigned long *)0x56000050

#define GPF0_MSK (0x3 << (0 * 2))
#define GPF1_MSK (0x3 << (1 * 2))
#define GPF2_MSK (0x3 << (2 * 2))
#define GPF4_MSK (0x3 << (4 * 2))

#define GPF0_INT (0x2 << (0 * 2))
#define GPF1_INT (0x2 << (1 * 2))
#define GPF2_INT (0x2 << (2 * 2))
#define GPF4_INT (0x2 << (4 * 2))

void button_init()
{
	*(GPFCON) &= ~(GPF0_MSK | GPF1_MSK | GPF2_MSK | GPF4_MSK);
	*(GPFCON) |=  (GPF0_INT | GPF1_INT | GPF2_INT | GPF4_INT);
}