#ifndef BSP_FLAGLIGHT_H
#define	BSP_FLAGLIGHT_H

//###############################��Ӳ����####################################
#define FLAGLIGHT_GPIOx GPIOA
#define FLAGLIGHT_Pin 8	 //PA8

//###############################��������####################################

#define BLINK_TIME_MS 10 //��˸����ʱ��ms

//###############################��API��####################################
void FlagLight_Init(void);
void FlagLight_On(void);
void FlagLight_Off(void);
void FlagLight_Blink(void);

#endif

