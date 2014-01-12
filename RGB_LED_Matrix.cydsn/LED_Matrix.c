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
#include <stdlib.h>

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
void drawPixel(uint8 x, uint8 y, RGB c, color *matrix)
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
	
	clearPixel(x, y, matrix);
	
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
void clearPixel(uint8 x, uint8 y, color *matrix)
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
void clearScreen(color *matrix)
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

void drawCircle(int8 x0, int8 y0, int8 r,RGB c, color *matrix) {
  int8 f = 1 - r;
  int8 ddF_x = 1;
  int8 ddF_y = -2 * r;
  int8 x = 0;
  int8 y = r;

  drawPixel(x0 , y0+r, c,matrix);
  drawPixel(x0 , y0-r, c,matrix);
  drawPixel(x0+r, y0 , c,matrix);
  drawPixel(x0-r, y0 , c,matrix);

  while (x < y) 
  {
    if (f >= 0) 
	{
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    drawPixel(x0 + x, y0 + y, c,matrix);
    drawPixel(x0 - x, y0 + y, c,matrix);
    drawPixel(x0 + x, y0 - y, c,matrix);
    drawPixel(x0 - x, y0 - y, c,matrix);
    drawPixel(x0 + y, y0 + x, c,matrix);
    drawPixel(x0 - y, y0 + x, c,matrix);
    drawPixel(x0 + y, y0 - x, c,matrix);
    drawPixel(x0 - y, y0 - x, c,matrix);
  }

}

void drawCircleHelper( int8 x0, int8 y0,int8 r, int8 cornername, RGB c, color *matrix) {
  int8 f = 1 - r;
  int8 ddF_x = 1;
  int8 ddF_y = -2 * r;
  int8 x = 0;
  int8 y = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    if (cornername & 0x4) {
      drawPixel(x0 + x, y0 + y, c, matrix);
      drawPixel(x0 + y, y0 + x, c, matrix);
    }
    if (cornername & 0x2) {
      drawPixel(x0 + x, y0 - y, c, matrix);
      drawPixel(x0 + y, y0 - x, c, matrix);
    }
    if (cornername & 0x8) {
      drawPixel(x0 - y, y0 + x, c, matrix);
      drawPixel(x0 - x, y0 + y, c, matrix);
    }
    if (cornername & 0x1) {
      drawPixel(x0 - y, y0 - x, c, matrix);
      drawPixel(x0 - x, y0 - y, c, matrix);
    }
  }
}

void drawLine(int8 x0, int8 y0, int8 x1, int8 y1, RGB c, color *matrix)
{
  int8 steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int8 dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int8 err = dx / 2;
  int8 ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      drawPixel(y0, x0, c, matrix);
    } else {
      drawPixel(x0, y0, c, matrix);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

void drawFastVLine(int8 x, int8 y, int8 h, RGB c, color *matrix) 
{
  // Update in subclasses if desired!
  drawLine(x, y, x, y+h-1, c, matrix);
}

void drawFastHLine(int8 x, int8 y, int8 w, RGB c, color *matrix) 
{
  // Update in subclasses if desired!
  drawLine(x, y, x+w-1, y, c, matrix);
}
/* [] END OF FILE */
