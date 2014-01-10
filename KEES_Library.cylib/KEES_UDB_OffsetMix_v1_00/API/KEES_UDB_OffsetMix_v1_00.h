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
#ifndef `$INSTANCE_NAME`_HEADERFILE
#define `$INSTANCE_NAME`_HEADERFILE

#include <device.h>

#define `$INSTANCE_NAME`_OUTPUT_PTR ((reg16 *) `$INSTANCE_NAME`_OffsetMixer_LSB__16BIT_F0_REG)
#define `$INSTANCE_NAME`_OUTPUT_LOW_PTR ((reg8 *) `$INSTANCE_NAME`_OffsetMixer_LSB__F0_REG)
#define `$INSTANCE_NAME`_OUTPUT_HIGH_PTR ((reg8 *) `$INSTANCE_NAME`_OffsetMixer_MSB__F0_REG)

#define `$INSTANCE_NAME`_OUTPUT_REG (*(reg16 *) `$INSTANCE_NAME`_OffsetMixer_LSB__16BIT_F0_REG)
#define `$INSTANCE_NAME`_OUTPUT_LOW_REG (*(reg8 *) `$INSTANCE_NAME`_OffsetMixer_LSB__F0_REG)
#define `$INSTANCE_NAME`_OUTPUT_HIGH_REG (*(reg8 *) `$INSTANCE_NAME`_OffsetMixer_MSB__F0_REG)

#endif
//[] END OF FILE
