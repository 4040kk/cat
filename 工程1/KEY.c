	#include "header.h"
	#include <STC89C5xRC.H>
	#define u8 unsigned char 
	sbit KEY1 = P3 ^ 1;
	sbit KEY2 = P3 ^ 0;
	sbit KEY3 = P3 ^ 3;
	//mode:0,不可连按;1,支持;

		u8 key_scan(u8 mode)
		{	 
			static u8 key_up=1;
			if(mode)key_up=1;   
			if(key_up&&(KEY1==0||KEY2==0||KEY3==0))
			{
				dlay(10);
				key_up=0;  
				if(KEY1==0)return 1; 
				else if(KEY2==0)return 2;
				if(KEY3==0)return 3;
			}else if(KEY1==1&&KEY2==1&&KEY3==1)key_up=1; 	    
			return 0; //无按下
		}
