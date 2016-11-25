#include"SOLGUI_Include.h"

#if GBASIC_LINE_EN==1||MENU_FRAME_EN==1


void _LineModes(s16 x,s16 y,u8 mode,u32 cnt)  		//����
{
	switch(mode&0x03)
	{
		case 0:SOLGUI_DrawPoint(x,y,0);break;  			//0������
		case 2:
		{
			if(cnt%2>=1) SOLGUI_DrawPoint(x,y,1); 	//2����	
			else	SOLGUI_DrawPoint(x,y,0);break;	
		}
		case 3:
		{
			if(cnt%4>=2) SOLGUI_DrawPoint(x,y,1);  		//3�̻���
			else	SOLGUI_DrawPoint(x,y,0);break;		
		}
		case 1:;										//1ʵ��
		default:SOLGUI_DrawPoint(x,y,1);	   			
	}	
}

void SOLGUI_GBasic_Line(u32 x0,u32 y0,u32 xEnd,u32 yEnd,u8 mode)		//���ߣ�mode��0�����ߣ�1ʵ�ߣ�2���ߣ�3�̻��ߣ�
{
	s16 dx=xEnd-x0;
	s16 dy=yEnd-y0;
	s16 ux=((dx>0)<<1)-1;//x����������ȡ��-1
	s16 uy=((dy>0)<<1)-1;//y����������ȡ��-1
	s16 x=x0,y=y0,eps;//epsΪ�ۼ����
	u32 cnt=0;
	
	eps=0;
	dx=SOLGUI_Fabs(dx);
	dy=SOLGUI_Fabs(dy); 
	if(dx>dy) 
	{
		for(x=x0;x!=xEnd+ux;x+=ux)
		{
			cnt++;
			_LineModes(x,y,mode,cnt);
			eps+=dy;
			if((eps<<1)>=dx)
			{
				y+=uy;
				eps-=dx;
			}
		}
	}
	else
	{
		for(y=y0;y!=yEnd+uy;y+=uy)
		{
			cnt++;
			_LineModes(x,y,mode,cnt);
			eps+=dx;
			if((eps<<1)>=dy)
			{
				x+=ux; 
				eps-=dy;
			}
		}
	}   
}

void SOLGUI_GBasic_MultiLine(const u32 *points,u8 num,u8 mode)
{
	u32 x0,y0;
	u32 x1,y1;
	u8 i=0;
	if(num<=0) return;		//û�е�
	if(1==num)				// ����
	{  
		x0=*points++;
		y0=*points;
		SOLGUI_DrawPoint(x0,y0,1);
	}
   /* ���������� */
	x0=*points++;					// ȡ����һ������ֵ����Ϊԭ�������ֵ
	y0=*points++;
	for(i=1;i<num;i++)
	{  
		x1=*points++;				// ȡ����һ������ֵ
		y1=*points++;
		SOLGUI_GBasic_Line(x0,y0,x1,y1,mode);
		x0=x1;					// ����ԭ�������
		y0=y1;
	}

}

#endif


#if GBASIC_RECTANGLE_EN==1||MENU_FRAME_EN==1

void  SOLGUI_GBasic_Rectangle(u32 x0,u32 y0,u32 x1,u32 y1,u8 mode)		//�����Σ����½ǣ����Ͻǣ�ģʽ��
{
	u32 i=0;
	u8 m=0;
	if(bit_istrue(mode,bit(2))||(mode==DELETE))	//�Ƿ����
	{
		if(x0>x1) {i=x0;x0=x1;x1=i;}	//��x0>x1����x0��x1����
		if(y0>y1) {i=y0;y0=y1;y1=i;}	//��y0>y1����y0��y1����
		if(mode==DELETE) m=DELETE;
		else m=ACTUAL;
		if(y0==y1) 
		{  
			SOLGUI_GBasic_Line(x0,y0,x1,y0,m);
			return;
		}
		if(x0==x1) 
		{  
			SOLGUI_GBasic_Line(x0,y0,x0,y1,m);
			return;
		}						
		while(y0<=y1)						
		{  
			SOLGUI_GBasic_Line(x0,y0,x1,y0,m);
			y0++;				
		}
	}
	else			   //�����
	{
		SOLGUI_GBasic_Line(x0,y0,x0,y1,mode);
		SOLGUI_GBasic_Line(x0,y1,x1,y1,mode);
		SOLGUI_GBasic_Line(x1,y0,x1,y1,mode);
		SOLGUI_GBasic_Line(x0,y0,x1,y0,mode);
	}
}

#endif


#if GBASIC_CIRCLE_EN==1||MENU_FRAME_EN==1
						                        
void SOLGUI_GBasic_Circle(u32 x0,u32 y0,u32 r,u8 mode)
{
	u16 x=0,y=r;
	s16 delta,temp;
	
	delta = 3-(r<<1);  //3-r*2
	while(y>x)
	{
		if(mode==FILL)
		{
			SOLGUI_GBasic_Line(x0+x,y0+y,x0-x,y0+y,ACTUAL);
			SOLGUI_GBasic_Line(x0+x,y0-y,x0-x,y0-y,ACTUAL);
			SOLGUI_GBasic_Line(x0+y,y0+x,x0-y,y0+x,ACTUAL);
			SOLGUI_GBasic_Line(x0+y,y0-x,x0-y,y0-x,ACTUAL);
		}
		else
		{
			SOLGUI_DrawPoint(x0+x,y0+y,mode);
			SOLGUI_DrawPoint(x0-x,y0+y,mode);
			SOLGUI_DrawPoint(x0+x,y0-y,mode);
			SOLGUI_DrawPoint(x0-x,y0-y,mode);
			SOLGUI_DrawPoint(x0+y,y0+x,mode);
			SOLGUI_DrawPoint(x0-y,y0+x,mode);
			SOLGUI_DrawPoint(x0+y,y0-x,mode);
			SOLGUI_DrawPoint(x0-y,y0-x,mode);
		}
		x++;
		if(delta >= 0)
		{
			y--;
			temp= (x<<2); //x*4
			temp-=(y<<2); //y*4
			delta += (temp+10);
		}
		else
		{
			delta += ((x<<2)+6); //x*4 + 6
		}
	}
}

#endif

