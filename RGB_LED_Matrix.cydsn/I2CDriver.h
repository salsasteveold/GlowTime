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
#ifndef I2CDriver_h_
#define I2CDriver_h_

struct PCF8583_Tag;
	
typedef struct PCF8583_Tag
{
	uint8 hour;
	uint8 minute;
	uint8 sec;
	uint8 day;
	uint8 weekday;
	uint8 month;
	uint8 year;
	uint8 pm;
	uint8 format;
	
} PCF8583;

void localTimeInit(PCF8583 *RTC);
uint8 decToBcd(uint8 val);
uint8 bcdToDec(uint8 val);
uint8 i2cWrite(uint8 Reg_Addr,uint8 Reg_Data);
void i2cBurstRead(uint8 Reg_Addr, uint8 *readData,uint8 dataSize);
uint8 setTime(PCF8583 *RTC);
uint8 getTime(PCF8583 *RTC);


#endif
//[] END OF FILE
