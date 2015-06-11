#include "led.h"
#include "delay.h"
#include "key.h"
#include "tpad.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "flash.h"
#include "sram.h"
#include "malloc.h"
#include "string.h"
#include "mmc_sd.h"
#include "ff.h"
#include "exfuns.h"
#include "fontupd.h"
#include "text.h"
#include "piclib.h"
#include "string.h"
#include "usmart.h"
#include "fattester.h"
#include "piclib.h"
#include "vs10xx.h"
#include "mp3player.h"
#include "audiosel.h"
#include "recorder.h"

/*
 * STM32-TEA-Encryption-Recorder
 * https://github.com/lincanbin/STM32-TEA-Encryption-Recorder
 *
 * Copyright 2015, Canbin Lin(lincanbin@hotmail.com)
 * http://www.94cb.com/
 *
 * Licensed under the Apache License, Version 2.0:
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * A STM32 encryption recorder that use Tiny Encryption Algorithm. 
 */


 int main(void)
 {	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	TPAD_Init();		//��ʼ����������
	LCD_Init();				//LCD��ʼ��
	KEY_Init();	 			//������ʼ��
	Audiosel_Init();	//��ʼ����Դѡ��
	usmart_dev.init(72);//usmart��ʼ��
 	mem_init(SRAMIN);	//��ʼ���ڲ��ڴ��	
 	VS_Init();	  

 	exfuns_init();					//Ϊfatfs��ر��������ڴ�  
  	f_mount(0,fs[0]); 		 		//����SD�� 
 	f_mount(1,fs[1]); 				//����FLASH.
	POINT_COLOR=RED;      
 	while(font_init()) 				//����ֿ�
	{	    
		LCD_ShowString(60,50,200,16,16,"Font Error!");
		delay_ms(200);				  
		LCD_Fill(60,50,240,66,WHITE);//�����ʾ	     
	}
 	Show_Str(60,50,200,16,"Author: Canbin",16,0);				    	 
	Show_Str(60,70,200,16,"TEA����¼����",16,0);				    	 
	Show_Str(60,90,200,16,"lincanbin@hotmail.com",16,0);				    	 
	Show_Str(60,110,200,16,"2015��6��11��",16,0);
	Show_Str(60,130,200,16,"KEY0:REC/PAUSE",16,0);
	Show_Str(60,150,200,16,"KEY2:STOP&SAVE",16,0);
	Show_Str(60,170,200,16,"KEY_UP:AGC+ KEY1:AGC-",16,0);
	Show_Str(60,190,200,16,"TPAD:Play The File",16,0);
	while(1)
	{
		Audiosel_Set(0);	//MP3ͨ��
 		LED1=0; 	  
		Show_Str(60,210,200,16,"�洢������...",16,0);
		VS_Ram_Test();	    
		Show_Str(60,210,200,16,"���Ҳ�����...",16,0); 	 	 
 		VS_Sine_Test();	   
		Show_Str(60,210,200,16,"<<WAV¼����>>",16,0); 		 
		LED1=1;
		recoder_play();
	}    					  
}


