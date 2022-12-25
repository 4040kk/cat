#include <STC89C5xRC.H>
sbit bu=P2^5;
void dlay(int x)		//@12.000MHz
{
	unsigned char i,j;
	
	while(x){
	i = 2;
	j = 39;
	do
	{
		while (--j);
	} while (--i);
	x--;
}
	
}
void delay_10us(unsigned int ten_us)
{
	while(ten_us--);	
}


void bueertime(int ms){
	while(ms){
		bu=!bu;
		dlay(1);
		bu=!bu;
		ms--;
	}
}




