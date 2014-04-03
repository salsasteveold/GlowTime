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

int8 height[]={0,2,4,6,8,10,12,14};

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
int PB = 0; 
CY_ISR(PB_ISR)
{
	if(PB==0)
	{
		PB=1;
	}
	else
	{
		PB=0;
	}
}

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
	/*else if(pwm_count == 7)
	{
		bit_shift = 3;
	}
	else if(pwm_count == 15)
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
	int i = 0;
	/* struct that can accomodate 8-bit RGB color */
	RGB white;
	white.r = 31;
	white.g = 31;
	white.b = 31;
	
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
	
	
	CyGlobalIntEnable;
	int dataChange = 0;
	int dataDecrease = 0;
	for(;;)
    { 	
		CyDelay(1);
		
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
}

///* [] END OF FILE */
	