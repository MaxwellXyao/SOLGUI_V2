【SOL开源】SOLGUI_V2

定位：目前只考虑专用于OLED12864，场景是飞思卡尔智能车


目前进度：
1.将SOLGUI从pixelC的源码中独立出来编写，已完成底层的剥离。














====================================================

SOLGUI_V2改进计划


预想SOLGUI文件结构的划分：


SOLGUI_Config.h		//参数，设置开关
1.可以设置要使用的字体：6x8，5x7等


SOLGUI_Hardware.h	//硬件接口，供移植使用
SOLGUI_Hardware.c

---------------------------------------------------

*******************
SOLGUI_Common.c		//常用
SOLGUI_Common.h


SOLGUI初始化API
屏幕刷新函数
画点函数
清屏函数
//局部显示函数

屏幕相关的基本操作


*******************
SOLGUI_Printf.c		//字符显示
SOLGUI_Printf.h 


void SOLGUI_Show_Char();
void SOLGUI_Show_String();
void SOLGUI_printf();


*******************	
SOLGUI_Picture.c	//图片显示
SOLGUI_Picture.h


//带缩放


*******************
SOLGUI_GBasic.c		//基础图形
SOLGUI_GBasic.h 

void SOLGUI_Graph_line();
void SOLGUI_Graph_Circle();
//需要扩展

*******************	
SOLGUI_Plot.c 		//图表
SOLGUI_Plot.h 


void SOLGUI_Plot_Bar();
void SOLGUI_Plot_Oscillogram();
void SOLGUI_Plot_Waveform();
3.solgui图形plot函数组优化	


*******************	
SOLGUI_Menu.c		//菜单
SOLGUI_Menu.h


9.solgui_menu要把定义页面的结构体中的page和curcer改为全局变量。
10.SOLGUI_Menu.c下加入输入窗，可以用现有按键简易的输入ascii码
11.solgui_menu参数设置页添加布尔型输入选项，  >boolean  |  on






