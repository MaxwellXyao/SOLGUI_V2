#include"SOLGUI_Include.h"
#include"SOLGUI_Hardware.h"
#include<string.h>

//##########################���������塿############################
/************GRAM����************/
u8 SOLGUI_GRAM[SCREEN_X_WIDTH][SCREEN_Y_PAGE];

//##########################��SOLGUI���ú�����############################

#if MENU_FRAME_EN==0		//SOLGUI��ʹ��ǰ̨

void SOLGUI_Init(void) 		//SOLGUI��ʹ��ǰ̨ʱ�ĳ�ʼ��
{
	SOLGUI_Hardware_Init();
	memset(SOLGUI_GRAM,0,sizeof(SOLGUI_GRAM));			//��ʼ����GRAM���㣬��ֹ����
}

#elif MENU_FRAME_EN==1		//SOLGUIʹ��ǰ̨

void SOLGUI_Init(MENU_PAGE *home_page) 		//SOLGUIʹ��ǰ̨ʱ�ĳ�ʼ��
{
	SOLGUI_Hardware_Init();
	memset(SOLGUI_GRAM,0,sizeof(SOLGUI_GRAM));			//��ʼ����GRAM���㣬��ֹ����
	SOLGUI_Menu_SetHomePage(home_page);
}

#endif 


void SOLGUI_Refresh(void)		//ˢ����Ļ
{
	SOLGUI_Hardware_FillScreen(SOLGUI_GRAM);
	SOLGUI_Clean();
}

void SOLGUI_Clean(void)			//������������ˢ��GRAM��
{
	memset(SOLGUI_GRAM,0,sizeof(SOLGUI_GRAM));			//GRAM����
}

void SOLGUI_DrawPoint(u32 x,u32 y,u8 t)			//���㣬t=1������t=!1Ϩ��.
{
	unsigned char pos,bx,temp=0;
	if(x>=(SCREEN_X_WIDTH)||y>=(SCREEN_Y_WIDTH))	//0~127
	{
		return;//������Χ��.
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



