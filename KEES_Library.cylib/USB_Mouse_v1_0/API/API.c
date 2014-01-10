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

void `$INSTANCE_NAME`_Write(int8 x, int8 y, int8 buttons)
{
    int8 Mouse_Data[3];
    
    Mouse_Data[0] = buttons;
    Mouse_Data[1] = x;
    Mouse_Data[2] = y;
    
    `$INSTANCE_NAME`_USBFS_LoadInEP(1, Mouse_Data, 3);
    while(!`$INSTANCE_NAME`_USBFS_bGetEPAckState(1));  //Wait for ACK before loading data 

    return;
}

/* [] END OF FILE */
