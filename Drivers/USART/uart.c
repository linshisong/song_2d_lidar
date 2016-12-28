/**
	* @file            uart.c
	* @author					 ��ʿ��
	* @version         V01
	* @data            2016.12.28
	* @brief					 ��������
	* @note
	*
	* @attention       COYPRIGHT INMOTION
	*/

#include "uart.h"



void uart1_init(u32 bound) 
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	USART_InitTypeDef  USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//ʹ��USART1ʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	    //ʹ��GPIOAʱ��
	
	//��������
	//UART1_TX  PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//�����������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9

	//UART1_RX  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	//�����������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10
	
	USART_InitStructure.USART_BaudRate=bound;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;

	USART_Init(USART1,&USART_InitStructure);
	USART_ClearFlag(USART1,USART_FLAG_TC);
	USART_Cmd(USART1,ENABLE);	
}
