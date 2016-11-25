/**********************************************************************************
	Copyright (C) 2016 SOL.lab <maxwellxyao@foxmail.com>

*File name:		simui2c.c
*Description:	ģ��I2CЭ��
*Author:		MaxwellXyao
*Versionc:		V0.0.20160626
*Date:			2016-6-26 21:26:33
*History:		
[2016-6-26]	�ļ�����;

**********************************************************************************/
#include "simui2c.h"	//ģ��I2CЭ��

//###########################��������###########################


/*****************************************************************
*Function:	SimuI2C_Start
*Description:	����IIC��ʼ�ź�
*Input:		ģ��I2C�ṹ��
*Output:	��
*Other:		��
*****************************************************************/
void SimuI2C_Start(SimuI2C *SimuI2C_Struct)			 //����IIC��ʼ�ź�
{
	SimuI2C_Struct->PinSetSDA(1);	  	  
	SimuI2C_Struct->PinSetSCL(1);
	SimuI2C_Struct->Delayus(4);
 	SimuI2C_Struct->PinSetSDA(0);//START:when CLK is high,DATA change form high to low 
	SimuI2C_Struct->Delayus(4);
	SimuI2C_Struct->PinSetSCL(0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  

/*****************************************************************
*Function:	SimuI2C_Stop
*Description:	����IICֹͣ�ź�
*Input:		ģ��I2C�ṹ��
*Output:	��
*Other:		��
*****************************************************************/
void SimuI2C_Stop(SimuI2C *SimuI2C_Struct)			   //����IICֹͣ�ź�
{
	SimuI2C_Struct->PinSetSCL(0);
	SimuI2C_Struct->PinSetSDA(0);//STOP:when CLK is high DATA change form low to high
 	SimuI2C_Struct->Delayus(4);
	SimuI2C_Struct->PinSetSCL(1); 
	SimuI2C_Struct->PinSetSDA(1);//����I2C���߽����ź�
	SimuI2C_Struct->Delayus(4);							   	
}

/*****************************************************************
*Function:	SimuI2C_WaitAck
*Description:	�ȴ�Ӧ���źŵ���
*Input:		ģ��I2C�ṹ��
*Output:	1������Ӧ��ʧ��
        	0������Ӧ��ɹ�
*Other:		��
*****************************************************************/
unsigned char SimuI2C_WaitAck(SimuI2C *SimuI2C_Struct)
{
	unsigned char ucErrTime=0;  
	SimuI2C_Struct->PinSetSDA(1);SimuI2C_Struct->Delayus(1);	   
	SimuI2C_Struct->PinSetSCL(1);SimuI2C_Struct->Delayus(1);	 
	while(SimuI2C_Struct->PinGetSDA())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			SimuI2C_Stop(SimuI2C_Struct);
			return 1;
		}
	}
	SimuI2C_Struct->PinSetSCL(0);//ʱ�����0 	   
	return 0;  
} 

/*****************************************************************
*Function:	SimuI2C_Ack
*Description:	����ACKӦ��
*Input:		ģ��I2C�ṹ��
*Output:	��
*Other:		��
*****************************************************************/
void SimuI2C_Ack(SimuI2C *SimuI2C_Struct)
{
	SimuI2C_Struct->PinSetSCL(0);
	SimuI2C_Struct->PinSetSDA(0);
	SimuI2C_Struct->Delayus(2);
	SimuI2C_Struct->PinSetSCL(1);
	SimuI2C_Struct->Delayus(2);
	SimuI2C_Struct->PinSetSCL(0);
}

/*****************************************************************
*Function:	SimuI2C_NAck
*Description:	������ACKӦ��
*Input:		ģ��I2C�ṹ��
*Output:	��
*Other:		��
*****************************************************************/	    
void SimuI2C_NAck(SimuI2C *SimuI2C_Struct)
{
	SimuI2C_Struct->PinSetSCL(0);
	SimuI2C_Struct->PinSetSDA(1);
	SimuI2C_Struct->Delayus(2);
	SimuI2C_Struct->PinSetSCL(1);
	SimuI2C_Struct->Delayus(2);
	SimuI2C_Struct->PinSetSCL(0);
}


/*****************************************************************
*Function:	SimuI2C_WriteByte
*Description:	IIC����һ���ֽ�
*Input:			ģ��I2C�ṹ�壬���͵��ֽ�
*Output:		1����Ӧ��
				0����Ӧ��	
*Other:		��
*****************************************************************/					 				     	  
void SimuI2C_WriteByte(SimuI2C *SimuI2C_Struct,unsigned char data)
{                        
    unsigned char t;   	    
    SimuI2C_Struct->PinSetSCL(0);//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        SimuI2C_Struct->PinSetSDA((data&0x80)>>7);
        data<<=1; 	  
		SimuI2C_Struct->Delayus(2);   //��TEA5767��������ʱ���Ǳ����
		SimuI2C_Struct->PinSetSCL(1);
		SimuI2C_Struct->Delayus(2); 
		SimuI2C_Struct->PinSetSCL(0);	
		SimuI2C_Struct->Delayus(2);
    }	 
} 


/*****************************************************************
*Function:	SimuI2C_ReadByte
*Description:	IIC��һ���ֽ�
*Input:			ģ��I2C�ṹ�壬Ӧ���ź�
*Output:		��
*Other:			ack=1ʱ������ACK��ack=0������nACK   
*****************************************************************/	    
unsigned char SimuI2C_ReadByte(SimuI2C *SimuI2C_Struct,unsigned char ack)
{
	unsigned char i,receive=0;
    for(i=0;i<8;i++ )
	{
        SimuI2C_Struct->PinSetSCL(0); 
        SimuI2C_Struct->Delayus(2);
		SimuI2C_Struct->PinSetSCL(1);
        receive<<=1;
        if(SimuI2C_Struct->PinGetSDA())receive++;   
		SimuI2C_Struct->Delayus(1); 
    }					 
    if (!ack)
        SimuI2C_NAck(SimuI2C_Struct);//����nACK
    else
        SimuI2C_Ack(SimuI2C_Struct); //����ACK   
    return receive;
}




