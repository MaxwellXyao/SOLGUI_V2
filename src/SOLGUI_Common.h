#ifndef SOLGUI_COMMON_H
#define SOLGUI_COMMON_H

#include"SOLGUI_Menu.h"


//########################【宏函数】############################
#define SOLGUI_Fabs(num) (num<0)?-num:num						//用于数字显示，绝对值

#define bit(n) (1<<n) 
#define bit_istrue(x,mask) ((x&mask) != 0)
#define bit_isfalse(x,mask) ((x&mask) == 0)

//##########################【API】############################
#if MENU_FRAME_EN==0	//SOLGUI不使用前台
	void SOLGUI_Init(void); 		//SOLGUI不使用前台时的初始化
#elif MENU_FRAME_EN==1	//SOLGUI使用前台
	void SOLGUI_Init(MENU_PAGE *home_page); 		//SOLGUI使用前台时的初始化
#endif
 
void SOLGUI_Refresh(void);		//刷新屏幕
void SOLGUI_Clean(void);		//软清屏（必须刷新GRAM）
void SOLGUI_DrawPoint(u32 x,u32 y,u8 t);			//画点，t=1点亮；t=0熄灭.

#endif

