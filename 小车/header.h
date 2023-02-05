#pragma once
#ifndef __SHUMA_H
#define __SHUMA_H
#define u8 unsigned char 
#define u16 unsigned int 
void dlay(u16 x);
u8 key_scan(u8 mod);
void delay_10us(u16 ten_us);
void findload();
#endif