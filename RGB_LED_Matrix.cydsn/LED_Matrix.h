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
 * Header For LED Matrix Component/Project
 ********************************************************************************/
 
#include <CR_Addr.h>

/* Few defines to simplify setting A B C and LAT */
#define Row_Select(r)			CR_Addr_Control=(CR_Addr_Control&0xF8)|(r&0x07)

#define Set_LAT					CR_Addr_Control=(CR_Addr_Control|0x08)
#define Clear_LAT				CR_Addr_Control=(CR_Addr_Control&0xF7)			/* LAT is Addr_CR 3 */
#define swap(a, b) 				{uint8 t = a; a = b; b = t;}






/*******************************************************************************
* Type Declarations
********************************************************************************/
/* Struct to hold 5-bit RGB color planes (For Matrix) */
typedef struct
{
	uint8 r[5];
	uint8 g[5];
	uint8 b[5];
} color;

/* struct to hold actual (upto 8-bit) color */
typedef struct
{
	uint8 r;
	uint8 g;
	uint8 b;
} RGB;

/*******************************************************************************
* Array to hold the matrix image - defined in main
********************************************************************************/
extern color matrix[64];

/*******************************************************************************
* Function Prototypes
********************************************************************************/
void drawPixel(int8 x, int8 y, RGB c, color *matrix);
void clearPixel(uint8 x, uint8 y, color *matrix);
void clearScreen(color *matrix);
void drawCircle(int8 x0, int8 y0, int8 r,RGB c, color *matrix);
void drawCircleHelper( int8 x0, int8 y0,int8 r, int8 cornername, RGB c, color *matrix);
void drawLine(int8 x0, int8 y0, int8 x1, int8 y1, RGB c, color *matrix);
void drawFastVLine(int8 x, int8 y, int8 h, RGB c, color *matrix);
void drawFastHLine(int8 x, int8 y, int8 h, RGB c, color *matrix);
void fillRect(int8 x, int8 y, int8 w, int8 h, RGB c, color *matrix);
void fillScreen(RGB c, color *matrix);
void drawTriangle(int8 x0, int8 y0,int8 x1, int8 y1,int8 x2, int8 y2, RGB c, color *matrix);
void drawOne(int8 x0, int8 y0,RGB c, color *matrix);
void drawTwo(int8 x0, int8 y0,RGB c, color *matrix);
void drawColon(int8 x0, int8 y0,RGB c, color *matrix);
void drawThree(int8 x0, int8 y0,RGB c, color *matrix);
void drawFour(int8 x0, int8 y0,RGB c, color *matrix);
void drawFive(int8 x0, int8 y0,RGB c, color *matrix);
void drawSix(int8 x0, int8 y0,RGB c, color *matrix);
void drawSeven(int8 x0, int8 y0,RGB c, color *matrix);
void drawEight(int8 x0, int8 y0,RGB c, color *matrix);
void drawNine(int8 x0, int8 y0,RGB c, color *matrix);
void drawZero(int8 x0, int8 y0,RGB c, color *matrix);
void drawA(int8 x0, int8 y0,RGB c, color *matrix);
void drawB(int8 x0, int8 y0,RGB c, color *matrix);
void drawC(int8 x0, int8 y0,RGB c, color *matrix);
void drawD(int8 x0, int8 y0,RGB c, color *matrix);
void drawE(int8 x0, int8 y0,RGB c, color *matrix);
void drawF(int8 x0, int8 y0,RGB c, color *matrix);
void printTime(uint8 hours,uint8 min,RGB c, color *matrix);
void printHexString(uint16 num,int8 x0, int8 y0,RGB c, color *matrix);
void drawHex(uint8 num,int8 x0, int8 y0,RGB c, color *matrix);


//[] END OF FILE
