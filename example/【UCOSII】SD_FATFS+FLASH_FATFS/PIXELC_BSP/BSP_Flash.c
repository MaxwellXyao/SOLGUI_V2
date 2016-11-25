#include "project_include.h"

//##############################【硬件定义】##############################

//========================[SPI]===========================
//SPI3速度设置函数
//SpeedSet:0~7
//SPI速度=fAPB1/2^(SpeedSet+1)
//APB1时钟一般为36Mhz
static void SPI3_SetSpeed(u8 SpeedSet)
{
	SpeedSet&=0X07;			//限制范围
	SPI3->CR1&=0XFFC7; 
	SPI3->CR1|=SpeedSet<<3;	//设置SPI3速度  
	SPI3->CR1|=1<<6; 		//SPI设备使能	  
} 
//SPI3 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
static u8 SPI3_ReadWriteByte(u8 TxData)
{		
	u16 retry=0;				 
	while((SPI3->SR&1<<1)==0)		//等待发送区空	
	{
		retry++;
		if(retry>=0XFFFE)return 0; 	//超时退出
	}			  
	SPI3->DR=TxData;	 	  		//发送一个byte 
	retry=0;
	while((SPI3->SR&1<<0)==0) 		//等待接收完一个byte  
	{
		retry++;
		if(retry>=0XFFFE)return 0;	//超时退出
	}	  						    
	return SPI3->DR;          		//返回收到的数据				    
}

static void SPI3_Init(void)
{	 
	RCC->APB2ENR|=1<<3;  	//PORTB时钟使能 	 
	RCC->APB1ENR|=1<<15;   	//SPI3时钟使能 
	//这里只针对SPI口初始化
	GPIOB->CRL&=0XFF000FFF; 
	GPIOB->CRL|=0X00BBB000;	//PB3/4/5复用 	    
	GPIOB->ODR|=0X7<<3;   	//PB3/4/5上拉
	SPI3->CR1|=0<<10;		//全双工模式	
	SPI3->CR1|=1<<9; 		//软件nss管理
	SPI3->CR1|=1<<8;  

	SPI3->CR1|=1<<2; 		//SPI主机
	SPI3->CR1|=0<<11;		//8bit数据格式	
	SPI3->CR1|=1<<1; 		//空闲模式下SCK为1 CPOL=1
	SPI3->CR1|=1<<0; 		//数据采样从第二个时间边沿开始,CPHA=1  
	//对SPI2属于APB1的外设.时钟频率最大为36M.
	SPI3->CR1|=3<<3; 		//Fsck=Fpclk1/256
	SPI3->CR1|=0<<7; 		//MSBfirst   
	SPI3->CR1|=1<<6; 		//SPI设备使能
	SPI3_ReadWriteByte(0xff);//启动传输		 
}   

//========================[FLASH 驱动部分]==========================
u16 SPI_FLASH_TYPE=W25Q64;//默认就是25Q64

//4Kbytes为一个Sector
//16个扇区为1个Block
//W25Q64
//容量为8M字节,共有128个Block,2048个Sector 
													 
//初始化SPI FLASH的IO口
void Flash_Init(void)
{
	RCC->APB2ENR|=1<<2;     //使能PORTA时钟 	    
	GPIOA->CRH&=0X0FFFFFFF; 
	GPIOA->CRH|=0X30000000;	//PA15 推挽 	    
	GPIOA->ODR|=1<<15;    	//PA15上拉

	SPI3_Init();		   	//初始化SPI
	SPI3_SetSpeed(SPI_SPEED_2);//设置为18M时钟,高速模式
	SPI_FLASH_TYPE=Flash_ReadID();//读取FLASH ID.
}  

//读取SPI_FLASH的状态寄存器
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:默认0,状态寄存器保护位,配合WP使用
//TB,BP2,BP1,BP0:FLASH区域写保护设置
//WEL:写使能锁定
//BUSY:忙标记位(1,忙;0,空闲)
//默认:0x00
u8 Flash_ReadSR(void)   
{  
	u8 byte=0;   
	SPI_FLASH_CS=0;                            //使能器件   
	SPI3_ReadWriteByte(W25X_ReadStatusReg);    //发送读取状态寄存器命令    
	byte=SPI3_ReadWriteByte(0Xff);             //读取一个字节  
	SPI_FLASH_CS=1;                            //取消片选     
	return byte;   
} 
//写SPI_FLASH状态寄存器
//只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
void Flash_Write_SR(u8 sr)   
{   
	SPI_FLASH_CS=0;                            //使能器件   
	SPI3_ReadWriteByte(W25X_WriteStatusReg);   //发送写取状态寄存器命令    
	SPI3_ReadWriteByte(sr);               //写入一个字节  
	SPI_FLASH_CS=1;                            //取消片选     	      
}   
//SPI_FLASH写使能	
//将WEL置位   
void Flash_Write_Enable(void)   
{
	SPI_FLASH_CS=0;                            //使能器件   
    SPI3_ReadWriteByte(W25X_WriteEnable);      //发送写使能  
	SPI_FLASH_CS=1;                            //取消片选     	      
} 
//SPI_FLASH写禁止	
//将WEL清零  
void SPI_FLASH_Write_Disable(void)   
{  
	SPI_FLASH_CS=0;                            //使能器件   
    SPI3_ReadWriteByte(W25X_WriteDisable);     //发送写禁止指令    
	SPI_FLASH_CS=1;                            //取消片选     	      
} 		
//读取芯片ID
//返回值如下:				   
//0XEF13,表示芯片型号为W25Q80  
//0XEF14,表示芯片型号为W25Q16    
//0XEF15,表示芯片型号为W25Q32  
//0XEF16,表示芯片型号为W25Q64   	  
u16 Flash_ReadID(void)
{
	u16 Temp = 0;	  
	SPI_FLASH_CS=0;				    
	SPI3_ReadWriteByte(0x90);//发送读取ID命令	    
	SPI3_ReadWriteByte(0x00); 	    
	SPI3_ReadWriteByte(0x00); 	    
	SPI3_ReadWriteByte(0x00); 	 			   
	Temp|=SPI3_ReadWriteByte(0xFF)<<8;  
	Temp|=SPI3_ReadWriteByte(0xFF);	 
	SPI_FLASH_CS=1;				    
	return Temp;
}   		    

//等待空闲
static void SPI_Flash_Wait_Busy(void)   
{   
	while((Flash_ReadSR()&0x01)==0x01);   // 等待BUSY位清空
}   
//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!	 
static void SPI_Flash_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
 	u16 i;  
    Flash_Write_Enable();                  //SET WEL 
	SPI_FLASH_CS=0;                            //使能器件   
    SPI3_ReadWriteByte(W25X_PageProgram);      //发送写页命令   
    SPI3_ReadWriteByte((u8)((WriteAddr)>>16)); //发送24bit地址    
    SPI3_ReadWriteByte((u8)((WriteAddr)>>8));   
    SPI3_ReadWriteByte((u8)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++)SPI3_ReadWriteByte(pBuffer[i]);//循环写数  
	SPI_FLASH_CS=1;                            //取消片选 
	SPI_Flash_Wait_Busy();					   //等待写入结束
} 






//擦除一个扇区
//Dst_Addr:扇区地址 根据实际容量设置
//擦除一个山区的最少时间:150ms
void Flash_Erase_Sector(u32 Dst_Addr)   
{  	  
 	Dst_Addr*=4096;
    Flash_Write_Enable();                  //SET WEL 	 
    SPI_Flash_Wait_Busy();   
  	SPI_FLASH_CS=0;                            //使能器件   
    SPI3_ReadWriteByte(W25X_SectorErase);      //发送扇区擦除指令 
    SPI3_ReadWriteByte((u8)((Dst_Addr)>>16));  //发送24bit地址    
    SPI3_ReadWriteByte((u8)((Dst_Addr)>>8));   
    SPI3_ReadWriteByte((u8)Dst_Addr);  
	SPI_FLASH_CS=1;                            //取消片选     	      
    SPI_Flash_Wait_Busy();   				   //等待擦除完成
}  



//无检验写SPI FLASH 
//必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能 
//在指定地址开始写入指定长度的数据,但是要确保地址不越界!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)
//CHECK OK
static void SPI_Flash_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 			 		 
	u16 pageremain;	   
	pageremain=256-WriteAddr%256; //单页剩余的字节数		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//不大于256个字节
	while(1)
	{	   
		SPI_Flash_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//写入结束了
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //减去已经写入了的字节数
			if(NumByteToWrite>256)pageremain=256; //一次可以写入256个字节
			else pageremain=NumByteToWrite; 	  //不够256个字节了
		}
	};	    
} 
//写SPI FLASH  
//在指定地址开始写入指定长度的数据
//该函数带擦除操作!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)						
//NumByteToWrite:要写入的字节数(最大65535)   
u8 SPI_FLASH_BUFFER[4096];		 
void Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 
	u32 secpos;
	u16 secoff;
	u16 secremain;	   
 	u16 i;    
	u8 * SPI_FLASH_BUF;	  
   	SPI_FLASH_BUF=SPI_FLASH_BUFFER;	     
 	secpos=WriteAddr/4096;//扇区地址  
	secoff=WriteAddr%4096;//在扇区内的偏移
	secremain=4096-secoff;//扇区剩余空间大小   
 	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//不大于4096个字节
	while(1) 
	{	
		Flash_Read(SPI_FLASH_BUF,secpos*4096,4096);//读出整个扇区的内容
		for(i=0;i<secremain;i++)//校验数据
		{
			if(SPI_FLASH_BUF[secoff+i]!=0XFF)break;//需要擦除  	  
		}
		if(i<secremain)//需要擦除
		{
			Flash_Erase_Sector(secpos);//擦除这个扇区
			for(i=0;i<secremain;i++)	   //复制
			{
				SPI_FLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			SPI_Flash_Write_NoCheck(SPI_FLASH_BUF,secpos*4096,4096);//写入整个扇区  

		}else SPI_Flash_Write_NoCheck(pBuffer,WriteAddr,secremain);//写已经擦除了的,直接写入扇区剩余区间. 				   
		if(NumByteToWrite==secremain)break;//写入结束了
		else//写入未结束
		{
			secpos++;//扇区地址增1
			secoff=0;//偏移位置为0 	 

		   	pBuffer+=secremain;  //指针偏移
			WriteAddr+=secremain;//写地址偏移	   
		   	NumByteToWrite-=secremain;				//字节数递减
			if(NumByteToWrite>4096)secremain=4096;	//下一个扇区还是写不完
			else secremain=NumByteToWrite;			//下一个扇区可以写完了
		}	 
	};	 
}

//读取SPI FLASH  
//在指定地址开始读取指定长度的数据
//pBuffer:数据存储区
//ReadAddr:开始读取的地址(24bit)
//NumByteToRead:要读取的字节数(最大65535)
void Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{ 
 	u16 i;   										    
	SPI_FLASH_CS=0;                            //使能器件   
    SPI3_ReadWriteByte(W25X_ReadData);         //发送读取命令   
    SPI3_ReadWriteByte((u8)((ReadAddr)>>16));  //发送24bit地址    
    SPI3_ReadWriteByte((u8)((ReadAddr)>>8));   
    SPI3_ReadWriteByte((u8)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
	{ 
        pBuffer[i]=SPI3_ReadWriteByte(0XFF);   //循环读数  
    }
	SPI_FLASH_CS=1;  				    	      
}

//擦除整个芯片		  
//等待时间超长...
void Flash_Erase_Chip(void)   
{                                   
    Flash_Write_Enable();                  //SET WEL 
    SPI_Flash_Wait_Busy();   
  	SPI_FLASH_CS=0;                            //使能器件   
    SPI3_ReadWriteByte(W25X_ChipErase);        //发送片擦除命令  
	SPI_FLASH_CS=1;                            //取消片选     	      
	SPI_Flash_Wait_Busy();   				   //等待芯片擦除结束
}   
 
//进入掉电模式
void Flash_PowerDown(void)   
{ 
  	SPI_FLASH_CS=0;                            //使能器件   
    SPI3_ReadWriteByte(W25X_PowerDown);        //发送掉电命令  
	SPI_FLASH_CS=1;                            //取消片选     	      
    delay_us(3);                               //等待TPD  
}   
//唤醒
void Flash_WAKEUP(void)   
{  
  	SPI_FLASH_CS=0;                            //使能器件   
    SPI3_ReadWriteByte(W25X_ReleasePowerDown);   //  send W25X_PowerDown command 0xAB    
	SPI_FLASH_CS=1;                            //取消片选     	      
    delay_us(3);                               //等待TRES1
}   




