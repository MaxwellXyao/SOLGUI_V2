#include "project_include.h"




//###############################【任务声明】###############################
//==========================[START 任务]============================
#define START_TASK_PRIO 43 				//设置任务优先级（开始任务的优先级设置为最低）
#define START_STK_SIZE 64			   	//设置任务堆栈大小
OS_STK START_TASK_STK[START_STK_SIZE];	//创建任务堆栈空间
void start_task(void *pdata);			//任务函数接口

//==========================[MAIN 任务]============================					
#define MAIN_TASK_PRIO 10				//设置任务优先级
#define MAIN_TASK_STK_SIZE 512			//设置任务堆栈大小
OS_STK MAIN_TASK_STK[MAIN_TASK_STK_SIZE];  //创建任务堆栈空间
void Main_task(void *pdata);			//任务函数接口

//########################################【变量】########################################

MENU_PAGE index,page_flagLightTest,page_KeyTest,page_fatfsTest;						//页面声明

//########################################【功能目录】########################################
__M_PAGE(index,"pixelC3",PAGE_NULL,{		//宏方式创建页面
	SOLGUI_Cursor(6,0,4);
	SOLGUI_Widget_GotoPage(0,&page_flagLightTest);
	SOLGUI_Widget_GotoPage(1,&page_KeyTest);
	SOLGUI_Widget_GotoPage(2,&page_fatfsTest);
});


//########################################【标志灯测试】########################################

__M_PAGE(page_flagLightTest,"Flaglight",&index,{		//宏方式创建页面
	SOLGUI_Cursor(6,0,3);
	SOLGUI_Widget_Button(0,"On",FlagLight_On);						
	SOLGUI_Widget_Button(1,"Off",FlagLight_Off);
	SOLGUI_Widget_Button(2,"Blink",FlagLight_Blink);
});

//########################################【按键测试】########################################

__M_PAGE(page_KeyTest,"Key",&index,{		//宏方式创建页面
	u8 k=0;
	static u8 k1=0;

	k=SOLGUI_GetCurrentKey();
	if(k!=0) k1=k;
	SOLGUI_Widget_Text(0,8,F6X8,"key=%X,switch=%X",k1,Switch_GetValue());
});

//########################################【FATFS测试】########################################
MENU_PAGE page_fatfsTest_SD,page_fatfsTest_Flash;

__M_PAGE(page_fatfsTest,"FATFS",&index,{		//宏方式创建页面
	SOLGUI_Cursor(6,0,2);
	SOLGUI_Widget_GotoPage(0,&page_fatfsTest_SD);
	SOLGUI_Widget_GotoPage(1,&page_fatfsTest_Flash);
});

//=========================================【FATFS测试_SD卡】

FATFS FatFs[2];   				//存放文件系统信息
FIL file,file1;	   				//存放文件信息
FRESULT f_res;			//FatFs通用结果码
unsigned int br,bw;				//读写变量
u8 SDdatabuff[100];	//SD卡数据缓存
u16 rlen;			//读取到数据长度
u8 SDtatus;			//SD卡初始化状态
u8 test_buff[]="This is FAFTS on SDCcard";
u8 test_buff1[]="This is FAFTS on flash";

void SD_f_mount_test(void)
{
	FlagLight_Blink();
	f_res = f_mount(SD_CARD,&FatFs[SD_CARD]);	//挂载SD卡
}

void SD_f_write_test(void)
{
	FlagLight_Blink();
	f_res = f_open(&file,"0:/ftest.txt",FA_OPEN_NEW_COVER);	
	f_res = f_write(&file, test_buff, sizeof(test_buff), &bw);	//写入字符串
	f_res = f_close(&file);	//关闭文件
}

void SD_f_open_test(void)
{
	FlagLight_Blink();
	f_res = f_open(&file,"0:/ftest.txt",FA_OPEN_READONLY);	//打开文件
	f_res = f_read(&file,SDdatabuff,80,&br);	//读取文件内容
	f_res = f_close(&file);	//关闭文件
}

__M_PAGE(page_fatfsTest_SD,"FATFS_SD",&page_fatfsTest,{		//宏方式创建页面
	SOLGUI_Cursor(6,5,3);
	SOLGUI_Widget_Button(0,"1.f_mount",SD_f_mount_test);						//按键
	SOLGUI_Widget_Button(1,"2.f_write",SD_f_write_test);						//按键
	SOLGUI_Widget_Button(2,"3.f_open",SD_f_open_test);						//按键
	SOLGUI_Widget_Text(0,32,~F6X8,"S=%d,r=%d,C=%d",SDtatus,f_res,SDCardInfo.CardCapacity);
	SOLGUI_Widget_Text(0,24,F6X8,"%s",SDdatabuff);
	SOLGUI_Widget_Text(0,16,F6X8,"%s",SDdatabuff+21);
	SOLGUI_Widget_Text(0,8,F6X8,"%s",SDdatabuff+42);
	SOLGUI_Widget_Text(0,0,F6X8,"%s",SDdatabuff+63);
});

//=========================================【FATFS测试_Flash】

void Flash_f_mkfs_test(void)
{
	f_mkfs(EX_FLASH,0,512);
}

void Flash_f_mount_test(void)
{
	FlagLight_Blink();
	f_res = f_mount(EX_FLASH,&FatFs[EX_FLASH]);	//挂载Flash
}

void Flash_f_write_test(void)
{
	FlagLight_Blink();
	f_res = f_open(&file1,"1:/ftest.txt",FA_OPEN_NEW_COVER);	
	f_res = f_write(&file1, test_buff1, sizeof(test_buff1), &bw);	//写入字符串
	f_res = f_close(&file1);	//关闭文件
}

void Flash_f_open_test(void)
{
	FlagLight_Blink();
	f_res = f_open(&file1,"1:/ftest.txt",FA_OPEN_READONLY);	//打开文件
	f_res = f_read(&file1,SDdatabuff,80,&br);	//读取文件内容
	f_res = f_close(&file1);	//关闭文件
}



		
__M_PAGE(page_fatfsTest_Flash,"FATFS_Flash",&page_fatfsTest,{		//宏方式创建页面
	SOLGUI_Cursor(6,5,4);
	SOLGUI_Widget_Button(0,"1.f_mkfs",Flash_f_mkfs_test);						//按键
	SOLGUI_Widget_Button(1,"2.f_mount",Flash_f_mount_test);						//按键
	SOLGUI_Widget_Button(2,"3.f_write",Flash_f_write_test);						//按键
	SOLGUI_Widget_Button(3,"4.f_open",Flash_f_open_test);						//按键
	SOLGUI_Widget_Text(0,32,~F6X8,"S=%d,r=%d",SDtatus,f_res);
	SOLGUI_Widget_Text(0,24,F6X8,"%s",SDdatabuff);
	SOLGUI_Widget_Text(0,16,F6X8,"%s",SDdatabuff+21);
	SOLGUI_Widget_Text(0,8,F6X8,"%s",SDdatabuff+42);
	SOLGUI_Widget_Text(0,0,F6X8,"%s",SDdatabuff+63);

});

//########################################【主任务】########################################
void Main_task(void *pdata)
{	
	u8 kv=0;

	pdata=pdata;		
	while(1)
	{
		kv=Key_GetValue();				//键值获取
		SOLGUI_InputKey(kv);			//键值输入
		SOLGUI_Menu_PageStage();	 	//前台
		SOLGUI_Refresh();				//更新屏幕
		delay_ms(30);
	}
}















//###############################【开始任务】###############################
void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr=0;
	pdata = pdata;

	OSStatInit(); //初始化统计任务.这里会延时 1 秒钟左右
	OS_ENTER_CRITICAL(); //进入临界区(无法被中断打断)
//-------------------[添加其他的任务初始化函数]

	OSTaskCreate(Main_task,(void *)0,(OS_STK*)&MAIN_TASK_STK[MAIN_TASK_STK_SIZE-1],MAIN_TASK_PRIO); 
	
	 
//---------------------------------------------
	OSTaskSuspend(START_TASK_PRIO); //挂起起始任务.
	OS_EXIT_CRITICAL(); //退出临界区(可以被中断打断)
}








//###############################【主函数】###############################

int main(void)
{		
	delay_init();
	FlagLight_Init();
	Flash_Init();
	Key_Init();						//按键扫描初始化
	SOLGUI_Init(&index);
	FlagLight_Blink();

	OSInit(); 			//UCOSII 初始化
	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO);//创建起始任务
	OSStart(); 										  
}
