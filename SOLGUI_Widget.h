#ifndef SOLGUI_WIDGET_H


//##################################【mode宏定义】########################################

//------------【SPIN控件】
#define INTEGRAL	0x00	//整数的		
#define DECIMAL		0x01	//小数的

//------------【SWITCH控件】
#define ONxOFF1	  	0x00	//文字式
#define ONxOFF2 	0x01	//亮灭式
#define ONxOFF3		0x02	//勾叉式


//------------【BAR控件】
/*---------------------
	mode[0]		生长方向
	mode[2:1]	外观类型
---------------------*/
//mode[0]
#define DIREC_X		0x00	//x方向生长
#define DIREC_Y		0x01	//y方向生长
//mode[2:1]			 
#define PROGBAR 	0x00	//进度条
#define SCALEBAR 	0x02	//刻度





//####################################【API】##########################################
void SOLGUI_Cursor(u8 rowBorder_Top,u8 rowBorder_Bottom,u8 option_num);		//光标（上边界行，下边界行，选项个数）
//---------------【选项式控件】
void SOLGUI_Widget_GotoPage(u8 USN,MENU_PAGE *page);						//页面跳转
void SOLGUI_Widget_Spin(u8 USN,const u8 *name,u8 type,double max,double min,void* value);	//数字旋钮
void SOLGUI_Widget_Text(u8 USN,const u8 *text);								//文本
void SOLGUI_Widget_Button(u8 USN,const u8 *name,void (*func)(void));		//按键
void SOLGUI_Widget_Switch(u8 USN,const u8 *name,u32 *mem_value,u8 L_shift,u8 mode);	//变量开关（mem_value是一个外部申请的非易失性存储器变量）

//---------------【自由式控件】
void SOLGUI_Widget_Bar(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,s32 value,u8 mode);		//条



#endif
