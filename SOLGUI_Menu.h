#ifndef SOLGUI_MENU_H
#define SOLGUI_MENU_H

//###########################【可修改参数】##############################
#define MAX_MENU_OPTION 17 		//单页最大菜单选项数(设置小一些可以减少内存使用量)
//-------键值定义
#define	MENU_KEY_UP		0x50	//上键键值
#define MENU_KEY_DOWN	0x20	//下键键值
#define	MENU_KEY_LEFT	0x30	//左键键值
#define MENU_KEY_RIGHT	0x10	//右键键值
#define	MENU_KEY_OK		0x40 	//OK键短按键值
#define	MENU_KEY_OK_L	0x40	//OK键长按键值（若没有长按，可以用短按键值代替，影响不大）【PS：有时长按时间太长，会用短按代替】
#define	MENU_KEY_BACK	0x60	//返回键键值

//############################【内部定义】##############################
#define NULL 		0				//空
#define FUNC_NULL 	0				//函数空
#define LIST_NULL	{0}				//指针列表空

#define MENU_KIND	0x01  			//菜单页类型
#define	FUNC_KIND	0x10			//功能页类型


typedef struct __MENU_ITEM{									//菜单/函数类型
	unsigned char pageKind;									//页面类型（MENU_KIND菜单型（枝），FUNC_KIND功能型（叶）)
//--------【菜单相关属性】
	unsigned char *menuTitle;								//该层菜单的标题
	unsigned char page;										//初始页		（用于卷动）【置0】
	unsigned char page_cursor;								//初始页内光标	（用于卷动）【置0】
	unsigned char optionCnt;								//该层菜单中含有的选项条目数
	struct __MENU_ITEM *ChildrenMenus[MAX_MENU_OPTION];		//该层菜单中含有的子菜单指针数组
	struct __MENU_ITEM *ParentMenus;						//该层菜单中的父菜单指针
//--------【功能相关属性】
	void (*HookFunc)();										//该功能页的执行函数
}MENU_ITEM;

//##############################【API】##############################
//--------【菜单引擎】
void SOLGUI_Menu_Init(MENU_ITEM *Root_Menu);				//菜单引擎初始化（输入根菜单指针）
void SOLGUI_Menu_GetKeyValue(unsigned char key_value);		//取得输入引擎的键值（输入键值）
void SOLGUI_Menu_Main(void);								//菜单引擎（要先用函数取得键值）【非阻塞，要循环调用】

//--------【功能页使用】
void SOLGUI_Menu_Title(void);										//显示该页标题（可选）
unsigned char SOLGUI_Menu_GetKeyInline(void);						//从引擎中取得键值

//--------【设置页使用】
void SOLGUI_Menu_Cursor_Alone(unsigned char top_col,unsigned char bot_col,unsigned char option_cnt); 			//设置页光标及选项选通器（输入选项显示上界，下界，选项数）
void SOLGUI_Menu_Set_Int(unsigned char handle,unsigned char *value_name,int *value,int value_max,int value_min);//设置整数变量项函数，变量名限制10个字符
void SOLGUI_Menu_Set_Double(unsigned char handle,unsigned char *value_name,double *value,int value_max,int value_min);  //设置小数变量项函数，变量名限制10个字符，3位小数
void SOLGUI_Menu_Trig_Func(unsigned char handle,unsigned char *func_name,void (*func)(void));					//设置页中的单次触发函数,函数名限制10个字符

/*---------------------------------------------------------------------------------------------------------------------------------
【SOLGUI_MENU_2.0 SOL菜单引擎v2.0使用说明】

需要的文件：
	pixelC_SOLGUI_General.h
	pixelC_SOLGUI_General.c	//基本字符串，数字显示【可选】
	pixelC_SOLGUI_MENU.h
	pixelC_SOLGUI_MENU.c	//菜单引擎【核心】


【1】原理：基于双向链表的状态机
整个.c文件作为状态机，用键值输入函数输入键值来改变状态。整个引擎是非阻塞结构，在执行功能页面的函数时，菜单引
擎占用系统时间极少。

【2】结构：分为两种页面，MENU_KIND菜单型和FUNC_KIND功能型。由菜单引导进入功能页，功能页执行函数，任意时间按
下返回键即可以退回上级菜单中。类似于树形结构：菜单页是树枝树干，功能页是树叶

【3】移植步骤：
1.参数栏修改键值（当外部输入何键值时会触发的操作）

2.声明页面：将要用到的页面变量事先声明（注意，不是定义！），防止在定义页面时用到在其之后定义的页面而引发的错误
如：
	MENU_ITEM root,temp_1,temp_2,···; 	//变量声明

3.定义页面：

使用MENU_ITEM类型定义页面，各成员作用：
	unsigned char pageKind;									//页面类型（MENU_KIND菜单型，FUNC_KIND功能型)
	unsigned char *menuTitle;								//该菜单的标题
	unsigned char page;										//页标				
	unsigned char page_cursor;								//页内光标位置
	unsigned char optionCnt;								//该菜单中的选项数目
	struct __MENU_ITEM *ChildrenMenus[MAX_MENU_OPTION];		//该菜单中的子菜单页/功能页指针数组
	struct __MENU_ITEM *ParentMenus;						//该菜单中的父菜单指针
	void (*HookFunc)();										//若为功能页时的执行函数

【下面给出两种页面的定义模板：（直接复制修改即可）】
//----------------------------------//菜单页模板
MENU_ITEM temp={					
	MENU_KIND,						//MENU_KIND菜单型
	"title",						//标题
	0,								//置0
	0,								//置0
	2,								//选项数目
	{&temp_func,&temp_menu},		//选项页面变量指针列表（可以是功能页或者是菜单页，注意加&取地址）
	&root,							//上级页面变量指针（按返回键后可以回到的这个页面）
	FUNC_NULL 						//FUNC_NULL没有执行函数 
};

//----------------------------------//功能页模板

void function(void)				 	//功能页执行函数（必须为无参数无返回值的函数类型）
{
	...
}

MENU_ITEM temp={					
	FUNC_KIND,						//FUNC_KIND功能型
	"title",						//标题
	0,								//置0
	0,								//置0
	0,								//置0
	LIST_NULL,						//置LIST_NULL
	&root,					    	//上级页面变量指针（按返回键后可以回到的这个页面）
	function 						//该功能页的执行函数名
};



4.使用菜单引擎
用到三个函数：
void SOLGUI_Menu_Init(MENU_ITEM *Root_Menu);				//初始化菜单引擎，要输入根页面（运行后显示的第一个页面）指针
void SOLGUI_Menu_GetKeyValue(unsigned char key_value);		//获取键值传入菜单引擎（输入从按键扫描函数中得到的键值）【非阻塞，要循环调用】				
void SOLGUI_Menu_Main(void);								//菜单引擎主体【非阻塞，要循环调用】

下面给出使用引擎的模板：
//----------------------------------//引擎使用模板
void main()
{
	...
	SOLGUI_Menu_Init(&root);				//初始化菜单引擎，要输入根页面指针
	...
	while(1)
	{
		...
		key_value=Key_Scan();				//按键扫描函数，返回键值。Key_Scan()需要自己定义
		SOLGUI_Menu_GetKeyValue(key_value);	//键值传入菜单引擎
		SOLGUI_Menu_Main();					//菜单引擎主体
		...
	}
}

【PS：pixelC_SOLGUI_MENU.c文件中用@标识的注释是使用了pixelC_SOLGUI_General.h中的函数实现的，可以自行编写替换】

【4】功能页：
菜单引擎在判断当前页面为功能型页后，会执行功能页的执行函数，并在每次循环，查询是否有返回键按下，如果有，则返回上级菜单；
因此，【只要在功能页执行函数中不发生:①修改页面类型(变成菜单型)，②使用返回键，便可以直接将菜单引擎当作功能页执行函数!】
即：
	 function(void)<----->SOLGUI_Menu_Main(void); 		//两者等价
	
此时，在功能页执行函数中可以调用其他函数（如获取键值（返回键除外），屏幕绘图，GPIO，串口等），
此时在执行函数编写环境等价于：
					while(1)
					{
						...
						function();
						...
					}


【功能页中获取键值】如果要在功能页中获取按键值，可以使用
						SOLGUI_Menu_GetKeyInline();
函数获取输入，返回输入菜单引擎中的键值。这方便多文件编程时使用。

【功能页中显示该页标题】如果要在功能页顶部显示标题，可以使用
						SOLGUI_Menu_Title(void); 
生成与菜单页顶部一致的标题


【5】参数设置页：
特别的，菜单引擎提供一种用于参数设置的功能页，称为参数设置页。每个页面可以包含最多MAX_MENU_OPTION(默认16)个参
数进行设置，支持滚屏操作。

我们对屏幕的行进行如下定义:

					+-----------------------+
					|________[ 标题 ]_______|	-----第7行
					| 	参数1		| 值	|	-----第6行
					|	参数2		| 值	|	-----第5行
					|	参数3		| 值	|	-----第4行
					|	参数4		| 值	|	-----第3行
					|	参数5		| 值	|	-----第2行
					|	单触发函数	-> 		|	-----第1行
					|	单触发函数	-> 		|	-----第0行
					+-----------------------+

【如何在参数设置页中设置参数？】
（1）上下键移动光标，选中要修改的参数；
（2）长按确认键呼出设置器，左右键设置步进值，上下键对参数进行加减；
（3）再次长按确认键挂起设置器（在设置器中退出键失效），重复（1）或者按退出键退出参数设置页；


2. 参数设置页编写：
（1）定义:
定义为功能页，请参考【功能页模板】，只需在功能页执行函数中，使用模板即可；

（2）执行函数：
【设置页相关函数】
void SOLGUI_Menu_Cursor_Alone(unsigned char top_col,unsigned char bot_col,unsigned char option_cnt); 			
	//独立光标及选项选通器（选项行上界，选项行下界，选项数；加入防错机制，上下界可颠倒）
	
void SOLGUI_Menu_Set_Int(unsigned char handle,unsigned char *value_name,int *value,int value_max,int value_min);
	//设置整数变量选项函数（显示序号，变量显示名，变量值指针，上限，下限）
	（PS：变量名限制10个字符，调节精度：1；加入防错机制，上下限可颠倒）

void SOLGUI_Menu_Set_Double(unsigned char handle,unsigned char *value_name,double *value,int value_max,int value_min);  
	//设置小数变量选项函数（显示序号，变量显示名，变量值指针，上限，下限）
	（PS：变量名限制10个字符，调节精度：0.001；加入防错机制，上下限可颠倒）
	
void SOLGUI_Menu_Trig_Func(unsigned char handle,unsigned char *func_name,void (*func)(void));					
	//设置页中的单次触发函数（显示序号，函数显示名，函数指针）
	（PS：变量名限制10个字符，按下确认键后会执行func()中的代码）

（每个可设置选项函数必须赋予一个唯一的显示序号，显示时会按显示序号顺序显示，范围从0~选项数-1）

//----------------------------------//参数设置页模板

void function(void)		 						//SOLGUI_Menu_Trig_Func()使用的单次触发函数
{
//	...(可以调用全部资源，不可死循环)
}

void set(void)			
{
	SOLGUI_Menu_Cursor_Alone(6,3,8); 			//从第6行到第3行显示选项，共有8个可设置项，下面的显示序号为0~7排列
//--------以下为各可设置项定义
	SOLGUI_Menu_Set_Int(0,"Enable_PID?",&PID_en,1,0);
	SOLGUI_Menu_Set_Int(1,"PIDobj_addr",&addr,255,0);
	SOLGUI_Menu_Set_Int(2,"PIDobj_opt",&opt,5,0);
	SOLGUI_Menu_Set_Int(3,"PID_balance",&bal,100,-100);
	SOLGUI_Menu_Set_Double(4,"PIDobj_Kp",&Kp,10000,-10000);
	SOLGUI_Menu_Set_Double(5,"PIDobj_Ki",&Ki,10000,-10000);
	SOLGUI_Menu_Set_Double(6,"PIDobj_Kd",&Kd,10000,-10000);
	SOLGUI_Menu_Trig_Func(7,"SetToPID",function);
	
	... 	

}

---------------------------------------------------------------------------------------------------------------------------------*/

#endif
