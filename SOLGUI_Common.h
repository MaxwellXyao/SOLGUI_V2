#ifndef SOLGUI_COMMON_H
#define SOLGUI_COMMON_H


//########################【宏函数】############################
#define SOLGUI_Fabs(num) (num<0)?-num:num						//用于数字显示，绝对值

//##########################【API】############################
void SOLGUI_Init(void);		//SOLGUI初始化
void SOLGUI_Refresh(void);		//刷新屏幕
void SOLGUI_DrawPoint(u32 x,u32 y,u8 t);			//画点，t=1点亮；t=0熄灭.

#endif

