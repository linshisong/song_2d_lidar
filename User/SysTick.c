#include "SysTick.h"

void SysTick_Init(void) 
{
	if (SysTick_Config(SystemCoreClock / 100000)) 
	{
		while(1);
	}
	
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

void Delay_us(__IO u32 nTime) 
{
	TimingDelay = nTime;
	
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	
	while(TimingDelay != 0);
}

void TimingDelay_Decrement(void) 
{
	if (TimingDelay != 0x00) 
	{
		TimingDelay--;
	}
}

