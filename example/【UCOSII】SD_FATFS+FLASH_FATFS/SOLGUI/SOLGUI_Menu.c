#include"SOLGUI_Include.h"
#include<string.h>


#if MENU_FRAME_EN==1

//##############################��ȫ�ֱ������塿##############################
MENU_PAGE *current_page;//��ǰҳ��
GUI_FIFO _key_cache;	//��ֵFIFO
u8 cur_key=0;			//ȫ�ּ�ֵ

u8 SOLGUI_CSR=0;		//ռ�ñ�־�Ĵ����������㼴��ʾռ�ã������˳���ǰҳ�棩
/*----------------��ռ�ñ�־�Ĵ�����------------------	
	SOLGUI_CSR[0]��	OK[���1]ռ��1������0
	SOLGUI_CSR[1]��	ȫ��ռ��1������0��Ҫռ��ȫ����
	SOLGUI_CSR[2]�� OK[���2]ռ��1���ر�0
-----------------------------------------------------*/

extern CURSOR *cursor;	//������

//##############################���ڲ�ʹ�á�##############################

void FIFO_Init(void)
{
//------------��FIFO�������㡿
	memset(_key_cache.FIFOBuffer,0,sizeof(_key_cache.FIFOBuffer));
//------------��FIFO��дָ�����㡿
	_key_cache.Read=0;
	_key_cache.Write=0;
}

void FIFO_EnQueue(u8 KeyCode)
{
	_key_cache.FIFOBuffer[_key_cache.Write]=KeyCode;
	if(++_key_cache.Write>=FIFOBUF_SIZE) _key_cache.Write=0;
}

u8 FIFO_DeQueue(void)
{
	u8 ret;
	if(_key_cache.Read==_key_cache.Write) return(FIFO_NONE); 	//FIFO��
	else
	{
		ret=_key_cache.FIFOBuffer[_key_cache.Read];
		if (++_key_cache.Read>=FIFOBUF_SIZE) _key_cache.Read=0;
		return(ret);
	}
} 

void SOLGUI_Menu_Title(MENU_PAGE *page)
{
	u8 left_len=0,title_len=0;

	title_len=6*(strlen((const char*)page->pageTitle)+4);					//����������ؿ�� 
	left_len=(SCREEN_X_WIDTH-title_len)>>1;									//�������ƫ������

//---------�����⡿
	SOLGUI_printf(left_len+2,56,F6X8,"[ %s ]",page->pageTitle);				//page.pageTitle  ҳ��������
	SOLGUI_GBasic_Line(6,57,left_len+2,57,ACTUAL);							//��������
	SOLGUI_GBasic_Line(left_len+title_len-2,57,SCREEN_X_WIDTH-7,57,ACTUAL);	//��������
//---------������ͼ�꡿
	if((page->parentPage!=PAGE_NULL)&&(SOLGUI_CSR==0)) SOLGUI_printf(0,56,F6X8,"%c",ICON_BACK);	//�и�ҳ�����ڷ�ռ��ģʽ�����������ͼ��

}

//##############################��API��##############################
void SOLGUI_Menu_SetHomePage(MENU_PAGE *home_page)	//��ҳ����
{
	current_page=home_page;
	FIFO_Init();
}

void SOLGUI_InputKey(u8 key_value) 					//������������ϵͳ�л�ȡ��ǰ������ֵ�������
{
	FIFO_EnQueue(key_value);
}

u8 SOLGUI_GetCurrentKey(void) 						//������������ȡGUI��ǰ��ȫ�ּ�ֵ
{
  	return(cur_key); 	
}

void SOLGUI_Menu_PageStage(void)					//����������SOLGUIǰ̨ҳ���л���
{
//------------------����ֵ��ȡ��
	cur_key=FIFO_DeQueue();							//�ӳ���ȡһ����ֵ��Ϊ��ǰGUI��ȫ�ּ�ֵ
//------------------��������ơ�
	SOLGUI_Menu_Title(current_page);				//����
//------------------��ִ��ҳ�溯����
	current_page->pageFunc();						//ִ��ҳ�溯��
	if(cur_key==SOLGUI_KEY_BACK&&SOLGUI_CSR==0){	//����Ƿ�Ϊ���ؼ�ֵ��CSR��ռ��
		if(current_page->parentPage!=PAGE_NULL)		//�и�ҳ��ſ�ʹ�÷��ؼ�
		{
			current_page=current_page->parentPage;	//�´�ִ�и�ҳ�溯��
			cursor->cursor_rel_offset=0;			//��չ��ƫ�Ƽ�����
			cursor->viewport_offset=0;
		}
	}
}

#endif
