#include <STC15F2K60S2.H>
#include "UR_com.h"
#include "UR0_com.h"
#include "header.h"
#include "CSB.h"
#include "ADC.h"
sbit FDZ=P2^2;
sbit FDY=P2^3;
sbit FDC_1=P2^5;
sbit FDC_2=P2^6;
sbit FDC_3=P2^7;
sbit FDC_4=P4^5;
sbit DJ=P5^5;
sbit beep=P4^6;

sbit SJ1=P4^3;
sbit SJ2=P4^4;
sbit SJ3=P2^0;

sbit SW4=P1^3;
u8 t=0;
u8 v1,v2;
int T0=0;
void Timer0Init(void)		//100微秒@11.0592MHz
{
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;
	EA=1;
	ES=1;
}
void Timer0_Isr() interrupt 1
{
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	if(t<v1){FDZ=1;}else{FDZ=0;}
	if(t<v2){FDY=1;}else{FDY=0;}
	t++;
	t%=110;
	T0++;
	T0%=15000;

}
u8 stations;
int j=100;
u8 gw,sw,bw;
int csb=100;
u8 csb_cs=0;
int main(){
	
	//UartInit0();
	Timer0Init();
	//SendString0("OKKKKKKKKKK");
	v1=0;v2=0;
	FDC_1=1;FDC_2=0;FDC_3=1;FDC_4=0;
	gw=0;sw=0;bw=0;
	stations=0;
while(1){ 
		
 if(stations==0){
	   if(P07==0){
			 UartInit();
			 dlay(2000);
			SendString("AT+CIPMUX=1");
			 dlay(1000);
			SendString("AT+CIPSERVER=1,8080");
		 }
		 if(SW4==0){
			 dlay(2000);
			 while(SW4==0);
			 beep=0;
			 dlay(1000);
			 beep=1;
			 while(1){
			 findload();
				 if(SW4==0){
					  beep=0;
						dlay(1000);
						beep=1;
						break;
				 }
			 }
		 }
		 /////////////////////////////////////////////////		
			if(T0%300==0){			
				//j=CSB_Getnum();
				//j=ADC_GetNum()*0.196;
				j=UR_Getnum();
				gw=j%10;
				sw=(j / 10) % 10;
				bw=j/100;
				if(sw==1){FDC_1=0;FDC_2=1;FDC_3=0;FDC_4=1;}else{FDC_1=1;FDC_2=0;FDC_3=1;FDC_4=0;}
			}		
		 ///////////////////////////////////////////////////					
//			 if(T0%4000==0){
//				 SendString0("num=");	
//				SendChar0(bw+48);
//				SendChar0(sw+48);
//				SendChar0(gw+48); 		 
//				SendChar0(0x0D);SendChar0(0x0A);}
		 ////////////////////////////////////////////////// 
			if(T0%1000==0){	
				csb=CSB_Getnum();
				//j=CSB_Getnum();
				CSB_Onece();
				if(csb<40&csb_cs==0){	csb_cs++;}else csb_cs==0;
				if(csb<40&csb_cs==1){	csb_cs++;}else csb_cs==0;
				if(csb<40&csb_cs==2){	csb_cs++;}else csb_cs==0;
				if(csb_cs==3&csb<40){
				csb_cs=0;
				FDC_1=0;FDC_2=1;FDC_3=0;FDC_4=1;		
				stations=1;}
				else {csb_cs==0;}
			}
			
		/////////////////////////////////////////////////////////		
			if(gw==0){v1=0;v2=v1;}
			if(gw!=0&&gw<=3){v1=20;v2=v1;}
			switch(gw){
				case 4: v1=40;v2=v1; break;
				case 5: v1=60;v2=v1; break;
				case 6: v1=100;v2=v1; break;
				default:;
			}
			switch(bw){
				case 3: 	stations=2;	break;
				case 1:  if(gw<=4){v1=50; v2=25;}else{FDC_1=1;FDC_2=0;FDC_3=0;FDC_4=1;v1=60; v2=60;}break;
				case 2: 	if(gw<=4){v2=50; v1=25;}else{FDC_1=0;FDC_2=1;FDC_3=1;FDC_4=0;	v2=60; v1=60;}break;
				default: v1=v2; 
			}
			
			
															}
 
		if(stations==1){  
				v1=30;v2=30;
				beep=0;
				if(T0%300==0){
					CSB_Onece();
					csb=CSB_Getnum();
				}				
				if(csb>60&csb_cs==0){	csb_cs++;}else csb_cs==0;
				if(csb_cs==1&csb>60){csb_cs++;}else csb_cs==0;
				if(csb_cs==2&csb>60){csb_cs=0;FDC_1=1;FDC_2=0;FDC_3=1;FDC_4=0;stations=0;beep=1;}else csb_cs==0;
		}
		
		if(stations==2){
			
				if(T0%1000==0){
						j=UR_Getnum();
						bw=j/100;
						if(bw==0){stations=0;}
				}
			 findload();
		}
		
		
			
		}
}
		void findload(){
		
					FDC_1=1;FDC_2=0;FDC_3=1;FDC_4=0;
			if(SJ2==1){
			v1=37;v2=37;
			if(SJ2==1&&SJ3==1){return;}	
			if(SJ1==1){dlay(500);	while(SJ2==0){FDC_1=0;FDC_2=1;FDC_3=1;FDC_4=0;v2=37; v1=37;}	v1=0;v2=0;dlay(500);	}	
			if(SJ3==1){dlay(500);	while(SJ2==0){FDC_1=1;FDC_2=0;FDC_3=0;FDC_4=1;v1=37; v2=37;}	v1=0;v2=0;dlay(500);	}	
			//SendString0("1");
			}else{
			v1=37;v2=37;
			if(SJ1==1){dlay(100);	while(SJ2==0){FDC_1=0;FDC_2=1;FDC_3=1;FDC_4=0;v2=28; v1=38;}	v1=0;v2=0;dlay(100);	}	
			if(SJ3==1){dlay(100);	while(SJ2==0){FDC_1=1;FDC_2=0;FDC_3=0;FDC_4=1;v1=28; v2=38;}	v1=0;v2=0;dlay(100);	}	
			}
		}