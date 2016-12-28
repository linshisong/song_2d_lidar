/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    04-April-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include "SysTick.h"

/** @addtogroup STM32F30x_StdPeriph_Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t TimingDelay;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void NVIC_Configuration(void)
{
	//NVIC_InitTypeDef USART2_init2;
	//NVIC_InitTypeDef NVIC_InitStructure;
	//NVIC_InitTypeDef 
	/*NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	USART2_init2.NVIC_IRQChannel = USART2_IRQn;
	USART2_init2.NVIC_IRQChannelPreemptionPriority = 0;
	USART2_init2.NVIC_IRQChannelSubPriority = 1;
	USART2_init2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&USART2_init2);
	*/
	/*NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);*/
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//EXTI_InitTypeDef EXTI_InitStructure;
	//≈‰÷√LEDµ∆
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//≈‰÷√∞¥º¸
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/*GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7);  
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &GPIO_InitStructure);*/
	
	//GPIO_PinAFConfig(GPIOC, GPIO_PinSource13, GPIO_AF_5);
	/*SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,GPIO_PinSource13);
	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);*/
}

/*void USART_Configuration(void) 
{
	USART_InitTypeDef  USART_InitStructure;

	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;

	USART_Init(USART2,&USART_InitStructure);
	USART_ClearFlag(USART1,USART_FLAG_TC);
	USART_Cmd(USART1,ENABLE);	
}*/

u8 Key_Scan(GPIO_TypeDef * GPIOx, u16 GPIO_Pin) 
{
	u32 i;
	if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin)  == Bit_SET) 
	{
		for(i = 0; i < 10000; i++);
		if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin)  == Bit_SET) 
		{
			while(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin)  == Bit_SET);
			return Bit_SET;
		}
		return Bit_RESET;
	}
	return Bit_RESET;
}
	

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	//uint32_t i = 0;
		
		//SystemInit();//72m
	
	
  	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
		//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); 
		//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
		//RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
		NVIC_Configuration();
  	GPIO_Configuration(); 
		//USART_Configuration();
		//SysTick_Init();
		GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_SET);
  	while (1)
  	{
			
			//GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_SET);
			if (Key_Scan(GPIOC, GPIO_Pin_13) == Bit_SET) {
				GPIO_WriteBit(GPIOB, GPIO_Pin_13, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_13)));
			}
			
			//Delay_us(500);
			//for(i = 0; i < 1000000; i++);
			//GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET);
			//Delay_us(500);
			//for(i = 0; i < 1000000; i++);
			//puts("I Love MCU!");
			
  	}
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
