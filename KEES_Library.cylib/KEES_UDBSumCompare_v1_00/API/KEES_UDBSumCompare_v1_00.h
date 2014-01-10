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

#ifndef `$INSTANCE_NAME`_UDBSumCompare
#define `$INSTANCE_NAME`_UDBSumCompare

#include "cytypes.h"
#include "cyfitter.h"

#define `$INSTANCE_NAME`_A0_REG (* (reg8 *) `$INSTANCE_NAME`_SumCompare_u0__A0_REG)
#define `$INSTANCE_NAME`_A1_REG (* (reg8 *) `$INSTANCE_NAME`_SumCompare_u0__A1_REG)
#define `$INSTANCE_NAME`_B0_REG (* (reg8 *) `$INSTANCE_NAME`_SumCompare_u0__D0_REG)
#define `$INSTANCE_NAME`_B1_REG (* (reg8 *) `$INSTANCE_NAME`_SumCompare_u0__D1_REG)
#define `$INSTANCE_NAME`_RSSI_REG (* (reg8 *) `$INSTANCE_NAME`_SumCompare_u0__F0_REG)
#define `$INSTANCE_NAME`_CDLevel_REG (* (reg8 *) `$INSTANCE_NAME`_SumCompare_u0__F1_REG)

#define `$INSTANCE_NAME`_A0_PTR ( (reg8 *) `$INSTANCE_NAME`_SumCompare_u0__A0_REG)
#define `$INSTANCE_NAME`_A1_PTR ( (reg8 *) `$INSTANCE_NAME`_SumCompare_u0__A1_REG)
#define `$INSTANCE_NAME`_B0_PTR ( (reg8 *) `$INSTANCE_NAME`_SumCompare_u0__D0_REG)
#define `$INSTANCE_NAME`_B1_PTR ( (reg8 *) `$INSTANCE_NAME`_SumCompare_u0__D1_REG)
#define `$INSTANCE_NAME`_RSSI_PTR ( (reg8 *) `$INSTANCE_NAME`_SumCompare_u0__F0_REG)
#define `$INSTANCE_NAME`_CDLevel_PTR ( (reg8 *) `$INSTANCE_NAME`_SumCompare_u0__F1_REG)

// Compare = (A1 + B1) < (A0 + B0)

void `$INSTANCE_NAME`_Start();

#endif
//[] END OF FILE
