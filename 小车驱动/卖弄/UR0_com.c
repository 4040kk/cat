#include <STC89C5xRC.H>
#include "header.h"

void UR_com_sendByte(u8 Byte){
	
	SBUF=Byte;
	while(TI==0){}
	TI=0;
}
 u8 UR_com_GetByte(){
	
		while(RI==0){}
		RI=0;
		return SBUF;
}
void UartInit(void)		//4800bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFA;		//设置定时初始值
	TH1 = 0xFA;		//设置定时重载值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
	EA=1;
	ES=1;
}
void SendChar(unsigned char Char)
{	
	SBUF=Char;
	while(!TI);
	TI=0;
}
 
void  SendString(unsigned char *p)
{
	while(*p)
	{
		SendChar(*p);
		p++;
	}
	SendChar(0x0D);
	SendChar(0x0A);
}

unsigned char sr;
	u8 UR_count=0;
	u8 UR_BUF[5]={11,11,11,11,11};
	u8 i;
	bit UR_OA=0; 
  u8 UR_DAT[5]={11,11,11,11,11};
	u8 UR_flag=0;
void UR_com__Rountine() interrupt 4
{
		if(RI)               //判断串口接收标志位
		{
			if(UR_flag==0){	
					for(i=0;i<5;i++){
					UR_DAT[i]=11;
					}
			}
				
			sr=SBUF;
			if(sr==10&&UR_OA){
			for(i=0;i<UR_count;i++){
					UR_DAT[i]=UR_BUF[i];
			}
			UR_OA=0;
			UR_flag=1;
			UR_count=0;
			}
			if(UR_OA){
			UR_BUF[UR_count++]=sr;
			}
			if(sr==58){UR_OA=1;}
		}
		RI=0;
}

int UR_Getnum(){
	static	int num=0;

	if(UR_flag){
		
		num=0;
	for(i=0;i<4;i++){
		if(UR_DAT[i]!=11&&UR_DAT[i]!=13){
			num=num*10+(UR_DAT[i]-48);	
		}else{UR_flag=0;

			for(i=0;i<5;i++){
					UR_DAT[i]=11;
					}

		return num;}	
		
	}
	//UR_flag=0;
	}
	return num;
}