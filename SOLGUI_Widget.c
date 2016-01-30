#include"SOLGUI_Include.h"

#if MENU_FRAME_EN==1
//##############################【变量定义】##############################
//-----------【状态寄存器】
u8 SOLGUI_CSR=0;		//设置模式控制寄存器（1在设置模式中，0空闲）
//-----------【光标偏移计数器】
/*选项编号向下生长*/
u8 cursor_rel_offset=0;	//光标相对视口的偏移
u8 viewport_offset=0;	//视口的偏移
//-----------【光标位置计算】
u8 row_start=0;			//选项起始行（光标运动上界）
u8 viewport_width=0;	//视口宽度

//-----------【选项使能表】
u8 option_enable_list[OPTIONS_MAX];		//选项使能表,此处可以改进


//-----------【GotoPage控件】
extern MENU_PAGE *current_page;//当前页面

//################################【光标】##############################
//选项式控件必须有光标才能操作
void SOLGUI_Cursor(u8 rowBorder_Top,u8 rowBorder_Bottom,u8 option_num)		//光标（上边界行，下边界行，选项个数）	
{
	u8 i=0;
	u8 temp=0;
	u8 cur_key=0;
	u8 cursor_row=0;
	u8 cursor_abs_offset=0;	//光标的绝对偏移

	u32 y_t=0,y_b=0;
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
	row_start=rowBorder_Top;	//设置选项起始行
	viewport_width=rowBorder_Top-rowBorder_Bottom; //视口行数计算
	if(option_num<=viewport_width) viewport_width=option_num-1;		//选项数小于视口宽度处理
//--------【键值解析】
	cur_key=SOLGUI_GetCurrentKey();										//获取当前全局键值
	if(cur_key==SOLGUI_KEY_UP){											//当前全局为上键
		if(cursor_rel_offset>0&&SOLGUI_CSR==0)cursor_rel_offset--;		//光标在视口内上移	   	
		else if(viewport_offset>0&&SOLGUI_CSR==0)viewport_offset--;	 	//视口上移	
	}
	else if(cur_key==SOLGUI_KEY_DOWN){								    //当前全局为下键
		if((cursor_rel_offset<viewport_width)&&SOLGUI_CSR==0)cursor_rel_offset++; //光标在视口内下移
		else if((viewport_offset<option_num-viewport_width-1)&&SOLGUI_CSR==0)viewport_offset++;	 //视口下移
	}
	cursor_abs_offset=viewport_offset+cursor_rel_offset;	//计算当前光标的绝对偏移
//--------【屏幕绘制】
	y_t=rowBorder_Top*8;									//顶y坐标
	y_b=rowBorder_Bottom*8;									//底y坐标
//---【光标】
	cursor_row=y_t-cursor_rel_offset*8;	 		//将光标相对视口的偏移换算成像素坐标
	SOLGUI_printf(0,cursor_row,F6X8,"%c",ICON_CURSOR);		//光标绘制
//---【上下边线】
	if(rowBorder_Top!=6) SOLGUI_GBasic_Line(0,y_t+8,SCREEN_X_WIDTH-1,y_t+8,DOTTED);		//上边线
	if(rowBorder_Top!=0) SOLGUI_GBasic_Line(0,y_b-1,SCREEN_X_WIDTH-1,y_b-1,DOTTED);		//下边线
//---【滚动条】

	s_h=(double)(y_t-y_b+8)/(double)option_num;									//滑块高度???????????????????????
	s_y=y_t+7-s_h*(cursor_abs_offset+1);							//滑块位置???????????????????????
	GUI_GBasic_Rectangle(SCREEN_X_WIDTH-4,s_y,SCREEN_X_WIDTH-1,s_y+s_h,FILL);	//滑块???????????????????????

	GUI_GBasic_Rectangle(SCREEN_X_WIDTH-4,y_b,SCREEN_X_WIDTH-1,y_t+7,ACTUAL);	//边框

//--------【修改选项使能表】			
	for(i=0;i<=option_num;i++){
		option_enable_list[i]=(cursor_abs_offset==i)?1:0;	//填写选项使能表，在绝对偏移位置上为1，其余位置为0；
	}
}

//##############################【选项式控件】##############################

void SOLGUI_Widget_GotoPage(u8 USN,MENU_PAGE *page)		//页面跳转控件
{
	u8 row_disp=0;	//该选项应该显示的行位置
	u8 cur_key=0;	//键值
//--------【参数过滤】
	if(USN>=OPTIONS_MAX) return;		//USN只允许取0~OPTIONS_MAX-1
//--------【计算显示行】
	if((USN-viewport_offset)>=0&&(USN-viewport_offset)<=viewport_width)
	{		
		row_disp=row_start-USN+viewport_offset;
		if(option_enable_list[USN]==1)
		{
//--------【键值解析】
			cur_key=SOLGUI_GetCurrentKey();				//获取当前全局键值
			if(cur_key==SOLGUI_KEY_OK){					//OK键			
				current_page=page;						//跳转
				cursor_rel_offset=0;					//清空光标偏移计数器
				viewport_offset=0;											
			}					
		}
//--------【选项绘制】
		SOLGUI_printf(6,row_disp*8,F6X8,"%s",page->pageTitle);		//下一个页面标题
		SOLGUI_printf(SCREEN_X_WIDTH-13,row_disp*8,F6X8,"%c",0x8f);	//图标
//--------【操作提示绘制】
		if((viewport_offset+cursor_rel_offset)==USN)
		SOLGUI_printf(SCREEN_X_WIDTH-6,56,F6X8,"%c",0x84);			//操作指示（根据键值解析部分来编写）
	}
}



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

void SOLGUI_Widget_Spin(u8 USN,u8 type,const u8 *name,double max,double min,void* value)		//数字旋钮控件
{
	double swap;	
	u8 row_disp=0;	//该选项应该显示的行位置
	u8 cur_key=0;	//键值
	static s8 spin_pos=0;	//旋钮位置
	double dat_step=0;
	s32 *v_l;
	double *v_f;
//--------【参数过滤】
	if(max<min)
	{
		swap=max;
		max=min;
		min=swap;
	}
	if(USN>=OPTIONS_MAX) return;		//USN只允许取0~OPTIONS_MAX-1
//--------【参数准备】
	if(type==INTEGRAL) v_l=(s32 *)value;	//整数	
	else if(type==DECIMAL) v_f=(double *)value;	 //小数
	else v_l=(s32 *)value;		//其他默认做整数处理（待扩展）
//--------【计算显示行】
	if((USN-viewport_offset)>=0&&(USN-viewport_offset)<=viewport_width)
	{		
		row_disp=row_start-USN+viewport_offset;
		if(option_enable_list[USN]==1)
		{
//--------【键值解析】
			cur_key=SOLGUI_GetCurrentKey();				//获取当前全局键值
			if(cur_key==SOLGUI_KEY_OK){					//OK键			
				SOLGUI_CSR++;							//CSR翻转
				if(SOLGUI_CSR>1) SOLGUI_CSR=0;													
			}
			if(SOLGUI_CSR==1)							//如果处于设置模式中
			{
				dat_step=_Pow_10(spin_pos);				//计算调节步进值

				if(cur_key==SOLGUI_KEY_UP)														//数值加步进
				{
					if(type==DECIMAL) { if(((*v_f)+dat_step)<=max) (*v_f)+=dat_step; }			//小数	
					else { if(((*v_l)+(s32)dat_step)<=(s32)max) (*v_l)+=(s32)dat_step; }	 	//整数		
				}
				else if(cur_key==SOLGUI_KEY_DOWN)												//数值减步进
				{
					if(type==DECIMAL) { if(((*v_f)-dat_step)>=min) (*v_f)-=dat_step; }			//小数	
					else { if(((*v_l)-(s32)dat_step)>=(s32)min) (*v_l)-=(s32)dat_step; }	 	//整数
				}
				else if(cur_key==SOLGUI_KEY_LEFT)												//左步进
				{
					if(spin_pos<SPIN_DIGIT_MAX-1) spin_pos++;						
				}
				else if(cur_key==SOLGUI_KEY_RIGHT)												//右步进
				{
					if(type==INTEGRAL) { if(spin_pos>0) spin_pos--; }	//整数	
					else if(type==DECIMAL) { if(spin_pos>SPIN_DIGIT_MIN) spin_pos--; }	 //小数
					else { if(spin_pos>0) spin_pos--; }		//其他默认做整数处理（待扩展）
				}
			}				
		}
//--------【选项：变量名&数值绘制】
		SOLGUI_printf(6,row_disp*8,F6X8,"%s",name);		//变量名
		if(type==DECIMAL) SOLGUI_printf(68,row_disp*8,F6X8,"=%f",*v_f);	//数值		
		else SOLGUI_printf(68,row_disp*8,F6X8,"=%d",*v_l);	//数值						
//--------【旋钮绘制】
		if((SOLGUI_CSR==1)&&(option_enable_list[USN]==1)) 
		SOLGUI_printf(0,row_disp*8,0,"%c%f%c",0x82,dat_step,0x83);	   	//如果处于设置模式中，显示旋钮数值
//--------【操作提示绘制】
		if((viewport_offset+cursor_rel_offset)==USN)
		SOLGUI_printf(SCREEN_X_WIDTH-6,56,F6X8,"%c",0x84);			//操作指示（根据键值解析部分来编写）
	}	
}





//##############################【自由式控件】##############################

void SOLGUI_Widget_Bar(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,s32 value,u8 mode)		//条
{
	double f=0;
	u32 d=0;

	value=(value<max)?value:max;
	value=(value>min)?value:min;

	f=(double)(value-min)/(double)(max-min);

	if((mode&0x01)==DIREC_X)				//x生长
	{
		d=f*xsize;
		if((mode&0x06)==PROGBAR) 			//进度条
		{
			GUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+ysize,ACTUAL);
			GUI_GBasic_Rectangle(x0,y0,x0+d,y0+ysize,FILL);		
		}
		else if((mode&0x06)==SCALEBAR)		//刻度
		{
			GUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+ysize,ACTUAL);
			GUI_GBasic_Rectangle(x0,y0,x0+d,y0+ysize,ACTUAL);
			SOLGUI_GBasic_Line(x0,y0+ysize,x0+xsize,y0+ysize,DELETE);
		}
	}
	else									//y生长
	{		
		d=f*ysize;
		if((mode&0x06)==PROGBAR) 			//进度条
		{
			GUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+ysize,ACTUAL);
			GUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+d,FILL);
		}
		else if((mode&0x06)==SCALEBAR)		//刻度
		{
			GUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+ysize,ACTUAL);
			GUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+d,ACTUAL);
			SOLGUI_GBasic_Line(x0,y0,x0,y0+ysize,DELETE);
		}
	}	
}

#endif





