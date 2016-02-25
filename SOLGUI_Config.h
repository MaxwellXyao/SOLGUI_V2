#ifndef SOLGUI_CONFIG_H
#define SOLGUI_CONFIG_H

//##############################【参数设置】##############################
//--------------【屏幕长宽像素数】
#define SCREEN_X_WIDTH 		128				//屏幕的X轴像素数
#define SCREEN_Y_WIDTH 		64				//屏幕的Y轴像素数

//--------------【屏幕长宽字数】		
#define SCREEN_X_PAGE (SCREEN_X_WIDTH/6)	//支持多少个默认6x8字宽
#define SCREEN_Y_PAGE (SCREEN_Y_WIDTH/8)	//支持多少个默认6x8字高

//--------------【选项最大数目】
#define OPTIONS_MAX			16				//每页最大可以存放的选项数

//--------------【FIFO键值缓存大小】
#define FIFOBUF_SIZE		5				//可以缓存的键值数

//--------------【系统返回的按键键值】
#define	SOLGUI_KEY_UP		0x50			//上键键值
#define SOLGUI_KEY_DOWN		0x20			//下键键值
#define	SOLGUI_KEY_LEFT		0x30			//左键键值
#define SOLGUI_KEY_RIGHT	0x10			//右键键值
#define SOLGUI_KEY_OK		0x40 			//OK键短按键值
#define	SOLGUI_KEY_BACK		0x60			//返回键键值

//--------------【系统图标设置】
#define	ICON_UP				0x80			//上（可以在Font6x8_ASCII.c中设置）
#define	ICON_DOWN			0x81			//下（可以在Font6x8_ASCII.c中设置）
#define	ICON_LEFT			0x82			//左（可以在Font6x8_ASCII.c中设置）
#define	ICON_RIGHT			0x83			//右（可以在Font6x8_ASCII.c中设置）
#define	ICON_OK				0x84			//OK（可以在Font6x8_ASCII.c中设置）
#define	ICON_BACK			0x85			//返回（可以在Font6x8_ASCII.c中设置）
#define	ICON_CURSOR 		0x86			//光标（可以在Font6x8_ASCII.c中设置）

#define	ICON_WIDGET_GOTOPAGE 0x87			//页面跳转控件（可以在Font6x8_ASCII.c中设置）
#define	ICON_WIDGET_EDIT	0x88			//文本编辑控件（可以在Font6x8_ASCII.c中设置）

#define	ICON_OTHER_HIDE		0x89			//省略号（可以在Font6x8_ASCII.c中设置）

//--------------【SPIN控件：上下限位数设置】
#define SPIN_DIGIT_MAX 		5				//可在SPIN中设置的上限位数（超过5位会出错）
#define SPIN_DIGIT_MIN 		(-3)			//可在SPIN中设置的下限位数

//--------------【EDIT控件：buf大小设置】
#define EDIT_BUF_SIZE		(40+1)			//在EDIT中缓存的buf大小（128*64下最大94）
#define EDIT_THUMBNAIL_SIZE	7				//在EDIT选项中简略信息的大小


//##############################【功能开关】############################## 
//--------------【字库开关】
/*----------------默认使用6x8字体----------------*/
#define FONT4X6_EN 				0	 		//允许使用4x6字体
#define FONT8X8_EN 				0	 		//允许使用8x8字体
#define FONT8X10_EN				0	 		//允许使用8x10字体

//--------------【使用SOLGUI菜单框架前台开关】
#define MENU_FRAME_EN 			1	 		//允许SOLGUI菜单框架作为前台，选否则只可使用到中间层

//--------------【Widget开关】
#define WIDGET_TEXT_EN 			1			//使用控件：Text静态文本
#define WIDGET_GOTOPAGE_EN 		1			//使用控件：GotoPage页面跳转
#define WIDGET_BUTTON_EN 		1			//使用控件：Button按键
#define WIDGET_SWITCH_EN		1			//使用控件：Switch复选开关
#define WIDGET_SPIN_EN 			1			//使用控件：Spin数字旋钮
#define WIDGET_EDIT_EN 			1			//使用控件：Edit文本编辑

#define WIDGET_BAR_EN 			1			//使用控件：Bar条
#define WIDGET_SPECTRUM_EN 		1			//使用控件：Spectrum谱


#endif
