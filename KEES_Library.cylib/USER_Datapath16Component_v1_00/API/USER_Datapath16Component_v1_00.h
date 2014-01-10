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

#include "cytypes.h"
#include "cyfitter.h"
#include <cydevice.h>

// A0 register and pointer definitions
#define `$INSTANCE_NAME`_A0_PTR			((reg16 *) `$INSTANCE_NAME`_datapath_u0__16BIT_A0_REG)
#define `$INSTANCE_NAME`_A0_REG			(*(reg16 *) `$INSTANCE_NAME`_datapath_u0__16BIT_A0_REG)

// A1 register and pointer definitions
#define `$INSTANCE_NAME`_A1_PTR			((reg16 *) `$INSTANCE_NAME`_datapath_u0__16BIT_A1_REG)
#define `$INSTANCE_NAME`_A1_REG			(*(reg16 *) `$INSTANCE_NAME`_datapath_u0__16BIT_A1_REG)

// D0 register and pointer definitions
#define `$INSTANCE_NAME`_D0_PTR			((reg16 *) `$INSTANCE_NAME`_datapath_u0__16BIT_D0_REG)
#define `$INSTANCE_NAME`_D0_REG			(*(reg16 *) `$INSTANCE_NAME`_datapath_u0__16BIT_D0_REG)

// D1 register and pointer definitions
#define `$INSTANCE_NAME`_D1_PTR			((reg16 *) `$INSTANCE_NAME`_datapath_u0__16BIT_D1_REG)
#define `$INSTANCE_NAME`_D1_REG			(*(reg16 *) `$INSTANCE_NAME`_datapath_u0__16BIT_D1_REG)

// F0 register and pointer definitions
#define `$INSTANCE_NAME`_F0_PTR			((reg16 *) `$INSTANCE_NAME`_datapath_u0__16BIT_F0_REG)
#define `$INSTANCE_NAME`_F0_REG			(*(reg16 *) `$INSTANCE_NAME`_datapath_u0__16BIT_F0_REG)

// F1 register and pointer definitions
#define `$INSTANCE_NAME`_F1_PTR			((reg16 *) `$INSTANCE_NAME`_datapath_u0__16BIT_F1_REG)
#define `$INSTANCE_NAME`_F1_REG			(*(reg16 *) `$INSTANCE_NAME`_datapath_u0__16BIT_F1_REG)

// AUX CTL register and pointer definitions
#define `$INSTANCE_NAME`_AUX_CTL_A_PTR	((reg8 *) `$INSTANCE_NAME`_datapath_u0__DP_AUX_CTL_REG)
#define `$INSTANCE_NAME`_AUX_CTL_A_REG	(*(reg8 *) `$INSTANCE_NAME`_datapath_u0__DP_AUX_CTL_REG)

// AUX CTL register and pointer definitions
#define `$INSTANCE_NAME`_AUX_CTL_B_PTR	((reg8 *) `$INSTANCE_NAME`_datapath_u1__DP_AUX_CTL_REG)
#define `$INSTANCE_NAME`_AUX_CTL_B_REG	(*(reg8 *) `$INSTANCE_NAME`_datapath_u1__DP_AUX_CTL_REG)

// AUX CTL definitions
//  ----------------- MASKS ----------------------
#define `$INSTANCE_NAME`_F1_LEVEL_MASK				(0x08u)
#define `$INSTANCE_NAME`_F0_LEVEL_MASK				(0x04u)
#define `$INSTANCE_NAME`_F1_SINGLE_BUFFER_MASK		(0x02u)
#define `$INSTANCE_NAME`_F0_SINGLE_BUFFER_MASK		(0x01u)

//  ----------------- MODES ----------------------
#define `$INSTANCE_NAME`_F1_LEVEL_MODE_0			(0u)
#define `$INSTANCE_NAME`_F1_LEVEL_MODE_1			(1u)

#define `$INSTANCE_NAME`_F0_LEVEL_MODE_0			(0u)
#define `$INSTANCE_NAME`_F0_LEVEL_MODE_1			(1u)

#define `$INSTANCE_NAME`_F1_SINGLE_BUFFER_DISABLE	(0u)
#define `$INSTANCE_NAME`_F1_SINGLE_BUFFER_ENABLE	(1u)

#define `$INSTANCE_NAME`_F0_SINGLE_BUFFER_DISABLE	(0u)
#define `$INSTANCE_NAME`_F0_SINGLE_BUFFER_ENABLE	(1u)

// ----------------- SHIFT -----------------------
#define `$INSTANCE_NAME`_F1_LEVEL_SHIFT				(3u)
#define `$INSTANCE_NAME`_F0_LEVEL_SHIFT				(2u)
#define `$INSTANCE_NAME`_F1_SINGLE_BUFFER_SHIFT		(1u)
#define `$INSTANCE_NAME`_F0_SINGLE_BUFFER_SHIFT		(0u)

void `$INSTANCE_NAME`_Start();

#endif
//[] END OF FILE
