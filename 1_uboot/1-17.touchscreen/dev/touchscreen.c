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

//1,电阻屏初始化函数
void touchscreen_init()
{
	//1.1设置ADC时钟
	rADCCON |= (1<<14);
	rADCCON &= ~(0xff<<6);
	rADCCON |= (49<<6);
	rADCCON &= ~(1<<2);
	/*    rADCCON = (1<<14) | (49<<6);*/
	
	//1.2设置中断屏蔽位
	rINTMSK    &= ~(1<<31);
	rINTSUBMSK &= ~(1<<9);
	
	//1.3进入等待终端模式（按下）
	rADCTSC = 0xd3;
}



//2，TC中断处理函数
void tc_handler()
{

	//2.1启动XY坐标自动转换
	rADCCON |= (1<<0);
	rADCTSC |= (1<<2);
	
	//2.2等待完成转换，获取XY坐标
	while(!(rADCCON & (1<<15)));
	
	xdata = (rADCDAT0 & 0x3ff);
	ydata = (rADCDAT1 & 0x3ff);
	
	//2.3清除中断
	rSRCPND    |= (1<<31);
	rINTPND    |= (1<<31);
	rSUBSRCPND |= (1<<9);
	
	//2.4等待弹起中断
	rADCTSC = 0xd3;
	rADCTSC |= (1<<8);
	while(!(rSUBSRCPND & (1<<9)));
	
	//2.5清除中断
	rSRCPND    |= (1<<31);
	rINTPND    |= (1<<31);
	rSUBSRCPND |= (1<<9);
	
	//2.6打印X、Y坐标
	printf("\nX is %d, Y is %d. \n\r",xdata,ydata);
	
	//2.7进入等待中断模式
	rADCTSC = 0xd3;
}