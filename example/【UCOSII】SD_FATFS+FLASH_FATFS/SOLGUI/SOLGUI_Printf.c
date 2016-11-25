#include"SOLGUI_Include.h"
#include<stdarg.h> 						//֧�ֱ䳤����

//########################���ֿ��ļ���########################
#include"Font6x8_ASCII.h"
#include"Font4x6_ASCII.h"
#include"Font8x8_ASCII.h"
#include"Font8x10_ASCII.h"

//########################���ֿ�ѡ��########################
//---------------------���ֿ�ע�᡿

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

//---------------------���ֿ�ѡ������
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


//########################���ڲ�ʹ�á�########################
//----------------������Ļ������ַ���
void SOLGUI_PutChar(u32 x,u32 y,u8 ch,u8 mode)//��ʾ�����ַ���mode��1������ʾ��0������ʾ��
{
	u8 temp,m=1,tl,x0=x;
	s8 t;
	FontInfo fi=SOLGUI_SwitchFont(mode);
	m=mode&fi.FontMask;
//-------------���ַ���ʾ��  
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

//----------------������Ļ������ַ�����

void SOLGUI_PutString(u32 x,u32 y,const u8 *str,u8 mode)	//��ʾ�ַ�����mode��1������ʾ��0������ʾ��
{
	u8 j=0;
	FontInfo fi=SOLGUI_SwitchFont(mode);
//-------------���ֿ�ѡ��
	while (str[j]!='\0')
	{		
		SOLGUI_PutChar(x,y,str[j],mode);
		x+=fi.FontWidth;										
		j++;
	}
}


//##############################��API��##############################

void __SOLGUI_printf(u32 x,u32 y,u8 mode,const u8* str,va_list arp)		//SOLGUI�ڲ�ʹ�õ���Ļprintf�ײ�
{
	u8 xpp=x;
	u8 f,r,fl=0,l=3,lt;		//Ĭ����3λС��,С������0~7λ
	u8 i,j,w,lp;
	u32 v;
	s8 c, d, s[16], *p;
	s16 res, chc, cc,ll;
	s16 kh,kl,pow=1;
	double k;
	FontInfo fi=SOLGUI_SwitchFont(mode);

	for (cc=res=0;cc!=-1;res+=cc) 		   			//������ʽ���ַ����������
	{
		c = *str++;						   			//ÿһ��ȡһ���ַ�
//---------------------------------//��ȡ��'\0',��������
		if (c == 0) break;					
//---------------------------------//��ȡ����'%'����ʱ
		if (c != '%') {						
			//cc = f_putc(c, fil);		   			//��������ַ�
			SOLGUI_PutChar(xpp,y,c,mode);
			xpp+=fi.FontWidth;									
			continue;
		}
//---------------------------------//��ȡ��'%'����ʱ
		w=f=0;
		k=0;
		lp=0;
		c=*str++;				   					//Խ��'%'�������ʽ
		if (c == '0') {								//%0��0���
			f = 1; c = *str++;						//f0�����λ��1����ȡ��һ���ַ�
		} 
		else if (c == '-') {							//%-������루�����ո�
				f = 2; c = *str++;					//f�������λ��1����ȡ��һ���ַ�
			}
		else if (c == '.') {						//%.3f��ʾ��3λС��
			fl=1;c=*str++;
		}

		while (((c)>='0')&&((c)<='9')) {			//"%030"����30ת��Ϊ����
			if(fl==1){
				lp=lp*10+c-'0';		
				c=*str++;
			}
			else{
				w=w*10+c-'0';		
				c=*str++;
			}								//�����ֶ���
		}
		if(fl==1) l=(lp>7)? 7:lp;
		if (c == 'l' || c == 'L') {					//%ld�ȳ�����
			f |= 4; c = *str++;		 				//f���α��λ��1������һ���ַ�
		}
		if (!c) break;								//�����ʱ���ַ����������
//---------------------------------//�����ʽ����ʶ����d,s,c,x,o,f��
		d = c;						
		if (((c)>='a')&&((c)<='z')) d -= 0x20;		//�����Сд������ɴ�д����
		switch (d) {								//����%*�����

		case 'S' :					/* String */
			p = va_arg(arp,s8*);					//ȡ�ַ�������
			for(j=0;p[j];j++);						//���ȼ���
			ll=j;
			chc = 0;
			if (!(f&2)) {							//��������룬��߾�Ҫ���ո�%06s
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
			while (j++ < w) 						//����룬��߾Ͳ��ÿո��ұ���ո�%-06s
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

		case 'F' :											//Ĭ�ϱ���3λС��
		{													/* double(64λ)/float(32λ) */												
			k=va_arg(arp,double);
			if(k<0){
				l|=8;
				k*=-1;										//�����õ�λ1
			}
			kh=(int)k;										//����С������
			pow=1;
			lt=l&7;
			while((lt-1)>=0){
				pow*=10;
				lt--;
			}
			kl=(int)(pow*(k-kh));				
			i=0;

			lt=l&7;
			while(lt--){												//����С������
				if(kl){
					d=(char)(kl%10);							//��10����ȡ�࣬��ȡ��λ������Ϊ�ַ�����
					kl/=10;										//�ݽ�								
					s[i++]='0'+d;								//�������s
				}
				else s[i++]='0';
			}

			s[i++]='.';										//����С����
			do{												//������������
				d=(char)(kh%10);								//��10����ȡ�࣬��ȡ��λ������Ϊ�ַ�����
				kh/=10;										//�ݽ�
				s[i++]='0'+d;								//�������s
			}while(kh && i<sizeof s /sizeof s[0]);
			if (l&8)s[i++]='-';								//��ӷ��ţ�ע���λ��ǰ��
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
/*ȡ����  ��%ld�ͣ�		����longȡ����			û��l����d��intȡ����						û��lҲû��d���Ȱ�unsigned intȡ������������	*/
		v =(f&4)?(unsigned long)va_arg(arp, long):((d=='D')?(unsigned long)(long)va_arg(arp, int):(unsigned long)va_arg(arp, unsigned int));
		if (d == 'D' && (v & 0x80000000)) {					//��%d���ҷ���λΪ1��������	//ֻ��int��������֮��
			v = 0 - v;										//����Ϊ��������
			f |= 8;											//f���ű��λ��1
		}
		i = 0;
		do {												//���ֽ������ַ�
			d=(char)(v%r);									//������rȡ�࣬��ȡ��λ������Ϊ�ַ�����
			v/=r;											//�ݽ�
			if(d>9)d+=(c=='x')?0x27:0x07;					//�ж�������10���ƶ���16����ʱ��d���ȼ�һ�������ת��'A'(��дX)��'a'(СдX)
			s[i++]=d+'0';									//����Ϊ�ַ�������ע���λ��ǰ��
		} while (v && i<sizeof s /sizeof s[0]);				//��i<sizeof s /sizeof s[0]����ֹ��0����������
		if (f & 8) s[i++] = '-';							//��ӷ��ţ�ע���λ��ǰ��
PRT:		
		j=i;
		d=(f&1)?'0':' ';									//�ж�0��仹�������
		while (!(f&2)&&j++<w)
		{
			//res+=(cc = f_putc(d, fil));	//��������룬��߾�Ҫ��0��ո�
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
			//res += (cc = f_putc(' ', fil));		//�ұ߲��ո�
			SOLGUI_PutChar(xpp,y,d,mode);
			xpp+=fi.FontWidth;										
		}
	}
}


//----------------������Ļ�ϸ�ʽ������ַ�����
void SOLGUI_printf(u32 x,u32 y,u8 mode,const u8* str,...)			//�ⲿʹ�õ�API��printf����
{
	va_list arp;
	va_start(arp,str);								//�䳤����ջʼ����str
	__SOLGUI_printf(x,y,mode,str,arp);				//���õײ�
	va_end(arp);
}


