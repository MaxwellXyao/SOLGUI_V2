#include"SOLGUI_Include.h"
#include"SOLGUI_Hardware.h"
#include<string.h>

//##########################【变量定义】############################
/************GRAM定义************/
u8 SOLGUI_GRAM[SCREEN_X_WIDTH][SCREEN_Y_PAGE];

//##########################【SOLGUI共用函数】############################

#if MENU_FRAME_EN==0		//SOLGUI不使用前台

void SOLGUI_Init(void) 		//SOLGUI不使用前台时的初始化
{
	SOLGUI_Hardware_Init();
	memset(SOLGUI_GRAM,0,sizeof(SOLGUI_GRAM));			//初始化后GRAM清零，防止出错
}

#elif MENU_FRAME_EN==1		//SOLGUI使用前台

void SOLGUI_Init(MENU_PAGE *home_page) 		//SOLGUI使用前台时的初始化
{
	SOLGUI_Hardware_Init();
	memset(SOLGUI_GRAM,0,sizeof(SOLGUI_GRAM));			//初始化后GRAM清零，防止出错
	SOLGUI_Menu_SetHomePage(home_page);
}

#endif 


void SOLGUI_Refresh(void)		//刷新屏幕
{
	SOLGUI_Hardware_FillScreen(SOLGUI_GRAM);
	SOLGUI_Clean();
}

void SOLGUI_Clean(void)			//软清屏（必须刷新GRAM）
{
	memset(SOLGUI_GRAM,0,sizeof(SOLGUI_GRAM));			//GRAM清零
}

void SOLGUI_DrawPoint(u32 x,u32 y,u8 t)			//画点，t=1点亮；t=!1熄灭.
{
	unsigned char pos,bx,temp=0;
	if(x>=(SCREEN_X_WIDTH)||y>=(SCREEN_Y_WIDTH))	//0~127
	{
		return;//超出范围了.
	}
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)
	{
		SOLGUI_GRAM[x][pos]|=temp;
	}
	else 
	{
		SOLGUI_GRAM[x][pos]&=~temp;
	}

}



