#ifndef _ired_H
#define _ired_H

#include "public.h"
#include "header.h"
//管脚定义
sbit IRED=P3^2;

//声明变量
extern u8 gired_data[4];


//函数声明
void ired_init(void);

#endif