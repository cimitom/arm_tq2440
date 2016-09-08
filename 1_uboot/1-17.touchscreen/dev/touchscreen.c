#define rSRCPND    (*(volatile unsigned long *)0x4A000000)
#define rINTMSK    (*(volatile unsigned long *)0x4A000008)
#define rINTPND    (*(volatile unsigned long *)0x4A000010)
#define rSUBSRCPND (*(volatile unsigned long *)0x4A000018)
#define rINTSUBMSK (*(volatile unsigned long *)0x4A00001C)
#define rADCCON    (*(volatile unsigned long *)0x58000000)
#define rADCTSC    (*(volatile unsigned long *)0x58000004)
#define rADCDAT0   (*(volatile unsigned long *)0x5800000C)
#define rADCDAT1   (*(volatile unsigned long *)0x58000010)

int xdata, ydata;
xdata = 0;
ydata = 0;

//1,��������ʼ������
void touchscreen_init()
{
	//1.1����ADCʱ��
	rADCCON |= (1<<14);
	rADCCON &= ~(0xff<<6);
	rADCCON |= (49<<6);
	rADCCON &= ~(1<<2);
	/*    rADCCON = (1<<14) | (49<<6);*/
	
	//1.2�����ж�����λ
	rINTMSK    &= ~(1<<31);
	rINTSUBMSK &= ~(1<<9);
	
	//1.3����ȴ��ն�ģʽ�����£�
	rADCTSC = 0xd3;
}



//2��TC�жϴ�����
void tc_handler()
{

	//2.1����XY�����Զ�ת��
	rADCCON |= (1<<0);
	rADCTSC |= (1<<2);
	
	//2.2�ȴ����ת������ȡXY����
	while(!(rADCCON & (1<<15)));
	
	xdata = (rADCDAT0 & 0x3ff);
	ydata = (rADCDAT1 & 0x3ff);
	
	//2.3����ж�
	rSRCPND    |= (1<<31);
	rINTPND    |= (1<<31);
	rSUBSRCPND |= (1<<9);
	
	//2.4�ȴ������ж�
	rADCTSC = 0xd3;
	rADCTSC |= (1<<8);
	while(!(rSUBSRCPND & (1<<9)));
	
	//2.5����ж�
	rSRCPND    |= (1<<31);
	rINTPND    |= (1<<31);
	rSUBSRCPND |= (1<<9);
	
	//2.6��ӡX��Y����
	printf("\nX is %d, Y is %d. \n\r",xdata,ydata);
	
	//2.7����ȴ��ж�ģʽ
	rADCTSC = 0xd3;
}