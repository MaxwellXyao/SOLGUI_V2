#include"SOLGUI_Include.h"

void SOLGUI_Pictrue(u32 x,u32 y,u32 x_len,u32 y_len,u8 *pic,u8 mode)
{
	int y_i=0,y_j=0,x_i=0,lie;
	unsigned char temp;

	if(y_len%8!=0) lie=y_len/8+1;	
	else lie=y_len/8;
	for(y_j=0;y_j<lie;y_j++)
	{
		for(x_i=0;x_i<x_len;x_i++)
		{
			temp=*(pic+y_j*x_len+x_i);
			for(y_i=0;y_i<8;y_i++)
			{
				if(temp&0x80)
				{
					 SOLGUI_DrawPoint(x+x_i,y+y_i-y_j*8-8,mode);
				}
				else
				{
					 SOLGUI_DrawPoint(x+x_i,y+y_i-y_j*8-8,!mode); 
				}
				temp<<=1;
			}
		}
	}
}
