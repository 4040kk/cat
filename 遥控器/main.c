#include <STC15F2K60S2.H>
#include <math.h>
#include "drive.h"
#include "UR0_com.h"
#include "oled.h"
#include "bmp.h"
#include "ADC.h"
#include "UR_com.h"
sbit SW2=P0^0;
sbit SW3=P0^1;
sbit beep=P4^7;
void draw_wait(u8 x);
void init();
void Timer0Init(void)		//100us@22.1184MHz
{
	AUXR &= 0x7F;		//?????12T??
	TMOD &= 0xF0;		//???????
	TL0 = 0x44;		//???????
	TH0 = 0xFF;		//???????
	TF0 = 0;		//??TF0??
	TR0 = 1;		//???0????	
	EA=1;
	ES=1;
	ET0=1;
	PT0=1;
}
u8 RY,RX,LY,LX;
int T=0;
bit sw=1;
void Time0_R() interrupt 1
{			TL0 = 0x44;		//???????
			TH0 = 0xFF;		//???????
			T++;
			if(T%1000==0){
			RX=	(ADC_GetNum(PRX)*0.016);
			RY=7-(ADC_GetNum(PRY)*0.024);
			LX=(ADC_GetNum(PLX)*0.016);
			}
			if(RX==2){sw=1;}
			T%=10000;
			
}

char meg[4]="0000";
bit one=0;
int js=2;
u8 dw=0;
u8 stations =0;
char cj=0;
char yd=0;
u8 angle=0;
bit connect=0;
int main(){
	beep=0;
	delay(100);
	beep=1;
	init();
	while(1){

		if(stations==0){
			one=1; 
			if(js>6||js<2){js=2;}
			if(T%10==0){
				OLED_DrawBMP(0, 0,20, 1,BMP3);
			if(connect){OLED_DrawBMP(118, 0,127, 1,BMP6);SendString("AT+CIPSTART=\"TCP\",\"192.168.4.1\",8080");}
			OLED_DrawBMP(0, 1,128, 8,BMP1);
			OLED_DrawBMP(110, js,128, js+2,BMP2);	
			}
				
			if(js==4&&RX==4){OLED_Clear();stations=1;}
			if(js==2&&RX==4){stations=2;T=0;}
			if(js==6&&RX==4){stations=3;T=0;}
			if(RY>4){delay(5);js-=2;one=1;}
			if(RY<2){delay(5);js+=2;one=1;}
				if(SW2==0){
					delay(100);
					while(SW2==0);
					js++;}
		}
		
		if(stations==1){//control
			if(one){
			OLED_Clear();
			one=0;
			T=0;
			OLED_DrawBMP(52, 0,68, 2,Control);
			}
			if(T%5==0){
			OLED_DrawBMP(cj, 2,cj+15, 3,CAT);
			OLED_DrawBMP(46-yd, 0,51-yd, 2,ZWIFI);
			OLED_DrawBMP(69+yd, 0,74+yd, 2,RWIFI);
			yd++;
			cj++;
			if(cj+15>125){OLED_DrawBMP(cj, 2,cj+15, 3,CAT0);cj=0;};
			if(69+yd>120){yd=0;}
			}	
				if(T%10==0&&connect==1){
				SendString("AT+CIPSEND=4");
					delay(40);
				SendString(meg);
				}		
				if(SW2==0){
				delay(100);
				while(SW2==0);
				OLED_Clear();	
				stations=0;}
				
				if(T%20==0){OLED_ShowNum(42,4,dw,5,8);}
				if(T%25==0){OLED_ShowNum(42,5,RX,5,8);}
				if(T%30==0){OLED_ShowNum(42,6,LX,5,8);}
				if(T%10==0){
				if(RX>2&&sw==1){sw=0;dw-=1;}
				if(RX<2&&sw==1){sw=0;dw+=1;}
				if(dw<3||dw>6){dw=3;}
				}
					
					if(RY==3){meg[3]='0';}else{	meg[3]=dw+48;}
					if(RY<3){ meg[2]='1';}else{	meg[2]='0';}
					if(LX>2){ meg[1]='2';}
					if(LX==2){meg[1]='0';}
					if(LX<2){ meg[1]='1';}
					
		}
		
		if(stations==2){
			delay(500);
			if(one){
			OLED_Clear();	
			one=0;
			SendString("AT+CWJAP=\"ESP8266\",\"55555555\"");
			}
			draw_wait(4);
			stations=0;
		}
		
		if(stations==3){
			if(one){
			draw_wait(1);
			OLED_Clear();	
			one=0;
			T=0;
			}
			if(!connect){SendString("AT+CWJAP=\"ESP8266\",\"55555555\"");draw_wait(4);}
			if(connect)	{SendString("AT+CIPSTART=\"TCP\",\"192.168.4.1\",8080");}else{stations=0;return;}
			delay(1000);
			SendString("AT+CIPSEND=4");
			delay(40);
			SendString("0300");	
			while(1){
				T=0;
				draw_wait(1);
				if(stations==0){OLED_Clear();	break;}
			}
			}
		}
}

void draw_wait(u8 x){
		while(1){
			angle++;if(angle>=360){angle=0;}
			switch(x){
				case 1:	cj= 20*cos(angle)+65;yd= 20*sin(angle)+40; break;
				case 2: cj=	cos(angle)*20*(1-sin(angle))+60;	yd=sin(angle)*20*(1-sin(angle))+50;break;
				case 3: cj=20 * (sin(angle))*(sin(angle))*(sin(angle))+65;	yd=16 * cos(angle)-5*cos(2*angle)-2*cos(3*angle)-cos(4*angle)+30;break;
				case 4:	cj= 20*cos(angle)+65;	yd=  20*sin(angle)+40; break;
			}
					DrawP(128-cj,64-yd);
					if(T%1200==0&&x<4) { cj=0; yd=0;break;}
					if(GetWIFI()&&x==4){	OLED_Clear();connect=1;	return;	}
					if(T%5000==0&&x>3){	OLED_Clear();return;}
					if(SW2==0){
						while(SW2==0);
						OLED_Clear();	
						stations=0;	
						break;
					}
	}
}
void init(){
	Timer0Init();	
	OLED_Init();
	OLED_Clear();
	draw_wait(1);
	UartInit0();
	UartInit();
	OLED_Clear();
}