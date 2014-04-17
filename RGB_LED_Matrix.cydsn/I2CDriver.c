/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <device.h>
#include "I2CDriver.h"

//I2C Constants
#define I2C_ACK             0x00
#define I2C_NACK            0xff
#define I2C_WRITE           0x00
#define I2C_READ            0xff
#define RTC_ADDR 			0x51
#define RTC_CTRLSTAT_ADDR	0x00
#define RTC_SEC_ADDR		0x02
#define RTC_MIN_ADDR		0x03
#define RTC_HOUR_ADDR 		0x04


uint8 decToBcd( uint8 val )
{
    return (uint8) ((val / 10 * 16) + (val % 10));
}
 

uint8 bcdToDec( uint8 val )
{
    return (uint8) ((val / 16 * 10) + (val % 16));
}

void localTimeInit(PCF8583 *RTC)
{
	RTC->hour = 12;
	RTC->minute = 40;
	RTC->sec = 0;
	RTC->day = 1;
	RTC->weekday = 1;
	RTC->month = 2;
	RTC->year = 1;
	RTC->pm = 1;
	RTC->format = 1;
}

void randomTimeInit(PCF8583 *RTC)
{
	RTC->hour = 0;
	RTC->minute = 0;
	RTC->sec = 0;
	RTC->day = 0;
	RTC->weekday = 0;
	RTC->month = 0;
	RTC->year = 0;
	RTC->pm = 0;
	RTC->format = 0;
}

uint8 i2cWrite(uint8 Reg_Addr,uint8 Reg_Data)
{
    uint8 I2C_Status;
    I2C_Status = RTC_I2CMasterSendStart(RTC_ADDR, I2C_WRITE);
    I2C_Status = RTC_I2CMasterWriteByte(Reg_Addr);
    I2C_Status = RTC_I2CMasterWriteByte(Reg_Data);
    I2C_Status = RTC_I2CMasterSendStop();
	return I2C_Status;
}
uint8 setTime(PCF8583 *RTC)
{
	uint8 I2C_Status;
	uint8 hour = (decToBcd(RTC->hour)&0x3F); 
	uint8 am = ((RTC->pm<<6)&0x40);
	uint8 format = ((RTC->format)<<7)&0x80;
	uint8 time = format|am|hour;
	I2C_Status = i2cWrite(RTC_HOUR_ADDR,time);
	I2C_Status = i2cWrite(RTC_MIN_ADDR,decToBcd(RTC->minute));
	return I2C_Status;
}




uint8 getTime(PCF8583 *RTC)
{
	uint8 I2C_Status;
	I2C_Status = RTC_I2CMasterSendStart(RTC_ADDR, I2C_WRITE);
	I2C_Status = RTC_I2CMasterWriteByte(RTC_SEC_ADDR);
    I2C_Status = RTC_I2CMasterSendRestart(RTC_ADDR, I2C_READ);
    RTC->sec = RTC_I2CMasterReadByte(RTC_I2C_ACK_DATA);
    RTC->minute = RTC_I2CMasterReadByte(RTC_I2C_ACK_DATA);
    RTC->hour = RTC_I2CMasterReadByte(RTC_I2C_NAK_DATA)& 0x3F;
	I2C_Status = RTC_I2CMasterSendStop();
	return I2C_Status;
	
}

void i2cBurstRead(uint8 Reg_Addr, uint8 *readData,uint8 dataSize)
{
	uint8 I2C_Status;
	I2C_Status = RTC_I2CMasterSendStart(RTC_ADDR, I2C_WRITE);
	I2C_Status = RTC_I2CMasterWriteByte(Reg_Addr);
    I2C_Status = RTC_I2CMasterSendRestart(RTC_ADDR, I2C_READ);
	if(RTC_I2C_MSTR_NO_ERROR == I2C_Status)/* Check if transfer completed without errors*/
	{
		/* Read array of dataSize bytes */
        int i;
		for(i=0; i<dataSize; i++)
		{ 
			if(i < dataSize-1)
			{
				readData[i] = RTC_I2CMasterReadByte(RTC_I2C_ACK_DATA);
			}
			else
			{
				readData[i] = RTC_I2CMasterReadByte(RTC_I2C_NAK_DATA);
			}
		}
	}
    I2C_Status = RTC_I2CMasterSendStop();
}
/* [] END OF FILE */
