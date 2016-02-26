#ifndef SOLGUI_WIDGET_H


//##################################【mode宏定义】########################################

//------------【SPIN控件】
#define INTEGRAL	0x00	//整数的		
#define DECIMAL		0x01	//小数的


//------------【BAR控件】
//mode[0]  生长方向
#define DIREC_X		0x00	//x方向生长
#define DIREC_Y		0x01	//y方向生长
//mode[2:1]	外观类型		 
#define PROGBAR 	0x00	//进度条
#define SCALEBAR 	0x02	//刻度

//------------【PICTURE控件】
#define NML			0x00	//正常无附加
#define FRM			0x40	//mode[6]:边框开关
#define REV			0x80	//mode[7]:反白开关


//####################################【结构体定义】##########################################
//------------【光标结构体】
typedef struct _CURSOR{
	u8 cursor_rel_offset;	//光标相对视口的偏移
	u8 viewport_offset;		//视口的偏移
	u8 row_start;			//选项起始行（光标运动上界）
	u8 viewport_width;		//视口宽度
	u32 y_t;				//边界上坐标
	u32	y_b;				//边界下坐标
}CURSOR;					//光标类


//------------【EDIT控件】

typedef struct _IME_CLUSTER{ 
			u8 	finger;		//字符簇当前指向储存
	const 	u8 	*name;		//字符簇名
	const 	u8 	size;		//该字符簇容量
	const 	u8	*table;		//字符簇本体
}IME_CLUSTER;				//字符簇结构体

#define SOL_ASCII_IME_SIZE 5

typedef struct _EDIT_IME{
			u8 	finger;		//字符集当前指向储存 
	const 	u8 	size;	 	//字符集容量
	IME_CLUSTER *cluster[SOL_ASCII_IME_SIZE];	//字符集本体
}EDIT_IME;					//输入法字符集结构体




//####################################【API】##########################################
void SOLGUI_Cursor(u8 rowBorder_Top,u8 rowBorder_Bottom,u8 option_num);				//光标（上边界行，下边界行，选项个数）

//---------------【选项式控件】
void SOLGUI_Widget_GotoPage(u8 USN,MENU_PAGE *page);								//页面跳转
void SOLGUI_Widget_Spin(u8 USN,const u8 *name,u8 type,double max,double min,void* value);	//数字旋钮
void SOLGUI_Widget_OptionText(u8 USN,const u8* str,...);							//选项文本（太长的文字str会遮盖滚动条）
void SOLGUI_Widget_Button(u8 USN,const u8 *name,void (*func)(void));				//按键
void SOLGUI_Widget_Switch(u8 USN,const u8 *name,u32 *mem_value,u8 L_shift);			//变量开关（mem_value是一个外部申请的非易失性存储器变量）
void SOLGUI_Widget_Edit(u8 USN,const u8 *name,u16 char_num,u8 *buf);				//文本编辑器（char_num可修改长度）

//---------------【自由式控件】
void SOLGUI_Widget_Bar(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,s32 value,u8 mode);		//条
void SOLGUI_Widget_Spectrum(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,u16 val_num,s32 value[]);	//谱
void SOLGUI_Widget_Picture(u32 x0,u32 y0,u32 xsize,u32 ysize,const u8 *pic,u32 x_len,u32 y_len,u8 mode); //图片	
void SOLGUI_Widget_Text(u32 x,u32 y,u8 mode,const u8* str,...);			//文字（在该层应尽量避免调用printf）


#endif
