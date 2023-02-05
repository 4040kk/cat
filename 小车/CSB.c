#include "CSB.h"
#include <STC15F2K60S2.H>
#include <intrins.h>
#include "UR0_com.h"
sbit CSB_FS=P3^6;
sbit CSB_JS=P3^7;
void CSB10us()		//@11.0592MHz
{
		unsigned char i;

	_nop_();
	i = 25;
	while (--i);
}

void send_csb(){
		CSB_FS=0;
		CSB_FS=1;
		CSB10us();
		CSB10us();
		CSB10us();
		CSB10us();
		CSB_FS=0;
}

void CSB_Init()
{
}	
	u16 tm=0;
	long timec=0;

void CSB_Onece(){
		send_csb();
		timec=0;
		while(!CSB_JS){
			CSB10us();
			timec+=10;
			if(timec>5000){break;}
		};
			timec=0;
		while(CSB_JS){
			CSB10us();
			timec+=10;
			if(timec>5000){break;}
		}
		tm=timec;
		timec=0;
		
}

float CSB_Getnum(){
		
			return (tm*0.0425);
	//return t;
	
	}


