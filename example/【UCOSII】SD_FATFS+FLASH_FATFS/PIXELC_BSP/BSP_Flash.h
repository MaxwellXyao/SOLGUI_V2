#ifndef BSP_FLASH_H
#define	BSP_FLASH_H

#define EX_FLASH			    1	//�߼��豸1

//############################��Ӳ�����塿##############################	
				    
// SPI�����ٶ����� 
#define SPI_SPEED_2   		0
#define SPI_SPEED_4   		1
#define SPI_SPEED_8   		2
#define SPI_SPEED_16  		3
#define SPI_SPEED_32 		4
#define SPI_SPEED_64 		5
#define SPI_SPEED_128 		6
#define SPI_SPEED_256 		7

//##############################��API��##############################


//W25Xϵ��/Qϵ��оƬ�б�	   
//W25Q80 ID  0XEF13
//W25Q16 ID  0XEF14
//W25Q32 ID  0XEF15
//W25Q32 ID  0XEF16	
#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16

extern u16 SPI_FLASH_TYPE;		//��������ʹ�õ�flashоƬ�ͺ�		   
#define	SPI_FLASH_CS PAout(15)  //ѡ��FLASH	


//ָ���
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

				 
////////////////////////////////////////////////////////////////////////////

void Flash_Init(void);
void Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //��ȡflash
void Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);//д��flash

u16  Flash_ReadID(void);  	    //��ȡFLASH ID
u8	 Flash_ReadSR(void);        //��ȡ״̬�Ĵ��� 
void Flash_Write_SR(u8 sr);  	//д״̬�Ĵ���
void Flash_Write_Enable(void);  //дʹ�� 
void Flash_Write_Disable(void);	//д����

void Flash_Erase_Chip(void);    	  //��Ƭ����
void Flash_Erase_Sector(u32 Dst_Addr);//��������
void Flash_PowerDown(void);           //�������ģʽ
void Flash_WAKEUP(void);			  //����



#endif
