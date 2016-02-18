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

//------------【PICTURE控件】


//####################################【结构体定义】##########################################
//------------【光标结构体】
typedef struct _CURSOR{
	u8 cursor_rel_offset;	//光标相对视口的偏移
	u8 viewport_offset;		//视口的偏移
	u8 row_start;			//选项起始行（光标运动上界）
	u8 viewport_width;		//视口宽度
	u32 y_t;				//边界上坐标
	u32	y_b;				//边界下坐标
	u8 option_enable_list[OPTIONS_MAX];		//选项使能表,此处可以改进
}CURSOR;					//光标类




//------------【EDIT控件输入法结构体】
#define SOL_ASCII_IME_SIZE 5

typedef struct _IME_CLUSTER{ 
	u8 finger;			//字符簇当前指向储存
	const u8 *name;		//字符簇名
	const u8 size;		//该字符簇容量
	const u8 *table;	//字符簇本体
}IME_CLUSTER;			//字符簇结构体

typedef struct _EDIT_IME{
	u8 finger;					//字符集当前指向储存 
	const u8 size;	 			//字符集容量
	IME_CLUSTER cluster[SOL_ASCII_IME_SIZE];		//字符集本体
}EDIT_IME;				//输入法字符集结构体




//####################################【API】##########################################
void SOLGUI_Cursor(u8 rowBorder_Top,u8 rowBorder_Bottom,u8 option_num);				//光标（上边界行，下边界行，选项个数）

//---------------【选项式控件】
void SOLGUI_Widget_GotoPage(u8 USN,MENU_PAGE *page);								//页面跳转
void SOLGUI_Widget_Spin(u8 USN,const u8 *name,u8 type,double max,double min,void* value);	//数字旋钮
void SOLGUI_Widget_Text(u8 USN,const u8 *text);										//静态文本
void SOLGUI_Widget_Button(u8 USN,const u8 *name,void (*func)(void));				//按键
void SOLGUI_Widget_Switch(u8 USN,const u8 *name,u32 *mem_value,u8 L_shift,u8 mode);	//变量开关（mem_value是一个外部申请的非易失性存储器变量）
void SOLGUI_Widget_Edit(u8 USN,const u8 *name,u8 *buf);								//文本编辑器

//---------------【自由式控件】
void SOLGUI_Widget_Bar(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,s32 value,u8 mode);		//条
void SOLGUI_Widget_Spectrum(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,u16 val_num,s32 value[]);	//谱
void SOLGUI_Widget_Picture(u32 x0,u32 y0,u32 xsize,u32 ysize,const u8 *pic,u8 mode);				//图



#endif
