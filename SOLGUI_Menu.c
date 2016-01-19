#include"pixelC_Hardware_include.h"

//############################【菜单引擎变量】##############################

MENU_ITEM *menu_now;		//当前的页面
int pow10=0,pow10_d=0;		
unsigned char cursor_op=0;
//---------------【设置页面控制变量】
unsigned char set_mode_flag=0,col_start=0,cursor_al=0,page_al=0,disp_w=0;//修改器使能，选项起始行，页内光标，页标，视口宽度	
unsigned char set_enable_list[MAX_MENU_OPTION];		//使能表




//##############################【内部使用】##############################
double Menu_Pow_10(int n) 	//用于数字显示，pow=m^n
{
	int i=0;
	double p=1;
	if(n>=0)
	{
		for(i=0;i<n;i++)
		{
			p*=10;
		}
		return(p);
	}
	else
	{
		n*=-1;
		for(i=0;i<n;i++)
		{
			p*=0.1;
		}
		return(p);
	}
}

unsigned char SOLGUI_Menu_CharCnt(unsigned char *str)
{
	unsigned char i=0;
	for(i=0;*(str+i)!='\0';i++);
	return i;
}

//##############################【菜单引擎】##############################

void SOLGUI_Menu_Init(MENU_ITEM *Root_Menu)
{
  	int i;
	for(i=0;i<MAX_MENU_OPTION;i++){
		set_enable_list[i]=0;	
	}
	menu_now=Root_Menu;
}

void SOLGUI_Menu_GetKeyValue(unsigned char key_value)  //取得输入引擎的键值（输入键值）
{
	cursor_op=key_value;	
}

void SOLGUI_Menu_Main(void)		//菜单引擎（非阻塞，要循环调用）
{
	int i=0,j=0,title_y=0;
//--------【功能页】
	if(menu_now->pageKind==FUNC_KIND)		   						//功能页
	{
		menu_now->HookFunc();										//执行功能函数
		if(cursor_op==MENU_KEY_BACK&&set_mode_flag==0){				//每次检查是否有返回信号且不在设置模式中
			if(menu_now->ParentMenus!=NULL)menu_now=menu_now->ParentMenus;
			cursor_al=0;
			page_al=0;
		}	
	}
//--------【菜单页】
	else if(menu_now->pageKind==MENU_KIND) 			//菜单页
	{
//--------【键值解释器】
		if(cursor_op==MENU_KEY_UP){		

			if(menu_now->page_cursor>0)menu_now->page_cursor--;
			else if(menu_now->page>0)menu_now->page--;	
		}
		else if(cursor_op==MENU_KEY_DOWN){
			if(menu_now->page_cursor<(menu_now->optionCnt-1<6?menu_now->optionCnt-1:6))menu_now->page_cursor++;
			else if(menu_now->page<menu_now->optionCnt-7)menu_now->page++;
		}
		else if(cursor_op==MENU_KEY_OK){
			if(menu_now->ChildrenMenus[menu_now->page_cursor+menu_now->page]!=NULL)
			menu_now=menu_now->ChildrenMenus[menu_now->page_cursor+menu_now->page];			
		}
			else if(cursor_op==MENU_KEY_BACK){
			if(menu_now->ParentMenus!=NULL)menu_now=menu_now->ParentMenus;		
		}
//--------【绘制界面】

		SOLGUI_Menu_Title();													//标题绘制函数

		if(menu_now->optionCnt<=7)
		{
			for(i=0;i<menu_now->optionCnt;i++)									//选项&光标（选项<7时单页显示）
			{
				title_y=48-8*i;
				if(menu_now->page_cursor==i){
					SOLGUI_printf(0,title_y,1,">%s",menu_now->ChildrenMenus[i]->menuTitle);				   	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				}
				else{
					SOLGUI_printf(0,title_y,1," %s",menu_now->ChildrenMenus[i]->menuTitle);				  	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				}
				if(menu_now->ChildrenMenus[i]->pageKind==MENU_KIND)SOLGUI_Show_Char(109,title_y,'>',1);	  	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			}
		}
		else if(7<menu_now->optionCnt&&menu_now->optionCnt<MAX_MENU_OPTION)		//选项&光标（选项>7时滚屏显示）
		{
				
			for(i=menu_now->page,j=0;j<7;i++,j++)								
			{
				title_y=48-8*j;
				if(menu_now->page_cursor==j){
					SOLGUI_printf(0,title_y,1,">%s",menu_now->ChildrenMenus[i]->menuTitle);				   	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				}
				else{
					SOLGUI_printf(0,title_y,1," %s",menu_now->ChildrenMenus[i]->menuTitle);				  	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				}
				if(menu_now->ChildrenMenus[i]->pageKind==MENU_KIND)SOLGUI_Show_Char(109,title_y,'>',1); //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			}		
		}
	}
}

void SOLGUI_Menu_Title(void)
{
	int i;
	int title_offset=0,title_lenght=0;
	title_lenght=SOLGUI_Menu_CharCnt(menu_now->menuTitle);		
	title_offset=(22-title_lenght)/2;
	for(i=0;i<title_offset-2;i++)
	{
		SOLGUI_Show_Char(6*i,56,'_',1);								   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		SOLGUI_Show_Char(6*(title_offset+title_lenght+2+i),56,'_',1);  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	}
	
	SOLGUI_Show_Char((title_offset-2)*6,56,'[',1);					   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	SOLGUI_Show_Char((title_offset+title_lenght+1)*6,56,']',1);		   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	SOLGUI_Show_String(title_offset*6,56,menu_now->menuTitle,1);	   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
}

//##############################【变量值显示】##############################

void SOLGUI_Menu_Show_Int(unsigned char col_y,unsigned char *value_name,int value)
{
	SOLGUI_Show_String(6,col_y*8,value_name,1);				  	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	SOLGUI_printf(68,col_y*8,1,"|%d",value);					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
}								

void SOLGUI_Menu_Show_Double(unsigned char col_y,unsigned char *value_name,double value)
{
	SOLGUI_Show_String(6,col_y*8,value_name,1);				   	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	SOLGUI_printf(68,col_y*8,1,"|%f",value);					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
}

//##############################【设置页各类型数据设置函数】##############################

void SOLGUI_Menu_Cursor_Alone(unsigned char top_col,unsigned char bot_col,unsigned char option_cnt) 	//独立的光标，用于参数设置功能页
{
	int i=0;
	unsigned char point_al=0,currsr_dispos=0;//显示宽度;
	col_start=(top_col>bot_col)?top_col:bot_col;
	if(disp_w>option_cnt) disp_w=option_cnt-1;
	else disp_w=(top_col>bot_col)?top_col-bot_col:bot_col-top_col;
//--------【键值解释器】
	if(cursor_op==MENU_KEY_UP){						
		if(cursor_al>0&&set_mode_flag==0)cursor_al--;
		else if(page_al>0&&set_mode_flag==0)page_al--;	 		
	}
	else if(cursor_op==MENU_KEY_DOWN){
		if((cursor_al<disp_w)&&set_mode_flag==0)cursor_al++;
		else if((page_al<option_cnt-disp_w-1)&&set_mode_flag==0)page_al++;
	}
//--------【绘图】
	currsr_dispos=(((top_col>bot_col)?top_col:bot_col)-cursor_al)*8;
	SOLGUI_Show_Char(0,currsr_dispos,'>',1);					   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	point_al=page_al+cursor_al;
	for(i=0;i<=option_cnt;i++){
		set_enable_list[i]=(point_al==i)?1:0;	
	}
}

//-------------------------------------【设置函数】

void SOLGUI_Menu_Set_Int(unsigned char handle,unsigned char *value_name,int *value,int value_max,int value_min)
{
	unsigned char col_y=0;
	int d_plus=0;
//--------【计算显示行】
	if((handle-page_al)>=0&&(handle-page_al)<=disp_w)
	{		
		col_y=col_start-handle+page_al;
		if(set_enable_list[handle]==1)
		{
			d_plus=(int)(Menu_Pow_10(pow10));
//--------【键值解释器】
			if(cursor_op==MENU_KEY_OK_L){							//OK长按进了修改
				set_mode_flag++;
				if(set_mode_flag>1)set_mode_flag=0;			
			}
			else if(cursor_op==MENU_KEY_UP){						
				if(set_mode_flag==1&&((*value)+d_plus)<=((value_max>value_min)?value_max:value_min))(*value)+=d_plus;		
			}
			else if(cursor_op==MENU_KEY_DOWN){
				if(set_mode_flag==1&&((*value)-d_plus)>=((value_min<value_max)?value_min:value_max))(*value)-=d_plus;
			}
			else if(cursor_op==MENU_KEY_RIGHT){		
				if(set_mode_flag==1&&pow10>0)pow10--;		
			}
			else if(cursor_op==MENU_KEY_LEFT){
				if(set_mode_flag==1&&pow10<7)pow10++;
			}
//--------【绘制变量名】
			if(set_mode_flag==1)
			{
				SOLGUI_printf(0,col_y*8,0,"set <%d>",d_plus);						  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				SOLGUI_Show_Char(68,col_y*8,'|',1);								  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				SOLGUI_printf(74,col_y*8,0,"%d",*value);						  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			}
			else SOLGUI_Menu_Show_Int(col_y,value_name,*value);		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
		else SOLGUI_Menu_Show_Int(col_y,value_name,*value);			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	}
}



void SOLGUI_Menu_Set_Double(unsigned char handle,unsigned char *value_name,double *value,int value_max,int value_min)
{
	unsigned char col_y=0;
	double d_plus=0;
//--------【计算显示行】
	if((handle-page_al)>=0&&(handle-page_al)<=disp_w)
	{		
		col_y=col_start-handle+page_al;
		if(set_enable_list[handle]==1)
		{
			d_plus=Menu_Pow_10(pow10_d);
//--------【键值解释器】
			if(cursor_op==MENU_KEY_OK_L){							//OK长按进了修改
				set_mode_flag++;
				if(set_mode_flag>1)set_mode_flag=0;			
			}
			else if(cursor_op==MENU_KEY_OK_L){							//OK长按进了修改
				set_mode_flag++;
				if(set_mode_flag>1)set_mode_flag=0;			
			}
			else if(cursor_op==MENU_KEY_UP){						
				if(set_mode_flag==1&&((*value)+d_plus)<=((value_max>value_min)?value_max:value_min))(*value)+=d_plus;		
			}
			else if(cursor_op==MENU_KEY_DOWN){
				if(set_mode_flag==1&&((*value)-d_plus)>=((value_min<value_max)?value_min:value_max))(*value)-=d_plus;
			}
			else if(cursor_op==MENU_KEY_RIGHT){		
				if(set_mode_flag==1&&pow10_d>-3)pow10_d--;		
			}
			else if(cursor_op==MENU_KEY_LEFT){
				if(set_mode_flag==1&&pow10_d<6)pow10_d++;
			}
//--------【绘制变量名】
			if(set_mode_flag==1)
			{
				SOLGUI_printf(0,col_y*8,0,"set <%f>",d_plus);						  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				SOLGUI_Show_Char(68,col_y*8,'|',1);								  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				SOLGUI_printf(74,col_y*8,0,"%f",*value);						  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
			}
			else SOLGUI_Menu_Show_Double(col_y,value_name,*value);	   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
		else SOLGUI_Menu_Show_Double(col_y,value_name,*value);		   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	}
}

void SOLGUI_Menu_Trig_Func(unsigned char handle,unsigned char *func_name,void (*func)(void))		//设置页中的单次触发函数
{
	unsigned char col_y=0;
	if((handle-page_al)>=0&&(handle-page_al)<=disp_w)
	{		
		col_y=col_start-handle+page_al;
		if(set_enable_list[handle]==1)
		{
//--------【键值解释器】
			if(cursor_op==MENU_KEY_OK){									//OK短按单次触发
//--------【函数单次动作】
				func();				
			}
			SOLGUI_Show_String(6,col_y*8,func_name,1);				   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SOLGUI_Show_Char(68,col_y*8,'-',1);					   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SOLGUI_Show_Char(74,col_y*8,'>',1);					   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
		else
		{
			SOLGUI_Show_String(6,col_y*8,func_name,1);				   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SOLGUI_Show_Char(68,col_y*8,'-',1);						   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SOLGUI_Show_Char(74,col_y*8,'>',1);					   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`
		}
	}
}

unsigned char SOLGUI_Menu_GetKeyInline(void)
{
	return (cursor_op);	
}
