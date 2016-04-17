#ifndef SOLGUI_CONFIG_H
#define SOLGUI_CONFIG_H

//##############################【硬件层】##############################
//--------------【屏幕长宽像素数】
#define SCREEN_X_WIDTH 			128				//屏幕的X轴像素数
#define SCREEN_Y_WIDTH 			64				//屏幕的Y轴像素数

//--------------【屏幕长宽字数】		
#define SCREEN_X_PAGE 	(SCREEN_X_WIDTH/6)		//支持多少个6x8字宽（一般不需要修改，默认即可）
#define SCREEN_Y_PAGE 	(SCREEN_Y_WIDTH/8)		//支持多少个6x8字高（一般不需要修改，默认即可）

//##############################【中间层】##############################
//--------------【字库开关】
/*----------------默认使用6x8字体----------------*/
/*---------可根据实际使用情况开关，节约空间---------*/
#define FONT4X6_EN 				0	 		//允许使用4x6字体
#define FONT8X8_EN 				0	 		//允许使用8x8字体
#define FONT8X10_EN				0	 		//允许使用8x10字体

//--------------【基础图形库开关】
#define GBASIC_LINE_EN			0			//允许使用直线绘制
#define GBASIC_RECTANGLE_EN		0			//允许使用矩形绘制
#define GBASIC_CIRCLE_EN		0			//允许使用圆形绘制



//##############################【应用层】##############################
//--------------【SOLGUI菜单框架前台使用开关】
/*---------关闭后不能调用应用层中函数，即无法使用菜单框架---------*/
#define MENU_FRAME_EN 			1	 			//允许SOLGUI菜单框架作为前台

//--------------【Widget开关】
/*---------可根据实际使用情况开关，节约空间---------*/
#define WIDGET_GOTOPAGE_EN 		1				//允许使用控件：GotoPage页面跳转
#define WIDGET_SPIN_EN 			1				//允许使用控件：Spin数字旋钮
#define WIDGET_OPTIONTEXT_EN 	1				//允许使用控件：OptionText选项文本
#define WIDGET_BUTTON_EN 		1				//允许使用控件：Button按键
#define WIDGET_SWITCH_EN		1				//允许使用控件：Switch复选开关
#define WIDGET_EDIT_EN 			1				//允许使用控件：Edit文本编辑
										 	
#define WIDGET_TEXT_EN 			1				//允许使用控件：Text文字
#define WIDGET_BAR_EN 			1				//允许使用控件：Bar条
#define WIDGET_SPECTRUM_EN 		1				//允许使用控件：Spectrum谱
#define WIDGET_OSCILLOGRAM_EN 	1				//允许使用控件：Oscillogram波形
#define WIDGET_PICTURE_EN		1				//允许使用控件：Picture图

//--------------【选项最大数目】
#define OPTIONS_MAX				16				//每页最大可以容纳的选项数（不可设置太大）

//--------------【FIFO键值缓存大小】
#define FIFOBUF_SIZE			5				//可以缓存的键值数（默认即可）

//--------------【键值对应行为设置】
/*---------用户需根据系统按键返回的键值来进行设定---------*/
#define	SOLGUI_KEY_UP			0x50			//上
#define SOLGUI_KEY_DOWN			0x20			//下
#define	SOLGUI_KEY_LEFT			0x30			//左
#define SOLGUI_KEY_RIGHT		0x10			//右
#define SOLGUI_KEY_OK			0x40 			//确认
#define	SOLGUI_KEY_BACK			0x60			//返回

//--------------【系统图标设置】
/*---------如果用户不添加自定义图标，此处默认即可，不需修改---------*/
#define	ICON_UP					0x80			//上（可以在Font6x8_ASCII.c中设置）
#define	ICON_DOWN				0x81			//下（可以在Font6x8_ASCII.c中设置）
#define	ICON_LEFT				0x82			//左（可以在Font6x8_ASCII.c中设置）
#define	ICON_RIGHT				0x83			//右（可以在Font6x8_ASCII.c中设置）
#define	ICON_OK					0x84			//OK（可以在Font6x8_ASCII.c中设置）
#define	ICON_BACK				0x85			//返回（可以在Font6x8_ASCII.c中设置）
#define	ICON_CURSOR 			0x86			//光标（可以在Font6x8_ASCII.c中设置）
#define	ICON_WIDGET_GOTOPAGE 	0x87			//页面跳转控件（可以在Font6x8_ASCII.c中设置）
#define	ICON_WIDGET_EDIT		0x88			//文本编辑控件（可以在Font6x8_ASCII.c中设置）
#define	ICON_OTHER_HIDE			0x89			//省略号（可以在Font6x8_ASCII.c中设置）

//--------------【SPIN控件：上下限位数设置】
#define SPIN_DIGIT_MAX 			5				//可在SPIN中可设置的上限位数（超过5位会出错）
#define SPIN_DIGIT_MIN 			(-3)			//可在SPIN中可设置的下限位数（精度10^-3）

//--------------【EDIT控件：缓存大小设置】
#define EDIT_BUF_SIZE			(40+1)			//在EDIT中字符缓存的最大长度（128*64下最大94）
#define EDIT_THUMBNAIL_SIZE		7				//在EDIT选项中缩略信息缓存的最大长度										 	

#endif
