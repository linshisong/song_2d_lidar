#ifndef __I2C_H
#define __I2C_H
 

#include "main.h"

#define SCL_H         LSS_GPIO_I2C->BSRR = I2C_Pin_SCL
#define SCL_L         LSS_GPIO_I2C->BRR  = I2C_Pin_SCL
#define SDA_H         LSS_GPIO_I2C->BSRR = I2C_Pin_SDA
#define SDA_L         LSS_GPIO_I2C->BRR  = I2C_Pin_SDA
#define SCL_read      LSS_GPIO_I2C->IDR  & I2C_Pin_SCL
#define SDA_read      LSS_GPIO_I2C->IDR  & I2C_Pin_SDA

//仅给本文件调用
static void I2C_delay( void ) ;
static int I2C_Start(void);
static void I2C_Stop(void);
static void I2C_Ack(void);
static void I2C_NoAck(void);
static int I2C_WaitAck(void);
static u8 I2C_ReadByte(void); 
static void I2C_SendByte(u8 SendByte) ;

//可给其他工程文件调用
void MYI2C_Init(void);
int I2C_Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data)	;	
int I2C_Single_Read(u8 SlaveAddress,u8 REG_Address) ;
int I2C_Mult_Read(u8 SlaveAddress,u8 REG_Address,u8 * ptChar,u8 size);

#endif
