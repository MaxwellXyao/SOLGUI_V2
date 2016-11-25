#include "project_include.h"




//###############################������������###############################
//==========================[START ����]============================
#define START_TASK_PRIO 43 				//�����������ȼ�����ʼ��������ȼ�����Ϊ��ͣ�
#define START_STK_SIZE 64			   	//���������ջ��С
OS_STK START_TASK_STK[START_STK_SIZE];	//���������ջ�ռ�
void start_task(void *pdata);			//�������ӿ�

//==========================[MAIN ����]============================					
#define MAIN_TASK_PRIO 10				//�����������ȼ�
#define MAIN_TASK_STK_SIZE 512			//���������ջ��С
OS_STK MAIN_TASK_STK[MAIN_TASK_STK_SIZE];  //���������ջ�ռ�
void Main_task(void *pdata);			//�������ӿ�

//########################################��������########################################

MENU_PAGE index,page_flagLightTest,page_KeyTest,page_fatfsTest;						//ҳ������

//########################################������Ŀ¼��########################################
__M_PAGE(index,"pixelC3",PAGE_NULL,{		//�귽ʽ����ҳ��
	SOLGUI_Cursor(6,0,4);
	SOLGUI_Widget_GotoPage(0,&page_flagLightTest);
	SOLGUI_Widget_GotoPage(1,&page_KeyTest);
	SOLGUI_Widget_GotoPage(2,&page_fatfsTest);
});


//########################################����־�Ʋ��ԡ�########################################

__M_PAGE(page_flagLightTest,"Flaglight",&index,{		//�귽ʽ����ҳ��
	SOLGUI_Cursor(6,0,3);
	SOLGUI_Widget_Button(0,"On",FlagLight_On);						
	SOLGUI_Widget_Button(1,"Off",FlagLight_Off);
	SOLGUI_Widget_Button(2,"Blink",FlagLight_Blink);
});

//########################################���������ԡ�########################################

__M_PAGE(page_KeyTest,"Key",&index,{		//�귽ʽ����ҳ��
	u8 k=0;
	static u8 k1=0;

	k=SOLGUI_GetCurrentKey();
	if(k!=0) k1=k;
	SOLGUI_Widget_Text(0,8,F6X8,"key=%X,switch=%X",k1,Switch_GetValue());
});

//########################################��FATFS���ԡ�########################################
MENU_PAGE page_fatfsTest_SD,page_fatfsTest_Flash;

__M_PAGE(page_fatfsTest,"FATFS",&index,{		//�귽ʽ����ҳ��
	SOLGUI_Cursor(6,0,2);
	SOLGUI_Widget_GotoPage(0,&page_fatfsTest_SD);
	SOLGUI_Widget_GotoPage(1,&page_fatfsTest_Flash);
});

//=========================================��FATFS����_SD����

FATFS FatFs[2];   				//����ļ�ϵͳ��Ϣ
FIL file,file1;	   				//����ļ���Ϣ
FRESULT f_res;			//FatFsͨ�ý����
unsigned int br,bw;				//��д����
u8 SDdatabuff[100];	//SD�����ݻ���
u16 rlen;			//��ȡ�����ݳ���
u8 SDtatus;			//SD����ʼ��״̬
u8 test_buff[]="This is FAFTS on SDCcard";
u8 test_buff1[]="This is FAFTS on flash";

void SD_f_mount_test(void)
{
	FlagLight_Blink();
	f_res = f_mount(SD_CARD,&FatFs[SD_CARD]);	//����SD��
}

void SD_f_write_test(void)
{
	FlagLight_Blink();
	f_res = f_open(&file,"0:/ftest.txt",FA_OPEN_NEW_COVER);	
	f_res = f_write(&file, test_buff, sizeof(test_buff), &bw);	//д���ַ���
	f_res = f_close(&file);	//�ر��ļ�
}

void SD_f_open_test(void)
{
	FlagLight_Blink();
	f_res = f_open(&file,"0:/ftest.txt",FA_OPEN_READONLY);	//���ļ�
	f_res = f_read(&file,SDdatabuff,80,&br);	//��ȡ�ļ�����
	f_res = f_close(&file);	//�ر��ļ�
}

__M_PAGE(page_fatfsTest_SD,"FATFS_SD",&page_fatfsTest,{		//�귽ʽ����ҳ��
	SOLGUI_Cursor(6,5,3);
	SOLGUI_Widget_Button(0,"1.f_mount",SD_f_mount_test);						//����
	SOLGUI_Widget_Button(1,"2.f_write",SD_f_write_test);						//����
	SOLGUI_Widget_Button(2,"3.f_open",SD_f_open_test);						//����
	SOLGUI_Widget_Text(0,32,~F6X8,"S=%d,r=%d,C=%d",SDtatus,f_res,SDCardInfo.CardCapacity);
	SOLGUI_Widget_Text(0,24,F6X8,"%s",SDdatabuff);
	SOLGUI_Widget_Text(0,16,F6X8,"%s",SDdatabuff+21);
	SOLGUI_Widget_Text(0,8,F6X8,"%s",SDdatabuff+42);
	SOLGUI_Widget_Text(0,0,F6X8,"%s",SDdatabuff+63);
});

//=========================================��FATFS����_Flash��

void Flash_f_mkfs_test(void)
{
	f_mkfs(EX_FLASH,0,512);
}

void Flash_f_mount_test(void)
{
	FlagLight_Blink();
	f_res = f_mount(EX_FLASH,&FatFs[EX_FLASH]);	//����Flash
}

void Flash_f_write_test(void)
{
	FlagLight_Blink();
	f_res = f_open(&file1,"1:/ftest.txt",FA_OPEN_NEW_COVER);	
	f_res = f_write(&file1, test_buff1, sizeof(test_buff1), &bw);	//д���ַ���
	f_res = f_close(&file1);	//�ر��ļ�
}

void Flash_f_open_test(void)
{
	FlagLight_Blink();
	f_res = f_open(&file1,"1:/ftest.txt",FA_OPEN_READONLY);	//���ļ�
	f_res = f_read(&file1,SDdatabuff,80,&br);	//��ȡ�ļ�����
	f_res = f_close(&file1);	//�ر��ļ�
}



		
__M_PAGE(page_fatfsTest_Flash,"FATFS_Flash",&page_fatfsTest,{		//�귽ʽ����ҳ��
	SOLGUI_Cursor(6,5,4);
	SOLGUI_Widget_Button(0,"1.f_mkfs",Flash_f_mkfs_test);						//����
	SOLGUI_Widget_Button(1,"2.f_mount",Flash_f_mount_test);						//����
	SOLGUI_Widget_Button(2,"3.f_write",Flash_f_write_test);						//����
	SOLGUI_Widget_Button(3,"4.f_open",Flash_f_open_test);						//����
	SOLGUI_Widget_Text(0,32,~F6X8,"S=%d,r=%d",SDtatus,f_res);
	SOLGUI_Widget_Text(0,24,F6X8,"%s",SDdatabuff);
	SOLGUI_Widget_Text(0,16,F6X8,"%s",SDdatabuff+21);
	SOLGUI_Widget_Text(0,8,F6X8,"%s",SDdatabuff+42);
	SOLGUI_Widget_Text(0,0,F6X8,"%s",SDdatabuff+63);

});

//########################################��������########################################
void Main_task(void *pdata)
{	
	u8 kv=0;

	pdata=pdata;		
	while(1)
	{
		kv=Key_GetValue();				//��ֵ��ȡ
		SOLGUI_InputKey(kv);			//��ֵ����
		SOLGUI_Menu_PageStage();	 	//ǰ̨
		SOLGUI_Refresh();				//������Ļ
		delay_ms(30);
	}
}















//###############################����ʼ����###############################
void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr=0;
	pdata = pdata;

	OSStatInit(); //��ʼ��ͳ������.�������ʱ 1 ��������
	OS_ENTER_CRITICAL(); //�����ٽ���(�޷����жϴ��)
//-------------------[��������������ʼ������]

	OSTaskCreate(Main_task,(void *)0,(OS_STK*)&MAIN_TASK_STK[MAIN_TASK_STK_SIZE-1],MAIN_TASK_PRIO); 
	
	 
//---------------------------------------------
	OSTaskSuspend(START_TASK_PRIO); //������ʼ����.
	OS_EXIT_CRITICAL(); //�˳��ٽ���(���Ա��жϴ��)
}








//###############################����������###############################

int main(void)
{		
	delay_init();
	FlagLight_Init();
	Flash_Init();
	Key_Init();						//����ɨ���ʼ��
	SOLGUI_Init(&index);
	FlagLight_Blink();

	OSInit(); 			//UCOSII ��ʼ��
	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO);//������ʼ����
	OSStart(); 										  
}
