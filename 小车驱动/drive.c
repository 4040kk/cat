#include"header.h"
#include <intrins.h>
void dlay(u16 x)		//@11.0592MHz 100US
{
	unsigned char i, j;
while(x){

	_nop_();
	_nop_();
	i = 2;
	j = 15;
	do
	{
		while (--j);
	} while (--i);
	x--;
}

}
