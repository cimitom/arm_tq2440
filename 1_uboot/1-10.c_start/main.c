//#define pGPBCON (volatile unsigned long *)0x56000010
//#define pGPBDAT (volatile unsigned long *)0x56000014
#define pGPBCON 0x56000010
#define pGPBDAT 0x56000014

int gboot_main()
{
//	*pGPBCON = 0x1540;
//	*pGPBDAT = 0x75f;

//	void light_led(void)
//	{
		__asm__(
			"ldr r1, =0x15400\n"
			"str r1, [%0]\n"
			"ldr r1, =0x75f\n"
			"str r1, [%1]\n"
			:
			:"r"(pGPBCON), "r"(pGPBDAT)
			:"r1"
		);
//	}
	
	return 0;
}
