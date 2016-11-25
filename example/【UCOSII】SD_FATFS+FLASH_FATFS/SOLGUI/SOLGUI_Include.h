#ifndef SOLGUI_INCLUDE_H
#define SOLGUI_INCLUDE_H

//#########################��SOLGUI�汾��Ϣ��############################
#define SOLGUI_VERSION "2.0"

//##########################��SOLGUIԴ�ļ���############################
//-----------����ֲ���á�
#include"SOLGUI_Type.h"
#include"SOLGUI_Config.h"

//-----------���м�㡿
#include"SOLGUI_Common.h"
#include"SOLGUI_Printf.h"
#include"SOLGUI_GBasic.h"
#include"SOLGUI_Picture.h"
//-----------��Ӧ�ò㡿
#include"SOLGUI_Menu.h"
#include"SOLGUI_Widget.h"

/*##########################��ʹ��˵����##########################
��1���ַ����ĸ�ʽ�����:
SOLGUI_printf(21,26,F8X10,"helloworld!");

�˴���SOLGUI_printf������PC��printf��һ���Ӽ�
��˸�ʽ�÷���PC��prinfһ����

0x01:��ʽ����
	%s,%S:�ַ���
	%c,%C:�����ַ�

	%f,%F:double��������ÿ����ʽ���ַ���ֻ�ܴ���һ����Ĭ����3λС����

	%b,%B:���Ͷ�����
	%o,%O:���Ͱ˽���
	%d,%D:����ʮ���ƣ�����������
	%u,%U:����ʮ���ƣ�����������
	%x,%X:����ʮ������

0x02:������ֻ�������֣�
	%07d�����㣨������С��ʾ����7�񣬲�������0��ǰ�油�룩
	%-7d������루������С��ʾ����7�񣬲������ÿո��ں��油�룩
	%.4f: ����С��λ��������4λС������ౣ��7λ��

��2��ҳ���ܲ���:

	SOLGUI_Init(&index);			//��ʼ��

	while(1)
	{
		kv=pixelC_HW_Key_GetValue();	//��ֵ��ȡ
		SOLGUI_InputKey(kv);			//��ֵ����
		SOLGUI_Menu_PageStage();	 	//ǰ̨
		SOLGUI_Refresh();				//������Ļ
	}


��3��ҳ�洴��:
MENU_PAGE index;						//ҳ������
 __M_PAGE(index,"test",PAGE_NULL,{		//�귽ʽ����ҳ��
	////////////////////////////
});

��3����ӿؼ�:
//---------------��ҳ����ơ�
SOLGUI_Cursor(u8 rowBorder_Top,u8 rowBorder_Bottom,u8 option_num);					//��꣨�ϱ߽��У��±߽��У�ѡ�������
//---------------��ѡ��ʽ�ؼ���
SOLGUI_Widget_GotoPage(u8 USN,MENU_PAGE *page);										//ҳ����ת
SOLGUI_Widget_Spin(u8 USN,const u8 *name,u8 type,double max,double min,void* value);//������ť
SOLGUI_Widget_OptionText(u8 USN,const u8* str,...);									//ѡ���ı���̫��������str���ڸǹ�������
SOLGUI_Widget_Button(u8 USN,const u8 *name,void (*func)(void));						//����
SOLGUI_Widget_Switch(u8 USN,const u8 *name,u32 *mem_value,u8 L_shift);				//�������أ�mem_value��һ���ⲿ����ķ���ʧ�Դ洢��������
SOLGUI_Widget_Edit(u8 USN,const u8 *name,u16 char_num,u8 *buf);						//�ı��༭����char_num���޸ĳ��ȣ�
//---------------������ʽ�ؼ���
SOLGUI_Widget_Text(u32 x0,u32 y0,u8 mode,const u8* str,...);										//���֣��ڸò�Ӧ�����������printf��
SOLGUI_Widget_Bar(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,s32 value,u8 mode);				//��
SOLGUI_Widget_Spectrum(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,u16 val_num,s32 value[]);	//��
SOLGUI_Widget_Oscillogram(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,WaveMemBlk *wmb);  		//����ʾ��Ҫͨ����̽���������ݸ���
SOLGUI_Widget_Picture(u32 x0,u32 y0,u32 xsize,u32 ysize,const u8 *pic,u32 x_len,u32 y_len,u8 mode); //ͼƬ	
//---------------��������
SOLGUI_Oscillogram_Probe(WaveMemBlk *wmb,s32 value);												//��̽��





-------------------------------------------------------------------*/

#endif
