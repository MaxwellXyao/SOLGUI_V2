#ifndef BSP_KEY_H
#define BSP_KEY_H


//###########################【内部】##############################
typedef struct __KEY_T{
	u8 (*Is_Key_Down)(void);		//硬件检测函数
	u8 Trg;							//触发 
	u8 Cont;						//按住
	u16 fliter_cont;
	u8 S_Value;						//短按键值
	u8 L_Value;						//长按键值
}KEY_T;

void KeyRead(KEY_T *key);

//##############################【参数】##############################
//----【长按时间参数】
#define Long_Press_Time 100

//----【按键个数】
#define KEY_NUM 8

//##############################【硬件定义】##############################
//---------------------【pixelC2使用】
//----------【引脚定义】
//********五向按键*********
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
//********功能键*********
#define Key_A_GPIOx GPIOB
#define Key_A_Pin 	6		//A		 B

#define Key_B_GPIOx GPIOC
#define Key_B_Pin 	7		//B		 C
//********拨码开关*********
#define Switch_1_GPIOx GPIOC
#define Switch_1_Pin 6	 	//拨码开关1	 C

//----【键值定义】
#define KEY_NULL 	0x00 	//未按下
#define KEY_R_S 	0x10	//右键短按
#define KEY_R_L 	0x11	//右键长按
#define KEY_D_S 	0x20	//下键短按
#define KEY_D_L 	0x21	//下键长按
#define KEY_L_S 	0x30	//左键短按
#define KEY_L_L 	0x31	//左键长按
#define KEY_OK_S 	0x40	//OK键短按
#define KEY_OK_L 	0x41	//OK键长按
#define KEY_U_S 	0x50	//上键短按
#define KEY_U_L 	0x51	//上键长按
#define KEY_BK_S 	0x60	//Back键短按
#define KEY_BK_L 	0x61	//Back键长按
#define KEY_A_S 	0x70	//A键短按
#define KEY_A_L 	0x71	//A键长按
#define KEY_B_S 	0x80	//B键短按
#define KEY_B_L 	0x81	//B键长按

//##############################【API】##############################
void Key_Init(void);						//按键扫描初始化
u8 Key_GetValue(void);			//方向键及功能键获取键值【非阻塞，必须被周期性的调用(主函数或定时器)】
u8 Switch_GetValue(void);			//拨码开关获取键值（0~1：switch_1）【非阻塞，必须被周期性的调用(主函数或定时器)】

#endif
