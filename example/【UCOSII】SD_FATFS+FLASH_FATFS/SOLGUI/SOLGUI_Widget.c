#include"SOLGUI_Include.h"
#include<string.h>
#include<stdarg.h> 						//֧�ֱ䳤����



//##############################���������塿##############################
#if WIDGET_EDIT_EN==1&&MENU_FRAME_EN==1

//-----------��EDIT��
const u8 SOL_ASCII_IME_lowerchar[]	="abcdefghijklmnopqrstuvwxyz";
const u8 SOL_ASCII_IME_upperchar[]	="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const u8 SOL_ASCII_IME_Number[]		="0123456789+-*/=%()[]{}<>&|~^";
const u8 SOL_ASCII_IME_symbol[]		=" .,:;_?!@#$'\"\\";
const u8 SOL_ASCII_IME_CRLchar[]	={0x00,0x0a,0x0d};	//�������ַ�

IME_CLUSTER IME_CLUSTER_LC={0,"LOWER",26,SOL_ASCII_IME_lowerchar};		//��д�ַ���
IME_CLUSTER IME_CLUSTER_UC={0,"UPPER",26,SOL_ASCII_IME_upperchar};		//Сд�ַ���
IME_CLUSTER IME_CLUSTER_NU={0,"NUMBER",28,SOL_ASCII_IME_Number};		//�����ַ���
IME_CLUSTER IME_CLUSTER_SY={0,"SYMBOL",14,SOL_ASCII_IME_symbol};		//�����ַ���
IME_CLUSTER IME_CLUSTER_CR={0,"CTRL",3,SOL_ASCII_IME_CRLchar};			//�����ַ���

EDIT_IME SOL_ASCII_IME_REG={		//����ascii���뷨
	0,								//�ַ�����ǰָ�򴢴�
	SOL_ASCII_IME_SIZE,				//�ַ�����С
   {&IME_CLUSTER_LC,
	&IME_CLUSTER_UC,
	&IME_CLUSTER_NU,
	&IME_CLUSTER_SY,
	&IME_CLUSTER_CR}
};

EDIT_IME *SOL_ASCII_IME=&SOL_ASCII_IME_REG;

#endif


#if MENU_FRAME_EN==1
/*ѡ��������������
   >option0
	option1
	option2
	...
*/
//-----------������ࡿ
CURSOR cursor_reg={0,0,0,0,0,0};
CURSOR *cursor=&cursor_reg;			//���ȫ����Ϣ����

//-----------��ѡ��ʹ�ܱ�
u8 option_enable_list[OPTIONS_MAX];	//ѡ��ʹ�ܱ�,�˴����ԸĽ�

//-----------��GotoPage�ؼ���
extern MENU_PAGE *current_page;		//��ǰҳ��

//-----------��ռ�ñ�־�Ĵ�����
extern u8 SOLGUI_CSR;		//����ģʽ���ƼĴ���

//################################���ڲ����ú�����##############################

boolean _OptionsDisplay_Judge(u8 USN)
{
	if((USN-cursor->viewport_offset)>=0&&((USN-cursor->viewport_offset)<=cursor->viewport_width))	
		return(True);	//��ʾѡ��	
	else return(False);	 //����ʾѡ��	
}

u32 _OptionsDisplay_coorY(u8 USN)
{
	return((cursor->row_start-USN+cursor->viewport_offset)*8);
}

//################################����꡿##############################
//ѡ��ʽ�ؼ������й����ܲ���
void SOLGUI_Cursor(u8 rowBorder_Top,u8 rowBorder_Bottom,u8 option_num)		//��꣨�ϱ߽��У��±߽��У�ѡ�������	
{
	u8 i=0;
	u8 temp=0;
	u8 cur_key=0;
	u8 cursor_row=0;
	u8 cursor_abs_offset=0;	//���ľ���ƫ��

	double s_h=0;			//����ĸ߶�
	u32 s_y=0;				//�����λ��
//--------���������ˡ�
	if(rowBorder_Top<rowBorder_Bottom)		//Ĭ���ϱ߽�����±߽磬���򽻻�
	{
		temp=rowBorder_Top;
		rowBorder_Top=rowBorder_Bottom;
		rowBorder_Bottom=temp;
	}
	if(option_num>OPTIONS_MAX) option_num=OPTIONS_MAX;		//���������Ϊ���
//--------����ز������㡿
	cursor->row_start=rowBorder_Top;	//����ѡ����ʼ��
	cursor->viewport_width=rowBorder_Top-rowBorder_Bottom; //�ӿ���������
	if(option_num<=cursor->viewport_width) cursor->viewport_width=option_num-1;		//ѡ����С���ӿڿ�ȴ���
//--------����ֵ������
	cur_key=SOLGUI_GetCurrentKey();										//��ȡ��ǰȫ�ּ�ֵ
	if(cur_key==SOLGUI_KEY_UP){											//��ǰȫ��Ϊ�ϼ�
		if(cursor->cursor_rel_offset>0&&SOLGUI_CSR==0) cursor->cursor_rel_offset--;		//������ӿ�������	   	
		else if(cursor->viewport_offset>0&&SOLGUI_CSR==0) cursor->viewport_offset--;	 	//�ӿ�����	
	}
	else if(cur_key==SOLGUI_KEY_DOWN){								    //��ǰȫ��Ϊ�¼�
		if((cursor->cursor_rel_offset<cursor->viewport_width)&&SOLGUI_CSR==0) cursor->cursor_rel_offset++; //������ӿ�������
		else if((cursor->viewport_offset<option_num-cursor->viewport_width-1)&&SOLGUI_CSR==0) cursor->viewport_offset++;	 //�ӿ�����
	}
	cursor_abs_offset=cursor->viewport_offset+cursor->cursor_rel_offset;	//���㵱ǰ���ľ���ƫ��
//--------����Ļ���ơ�
	cursor->y_t=rowBorder_Top*8;									//��y����
	cursor->y_b=rowBorder_Bottom*8;									//��y����
//---����꡿
	cursor_row=cursor->y_t-cursor->cursor_rel_offset*8;	 		//���������ӿڵ�ƫ�ƻ������������
	SOLGUI_printf(0,cursor_row,F6X8,"%c",ICON_CURSOR);		//������
//---�����±��ߡ�
	if(rowBorder_Top!=6) SOLGUI_GBasic_Line(0,cursor->y_t+8,SCREEN_X_WIDTH-1,cursor->y_t+8,DOTTED);		//�ϱ���
	if(rowBorder_Top!=0) SOLGUI_GBasic_Line(0,cursor->y_b-1,SCREEN_X_WIDTH-1,cursor->y_b-1,DOTTED);		//�±���
//---������������������Ϊѡ����ӵĲ��֣�
	s_h=(double)(cursor->y_t-cursor->y_b+8)/(double)option_num;									//����߶�
	s_y=cursor->y_t+7-s_h*(cursor_abs_offset+1);										//����λ��
	SOLGUI_GBasic_Rectangle(SCREEN_X_WIDTH-4,s_y,SCREEN_X_WIDTH-1,s_y+s_h,FILL);	//����
	SOLGUI_GBasic_Rectangle(SCREEN_X_WIDTH-4,cursor->y_b,SCREEN_X_WIDTH-1,cursor->y_t+7,ACTUAL);	//�߿�
//--------���޸�ѡ��ʹ�ܱ�			
	for(i=0;i<=option_num;i++){
		option_enable_list[i]=(cursor_abs_offset==i)?1:0;	//��дѡ��ʹ�ܱ��ھ���ƫ��λ����Ϊ1������λ��Ϊ0��
	}
}

#endif

//##############################��ѡ��ʽ�ؼ���##############################


#if WIDGET_GOTOPAGE_EN==1&&MENU_FRAME_EN==1

void SOLGUI_Widget_GotoPage(u8 USN,MENU_PAGE *page)		//ҳ����ת�ؼ�
{
	u32 y_disp=0;	//��ѡ��Ӧ����ʾ����λ��
	u8 cur_key=0;	//��ֵ
	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//ȫ��ռ��
//--------���������ˡ�
	if(USN>=OPTIONS_MAX) return;		//USNֻ����ȡ0~OPTIONS_MAX-1
//--------��������ʾ�С�
	if(True==_OptionsDisplay_Judge(USN))
	{		
		y_disp=_OptionsDisplay_coorY(USN);
		if(option_enable_list[USN]==1)
		{
//--------����ֵ������
			cur_key=SOLGUI_GetCurrentKey();				//��ȡ��ǰȫ�ּ�ֵ
			if(cur_key==SOLGUI_KEY_OK){					//OK��			
				current_page=page;						//��ת
				cursor->cursor_rel_offset=0;					//��չ��ƫ�Ƽ�����
				cursor->viewport_offset=0;											
			}					
		}
//--------��ѡ����ơ�
		SOLGUI_printf(6,y_disp,F6X8,"%s",page->pageTitle);		//��һ��ҳ�����
		SOLGUI_printf(SCREEN_X_WIDTH-13,y_disp,F6X8,"%c",ICON_WIDGET_GOTOPAGE);	//ͼ��
//--------��������ʾ���ơ�
		if((cursor->viewport_offset+cursor->cursor_rel_offset)==USN)
		SOLGUI_printf(SCREEN_X_WIDTH-6,56,F6X8,"%c",ICON_OK);	//����ָʾ�����ݼ�ֵ������������д��
	}
}

#endif


#if WIDGET_SPIN_EN==1&&MENU_FRAME_EN==1

double _Pow_10(s8 n) 	//pow=10^n
{
	s16 i=0;
	s8 m=(n>=0)?n:-n;
	double p=1;

	for(i=0;i<m;i++)
	{
		if(n>=0) p*=10;
		else p*=0.1;
	}
	return(p);
}

void SOLGUI_Widget_Spin(u8 USN,const u8 *name,u8 type,double max,double min,void* value)		//������ť�ؼ�
{
	double swap;	
	u32 y_disp=0;	//��ѡ��Ӧ����ʾ����λ��
	u8 cur_key=0;	//��ֵ

	static s8 spin_pos=0;	//��ťλ��
	double dat_step=0;

	s8		*v_i8=NULL;
	u8		*v_u8=NULL;
	s16		*v_i16=NULL;
	s32		*v_i32=NULL;
	float 	*v_f16=NULL;
	double	*v_f32=NULL;

	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//ȫ��ռ��
//--------���������ˡ�
	if(max<min)
	{
		swap=max;
		max=min;
		min=swap;
	}
	if(USN>=OPTIONS_MAX) return;		//USNֻ����ȡ0~OPTIONS_MAX-1
//--------������׼����
	switch(type)
	{
		case INT8:	v_i8=(s8 *)value;break;
		case UINT8:	v_u8=(u8 *)value;break;  
		case INT32: v_i32=(s32 *)value; break;
		case FLT16: v_f16=(float *)value; break;
		case FLT32: v_f32=(double *)value; break;
		case INT16: ;	
		default:	v_i16=(s16 *)value; break;
	}
//--------��������ʾ�С�
	if(True==_OptionsDisplay_Judge(USN))
	{		
		y_disp=_OptionsDisplay_coorY(USN);
		if(option_enable_list[USN]==1)
		{
//--------����ֵ������
			cur_key=SOLGUI_GetCurrentKey();				//��ȡ��ǰȫ�ּ�ֵ
			if(cur_key==SOLGUI_KEY_OK){					//OK��			
				SOLGUI_CSR^=bit(0);						//CSR[0]��ת����1��ʾSPINռ��									
			}
			if(bit_istrue(SOLGUI_CSR,bit(0)))			//�������SPINռ����
			{
				dat_step=_Pow_10(spin_pos);				//������ڲ���ֵ

				if(cur_key==SOLGUI_KEY_UP)														//��ֵ�Ӳ���
				{
					switch(type)
					{
						case INT8:	{if(((*v_i8)+dat_step)<=max)(*v_i8)+=(s8)dat_step;}break;
						case UINT8:	{if(((*v_u8)+dat_step)<=max)(*v_u8)+=(u8)dat_step;}break;  
						case INT32: {if(((*v_i32)+dat_step)<=max)(*v_i32)+=(s32)dat_step;}break;
						case FLT16: {if(((*v_f16)+dat_step)<=max)(*v_f16)+=(float)dat_step;}break;
						case FLT32: {if(((*v_f32)+dat_step)<=max)(*v_f32)+=(double)dat_step;}break;
						case INT16: ;	
						default:	{if(((*v_i16)+dat_step)<=max)(*v_i16)+=(s16)dat_step;}break;
					}	
				}
				else if(cur_key==SOLGUI_KEY_DOWN)												//��ֵ������
				{
					switch(type)
					{
						case INT8:	{if(((*v_i8)-dat_step)>=min)(*v_i8)-=(s8)dat_step;}break;
						case UINT8:	{if(((*v_u8)-dat_step)>=min)(*v_u8)-=(u8)dat_step;}break;  
						case INT32: {if(((*v_i32)-dat_step)>=min)(*v_i32)-=(s32)dat_step;}break;
						case FLT16: {if(((*v_f16)-dat_step)>=min)(*v_f16)-=(float)dat_step;}break;
						case FLT32: {if(((*v_f32)-dat_step)>=min)(*v_f32)-=(double)dat_step;}break;
						case INT16: ;	
						default:	{if(((*v_i16)-dat_step)>=min)(*v_i16)-=(s16)dat_step;}break;
					}	
				}
				else if(cur_key==SOLGUI_KEY_LEFT)												//�󲽽�
				{
					if(spin_pos<SPIN_DIGIT_MAX-1) spin_pos++;						
				}
				else if(cur_key==SOLGUI_KEY_RIGHT)												//�Ҳ���
				{
					if((type==FLT16)||(type==FLT32)) { if(spin_pos>SPIN_DIGIT_MIN) spin_pos--; }	 //С��
					else { if(spin_pos>0) spin_pos--; }		//����Ĭ����������������չ��
				}
			}				
		}
//--------��ѡ�������&��ֵ���ơ�
		switch(type)
		{
			case INT8:	SOLGUI_printf(68,y_disp,F6X8,"%d",*v_i8);break;
			case UINT8:	SOLGUI_printf(68,y_disp,F6X8,"%d",*v_u8);break; 
			case INT32: SOLGUI_printf(68,y_disp,F6X8,"%d",*v_i32);break;
			case FLT16: SOLGUI_printf(68,y_disp,F6X8,"%f",*v_f16);break;
			case FLT32: SOLGUI_printf(68,y_disp,F6X8,"%f",*v_f32);break;
			case INT16: ;	
			default:	SOLGUI_printf(68,y_disp,F6X8,"%d",*v_i16);break;
		}

								
//--------����ť���ơ�
		if(bit_istrue(SOLGUI_CSR,bit(0))&&(option_enable_list[USN]==1)) 
		SOLGUI_printf(0,y_disp,~F6X8,"%c%f%c",ICON_LEFT,dat_step,ICON_RIGHT);	   	//�����������ģʽ�У���ʾ��ť��ֵ
		else SOLGUI_printf(6,y_disp,F6X8,"%s",name);		//������
//--------��������ʾ���ơ�
		if((cursor->viewport_offset+cursor->cursor_rel_offset)==USN)
		SOLGUI_printf(SCREEN_X_WIDTH-6,56,F6X8,"%c",ICON_OK);			//����ָʾ�����ݼ�ֵ������������д��
	}	
}

#endif



#if WIDGET_OPTIONTEXT_EN==1&&MENU_FRAME_EN==1

void SOLGUI_Widget_OptionText(u8 USN,const u8* str,...)					//ѡ���ı�
{
	va_list ap;
	u32 y_disp=0;	//��ѡ��Ӧ����ʾ����λ��
//	u8 t[SCREEN_X_PAGE-2];		//�ַ�����
//--------���������ˡ�
	if(USN>=OPTIONS_MAX) return;		//USNֻ����ȡ0~OPTIONS_MAX-1
//	_String_LenCtrlCpy(SCREEN_X_PAGE-2,t,(u8 *)str);
//--------��������ʾ�С�
	if(True==_OptionsDisplay_Judge(USN))
	{		
		y_disp=_OptionsDisplay_coorY(USN);
//--------��ѡ����ơ�
		va_start(ap,str);
		__SOLGUI_printf(6,y_disp,F6X8,str,ap);		//�ı���ʾ
		va_end(ap);
	}
}

#endif


#if WIDGET_BUTTON_EN==1&&MENU_FRAME_EN==1

void SOLGUI_Widget_Button(u8 USN,const u8 *name,void (*func)(void))				//����
{
	u32 y_disp=0;	//��ѡ��Ӧ����ʾ����λ��
	u8 cur_key=0;	//��ֵ
	u8 run_f=0;		//���мǺ�
	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//ȫ��ռ��
//--------���������ˡ�
	if(USN>=OPTIONS_MAX) return;		//USNֻ����ȡ0~OPTIONS_MAX-1
//--------��������ʾ�С�
	if(True==_OptionsDisplay_Judge(USN))
	{		
		y_disp=_OptionsDisplay_coorY(USN);
		if(option_enable_list[USN]==1)
		{
//--------����ֵ������
			cur_key=SOLGUI_GetCurrentKey();				//��ȡ��ǰȫ�ּ�ֵ
			if(cur_key==SOLGUI_KEY_OK){					//OK��			
				run_f=1;								
			}					
		}
//--------��ѡ����ơ�
		SOLGUI_printf(6,y_disp,F6X8,"%s",name);					//ѡ����
		SOLGUI_printf(68,y_disp,F6X8,"->");						//ͼ��
//--------������ǣ��������		
		if(run_f==1) 											//����OK��������ǣ������
		{
			run_f=0;											//ֻ����һ��
			func();	
		}
//--------��������ʾ���ơ�
		if((cursor->viewport_offset+cursor->cursor_rel_offset)==USN)
		SOLGUI_printf(SCREEN_X_WIDTH-6,56,F6X8,"%c",0x84);			//����ָʾ�����ݼ�ֵ������������д��
	}
}

#endif



#if WIDGET_SWITCH_EN==1&&MENU_FRAME_EN==1

void SOLGUI_Widget_Switch(u8 USN,const u8 *name,u32 *mem_value,u8 L_shift)		//�������أ�mem_value��һ���ⲿ����ķ���ʧ�Դ洢��������
{
	u32 y_disp=0;	//��ѡ��Ӧ����ʾ����λ��
	u8 cur_key=0;	//��ֵ
	u32 temp=bit(L_shift);
	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//ȫ��ռ��
//--------���������ˡ�
	if((L_shift<1)||(L_shift>32)) L_shift=1;	//С��1�����32������Ϊ1
	if(USN>=OPTIONS_MAX) return;		//USNֻ����ȡ0~OPTIONS_MAX-1
//--------��������ʾ�С�
	if(True==_OptionsDisplay_Judge(USN))
	{		
		y_disp=_OptionsDisplay_coorY(USN);
		if(option_enable_list[USN]==1)
		{
//--------����ֵ������
			cur_key=SOLGUI_GetCurrentKey();				//��ȡ��ǰȫ�ּ�ֵ
			if(cur_key==SOLGUI_KEY_OK){					//OK��			
				(*mem_value)^=temp;			//��Ҫ�ⲿ����ʧ�Դ���ռ�����������־λ������ĳλȡ��									
			}					
		}
//--------��ѡ����ơ�
		SOLGUI_printf(6,y_disp,F6X8,"%s",name);						//ѡ����
//--------��ͼ����ơ�
		if(bit_istrue((*mem_value),temp)) SOLGUI_printf(68,y_disp,F6X8,"[ON ]");				//"��"����	
		else SOLGUI_printf(68,y_disp,F6X8,"[OFF]");												//"��"����
//--------��������ʾ���ơ�
		if((cursor->viewport_offset+cursor->cursor_rel_offset)==USN)
		SOLGUI_printf(SCREEN_X_WIDTH-6,56,F6X8,"%c",0x84);			//����ָʾ�����ݼ�ֵ������������д��
	}	
}

#endif


#if WIDGET_EDIT_EN==1&&MENU_FRAME_EN==1

void _String_LenCtrlCpy(u16 dest_size,u8 *dest,u8 *sour)		  	//���������Ƶĸ���
{
	if(strlen((const char *)sour)>dest_size) strncpy((char *)dest,(char *)sour,dest_size);	 
	else strcpy((char *)dest,(char *)sour);	
}

void SOLGUI_Widget_Edit(u8 USN,const u8 *name,u16 char_num,u8 *buf)			//�ı��༭��
{	
	u32 y_disp=0;	//��ѡ��Ӧ����ʾ����λ��
	u8 cur_key=0;	//��ֵ
	u16 i=0,j=0,buf_i=0;
	u8 edit_thumbnail_buf[EDIT_THUMBNAIL_SIZE];	//��������
	static u8 edit_buf[EDIT_BUF_SIZE];			//�༭������buf	
	static u16 edit_cursor_row=0;				//�༭�������ַ�λ��
	static u16 edit_cursor_col=0;				//�༭��������ַ�λ��
	u16 edit_buf_size_temp=char_num<EDIT_BUF_SIZE?(char_num+1):EDIT_BUF_SIZE;
//--------���������ˡ�
	if(USN>=OPTIONS_MAX) return;		//USNֻ����ȡ0~OPTIONS_MAX-1
	
//--------��������ʾ�С�
	if(True==_OptionsDisplay_Judge(USN))
	{		
		y_disp=_OptionsDisplay_coorY(USN);
		if(option_enable_list[USN]==1)
		{
//--------����ֵ����������EDITռ�á�
			cur_key=SOLGUI_GetCurrentKey();				//��ȡ��ǰȫ�ּ�ֵ
			if(cur_key==SOLGUI_KEY_OK){					//OK��
//--------�����ָ��(0,0)λ�á�
				if((edit_cursor_row==0)&&(edit_cursor_col==0)) 	 //������ָ�ַ�(0,0)λ
				{
					if(bit_istrue(SOLGUI_CSR,bit(1)))	//����ڱ༭״̬��
					{
						SOLGUI_CSR&=(~bit(1));					//CSR[1]=0����0��ʾEDITռ�ý��
						_String_LenCtrlCpy(char_num,buf,edit_buf);	//���ϸ���buf
					}
					else
					{
						SOLGUI_CSR|=bit(1);					//CSR[1]=1����0��ʾEDITռ��
						memset(edit_buf,0,sizeof(edit_buf));			//edit_buf����
						_String_LenCtrlCpy(edit_buf_size_temp,edit_buf,buf);
					}
				}										
				else
				{
//--------�����ָ�������ַ�λ�ã����¿������뷨��
					SOLGUI_CSR^=bit(2);						//CSR[2]��ת����1��ʾ���뷨ռ��
				}
			}
			if(bit_istrue(SOLGUI_CSR,bit(1)))			//�������EDITռ��״̬��
			{
				buf_i=(SCREEN_X_PAGE-2)*edit_cursor_col+edit_cursor_row;	//�޸�λ�ü���	
//--------����ֵ������EDITռ���µĲ�����
				if(cur_key==SOLGUI_KEY_UP)								//�������&�ַ���
				{
					if(bit_istrue(SOLGUI_CSR,bit(2)) && (SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->finger
					< SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->size-1))
						SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->finger++;//���뷨��	
					else if(bit_isfalse(SOLGUI_CSR,bit(2))&&edit_cursor_col>0) 
						edit_cursor_col--;										//�ݹ���
				}
				else if(cur_key==SOLGUI_KEY_DOWN)								//�������&�ַ���
				{
					if(bit_istrue(SOLGUI_CSR,bit(2)) && (SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->finger>0))
						SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->finger--;//���뷨��	
					else if(bit_isfalse(SOLGUI_CSR,bit(2))&&edit_cursor_col<(SCREEN_Y_PAGE-4)
					&& ((buf_i+(SCREEN_X_PAGE-2))<edit_buf_size_temp)) 
						edit_cursor_col++;										//�ݹ���
				}
				else if(cur_key==SOLGUI_KEY_LEFT)						//�������&�ַ��������л�
				{
					if(bit_istrue(SOLGUI_CSR,bit(2))&&(SOL_ASCII_IME->finger>0)) SOL_ASCII_IME->finger--;	 //���뷨������
					else if(bit_isfalse(SOLGUI_CSR,bit(2))&&edit_cursor_row>0) edit_cursor_row--;			//�����
				}
				else if(cur_key==SOLGUI_KEY_RIGHT)						//�������&�ַ��������л�
				{
					if(bit_istrue(SOLGUI_CSR,bit(2))&&(SOL_ASCII_IME->finger<SOL_ASCII_IME->size-1)) SOL_ASCII_IME->finger++; //���뷨������	
					else if(bit_isfalse(SOLGUI_CSR,bit(2))&&edit_cursor_row<(SCREEN_X_PAGE-3)&&((buf_i+1)<edit_buf_size_temp)) 
						edit_cursor_row++;//�����
				}
			}				
		}
//--------��ѡ�������&��ֵ���ơ�
		if(bit_istrue(SOLGUI_CSR,bit(1)))
		{
//----����EDITռ���£���ʾ�༭����ȫ��ռ�ã���
//----[���Ʊ༭��]
			SOLGUI_Clean();					//������
			SOLGUI_GBasic_Rectangle(0,0,SCREEN_X_WIDTH-1,SCREEN_Y_WIDTH-1,ACTUAL);		//�߿�
			SOLGUI_GBasic_Line(0,9,SCREEN_X_WIDTH-1,9,ACTUAL);						//�ײ�����
			if(bit_istrue(SOLGUI_CSR,bit(2)))										//�ַ��༭״̬
			{
				edit_buf[buf_i-1]=SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->table[SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->finger];	//�ַ�����ֵ
				SOLGUI_printf(2,1,F6X8,"%s",SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->name);	   //�ַ�����
				SOLGUI_printf(64,1,F6X8,"[ %c ]",SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->table[SOL_ASCII_IME->cluster[SOL_ASCII_IME->finger]->finger]);
			}
			else if((edit_cursor_col==0)&&(edit_cursor_row==0))		 	//������ʾ
			{
				SOLGUI_printf(2,1,F6X8,"BACK");							//���ָ��backλ��
			}
			else
			{
				SOLGUI_printf(2,1,F6X8,"L:%d C:%d",edit_cursor_col+1,edit_cursor_row+1); //���ָ��ɱ༭�ַ�λ��
			}
//----[������ʾ]
			for(i=0;i<(SCREEN_Y_PAGE-3);i++)
			{
				for(j=0;j<(SCREEN_X_PAGE-2);j++)
				{
					if(i==0&&j==0)
					{
//----[����λ��ʾ(0,0)]
						if((edit_cursor_row==0)&&(edit_cursor_col==0)) 
							SOLGUI_printf(6,48,~F6X8,"%c",ICON_BACK);			//ȷ�ϲ���ָʾ���ַ�����(0,0)����
						else SOLGUI_printf(6,48,F6X8,"%c",ICON_BACK);			
					}
					else
					{
//----[�����ַ���ʾ]
						buf_i=(SCREEN_X_PAGE-2)*i+j-1;			//���ָ�ŵ�λ��
						if(buf_i<edit_buf_size_temp)
						{
							if((edit_cursor_row==j)&&(edit_cursor_col==i))					//���ָ����ַ� 
							{
								if(edit_buf[buf_i]=='\0') SOLGUI_printf(6+j*6,48-i*8,~F6X8,"%c",ICON_OTHER_HIDE);	//'\0'��'...'����ʾ�����ɱ༭����
								else SOLGUI_printf(6+j*6,48-i*8,~F6X8,"%c",edit_buf[buf_i]);			//ѡ�е��ַ�����ʾ
							}
							else 
							{	
								if(edit_buf[buf_i]=='\0') SOLGUI_printf(6+j*6,48-i*8,F6X8,"%c",ICON_OTHER_HIDE);   //'\0'��'...'����ʾ�����ɱ༭����
								else SOLGUI_printf(6+j*6,48-i*8,F6X8,"%c",edit_buf[buf_i]);
							}
						}
						else 
						{
							i=SCREEN_Y_PAGE; j=SCREEN_X_PAGE;	//����ѭ��
						}
					}
				}
			}												
		}
		else
		{
//----������EDITռ���£���ʾѡ�
			SOLGUI_printf(6,y_disp,F6X8,"%s",name);		//������
			_String_LenCtrlCpy(EDIT_THUMBNAIL_SIZE,edit_thumbnail_buf,buf);	//��������Ϣ�����и���
			SOLGUI_printf(68,y_disp,F6X8,"%s",edit_thumbnail_buf);			//����������ʾ
			if(strlen((const char *)buf)>(SCREEN_X_PAGE-14))SOLGUI_printf(SCREEN_X_WIDTH-19,y_disp,F6X8,"%c",ICON_OTHER_HIDE);	//��������ͼ��
			SOLGUI_printf(SCREEN_X_WIDTH-13,y_disp,F6X8,"%c",ICON_WIDGET_EDIT);	//EDITͼ��
		}
//--------��������ʾ���ơ�
		if((cursor->viewport_offset+cursor->cursor_rel_offset)==USN)
		SOLGUI_printf(SCREEN_X_WIDTH-6,56,F6X8,"%c",ICON_OK);			//����ָʾ�����ݼ�ֵ������������д��
	}	
}

#endif

//##############################������ʽ�ؼ���##############################

#if WIDGET_TEXT_EN==1&&MENU_FRAME_EN==1

void SOLGUI_Widget_Text(u32 x0,u32 y0,u8 mode,const u8* str,...)
{
	va_list ap;
//--------����ǰ״̬��
	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//ȫ��ռ��
//--------�����������
	va_start(ap,str);
	__SOLGUI_printf(x0,y0,mode,str,ap); 		//ʹ���ڲ�printf�����ݱ䳤����
	va_end(ap);	
}

#endif


#if WIDGET_BAR_EN==1&&MENU_FRAME_EN==1

void SOLGUI_Widget_Bar(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,s32 value,u8 mode)		//��
{
	s32 swap=0;
	double f=0;
	u32 d=0;

//--------����ǰ״̬��
	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//ȫ��ռ��
//--------���������ˡ�
	if(max<min)
	{
		swap=max;
		max=min;
		min=swap;
	}
	value=(value<max)?value:max;
	value=(value>min)?value:min;

//----------������ÿ�񲽳���
	f=(double)(value-min)/(double)(max-min);
//----------������x����������
	if((mode&0x01)==DIREC_X)				//x����
	{
		d=f*xsize;
		if((mode&0x06)==PROGBAR) 			//������
		{
			SOLGUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+ysize,ACTUAL);
			SOLGUI_GBasic_Rectangle(x0,y0,x0+d,y0+ysize,FILL);		
		}
		else if((mode&0x06)==SCALEBAR)		//�̶�
		{
			SOLGUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+ysize,ACTUAL);
			SOLGUI_GBasic_Rectangle(x0,y0,x0+d,y0+ysize,ACTUAL);
			SOLGUI_GBasic_Line(x0,y0+ysize,x0+xsize,y0+ysize,DELETE);
		}
	}
	else									//y����
	{
//----------������y����������		
		d=f*ysize;
		if((mode&0x06)==PROGBAR) 			//������
		{
			SOLGUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+ysize,ACTUAL);
			SOLGUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+d,FILL);
		}
		else if((mode&0x06)==SCALEBAR)		//�̶�
		{
			SOLGUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+ysize,ACTUAL);
			SOLGUI_GBasic_Rectangle(x0,y0,x0+xsize,y0+d,ACTUAL);
			SOLGUI_GBasic_Line(x0,y0,x0,y0+ysize,DELETE);
		}
	}
}

#endif


#if MENU_FRAME_EN==1&&(WIDGET_SPECTRUM_EN==1||WIDGET_OSCILLOGRAM_EN==1)

void SOLGUI_Widget_Spectrum(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,u16 val_num,s32 value[])
{
	s32 swap=0;
	u16 i=0;
	double delta_x=0,delta_y=0;
	double x_p=0;
	u32 x_last=x0,y_last=y0,y_zero=0;
	s32 val_now=0;

	u32 x_now=0,y_now=0;

//--------����ǰ״̬��
	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//ȫ��ռ��
//--------���������ˡ�
	if(max<min)
	{
		swap=max;
		max=min;
		min=swap;
	}
//------------����ؼ��㡿
	delta_x=(double)(val_num)/(double)(xsize);		//����
	delta_y=(double)(ysize)/(double)(max-min);		//����һ�������Ƕ���ֵ
//------------�����߻��ơ�
	for(i=0;i<xsize;i++)
	{
		x_p+=delta_x;
		val_now=value[(int)x_p];
		x_now=x0+i;
		if((val_now>=min)&&(val_now<max)) y_now=y0+(u32)((val_now-min)*delta_y);
		else if(val_now<min) y_now=y0;
		else y_now=y0+ysize-1;
		SOLGUI_GBasic_Line(x_last,y_last,x_now,y_now,ACTUAL);
		x_last=x_now;
		y_last=y_now;	
	}
//------------�������ơ�
	SOLGUI_GBasic_Rectangle(x0,y0,x0+xsize-1,y0+ysize-1,ACTUAL);
//------------�������ơ�
	if(min<0)
	{
		y_zero=y0+(u32)((-min)*delta_y);
		SOLGUI_DrawPoint(x0+1,y_zero,1);
	}	
}

#endif


#if WIDGET_OSCILLOGRAM_EN==1&&MENU_FRAME_EN==1

void SOLGUI_Widget_Oscillogram(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,WaveMemBlk *wmb)	  //����Ҫͨ��̽���������ݸ���
{
//--------����ǰ״̬��
	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//ȫ��ռ��
//--------����ͼ��
	SOLGUI_Widget_Spectrum(x0,y0,xsize,ysize,max,min,wmb->size,wmb->mem);	//�����׻��Ʋ���
}

void SOLGUI_Oscillogram_Probe(WaveMemBlk *wmb,s32 value)									//̽��
{
	u16 f=0,b=1;
//--------�����ݶ��в�����				
	for(f=0,b=1;b<wmb->size;f++,b++){
		wmb->mem[f]=wmb->mem[b];				//������λ,O(n)
	}
	wmb->mem[wmb->size-1]=value;				//ĩβ���������	
}

#endif


#if WIDGET_PICTURE_EN==1&&MENU_FRAME_EN==1

void SOLGUI_Widget_Picture(u32 x0,u32 y0,u32 xsize,u32 ysize,const u8 *pic,u32 x_len,u32 y_len,u8 mode)	//����С�����ͼƬ�ؼ� 
{
	float fw=0,fh=0;
	u16 temp_x=0,temp_y=0;
	u16 y_i=0,x_i=0;
	u32 y0_t=y0+ysize;	//��ԭ���Ϊ���½ǣ�ԭ��ԭ��Ϊ���Ͻǣ�
	u8 m1=0;
//--------����ǰ״̬��
	if(bit_istrue(SOLGUI_CSR,bit(1))) return;	//ȫ��ռ��
	m1=bit_isfalse(mode,bit(7));				//�Ƿ񷴰�
//------------��ͼƬֱ�����ơ�
	if((xsize>=x_len)&&(ysize>=y_len)) 
		SOLGUI_Pictrue(x0,y0,pic,x_len,y_len,m1);
	else {
//------------��ͼƬ�����С���ơ�
		fw=(float)x_len/xsize; fh=(float)y_len/ysize;	//��С��
		for(x_i=0;x_i<xsize;x_i++)
		{
			temp_x=(u16)(fw*x_i);		 //�ٽ���ֵ�����㷨
			for(y_i=0;y_i<ysize;y_i++)
			{
				temp_y=(u16)(fh*y_i);		  
			   	if(SOLGUI_GetPixel(temp_x,temp_y,pic,x_len,y_len)) SOLGUI_DrawPoint(x0+x_i,y0_t-y_i,m1);
			   	else SOLGUI_DrawPoint(x0+x_i,y0_t-y_i,!m1);
			}
		}
	};	
//-----���߿���ơ�
	if(bit_istrue(mode,bit(6))) SOLGUI_GBasic_Rectangle(x0,y0,x0+xsize-1,y0+ysize-1,ACTUAL);
}

#endif




