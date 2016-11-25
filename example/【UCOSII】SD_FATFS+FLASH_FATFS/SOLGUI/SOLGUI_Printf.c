#include"SOLGUI_Include.h"
#include<stdarg.h> 						//支持变长参数

//########################【字库文件】########################
#include"Font6x8_ASCII.h"
#include"Font4x6_ASCII.h"
#include"Font8x8_ASCII.h"
#include"Font8x10_ASCII.h"

//########################【字库选择】########################
//---------------------【字库注册】

FontInfo _fontInfo_6x8={0x01,6,8,(u8*)_Font6x8};	   	//Font6x8_ASCII

#if FONT4X6_EN==1
FontInfo _fontInfo_4x6={0x02,4,6,(u8*)_Font4x6};		//Font4x6_ASCII
#endif
#if FONT8X8_EN==1
FontInfo _fontInfo_8x8={0x04,8,8,(u8*)_Font8x8};	   	//Font8x8_ASCII
#endif
#if FONT8X10_EN==1
FontInfo _fontInfo_8x10={0x08,8,10,(u8*)_Font8x10};	   	//Font8x10_ASCII
#endif

//---------------------【字库选择器】
FontInfo SOLGUI_SwitchFont(u8 mode)
{
	switch(mode)
	{
		case F6X8:
		case 0:
		case R6X8:	return(_fontInfo_6x8);
#if FONT4X6_EN==1
		case F4X6:
		case R4X6:	return(_fontInfo_4x6);
#endif
#if FONT8X8_EN==1
		case F8X8:
		case R8X8:	return(_fontInfo_8x8);
#endif
#if FONT8X10_EN==1
		case F8X10:
		case R8X10:	return(_fontInfo_8x10);
#endif
		default: 	return(_fontInfo_6x8);
	}
}


//########################【内部使用】########################
//----------------【在屏幕上输出字符】
void SOLGUI_PutChar(u32 x,u32 y,u8 ch,u8 mode)//显示单个字符（mode：1正常显示，0高亮显示）
{
	u8 temp,m=1,tl,x0=x;
	s8 t;
	FontInfo fi=SOLGUI_SwitchFont(mode);
	m=mode&fi.FontMask;
//-------------【字符显示】  
	ch=ch-' ';
	for(t=fi.FontHeight-1;t>=0;t--)								
	{	
		 temp=*(fi.Fontp+ch*fi.FontHeight+t);
		 for(tl=0;tl<8;tl++)
		 {
		 	if(temp&0x80) SOLGUI_DrawPoint(x,y,m);
			else SOLGUI_DrawPoint(x,y,!m);
			temp<<=1;
			x++;
			if((x-x0)==8)
			{ 
				x=x0;
				y++;
				break;
			}
		 }
	}
}

//----------------【在屏幕上输出字符串】

void SOLGUI_PutString(u32 x,u32 y,const u8 *str,u8 mode)	//显示字符串（mode：1正常显示，0高亮显示）
{
	u8 j=0;
	FontInfo fi=SOLGUI_SwitchFont(mode);
//-------------【字库选择】
	while (str[j]!='\0')
	{		
		SOLGUI_PutChar(x,y,str[j],mode);
		x+=fi.FontWidth;										
		j++;
	}
}


//##############################【API】##############################

void __SOLGUI_printf(u32 x,u32 y,u8 mode,const u8* str,va_list arp)		//SOLGUI内部使用的屏幕printf底层
{
	u8 xpp=x;
	u8 f,r,fl=0,l=3,lt;		//默认留3位小数,小数可留0~7位
	u8 i,j,w,lp;
	u32 v;
	s8 c, d, s[16], *p;
	s16 res, chc, cc,ll;
	s16 kh,kl,pow=1;
	double k;
	FontInfo fi=SOLGUI_SwitchFont(mode);

	for (cc=res=0;cc!=-1;res+=cc) 		   			//解析格式化字符串，且输出
	{
		c = *str++;						   			//每一轮取一个字符
//---------------------------------//读取到'\0',结束程序
		if (c == 0) break;					
//---------------------------------//读取到非'%'符号时
		if (c != '%') {						
			//cc = f_putc(c, fil);		   			//正常输出字符
			SOLGUI_PutChar(xpp,y,c,mode);
			xpp+=fi.FontWidth;									
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
			p = va_arg(arp,s8*);					//取字符串变量
			for(j=0;p[j];j++);						//长度计算
			ll=j;
			chc = 0;
			if (!(f&2)) {							//不用左对齐，左边就要补空格%06s
				while (j++ < w) 
				{
					SOLGUI_PutChar(xpp,y,' ',mode);
					chc+=1;
					xpp+=fi.FontWidth;						
				}
			}
			SOLGUI_PutString(xpp,y,(unsigned char *)p,mode);
			xpp=xpp+fi.FontWidth*ll;						
			chc+=ll;
			while (j++ < w) 						//左对齐，左边就不用空格，右边填空格%-06s
			{
				SOLGUI_PutChar(xpp,y,' ',mode);
				chc+=1;
				xpp+=fi.FontWidth;						
			}	 
			cc = chc;
			continue;

		case 'C' :
		{					/* Character */
		//	cc = f_putc((TCHAR)va_arg(arp, int), fil); continue;
			SOLGUI_PutChar(xpp,y,(char)va_arg(arp,int),mode);
			xpp+=fi.FontWidth;								
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
			pow=1;
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
				SOLGUI_PutChar(xpp,y,c,mode);
				xpp+=fi.FontWidth;								
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
			SOLGUI_PutChar(xpp,y,d,mode);
			xpp+=fi.FontWidth;									
		}
		do 
		{
			//res += (cc = f_putc(s[--i], fil)); 
			SOLGUI_PutChar(xpp,y,s[--i],mode);
			xpp+=fi.FontWidth;									
		}while(i);

		while (j++ < w) 
		{
			//res += (cc = f_putc(' ', fil));		//右边补空格
			SOLGUI_PutChar(xpp,y,d,mode);
			xpp+=fi.FontWidth;										
		}
	}
}


//----------------【在屏幕上格式化输出字符串】
void SOLGUI_printf(u32 x,u32 y,u8 mode,const u8* str,...)			//外部使用的API版printf函数
{
	va_list arp;
	va_start(arp,str);								//变长参数栈始点在str
	__SOLGUI_printf(x,y,mode,str,arp);				//调用底层
	va_end(arp);
}


