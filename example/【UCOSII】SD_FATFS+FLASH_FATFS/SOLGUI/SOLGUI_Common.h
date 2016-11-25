#ifndef SOLGUI_COMMON_H
#define SOLGUI_COMMON_H

#include"SOLGUI_Menu.h"


//########################���꺯����############################
#define SOLGUI_Fabs(num) (num<0)?-num:num						//����������ʾ������ֵ

#define bit(n) (1<<n) 
#define bit_istrue(x,mask) ((x&mask) != 0)
#define bit_isfalse(x,mask) ((x&mask) == 0)

//##########################��API��############################
#if MENU_FRAME_EN==0	//SOLGUI��ʹ��ǰ̨
	void SOLGUI_Init(void); 		//SOLGUI��ʹ��ǰ̨ʱ�ĳ�ʼ��
#elif MENU_FRAME_EN==1	//SOLGUIʹ��ǰ̨
	void SOLGUI_Init(MENU_PAGE *home_page); 		//SOLGUIʹ��ǰ̨ʱ�ĳ�ʼ��
#endif
 
void SOLGUI_Refresh(void);		//ˢ����Ļ
void SOLGUI_Clean(void);		//������������ˢ��GRAM��
void SOLGUI_DrawPoint(u32 x,u32 y,u8 t);			//���㣬t=1������t=0Ϩ��.

#endif

