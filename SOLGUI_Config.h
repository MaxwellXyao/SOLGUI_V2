#ifndef SOLGUI_CONFIG_H
#define SOLGUI_CONFIG_H

//##############################【硬件参数设置】##############################
//--------------【屏幕长宽像素数】
#define SCREEN_X_WIDTH 		128				//屏幕的X轴像素数
#define SCREEN_Y_WIDTH 		64				//屏幕的Y轴像素数

//--------------【屏幕长宽页数】		
#define SCREEN_X_PAGE SCREEN_X_WIDTH/6		//支持多少个默认6x8字宽
#define SCREEN_Y_PAGE SCREEN_Y_WIDTH/8		//支持多少个默认6x8字高

//--------------【选项最大数目】
#define OPTIONS_MAX			16				//最大可以的选项数

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
#define	ICON_CURSOR 		0x86			//可以在Font6x8_ASCII.c中设置

//--------------【SPIN控件上下限位数设置】
#define SPIN_DIGIT_MAX 		5				//可在SPIN中设置的上限位数（超过5位会出错）
#define SPIN_DIGIT_MIN 		-3				//可在SPIN中设置的下限位数


//##############################【功能开关】##############################
//--------------【字库开关】
/*----------------默认使用6x8字体----------------*/
#define FONT4X6_EN 			0	 			//允许使用4x6字体（1：是，0：否）
#define FONT8X8_EN 			0	 			//允许使用8x8字体（1：是，0：否）
#define FONT8X10_EN			0	 			//允许使用8x10字体（1：是，0：否）

//--------------【使用SOLGUI菜单框架前台开关】
#define MENU_FRAME_EN 		1	 			//允许SOLGUI菜单框架作为前台（1：是，0：否），选否则只可使用到中间层

//--------------【Widget开关】

#endif
