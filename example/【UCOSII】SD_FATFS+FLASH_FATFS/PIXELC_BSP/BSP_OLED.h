#ifndef BSP_OLED_H
#define BSP_OLED_H

#include "sys.h"
#include "delay.h"

//##############################【硬件定义】##############################
//-------------引脚定义
#define SPI_CK_GPIOx GPIOB
#define SPI_CK_Pin 	0	//PB0

#define SPI_DI_GPIOx GPIOB
#define SPI_DI_Pin 	1	//PB1

#define SPI_RST_GPIOx GPIOC
#define SPI_RST_Pin 4	//PC4

#define SPI_DC_GPIOx GPIOC
#define SPI_DC_Pin 	5	//PC5

//------------电平变化函数
//****CK****
#define OLED_CK_HIGH() 		PBout(0)=1
#define OLED_CK_LOW()		PBout(0)=0
//****DI****
#define OLED_DI_HIGH()		PBout(1)=1
#define OLED_DI_LOW()		PBout(1)=0
//****RST****
#define OLED_RST_HIGH()		PCout(4)=1
#define OLED_RST_LOW()		PCout(4)=0
//****DC****
#define OLED_DC_HIGH()		PCout(5)=1
#define OLED_DC_LOW()		PCout(5)=0

//------------延时函数
#define OLED_Delay() 		delay_ms(10)

//##############################【参数】##############################
#define OLED_X_WIDTH        	128		//X像素长
#define OLED_Y_WIDTH        	64		//Y像素长
#define OLED_Y_PAGE				8		//Y方向页长度

//############################【功能开关】############################
#define OLED_USE_SOLGUI		//使用SOL_GUI，不编译硬件字库

//##############################【内部】##############################
void OLED_PinInit(void);
void OLED_WrDat(u8 dat);
void OLED_WrCmd(u8 cmd);
void OLED_Set_Pos(u8 x,u8 y);
void OLED_Fill(u8 bmp_dat);

//##############################【API】##############################
void OLED_Init(void);			//OLED硬件初始化
void OLED_P6x8Str(u8 x,u8 y,u8 ch[]); 	//硬件写字符串:硬件测试
void OLED_CLS(void);			//硬件清屏

//##############################【移植用】##############################
void OLED_FillScreen(u8 gram[OLED_X_WIDTH][OLED_Y_PAGE]);

#endif
