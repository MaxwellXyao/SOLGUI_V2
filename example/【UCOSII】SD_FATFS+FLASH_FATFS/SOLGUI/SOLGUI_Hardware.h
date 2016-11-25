#ifndef SOLGUI_HARDWARE_H
#define SOLGUI_HARDWARE_H

#include"SOLGUI_Config.h"

//##########################【API】############################
void SOLGUI_Hardware_Init(void);											//硬件初始化
void SOLGUI_Hardware_FillScreen(u8 GRAM[SCREEN_X_WIDTH][SCREEN_Y_PAGE]);	//硬件屏幕填充函数
void SOLGUI_Hardware_ClearScreen(void);										//硬件清屏函数

#endif
