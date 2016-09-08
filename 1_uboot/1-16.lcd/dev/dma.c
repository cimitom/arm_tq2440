char *buf = "Hello Fucku!";

#define DISRC0     (*(volatile unsigned long *)0x4B000000)
#define DISRCC0    (*(volatile unsigned long *)0x4B000004)
#define DIDST0     (*(volatile unsigned long *)0x4B000008)
#define DIDSTC0    (*(volatile unsigned long *)0x4B00000C)
#define DCON0      (*(volatile unsigned long *)0x4B000010)
#define DMASKTRIG0 (*(volatile unsigned long *)0x4B000020)

#define UTXH0      (volatile unsigned long *)0x50000020

void dma_init(void)
{
	DISRC0 = (unsigned int)buf;
	DISRCC0 &= ~((1<<0)|(1<<1));
	
	DIDST0 = UTXH0;
	DIDSTC0 |= ((1<<0)|(1<<1));
	
	DCON0 |= ((1<<24)|(1<<23)|(1<<22)|(12<<0)); 
}

void dma_start(void)
{
	DMASKTRIG0 |= (1<<1);
}