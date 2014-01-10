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

#ifndef `$INSTANCE_NAME`_USBMOUSE_HEADERFILE
#define `$INSTANCE_NAME`_USBMOUSE_HEADERFILE

#include "cytypes.h"
#include "cyfitter.h"

#define `$INSTANCE_NAME`_LEFT_CLICK 0x01
#define `$INSTANCE_NAME`_MIDDLE_CLICK 0x02
#define `$INSTANCE_NAME`_RIGHT_CLICK 0x04
#define `$INSTANCE_NAME`_NO_CLICK 0

void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Enumerate(void);
void `$INSTANCE_NAME`_Write(int8 x, int8 y, int8 buttons);

#endif

//[] END OF FILE
