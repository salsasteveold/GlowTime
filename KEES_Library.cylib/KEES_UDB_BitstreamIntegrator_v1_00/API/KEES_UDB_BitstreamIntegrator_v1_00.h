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
#ifndef `$INSTANCE_NAME`_HEADER
#define `$INSTANCE_NAME`_HEADER

#include <device.h>

#define `$INSTANCE_NAME`_AUX_CTL (*(reg8 *) `$INSTANCE_NAME`_Counter7__CONTROL_AUX_CTL_REG)

void `$INSTANCE_NAME`_Start();

#endif