/**********************************************************
* @ File name -> diskio.c
* @ Version   -> V1.0
* @ Date      -> 02-11-2014
* @ Brief     -> fatfs文件系统的IO底层驱动函数
**********************************************************/

#include "diskio.h"

/**********************************************************
                     外部函数头文件                        
**********************************************************/

#include "BSP_SD.h"		   	//板载SD卡
#include "BSP_Flash.h"  	//板载Flash(8MB)
#include "sys.h"

/**********************************************************
                       外挂磁盘宏定义
**********************************************************/

#define SD_CARD					0	//逻辑设备0
#define EX_FLASH			    1	//逻辑设备1

/**********************************************************
                       定义扇区缓存大小
**********************************************************/
#define FLASH_SECTOR_SIZE 512
//对于 W25Q64
//前 6M 字节给 fatfs 用,6M 字节后给用户用
u16 FLASH_SECTOR_COUNT=2048*6; 	//6M 字节,默认为 W25Q64
#define FLASH_BLOCK_SIZE 8 		//每个 BLOCK 有 8 个扇区


/**********************************************************
* 函数功能 ---> 外挂磁盘初始化
* 入口参数 ---> pdrv：外挂磁盘号
* 返回数值 ---> 初始化成功与否标志
* 功能说明 ---> none
**********************************************************/
DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber (0..) */
)
{
	DRESULT res = RES_OK;
	u8 errorstatus;

	switch(pdrv)
	{
		case SD_CARD:	//外挂的是SD卡

				errorstatus = SD_Init();

				/* 装换响应信号为FatFs值 */
				if(errorstatus == SD_OK)	res = RES_OK;
				else	res = RES_NOTRDY;

				break;
				
		case EX_FLASH:	//外挂的是FLASH

				Flash_Init();

				if(SPI_FLASH_TYPE == W25Q64)	FLASH_SECTOR_COUNT = 2048*6;
				else	FLASH_SECTOR_COUNT = 2048*2;

				res = RES_OK;

				break;

		default:
				res = RES_ERROR;	//缺省值错误返回
				break;
	}

	return res;
}
/**********************************************************
* 函数功能 ---> 获取磁盘状态
* 入口参数 ---> pdrv：外挂磁盘号
* 返回数值 ---> 成功与否标志
* 功能说明 ---> none
**********************************************************/
DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber (0..) */
)
{
	return RES_OK;
}
/**********************************************************
* 函数功能 ---> 读取磁盘
* 入口参数 ---> pdrv：外挂磁盘号
*               *buff：读取数据缓存
*               sector：扇区起始地址
*               count：读取扇区数量
* 返回数值 ---> 成功与否标志
* 功能说明 ---> none
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

	if(!count)	return RES_PARERR;	//读取的是0个扇区的内容则返回错误

	switch(pdrv)
	{
		case SD_CARD:	//外挂的是SD卡

				errorstatus = SD_ReadDisk((u8*)buff, sector, count);	//读取磁盘
				//转换应答值为FatFs值
				if(errorstatus == SD_OK)	res = RES_OK;
				else	res = RES_ERROR; 

				break;
				
		case EX_FLASH:	//外挂的是FLASH

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
* 函数功能 ---> 写取磁盘
* 入口参数 ---> pdrv：外挂磁盘号
*               *buff：读取数据缓存
*               sector：扇区起始地址
*               count：写扇区数量
* 返回数值 ---> 成功与否标志
* 功能说明 ---> none
**********************************************************/

/* read only */

#if _FS_READONLY==0	//支持写操作

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..128) */
)
{
	DRESULT res = RES_OK;
	u8 errorstatus;
	u8 retry=0x1f;		//写入失败的时候,重试次数

	if(!count)	return RES_PARERR;	//写入的是0个扇区的内容则返回错误

	switch(pdrv)
	{
		case SD_CARD:	//外挂的是SD卡
				while(retry)
				{
					errorstatus = SD_WriteDisk((u8*)buff, sector, count);	//写入磁盘
					//转换应答值为FatFs值	
					if(errorstatus == SD_OK)	{	res = RES_OK;break;	}
					retry--;
				}
				if(retry == 0)	res = RES_ERROR;	//超时
				
				break;
				
		case EX_FLASH:	//外挂的是FLASH

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
* 函数功能 ---> FatFs获取时间信息，只读模式下不需要此函数
* 入口参数 ---> none
* 返回数值 ---> 读取到的32bit时间信息
* 功能说明 ---> 31 ~ 25：year(0 ~ 127 org.1980)
*               24 ~ 21：month(1 ~ 12)
*               20 ~ 16: date(1 ~ 31)
*               15 ~ 11: hour(00 ~ 23)
*               10 ~ 5:  minute(00 ~ 59)
*               4  ~ 0:  second(00 ~ 59)
**********************************************************/
DWORD get_fattime(void)
{
	DWORD time_buff=0;

//	PCF8563_ReadWrite_Time(1);	//获取时间信息
//
//	//将时间十六进制转换成BCD码
//	TimeValue.year = HX_to_DX(TimeValue.year);		//年
//	TimeValue.month = HEX_to_BCD(TimeValue.month);	//月
//	TimeValue.date = HEX_to_BCD(TimeValue.date);	//日
//	TimeValue.hour = HEX_to_BCD(TimeValue.hour);	//时
//	TimeValue.minute = HEX_to_BCD(TimeValue.minute);//分
//	TimeValue.second = HEX_to_BCD(TimeValue.second);//秒
//
//	//按照FatFs的时间格式组合
//	time_buff |= ((TimeValue.year - 1980)<<25);	//年
//	time_buff |= (TimeValue.month<<21);			//月
//	time_buff |= (TimeValue.date<<16);			//日
//	
//	time_buff |= (TimeValue.hour<<11);			//时 
//	time_buff |= (TimeValue.minute<<5);			//分
//	time_buff |= (TimeValue.second/2);			//秒

	return time_buff;
}
				 
#endif	/* end readonly */

/**********************************************************
* 函数功能 ---> 获取控制参数
* 入口参数 ---> pdrv：外挂磁盘号
*               cmd：控制命令
*               *buff：控制数据缓存
* 返回数值 ---> 成功与否标志
* 功能说明 ---> none
**********************************************************/
#if _USE_IOCTL

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res = RES_OK;

	if(pdrv == SD_CARD)	//选择外挂的SD卡
	{
		switch(cmd)
		{
			case CTRL_SYNC:	//读取卡的状态

					res = RES_OK;

					break;

			case GET_SECTOR_SIZE:	//获取扇区大小

					res = RES_OK;
					
					break;

			case GET_BLOCK_SIZE:	//获取块大小

					*(WORD*)buff = SDCardInfo.CardBlockSize;	//512
					res = RES_OK;

					break;

			case GET_SECTOR_COUNT:	//扇区总数

					*(WORD*)buff = SDCardInfo.CardCapacity / SDCardInfo.CardBlockSize;
					res = RES_OK;

					break;

			default:
					res = RES_PARERR;

					break;
		}	//end switch
	}	//end SD card

	else if(pdrv == EX_FLASH)	//选择外挂的flash
	{
		switch(cmd)	//控制命令选择
		{
			case CTRL_SYNC:

					res = RES_OK;

					break;

			case GET_SECTOR_SIZE:	//获取扇区大小

					*(WORD*)buff = FLASH_SECTOR_SIZE;
					res = RES_OK;

					break;

			case GET_BLOCK_SIZE:	//获取块大小

					*(WORD*)buff = FLASH_BLOCK_SIZE;
					res = RES_OK;
	
					break;

			case GET_SECTOR_COUNT:	//获取扇区大小

					*(WORD*)buff = FLASH_SECTOR_COUNT;
					res = RES_OK;
	
					break;

			default:
					res = RES_PARERR;
					break;
		}	//end switch
	}	//end EX FLASH

	else	res = RES_ERROR;	//其他的不支持

	return res;
}

#endif	/* end ioctr */

///**********************************************************
//* 函数功能 ---> 动态分配内存
//* 入口参数 ---> size：分配内存大小
//* 返回数值 ---> none
//* 功能说明 ---> none
//**********************************************************/
//void *ff_memalloc (UINT size)			
//{
//	return (void*)mymalloc(SRAMIN,size);
//}
///**********************************************************
//* 函数功能 ---> 释放内存
//* 入口参数 ---> mf：要释放的地址指针
//* 返回数值 ---> none
//* 功能说明 ---> none
//**********************************************************/
//void ff_memfree (void* mf)		 
//{
//	myfree(SRAMIN,mf);
//}

