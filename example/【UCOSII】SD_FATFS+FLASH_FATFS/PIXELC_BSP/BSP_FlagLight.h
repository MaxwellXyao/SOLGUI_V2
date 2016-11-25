#ifndef BSP_FLAGLIGHT_H
#define	BSP_FLAGLIGHT_H

//###############################【硬件】####################################
#define FLAGLIGHT_GPIOx GPIOA
#define FLAGLIGHT_Pin 8	 //PA8

//###############################【参数】####################################

#define BLINK_TIME_MS 10 //闪烁持续时间ms

//###############################【API】####################################
void FlagLight_Init(void);
void FlagLight_On(void);
void FlagLight_Off(void);
void FlagLight_Blink(void);

#endif

