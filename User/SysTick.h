#ifndef __SysTick_h
#define __SysTick_h

//#include ""


#include "main.h"

extern uint32_t TimingDelay;
void SysTick_Init(void);
void Delay_us(__IO u32 nTime); 
void TimingDelay_Decrement(void); 
#endif

