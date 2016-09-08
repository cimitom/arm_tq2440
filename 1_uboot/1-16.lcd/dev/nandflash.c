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
	//ѡ��nandflash
	select_chip();
	
	//���RnB
	clear_RnB();
	
	//����ָ��0xff
	send_cmd(0xff);

	//�ȴ�RnB
	wait_RnB();
	
	//ȡ��ѡ��nandflash
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
	//ѡ��nandflash
	select_chip();
	
	//���RnB
	clear_RnB();
	
	//����ָ��0x60
	send_cmd(0x60);
	
	//���������е�ַ
	send_addr(addr&0xff);
	send_addr((addr>>8)&0xff);
	send_addr((addr>>16)&0xff);
		
	//����ָ��0xd0
	send_cmd(0xd0);
	
	//�ȴ�RnB
	wait_RnB();
	
	//����ָ��0x70
	send_cmd(0x70);
	
	//���ս��
	ret = NFDATA;
	
	//ȡ��ѡ��nandflash
	deselect_chip();
	
	return ret;
}
void NF_ReadPage(unsigned long addr, unsigned char* buff)
{
	int i;
	//ѡ��nandflash
	select_chip();
	
	//���RnB
	clear_RnB();
	
	//����ָ��0x00
	send_cmd(0x00);
	
	//���������е�ַ
	send_addr(0x00);
	send_addr(0x00);
	
	//���������е�ַ
	send_addr(addr&0xff);
	send_addr((addr>>8)&0xff);
	send_addr((addr>>16)&0xff);
	
	//����ָ��0x30
	send_cmd(0x30);
	
	//�ȴ�RnB
	wait_RnB();

	//�����ݵ�ָ����ַ
	for(i = 0;i < 2048; i++)
	{
		buff[i] = NFDATA;
	}
	
	//ȡ��ѡ��nandflash
	deselect_chip();
}

void NandFlash_to_SDRAM(unsigned long nand_addr, unsigned char* sdram_addr, int size)
{//sizeԭ������Ϊunsigned size����Ȼ�����ܹ��������غ���޷����
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
	//ѡ��nandflash
	select_chip();
	
	//���RnB
	clear_RnB();
	
	//����ָ��0x80
	send_cmd(0x80);
	
	//���������е�ַ
	send_addr(0x00);
	send_addr(0x00);
	
	//���������е�ַ
	send_addr(addr&0xff);
	send_addr((addr>>8)&0xff);
	send_addr((addr>>16)&0xff);
	
	//д���ݵ�ָ����ַ
	for(i = 0;i < 2048; i++)
	{
		NFDATA = buff[i];
	}
	
	//����ָ��0x10
	send_cmd(0x10);
	
	//�ȴ�RnB
	wait_RnB();
		
	//����ָ��0x70
	send_cmd(0x70);
	
	//���ս��
	ret = NFDATA;
	
	//ȡ��ѡ��nandflash
	deselect_chip();
	
	return ret;
}