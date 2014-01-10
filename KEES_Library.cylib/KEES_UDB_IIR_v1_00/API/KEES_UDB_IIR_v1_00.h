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

#ifndef `$INSTANCE_NAME`_UDB_IIR
#define `$INSTANCE_NAME`_UDB_IIR

#include <device.h>

// filter output
//#define `$INSTANCE_NAME`_FILTER_LSB_REG  (*(reg8 *) `$INSTANCE_NAME`_UDB_IIR_u0__A0_REG)
#define `$INSTANCE_NAME`_FILTER_REG  (*(reg8 *) `$INSTANCE_NAME`_UDB_IIR_u0__F0_REG)
#define `$INSTANCE_NAME`_FILTER_PTR  ( (reg8 *) `$INSTANCE_NAME`_UDB_IIR_u0__F0_REG)
#define `$INSTANCE_NAME`_AUX_CTRL (*(reg8 *) `$INSTANCE_NAME`_Counter7Name__CONTROL_AUX_CTL_REG)
#define `$INSTANCE_NAME`_DEC_CNT (*(reg8 *) `$INSTANCE_NAME`_Counter7Name__COUNT_REG)

void `$INSTANCE_NAME`_Start(void);

#endif
//[] END OF FILE
