#ifndef SOLGUI_WIDGET_H


//##################################��mode�궨�塿########################################

//------------��SPIN�ؼ���
#define INT8	0x00
#define UINT8	0x01	
#define INT16	0x02	
#define INT32	0x03	
#define FLT16	0x04	
#define FLT32	0x05			


//------------��BAR�ؼ���
//mode[0]  ��������
#define DIREC_X		0x00	//x��������
#define DIREC_Y		0x01	//y��������
//mode[2:1]	�������		 
#define PROGBAR 	0x00	//������
#define SCALEBAR 	0x02	//�̶�

//------------��PICTURE�ؼ���
#define NML			0x00	//�����޸���
#define FRM			0x40	//mode[6]:�߿򿪹�
#define REV			0x80	//mode[7]:���׿���


//####################################���ṹ�嶨�塿##########################################
//------------�����ṹ�塿
typedef struct _CURSOR{
	u8 cursor_rel_offset;	//�������ӿڵ�ƫ��
	u8 viewport_offset;		//�ӿڵ�ƫ��
	u8 row_start;			//ѡ����ʼ�У�����˶��Ͻ磩
	u8 viewport_width;		//�ӿڿ��
	u32 y_t;				//�߽�������
	u32	y_b;				//�߽�������
}CURSOR;					//�����


//------------��EDIT�ؼ���

typedef struct _IME_CLUSTER{ 
			u8 	finger;		//�ַ��ص�ǰָ�򴢴�
	const 	u8 	*name;		//�ַ�����
	const 	u8 	size;		//���ַ�������
	const 	u8	*table;		//�ַ��ر���
}IME_CLUSTER;				//�ַ��ؽṹ��

#define SOL_ASCII_IME_SIZE 5

typedef struct _EDIT_IME{
			u8 	finger;		//�ַ�����ǰָ�򴢴� 
	const 	u8 	size;	 	//�ַ�������
	IME_CLUSTER *cluster[SOL_ASCII_IME_SIZE];	//�ַ�������
}EDIT_IME;					//���뷨�ַ����ṹ��


//------------��Oscillogram�ؼ���
typedef struct _WaveMemBlk{
	u16 size;				//��������������С��
	s32	*mem; 				//��ŵ�������ڴ��ַ
}WaveMemBlk;				//�������ݴ����

/*
�ռ����뷶��:
	s32 test_mem[128];						
	WaveMemBlk _wave_test1={128,test_mem};
	WaveMemBlk *wave_test1=&_wave_test1;

Ҳ����������ĺ������룺__M_WMB_MALLOC(��,��С)
*/
//------------���Զ����꡿
#define __M_WMB_MALLOC(name,size) 		\
s32 _##name##_mem[size];				\
WaveMemBlk _##name={size,_##name##_mem};\
WaveMemBlk *##name=&_##name;

//####################################��API��##########################################
//---------------����꡿
void SOLGUI_Cursor(u8 rowBorder_Top,u8 rowBorder_Bottom,u8 option_num);				//��꣨�ϱ߽��У��±߽��У�ѡ�������

//---------------��ѡ��ʽ�ؼ���
void SOLGUI_Widget_GotoPage(u8 USN,MENU_PAGE *page);								//ҳ����ת
void SOLGUI_Widget_Spin(u8 USN,const u8 *name,u8 type,double max,double min,void* value);	//������ť
void SOLGUI_Widget_OptionText(u8 USN,const u8* str,...);							//ѡ���ı���̫��������str���ڸǹ�������
void SOLGUI_Widget_Button(u8 USN,const u8 *name,void (*func)(void));				//����
void SOLGUI_Widget_Switch(u8 USN,const u8 *name,u32 *mem_value,u8 L_shift);			//�������أ�mem_value��һ���ⲿ����ķ���ʧ�Դ洢��������
void SOLGUI_Widget_Edit(u8 USN,const u8 *name,u16 char_num,u8 *buf);				//�ı��༭����char_num���޸ĳ��ȣ�

//---------------������ʽ�ؼ���
void SOLGUI_Widget_Text(u32 x0,u32 y0,u8 mode,const u8* str,...);			//���֣��ڸò�Ӧ�����������printf��
void SOLGUI_Widget_Bar(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,s32 value,u8 mode);		//��
void SOLGUI_Widget_Spectrum(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,u16 val_num,s32 value[]);	//��
void SOLGUI_Widget_Oscillogram(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,WaveMemBlk *wmb);  //����ʾ��Ҫͨ����̽���������ݸ���
void SOLGUI_Widget_Picture(u32 x0,u32 y0,u32 xsize,u32 ysize,const u8 *pic,u32 x_len,u32 y_len,u8 mode); //ͼƬ	

//---------------��������
void SOLGUI_Oscillogram_Probe(WaveMemBlk *wmb,s32 value);											//��̽��

#endif
