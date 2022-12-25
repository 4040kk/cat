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
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0xA4;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0 = 1;
	EA=1;}
TR0=Flag;

}