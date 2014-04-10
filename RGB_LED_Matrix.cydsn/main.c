#include <device.h>
#include <LED_Matrix.h>
#include "I2CDriver.h"

uint8 j = 0, pwm_count = 0;
uint8 bit_shift;
color matrix[16*4];

int clock = 1;
CY_ISR(PB_ISR)
{
	if(clock == 0)
	{
		clock=1;
	}
	else
	{
		clock=0;
	}
}

CY_ISR(FIFO_EMPTY)
{

	*isr_2_INTC_CLR_PD = isr_2__INTC_MASK;
	
	LED_Matrix_1_WriteControl(0x01);
	
	pwm_count++;

	if(pwm_count == 1)
	{
		bit_shift = 1;
	}
	else if(pwm_count == 3)
	{
		bit_shift = 0;
		pwm_count = 0;
		j++;
		
		if(j == 8)
		{
			j = 0;
		}
	}

	LED_Matrix_1_F0_REG_0 = (uint8)matrix[0 + j*4].r[bit_shift];
	LED_Matrix_1_F0_REG_0 = (uint8)matrix[1 + j*4].r[bit_shift];
	LED_Matrix_1_F0_REG_0 = (uint8)matrix[2 + j*4].r[bit_shift];
	LED_Matrix_1_F0_REG_0 = (uint8)matrix[3 + j*4].r[bit_shift];

	LED_Matrix_1_F0_REG_1 = (uint8)matrix[0 + j*4].g[bit_shift];
	LED_Matrix_1_F0_REG_1 = (uint8)matrix[1 + j*4].g[bit_shift];
	LED_Matrix_1_F0_REG_1 = (uint8)matrix[2 + j*4].g[bit_shift];
	LED_Matrix_1_F0_REG_1 = (uint8)matrix[3 + j*4].g[bit_shift];
	
	LED_Matrix_1_F1_REG_1 = (uint8)matrix[0 + (j+8)*4].g[bit_shift];
	LED_Matrix_1_F1_REG_1 = (uint8)matrix[1 + (j+8)*4].g[bit_shift];
	LED_Matrix_1_F1_REG_1 = (uint8)matrix[2 + (j+8)*4].g[bit_shift];
	LED_Matrix_1_F1_REG_1 = (uint8)matrix[3 + (j+8)*4].g[bit_shift];
	
	LED_Matrix_1_F0_REG_2 = (uint8)matrix[0 + j*4].b[bit_shift];
	LED_Matrix_1_F0_REG_2 = (uint8)matrix[1 + j*4].b[bit_shift];
	LED_Matrix_1_F0_REG_2 = (uint8)matrix[2 + j*4].b[bit_shift];
	LED_Matrix_1_F0_REG_2 = (uint8)matrix[3 + j*4].b[bit_shift];

	LED_Matrix_1_F1_REG_2 = (uint8)matrix[0 + (j+8)*4].b[bit_shift];
	LED_Matrix_1_F1_REG_2 = (uint8)matrix[1 + (j+8)*4].b[bit_shift];
	LED_Matrix_1_F1_REG_2 = (uint8)matrix[2 + (j+8)*4].b[bit_shift];
	LED_Matrix_1_F1_REG_2 = (uint8)matrix[3 + (j+8)*4].b[bit_shift];
	
	LED_Matrix_1_F1_REG_0 = (uint8)matrix[0 + (j+8)*4].r[bit_shift];
	LED_Matrix_1_F1_REG_0 = (uint8)matrix[1 + (j+8)*4].r[bit_shift];
	LED_Matrix_1_F1_REG_0 = (uint8)matrix[2 + (j+8)*4].r[bit_shift];

	LED_Matrix_1_WriteControl(0x03);
	
	Row_Select(j);

	LED_Matrix_1_F1_REG_0 = (uint8)matrix[3 + (j+8)*4].r[bit_shift];
}
uint8 dataReady = 0;
uint16 result[8] = {0,0,0,0,0,0,0,0};
uint8 oldResult[8] = {0,0,0,0,0,0,0,0};
int w = 0;
int refresh=0;
CY_ISR(eoc_isr)
{
	
	result[0] = (uint16)(ADC_SAR_CHAN0_RESULT_REG & ADC_RESULT_MASK);
	result[1] = (uint16)(ADC_SAR_CHAN1_RESULT_REG & ADC_RESULT_MASK);
	result[2] = (uint16)(ADC_SAR_CHAN2_RESULT_REG & ADC_RESULT_MASK);
	result[3] = (uint16)(ADC_SAR_CHAN3_RESULT_REG & ADC_RESULT_MASK);
	result[4] = (uint16)(ADC_SAR_CHAN4_RESULT_REG & ADC_RESULT_MASK);
	result[5] = (uint16)(ADC_SAR_CHAN5_RESULT_REG & ADC_RESULT_MASK);
	result[6] = (uint16)(ADC_SAR_CHAN6_RESULT_REG & ADC_RESULT_MASK);
	result[7] = (uint16)(ADC_SAR_CHAN7_RESULT_REG & ADC_RESULT_MASK);
	for(w=0;w<8;w++)
	{
		if((result[w] & 0xFF00) == 0xFF00)
		{
			result[w] = 0;
		}
	}
	dataReady = 1;
	
}


int main()
{	
	int i = 0;
	//RGB white;
    RTC_Start();
	PCF8583 rtc;
    uint8 I2C_Status;
    I2C_Status = i2cWrite(0x00,0x04);
	
    
	localTimeInit(&rtc);
    setTime(&rtc);
    
	//white.r = 0;
	//white.g = 0;
	//white.b = 0;
	
	RGB lotsOfColors[8];
	lotsOfColors[0].r = 1;
	lotsOfColors[0].g = 0;
	lotsOfColors[0].b = 0;
	
	lotsOfColors[1].r = 1;
	lotsOfColors[1].g = 1;
	lotsOfColors[1].b = 0;
	
	lotsOfColors[2].r = 0;
	lotsOfColors[2].g = 0;
	lotsOfColors[2].b = 1;
	
	lotsOfColors[3].r = 0;
	lotsOfColors[3].g = 1;
	lotsOfColors[3].b = 1;
	
	lotsOfColors[4].r = 1;
	lotsOfColors[4].g = 0;
	lotsOfColors[4].b = 1;
	
	lotsOfColors[5].r = 1;
	lotsOfColors[5].g = 1;
	lotsOfColors[5].b = 1;
	
	lotsOfColors[6].r = 2;
	lotsOfColors[6].g = 1;
	lotsOfColors[6].b = 1;
	
	lotsOfColors[7].r = 2;
	lotsOfColors[7].g = 2;
	lotsOfColors[7].b = 0;
	
	clearScreen(matrix);
	
	LED_Matrix_1_Start();
	
	LED_Matrix_1_WriteControl(0x03);

	isr_2_StartEx(FIFO_EMPTY);
	ADC_Start();
	ADC_StartConvert();
	eoc_StartEx(eoc_isr);
    PB_StartEx(PB_ISR); 
	
	
	CyGlobalIntEnable;
	int dataChange = 0;
   
	for(;;)
    { 	
		CyDelay(1);
		if(clock == 0)
        {
    		if(dataReady == 1)
    		{
    			dataChange = ifDataChange(&oldResult[0],&result[0]);
    			dataReady = 0;
    			if(dataChange == 1)
    			{
    				for(i=0;i<8;i++)
    				{
    					oldResult[i] = ((uint8)(result[i]>>7)) & 0x0F;
    				}
    				for(i=0;i<8;i++)
    				{
    					drawblock(i,oldResult[i],lotsOfColors[i],matrix);
    				}
    			}
    		}
        }
        else
        {
            I2C_Status = getTime(&rtc);
            printTime(decToBcd(rtc.hour),decToBcd(rtc.minute),lotsOfColors[2], matrix);
            clearScreen(matrix);
        }
	}
}

///* [] END OF FILE */
	