#pragma once
#ifndef __SHUMA_H
#define __SHUMA_H
#define u8 unsigned char 
#define u32 unsigned int 
#define	xpt_XP	0x9C
#define	xpt_YP	0xDC
#define	xpt_VBAT	0xAC
#define	xpt_AUX	0xEC
#define	beep	P2^5;

u32 xpt2046(u8 command);
void dlay(int x);
void sm(int i,int b);
void bueertime(int x);
u8 key_scan(u8 mod);
void delay_10us(u32 ten_us);
#endif