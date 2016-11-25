#ifndef SOLGUI_GBASIC_H
#define SOLGUI_GBASIC_H

//##############################��mode������##############################
/*----------------------------------------------------------------------

	mode���壺
	mode[1:0]	���Ϳ��ƣ�00��01ʵ�ߣ�10���ߣ�11�̻���
	mode[2]		�Ƿ����: 1��䣬0�����

----------------------------------------------------------------------*/
//-------------------�����͡�
#define DELETE 		0x00		//����
#define ACTUAL 		0x01		//ʵ��
#define DOTTED 		0x02		//����
#define DASHED 		0x03		//�̻���
//-------------------���Ƿ���䡿
#define FILL		0x04		//ʵ���


//##############################��API��##############################
void SOLGUI_GBasic_Line(u32 x0,u32 y0,u32 xEnd,u32 yEnd,u8 mode);	//���ߣ���㣬�յ㣬������
void SOLGUI_GBasic_Rectangle(u32 x0,u32 y0,u32 x1,u32 y1,u8 mode);		//�����Σ����½ǣ����Ͻǣ�������
void SOLGUI_GBasic_MultiLine(const u32 *points,u8 num,u8 mode);		//�������ߣ�������ָ�룬������������
void SOLGUI_GBasic_Circle(u32 x0,u32 y0,u32 r,u8 mode);			//��Բ��Բ�ģ��뾶��������


#endif
