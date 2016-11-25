#ifndef BSP_SD_H
#define BSP_SD_H


#define SD_CARD					0	//逻辑设备0

/**********************************************************
                     外部函数头文件                        
**********************************************************/

#include "sys.h"		//用到中断分组
#include "string.h"		//读写disk用到内存操作相关函数



/* 通讯调节速度分频因子 */
/* HCLK = 72MHz, SDIOCLK = 72MHz */
/* 计算公式：SDIO_CK = SDIO_CLK / (CLKDIV + 2） */

#define SDIO_INIT_CLK_DIV                  ((u8)0xb2)			//400KHz----> 0xb2(178)
#define SDIO_TRANSFER_CLK_DIV              ((u8)0x02)
//24MHz ----> 0x01
//18MHz ----> 0x02
//12MHz ----> 0x04

/**********************************************************
                      SDIO工作模式定义
                 要修改工作模式请修改这里
**********************************************************/

#define SD_DMA_MODE                                ((u32)0x00000000)
//#define SD_POLLING_MODE                            ((u32)0x00000002)

/**********************************************************
                       相关宏定义
**********************************************************/

//SDIO Static flags, TimeOut, FIFO Address
#define NULL							0
#define SDIO_STATIC_FLAGS               ((u32)0x000005FF)
#define SDIO_CMD0TIMEOUT                ((u32)0x00010000)
#define SDIO_DATATIMEOUT                ((u32)0x0001FFFF)

//Mask for errors Card Status R1 (OCR Register)
#define SD_OCR_ADDR_OUT_OF_RANGE        ((u32)0x80000000)
#define SD_OCR_ADDR_MISALIGNED          ((u32)0x40000000)
#define SD_OCR_BLOCK_LEN_ERR            ((u32)0x20000000)
#define SD_OCR_ERASE_SEQ_ERR            ((u32)0x10000000)
#define SD_OCR_BAD_ERASE_PARAM          ((u32)0x08000000)
#define SD_OCR_WRITE_PROT_VIOLATION     ((u32)0x04000000)
#define SD_OCR_LOCK_UNLOCK_FAILED       ((u32)0x01000000)
#define SD_OCR_COM_CRC_FAILED           ((u32)0x00800000)
#define SD_OCR_ILLEGAL_CMD              ((u32)0x00400000)
#define SD_OCR_CARD_ECC_FAILED          ((u32)0x00200000)
#define SD_OCR_CC_ERROR                 ((u32)0x00100000)
#define SD_OCR_GENERAL_UNKNOWN_ERROR    ((u32)0x00080000)
#define SD_OCR_STREAM_READ_UNDERRUN     ((u32)0x00040000)
#define SD_OCR_STREAM_WRITE_OVERRUN     ((u32)0x00020000)
#define SD_OCR_CID_CSD_OVERWRIETE       ((u32)0x00010000)
#define SD_OCR_WP_ERASE_SKIP            ((u32)0x00008000)
#define SD_OCR_CARD_ECC_DISABLED        ((u32)0x00004000)
#define SD_OCR_ERASE_RESET              ((u32)0x00002000)
#define SD_OCR_AKE_SEQ_ERROR            ((u32)0x00000008)
#define SD_OCR_ERRORBITS                ((u32)0xFDFFE008)

//Masks for R6 Response
#define SD_R6_GENERAL_UNKNOWN_ERROR     ((u32)0x00002000)
#define SD_R6_ILLEGAL_CMD               ((u32)0x00004000)
#define SD_R6_COM_CRC_FAILED            ((u32)0x00008000)

#define SD_VOLTAGE_WINDOW_SD            ((u32)0x80100000)
#define SD_VOLTAGE_WINDOW_MMC           ((u32)0x80FF8000)
#define SD_HIGH_CAPACITY                ((u32)0x40000000)
#define SD_STD_CAPACITY                 ((u32)0x00000000)
#define SD_CHECK_PATTERN                ((u32)0x000001AA)

#define SD_MAX_VOLT_TRIAL               ((u32)0x0000FFFF)
#define SD_ALLZERO                      ((u32)0x00000000)

#define SD_WIDE_BUS_SUPPORT             ((u32)0x00040000)
#define SD_SINGLE_BUS_SUPPORT           ((u32)0x00010000)
#define SD_CARD_LOCKED                  ((u32)0x02000000)

#define SD_DATATIMEOUT                  ((u32)0xFFFFFFFF)
#define SD_0TO7BITS                     ((u32)0x000000FF)
#define SD_8TO15BITS                    ((u32)0x0000FF00)
#define SD_16TO23BITS                   ((u32)0x00FF0000)
#define SD_24TO31BITS                   ((u32)0xFF000000)
#define SD_MAX_DATA_LENGTH              ((u32)0x01FFFFFF)

#define SD_HALFFIFO                     ((u32)0x00000008)
#define SD_HALFFIFOBYTES                ((u32)0x00000020)

//Command Class Supported
#define SD_CCCC_LOCK_UNLOCK             ((u32)0x00000080)
#define SD_CCCC_WRITE_PROT              ((u32)0x00000040)
#define SD_CCCC_ERASE                   ((u32)0x00000020)

//Following commands are SD Card Specific commands.
//SDIO_APP_CMD should be sent before sending these commands.
#define SDIO_SEND_IF_COND               ((u32)0x00000008)

/**********************************************************
            SD卡初始化和读写卡是的状态值定义
**********************************************************/

typedef enum
{
	/* 初始化过程当中错误信息定义 */
	  
	SD_CMD_CRC_FAIL                    = (1), /*!< Command response received (but CRC check failed) */
	SD_DATA_CRC_FAIL                   = (2), /*!< Data bock sent/received (CRC check Failed) */
	SD_CMD_RSP_TIMEOUT                 = (3), /*!< Command response timeout */
	SD_DATA_TIMEOUT                    = (4), /*!< Data time out */
	SD_TX_UNDERRUN                     = (5), /*!< Transmit FIFO under-run */
	SD_RX_OVERRUN                      = (6), /*!< Receive FIFO over-run */
	SD_START_BIT_ERR                   = (7), /*!< Start bit not detected on all data signals in widE bus mode */
	SD_CMD_OUT_OF_RANGE                = (8), /*!< CMD's argument was out of range.*/
	SD_ADDR_MISALIGNED                 = (9), /*!< Misaligned address */
	SD_BLOCK_LEN_ERR                   = (10), /*!< Transferred block length is not allowed for the card or the number of transferred bytes does not match the block length */
	SD_ERASE_SEQ_ERR                   = (11), /*!< An error in the sequence of erase command occurs.*/
	SD_BAD_ERASE_PARAM                 = (12), /*!< An Invalid selection for erase groups */
	SD_WRITE_PROT_VIOLATION            = (13), /*!< Attempt to program a write protect block */
	SD_LOCK_UNLOCK_FAILED              = (14), /*!< Sequence or password error has been detected in unlock command or if there was an attempt to access a locked card */
	SD_COM_CRC_FAILED                  = (15), /*!< CRC check of the previous command failed */
	SD_ILLEGAL_CMD                     = (16), /*!< Command is not legal for the card state */
	SD_CARD_ECC_FAILED                 = (17), /*!< Card internal ECC was applied but failed to correct the data */
	SD_CC_ERROR                        = (18), /*!< Internal card controller error */
	SD_GENERAL_UNKNOWN_ERROR           = (19), /*!< General or Unknown error */
	SD_STREAM_READ_UNDERRUN            = (20), /*!< The card could not sustain data transfer in stream read operation. */
	SD_STREAM_WRITE_OVERRUN            = (21), /*!< The card could not sustain data programming in stream mode */
	SD_CID_CSD_OVERWRITE               = (22), /*!< CID/CSD overwrite error */
	SD_WP_ERASE_SKIP                   = (23), /*!< only partial address space was erased */
	SD_CARD_ECC_DISABLED               = (24), /*!< Command has been executed without using internal ECC */
	SD_ERASE_RESET                     = (25), /*!< Erase sequence was cleared before executing because an out of erase sequence command was received */
	SD_AKE_SEQ_ERROR                   = (26), /*!< Error in sequence of authentication. */
	SD_INVALID_VOLTRANGE               = (27),
	SD_ADDR_OUT_OF_RANGE               = (28),
	SD_SWITCH_ERROR                    = (29),
	SD_SDIO_DISABLED                   = (30),
	SD_SDIO_FUNCTION_BUSY              = (31),
	SD_SDIO_FUNCTION_FAILED            = (32),
	SD_SDIO_UNKNOWN_FUNCTION           = (33),

	/* 初始化待机状态错误信息定义 */
	 
	SD_INTERNAL_ERROR, 
	SD_NOT_CONFIGURED,
	SD_REQUEST_PENDING, 
	SD_REQUEST_NOT_APPLICABLE, 
	SD_INVALID_PARAMETER,  
	SD_UNSUPPORTED_FEATURE,  
	SD_UNSUPPORTED_HW,  
	SD_ERROR,  
	SD_OK = 0 
}SD_Error;

/**********************************************************
                    传输状态信息定义
**********************************************************/

//DMA2传输方向
#define DMA2_ReadDATA						0	//DMA读取数据
#define DMA2_WriteDATA						1	//DMA写入数据

//SDIO传输方向
#define SDIO_To_Card						0	//SDIO主机写数据到卡
#define Card_To_SDIO						1	//SDIO主机从卡读取数据

//SD命令响应长短
#define SD_Response_No                    	0	//无响应
#define SD_Response_Short                 	1	//短响应
#define SD_Response_Long                  	3	//长响应

typedef enum
{
	SD_TRANSFER_OK  = 0,	/* 传输成功 */
	SD_TRANSFER_BUSY = 1,	/* 正忙着呢 */
	SD_TRANSFER_ERROR		/* 传输出错 */
}SDTransferState;

typedef enum
{
  SD_CARD_READY                  = ((u32)0x00000001),
  SD_CARD_IDENTIFICATION         = ((u32)0x00000002),
  SD_CARD_STANDBY                = ((u32)0x00000003),
  SD_CARD_TRANSFER               = ((u32)0x00000004),
  SD_CARD_SENDING                = ((u32)0x00000005),
  SD_CARD_RECEIVING              = ((u32)0x00000006),
  SD_CARD_PROGRAMMING            = ((u32)0x00000007),
  SD_CARD_DISCONNECTED           = ((u32)0x00000008),
  SD_CARD_ERROR                  = ((u32)0x000000FF)
}SDCardState;

/**********************************************************
                    卡信息寄存器结构
**********************************************************/

//CSD寄存器结构定义
typedef struct
{
	__IO u8  CSDStruct;            /*!< CSD structure */
	__IO u8  SysSpecVersion;       /*!< System specification version */
	__IO u8  Reserved1;            /*!< Reserved */
	__IO u8  TAAC;                 /*!< Data read access-time 1 */
	__IO u8  NSAC;                 /*!< Data read access-time 2 in CLK cycles */
	__IO u8  MaxBusClkFrec;        /*!< Max. bus clock frequency */
	__IO u16 CardComdClasses;      /*!< Card command classes */
	__IO u8  RdBlockLen;           /*!< Max. read data block length */
	__IO u8  PartBlockRead;        /*!< Partial blocks for read allowed */
	__IO u8  WrBlockMisalign;      /*!< Write block misalignment */
	__IO u8  RdBlockMisalign;      /*!< Read block misalignment */
	__IO u8  DSRImpl;              /*!< DSR implemented */
	__IO u8  Reserved2;            /*!< Reserved */
	__IO u32 DeviceSize;           /*!< Device Size */
	__IO u8  MaxRdCurrentVDDMin;   /*!< Max. read current @ VDD min */
	__IO u8  MaxRdCurrentVDDMax;   /*!< Max. read current @ VDD max */
	__IO u8  MaxWrCurrentVDDMin;   /*!< Max. write current @ VDD min */
	__IO u8  MaxWrCurrentVDDMax;   /*!< Max. write current @ VDD max */
	__IO u8  DeviceSizeMul;        /*!< Device size multiplier */
	__IO u8  EraseGrSize;          /*!< Erase group size */
	__IO u8  EraseGrMul;           /*!< Erase group size multiplier */
	__IO u8  WrProtectGrSize;      /*!< Write protect group size */
	__IO u8  WrProtectGrEnable;    /*!< Write protect group enable */
	__IO u8  ManDeflECC;           /*!< Manufacturer default ECC */
	__IO u8  WrSpeedFact;          /*!< Write speed factor */
	__IO u8  MaxWrBlockLen;        /*!< Max. write data block length */
	__IO u8  WriteBlockPaPartial;  /*!< Partial blocks for write allowed */
	__IO u8  Reserved3;            /*!< Reserded */
	__IO u8  ContentProtectAppli;  /*!< Content protection application */
	__IO u8  FileFormatGrouop;     /*!< File format group */
	__IO u8  CopyFlag;             /*!< Copy flag (OTP) */
	__IO u8  PermWrProtect;        /*!< Permanent write protection */
	__IO u8  TempWrProtect;        /*!< Temporary write protection */
	__IO u8  FileFormat;           /*!< File Format */
	__IO u8  ECC;                  /*!< ECC code */
	__IO u8  CSD_CRC;              /*!< CSD CRC */
	__IO u8  Reserved4;            /*!< always 1*/
}SD_CSD;

//CID寄存器结构定义
typedef struct
{
	__IO u8  ManufacturerID;       /*!< ManufacturerID */
	__IO u16 OEM_AppliID;          /*!< OEM/Application ID */
	__IO u32 ProdName1;            /*!< Product Name part1 */
	__IO u8  ProdName2;            /*!< Product Name part2*/
	__IO u8  ProdRev;              /*!< Product Revision */
	__IO u32 ProdSN;               /*!< Product Serial Number */
	__IO u8  Reserved1;            /*!< Reserved1 */
	__IO u16 ManufactDate;         /*!< Manufacturing Date */
	__IO u8  CID_CRC;              /*!< CID CRC */
	__IO u8  Reserved2;            /*!< always 1 */
}SD_CID;

//卡状态寄存器结构定义
typedef struct
{
	__IO u8 DAT_BUS_WIDTH;
	__IO u8 SECURED_MODE;
	__IO u16 SD_CARD_TYPE;
	__IO u32 SIZE_OF_PROTECTED_AREA;
	__IO u8 SPEED_CLASS;
	__IO u8 PERFORMANCE_MOVE;
	__IO u8 AU_SIZE;
	__IO u16 ERASE_SIZE;
	__IO u8 ERASE_TIMEOUT;
	__IO u8 ERASE_OFFSET;
}SD_CardStatus;

//卡信息汇总
typedef struct
{
	SD_CSD SD_csd;
	SD_CID SD_cid;
	long long CardCapacity;	/*!< Card Capacity */
	u32 CardBlockSize;	/*!< Card Block Size */
	u16 RCA;
	u8 CardType;
}SD_CardInfo;

extern SD_CardInfo SDCardInfo;

/**********************************************************
                    SD卡命令字节定义
                   对应十进制的 0 ~ 64
**********************************************************/

#define SD_CMD_GO_IDLE_STATE                       ((u8)0)
#define SD_CMD_SEND_OP_COND                        ((u8)1)
#define SD_CMD_ALL_SEND_CID                        ((u8)2)
#define SD_CMD_SET_REL_ADDR                        ((u8)3) /*!< SDIO_SEND_REL_ADDR for SD Card */
#define SD_CMD_SET_DSR                             ((u8)4)
#define SD_CMD_SDIO_SEN_OP_COND                    ((u8)5)
#define SD_CMD_HS_SWITCH                           ((u8)6)
#define SD_CMD_SEL_DESEL_CARD                      ((u8)7)
#define SD_CMD_HS_SEND_EXT_CSD                     ((u8)8)
#define SD_CMD_SEND_CSD                            ((u8)9)
#define SD_CMD_SEND_CID                            ((u8)10)
#define SD_CMD_READ_DAT_UNTIL_STOP                 ((u8)11) /*!< SD Card doesn't support it */
#define SD_CMD_STOP_TRANSMISSION                   ((u8)12)
#define SD_CMD_SEND_STATUS                         ((u8)13)
#define SD_CMD_HS_BUSTEST_READ                     ((u8)14)
#define SD_CMD_GO_INACTIVE_STATE                   ((u8)15)
#define SD_CMD_SET_BLOCKLEN                        ((u8)16)
#define SD_CMD_READ_SINGLE_BLOCK                   ((u8)17)
#define SD_CMD_READ_MULT_BLOCK                     ((u8)18)
#define SD_CMD_HS_BUSTEST_WRITE                    ((u8)19)
#define SD_CMD_WRITE_DAT_UNTIL_STOP                ((u8)20) /*!< SD Card doesn't support it */
#define SD_CMD_SET_BLOCK_COUNT                     ((u8)23) /*!< SD Card doesn't support it */
#define SD_CMD_WRITE_SINGLE_BLOCK                  ((u8)24)
#define SD_CMD_WRITE_MULT_BLOCK                    ((u8)25)
#define SD_CMD_PROG_CID                            ((u8)26) /*!< reserved for manufacturers */
#define SD_CMD_PROG_CSD                            ((u8)27)
#define SD_CMD_SET_WRITE_PROT                      ((u8)28)
#define SD_CMD_CLR_WRITE_PROT                      ((u8)29)
#define SD_CMD_SEND_WRITE_PROT                     ((u8)30)
#define SD_CMD_SD_ERASE_GRP_START                  ((u8)32) /*!< To set the address of the first write
                                                                  block to be erased. (For SD card only) */
#define SD_CMD_SD_ERASE_GRP_END                    ((u8)33) /*!< To set the address of the last write block of the
                                                                  continuous range to be erased. (For SD card only) */
#define SD_CMD_ERASE_GRP_START                     ((u8)35) /*!< To set the address of the first write block to be erased.
                                                                  (For MMC card only spec 3.31) */

#define SD_CMD_ERASE_GRP_END                       ((u8)36) /*!< To set the address of the last write block of the
                                                                  continuous range to be erased. (For MMC card only spec 3.31) */

#define SD_CMD_ERASE                               ((u8)38)
#define SD_CMD_FAST_IO                             ((u8)39) /*!< SD Card doesn't support it */
#define SD_CMD_GO_IRQ_STATE                        ((u8)40) /*!< SD Card doesn't support it */
#define SD_CMD_LOCK_UNLOCK                         ((u8)42)
#define SD_CMD_APP_CMD                             ((u8)55)
#define SD_CMD_GEN_CMD                             ((u8)56)
#define SD_CMD_NO_CMD                              ((u8)64)

//APP命令，先发送CMD55再发送以下命令

#define SD_CMD_APP_SD_SET_BUSWIDTH                 ((u8)6)  /*!< For SD Card only */
#define SD_CMD_SD_APP_STAUS                        ((u8)13) /*!< For SD Card only */
#define SD_CMD_SD_APP_SEND_NUM_WRITE_BLOCKS        ((u8)22) /*!< For SD Card only */
#define SD_CMD_SD_APP_OP_COND                      ((u8)41) /*!< For SD Card only */
#define SD_CMD_SD_APP_SET_CLR_CARD_DETECT          ((u8)42) /*!< For SD Card only */
#define SD_CMD_SD_APP_SEND_SCR                     ((u8)51) /*!< For SD Card only */
#define SD_CMD_SDIO_RW_DIRECT                      ((u8)52) /*!< For SD I/O Card only */
#define SD_CMD_SDIO_RW_EXTENDED                    ((u8)53) /*!< For SD I/O Card only */

//以下命令仅支持SD Card

#define SD_CMD_SD_APP_GET_MKB                      ((u8)43) /*!< For SD Card only */
#define SD_CMD_SD_APP_GET_MID                      ((u8)44) /*!< For SD Card only */
#define SD_CMD_SD_APP_SET_CER_RN1                  ((u8)45) /*!< For SD Card only */
#define SD_CMD_SD_APP_GET_CER_RN2                  ((u8)46) /*!< For SD Card only */
#define SD_CMD_SD_APP_SET_CER_RES2                 ((u8)47) /*!< For SD Card only */
#define SD_CMD_SD_APP_GET_CER_RES1                 ((u8)48) /*!< For SD Card only */
#define SD_CMD_SD_APP_SECURE_READ_MULTIPLE_BLOCK   ((u8)18) /*!< For SD Card only */
#define SD_CMD_SD_APP_SECURE_WRITE_MULTIPLE_BLOCK  ((u8)25) /*!< For SD Card only */
#define SD_CMD_SD_APP_SECURE_ERASE                 ((u8)38) /*!< For SD Card only */
#define SD_CMD_SD_APP_CHANGE_SECURE_AREA           ((u8)49) /*!< For SD Card only */
#define SD_CMD_SD_APP_SECURE_WRITE_MKB             ((u8)48) /*!< For SD Card only */

/**
  * @brief  SD detection on its memory slot
  */
#define SD_PRESENT                                 ((u8)0x01)
#define SD_NOT_PRESENT                             ((u8)0x00)

/**********************************************************
                     支持卡的类型定义
**********************************************************/

#define SDIO_STD_CAPACITY_SD_CARD_V1_1             ((u32)0x00000000)
#define SDIO_STD_CAPACITY_SD_CARD_V2_0             ((u32)0x00000001)
#define SDIO_HIGH_CAPACITY_SD_CARD                 ((u32)0x00000002)
#define SDIO_MULTIMEDIA_CARD                       ((u32)0x00000003)
#define SDIO_SECURE_DIGITAL_IO_CARD                ((u32)0x00000004)
#define SDIO_HIGH_SPEED_MULTIMEDIA_CARD            ((u32)0x00000005)
#define SDIO_SECURE_DIGITAL_IO_COMBO_CARD          ((u32)0x00000006)
#define SDIO_HIGH_CAPACITY_MMC_CARD                ((u32)0x00000007)

/**********************************************************
                     外部功能函数
**********************************************************/

void SD_DeInit(void);
SD_Error SD_Init(void);
SDTransferState SD_GetStatus(void);
SDCardState SD_GetState(void);
SD_Error SD_PowerON(void);
SD_Error SD_PowerOFF(void);
SD_Error SD_InitializeCards(void);
SD_Error SD_GetCardInfo(SD_CardInfo *cardinfo);
SD_Error SD_GetCardStatus(SD_CardStatus *cardstatus);
SD_Error SD_EnableWideBusOperation(u32 WideMode);
SD_Error SD_SelectDeselect(u32 addr);
SD_Error SD_ReadBlock(u8 *readbuff, u32 ReadAddr, u16 BlockSize);
SD_Error SD_ReadMultiBlocks(u8 *readbuff, u32 ReadAddr, u16 BlockSize, u32 NumberOfBlocks);
SD_Error SD_WriteBlock(u8 *writebuff, u32 WriteAddr, u16 BlockSize);
SD_Error SD_WriteMultiBlocks(u8 *writebuff, u32 WriteAddr, u16 BlockSize, u32 NumberOfBlocks);
SDTransferState SD_GetTransferState(void);
SD_Error SD_StopTransfer(void);
SD_Error SD_Erase(u32 startaddr, u32 endaddr);
SD_Error SD_SendStatus(u32 *pcardstatus);
SD_Error SD_SendSDStatus(u32 *psdstatus);
SD_Error SD_ProcessIRQSrc(void);
SD_Error SD_WaitReadOperation(void);
SD_Error SD_WaitWriteOperation(void);

SD_Error SD_ReadDisk(u8 *readbuff, u32 sector, u16 cnt);
SD_Error SD_WriteDisk(u8 *writebuff, u32 sector, u16 cnt);

#endif
