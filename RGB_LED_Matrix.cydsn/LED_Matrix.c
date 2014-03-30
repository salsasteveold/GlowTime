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
void drawPixel(int8 x, int8 y, RGB c, color *matrix)
{
	/* pre-calculate some values to index the matrix 
	 * Note that the translation has been done here to
	 * leave the ISR clean
	 */
	int8 i = 0, index;
	
	/* index indexes the elements of 'matrix' 
	 * 'matrix' consists of 64 'color' structs, 4 elements per row
	 * The formula for index thus is index = y*4 + x/8
	 */
	int8 scratch1 = y*4;
	
	/* The x-coordinate is broken up into 2 parts:
	* 1. Which of the 4 FIFO bytes need to be written (scratch2)
	* 2. Which bit of that byte needs to be written (bit_pos)
	*/
	int8 scratch2 = (int8)(x/8);
	int8 bit_pos = (int8)x%8;
	
	index = scratch1 + scratch2;
	
	clearPixel(x, y, matrix);
	
	for(i = 0; i < 5 ; i++)
	{
		matrix[index].r[i] |= (int8)((int8)((c.r & (0x01 << i)) && 1)<<(bit_pos));
		matrix[index].g[i] |= (int8)((int8)((c.g & (0x01 << i)) && 1)<<(bit_pos));
		matrix[index].b[i] |= (int8)((int8)((c.b & (0x01 << i)) && 1)<<(bit_pos));
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

void drawRect(int16_t x, int16_t y,int16_t w, int16_t h,RGB c, color *matrix) {
  drawFastHLine(x, y, w, c, matrix);
  drawFastHLine(x, y+h, w, c, matrix);
  drawFastVLine(x, y, h, c, matrix);
  drawFastVLine(x+w, y, h, c, matrix);
}

void drawFastVLine(int8 x, int8 y, int8 h, RGB c, color *matrix) 
{
  // Update in subclasses if desired!
  drawLine(x, y, x, y+h, c, matrix);
}

void drawFastHLine(int8 x, int8 y, int8 w, RGB c, color *matrix) 
{
  // Update in subclasses if desired!
  drawLine(x, y, x+w, y, c, matrix);
}

void fillRect(int8 x, int8 y, int8 w, int8 h, RGB c, color *matrix) 
{
  // Update in subclasses if desired!
	int8 i = 0;
  for(i=x; i<x+w; i++) {
    drawFastVLine(i, y, h, c, matrix);
  }
}

void fillScreen(RGB c, color *matrix)
{
  fillRect(0, 0, 32, 16, c, matrix);
}

void drawTriangle(int8 x0, int8 y0,int8 x1, int8 y1,
						int8 x2, int8 y2, RGB c, color *matrix) 
{
  drawLine(x0, y0, x1, y1, c, matrix);
  drawLine(x1, y1, x2, y2, c, matrix);
  drawLine(x2, y2, x0, y0, c, matrix);
}

void drawOne(int8 x0, int8 y0,RGB c, color *matrix) 
{ 
	drawLine(x0+1, y0+2, x0+3, y0, c,matrix); 
	drawLine(x0+3, y0, x0+3, y0+11, c,matrix); 
	drawLine(x0+2, y0+11, x0+4, y0+11, c,matrix);
}

void drawTwo(int8 x0, int8 y0,RGB c, color *matrix) 
{ 
	drawPixel(x0,y0+1,c,matrix);
	drawFastHLine(x0+1,y0,3,c,matrix);
	drawFastVLine(x0+4,y0+1,4,c,matrix);
	drawFastHLine(x0+1,y0+5,3,c,matrix);
	drawFastVLine(x0,y0+6,6,c,matrix);
	drawFastHLine(x0,y0+11,5,c,matrix);
}

void drawColon(int8 x0, int8 y0,RGB c, color *matrix)
{
	drawFastVLine(x0,y0+3,2,c,matrix);
	drawFastVLine(x0,y0+7,2,c,matrix);
}

void drawThree(int8 x0, int8 y0,RGB c, color *matrix)
{
	drawFastHLine(x0,y0,5,c,matrix);
	drawFastVLine(x0+4,y0,4,c,matrix);
	drawPixel(x0+3,y0+4,c,matrix);
	drawFastHLine(x0+2,y0+5,2,c,matrix);
	drawFastVLine(x0+4,y0+6,5,c,matrix);
	drawFastHLine(x0+1,y0+11,3,c,matrix);
	drawPixel(x0,y0+10,c,matrix);
}

void drawFour(int8 x0, int8 y0,RGB c, color *matrix)
{
	drawFastVLine(x0,y0,7,c,matrix);
	drawFastHLine(x0,y0+6,5,c,matrix);
	drawFastVLine(x0+3,y0,12,c,matrix);
}

void drawFive(int8 x0, int8 y0,RGB c, color *matrix)
{
	drawFastHLine(x0,y0,5,c,matrix);
	drawFastVLine(x0,y0+1,6,c,matrix);
	drawFastHLine(x0+1,y0+5,3,c,matrix);
	drawFastVLine(x0+4,y0+6,5,c,matrix);
	drawFastHLine(x0+1,y0+11,3,c,matrix);
	drawPixel(x0,y0+10,c,matrix);
	
	
}
void drawSix(int8 x0, int8 y0,RGB c, color *matrix)
{
	drawFastHLine(x0+1,y0,4,c,matrix);
	drawFastVLine(x0,y0+1,10,c,matrix);
	drawFastHLine(x0+1,y0+5,3,c,matrix);
	drawFastVLine(x0+4,y0+6,5,c,matrix);
	drawFastHLine(x0+1,y0+11,3,c,matrix);
	
}
void drawSeven(int8 x0, int8 y0,RGB c, color *matrix)
{
	drawPixel(x0,y0+1,c,matrix);
	drawFastHLine(x0,y0,5,c,matrix);
	drawFastVLine(x0+4,y0,12,c,matrix);
}
void drawEight(int8 x0, int8 y0,RGB c, color *matrix)
{
	drawFastHLine(x0+1,y0,3,c,matrix);
	drawFastHLine(x0+1,y0+5,3,c,matrix);
	drawFastHLine(x0+1,y0+11,3,c,matrix);
	drawFastVLine(x0,y0+1,4,c,matrix);
	drawFastVLine(x0+4,y0+1,4,c,matrix);
	drawFastVLine(x0,y0+6,5,c,matrix);
	drawFastVLine(x0+4,y0+6,5,c,matrix);
}
void drawNine(int8 x0, int8 y0,RGB c, color *matrix)
{
	drawFastHLine(x0+1,y0,3,c,matrix);
	drawFastHLine(x0+1,y0+5,3,c,matrix);
	drawFastVLine(x0,y0+1,4,c,matrix);
	drawFastVLine(x0+4,y0+1,11,c,matrix);
}
void drawZero(int8 x0, int8 y0,RGB c, color *matrix)
{
	drawFastHLine(x0+1,y0,3,c,matrix);
	drawFastHLine(x0+1,y0+11,3,c,matrix);
	drawFastVLine(x0,y0+1,10,c,matrix);
	drawFastVLine(x0+4,y0+1,10,c,matrix);
}

void drawA(int8 x0, int8 y0,RGB c, color *matrix)
{
	drawLine(x0+2, y0, x0+4, y0+2, c, matrix);
	drawLine(x0, y0+2, x0+1, y0+1, c, matrix);
	drawFastHLine(x0+1,y0+7,3,c,matrix);
	drawFastVLine(x0+4,y0+2,10,c,matrix);
	drawFastVLine(x0,y0+2,10,c,matrix);
	
}

void drawB(int8 x0, int8 y0,RGB c, color *matrix)
{
	drawFastHLine(x0+1,y0+5,3,c,matrix);
	drawFastVLine(x0,y0,12,c,matrix);
	drawFastVLine(x0+4,y0+1,4,c,matrix);
	drawFastVLine(x0+4,y0+6,5,c,matrix);
	drawFastHLine(x0+1,y0,3,c,matrix);
	drawFastHLine(x0+1,y0+11,3,c,matrix);
}

void drawC(int8 x0, int8 y0,RGB c, color *matrix)
{
	drawFastVLine(x0,y0+2,8,c,matrix);
	drawFastHLine(x0+2,y0,3,c,matrix);
	drawFastHLine(x0+2,y0+11,3,c,matrix);
	//drawPixel(x0+4,y0+1,c,matrix);
	//drawPixel(x0+4,y0+10,c,matrix);
	drawPixel(x0+1,y0+1,c,matrix);
	drawPixel(x0+1,y0+10,c,matrix);
}

void drawD(int8 x0, int8 y0,RGB c, color *matrix)
{
	drawFastHLine(x0+1,y0,3,c,matrix);
	drawFastVLine(x0,y0,12,c,matrix);
	drawFastHLine(x0+1,y0+11,3,c,matrix);
	drawFastVLine(x0+4,y0+1,10,c,matrix);
	
}

void drawE(int8 x0, int8 y0,RGB c, color *matrix)
{
	drawFastHLine(x0+1,y0,4,c,matrix);
	drawFastVLine(x0,y0,12,c,matrix);
	drawFastHLine(x0+1,y0+11,4,c,matrix);
	drawFastHLine(x0+1,y0+5,4,c,matrix);
}

void drawF(int8 x0, int8 y0,RGB c, color *matrix)
{
	drawFastHLine(x0+1,y0,4,c,matrix);
	drawFastVLine(x0,y0,12,c,matrix);
	drawFastHLine(x0+1,y0+5,4,c,matrix);
}

void printHexString(uint16 num,int8 x0, int8 y0,RGB c, color *matrix)
{
	uint8 tokens[4]={0,0,0,0};	
	tokens[3] = 0x000F & num;
	tokens[2] = 0x000F & num>>4;
	tokens[1] = 0x000F & num>>8;
	tokens[0] = 0x000F & num>>12;
	
	drawHex(tokens[0],3, 2,c, matrix);
	drawHex(tokens[1],9, 2,c, matrix);
	drawHex(tokens[2],15, 2,c, matrix);
	drawHex(tokens[3],21, 2,c, matrix);
}

void printTime(uint8 hours,uint8 min,RGB c, color *matrix)
{
	uint8 tHour = hours >>4;
	if(tHour > 0)
	{
		drawHex(hours>>4,3, 2,c, matrix);
	}
	drawHex(hours,9, 2,c, matrix);
	drawColon(15, 2,c, matrix);
	drawHex(min>>4,17, 2,c, matrix);
	drawHex(min,23, 2,c, matrix);
}

void drawHex(uint8 num,int8 x0, int8 y0,RGB c, color *matrix)
{
	switch (num & 0x0F) 
	{
		case 0x1:
		  drawOne(x0,y0,c,matrix);
		  break;
		case 0x2:
		  drawTwo(x0,y0,c,matrix);
		  break;
		case 0x3:
		  drawThree(x0,y0,c,matrix);
		  break;
		case 0x4:
		  drawFour(x0,y0,c,matrix);
		  break;
		case 0x5:
		  drawFive(x0,y0,c,matrix);
		  break;
		case 0x6:
		  drawSix(x0,y0,c,matrix);
		  break;
		case 0x7:
		  drawSeven(x0,y0,c,matrix);
		  break;
		case 0x8:
		  drawEight(x0,y0,c,matrix);
		  break;
		case 0x9:
		  drawNine(x0,y0,c,matrix);
		  break;
		case 0xA:
		  drawA(x0,y0,c,matrix);
		  break;
		case 0xB:
		  drawB(x0,y0,c,matrix);
		  break;
		case 0xC:
		  drawC(x0,y0,c,matrix);
		  break;
		case 0xD:
		  drawD(x0,y0,c,matrix);
		  break;
		case 0xE:
		  drawE(x0,y0,c,matrix);
		  break;
		case 0xF:
		  drawF(x0,y0,c,matrix);
		  break;
		default:
		  drawZero(x0,y0,c,matrix);
		  break;
	}	
}

void drawblock(int8 blockLoc, int8 h, RGB c, color *matrix)
{
	int i = 0;
	blockLoc = blockLoc*4;
	if(blockLoc>28)
	{
		blockLoc=28;
	}
	else if(blockLoc<0)
	{
		blockLoc=0;
	}
	
	for(i=0;i<4;i++)
	{
		drawFastVLine(blockLoc+i, 0,h, c, matrix);
	}
}

int ifDataChange(uint8 *oldResult,uint16 *result)
{
	int i;
	int count=0;
	for(i=0;i<8;i++)
	{
		if(oldResult[i]==result[i])
		{
			count++;
			if(count==8)
			{
				return 1;
			}
		}
		else
		{
			return 0;
		}
	}
}

/* [] END OF FILE */
