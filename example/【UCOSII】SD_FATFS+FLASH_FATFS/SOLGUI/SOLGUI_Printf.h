#ifndef SOLGUI_PRINTF_H
#define SOLGUI_PRINTF_H

#include<stdarg.h> 						//֧�ֱ䳤����

//##############################�������꡿##############################
//-------------��mode������
//      F��X��	ֵ
#define F6X8 	0x01  		//6x8����������ʾ��Ĭ�ϣ� //00000001
#define R6X8 	0xfe		//6x8���巴����ʾ����0��

#define F4X6 	0x02		//4X6����������ʾ		  //00000010
#define R4X6 	0xfd		//4X6���巴����ʾ

#define F8X8 	0x04		//8X8����������ʾ		  //00000100
#define R8X8 	0xfb		//8X8���巴����ʾ

#define F8X10 	0x08		//8X10����������ʾ		  //00001000
#define R8X10 	0xf7		//8X10���巴����ʾ

/*---------------------
�������к�������ֿ�
---------------------*/
//########################���ֿ���Ϣ�ṹ�塿########################
typedef struct _FontInfo{
	u8 FontMask;		//�ַ�ѡ������
	u8 FontWidth;		//�ַ����
	u8 FontHeight;		//�ַ��߶�
	const u8 *Fontp;	//�ַ���ָ��
}FontInfo;

//###########################���ڲ�ʹ�á�############################
void __SOLGUI_printf(u32 x,u32 y,u8 mode,const u8* str,va_list arp);		//SOLGUI�ڲ�ʹ�õ���Ļprintf�ײ�



//##############################��API��##############################
void SOLGUI_printf(u32 x,u32 y,u8 mode,const u8* str,...);	//��ʾ��ʽ���ַ�����mode��1������ʾ��0������ʾ��

#endif


