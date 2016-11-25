#include "project_include.h"

void FlagLight_Init(void)
{
	RCC->APB2ENR|=1<<2;    	  												
#if FLAGLIGHT_Pin/8									
		FLAGLIGHT_GPIOx->CRH&=~((u32)0xf<<((FLAGLIGHT_Pin%8)*4));		
		FLAGLIGHT_GPIOx->CRH|=(u32)0x3<<((FLAGLIGHT_Pin%8)*4);
#else
		FLAGLIGHT_GPIOx->CRL&=~((u32)0xf<<((FLAGLIGHT_Pin%8)*4));
		FLAGLIGHT_GPIOx->CRL|=(u32)0x3<<((FLAGLIGHT_Pin%8)*4);
#endif
	PAout(8)=1;	
}

void FlagLight_On(void)
{
	PAout(8)=0;
}

void FlagLight_Off(void)
{
	PAout(8)=1;
}

void FlagLight_Blink(void)
{
	FlagLight_On();
	delay_ms(BLINK_TIME_MS);
	FlagLight_Off();
}
