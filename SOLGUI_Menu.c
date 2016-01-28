#include"SOLGUI_Include.h"
#include<string.h>


#if MENU_FRAME_EN==1
//##############################【全局变量定义】##############################
MENU_PAGE *current_page;//当前页面
GUI_FIFO _key_cache;	//键值FIFO

extern u8 CSR;		//当前状态寄存器

//##############################【内部使用】##############################

void FIFO_Init(void)
{
//------------【FIFO缓存清零】
	memset(_key_cache.FIFOBuffer,0,sizeof(_key_cache.FIFOBuffer));
//------------【FIFO读写指针清零】
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
	if(_key_cache.Read==_key_cache.Write) return(FIFO_NONE); 	//FIFO空
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

	title_len=6*(strlen((const char*)page->pageTitle)+4);					//计算标题像素宽度 
	left_len=(SCREEN_X_WIDTH-title_len)>>1;									//计算居中偏移像素

//---------【标题】
	SOLGUI_printf(left_len+2,56,F6X8,"[ %s ]",page->pageTitle);				//page.pageTitle  页面标题居中
	SOLGUI_GBasic_Line(0,57,left_len+2,57,DOTTED);							//标题线左
	SOLGUI_GBasic_Line(left_len+title_len-2,57,SCREEN_X_WIDTH-1,57,DOTTED);	//标题线右
//---------【返回图标】
	if(page->parentPage!=PAGE_NULL) SOLGUI_printf(0,56,F6X8,"%c",0x85);	//有父页面则输出返回图标

}

//##############################【API】##############################
void SOLGUI_Menu_SetHomePage(MENU_PAGE *home_page)	//首页定义
{
	current_page=home_page;
	FIFO_Init();
}

void SOLGUI_GetKeyValue(u8 key_value) 				//【非阻塞】从系统中获取当前按键键值存入FIFO
{
	FIFO_EnQueue(key_value);
} 

void SOLGUI_Menu_PageStage(void)					//【非阻塞】SOLGUI前台页面切换器
{
	u8 cur_key=0;
//------------------【界面绘制】
	SOLGUI_Menu_Title(current_page);
//------------------【执行页面函数】
	current_page->pageFunc();						//执行页面函数
	cur_key=FIFO_DeQueue();							//从FIFO中取一个键值
	if(cur_key==SOLGUI_KEY_BACK&&CSR==0){			//检查是否有返回键值且CSR为零（无占用）
		if(current_page->parentPage!=PAGE_NULL)		//有父页面才可使用返回键
		{
			current_page=current_page->parentPage;	//下次执行父页面函数
//			cursor_al=0;							//清空指针计数器
//			page_al=0;
		}
	}
}










#endif
