#pragma once
#ifndef __UR_COM_H
#define __UR_COM_H

#define u8 unsigned char 
extern  bit UR_OA; 
extern u8 UR_DAT[5];
extern u8 UR_flag;
//void UR_com_sendByte(u8 Byte);
void UartInit(void);
u8 UR_com_GetByte();
int UR_Getnum();
void SendChar(unsigned char Char);
void  SendString(unsigned char *p);
void UR_com__Rountine();
#endif