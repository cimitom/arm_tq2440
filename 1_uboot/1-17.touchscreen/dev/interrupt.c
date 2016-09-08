#define EINTMASK  (volatile unsigned long *)0x560000a4
#define EINTPEND  (volatile unsigned long *)0x560000a8

#define SRCPND    (volatile unsigned long *)0x4a000000
#define INTMOD    (volatile unsigned long *)0x4a000004
#define INTMSK    (volatile unsigned long *)0x4a000008
#define INTPND    (volatile unsigned long *)0x4a000010
#define INTOFFSET (volatile unsigned long *)0x4a000014


#define EINT4_noMSK (1 << 4)

#define INT0_noMSK (1 << 0)
#define INT1_noMSK (1 << 1)
#define INT2_noMSK (1 << 2)
#define INT4_noMSK (1 << 4)

void irq_init()
{
	*(EINTMASK) &= ~EINT4_noMSK;
	*(INTMSK)   &= ~(INT0_noMSK | INT1_noMSK | INT2_noMSK | INT4_noMSK);
	
	__asm__(
	"mrs r0, cpsr\n"
	"bic r0, r0, #0x80\n"
	"msr cpsr, r0\n"
	:
	:
	);
}

void handle_int()
{
	unsigned long value = *(INTOFFSET);
	switch (value)
	{
		case 0:
			led_on();
			break;
		
		case 1:
			led_off();
			break;
		
		case 2:
			led_on();
			break;
		
		case 4:
			led_off();
			break;
		case 31:
			tc_handler();
			break;
			
		default:
			break;
	}
	
	if(4 == value)
		*(EINTPEND) |= (1 << 4);
	*(SRCPND) |= (1 << value);
	*(INTPND) |= (1 << value);
	
}