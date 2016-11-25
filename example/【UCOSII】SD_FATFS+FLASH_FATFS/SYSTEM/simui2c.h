#ifndef __SIMUI2C_H
#define __SIMUI2C_H

/**********************************************************************************
	Copyright (C) 2016 SOL.lab <maxwellxyao@foxmail.com>

*File name:		simui2c.h
*Description:	ģ��I2CЭ��
*Author:		MaxwellXyao
*Version:		V0.0.20160626
*Date:			2016-6-26 21:26:33
*History:		
[2016-6-26]	�ļ�����;

**********************************************************************************/

//###########################�����塿###########################
typedef struct _SimuI2C{				//I2CӲ�������
	void (*PinSetSCL)(unsigned char);		//SCL�����������
	void (*PinSetSDA)(unsigned char);		//SDA�����������
	unsigned char (*PinGetSDA)();			//SDA���Ŷ�ȡ����
	void (*Delayus)(unsigned int);		//us��ʱ����
}SimuI2C;								

//###########################��API��###########################
void SimuI2C_Start(SimuI2C *SimuI2C_Struct);			 	//����IIC��ʼ�ź�
void SimuI2C_Stop(SimuI2C *SimuI2C_Struct);			   		//����IICֹͣ�ź�
unsigned char SimuI2C_WaitAck(SimuI2C *SimuI2C_Struct);		//�ȴ�Ӧ���źŵ���
void SimuI2C_Ack(SimuI2C *SimuI2C_Struct);					//����ACKӦ��
void SimuI2C_NAck(SimuI2C *SimuI2C_Struct);					//������ACKӦ��
void SimuI2C_WriteByte(SimuI2C *SimuI2C_Struct,unsigned char data);			//IIC����һ���ֽ�
unsigned char SimuI2C_ReadByte(SimuI2C *SimuI2C_Struct,unsigned char ack);	//IIC��һ���ֽ�

#endif
