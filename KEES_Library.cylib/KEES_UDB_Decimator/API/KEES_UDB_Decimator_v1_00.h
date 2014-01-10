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
#ifndef `$INSTANCE_NAME`_API
#define `$INSTANCE_NAME`_API

#include <device.h>

#define `$INSTANCE_NAME`_OUTPUT_PTR  ((reg16 *) `$INSTANCE_NAME`_CIC_Decimator_u0__16BIT_F1_REG)
#define `$INSTANCE_NAME`_OUTPUT_LOW_PTR ((reg16 *) `$INSTANCE_NAME`_CIC_Decimator_u0__F1_REG)
#define `$INSTANCE_NAME`_OUTPUT_HIGH_PTR ((reg16 *) `$INSTANCE_NAME`_CIC_Decimator_u1__F1_REG)


void `$INSTANCE_NAME`_Start();

#endif
//[] END OF FILE
