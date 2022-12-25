#include <REGX52.H>
#include <STC89C5xRC.H>

sbit xpt_cs=P3^5;
sbit xpt_DCLK=P3^6;
sbit xpt_DIN=P3^4;
sbit xpt_DOUT=P3^7;
unsigned int xpt2046(unsigned char command){
	unsigned int adv=0; 
	unsigned char i;
	xpt_cs=0;
	xpt_DCLK=0;
	
	for(i=0;i<8;i++){
		xpt_DIN=command&(0x80>>i);
	xpt_DCLK=1;
	xpt_DCLK=0;
	}
	for(i=0;i<16;i++){
	xpt_DCLK=1;
	xpt_DCLK=0;
	if(xpt_DOUT){adv|=(0x8000>>i);}
	}
	
	return (adv>>8);
}
