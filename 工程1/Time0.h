
#ifndef __TIME0_H
#define __TIME0_H
void Timer0Init(void)	;
void Timer0_SetCounter(unsigned int value);
int Timer0_GetCounter();
void Timer0_Run(unsigned char Flag);
#endif