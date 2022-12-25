#include "header.h"
#include "Time0.h"
#include <STC89C5xRC.H>
#include "pm.h"
#include "IR.h"
 unsigned char count=0; u32 t = 0;  u8 compare; u8 xpt;
 bit sw=0;
static u8 key,speed; 
//////////////////////定时器区//////////////////////////////
u32 j=0;
void Timer1Init(void) //100us
{
	
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0x18;		//ÉèÖÃ¶¨Ê±³õÖµ
	TH1 = 0xFC;		//ÉèÖÃ¶¨Ê±³õÖµ
	TF1 = 0;		//Çå³ýTF0±êÖ¾
	TR1 = 1;		//¶¨Ê±Æ÷0¿ªÊ¼¼ÆÊ±
	ET1 = 1;
	EA=1;
	PT1=0;
}

void Timer1_Rountine() interrupt 3
{
	TL1 = 0x78;		//ÉèÖÃ¶¨Ê±³õÖµ
	TH1 = 0xEC;		//ÉèÖÃ¶¨Ê±³õÖµ
}
void Timer0_Isr() interrupt 1
{
	TL0 = 0xA4;		//ÉèÖÃ¶¨Ê±³õÖµ
	TH0 = 0xFF;		//ÉèÖÃ¶¨Ê±³õÖµ
	if(count< compare)  
	{P10=1; }		//ÅÐ¶Ï´ÎÊýÊÇ·ñÐ¡ÓÚ½Ç¶È±êÊ¶				//È·ÊµÐ¡ÓÚ£¬PWMÊä³ö¸ßµçÆ½
    else{
		  P10=0;  
		}            //´óÓÚÔòÊä³öµÍµçÆ½
    count=(count+1);          //0.1ms´ÎÊý¼Ó1
    count=count%160;     //±£³ÖÖÜÆÚÎª20ms£¬ÆÕÍ¨51µ¥Æ¬»ú¶¨Ê±100usÓÐÎó²î£¬¾­Ê¾²¨Æ÷²âÁ¿Ô¼Îª50Hz
		t++;
}

void Timer0_I(void)		//100Î¢Ãë@11.0592MHz
{
	TMOD |= 0x01;		//ÉèÖÃ¶¨Ê±Æ÷Ä£Ê½
	TL0 = 0xA4;		//ÉèÖÃ¶¨Ê±³õÖµ
	TH0 = 0xFF;		//ÉèÖÃ¶¨Ê±³õÖµ
	TF0 = 0;		//Çå³ýTF0±êÖ¾
	TR0 = 1;		//¶¨Ê±Æ÷0¿ªÊ¼¼ÆÊ±
	ET0 = 1;
	EA=1;
}



//////////////////////定时器区///////////////////////////////////


void main(){
	Timer0_I();
	compare=6;
	ired_init();
	LCD_Init();
	while(1){
		if(t>50000)t=0;
		key=key_scan(0);
		if(j==8){compare=8;}
		if(j==90){compare=5;}
		if(P32==0){P20=0;}
		//compare=(xpt2046(xpt_XP)*25)/255;

		if(key==1){
			j++;
		}
		
			LCD_ShowNum(1,1,j,4);
			LCD_ShowNum(2,1,compare,4);
		
		
		
}
	

	
}









