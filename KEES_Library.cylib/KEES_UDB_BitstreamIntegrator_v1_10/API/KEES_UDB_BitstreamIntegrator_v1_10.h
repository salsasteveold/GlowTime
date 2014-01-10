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

#define `$INSTANCE_NAME`_INTCONST_PTR ((reg16 *) `$INSTANCE_NAME`_Integrator16_u0__16BIT_A0_REG)
#define `$INSTANCE_NAME`_INTCONST_REG (*(reg16 *) `$INSTANCE_NAME`_Integrator16_u0__16BIT_A0_REG)

void `$INSTANCE_NAME`_Start();

#endif