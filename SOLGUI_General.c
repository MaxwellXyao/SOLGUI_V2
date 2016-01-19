#include"pixelC_Hardware_include.h"

const unsigned char G6x8[][6] ={
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// sp
0x00, 0x00, 0x00, 0x2f, 0x00, 0x00,// !
0x00, 0x00, 0x07, 0x00, 0x07, 0x00,// "
0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14,// #
0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12,// $
0x00, 0x62, 0x64, 0x08, 0x13, 0x23,// %
0x00, 0x36, 0x49, 0x55, 0x22, 0x50,// &
0x00, 0x00, 0x05, 0x03, 0x00, 0x00,// '
0x00, 0x00, 0x1c, 0x22, 0x41, 0x00,// (
0x00, 0x00, 0x41, 0x22, 0x1c, 0x00,// )
0x00, 0x14, 0x08, 0x3E, 0x08, 0x14,// *
0x00, 0x08, 0x08, 0x3E, 0x08, 0x08,// +
0x00, 0x00, 0x00, 0xA0, 0x60, 0x00,// ,
0x00, 0x08, 0x08, 0x08, 0x08, 0x08,// -
0x00, 0x00, 0x60, 0x60, 0x00, 0x00,// .
0x00, 0x20, 0x10, 0x08, 0x04, 0x02,// /
0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
0x00, 0x00, 0x42, 0x7F, 0x40, 0x00,// 1
0x00, 0x42, 0x61, 0x51, 0x49, 0x46,// 2
0x00, 0x21, 0x41, 0x45, 0x4B, 0x31,// 3
0x00, 0x18, 0x14, 0x12, 0x7F, 0x10,// 4
0x00, 0x27, 0x45, 0x45, 0x45, 0x39,// 5
0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
0x00, 0x01, 0x71, 0x09, 0x05, 0x03,// 7
0x00, 0x36, 0x49, 0x49, 0x49, 0x36,// 8
0x00, 0x06, 0x49, 0x49, 0x29, 0x1E,// 9
0x00, 0x00, 0x36, 0x36, 0x00, 0x00,// :
0x00, 0x00, 0x56, 0x36, 0x00, 0x00,// ;
0x00, 0x08, 0x14, 0x22, 0x41, 0x00,// <
0x00, 0x14, 0x14, 0x14, 0x14, 0x14,// =
0x00, 0x00, 0x41, 0x22, 0x14, 0x08,// >
0x00, 0x02, 0x01, 0x51, 0x09, 0x06,// ?
0x00, 0x32, 0x49, 0x59, 0x51, 0x3E,// @
0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C,// A
0x00, 0x7F, 0x49, 0x49, 0x49, 0x36,// B
0x00, 0x3E, 0x41, 0x41, 0x41, 0x22,// C
0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C,// D
0x00, 0x7F, 0x49, 0x49, 0x49, 0x41,// E
0x00, 0x7F, 0x09, 0x09, 0x09, 0x01,// F
0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A,// G
0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F,// H
0x00, 0x00, 0x41, 0x7F, 0x41, 0x00,// I
0x00, 0x20, 0x40, 0x41, 0x3F, 0x01,// J
0x00, 0x7F, 0x08, 0x14, 0x22, 0x41,// K
0x00, 0x7F, 0x40, 0x40, 0x40, 0x40,// L
0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F,// M
0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F,// N
0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E,// O
0x00, 0x7F, 0x09, 0x09, 0x09, 0x06,// P
0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
0x00, 0x7F, 0x09, 0x19, 0x29, 0x46,// R
0x00, 0x46, 0x49, 0x49, 0x49, 0x31,// S
0x00, 0x01, 0x01, 0x7F, 0x01, 0x01,// T
0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F,// U
0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F,// V
0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F,// W
0x00, 0x63, 0x14, 0x08, 0x14, 0x63,// X
0x00, 0x07, 0x08, 0x70, 0x08, 0x07,// Y
0x00, 0x61, 0x51, 0x49, 0x45, 0x43,// Z
0x00, 0x00, 0x7F, 0x41, 0x41, 0x00,// [
0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55,// 55
0x00, 0x00, 0x41, 0x41, 0x7F, 0x00,// ]
0x00, 0x04, 0x02, 0x01, 0x02, 0x04,// ^
0x40, 0x40, 0x40, 0x40, 0x40, 0x40,// _
0x00, 0x00, 0x01, 0x02, 0x04, 0x00,// '
0x00, 0x20, 0x54, 0x54, 0x54, 0x78,// a
0x00, 0x7F, 0x48, 0x44, 0x44, 0x38,// b
0x00, 0x38, 0x44, 0x44, 0x44, 0x20,// c
0x00, 0x38, 0x44, 0x44, 0x48, 0x7F,// d
0x00, 0x38, 0x54, 0x54, 0x54, 0x18,// e
0x00, 0x08, 0x7E, 0x09, 0x01, 0x02,// f
0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C,// g
0x00, 0x7F, 0x08, 0x04, 0x04, 0x78,// h
0x00, 0x00, 0x44, 0x7D, 0x40, 0x00,// i
0x00, 0x40, 0x80, 0x84, 0x7D, 0x00,// j
0x00, 0x7F, 0x10, 0x28, 0x44, 0x00,// k
0x00, 0x00, 0x41, 0x7F, 0x40, 0x00,// l
0x00, 0x7C, 0x04, 0x18, 0x04, 0x78,// m
0x00, 0x7C, 0x08, 0x04, 0x04, 0x78,// n
0x00, 0x38, 0x44, 0x44, 0x44, 0x38,// o
0x00, 0xFC, 0x24, 0x24, 0x24, 0x18,// p
0x00, 0x18, 0x24, 0x24, 0x18, 0xFC,// q
0x00, 0x7C, 0x08, 0x04, 0x04, 0x08,// r
0x00, 0x48, 0x54, 0x54, 0x54, 0x20,// s
0x00, 0x04, 0x3F, 0x44, 0x40, 0x20,// t
0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C,// u
0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C,// v
0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C,// w
0x00, 0x44, 0x28, 0x10, 0x28, 0x44,// x
0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C,// y
0x00, 0x44, 0x64, 0x54, 0x4C, 0x44,// z
0x00, 0x82, 0x82, 0x6C, 0x10, 0x00,// {
0x00, 0x00, 0x00, 0xFF, 0x00, 0x00,// |
0x00, 0x10, 0x6C, 0x82, 0x82, 0x00,// }
0x10, 0x20, 0x10, 0x08, 0x10, 0x00,//~
0x14, 0x14, 0x14, 0x14, 0x14, 0x14,// hirozy line
};

/************GRAM定义************/
unsigned char SOLGUI_GRAM[X_WIDTH][Y_PAGE];
/************波形图变量队列定义************/
unsigned int SOLGUI_Wave_CH1[X_WIDTH];		//波形缓存1
unsigned int SOLGUI_Wave_CH2[X_WIDTH]; 		//波形缓存2

//##############################API##############################

void SOLGUI_Init(void)
{
	SOLGUI_Graph_Wave_Init();
}

void SOLGUI_Refresh_GRAM()		//刷新GRAM
{
	int i=0,n=0,j=0;
	for(i=0;i<Y_PAGE;i++)
	{
		pixelC_HW_OLED_WrCmd(0xb0+i);
		pixelC_HW_OLED_WrCmd(0x00);
		pixelC_HW_OLED_WrCmd(0x10);
		for(n=0;n<X_WIDTH;n++)
		{
			pixelC_HW_OLED_WrDat(SOLGUI_GRAM[n][i]);
		}
	}	
	for(i=0;i<X_WIDTH;i++)
	{
		for(j=0;j<Y_PAGE;j++)
		{
			 SOLGUI_GRAM[i][j]=0;
		}
	}
}

void SOLGUI_DrawPoint(unsigned char x,unsigned char y,unsigned char t)			//画点，t=1点亮；t=0熄灭.
{
	unsigned char pos,bx,temp=0;
	if(x>=(X_WIDTH)||y>=(Y_WIDTH))	//0~127
	{
		return;//超出范围了.
	}
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)
	{
		SOLGUI_GRAM[x][pos]|=temp;
	}
	else 
	{
		SOLGUI_GRAM[x][pos]&=~temp;
	}

}

//----------<字符显示>

void SOLGUI_Show_Char(unsigned char x,unsigned char y,unsigned char ch,unsigned char mode)//显示单个字符（mode：1正常显示，0高亮显示）
{
	unsigned char temp,t,tl;
	unsigned char y0=y;
	ch=ch-' ';
	for(t=0;t<6;t++)
	{
		 temp=G6x8[ch][t];
		 for(tl=0;tl<8;tl++)
		 {
		 	if(temp&0x80)
			{
				SOLGUI_DrawPoint(x,y,mode);
			}
			else
			{
				SOLGUI_DrawPoint(x,y,!mode);
			}
			temp<<=1;
			y++;
			if((y-y0)==8)
			{ 
				y=y0;
				x++;
				break;
			}
		 }
	}
}

void SOLGUI_Show_String(unsigned char x,unsigned char y,unsigned char *str,unsigned char mode)	//显示字符串（mode：1正常显示，0高亮显示）
{
	unsigned char j=0;
	while (str[j]!='\0')
	{		
		SOLGUI_Show_Char(x,y,str[j],mode);
		x+=6;
		j++;
	}
}

/***************************************************************************/

void SOLGUI_printf(
	unsigned char x,
	unsigned char y,
	unsigned char mode,
	const unsigned char* str,
	...					
)
{
	va_list arp;
	unsigned char xpp=x;
	unsigned char f,r,fl=0,l=3,lt;		//默认留3位小数,小数可留0~7位
	unsigned char i,j,w,lp;
	unsigned long v;
	char c, d, s[16], *p;
	int res, chc, cc,ll;
	int kh,kl,pow=1;
	double k;

	va_start(arp, str);								//变长参数栈始点在str

	for (cc=res=0;cc!=-1;res+=cc) 		   			//解析格式化字符串，且输出
	{
		c = *str++;						   			//每一轮取一个字符
//---------------------------------//读取到'\0',结束程序
		if (c == 0) break;					
//---------------------------------//读取到非'%'符号时
		if (c != '%') {						
			//cc = f_putc(c, fil);		   			//正常输出字符
			SOLGUI_Show_Char(xpp,y,c,mode);
			xpp+=6;
			continue;
		}
//---------------------------------//读取到'%'符号时
		w=f=0;
		k=0;
		lp=0;
		c=*str++;				   					//越过'%'，读其格式
		if (c == '0') {								//%0，0填充
			f = 1; c = *str++;						//f0填充标记位置1，读取下一个字符
		} 
		else if (c == '-') {							//%-，左对齐（左边填空格）
				f = 2; c = *str++;					//f左对齐标记位置1，读取下一个字符
			}
		else if (c == '.') {						//%.3f表示留3位小数
			fl=1;c=*str++;
		}

		while (((c)>='0')&&((c)<='9')) {			//"%030"，将30转换为数字
			if(fl==1){
				lp=lp*10+c-'0';		
				c=*str++;
			}
			else{
				w=w*10+c-'0';		
				c=*str++;
			}								//将数字读完
		}
		if(fl==1) l=(lp>7)? 7:lp;
		if (c == 'l' || c == 'L') {					//%ld等长形数
			f |= 4; c = *str++;		 				//f长形标记位置1，读下一个字符
		}
		if (!c) break;								//如果此时无字符，结束输出
//---------------------------------//处理格式化标识符（d,s,c,x,o,f）
		d = c;						
		if (((c)>='a')&&((c)<='z')) d -= 0x20;		//如果是小写，划归成大写处理
		switch (d) {								//分类%*的情况

		case 'S' :					/* String */
			p = va_arg(arp,char*);					//取字符串变量
			for(j=0;p[j];j++);						//长度计算
			ll=j;
			chc = 0;
			if (!(f&2)) {							//不用左对齐，左边就要补空格%06s
				while (j++ < w) 
				{
					SOLGUI_Show_Char(xpp,y,' ',mode);
					chc+=1;
					xpp+=6;
				}
			}
			SOLGUI_Show_String(xpp,y,(unsigned char *)p,mode);
			xpp=xpp+6*ll;
			chc+=ll;
			while (j++ < w) 						//左对齐，左边就不用空格，右边填空格%-06s
			{
				SOLGUI_Show_Char(xpp,y,' ',mode);
				chc+=1;
				xpp+=6;
			}	 
			cc = chc;
			continue;

		case 'C' :
		{					/* Character */
		//	cc = f_putc((TCHAR)va_arg(arp, int), fil); continue;
			SOLGUI_Show_Char(xpp,y,(char)va_arg(arp,int),mode);
			xpp+=6;
			continue;
		}

		case 'F' :											//默认保留3位小数
		{													/* double(64位)/float(32位) */												
			k=va_arg(arp,double);
			if(k<0){
				l|=8;
				k*=-1;										//负数置低位1
			}
			kh=(int)k;										//整数小数分离
			lt=l&7;
			while((lt-1)>=0){
				pow*=10;
				lt--;
			}
			kl=(int)(pow*(k-kh));				
			i=0;

			lt=l&7;
			while(lt--){												//存入小数部分
				if(kl){
					d=(char)(kl%10);							//按10进制取余，即取个位，化归为字符处理
					kl/=10;										//递进								
					s[i++]='0'+d;								//倒叙存入s
				}
				else s[i++]='0';
			}

			s[i++]='.';										//加入小数点
			do{												//存入整数部分
				d=(char)(kh%10);								//按10进制取余，即取个位，化归为字符处理
				kh/=10;										//递进
				s[i++]='0'+d;								//倒叙存入s
			}while(kh && i<sizeof s /sizeof s[0]);
			if (l&8)s[i++]='-';								//添加符号（注意低位在前）
			fl=0;	
			goto PRT;
		}
		case 'B' :					/* Binary */
			r = 2; break;
		case 'O' :					/* Octal */
			r = 8; break;
		case 'D' :					/* Signed decimal */
		case 'U' :					/* Unsigned decimal */
			r = 10; break;
		case 'X' :					/* Hexdecimal */
			r = 16; break;
		default:{					/* Unknown type (pass-through) */
				SOLGUI_Show_Char(xpp,y,c,mode);
				xpp+=6;
				cc=1;
				continue;
			}
		}

		/* Get an argument and put it in numeral */
/*取变量  是%ld型？		有则按long取变量			没有l但有d则按int取变量						没有l也没有d则先按unsigned int取变量在做处理	*/
		v =(f&4)?(unsigned long)va_arg(arp, long):((d=='D')?(unsigned long)(long)va_arg(arp, int):(unsigned long)va_arg(arp, unsigned int));
		if (d == 'D' && (v & 0x80000000)) {					//是%d，且符号位为1（负数）	//只有int型有增幅之分
			v = 0 - v;										//化归为正数处理
			f |= 8;											//f符号标记位置1
		}
		i = 0;
		do {												//数字解析成字符
			d=(char)(v%r);									//按进制r取余，即取个位，化归为字符处理
			v/=r;											//递进
			if(d>9)d+=(c=='x')?0x27:0x07;					//判读，不是10进制而是16进制时，d欲先加一个间隔跳转至'A'(大写X)或'a'(小写X)
			s[i++]=d+'0';									//化归为字符串处理（注意低位在前）
		} while (v && i<sizeof s /sizeof s[0]);				//（i<sizeof s /sizeof s[0]）防止含0类数字误判
		if (f & 8) s[i++] = '-';							//添加符号（注意低位在前）
PRT:		
		j=i;
		d=(f&1)?'0':' ';									//判断0填充还是左对齐
		while (!(f&2)&&j++<w)
		{
			//res+=(cc = f_putc(d, fil));	//不用左对齐，左边就要补0或空格
			SOLGUI_Show_Char(xpp,y,d,mode);
			xpp+=6;
		}
		do 
		{
			//res += (cc = f_putc(s[--i], fil)); 
			SOLGUI_Show_Char(xpp,y,s[--i],mode);
			xpp+=6;
		}while(i);

		while (j++ < w) 
		{
			//res += (cc = f_putc(' ', fil));		//右边补空格
			SOLGUI_Show_Char(xpp,y,d,mode);
			xpp+=6;
		}
	}
	va_end(arp);
}

/***************************************************************************/

//-------------------------------------------
//----------<图形显示>

char SOLGUI_Find_Max(char input[],char num) 				//找数组最大值
{
	int i;
	char max;
	max=input[0];
	for(i=1;i<num;i++)
	{
		if(input[i]>max)
		{
			max=input[i];
		}
	}
	return(max);
}

char SOLGUI_Find_Min(char input[],char num) 				//找数组最大值
{
	int i;
	char min;
	min=input[0];
	for(i=1;i<num;i++)
	{
		if(input[i]<min)
		{
			min=input[i];
		}
	}
	return(min);
}

void SOLGUI_Graph_line(			unsigned char x0,unsigned char y0,		 //画线	（mode：0擦除线，1实线，2点线，3短划线）
								unsigned char xEnd,unsigned char yEnd,
								unsigned char mode)		
{
	int dx=xEnd-x0;
	int dy=yEnd-y0;
	int ux=((dx>0)<<1)-1;//x的增量方向，取或-1
	int uy=((dy>0)<<1)-1;//y的增量方向，取或-1
	int x=x0,y=y0,eps;//eps为累加误差
	unsigned char cnt=0;
	
	eps=0;
	dx=SOLGUI_Fabs(dx);
	dy=SOLGUI_Fabs(dy); 
	if(dx>dy) 
	{
		for(x=x0;x!=xEnd+ux;x+=ux)
		{
			cnt++;
			switch(mode)
			{
				case 0:SOLGUI_DrawPoint(x,y,0);break;  			//0擦除线
				case 1:
				{
					SOLGUI_DrawPoint(x,y,1);break;	   			//1实线
				}
				case 2:
				{
					if(cnt%2>=1)SOLGUI_DrawPoint(x,y,1); 	//2点线	
					else	SOLGUI_DrawPoint(x,y,0);break;	
				}
				case 3:
				{
					if(cnt%4>=2)SOLGUI_DrawPoint(x,y,1);  		//3短划线
					else	SOLGUI_DrawPoint(x,y,0);break;		
				}	
			}
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
			switch(mode)
			{
				case 0:SOLGUI_DrawPoint(x,y,0);break;  			//0擦除线
				case 1:
				{
					SOLGUI_DrawPoint(x,y,1);break;	   			//1实线
				}
				case 2:
				{
					if(cnt%2>=1)SOLGUI_DrawPoint(x,y,1); 	//2点线	
					else	SOLGUI_DrawPoint(x,y,0);break;	
				}
				case 3:
				{
					if(cnt%4>=2)SOLGUI_DrawPoint(x,y,1);  		//3短划线
					else	SOLGUI_DrawPoint(x,y,0);break;		
				}	
			}
			eps+=dx;
			if((eps<<1)>=dy)
			{
				x+=ux; 
				eps-=dy;
			}
		}
	}   


		
     

}

void SOLGUI_Graph_Circle(unsigned char x0,unsigned char y0,unsigned char r,unsigned char mode)			//画圆（圆心，半径，1点亮0熄灭）
{
	int x,y,s;
	for(x=x0-r;x<=x0+r;x++){	
		for(y=y0-r;y<=y0+r;y++){	
			s=(x-x0)*(x-x0)+(y-y0)*(y-y0);	
			if(s-r*r<r&&s-r*r>-r)
			SOLGUI_DrawPoint(x,y,mode);
		}	
	}	
}

void SOLGUI_Graph_pictrue(	unsigned char x,			//句柄x坐标	 	//图标
							unsigned char y,			//句柄y坐标
							unsigned char x_len,		//图形长
							unsigned char y_len,		//图形宽
							unsigned char *pic,			//图
							unsigned char mode 			//显示方式：1正常显示，0高亮显示
							)
{
	int y_i=0,y_j=0,x_i=0,lie;
	unsigned char temp;

	if(y_len%8!=0)
	{
		lie=y_len/8+1;	
	}
	else
	{
		lie=y_len/8;
	}
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


//----------<图表显示>

void SOLGUI_Plot_Bar(unsigned char x,			//句柄x坐标	 	//数值条(显示数值相对大小)
					unsigned char y,			//句柄y坐标
					unsigned char x_len,		//图形长
					unsigned char y_len,		//图形宽
					int graduated_max,			//标尺最大值
					int graduated_min,			//标尺最小值
					int Var_in,					//值输入
					unsigned char mode 			//显示方式：0进度条，1位置条
)
{
	int i,j;
	double Y_zoom,X_zoom;
	unsigned char temp;	

	if(x_len>=y_len)		//X方向生长
	{
//---------------<缩放系数>-------------------
		X_zoom=(double)(x_len)/(double)(graduated_max-graduated_min);		//计算一个像素是多少值
		temp=(unsigned char)((Var_in-graduated_min)*X_zoom);								//应该显示的像素长度
//---------------<绘图>-------------------
		if(mode==0)
		{
			for(i=0;i<x_len;i++)
			{
				SOLGUI_DrawPoint(x+i,y,1);			   //边框上下
				SOLGUI_DrawPoint(x+i,y+y_len,1);
			}
			for(i=0;i<y_len+1;i++)
			{
				SOLGUI_DrawPoint(x,y+i,1);			   //边框左右
				SOLGUI_DrawPoint(x+x_len,y+i,1);
			}
			for(i=0;i<temp;i++)
			{
				for(j=0;j<y_len;j++)
				{
					if(temp>x_len)	temp=x_len;
					SOLGUI_DrawPoint(x+i,y+j,1);			//填充色条填充
				}
			}
		}
		else if(mode==1)
		{
			for(i=0;i<x_len;i++)
			{
				SOLGUI_DrawPoint(x+i,y,1);			   //边框上下
			}
			for(i=0;i<y_len+1;i++)
			{
				SOLGUI_DrawPoint(x,y+i,1);			   //边框左右
				SOLGUI_DrawPoint(x+x_len,y+i,1);
			}
			for(j=0;j<y_len;j++)
			{
				if(temp>x_len)	temp=x_len;
				SOLGUI_DrawPoint(x+temp,y+j,1);			//填充色条填充
			}
		}
			
	}
	else				//Y方向生长
	{

//---------------<缩放系数>-------------------
		Y_zoom=(double)(y_len)/(double)(graduated_max-graduated_min);		//计算一个像素是多少值
		temp=(unsigned char)((Var_in-graduated_min)*Y_zoom);								//应该显示的像素长度
//---------------<绘图>-------------------
		if(mode==0)
		{
			for(i=0;i<y_len;i++)
			{
				SOLGUI_DrawPoint(x,y+i,1);
				SOLGUI_DrawPoint(x+x_len,y+i,1);
			}
			for(i=0;i<x_len+1;i++)
			{
				SOLGUI_DrawPoint(x+i,y,1);
				SOLGUI_DrawPoint(x+i,y+y_len,1);
			}
			for(i=0;i<temp;i++)
			{
				for(j=0;j<x_len;j++)
				{
					if(temp>y_len)	temp=y_len;
					SOLGUI_DrawPoint(x+j,y+i,1);
				}
			}
		}
		else if(mode==1)
		{
			for(i=0;i<y_len;i++)
			{
				SOLGUI_DrawPoint(x+x_len,y+i,1);
			}
			for(i=0;i<x_len+1;i++)
			{
				SOLGUI_DrawPoint(x+i,y,1);
				SOLGUI_DrawPoint(x+i,y+y_len,1);
			}
			for(j=0;j<x_len;j++)
			{
				if(temp>y_len)	temp=y_len;	
				SOLGUI_DrawPoint(x+j,y+temp,1);
			}
		}

	}	
}


void OLED_Plot_Oscillogram(	unsigned char x,			//句柄x坐标	 	//波形图(显示数组)
							unsigned char y,			//句柄y坐标
							unsigned char x_len,		//图形长
							unsigned char y_len,		//图形宽
							int graduated_max,			//标尺最大值
							int graduated_min,			//标尺最小值
							unsigned char dis_num,		//要显示的数据个数（wave_in[0]~wave_in[dis_num]）
							int wave_in[]				//波形数组
							)
{
	int i;
	double Y_zoom,X_zoom,x_count=0;
	char temp;
	int last_x=x,last_y=y;

	x_len-=1;
	y_len-=1;
	if((x+x_len)>X_WIDTH)	x_len=X_WIDTH-x-1; //限位
	if((y+y_len)>Y_WIDTH)	y_len=Y_WIDTH-y-1;
//------------<坐标轴显示>-------------------
	SOLGUI_DrawPoint(x,y,1);					//初始化图形
	for(i=1;i<x_len;i++)
	{
		SOLGUI_DrawPoint(x+i,y,1);			//x轴
	}
	SOLGUI_DrawPoint(x+x_len-1,y+1,1);
	for(i=1;i<y_len;i++)
	{
		SOLGUI_DrawPoint(x,y+i,1);			//y轴
	}
	SOLGUI_DrawPoint(x+1,y+y_len-1,1);
//---------------<缩放系数>-------------------
	X_zoom=(double)(dis_num)/(double)(x_len);							//计算
	Y_zoom=(double)(y_len)/(double)(graduated_max-graduated_min);		//计算一个像素是多少值
//---------------<波形显示核心>---------------
	for(i=0;i<x_len;i++)
	{
		x_count+=X_zoom;
		if((wave_in[(int)x_count]>=graduated_min)&&(wave_in[(int)x_count]<graduated_max))
		{
			temp=(unsigned char)((wave_in[(int)x_count]-graduated_min)*Y_zoom);
			SOLGUI_Graph_line(last_x,last_y,x+i,(y+temp),1);
			last_x=x+i;
			last_y=(y+temp);
		}
	}
}

void SOLGUI_Graph_Wave_Init()								//波形RAM初始化
{
	int i;
	for(i=0;i<X_WIDTH;i++)
	{
		SOLGUI_Wave_CH1[i]=0;
		SOLGUI_Wave_CH2[i]=0;
	}
}

void SOLGUI_Plot_Waveform(	unsigned char x,			//句柄x坐标	 	//波形图表(显示数值时域波动)
							unsigned char y,			//句柄y坐标
							unsigned char x_len,		//图形长
							unsigned char y_len,		//图形宽
							int graduated_max,			//标尺最大值
							int graduated_min,			//标尺最小值
							unsigned char channel,		//使用通道
							int Var_in					//欲显示波形的变量
							)
{
	int i,fwd,bck;
	double Y_zoom,X_zoom,x_count=0;
	char temp;
	int last_x=x,last_y=y;

	x_len-=1;
	y_len-=1;
	if((x+x_len)>X_WIDTH)	x_len=X_WIDTH-x-1; //限位
	if((y+y_len)>Y_WIDTH)	y_len=Y_WIDTH-y-1;
//------------<坐标轴显示>-------------------
	SOLGUI_DrawPoint(x,y,1);					//初始化图形
	for(i=1;i<x_len;i++)
	{
		SOLGUI_DrawPoint(x+i,y,1);			//x轴
	}
	SOLGUI_DrawPoint(x+x_len-1,y+1,1);
	for(i=1;i<y_len;i++)
	{
		SOLGUI_DrawPoint(x,y+i,1);			//y轴
	}
	SOLGUI_DrawPoint(x+1,y+y_len-1,1);
//---------------<缩放系数>-------------------
	X_zoom=(double)(X_WIDTH)/(double)(x_len);							//计算
	Y_zoom=(double)(y_len)/(double)(graduated_max-graduated_min);		//计算一个像素是多少值

	if(channel==2)							//通道选择默认1通道；
	{
//---------------<生成变量队列>---------------
		for(fwd=0,bck=1;bck<X_WIDTH;fwd++,bck++)
		{
			SOLGUI_Wave_CH2[fwd]=SOLGUI_Wave_CH2[bck];
		}
		SOLGUI_Wave_CH2[X_WIDTH-1]=Var_in;
//---------------<波形显示核心>---------------
		for(i=0;i<x_len;i++)
		{
			x_count+=X_zoom;
			if((SOLGUI_Wave_CH2[(int)x_count]>=graduated_min)&&(SOLGUI_Wave_CH2[(int)x_count]<graduated_max))
			{
				temp=(unsigned char)((SOLGUI_Wave_CH2[(int)x_count]-graduated_min)*Y_zoom);
				SOLGUI_Graph_line(last_x,last_y,x+i,(y+temp),1);
				last_x=x+i;
				last_y=(y+temp);
			}
		}
	}
	else
	{
//---------------<生成变量队列>---------------
		for(fwd=0,bck=1;bck<X_WIDTH;fwd++,bck++)
		{
			SOLGUI_Wave_CH1[fwd]=SOLGUI_Wave_CH1[bck];
		}
		SOLGUI_Wave_CH1[X_WIDTH-1]=Var_in;
//---------------<波形显示核心>---------------
		for(i=0;i<x_len;i++)
		{
			x_count+=X_zoom;
			if((SOLGUI_Wave_CH1[(int)x_count]>=graduated_min)&&(SOLGUI_Wave_CH1[(int)x_count]<graduated_max))
			{
				temp=(unsigned char)((SOLGUI_Wave_CH1[(int)x_count]-graduated_min)*Y_zoom);
				SOLGUI_Graph_line(last_x,last_y,x+i,(y+temp),1);
				last_x=x+i;
				last_y=(y+temp);
			}
		}
	}
}

