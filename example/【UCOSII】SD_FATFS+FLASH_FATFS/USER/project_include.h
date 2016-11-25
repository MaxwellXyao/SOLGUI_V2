#ifndef __PROJECT_INCLUDE_H
#define __PROJECT_INCLUDE_H

/*----------------------------------------------------------------------		
>>pixelC3		 
>>简介：使用STM32F103RET6[512kB Flash, 64kB SRAM]。引出16路GPIO，8路ADC，
2路DAC，8路PWM，16路外部中断，3路串口，2路硬件SPI，板载OLED，SD卡(SDIO)和
FLASH(8MB)，USB接口，可输出3.3v和5v电压
----------------------------------------------------------------------*/

#include<stdio.h>
#include<stdarg.h> 						//支持变长参数

//#######################【芯片级支持库】#######################
#include "stm32f10x.h"

//#######################【工程全局支持库】#######################
#include "delay.h"		//延时
#include "sys.h"		//快捷使用
#include "bit.h"		//快速位操作
#include "strprintf.h"	//格式化字符串核
#include "simui2c.h"	//模拟I2C协议
#include "simuspi.h"	//模拟SPI协议
	
//#######################【硬件支持库】#######################
/*------[指示灯]-------
@ FLAGLIGHT		：PA8 			*/
#include "BSP_FlagLight.h"	//板载指示灯

/*------[OLED]-------
@ OLED_CK		: PB0
@ OLED_DI		: PB1
@ OLED_RST		: PC4
@ OLED_DC		: PC5		   	*/
#include "BSP_OLED.h"			//OLED硬件驱动

/*------[按键]-------
@ 5Key_UP		: PC2
@ 5Key_DOWN		: PC0
@ 5Key_LEFT		: PC1
@ 5Key_RIGHT	: PC3
@ 5Key_OK		: PC13
@ Key_RETURN	: PB7
@ Key_A			: PB6
@ Key_B			: PC7
@ SWITCH1		: PC6			*/
#include"BSP_Key.h"			   	//按键

/*------[SD卡（SDIO）]-------
@ SDcard_SDIO0	: PC8 
@ SDcard_SDIO1	: PC9
@ SDcard_SDIO2	: PC10
@ SDcard_SDIO3	: PC11
@ SDcard_CLK	: PC12
@ SDcard_CMD	: PD2		 	*/
#include"BSP_SD.h"		   	//板载SD卡

/*------[FLASH]-------
@ FLASH_CLK		: PB3
@ FLASH_DO		: PB4
@ FLASH_DI		: PB5
@ FLASH_CS		: PA15	  		*/
#include"BSP_Flash.h"  		//板载Flash(8MB)

/*------[USB]-------
@ USB_D-		：PA11
@ USB_D+		：PA12			*/	


/*------[IO复用]-------
-USART:
@ USART2_TX		：PA2
@ USART2_RX		：PA3

@ USART3_TX		：PB10
@ USART3_RX		：PB11

-SPI:
@ SPI1_CS 		：PA4
@ SPI1_SCK		：PA5
@ SPI1_MISO		：PA6
@ SPI1_MOSI	  	：PA7

@ SPI2_CS 		：PB12
@ SPI2_SCK		：PB13
@ SPI2_MISO		：PB14
@ SPI2_MOSI	  	：PB15

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

//#######################【SOLGUI】#######################
#include"SOLGUI_Include.h"				//SOLGUI

//#######################【FATFS】#######################
#include"ff.h"							//FATFS
//打开文件方式宏定义，针对f_open函数
#define FA_OPEN_DEFAULT			(u8)(FA_OPEN_EXISTING 	| FA_READ | FA_WRITE)	//可读写操作
#define FA_OPEN_READONLY		(u8)(FA_OPEN_EXISTING 	| FA_READ)				//只读取，不执行写
#define FA_OPEN_ADD_DATA		(u8)(FA_OPEN_ALWAYS 	| FA_READ | FA_WRITE)	//文件不存在则创建新文件，可用f_lseek函数在文件上追加数据
#define FA_OPEN_NEW_FAIL		(u8)(FA_CREATE_NEW 		| FA_READ | FA_WRITE)	//新建文件，如果存在则失败
#define FA_OPEN_NEW_COVER		(u8)(FA_CREATE_ALWAYS 	| FA_READ | FA_WRITE)	//新建文件，如果存在则覆盖

//#######################【UCOSII】#######################
#include "includes.h"					//UCOSII












#endif
