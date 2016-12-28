/**
	* @file            I2C.c
	* @author					 林士松
	* @version         V01
	* @data            2016.12.28
	* @brief					 i2c 软件模拟，stm32与epc901通信方式
	* @note
	*
	* @attention       COYPRIGHT INMOTION
	*/


#include "i2c.h"

//模拟IIC初始化
void MYI2C_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
	RCC_AHBPeriphClockCmd(LSS_RCC_I2C, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin =  I2C_Pin_SCL;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LSS_GPIO_I2C, &GPIO_InitStructure);		
	
	
	GPIO_InitStructure.GPIO_Pin =  I2C_Pin_SDA;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LSS_GPIO_I2C, &GPIO_InitStructure);	
}

//普通延时，需要修改
static void I2C_delay(void)
{
   u8 i=0; 
   while(i) 
   { 
     i--; 
   } 
}


//开始信号
static int I2C_Start(void)
{
	SDA_H;
	SCL_H;
	I2C_delay();
	if(!SDA_read)return 0;	//SDA线为低电平则总线忙,退出
	SDA_L;
	I2C_delay();
	if(SDA_read) return 0;	//SDA线为高电平则总线出错,退出
	SDA_L;
	I2C_delay();
	return 1;	
}

//停止信号
static void I2C_Stop(void)
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SDA_H;
	I2C_delay();
} 
 
//从机发送数据给主机时，主机应答
static void I2C_Ack(void)
{	
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}   

//从机发送数据给主机时，主机不应答
static void I2C_NoAck(void)
{	
	SCL_L;
	I2C_delay();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
} 

//主机等待从机的应答信号，返回为:=1有ACK,=0无ACK
static int I2C_WaitAck(void) 	
{
	SCL_L;
	I2C_delay();
	SDA_H;			
	I2C_delay();
	SCL_H;
	I2C_delay();
	if(SDA_read)
	{
      SCL_L;
			I2C_delay();
      return 0;
	}
	SCL_L;
	I2C_delay();
	return 1;
}

//主机到从机，写数据，数据从高位到低位//
static void I2C_SendByte(u8 SendByte) 
{
    u8 i=8;
    while(i--)
    {
        SCL_L;
        I2C_delay();
      if(SendByte&0x80)
        SDA_H;  
      else 
        SDA_L;   
        SendByte<<=1;
        I2C_delay();
				SCL_H;
				I2C_delay();
    }
    SCL_L;
}  

//主句从从机读数据
static u8 I2C_ReadByte(void)  //数据从高位到低位//
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L;
      I2C_delay();
			SCL_H;
      I2C_delay();	
      if(SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L;
    return ReceiveByte;
} 

//单字节写入*******************************************
int I2C_Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data)		
{
  	if(!I2C_Start())
			return 0;
    I2C_SendByte (SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck())
		{
			I2C_Stop(); 
			return 0;
		}
    I2C_SendByte(REG_Address );   //设置低起始地址      
    I2C_WaitAck();	
    I2C_SendByte(REG_data);
    I2C_WaitAck();   
    I2C_Stop(); 
    return 1;
}

//单字节读取*****************************************
int I2C_Single_Read(u8 SlaveAddress,u8 REG_Address)
{   
		unsigned char REG_data;     	
		if(!I2C_Start())return 0;
    I2C_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck())
		{
			I2C_Stop();
			return 0;
		}
    I2C_SendByte((u8) REG_Address);   //设置低起始地址      
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(SlaveAddress+1);
    I2C_WaitAck();

		REG_data= I2C_ReadByte();
    I2C_NoAck();
    I2C_Stop();
    //return TRUE;
		return REG_data;

}	

/******************************************************************************
多字节读取
******************************************************************************/
int I2C_Mult_Read(u8 SlaveAddress,u8 REG_Address,u8 * ptChar,u8 size)
{
    uint8_t i;
    
    if(size < 1)
			return 0;
    if(!I2C_Start())
			return 0;
    I2C_SendByte(SlaveAddress);
    if(!I2C_WaitAck())
		{
			I2C_Stop();
			return 0;
		}
    I2C_SendByte(REG_Address);    
    I2C_WaitAck();
    
    I2C_Start();
    I2C_SendByte(SlaveAddress+1);
    I2C_WaitAck();
    
    for(i=1;i<size; i++)
    {
        *ptChar++ = I2C_ReadByte();
        I2C_Ack();
    }
    *ptChar++ = I2C_ReadByte();
    I2C_NoAck();
    I2C_Stop();
    return 1;    
}	
