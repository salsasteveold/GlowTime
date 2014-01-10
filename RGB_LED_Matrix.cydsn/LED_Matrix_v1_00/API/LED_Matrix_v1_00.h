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
#include <device.h>

// F0 register and pointer definitions
#define `$INSTANCE_NAME`_F0_PTR_0			((reg8 *) `$INSTANCE_NAME`_datapath_0_u0__F0_REG)
#define `$INSTANCE_NAME`_F0_PTR_1			((reg8 *) `$INSTANCE_NAME`_datapath_1_u0__F0_REG)
#define `$INSTANCE_NAME`_F0_PTR_2			((reg8 *) `$INSTANCE_NAME`_datapath_2_u0__F0_REG)

// F1 register and pointer definitions
#define `$INSTANCE_NAME`_F1_PTR_0			((reg8 *) `$INSTANCE_NAME`_datapath_0_u0__F1_REG)
#define `$INSTANCE_NAME`_F1_PTR_1			((reg8 *) `$INSTANCE_NAME`_datapath_1_u0__F1_REG)
#define `$INSTANCE_NAME`_F1_PTR_2			((reg8 *) `$INSTANCE_NAME`_datapath_2_u0__F1_REG)

// F0 registerdefinitions
#define `$INSTANCE_NAME`_F0_REG_0			(*(reg8 *) `$INSTANCE_NAME`_datapath_0_u0__F0_REG)
#define `$INSTANCE_NAME`_F0_REG_1			(*(reg8 *) `$INSTANCE_NAME`_datapath_1_u0__F0_REG)
#define `$INSTANCE_NAME`_F0_REG_2			(*(reg8 *) `$INSTANCE_NAME`_datapath_2_u0__F0_REG)

// F1 register definitions
#define `$INSTANCE_NAME`_F1_REG_0			(*(reg8 *) `$INSTANCE_NAME`_datapath_0_u0__F1_REG)
#define `$INSTANCE_NAME`_F1_REG_1			(*(reg8 *) `$INSTANCE_NAME`_datapath_1_u0__F1_REG)
#define `$INSTANCE_NAME`_F1_REG_2			(*(reg8 *) `$INSTANCE_NAME`_datapath_2_u0__F1_REG)


//// F0 F1 register and pointer definitions
//#define `$INSTANCE_NAME`_F0_F1_PTR		((reg16 *) `$INSTANCE_NAME`_datapath_0_u0__F0_F1_REG)
#define `$INSTANCE_NAME`_F0_F1_REG_0		(*(reg16 *) `$INSTANCE_NAME`_datapath_0_u0__F0_F1_REG)

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
//------------------------------------------------------
#define `$INSTANCE_NAME`_WriteControl(value)		CY_SET_REG8(`$INSTANCE_NAME`_ControlReg_1__CONTROL_REG, value)
#define `$INSTANCE_NAME`_ReadControl(value)			CY_SGET_REG8(`$INSTANCE_NAME`_ControlReg_1__CONTROL_REG)

#define `$INSTANCE_NAME`_WriteF0(value)				CY_SET_REG8(`$INSTANCE_NAME`_F0_PTR, (uint8)value )
#define `$INSTANCE_NAME`_WriteF1(value)				CY_SET_REG8(`$INSTANCE_NAME`_F1_PTR, (uint8)value )


void `$INSTANCE_NAME`_Start();

#endif
//[] END OF FILE
