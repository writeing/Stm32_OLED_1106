#include  "delay.h"
#include  "led.h"
#include  "usart.h"
#include  "spi.h"
#include  "string.h"
#include  "main.h"
#include  "Time_test.h"
#include  "string.h"
#include  "OLED.h"
int main(void)
{
		uint16_t il=0,ih=0;		
  
   	delay_init();	    	 //��ʱ������ʼ��
    uart_init(115200);	 //���ڳ�ʼ��Ϊ9600  
 	  LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
		TIM2_NVIC_Configuration();
		TIM2_Configuration();
	  SPI1_Init();	 //��ʼ��SPI1  PA5 PA6 PA7 IOΪSPIģʽ
	  //SPI1_SetSpeed(SPI_BaudRatePrescaler_16);	 //����SPI1�ٶ�Ϊ���
		START_TIME;	
		OLED_Init();
		OLED_Clear();


		OLED_DrawBMP(3,0,1);
		OLED_DrawBMP(1,0,0);
		OLED_DrawBMP(5,0,2);		
		OLED_sDrawBMP(9,0,0);
//		OLED_ShowChinese(4,0,0);
//		OLED_ShowChinese(6,0,1);
//		OLED_ShowChinese(8,0,2);
//		OLED_ShowChinese(10,0,3);
//		OLED_ShowChinese(0,2,4);
//		OLED_ShowChinese(2,2,6);
//		OLED_ShowChinese(0,4,5);
//		OLED_ShowChinese(2,4,6);	
//		OLED_ShowString(0,0,"OLED");
//		OLED_ShowChar(12*8,0,':');
//		OLED_ShowChar(4*8,2,':');
//		OLED_ShowChar(4*8,4,':');
		while(1)
		{
			if(usart_recv_flag)
			{
				usart_recv_flag = 0;
				printf("hehe\r\n");
			}								
			OLED_ShowNum(40,4,++il,4,16);
			delay_ms(100);
			OLED_ShowNum(40,2,++ih,4,16);
			delay_ms(100);
		}
}









