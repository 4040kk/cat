#include <STC89C5xRC.H>
void Timer0Init(void)		//1??@12.000MHz
{
	TMOD &= 0xF0;		//???????
	TMOD |= 0x01;		//???????
	TL0 = 0;		//???????
	TH0 = 0;		//???????
	TF0 = 0;		//??TF0??
	TR0 = 0;		//???0????
	ET0=0;
}

void Timer0_SetCounter(unsigned int value)
{
	TH0=value/256;
	TL0=value%256;
}

 int Timer0_GetCounter(){
			return ((TH0<<8)|TL0);
}

void Timer0_Run(unsigned char Flag){
if(Flag==0){
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;
	EA=1;}
TR0=Flag;

}