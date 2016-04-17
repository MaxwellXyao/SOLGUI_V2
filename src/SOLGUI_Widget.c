#include"SOLGUI_Include.h"
#include<string.h>
#include<stdarg.h> 						//支持变长参数



//##############################【变量定义】##############################
#if WIDGET_EDIT_EN==1&&MENU_FRAME_EN==1

//-----------【EDIT】
const u8 SOL_ASCII_IME_lowerchar[]	="abcdefghijklmnopqrstuvwxyz";
const u8 SOL_ASCII_IME_upperchar[]	="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const u8 SOL_ASCII_IME_Number[]		="0123456789+-*/=%()[]{}<>&|~^";
const u8 SOL_ASCII_IME_symbol[]		=" .,:;_?!@#$'\"\\";
const u8 SOL_ASCII_IME_CRLchar[]	={0x00,0x0a,0x0d};	//控制类字符

IME_CLUSTER IME_CLUSTER_LC={0,"LOWER",26,SOL_ASCII_IME_lowerchar};		//大写字符簇
IME_CLUSTER IME_CLUSTER_UC={0,"UPPER",26,SOL_ASCII_IME_upperchar};		//小写字符簇
IME_CLUSTER IME_CLUSTER_NU={0,"NUMBER",28,SOL_ASCII_IME_Number};		//数字字符簇
IME_CLUSTER IME_CLUSTER_SY={0,"SYMBOL",14,SOL_ASCII_IME_symbol};		//符号字符簇
IME_CLUSTER IME_CLUSTER_CR={0,"CTRL",3,SOL_ASCII_IME_CRLchar};			//控制字符簇

EDIT_IME SOL_ASCII_IME_REG={		//简易ascii输入法
	0,								//字符集当前指向储存
	SOL_ASCII_IME_SIZE,				//字符集大小
   {&IME_CLUSTER_LC,
	&IME_CLUSTER_UC,
	&IME_CLUSTER_NU,
	&IME_CLUSTER_SY,
	&IME_CLUSTER_CR}
};

EDIT_IME *SOL_ASCII_IME=&SOL_ASCII_IME_REG;

#endif


#if MENU_FRAME_EN==1
/*选项编号向下生长：
   >option0
	option1
	option2
	...
*/
//-----------【光标类】
CURSOR cursor_reg={0,0,0,0,0,0};
CURSOR *cursor=&cursor_reg;			//光标全局信息记载

//-----------【选项使能表】
u8 option_enable_list[OPTIONS_MAX];	//选项使能表,此处可以改进

//-----------【GotoPage控件】
extern MENU_PAGE *current_page;		//当前页面

//-----------【占用标志寄存器】
extern u8 SOLGUI_CSR;		//设置模式控制寄存器

//################################【内部调用函数】##############################

boolean _OptionsDisplay_Judge(u8 USN)
{
	if((USN-cursor->viewport_offset)>=0&&((USN-cursor->viewport_offset)<=cursor->viewport_width))	
		return(True);	//显示选项	
	else return(False);	 //不显示选项	
}

u32 _OptionsDisplay_coorY(u8 USN)
{
	return((cursor->row_start-USN+cursor->viewport_offset)*8);
}

//################################【光标】##############################
//选项式控件必须有光标才能操作
void SOLGUI_Cursor(u8 rowBorder_Top,u8 rowBorder_Bottom,u8 option_num)		//光标（上边界行，下边界行，选项个数）	
{
	u8 i=0;
	u8 temp=0;
	u8 cur_key=0;
	u8 cursor_row=0;
	u8 cursor_abs_offset=0;	//光标的绝对偏移

	double s_h=0;			//滑块的高度
	u32 s_y=0;				//滑块的位置
//--------【参数过滤】
	if(rowBorder_Top<rowBorder_Bottom)		//默认上边界大于下边界，否则交换
	{
		temp=rowBorder_Top;
		rowBorder_Top=rowBorder_Bottom;
		rowBorder_Bottom=temp;
	}
	if(option_num>OPTIONS_MAX) option_num=OPTIONS_MAX;		//超过最大设为最大
//--------【相关参数计算】
	cursor->row_start=rowBorder_Top;	//设置选项起始行
	cursor->viewport_width=rowBorder_Top-rowBorder_Bottom; //视口行数计算
	if(option_num<=cursor->viewport_width) cursor->viewport_width=option_num-1;		//选项数小于视口宽度处理
//--------【键值解析】
	cur_key=SOLGUI_GetCurrentKey();										//获取当前全局键值
	if(cur_key==SOLGUI_KEY_UP){											//当前全局为上键
		if(cursor->cursor_rel_offset>0&&SOLGUI_CSR==0) cursor->cursor_rel_offset--;		//光标在视口内上移	   	
		else if(cursor->viewport_offset>0&&SOLGUI_CSR==0) cursor->viewport_offset--;	 	//视口上移	
	}
	else if(cur_key==SOLGUI_KEY_DOWN){								    //当前全局为下键
		if((cursor->cursor_rel_offset<cursor->viewport_width)&&SOLGUI_CSR==0) cursor->cursor_rel_offset++; //光标在视口内下移
		else if((cursor->viewport_offset<option_num-cursor->viewport_width-1)&&SOLGUI_CSR==0) cursor->viewport_offset++;	 //视口下移
	}
	cursor_abs_offset=cursor->viewport_offset+cursor->cursor_rel_offset;	//计算当前光标的绝对偏移
//--------【屏幕绘制】
	cursor->y_t=rowBorder_Top*8;									//顶y坐标
	cursor->y_b=rowBorder_Bottom*8;									//底y坐标
//---【光标】
	cursor_row=cursor->y_t-cursor->cursor_rel_offset*8;	 		//将光标相对视口的偏移换算成像素坐标
	SOLGUI_printf(0,cursor_row,F6X8,"%c",ICON_CURSOR);		//光标绘制
//---【上下边线】
	if(rowBorder_Top!=6) SOLGUI_GBasic_Line(0,cursor->y_t+8,SCREEN_X_WIDTH-1,cursor->y_t+8,DOTTED);		//上边线
	if(rowBorder_Top!=0) SOLGUI_GBasic_Line(0,cursor->y_b-1,SCREEN_X_WIDTH-1,cursor->y_b-1,DOTTED);		//下边线
//---【滚动条】（可以作为选择添加的部分）
	s_h=(double)(cursor->y_t-cursor->y_b+8)/(double)option_num;									//滑块高度
	s_y=cursor->y_t+7-s_h*(cursor_abs_offset+1);										//滑块位置
	SOLGUI_GBasic_Rectangle(SCREEN_X_WIDTH-4,s_y,SCREEN_X_WIDTH-1,s_y+s_h,FILL);	//滑块
	SOLGUI_GBasic_Rectangle(SCREEN_X_WIDTH-4,cursor->y_b,SCREEN_X_WIDTH-1,cursor->y_t+7,ACTUAL);	//边框
//--------【修改选项使能表】			
	for(i=0;i<=option_num;i++){
		option_enable_list[i]=(cursor_abs_offset==i)?1:0;	//填写选项使能表，在绝对偏移位置上为1，其余位置为0；
	}
}

#endif

//##############################【选项式控件】##############################


#if WIDGET_GOTOPAGE_EN==1&&MENU_FRAME_EN==1

void SOLGUI_Widget_GotoPage(u8 USN,MENU_PAGE *page)		//页面跳转控件
{
	u32 y_disp=0;	//该选项应该显示的行位置
	u8 cur_key=0;	//键值
	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//全屏占用
//--------【参数过滤】
	if(USN>=OPTIONS_MAX) return;		//USN只允许取0~OPTIONS_MAX-1
//--------【计算显示行】
	if(True==_OptionsDisplay_Judge(USN))
	{		
		y_disp=_OptionsDisplay_coorY(USN);
		if(option_enable_list[USN]==1)
		{
//--------【键值解析】
			cur_key=SOLGUI_GetCurrentKey();				//获取当前全局键值
			if(cur_key==SOLGUI_KEY_OK){					//OK键			
				current_page=page;						//跳转
				cursor->cursor_rel_offset=0;					//清空光标偏移计数器
				cursor->viewport_offset=0;											
			}					
		}
//--------【选项绘制】
		SOLGUI_printf(6,y_disp,F6X8,"%s",page->pageTitle);		//下一个页面标题
		SOLGUI_printf(SCREEN_X_WIDTH-13,y_disp,F6X8,"%c",ICON_WIDGET_GOTOPAGE);	//图标
//--------【操作提示绘制】
		if((cursor->viewport_offset+cursor->cursor_rel_offset)==USN)
		SOLGUI_printf(SCREEN_X_WIDTH-6,56,F6X8,"%c",ICON_OK);	//操作指示（根据键值解析部分来编写）
	}
}

#endif


#if WIDGET_SPIN_EN==1&&MENU_FRAME_EN==1

double _Pow_10(s8 n) 	//pow=10^n
{
	s16 i=0;
	s8 m=(n>=0)?n:-n;
	double p=1;

	for(i=0;i<m;i++)
	{
		if(n>=0) p*=10;
		else p*=0.1;
	}
	return(p);
}

void SOLGUI_Widget_Spin(u8 USN,const u8 *name,u8 type,double max,double min,void* value)		//数字旋钮控件
{
	double swap;	
	u32 y_disp=0;	//该选项应该显示的行位置
	u8 cur_key=0;	//键值

	static s8 spin_pos=0;	//旋钮位置
	double dat_step=0;

	s8		*v_i8=NULL;
	u8		*v_u8=NULL;
	s16		*v_i16=NULL;
	s32		*v_i32=NULL;
	float 	*v_f16=NULL;
	double	*v_f32=NULL;

	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//全屏占用
//--------【参数过滤】
	if(max<min)
	{
		swap=max;
		max=min;
		min=swap;
	}
	if(USN>=OPTIONS_MAX) return;		//USN只允许取0~OPTIONS_MAX-1
//--------【参数准备】
	switch(type)
	{
		case INT8:	v_i8=(s8 *)value;break;
		case UINT8:	v_u8=(u8 *)value;break;  
		case INT32: v_i32=(s32 *)value; break;
		case FLT16: v_f16=(float *)value; break;
		case FLT32: v_f32=(double *)value; break;
		case INT16: ;	
		default:	v_i16=(s16 *)value; break;
	}
//--------【计算显示行】
	if(True==_OptionsDisplay_Judge(USN))
	{		
		y_disp=_OptionsDisplay_coorY(USN);
		if(option_enable_list[USN]==1)
		{
//--------【键值解析】
			cur_key=SOLGUI_GetCurrentKey();				//获取当前全局键值
			if(cur_key==SOLGUI_KEY_OK){					//OK键			
				SOLGUI_CSR^=bit(0);						//CSR[0]翻转，置1表示SPIN占用									
			}
			if(bit_istrue(SOLGUI_CSR,bit(0)))			//如果处于SPIN占用中
			{
				dat_step=_Pow_10(spin_pos);				//计算调节步进值

				if(cur_key==SOLGUI_KEY_UP)														//数值加步进
				{
					switch(type)
					{
						case INT8:	{if(((*v_i8)+dat_step)<=max)(*v_i8)+=(s8)dat_step;}break;
						case UINT8:	{if(((*v_u8)+dat_step)<=max)(*v_u8)+=(u8)dat_step;}break;  
						case INT32: {if(((*v_i32)+dat_step)<=max)(*v_i32)+=(s32)dat_step;}break;
						case FLT16: {if(((*v_f16)+dat_step)<=max)(*v_f16)+=(float)dat_step;}break;
						case FLT32: {if(((*v_f32)+dat_step)<=max)(*v_f32)+=(double)dat_step;}break;
						case INT16: ;	
						default:	{if(((*v_i16)+dat_step)<=max)(*v_i16)+=(s16)dat_step;}break;
					}	
				}
				else if(cur_key==SOLGUI_KEY_DOWN)												//数值减步进
				{
					switch(type)
					{
						case INT8:	{if(((*v_i8)-dat_step)>=min)(*v_i8)-=(s8)dat_step;}break;
						case UINT8:	{if(((*v_u8)-dat_step)>=min)(*v_u8)-=(u8)dat_step;}break;  
						case INT32: {if(((*v_i32)-dat_step)>=min)(*v_i32)-=(s32)dat_step;}break;
						case FLT16: {if(((*v_f16)-dat_step)>=min)(*v_f16)-=(float)dat_step;}break;
						case FLT32: {if(((*v_f32)-dat_step)>=min)(*v_f32)-=(double)dat_step;}break;
						case INT16: ;	
						default:	{if(((*v_i16)-dat_step)>=min)(*v_i16)-=(s16)dat_step;}break;
					}	
				}
				else if(cur_key==SOLGUI_KEY_LEFT)												//左步进
				{
					if(spin_pos<SPIN_DIGIT_MAX-1) spin_pos++;						
				}
				else if(cur_key==SOLGUI_KEY_RIGHT)												//右步进
				{
					if((type==FLT16)||(type==FLT32)) { if(spin_pos>SPIN_DIGIT_MIN) spin_pos--; }	 //小数
					else { if(spin_pos>0) spin_pos--; }		//其他默认做整数处理（待扩展）
				}
			}				
		}
//--------【选项：变量名&数值绘制】
		switch(type)
		{
			case INT8:	SOLGUI_printf(68,y_disp,F6X8,"%d",*v_i8);break;
			case UINT8:	SOLGUI_printf(68,y_disp,F6X8,"%d",*v_u8);break; 
			case INT32: SOLGUI_printf(68,y_disp,F6X8,"%d",*v_i32);break;
			case FLT16: SOLGUI_printf(68,y_disp,F6X8,"%f",*v_f16);break;
			case FLT32: SOLGUI_printf(68,y_disp,F6X8,"%f",*v_f32);break;
			case INT16: ;	
			default:	SOLGUI_printf(68,y_disp,F6X8,"%d",*v_i16);break;
		}

								
//--------【旋钮绘制】
		if(bit_istrue(SOLGUI_CSR,bit(0))&&(option_enable_list[USN]==1)) 
		SOLGUI_printf(0,y_disp,~F6X8,"%c%f%c",ICON_LEFT,dat_step,ICON_RIGHT);	   	//如果处于设置模式中，显示旋钮数值
		else SOLGUI_printf(6,y_disp,F6X8,"%s",name);		//变量名
//--------【操作提示绘制】
		if((cursor->viewport_offset+cursor->cursor_rel_offset)==USN)
		SOLGUI_printf(SCREEN_X_WIDTH-6,56,F6X8,"%c",ICON_OK);			//操作指示（根据键值解析部分来编写）
	}	
}

#endif



#if WIDGET_OPTIONTEXT_EN==1&&MENU_FRAME_EN==1

void SOLGUI_Widget_OptionText(u8 USN,const u8* str,...)					//选项文本
{
	va_list ap;
	u32 y_disp=0;	//该选项应该显示的行位置
//	u8 t[SCREEN_X_PAGE-2];		//字符缓存
	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//全屏占用
//--------【参数过滤】
	if(USN>=OPTIONS_MAX) return;		//USN只允许取0~OPTIONS_MAX-1
//	_String_LenCtrlCpy(SCREEN_X_PAGE-2,t,(u8 *)str);
//--------【计算显示行】
	if(True==_OptionsDisplay_Judge(USN))
	{		
		y_disp=_OptionsDisplay_coorY(USN);
//--------【选项绘制】
		va_start(ap,str);
		__SOLGUI_printf(6,y_disp,F6X8,str,ap);		//文本显示
		va_end(ap);
	}
}

#endif


#if WIDGET_BUTTON_EN==1&&MENU_FRAME_EN==1

void SOLGUI_Widget_Button(u8 USN,const u8 *name,void (*func)(void))				//按键
{
	u32 y_disp=0;	//该选项应该显示的行位置
	u8 cur_key=0;	//键值
	u8 run_f=0;		//运行记号
	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//全屏占用
//--------【参数过滤】
	if(USN>=OPTIONS_MAX) return;		//USN只允许取0~OPTIONS_MAX-1
//--------【计算显示行】
	if(True==_OptionsDisplay_Judge(USN))
	{		
		y_disp=_OptionsDisplay_coorY(USN);
		if(option_enable_list[USN]==1)
		{
//--------【键值解析】
			cur_key=SOLGUI_GetCurrentKey();				//获取当前全局键值
			if(cur_key==SOLGUI_KEY_OK){					//OK键			
				run_f=1;								
			}					
		}
//--------【选项绘制】
		SOLGUI_printf(6,y_disp,F6X8,"%s",name);					//选项名
		SOLGUI_printf(68,y_disp,F6X8,"->");						//图标
//--------【运行牵连函数】		
		if(run_f==1) 											//按下OK键，运行牵连函数
		{
			run_f=0;											//只运行一次
			func();	
		}
//--------【操作提示绘制】
		if((cursor->viewport_offset+cursor->cursor_rel_offset)==USN)
		SOLGUI_printf(SCREEN_X_WIDTH-6,56,F6X8,"%c",0x84);			//操作指示（根据键值解析部分来编写）
	}
}

#endif



#if WIDGET_SWITCH_EN==1&&MENU_FRAME_EN==1

void SOLGUI_Widget_Switch(u8 USN,const u8 *name,u32 *mem_value,u8 L_shift)		//变量开关（mem_value是一个外部申请的非易失性存储器变量）
{
	u32 y_disp=0;	//该选项应该显示的行位置
	u8 cur_key=0;	//键值
	u32 temp=bit(L_shift);
	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//全屏占用
//--------【参数过滤】
	if((L_shift<1)||(L_shift>32)) L_shift=1;	//小于1或大于32都划归为1
	if(USN>=OPTIONS_MAX) return;		//USN只允许取0~OPTIONS_MAX-1
//--------【计算显示行】
	if(True==_OptionsDisplay_Judge(USN))
	{		
		y_disp=_OptionsDisplay_coorY(USN);
		if(option_enable_list[USN]==1)
		{
//--------【键值解析】
			cur_key=SOLGUI_GetCurrentKey();				//获取当前全局键值
			if(cur_key==SOLGUI_KEY_OK){					//OK键			
				(*mem_value)^=temp;			//需要外部非易失性储存空间来存放这个标志位，对其某位取反									
			}					
		}
//--------【选项绘制】
		SOLGUI_printf(6,y_disp,F6X8,"%s",name);						//选项名
//--------【图标绘制】
		if(bit_istrue((*mem_value),temp)) SOLGUI_printf(68,y_disp,F6X8,"[ON ]");				//"开"文字	
		else SOLGUI_printf(68,y_disp,F6X8,"[OFF]");												//"关"文字
//--------【操作提示绘制】
		if((cursor->viewport_offset+cursor->cursor_rel_offset)==USN)
		SOLGUI_printf(SCREEN_X_WIDTH-6,56,F6X8,"%c",0x84);			//操作指示（根据键值解析部分来编写）
	}	
}

#endif


#if WIDGET_EDIT_EN==1&&MENU_FRAME_EN==1

void _String_LenCtrlCpy(u16 dest_size,u8 *dest,u8 *sour)		  	//带字数限制的复制
{
	if(strlen((const char *)sour)>dest_size) strncpy((char *)dest,(char *)sour,dest_size);	 
	else strcpy((char *)dest,(char *)sour);	
}

void SOLGUI_Widget_Edit(u8 USN,const u8 *name,u16 char_num,u8 *buf)			//文本编辑器
{	
	u32 y_disp=0;	//该选项应该显示的行位置
	u8 cur_key=0;	//键值
	u16 i=0,j=0,buf_i=0;
	u8 edit_thumbnail_buf[EDIT_THUMBNAIL_SIZE];	//缩略内容
	static u8 edit_buf[EDIT_BUF_SIZE];			//编辑器缓存buf	
	static u16 edit_cursor_row=0;				//编辑器光标横字符位置
	static u16 edit_cursor_col=0;				//编辑器光标纵字符位置
	u16 edit_buf_size_temp=char_num<EDIT_BUF_SIZE?(char_num+1):EDIT_BUF_SIZE;
//--------【参数过滤】
	if(USN>=OPTIONS_MAX) return;		//USN只允许取0~OPTIONS_MAX-1
	
//--------【计算显示行】
	if(True==_OptionsDisplay_Judge(USN))
	{		
		y_disp=_OptionsDisplay_coorY(USN);
		if(option_enable_list[USN]==1)
		{
//--------【键值解析：进入EDIT占用】
			cur_key=SOLGUI_GetCurrentKey();				//获取当前全局键值
			if(cur_key==SOLGUI_KEY_OK){					//OK键
//--------【光标指在(0,0)位置】
				if((edit_cursor_row==0)&&(edit_cursor_col==0)) 	 //如果光标指字符(0,0)位
				{
					if(bit_istrue(SOLGUI_CSR,bit(1)))	//如果在编辑状态下
					{
						SOLGUI_CSR&=(~bit(1));					//CSR[1]=0，置0表示EDIT占用解除
						_String_LenCtrlCpy(char_num,buf,edit_buf);	//向上更新buf
					}
					else
					{
						SOLGUI_CSR|=bit(1);					//CSR[1]=1，置0表示EDIT占用
						memset(edit_buf,0,sizeof(edit_buf));			//edit_buf清零
						_String_LenCtrlCpy(edit_buf_size_temp,edit_buf,buf);
					}
				}										
				else
				{
//--------【光标指在其他字符位置，按下开关输入法】
					SOLGUI_CSR^=bit(2);						//CSR[2]翻转，置1表示输入法占用
				}
			}
			if(bit_istrue(SOLGUI_CSR,bit(1)))			//如果处于EDIT占用状态下
			{
				buf_i=(SCREEN_X_PAGE-2)*edit_cursor_col+edit_cursor_row;	//修改位置计算	
//--------【键值解析：EDIT占用下的操作】
				if(cur_key==SOLGUI_KEY_UP)								//光标向上&字符加
				{
					if(bit_istrue(SOLGUI_CSR,bit(2)) && (SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->finger
					< SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->size-1))
						SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->finger++;//输入法下	
					else if(bit_isfalse(SOLGUI_CSR,bit(2))&&edit_cursor_col>0) 
						edit_cursor_col--;										//纵光标减
				}
				else if(cur_key==SOLGUI_KEY_DOWN)								//光标向下&字符减
				{
					if(bit_istrue(SOLGUI_CSR,bit(2)) && (SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->finger>0))
						SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->finger--;//输入法上	
					else if(bit_isfalse(SOLGUI_CSR,bit(2))&&edit_cursor_col<(SCREEN_Y_PAGE-4)
					&& ((buf_i+(SCREEN_X_PAGE-2))<edit_buf_size_temp)) 
						edit_cursor_col++;										//纵光标加
				}
				else if(cur_key==SOLGUI_KEY_LEFT)						//光标向左&字符类型左切换
				{
					if(bit_istrue(SOLGUI_CSR,bit(2))&&(SOL_ASCII_IME->finger>0)) SOL_ASCII_IME->finger--;	 //输入法换簇左
					else if(bit_isfalse(SOLGUI_CSR,bit(2))&&edit_cursor_row>0) edit_cursor_row--;			//横光标减
				}
				else if(cur_key==SOLGUI_KEY_RIGHT)						//光标向左&字符类型右切换
				{
					if(bit_istrue(SOLGUI_CSR,bit(2))&&(SOL_ASCII_IME->finger<SOL_ASCII_IME->size-1)) SOL_ASCII_IME->finger++; //输入法换簇右	
					else if(bit_isfalse(SOLGUI_CSR,bit(2))&&edit_cursor_row<(SCREEN_X_PAGE-3)&&((buf_i+1)<edit_buf_size_temp)) 
						edit_cursor_row++;//横光标加
				}
			}				
		}
//--------【选项：变量名&数值绘制】
		if(bit_istrue(SOLGUI_CSR,bit(1)))
		{
//----【在EDIT占用下，显示编辑窗（全屏占用）】
//----[绘制编辑框]
			SOLGUI_Clean();					//软清屏
			SOLGUI_GBasic_Rectangle(0,0,SCREEN_X_WIDTH-1,SCREEN_Y_WIDTH-1,ACTUAL);		//边框
			SOLGUI_GBasic_Line(0,9,SCREEN_X_WIDTH-1,9,ACTUAL);						//底部的线
			if(bit_istrue(SOLGUI_CSR,bit(2)))										//字符编辑状态
			{
				edit_buf[buf_i-1]=SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->table[SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->finger];	//字符串赋值
				SOLGUI_printf(2,1,F6X8,"%s",SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->name);	   //字符簇名
				SOLGUI_printf(64,1,F6X8,"[ %c ]",SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->table[SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->finger]);
			}
			else if((edit_cursor_col==0)&&(edit_cursor_row==0))		 	//底栏显示
			{
				SOLGUI_printf(2,1,F6X8,"BACK");							//光标指向back位置
			}
			else
			{
				SOLGUI_printf(2,1,F6X8,"L:%d C:%d",edit_cursor_col+1,edit_cursor_row+1); //光标指向可编辑字符位置
			}
//----[内容显示]
			for(i=0;i<(SCREEN_Y_PAGE-3);i++)
			{
				for(j=0;j<(SCREEN_X_PAGE-2);j++)
				{
					if(i==0&&j==0)
					{
//----[控制位显示(0,0)]
						if((edit_cursor_row==0)&&(edit_cursor_col==0)) 
							SOLGUI_printf(6,48,~F6X8,"%c",ICON_BACK);			//确认操作指示，字符坐标(0,0)反白
						else SOLGUI_printf(6,48,F6X8,"%c",ICON_BACK);			
					}
					else
					{
//----[其他字符显示]
						buf_i=(SCREEN_X_PAGE-2)*i+j-1;			//光标指着的位置
						if(buf_i<edit_buf_size_temp)
						{
							if((edit_cursor_row==j)&&(edit_cursor_col==i))					//如果指向该字符 
							{
								if(edit_buf[buf_i]=='\0') SOLGUI_printf(6+j*6,48-i*8,~F6X8,"%c",ICON_OTHER_HIDE);	//'\0'用'...'来表示，即可编辑区域
								else SOLGUI_printf(6+j*6,48-i*8,~F6X8,"%c",edit_buf[buf_i]);			//选中的字反白显示
							}
							else 
							{	
								if(edit_buf[buf_i]=='\0') SOLGUI_printf(6+j*6,48-i*8,F6X8,"%c",ICON_OTHER_HIDE);   //'\0'用'...'来表示，即可编辑区域
								else SOLGUI_printf(6+j*6,48-i*8,F6X8,"%c",edit_buf[buf_i]);
							}
						}
						else 
						{
							i=SCREEN_Y_PAGE; j=SCREEN_X_PAGE;	//跳出循环
						}
					}
				}
			}												
		}
		else
		{
//----【不在EDIT占用下，显示选项】
			SOLGUI_printf(6,y_disp,F6X8,"%s",name);		//变量名
			_String_LenCtrlCpy(EDIT_THUMBNAIL_SIZE,edit_thumbnail_buf,buf);	//向缩略信息数组中复制
			SOLGUI_printf(68,y_disp,F6X8,"%s",edit_thumbnail_buf);			//缩略内容显示
			if(strlen((const char *)buf)>(SCREEN_X_PAGE-14))SOLGUI_printf(SCREEN_X_WIDTH-19,y_disp,F6X8,"%c",ICON_OTHER_HIDE);	//内容隐藏图标
			SOLGUI_printf(SCREEN_X_WIDTH-13,y_disp,F6X8,"%c",ICON_WIDGET_EDIT);	//EDIT图标
		}
//--------【操作提示绘制】
		if((cursor->viewport_offset+cursor->cursor_rel_offset)==USN)
		SOLGUI_printf(SCREEN_X_WIDTH-6,56,F6X8,"%c",ICON_OK);			//操作指示（根据键值解析部分来编写）
	}	
}

#endif

//##############################【自由式控件】##############################

#if WIDGET_TEXT_EN==1&&MENU_FRAME_EN==1

void SOLGUI_Widget_Text(u32 x0,u32 y0,u8 mode,const u8* str,...)
{
	va_list ap;
//--------【当前状态】
	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//全屏占用
//--------【文字输出】
	va_start(ap,str);
	__SOLGUI_printf(x0,y0,mode,str,ap); 		//使用内部printf来传递变长参数
	va_end(ap);	
}

#endif


#if WIDGET_BAR_EN==1&&MENU_FRAME_EN==1

void SOLGUI_Widget_Bar(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,s32 value,u8 mode)		//条
{
	s32 swap=0;
	double f=0;
	u32 d=0;

//--------【当前状态】
	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//全屏占用
//--------【参数过滤】
	if(max<min)
	{
		swap=max;
		max=min;
		min=swap;
	}
	value=(value<max)?value:max;
	value=(value>min)?value:min;

//----------【计算每格步长】
	f=(double)(value-min)/(double)(max-min);
//----------【绘制x生长的条】
	if((mode&0x01)==DIREC_X)				//x生长
	{
		d=f*xsize;
		if((mode&0x06)==PROGBAR) 			//进度条
		{
			SOLGUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+ysize,ACTUAL);
			SOLGUI_GBasic_Rectangle(x0,y0,x0+d,y0+ysize,FILL);		
		}
		else if((mode&0x06)==SCALEBAR)		//刻度
		{
			SOLGUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+ysize,ACTUAL);
			SOLGUI_GBasic_Rectangle(x0,y0,x0+d,y0+ysize,ACTUAL);
			SOLGUI_GBasic_Line(x0,y0+ysize,x0+xsize,y0+ysize,DELETE);
		}
	}
	else									//y生长
	{
//----------【绘制y生长的条】		
		d=f*ysize;
		if((mode&0x06)==PROGBAR) 			//进度条
		{
			SOLGUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+ysize,ACTUAL);
			SOLGUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+d,FILL);
		}
		else if((mode&0x06)==SCALEBAR)		//刻度
		{
			SOLGUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+ysize,ACTUAL);
			SOLGUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+d,ACTUAL);
			SOLGUI_GBasic_Line(x0,y0,x0,y0+ysize,DELETE);
		}
	}
}

#endif


#if MENU_FRAME_EN==1&&(WIDGET_SPECTRUM_EN==1||WIDGET_OSCILLOGRAM_EN==1)

void SOLGUI_Widget_Spectrum(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,u16 val_num,s32 value[])
{
	s32 swap=0;
	u16 i=0;
	double delta_x=0,delta_y=0;
	double x_p=0;
	u32 x_last=x0,y_last=y0,y_zero=0;
	s32 val_now=0;

	u32 x_now=0,y_now=0;

//--------【当前状态】
	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//全屏占用
//--------【参数过滤】
	if(max<min)
	{
		swap=max;
		max=min;
		min=swap;
	}
//------------【相关计算】
	delta_x=(double)(val_num)/(double)(xsize);		//计算
	delta_y=(double)(ysize)/(double)(max-min);		//计算一个像素是多少值
//------------【曲线绘制】
	for(i=0;i<xsize;i++)
	{
		x_p+=delta_x;
		val_now=value[(int)x_p];
		x_now=x0+i;
		if((val_now>=min)&&(val_now<max)) y_now=y0+(u32)((val_now-min)*delta_y);
		else if(val_now<min) y_now=y0;
		else y_now=y0+ysize-1;
		SOLGUI_GBasic_Line(x_last,y_last,x_now,y_now,ACTUAL);
		x_last=x_now;
		y_last=y_now;	
	}
//------------【外框绘制】
	SOLGUI_GBasic_Rectangle(x0,y0,x0+xsize-1,y0+ysize-1,ACTUAL);
//------------【零点绘制】
	if(min<0)
	{
		y_zero=y0+(u32)((-min)*delta_y);
		SOLGUI_DrawPoint(x0+1,y_zero,1);
	}	
}

#endif


#if WIDGET_OSCILLOGRAM_EN==1&&MENU_FRAME_EN==1

void SOLGUI_Widget_Oscillogram(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,WaveMemBlk *wmb)	  //波，要通过探针输入数据更新
{
//--------【当前状态】
	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//全屏占用
//--------【绘图】
	SOLGUI_Widget_Spectrum(x0,y0,xsize,ysize,max,min,wmb->size,wmb->mem);	//调用谱绘制波形
}

void SOLGUI_Oscillogram_Probe(WaveMemBlk *wmb,s32 value)									//探针
{
	u16 f=0,b=1;
//--------【数据队列操作】				
	for(f=0,b=1;b<wmb->size;f++,b++){
		wmb->mem[f]=wmb->mem[b];				//数组移位,O(n)
	}
	wmb->mem[wmb->size-1]=value;				//末尾添加新数据	
}

#endif


#if WIDGET_PICTURE_EN==1&&MENU_FRAME_EN==1

void SOLGUI_Widget_Picture(u32 x0,u32 y0,u32 xsize,u32 ysize,const u8 *pic,u32 x_len,u32 y_len,u8 mode)	//带缩小适配的图片控件 
{
	float fw=0,fh=0;
	u16 temp_x=0,temp_y=0;
	u16 y_i=0,x_i=0;
	u32 y0_t=y0+ysize;	//将原点改为左下角（原本原点为右上角）
	u8 m1=0;
//--------【当前状态】
	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//全屏占用
	m1=bit_isfalse(mode,bit(7));				//是否反白
//------------【图片直出绘制】
	if((xsize>=x_len)&&(ysize>=y_len)) 
		SOLGUI_Pictrue(x0,y0,pic,x_len,y_len,m1);
	else {
//------------【图片适配大小绘制】
		fw=(float)x_len/xsize; fh=(float)y_len/ysize;	//缩小比
		for(x_i=0;x_i<xsize;x_i++)
		{
			temp_x=(u16)(fw*x_i);		 //临近插值缩放算法
			for(y_i=0;y_i<ysize;y_i++)
			{
				temp_y=(u16)(fh*y_i);		  
			   	if(SOLGUI_GetPixel(temp_x,temp_y,pic,x_len,y_len)) SOLGUI_DrawPoint(x0+x_i,y0_t-y_i,m1);
			   	else SOLGUI_DrawPoint(x0+x_i,y0_t-y_i,!m1);
			}
		}
	};	
//-----【边框绘制】
	if(bit_istrue(mode,bit(6))) SOLGUI_GBasic_Rectangle(x0,y0,x0+xsize-1,y0+ysize-1,ACTUAL);
}

#endif




