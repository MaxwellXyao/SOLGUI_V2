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

//####################################【FIFO】##############################
//使用FIFO增强多任务异步情况下的稳定性
typedef struct __GUI_FIFO{
	u8 FIFOBuffer[FIFOBUF_SIZE];	   						//按键FIFO池
	u8 Read;												//缓冲区读指针				
	u8 Write;												//缓冲区写指针
}GUI_FIFO;													//FIFO类			

//####################################【API】##########################################
void SOLGUI_Menu_SetHomePage(MENU_PAGE *home_page);	//首页定义
void SOLGUI_InputKey(u8 key_value); 				//【非阻塞】从系统中获取当前按键键值存入键池
u8 	 SOLGUI_GetCurrentKey(void); 					//【非阻塞】获取GUI当前的全局键值
void SOLGUI_Menu_PageStage(void);					//【非阻塞】SOLGUI前台页面切换器




#endif
