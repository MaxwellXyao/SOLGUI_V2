#ifndef SOLGUI_PICTURE_H
#define SOLGUI_PICTURE_H

//##########################【mode参数】############################

#define	NORMAL	0x01	//正常显示
#define	REVERSE	0x00	//反白显示

//##########################【API】############################
void SOLGUI_Pictrue(u32 x0,u32 y0,const u8 *pic,u32 x_len,u32 y_len,u8 mode);		//单色图片显示（mode：0反白，1正常）
//应储存为1维数组，取模方式列行式：数据水平，字节垂直，从左到右，从上到下扫描
u8 SOLGUI_GetPixel(u32 x,u32 y,const u8 *pic,u32 x_len,u32 y_len);				//获取像素点值（返回1点亮，0熄灭）

#endif

