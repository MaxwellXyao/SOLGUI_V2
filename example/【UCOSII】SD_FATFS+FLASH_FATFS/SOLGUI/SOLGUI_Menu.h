#ifndef SOLGUI_MENU_H
#define SOLGUI_MENU_H

#define PAGE_NULL 		0		//��ҳ��
#define FIFO_NONE		0		//FIFO��

//##############################��ҳ�溯����Ϣ�ṹ�塿##############################
//ÿ��������ҳ�����ҳ�溯����һ����Ϣ�ṹ�壨��������ҳ�������Ϣ��
typedef struct __MENU_PAGE{									//�˵�/��������
	const u8 *pageTitle;									//�ò�˵��ı���
	struct __MENU_PAGE *parentPage;							//�ò�˵��еĸ��˵�ָ��
	void (*pageFunc)();										//ҳ�溯��ָ��
}MENU_PAGE;

//�������·����Զ�����������ҳ��

//------------���Զ����꡿
#define __M_PAGE(name,pageTitle,parentPage,Program)	\
void _##name(){Program}								\
MENU_PAGE name={pageTitle,parentPage,_##name};

/*�÷�:
������
void _sub()
{
	SOLGUI_Cursor(0,1,8);
	SOLGUI_Widget_GotoPage(0,&test1);
	SOLGUI_Widget_Edit(2,"edit",1,test_str);								//�ı��༭��
	SOLGUI_Widget_Spin(1,"t",INTEGRAL,-1000,1000,&t);
	SOLGUI_Widget_Spin(3,"t1",DECIMAL,1000,-1000,&t1);							 
}
MENU_PAGE sub={
	"sub_page",
	&index,
	_sub
};

��Ӧ���Զ����꣺
__M_PAGE(ҳ�������,ҳ�����,��ҳ���ַ,
{
	/////////////�˴���дҳ�溯��////////////
});


*/


//####################################��FIFO��##############################
//ʹ��FIFO��ǿ�������첽����µ��ȶ���
typedef struct __GUI_FIFO{
	u8 FIFOBuffer[FIFOBUF_SIZE];	   						//����FIFO��
	u8 Read;												//��������ָ��				
	u8 Write;												//������дָ��
}GUI_FIFO;													//FIFO��			

//####################################���ڲ�ʹ�á�##########################################
void SOLGUI_Menu_SetHomePage(MENU_PAGE *home_page);	//��ҳ����

//####################################��API��##########################################
void SOLGUI_InputKey(u8 key_value); 				//������������ϵͳ�л�ȡ��ǰ������ֵ�������
u8 	 SOLGUI_GetCurrentKey(void); 					//������������ȡGUI��ǰ��ȫ�ּ�ֵ
void SOLGUI_Menu_PageStage(void);					//����������SOLGUIǰ̨ҳ���л���




#endif
