#include <STC15F2K60S2.H>
#include "header.h"
void ADC_init(){
	P1ASF=32;
	ADC_CONTR=0xEA;
	CLK_DIV&=0XDF;
	ADC_RES=0;
	 dlay(100);
	
}

u8 ADC_GetNum(){
	ADC_RES=0;
	ADC_init();
	
	dlay(50);
	while(!(ADC_CONTR&0X10));
	ADC_CONTR&=0XEF;
	return ADC_RES;
}