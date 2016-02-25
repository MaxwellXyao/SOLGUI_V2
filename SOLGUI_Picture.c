#include"SOLGUI_Include.h"

void SOLGUI_Pictrue(u32 x,u32 y,const u8 *pic,u32 x_len,u32 y_len,u8 mode)
{
	s16 y_i=0,y_j=0,x_i=0,lie;
	u32 yii=0,yb=y;
	u8 temp;

	y=y+y_len;		//坐标转换
	if(y_len%8!=0) lie=y_len/8+1;	
	else lie=y_len/8;
	for(y_j=0;y_j<lie;y_j++)
	{
		for(x_i=0;x_i<x_len;x_i++)
		{
			temp=*(pic+y_j*x_len+x_i);
			for(y_i=0;y_i<8;y_i++)
			{
				yii=y+y_i-y_j*8-8;
				if(yii>=yb){
					if(temp&0x80) SOLGUI_DrawPoint(x+x_i,yii,mode);
					else SOLGUI_DrawPoint(x+x_i,yii,!mode);
				}
				temp<<=1;
			}
		}
	}
}

void SOLGUI_Pictrue_Resize(u32 x,u32 y,double fw,double fh,const u8 *pic,u32 x_len,u32 y_len,u8 mode)	//带缩放的图形显示
{
	s16 y_i=0,y_j=0,x_i=0,lie;
	u32 yii=0,yb=y;
	u8 temp;

	y=y+y_len;		//坐标转换
	if(y_len%8!=0) lie=y_len/8+1;	
	else lie=y_len/8;
	for(y_j=0;y_j<lie;y_j++)
	{
		for(x_i=0;x_i<x_len;x_i++)
		{
			temp=*(pic+y_j*x_len+x_i);
			for(y_i=0;y_i<8;y_i++)
			{
				yii=y+y_i-y_j*8-8;
				if(yii>=yb){
					if(temp&0x80) SOLGUI_DrawPoint(x+x_i,yii,mode);
					else SOLGUI_DrawPoint(x+x_i,yii,!mode);
				}
				temp<<=1;
			}
		}
	}
}
