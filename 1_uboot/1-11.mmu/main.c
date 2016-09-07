#define pGPBCON (volatile unsigned long *)0xA0000010
#define pGPBDAT (volatile unsigned long *)0xA0000014

#define MMU_FULL_ACCESS (3 << 10)
#define MMU_DOMAIN  	(0 << 5)
#define MMU_CACHEABLE 	(1 << 3)
#define MMU_BUFFERABLE 	(1 << 2)
#define MMU_SPECIAL 	(1 << 4)
#define MMU_SECTION 	(2 << 0)
#define MMU_SECDESC (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | MMU_SECTION)
#define MMU_SECDESC_WB (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | MMU_SECTION|MMU_CACHEABLE | MMU_BUFFERABLE)

void create_page_table()
{
	unsigned long *ttb = (unsigned long *)0x30000000;
	unsigned long vaddr, paddr;
	
	vaddr = 0xA0000000;
	paddr = 0x56000000;
	*(ttb + (vaddr >> 20)) = (paddr & 0xFFF00000) | MMU_SECDESC;
	
	vaddr = 0x30000000;
	paddr = 0x30000000;
	while (vaddr < 0x34000000)
	{
		*(ttb + (vaddr >> 20)) = (paddr & 0xFFF00000) | MMU_SECDESC_WB;
		vaddr = vaddr + 0x100000;
		paddr = paddr + 0x100000;
	}
}

void mmu_init()
{
	__asm__(
	
	"ldr	r0, =0x30000000\n"
	"mcr	p15, 0, r0, c2, c0, 0\n"
	"mvn	r0, #0x0\n"
	"mcr	p15, 0, r0, c3, c0, 0\n"
	"mrc	p15, 0, r0, c1, c0, 0\n"
	"orr	r0, r0, #0x0001\n"
	"mcr	p15, 0, r0, c1, c0, 0\n"
	:
	:
	);
}

int gboot_main()
{
	create_page_table();
	
	mmu_init();
	
	*pGPBCON = 0x1540;
	*pGPBDAT = 0x75f;
	
	return 0;
}
