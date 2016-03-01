#ifndef SOLGUI_PRINTF_H
#define SOLGUI_PRINTF_H

#include<stdarg.h> 						//支持变长参数

//##############################【参数宏】##############################
//-------------【mode参数】
//      F宽X高	值
#define F6X8 	0x01  		//6x8字体正常显示（默认） //00000001
#define R6X8 	0xfe		//6x8字体反白显示（或0）

#define F4X6 	0x02		//4X6字体正常显示		  //00000010
#define R4X6 	0xfd		//4X6字体反白显示

#define F8X8 	0x04		//8X8字体正常显示		  //00000100
#define R8X8 	0xfb		//8X8字体反白显示

#define F8X10 	0x08		//8X10字体正常显示		  //00001000
#define R8X10 	0xf7		//8X10字体反白显示

/*---------------------
可以自行后续添加字库
---------------------*/
//########################【字库信息结构体】########################
typedef struct _FontInfo{
	u8 FontMask;		//字符选择掩码
	u8 FontWidth;		//字符宽度
	u8 FontHeight;		//字符高度
	const u8 *Fontp;	//字符库指针
}FontInfo;

//###########################【内部使用】############################
void __SOLGUI_printf(u32 x,u32 y,u8 mode,const u8* str,va_list arp);		//SOLGUI内部使用的屏幕printf底层



//##############################【API】##############################
void SOLGUI_printf(u32 x,u32 y,u8 mode,const u8* str,...);	//显示格式化字符串（mode：1正常显示，0高亮显示）

#endif


