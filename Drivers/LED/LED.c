/**
	* @file            led.c
	* @author					 林士松
	* @version         V01
	* @data            2016.12.28
	* @brief					 led 驱动
	* @note
	*
	* @attention       COYPRIGHT INMOTION
	*/


#include "LED.h"


void LED_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//配置LED灯
	RCC_AHBPeriphClockCmd(LSS_RCC_LED, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LSS_Pin_LED;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LSS_GPIO_LED, &GPIO_InitStructure);
	
	//点灯
	GPIO_ResetBits(LSS_GPIO_LED, LSS_Pin_LED);
	
}

void LED_ON(void)
{
	GPIO_SetBits(LSS_GPIO_LED, LSS_Pin_LED);
}	

void LED_OFF(void)
{
	GPIO_SetBits(LSS_GPIO_LED, LSS_Pin_LED);
}

