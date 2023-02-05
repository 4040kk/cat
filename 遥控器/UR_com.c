#include <STC15F2K60S2.H>
#include "UR_com.h"
 u8 UR_com_GetByte(){
		while(!(S2CON&0x01)){};
	 
		return S2BUF;
}
void UartInit(void)		//4800bps@1MHz
{

	S2CON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xFB;		//定时器时钟12T模式
	T2L = 0xE8;		//设置定时初始值
	T2H = 0xFF;		//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时
	EA=1;
	IE2&=0xFE;
	IE2|=	0X01;
	ES=1;
}
void SendChar(unsigned char Char)
{	
		S2BUF=Char;
		while(!(S2CON&0x02)){};
		S2CON&=0xFD;
}
 
void  SendString(unsigned char *p)
{
	while(*p)
	{
		SendChar(*p);
		
	//dlay(10);
		p++;
	}
	SendChar(0x0D);
	//dlay(10);
	SendChar(0x0A);
}

unsigned char sr;
	u8 UR_BUF[10];
	u8 i;
	u8 UR_OA=0; 
   UR_DAT[10]={0};
	u8 UR_flag=0;
void UR_com__Rountine() interrupt 8 using 2
{
		if(S2CON&0X01)               //判断串口接收标志位
		{
				S2CON&=0xFE;			
				sr=S2BUF;			
			//接收冒号以后的数据
			if(UR_OA==2){//结束
			for(i=0;i<UR_OA;i++){
					UR_DAT[i]=UR_BUF[i];
			}
			UR_OA=0;
			UR_flag=1;
			}
			
			if(sr==75&&UR_OA==1){UR_BUF[UR_OA]=sr;UR_OA=2;}	
			if(sr==79){UR_BUF[UR_OA]=sr;UR_OA=1;}			
		}
	
		
}

bit GetWIFI(){
	if(UR_flag){
		
	return 1;
	UR_flag=0;
	}
	return 0;
}