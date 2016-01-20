#ifndef SOLGUI_COMMON_H
#define SOLGUI_COMMON_H


//##########################【API】############################
void SOLGUI_Init(void);		//SOLGUI初始化
void SOLGUI_Refresh(void);		//刷新屏幕
void SOLGUI_DrawPoint(u8 x,u8 y,u8 t);			//画点，t=1点亮；t=0熄灭.

#endif

