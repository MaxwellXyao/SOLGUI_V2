#ifndef SOLGUI_HARDWARE_H
#define SOLGUI_HARDWARE_H

#include"SOLGUI_Config.h"

//##########################��API��############################
void SOLGUI_Hardware_Init(void);											//Ӳ����ʼ��
void SOLGUI_Hardware_FillScreen(u8 GRAM[SCREEN_X_WIDTH][SCREEN_Y_PAGE]);	//Ӳ����Ļ��亯��
void SOLGUI_Hardware_ClearScreen(void);										//Ӳ����������

#endif
