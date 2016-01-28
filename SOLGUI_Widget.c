#include"SOLGUI_Include.h"

#if MENU_FRAME_EN==1
//##############################【变量定义】##############################
//-----------【状态寄存器】
u8 SOLGUI_CSR=0;		//控制寄存器
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
//--------【参数过滤】
	if(rowBorder_Top<rowBorder_Bottom)		//默认上边界大于下边界，否则交换
	{
		temp=rowBorder_Top;
		rowBorder_Top=rowBorder_Bottom;
		rowBorder_Bottom=temp;
	}
	row_start=rowBorder_Top;	//设置选项起始行
	viewport_width=rowBorder_Top-rowBorder_Bottom; //视口行数计算
	if(option_num<viewport_width) viewport_width=option_num-1;		//选项数小于视口宽度处理
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
//--------【屏幕绘制】
//---【光标】
	cursor_row=(rowBorder_Top-cursor_rel_offset)*8;	 		//将光标相对视口的偏移换算成像素坐标
	SOLGUI_printf(0,cursor_row,F6X8,"%c",ICON_CURSOR);		//光标绘制
//---【滚动条】



//--------【修改选项使能表】			
	cursor_abs_offset=viewport_offset+cursor_rel_offset;	//计算当前光标的绝对偏移
	for(i=0;i<=option_num;i++){
		option_enable_list[i]=(cursor_abs_offset==i)?1:0;	//填写选项使能表，在绝对偏移位置上为1，其余位置为0；
	}
}

//##############################【选项式控件】##############################

void SOLGUI_Widget_GotoPage(u8 USN,MENU_PAGE *page)		//页面跳转控件
{
	u8 row_disp=0;	//该选项应该显示的行位置
	u8 cur_key=0;	//键值
//--------【计算显示行】
	if((USN-viewport_offset)>=0&&(USN-viewport_offset)<=viewport_width)
	{		
		row_disp=row_start-USN+viewport_offset;
		if(option_enable_list[USN]==1)
		{
//--------【键值解析】
			cur_key=SOLGUI_GetCurrentKey();				//获取当前全局键值
			if(cur_key==SOLGUI_KEY_OK){								
				current_page=page;						//短按OK键跳转
				cursor_rel_offset=0;					//清空光标偏移计数器
				viewport_offset=0;											
			}					
		}
//--------【选项绘制】
		SOLGUI_printf(6,row_disp*8,F6X8,"%s",page->pageTitle);		//下一个页面标题

//--------【操作提示绘制】
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
		else if((mode&0x06)==SCROLL)		//滚动条
		{
			
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
		else if((mode&0x06)==SCROLL)		//滚动条
		{
			
		}		
	}	
}

#endif





