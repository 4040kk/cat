#include "drive.h"

void delay(int x)		//@22.1184MHz 100us
{
	unsigned char i, j;

	while(x){
		i = 3;
	j = 35;
	do
	{
		while (--j);
	} while (--i);
	x--;
	}

}
