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

#ifndef `$INSTANCE_NAME`_USBKEYBOARD_HEADERFILE
#define `$INSTANCE_NAME`_USBKEYBOARD_HEADERFILE

#include "cytypes.h"
#include "cyfitter.h"

typedef struct{
    uint8 control;
    uint8 reserved;
    uint8 key0;
    uint8 key1;
    uint8 key2;
    uint8 key3;
    uint8 key4;
    uint8 key5;
} `$INSTANCE_NAME`_KEYBOARD_BUFFER;

#define `$INSTANCE_NAME`_LCTRL 0x01
#define `$INSTANCE_NAME`_LSHIFT 0x02
#define `$INSTANCE_NAME`_LALT 0x04
#define `$INSTANCE_NAME`_LWINDOWS 0x08

#define `$INSTANCE_NAME`_RCTRL 0x10
#define `$INSTANCE_NAME`_RSHIFT 0x20
#define `$INSTANCE_NAME`_RALT 0x40
#define `$INSTANCE_NAME`_RWINDOWS 0x80

#define `$INSTANCE_NAME`_ENTER 0x28
#define `$INSTANCE_NAME`_TAB 0x2B
#define `$INSTANCE_NAME`_BACKSPACE 0x2A
#define `$INSTANCE_NAME`_ESCAPE 0x29

void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Enumerate(void);
void `$INSTANCE_NAME`_TypeString(uint8 * szBuffer);

#endif

//[] END OF FILE
