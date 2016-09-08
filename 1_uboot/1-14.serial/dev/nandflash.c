#define NFCONF (*(volatile unsigned long*)0x4E000000)
#define NFCONT (*(volatile unsigned long*)0x4E000004)
#define NFCMMD (*(volatile unsigned char*)0x4E000008)
#define NFADDR (*(volatile unsigned char*)0x4E00000C)
#define NFDATA (*(volatile unsigned char*)0x4E000010)
#define NFSTAT (*(volatile unsigned char*)0x4E000020)

#define TACLS               (1<<12)
#define TWRPH0              (2<<8)
#define TWRPH1              (1<<4)
#define NAND_ENABLE         (1<<0)
#define NAND_SELECT_DISABLE (1<<1)

void select_chip()
{
	NFCONT &= ~(1<<1);
}

void deselect_chip()
{
	NFCONT |= (1<<1);
}

void clear_RnB()
{
	NFSTAT |= (1<<2);
}

void send_cmd(unsigned cmd)
{
	NFCMMD = cmd;
}

void send_addr(unsigned addr)
{
	NFADDR = addr;
}

void wait_RnB()
{
	while(!(NFSTAT&(1<<2)));
}

void nand_rest()
{
	//选中nandflash
	select_chip();
	
	//清楚RnB
	clear_RnB();
	
	//发送指令0xff
	send_cmd(0xff);

	//等待RnB
	wait_RnB();
	
	//取消选中nandflash
	deselect_chip();
}

void nand_init()
{
	NFCONF |= (TACLS | TWRPH0 | TWRPH1);
	NFCONT |= (NAND_ENABLE | NAND_SELECT_DISABLE);
	nand_rest();
}

int NF_Erase(unsigned long addr)
{
	int ret;
	//选中nandflash
	select_chip();
	
	//清楚RnB
	clear_RnB();
	
	//发送指令0x60
	send_cmd(0x60);
	
	//发送三个行地址
	send_addr(addr&0xff);
	send_addr((addr>>8)&0xff);
	send_addr((addr>>16)&0xff);
		
	//发送指令0xd0
	send_cmd(0xd0);
	
	//等待RnB
	wait_RnB();
	
	//发送指令0x70
	send_cmd(0x70);
	
	//接收结果
	ret = NFDATA;
	
	//取消选中nandflash
	deselect_chip();
	
	return ret;
}
void NF_ReadPage(unsigned long addr, unsigned char* buff)
{
	int i;
	//选中nandflash
	select_chip();
	
	//清楚RnB
	clear_RnB();
	
	//发送指令0x00
	send_cmd(0x00);
	
	//发送两个列地址
	send_addr(0x00);
	send_addr(0x00);
	
	//发送三个行地址
	send_addr(addr&0xff);
	send_addr((addr>>8)&0xff);
	send_addr((addr>>16)&0xff);
	
	//发送指令0x30
	send_cmd(0x30);
	
	//等待RnB
	wait_RnB();

	//读数据到指定地址
	for(i = 0;i < 2048; i++)
	{
		buff[i] = NFDATA;
	}
	
	//取消选中nandflash
	deselect_chip();
}

void NandFlash_to_SDRAM(unsigned long nand_addr, unsigned char* sdram_addr, int size)
{//size原来定义为unsigned size，虽然编译能过，但下载后就无法点灯
	int i;
	for(i = (nand_addr>>11); size >0;)
	{
		NF_ReadPage(i,sdram_addr);
		sdram_addr += 2048;
		size -= 2048;
		i++;
	}
}

int NF_WritePage(unsigned long addr, unsigned char* buff)
{
	int i, ret;
	//选中nandflash
	select_chip();
	
	//清楚RnB
	clear_RnB();
	
	//发送指令0x80
	send_cmd(0x80);
	
	//发送两个列地址
	send_addr(0x00);
	send_addr(0x00);
	
	//发送三个行地址
	send_addr(addr&0xff);
	send_addr((addr>>8)&0xff);
	send_addr((addr>>16)&0xff);
	
	//写数据到指定地址
	for(i = 0;i < 2048; i++)
	{
		NFDATA = buff[i];
	}
	
	//发送指令0x10
	send_cmd(0x10);
	
	//等待RnB
	wait_RnB();
		
	//发送指令0x70
	send_cmd(0x70);
	
	//接收结果
	ret = NFDATA;
	
	//取消选中nandflash
	deselect_chip();
	
	return ret;
}
