#include <STC15F2K60S2.H>
sbit pwm=P5^5;
void Timer0_Init(void)		//100微秒@11.0592MHz
{
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	//PT0=9;
	ET0 = 1;
	EA=1;
	ES=1;
}
int count=0;int angle=18;

void Timer0_Isr() interrupt 1
{
		TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	if(count< angle)              //判断次数是否小于角度标识
      pwm=1;                  //确实小于，PWM输出高电平
    else
      pwm=0;                  //大于则输出低电平
    count=(count+1);          //0.1ms次数加1
    count=count%160;     //保持周期为20ms，普通51单片机定时100us有误差，经示波器测量约为50Hz
}
int main(){
Timer0_Init();
while(1){
//		if(count%100==0){
//		  if(P07==0){
//				 while(P07==0);
//			 angle+=10;
//	
//		 }
//		}
		 


}





}