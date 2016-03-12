#ifndef SOLGUI_MENU_H
#define SOLGUI_MENU_H

#define PAGE_NULL 		0		//无页面
#define FIFO_NONE		0		//FIFO空

//##############################【页面函数信息结构体】##############################
//每个完整的页面包含页面函数和一个信息结构体（用来设置页面基本信息）
typedef struct __MENU_PAGE{									//菜单/函数类型
	const u8 *pageTitle;									//该层菜单的标题
	struct __MENU_PAGE *parentPage;							//该层菜单中的父菜单指针
	void (*pageFunc)();										//页面函数指针
}MENU_PAGE;

//可以用下方的自动化宏来定义页面

//------------【自动化宏】
#define __M_PAGE(name,pageTitle,parentPage,Program)	\
void _##name(){Program}								\
MENU_PAGE name={pageTitle,parentPage,_##name};

/*用法:
正常：
void _sub()
{
	SOLGUI_Cursor(0,1,8);
	SOLGUI_Widget_GotoPage(0,&test1);
	SOLGUI_Widget_Edit(2,"edit",1,test_str);								//文本编辑器
	SOLGUI_Widget_Spin(1,"t",INTEGRAL,-1000,1000,&t);
	SOLGUI_Widget_Spin(3,"t1",DECIMAL,1000,-1000,&t1);							 
}
MENU_PAGE sub={
	"sub_page",
	&index,
	_sub
};

对应的自动化宏：
__M_PAGE(页面变量名,页面标题,父页面地址,
{
	/////////////此处编写页面函数////////////
});


*/


//####################################【FIFO】##############################
//使用FIFO增强多任务异步情况下的稳定性
typedef struct __GUI_FIFO{
	u8 FIFOBuffer[FIFOBUF_SIZE];	   						//按键FIFO池
	u8 Read;												//缓冲区读指针				
	u8 Write;												//缓冲区写指针
}GUI_FIFO;													//FIFO类			

//####################################【内部使用】##########################################
void SOLGUI_Menu_SetHomePage(MENU_PAGE *home_page);	//首页定义

//####################################【API】##########################################
void SOLGUI_InputKey(u8 key_value); 				//【非阻塞】从系统中获取当前按键键值存入键池
u8 	 SOLGUI_GetCurrentKey(void); 					//【非阻塞】获取GUI当前的全局键值
void SOLGUI_Menu_PageStage(void);					//【非阻塞】SOLGUI前台页面切换器




#endif
