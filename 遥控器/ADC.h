#pragma once
#ifndef __ADC_H
#define __ADC_H
#define u8 unsigned char 
#define u16 unsigned int 
	
#define PLX 1
#define PLY 2
#define PRX 3
#define PRY 4

void ADC_init(u8 w);
u8 ADC_GetNum(u8 w);
#endif