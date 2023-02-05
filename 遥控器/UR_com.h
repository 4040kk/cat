#pragma once
#ifndef __UR_COM_H
#define __UR_COM_H
#define u8 unsigned char 
//void UR_com_sendByte(u8 Byte);
void UartInit(void);
u8 UR_com_GetByte();
bit GetWIFI();
void SendChar(unsigned char Char);
void  SendString(unsigned char *p);
void UR_com__Rountine();
#endif