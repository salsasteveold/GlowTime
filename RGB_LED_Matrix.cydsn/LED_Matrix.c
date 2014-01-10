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
 * C File For LED Matrix Component/Project
 ********************************************************************************/
 
#include <device.h>
#include <LED_Matrix.h>

/*******************************************************************************
* Function Name: DrawPixel
********************************************************************************
*
* Summary:
*  This function writes to the (x,y) coordinate of the 'matrix' buffer in RAM
*
* Parameters:  
*   uint8 x: 		betn 0 and 31
*	uint8 y: 		betn 0 and 15
*	RGB c:			5-bit color to be written to the pixel 
* 	color *matrix: 	pointer to the matrix buffer
*
* Return:
*   None
*
*******************************************************************************/
void DrawPixel(uint8 x, uint8 y, RGB c, color *matrix)
{
	/* pre-calculate some values to index the matrix 
	 * Note that the translation has been done here to
	 * leave the ISR clean
	 */
	uint8 i = 0, index;
	
	/* index indexes the elements of 'matrix' 
	 * 'matrix' consists of 64 'color' structs, 4 elements per row
	 * The formula for index thus is index = y*4 + x/8
	 */
	uint8 scratch1 = y*4;
	
	/* The x-coordinate is broken up into 2 parts:
	* 1. Which of the 4 FIFO bytes need to be written (scratch2)
	* 2. Which bit of that byte needs to be written (bit_pos)
	*/
	uint8 scratch2 = (uint8)(x/8);
	uint8 bit_pos = (uint8)x%8;
	
	index = scratch1 + scratch2;
	
	ClearPixel(x, y, matrix);
	
	for(i = 0; i < 5 ; i++)
	{
		matrix[index].r[i] |= (uint8)((uint8)((c.r & (0x01 << i)) && 1)<<(bit_pos));
		matrix[index].g[i] |= (uint8)((uint8)((c.g & (0x01 << i)) && 1)<<(bit_pos));
		matrix[index].b[i] |= (uint8)((uint8)((c.b & (0x01 << i)) && 1)<<(bit_pos));
	}
}

/*******************************************************************************
* Function Name: ClearPixel
********************************************************************************
*
* Summary:
*  This function clears the (x,y) pixel of the matrix buffer
*
* Parameters:  
*   uint8 x: 		betn 0 and 31
*	uint8 y: 		betn 0 and 15
* 	color *matrix: 	pointer to the matrix buffer
*
* Return:
*   None
*
*******************************************************************************/
void ClearPixel(uint8 x, uint8 y, color *matrix)
{
	uint8 i, index;
	uint8 scratch1 = y*4;
	uint8 scratch2 = (uint8)(x/8);
	uint8 bit_pos = (uint8)x%8;
	
	index = scratch1 + scratch2;
	
	for(i = 0; i < 5 ; i++)
	{
		matrix[index].r[i] &= ~(uint8)(0x01<<(bit_pos));
		matrix[index].g[i] &= ~(uint8)(0x01<<(bit_pos));
		matrix[index].b[i] &= ~(uint8)(0x01<<(bit_pos));
	}
}

/*******************************************************************************
* Function Name: ClearScreen
********************************************************************************
*
* Summary:
*  This function clears the 'matrix' buffer in RAM
*
* Parameters:  
* 	color *matrix: 	pointer to the matrix buffer
*
* Return:
*   None
*
*******************************************************************************/
void ClearScreen(color *matrix)
{
	uint8 x, index;
	
	for(index = 0; index < 64; index++)
	{
		for(x = 0; x < 5 ; x++)
		{
			matrix[index].r[x] = 0x00;
			matrix[index].g[x] = 0x00;
			matrix[index].b[x] = 0x00;
		}
	}
}

/* [] END OF FILE */
