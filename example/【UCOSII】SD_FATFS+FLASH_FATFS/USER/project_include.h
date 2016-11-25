#ifndef __PROJECT_INCLUDE_H
#define __PROJECT_INCLUDE_H

/*----------------------------------------------------------------------		
>>pixelC3		 
>>��飺ʹ��STM32F103RET6[512kB Flash, 64kB SRAM]������16·GPIO��8·ADC��
2·DAC��8·PWM��16·�ⲿ�жϣ�3·���ڣ�2·Ӳ��SPI������OLED��SD��(SDIO)��
FLASH(8MB)��USB�ӿڣ������3.3v��5v��ѹ
----------------------------------------------------------------------*/

#include<stdio.h>
#include<stdarg.h> 						//֧�ֱ䳤����

//#######################��оƬ��֧�ֿ⡿#######################
#include "stm32f10x.h"

//#######################������ȫ��֧�ֿ⡿#######################
#include "delay.h"		//��ʱ
#include "sys.h"		//���ʹ��
#include "bit.h"		//����λ����
#include "strprintf.h"	//��ʽ���ַ�����
#include "simui2c.h"	//ģ��I2CЭ��
#include "simuspi.h"	//ģ��SPIЭ��
	
//#######################��Ӳ��֧�ֿ⡿#######################
/*------[ָʾ��]-------
@ FLAGLIGHT		��PA8 			*/
#include "BSP_FlagLight.h"	//����ָʾ��

/*------[OLED]-------
@ OLED_CK		: PB0
@ OLED_DI		: PB1
@ OLED_RST		: PC4
@ OLED_DC		: PC5		   	*/
#include "BSP_OLED.h"			//OLEDӲ������

/*------[����]-------
@ 5Key_UP		: PC2
@ 5Key_DOWN		: PC0
@ 5Key_LEFT		: PC1
@ 5Key_RIGHT	: PC3
@ 5Key_OK		: PC13
@ Key_RETURN	: PB7
@ Key_A			: PB6
@ Key_B			: PC7
@ SWITCH1		: PC6			*/
#include"BSP_Key.h"			   	//����

/*------[SD����SDIO��]-------
@ SDcard_SDIO0	: PC8 
@ SDcard_SDIO1	: PC9
@ SDcard_SDIO2	: PC10
@ SDcard_SDIO3	: PC11
@ SDcard_CLK	: PC12
@ SDcard_CMD	: PD2		 	*/
#include"BSP_SD.h"		   	//����SD��

/*------[FLASH]-------
@ FLASH_CLK		: PB3
@ FLASH_DO		: PB4
@ FLASH_DI		: PB5
@ FLASH_CS		: PA15	  		*/
#include"BSP_Flash.h"  		//����Flash(8MB)

/*------[USB]-------
@ USB_D-		��PA11
@ USB_D+		��PA12			*/	


/*------[IO����]-------
-USART:
@ USART2_TX		��PA2
@ USART2_RX		��PA3

@ USART3_TX		��PB10
@ USART3_RX		��PB11

-SPI:
@ SPI1_CS 		��PA4
@ SPI1_SCK		��PA5
@ SPI1_MISO		��PA6
@ SPI1_MOSI	  	��PA7

@ SPI2_CS 		��PB12
@ SPI2_SCK		��PB13
@ SPI2_MISO		��PB14
@ SPI2_MOSI	  	��PB15

-ADC:
@ ADC123_IN0	: PA0
@ ADC123_IN1	: PA1
@ ADC123_IN2	: PA2
@ ADC123_IN3	: PA3
@ ADC12_IN4 	: PA4
@ ADC12_IN5 	: PA5
@ ADC12_IN6 	: PA6
@ ADC12_IN7 	: PA7

-DAC:
@ DAC_OUT1		: PA4
@ DAC_OUT2		: PA5	

-TIM_CH:
@ TIM2_CH1(TIM5_CH1): PA0
@ TIM2_CH2(TIM5_CH2): PA1
@ TIM2_CH3(TIM5_CH3): PA2
@ TIM2_CH4(TIM5_CH4): PA3
@ TIM3_CH1			: PA6
@ TIM3_CH2			: PA7
@ TIM4_CH3			: PB8
@ TIM4_CH4			: PB9			*/

//#######################��SOLGUI��#######################
#include"SOLGUI_Include.h"				//SOLGUI

//#######################��FATFS��#######################
#include"ff.h"							//FATFS
//���ļ���ʽ�궨�壬���f_open����
#define FA_OPEN_DEFAULT			(u8)(FA_OPEN_EXISTING 	| FA_READ | FA_WRITE)	//�ɶ�д����
#define FA_OPEN_READONLY		(u8)(FA_OPEN_EXISTING 	| FA_READ)				//ֻ��ȡ����ִ��д
#define FA_OPEN_ADD_DATA		(u8)(FA_OPEN_ALWAYS 	| FA_READ | FA_WRITE)	//�ļ��������򴴽����ļ�������f_lseek�������ļ���׷������
#define FA_OPEN_NEW_FAIL		(u8)(FA_CREATE_NEW 		| FA_READ | FA_WRITE)	//�½��ļ������������ʧ��
#define FA_OPEN_NEW_COVER		(u8)(FA_CREATE_ALWAYS 	| FA_READ | FA_WRITE)	//�½��ļ�����������򸲸�

//#######################��UCOSII��#######################
#include "includes.h"					//UCOSII












#endif
