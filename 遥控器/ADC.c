#include <STC15F2K60S2.H>
#include "drive.h"

void ADC_init(u8 w){
	P1ASF=(0x20>>w);
	//P1ASF=0x10;
	ADC_CONTR=0xE8;
	ADC_CONTR|=(w+2);
	CLK_DIV=0x50;
	ADC_RES=0;
}

u8 ADC_GetNum(u8 w){
	ADC_RES=0;
	ADC_init(w);
	while(!(ADC_CONTR&0X10));//flag
	ADC_CONTR=0;
	P1ASF=0;
	return ADC_RES;
}