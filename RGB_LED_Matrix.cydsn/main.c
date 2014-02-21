/* ========================================
 *
 * The following firmware was developed by Cypress Semiconductor
 * This work is licensed under a Creative Commons Attribution 3.0 Unported License.
 * 
 * http://creativecommons.org/licenses/by/3.0/deed.en_US
 * 
 * You are free to:
 * -To Share — to copy, distribute and transmit the work 
 * -To Remix — to adapt the work 
 * -To make commercial use of the work
 *
 * ======================================== 
 */
 
/*******************************************************************************
 * Pioneer Kit 16x32 RGB LED Matrix Example Project
 ********************************************************************************
 * This project Displays 5-bit color image at a refresh rate of 360 Hz
 * It uses 75% of the UDB datapaths and 50% of the PLDs
 * The matrix is constructed as 2 planes of 8 rows each. (R1, G1, B1) write to the first plane
 * (R2, G2, B2) are for the second plane. Rows are selected using (A, B, C). Columns are
 * written by clocking out 32 (R, G, B) values.
 * LAT and OE are active low: i.e. data is latched and output is enabled on logic 0
 *
 * Expanding the project to 8-bit color is simple - just needs a little more code! This is 
 * left to the user to implement. Also TO DO: gamma correction
 * 
 * To buy or see a tutorial on the RGB LED Matrix, go here: http://www.adafruit.com/products/420
 * For more details on the panel itself, see one of the links below
 *
 * Credit to the following sites/authors:
 * Reference: Adafruit tutorial and code https://github.com/adafruit/RGB-matrix-Panel
 * Ghosting: http://www.rayslogic.com/propeller/Programming/AdafruitRGB/AdafruitRGB.htm 
 * Technical: http://www.hobbypcb.com/blog/item/3-16x32-rgb-led-matrix-technical-details.html
 * Favicon idea: http://rhb.me/2012/05/led-matrix-bringup/
 **************************************************************************************** */

#include <device.h>
#include <LED_Matrix.h>
#include "I2CDriver.h"

/* j is the row counter (0-7), pwm_count is used for Binary Coded Modulation */
uint8 j = 0, pwm_count = 0;
/* Tells which bit of color is currently being written */
uint8 bit_shift;
/* stores the currently displayed image in 5-bit color */
color matrix[16*4];

/*******************************************************************************
* Function Name: isr_2
********************************************************************************
*
* Summary:
*  ISR that does most of the heavy lifting: 
*  - BCM for 5-bit color
*  - Writes image in matrix[] to the FIFOs in the LED_Matrix Component
*  - Takes about 9.80uS @ 48MHz, the Component then takes ~2.3 uS to shift out data
*
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(FIFO_EMPTY)
{
	/* Clear pending interrupts */
	*isr_2_INTC_CLR_PD = isr_2__INTC_MASK;
	
	/* Setting the latch passes the value through the LED driver
	 * Clearing the latch then latches this value
	 * See: http://www.bjtopspace.com/ziliao/CYT62726.pdf
	 */
//	Set_LAT;				/* Note that this is done in hardware, and these 2 lines have no effect since CR_Addr[3] is not connected anywhere */
//	Clear_LAT;

	/* Enable Outputs - OE is control[1], and is active low. 
	 * control[0] is 'enable', so leave it at 1 
	 */ 
	LED_Matrix_1_WriteControl(0x01);
	
	pwm_count++;

	/* Binary coded modulation. Read more here: http://www.batsocks.co.uk/readme/art_bcm_1.htm  */
	/*if(pwm_count == 31)
	{
		bit_shift = 0;
		pwm_count = 0;
		j++;
		
		if(j == 8)
		{
			j = 0;
		}
	}*/
	/*if(pwm_count == 7)
	{
		bit_shift = 0;
		pwm_count = 0;
		j++;
		
		if(j == 8)
		{
			j = 0;
		}
	}*/
	if(pwm_count == 3)
	{
		//bit_shift = 2;
		bit_shift = 0;
		pwm_count = 0;
		j++;
		
		if(j == 8)
		{
			j = 0;
		}
	}
	else if(pwm_count == 1)
	{
		bit_shift = 1;
	}
	
	/*
	else if(pwm_count == 7)
	{
		bit_shift = 3;
	}*/
	/*else if(pwm_count == 15)
	{
		bit_shift = 4;
	}*/

	/* Write the values to the FIFOs. Note that the data is not written to the matrix until all the FIFOs are written to */
	
	/****************************** Visually mapping out the matrix **********************
	*	A row in Plane1:		0th byte		1st byte		2nd byte		3rd byte
	* 	F0_REG_0 	R1	 	x-x-x-x-x-x-x-x x-x-x-x-x-x-x-x x-x-x-x-x-x-x-x x-x-x-x-x-x-x-x 
	*	F0_REG_1	G1			.												.
	*	F0_REG_2	B1			.												.
	*							.												.
	*	A row in Plane2:		.												.
	*	F1_REG_0 	R2	 	x-x-x-x-x-x-x-x x-x-x-x-x-x-x-x x-x-x-x-x-x-x-x x-x-x-x-x-x-x-x 
	*	F1_REG_1	G2			.												.
	*	F1_REG_2	B2			.												.
	*
	* Note: The 8 rows are selected by (A, B, C)
	*************************************************************************************/
	
	/* These four lines write to the first plane */
	LED_Matrix_1_F0_REG_0 = (uint8)matrix[0 + j*4].r[bit_shift];
	LED_Matrix_1_F0_REG_0 = (uint8)matrix[1 + j*4].r[bit_shift];
	LED_Matrix_1_F0_REG_0 = (uint8)matrix[2 + j*4].r[bit_shift];
	LED_Matrix_1_F0_REG_0 = (uint8)matrix[3 + j*4].r[bit_shift];

	LED_Matrix_1_F0_REG_1 = (uint8)matrix[0 + j*4].g[bit_shift];
	LED_Matrix_1_F0_REG_1 = (uint8)matrix[1 + j*4].g[bit_shift];
	LED_Matrix_1_F0_REG_1 = (uint8)matrix[2 + j*4].g[bit_shift];
	LED_Matrix_1_F0_REG_1 = (uint8)matrix[3 + j*4].g[bit_shift];
	
	/* These four lines write to the second plane */
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

	/* Disable outputs */
	LED_Matrix_1_WriteControl(0x03);
	
	/* Note that row change occurs at a lower frequency than the BCM because of mystery ghosting */
	Row_Select(j);

	/* Once F1_REG_0 is full (this line does it), the Component will begin shifting out values */
	LED_Matrix_1_F1_REG_0 = (uint8)matrix[3 + (j+8)*4].r[bit_shift];
}
uint8 dataReady = 0;
uint16 result = 0x0000;
uint16 oldResult = 0x0000;
CY_ISR(eoc_isr)
{
	result = (uint16)(ADC_SAR_CHAN0_RESULT_REG & ADC_RESULT_MASK);
	if((result & 0xFF00) == 0xFF00)
	{
		result = 0;
	}
	result=result & 0x0FE0;
	dataReady = 1;
}

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Handles UART Comm and updates matrix buffer
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/

int main()
{	
	/* struct that can accomodate 8-bit RGB color */
	RGB c;
	RTC_Start();
	PCF8583 rtc;
	uint8 I2C_Status;
	localTimeInit(&rtc);
	//setTime(&rtc);
	
	
	I2C_Status = getTime(&rtc);
	
	
	/* Buffer for UART data */
	//uint16 array[6] = {0, 0, 0, 0, 0, 0};
	

	/* Initializations */
	c.r = 0x00;
	c.g = 0x00;
	c.b = 0x00;
	clearScreen(matrix);
	
	LED_Matrix_1_Start();
    //UART_Start();
    
	
	
	/* Enable Component */
	LED_Matrix_1_WriteControl(0x03);

	/* Start the isr that is triggered everytime the Component finishes writing to the matrix */
	isr_2_StartEx(FIFO_EMPTY);
	ADC_Start();
	eoc_StartEx(eoc_isr);
	ADC_StartConvert();
	
	/* Enable interrupts */
	CyGlobalIntEnable;
	c.r = 3;
	c.g = 0;
	c.b = 0;
	int8 tmp = 0x07;
	int i;
	for(;;)
    { 	
		
		/*
		//ADCVoltage = ADC_CountsTo_Volts(0,result);
		//drawF(3,2,c,matrix);
		//drawC(9,2,c, matrix);
		//drawColon(15,2,c,matrix);
		//drawD(17,2,c,matrix);
		//drawE(23,2,c,matrix);
		if((dataReady != 0) && (result != oldResult))
		{
			oldResult = result;
			dataReady = 0 ;
			tmp = (int8)(result>>7);
			clearScreen(matrix);
			if(tmp<0)
			{
				tmp = 0;	
			}
			else if(tmp>16)
			{
				tmp=16;
			}
			for(i=0;i<32;i++)
			{
				drawFastVLine(i, 0, 5, c, matrix);
			}
			
		}
		else
		{
			
			for(i=0;i<32;i++)
			{
				drawFastVLine(i, 0, 5, c, matrix);
			}
		}
		*/
		printTime(decToBcd(rtc.hour),decToBcd(rtc.minute),c, matrix);
		//fillScreen(c, matrix);
	}
	return 0;
}

///* [] END OF FILE */
	