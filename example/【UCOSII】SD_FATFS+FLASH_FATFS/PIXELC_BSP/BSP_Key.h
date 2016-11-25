#ifndef BSP_KEY_H
#define BSP_KEY_H


//###########################���ڲ���##############################
typedef struct __KEY_T{
	u8 (*Is_Key_Down)(void);		//Ӳ����⺯��
	u8 Trg;							//���� 
	u8 Cont;						//��ס
	u16 fliter_cont;
	u8 S_Value;						//�̰���ֵ
	u8 L_Value;						//������ֵ
}KEY_T;

void KeyRead(KEY_T *key);

//##############################��������##############################
//----������ʱ�������
#define Long_Press_Time 100

//----������������
#define KEY_NUM 8

//##############################��Ӳ�����塿##############################
//---------------------��pixelC2ʹ�á�
//----------�����Ŷ��塿
//********���򰴼�*********
#define Key_R_GPIOx GPIOC
#define Key_R_Pin 	3 		//Right	 C

#define Key_D_GPIOx GPIOC
#define Key_D_Pin 	0		//Down	 C

#define Key_L_GPIOx GPIOC
#define Key_L_Pin 	1		//Left	 c

#define Key_OK_GPIOx GPIOC
#define Key_OK_Pin 	13		//OK	 C

#define Key_U_GPIOx GPIOC
#define Key_U_Pin 	2		//UP	 B
									 
#define Key_BK_GPIOx GPIOB
#define Key_BK_Pin 	7		//BK	 B
//********���ܼ�*********
#define Key_A_GPIOx GPIOB
#define Key_A_Pin 	6		//A		 B

#define Key_B_GPIOx GPIOC
#define Key_B_Pin 	7		//B		 C
//********���뿪��*********
#define Switch_1_GPIOx GPIOC
#define Switch_1_Pin 6	 	//���뿪��1	 C

//----����ֵ���塿
#define KEY_NULL 	0x00 	//δ����
#define KEY_R_S 	0x10	//�Ҽ��̰�
#define KEY_R_L 	0x11	//�Ҽ�����
#define KEY_D_S 	0x20	//�¼��̰�
#define KEY_D_L 	0x21	//�¼�����
#define KEY_L_S 	0x30	//����̰�
#define KEY_L_L 	0x31	//�������
#define KEY_OK_S 	0x40	//OK���̰�
#define KEY_OK_L 	0x41	//OK������
#define KEY_U_S 	0x50	//�ϼ��̰�
#define KEY_U_L 	0x51	//�ϼ�����
#define KEY_BK_S 	0x60	//Back���̰�
#define KEY_BK_L 	0x61	//Back������
#define KEY_A_S 	0x70	//A���̰�
#define KEY_A_L 	0x71	//A������
#define KEY_B_S 	0x80	//B���̰�
#define KEY_B_L 	0x81	//B������

//##############################��API��##############################
void Key_Init(void);						//����ɨ���ʼ��
u8 Key_GetValue(void);			//����������ܼ���ȡ��ֵ�������������뱻�����Եĵ���(��������ʱ��)��
u8 Switch_GetValue(void);			//���뿪�ػ�ȡ��ֵ��0~1��switch_1���������������뱻�����Եĵ���(��������ʱ��)��

#endif
