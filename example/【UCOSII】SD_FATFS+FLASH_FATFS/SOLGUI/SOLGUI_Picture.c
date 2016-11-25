#include"SOLGUI_Include.h"

void SOLGUI_Pictrue(u32 x0,u32 y0,const u8 *pic,u32 x_len,u32 y_len,u8 mode)		//原尺寸直出
{
	s16 y_i=0,x_i=0;
	y0+=y_len; 	//将原点改为左下角（原本原点为右上角）
	for(x_i=0;x_i<x_len;x_i++)
	{
		for(y_i=0;y_i<y_len;y_i++)
		{
		   if(SOLGUI_GetPixel(x_i,y_i,pic,x_len,y_len)) SOLGUI_DrawPoint(x0+x_i,y0-y_i,mode);
		   else SOLGUI_DrawPoint(x0+x_i,y0-y_i,!mode);
		}
	}
}

u8 SOLGUI_GetPixel(u32 x,u32 y,const u8 *pic,u32 x_len,u32 y_len)		//获取像素点值（原点为左上角为）
{     
	return bit_istrue(*(pic+(y>>3)*x_len+x),bit((7-y%8)));
}
