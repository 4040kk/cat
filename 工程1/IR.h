
#ifndef __IR_H
#define __IR_H
#include <STC89C5xRC.H>

#include "header.h"
#define u8 unsigned char 
#define u16 unsigned int 
//void Int0Init(void);
//void IR_Init();
//u8 IR_GetDataFlag();
//u8 IR_GetRepeatFlag();
//u8 IR_GetAddress();
//u8 IR_GetCommand();
sbit IRED=P3^2;
//声明变量
extern u8 gired_data[4];


//函数声明
void ired_init(void);
#endif