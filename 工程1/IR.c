#include <STC89C5xRC.H>
#include "header.h"
#include "Time0.h"
#include "IR.h"

u32 IR_time;
u8 IR_state;
u8 IR_data[4];
u8 IR_pdata;
u8 IR_dataFlag;
u8 IR_repeatFlag;
u8 IR_Address;
u8 IR_command;

u8 IR_GetDataFlag(){

return IR_dataFlag;
}

u8 IR_GetRepeatFlag(){
return IR_repeatFlag;
}
u8 IR_GetAddress(){

return IR_Address;
}
u8 IR_GetCommand(){
return IR_command;
}

void IR_Init(){
	IR_repeatFlag=0;
	Timer0Init();
	Int0Init();
	IR_dataFlag=0;
}

//void Int0Init(void){
//		IT0=1;
//		IE0=0;
//		EX0=1;
//		EA=1;
//		PX0=1;
//}
void Int0_Routine(void) interrupt 0
{
		if(IR_state==0){
			Timer0_SetCounter(0);
			Timer0_Run(1);
			IR_state=1;
		}
		else if(IR_state==1){
				
		IR_time=Timer0_GetCounter();
		Timer0_SetCounter(0);
			if(IR_time>12440-600&&IR_time<12440+600){
				IR_state=2;
		
			}else if(IR_time>10360-600&&IR_time<10368+600)
			{
				IR_repeatFlag=1;
				IR_state=0;
				Timer0_Run(0);
			}
			else{
				IR_state=1;
			}
			
		}
		else if(IR_state=2){
		IR_time=Timer0_GetCounter();
			if(IR_time>1035-500&&IR_time<1035+500){
			
			IR_data[IR_pdata/8]&=~(0x01<<(IR_pdata%8));
			IR_pdata++;
			}
			else if(IR_time>2025-500&&IR_time<2025+500){
			IR_data[IR_pdata/8]|=(0x01<<(IR_pdata%8));
			IR_pdata++;
			
			}
			else{
			 IR_state=1;
				IR_pdata=0;
			}
			if(IR_pdata>=32){
			IR_pdata=0;
			if((IR_data[0]==~IR_data[1])&&(IR_data[2]==~IR_data[3])){
				IR_Address=IR_data;
				IR_command=IR_data;
					IR_dataFlag=1;
			}
			Timer0_Run(0); 
			IR_state=0;
			
			}
		}
		
		
}