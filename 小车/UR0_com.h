#pragma once
#ifndef __UR0_COM_H
#define __UR0_COM_H
#define u8 unsigned char 
void UartInit0(void);
void SendChar0(unsigned char Char);
void  SendString0(unsigned char *p);
void UR0_com__Rountine();
#endif