#include <STC15F2K60S2.H>
sbit pwm=P5^5;
void Timer0_Init(void)		//100΢��@11.0592MHz
{
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0xA4;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	//PT0=9;
	ET0 = 1;
	EA=1;
	ES=1;
}
int count=0;int angle=18;

void Timer0_Isr() interrupt 1
{
		TL0 = 0xA4;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	if(count< angle)              //�жϴ����Ƿ�С�ڽǶȱ�ʶ
      pwm=1;                  //ȷʵС�ڣ�PWM����ߵ�ƽ
    else
      pwm=0;                  //����������͵�ƽ
    count=(count+1);          //0.1ms������1
    count=count%160;     //��������Ϊ20ms����ͨ51��Ƭ����ʱ100us������ʾ��������ԼΪ50Hz
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