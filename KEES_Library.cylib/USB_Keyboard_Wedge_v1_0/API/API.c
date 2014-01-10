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

#include "project.h"

// decode shift need based on ascii value
// implements ASCII from 0x20 to 0x7F
const uint8 `$INSTANCE_NAME`_aASCII_ToScanCode[] = {0x2C, 0x1E, 0x34, 0x20, 0x21, 0x22, 0x24, 0x34, 0x26, 0x27, 0x25, 0x2E, 0x36, 0x2D, 0x37, 0x38, 0x27, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x33, 0x33, 0x36, 0x2E, 0x37, 0x38, 0x1F, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15 ,0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x2F, 0x31, 0x30, 0x23, 0x2D, 0x35, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15 ,0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x2F, 0x31, 0x30, 0x35, 0x4C};
`$INSTANCE_NAME`_KEYBOARD_BUFFER buffer;

void `$INSTANCE_NAME`_Start(void) 
{
    `$INSTANCE_NAME`_USBFS_Start(0, `$INSTANCE_NAME`_USBFS_3V_OPERATION);
    
    return;
}

void `$INSTANCE_NAME`_Enumerate(void)
{
    while(!`$INSTANCE_NAME`_USBFS_bGetConfiguration());      //Wait for Device to enumerate 
    
    return;
}

void `$INSTANCE_NAME`_TypeString(uint8 * szBuffer)
{
    uint8 i = 0; // limits the maximum length the string passed can be
    uint8 key;
    
    buffer.control = 0;
    buffer.reserved = 0;
    buffer.key0 = 0;
    buffer.key1 = 0;
    buffer.key2 = 0;
    buffer.key3 = 0;
    buffer.key4 = 0;
    buffer.key5 = 0;
    
    while(szBuffer[i] != 0)
    {
        // ensure that the key is within the range of decodable characters
        if((szBuffer[i] >= 0x20) && (szBuffer[i] <= 0x7F))
        {
            key = szBuffer[i] - 0x20; // remove the offset so we can index into our array
            // determine if we need a shift key
            if(((key >= 1) && (key <= 6)) || ((key >= 8) && (key <=11)) || (key == 26) || (key == 28) || ((key >= 30) && (key <=58)) || (key == 62) || (key == 63) || ((key >= 91) && (key <= 94)))
            {

                buffer.control = `$INSTANCE_NAME`_LSHIFT;
            }
            else
            {
                buffer.control = 0;
            }
            
                buffer.key0 = `$INSTANCE_NAME`_aASCII_ToScanCode[key];
        }
        else if(szBuffer[i] == 0x08)
        {
            // backspace
            buffer.key0 = `$INSTANCE_NAME`_BACKSPACE;
        }
        else if(szBuffer[i] == 0x09)
        {
            buffer.key0 = `$INSTANCE_NAME`_TAB;
        }
        else if(szBuffer[i] == 0x0A || szBuffer[i] == 0x0D)
        {
            buffer.key0 = `$INSTANCE_NAME`_ENTER;
        }
        else if(szBuffer[i] == 0x1B)
        {
            buffer.key0 = `$INSTANCE_NAME`_ESCAPE;
        }
        
        `$INSTANCE_NAME`_USBFS_LoadInEP(1, &(buffer.control), sizeof(`$INSTANCE_NAME`_KEYBOARD_BUFFER)); 
        while(!`$INSTANCE_NAME`_USBFS_bGetEPAckState(1));  //Wait for ACK before loading data 
        
        buffer.control = 0;
        buffer.key0 = 0;
        
        `$INSTANCE_NAME`_USBFS_LoadInEP(1, &(buffer.control), sizeof(`$INSTANCE_NAME`_KEYBOARD_BUFFER)); 
        while(!`$INSTANCE_NAME`_USBFS_bGetEPAckState(1));  //Wait for ACK before loading data 
        
        i++;
    }
}

/* [] END OF FILE */
