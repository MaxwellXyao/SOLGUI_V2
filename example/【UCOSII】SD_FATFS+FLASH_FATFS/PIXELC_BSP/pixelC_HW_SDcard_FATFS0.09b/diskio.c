/**********************************************************
* @ File name -> diskio.c
* @ Version   -> V1.0
* @ Date      -> 02-11-2014
* @ Brief     -> fatfs�ļ�ϵͳ��IO�ײ���������
**********************************************************/

#include "diskio.h"

/**********************************************************
                     �ⲿ����ͷ�ļ�                        
**********************************************************/

#include "BSP_SD.h"		   	//����SD��
#include "BSP_Flash.h"  	//����Flash(8MB)
#include "sys.h"

/**********************************************************
                       ��Ҵ��̺궨��
**********************************************************/

#define SD_CARD					0	//�߼��豸0
#define EX_FLASH			    1	//�߼��豸1

/**********************************************************
                       �������������С
**********************************************************/
#define FLASH_SECTOR_SIZE 512
//���� W25Q64
//ǰ 6M �ֽڸ� fatfs ��,6M �ֽں���û���
u16 FLASH_SECTOR_COUNT=2048*6; 	//6M �ֽ�,Ĭ��Ϊ W25Q64
#define FLASH_BLOCK_SIZE 8 		//ÿ�� BLOCK �� 8 ������


/**********************************************************
* �������� ---> ��Ҵ��̳�ʼ��
* ��ڲ��� ---> pdrv����Ҵ��̺�
* ������ֵ ---> ��ʼ���ɹ�����־
* ����˵�� ---> none
**********************************************************/
DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber (0..) */
)
{
	DRESULT res = RES_OK;
	u8 errorstatus;

	switch(pdrv)
	{
		case SD_CARD:	//��ҵ���SD��

				errorstatus = SD_Init();

				/* װ����Ӧ�ź�ΪFatFsֵ */
				if(errorstatus == SD_OK)	res = RES_OK;
				else	res = RES_NOTRDY;

				break;
				
		case EX_FLASH:	//��ҵ���FLASH

				Flash_Init();

				if(SPI_FLASH_TYPE == W25Q64)	FLASH_SECTOR_COUNT = 2048*6;
				else	FLASH_SECTOR_COUNT = 2048*2;

				res = RES_OK;

				break;

		default:
				res = RES_ERROR;	//ȱʡֵ���󷵻�
				break;
	}

	return res;
}
/**********************************************************
* �������� ---> ��ȡ����״̬
* ��ڲ��� ---> pdrv����Ҵ��̺�
* ������ֵ ---> �ɹ�����־
* ����˵�� ---> none
**********************************************************/
DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber (0..) */
)
{
	return RES_OK;
}
/**********************************************************
* �������� ---> ��ȡ����
* ��ڲ��� ---> pdrv����Ҵ��̺�
*               *buff����ȡ���ݻ���
*               sector��������ʼ��ַ
*               count����ȡ��������
* ������ֵ ---> �ɹ�����־
* ����˵�� ---> none
**********************************************************/
DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..128) */
)
{
	DRESULT res = RES_OK;
	u8 errorstatus;

	if(!count)	return RES_PARERR;	//��ȡ����0�������������򷵻ش���

	switch(pdrv)
	{
		case SD_CARD:	//��ҵ���SD��

				errorstatus = SD_ReadDisk((u8*)buff, sector, count);	//��ȡ����
				//ת��Ӧ��ֵΪFatFsֵ
				if(errorstatus == SD_OK)	res = RES_OK;
				else	res = RES_ERROR; 

				break;
				
		case EX_FLASH:	//��ҵ���FLASH

				for(;count != 0;count--)
				{
					Flash_Read(buff,sector*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);
					sector++;
					buff += FLASH_SECTOR_SIZE;
				}
				res = RES_OK;

				break;

		default:
				res = RES_ERROR;
				break;
	}

	return res;
}
/**********************************************************
* �������� ---> дȡ����
* ��ڲ��� ---> pdrv����Ҵ��̺�
*               *buff����ȡ���ݻ���
*               sector��������ʼ��ַ
*               count��д��������
* ������ֵ ---> �ɹ�����־
* ����˵�� ---> none
**********************************************************/

/* read only */

#if _FS_READONLY==0	//֧��д����

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..128) */
)
{
	DRESULT res = RES_OK;
	u8 errorstatus;
	u8 retry=0x1f;		//д��ʧ�ܵ�ʱ��,���Դ���

	if(!count)	return RES_PARERR;	//д�����0�������������򷵻ش���

	switch(pdrv)
	{
		case SD_CARD:	//��ҵ���SD��
				while(retry)
				{
					errorstatus = SD_WriteDisk((u8*)buff, sector, count);	//д�����
					//ת��Ӧ��ֵΪFatFsֵ	
					if(errorstatus == SD_OK)	{	res = RES_OK;break;	}
					retry--;
				}
				if(retry == 0)	res = RES_ERROR;	//��ʱ
				
				break;
				
		case EX_FLASH:	//��ҵ���FLASH

				for(;count != 0;count--)
				{
					Flash_Write((u8*)buff,sector*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);
					sector++;
					buff += FLASH_SECTOR_SIZE;
				}
				res = RES_OK;

				break;

		default:
				res = RES_ERROR;
				break;
	}

	return res;
}
/**********************************************************
* �������� ---> FatFs��ȡʱ����Ϣ��ֻ��ģʽ�²���Ҫ�˺���
* ��ڲ��� ---> none
* ������ֵ ---> ��ȡ����32bitʱ����Ϣ
* ����˵�� ---> 31 ~ 25��year(0 ~ 127 org.1980)
*               24 ~ 21��month(1 ~ 12)
*               20 ~ 16: date(1 ~ 31)
*               15 ~ 11: hour(00 ~ 23)
*               10 ~ 5:  minute(00 ~ 59)
*               4  ~ 0:  second(00 ~ 59)
**********************************************************/
DWORD get_fattime(void)
{
	DWORD time_buff=0;

//	PCF8563_ReadWrite_Time(1);	//��ȡʱ����Ϣ
//
//	//��ʱ��ʮ������ת����BCD��
//	TimeValue.year = HX_to_DX(TimeValue.year);		//��
//	TimeValue.month = HEX_to_BCD(TimeValue.month);	//��
//	TimeValue.date = HEX_to_BCD(TimeValue.date);	//��
//	TimeValue.hour = HEX_to_BCD(TimeValue.hour);	//ʱ
//	TimeValue.minute = HEX_to_BCD(TimeValue.minute);//��
//	TimeValue.second = HEX_to_BCD(TimeValue.second);//��
//
//	//����FatFs��ʱ���ʽ���
//	time_buff |= ((TimeValue.year - 1980)<<25);	//��
//	time_buff |= (TimeValue.month<<21);			//��
//	time_buff |= (TimeValue.date<<16);			//��
//	
//	time_buff |= (TimeValue.hour<<11);			//ʱ 
//	time_buff |= (TimeValue.minute<<5);			//��
//	time_buff |= (TimeValue.second/2);			//��

	return time_buff;
}
				 
#endif	/* end readonly */

/**********************************************************
* �������� ---> ��ȡ���Ʋ���
* ��ڲ��� ---> pdrv����Ҵ��̺�
*               cmd����������
*               *buff���������ݻ���
* ������ֵ ---> �ɹ�����־
* ����˵�� ---> none
**********************************************************/
#if _USE_IOCTL

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res = RES_OK;

	if(pdrv == SD_CARD)	//ѡ����ҵ�SD��
	{
		switch(cmd)
		{
			case CTRL_SYNC:	//��ȡ����״̬

					res = RES_OK;

					break;

			case GET_SECTOR_SIZE:	//��ȡ������С

					res = RES_OK;
					
					break;

			case GET_BLOCK_SIZE:	//��ȡ���С

					*(WORD*)buff = SDCardInfo.CardBlockSize;	//512
					res = RES_OK;

					break;

			case GET_SECTOR_COUNT:	//��������

					*(WORD*)buff = SDCardInfo.CardCapacity / SDCardInfo.CardBlockSize;
					res = RES_OK;

					break;

			default:
					res = RES_PARERR;

					break;
		}	//end switch
	}	//end SD card

	else if(pdrv == EX_FLASH)	//ѡ����ҵ�flash
	{
		switch(cmd)	//��������ѡ��
		{
			case CTRL_SYNC:

					res = RES_OK;

					break;

			case GET_SECTOR_SIZE:	//��ȡ������С

					*(WORD*)buff = FLASH_SECTOR_SIZE;
					res = RES_OK;

					break;

			case GET_BLOCK_SIZE:	//��ȡ���С

					*(WORD*)buff = FLASH_BLOCK_SIZE;
					res = RES_OK;
	
					break;

			case GET_SECTOR_COUNT:	//��ȡ������С

					*(WORD*)buff = FLASH_SECTOR_COUNT;
					res = RES_OK;
	
					break;

			default:
					res = RES_PARERR;
					break;
		}	//end switch
	}	//end EX FLASH

	else	res = RES_ERROR;	//�����Ĳ�֧��

	return res;
}

#endif	/* end ioctr */

///**********************************************************
//* �������� ---> ��̬�����ڴ�
//* ��ڲ��� ---> size�������ڴ��С
//* ������ֵ ---> none
//* ����˵�� ---> none
//**********************************************************/
//void *ff_memalloc (UINT size)			
//{
//	return (void*)mymalloc(SRAMIN,size);
//}
///**********************************************************
//* �������� ---> �ͷ��ڴ�
//* ��ڲ��� ---> mf��Ҫ�ͷŵĵ�ַָ��
//* ������ֵ ---> none
//* ����˵�� ---> none
//**********************************************************/
//void ff_memfree (void* mf)		 
//{
//	myfree(SRAMIN,mf);
//}

