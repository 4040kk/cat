#include <STC15F2K60S2.H>
#include"UR0_com.h"
void UartInit0(void)		//4800bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xBF;		//定时器时钟12T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xA0;		//设置定时初始值
	TH1 = 0xFF;		//设置定时初始值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
	EA=1;
	ES=1;
}
void SendChar0(unsigned char Char)
{	
	SBUF=Char;
	while(!TI);
	TI=0;
}
 
void  SendString0(unsigned char *p)
{
	while(*p)
	{
		SendChar0(*p);
		p++;
	}
	SendChar0(0x0D);
	SendChar0(0x0A);
}

void UR0_com__Rountine() interrupt 4
{
		RI=0;
}
