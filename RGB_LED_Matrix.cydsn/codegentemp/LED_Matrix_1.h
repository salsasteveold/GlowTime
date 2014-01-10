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

#ifndef LED_Matrix_1_HEADER
#define LED_Matrix_1_HEADER

#include "cytypes.h"
#include "cyfitter.h"
#include <device.h>

// F0 register and pointer definitions
#define LED_Matrix_1_F0_PTR_0			((reg8 *) LED_Matrix_1_datapath_0_u0__F0_REG)
#define LED_Matrix_1_F0_PTR_1			((reg8 *) LED_Matrix_1_datapath_1_u0__F0_REG)
#define LED_Matrix_1_F0_PTR_2			((reg8 *) LED_Matrix_1_datapath_2_u0__F0_REG)

// F1 register and pointer definitions
#define LED_Matrix_1_F1_PTR_0			((reg8 *) LED_Matrix_1_datapath_0_u0__F1_REG)
#define LED_Matrix_1_F1_PTR_1			((reg8 *) LED_Matrix_1_datapath_1_u0__F1_REG)
#define LED_Matrix_1_F1_PTR_2			((reg8 *) LED_Matrix_1_datapath_2_u0__F1_REG)

// F0 registerdefinitions
#define LED_Matrix_1_F0_REG_0			(*(reg8 *) LED_Matrix_1_datapath_0_u0__F0_REG)
#define LED_Matrix_1_F0_REG_1			(*(reg8 *) LED_Matrix_1_datapath_1_u0__F0_REG)
#define LED_Matrix_1_F0_REG_2			(*(reg8 *) LED_Matrix_1_datapath_2_u0__F0_REG)

// F1 register definitions
#define LED_Matrix_1_F1_REG_0			(*(reg8 *) LED_Matrix_1_datapath_0_u0__F1_REG)
#define LED_Matrix_1_F1_REG_1			(*(reg8 *) LED_Matrix_1_datapath_1_u0__F1_REG)
#define LED_Matrix_1_F1_REG_2			(*(reg8 *) LED_Matrix_1_datapath_2_u0__F1_REG)


//// F0 F1 register and pointer definitions
//#define LED_Matrix_1_F0_F1_PTR		((reg16 *) LED_Matrix_1_datapath_0_u0__F0_F1_REG)
#define LED_Matrix_1_F0_F1_REG_0		(*(reg16 *) LED_Matrix_1_datapath_0_u0__F0_F1_REG)

// AUX CTL definitions
//  ----------------- MASKS ----------------------
#define LED_Matrix_1_F1_LEVEL_MASK				(0x08u)
#define LED_Matrix_1_F0_LEVEL_MASK				(0x04u)
#define LED_Matrix_1_F1_SINGLE_BUFFER_MASK		(0x02u)
#define LED_Matrix_1_F0_SINGLE_BUFFER_MASK		(0x01u)

//  ----------------- MODES ----------------------
#define LED_Matrix_1_F1_LEVEL_MODE_0			(0u)
#define LED_Matrix_1_F1_LEVEL_MODE_1			(1u)

#define LED_Matrix_1_F0_LEVEL_MODE_0			(0u)
#define LED_Matrix_1_F0_LEVEL_MODE_1			(1u)

#define LED_Matrix_1_F1_SINGLE_BUFFER_DISABLE	(0u)
#define LED_Matrix_1_F1_SINGLE_BUFFER_ENABLE	(1u)

#define LED_Matrix_1_F0_SINGLE_BUFFER_DISABLE	(0u)
#define LED_Matrix_1_F0_SINGLE_BUFFER_ENABLE	(1u)

// ----------------- SHIFT -----------------------
#define LED_Matrix_1_F1_LEVEL_SHIFT				(3u)
#define LED_Matrix_1_F0_LEVEL_SHIFT				(2u)
#define LED_Matrix_1_F1_SINGLE_BUFFER_SHIFT		(1u)
#define LED_Matrix_1_F0_SINGLE_BUFFER_SHIFT		(0u)
//------------------------------------------------------
#define LED_Matrix_1_WriteControl(value)		CY_SET_REG8(LED_Matrix_1_ControlReg_1__CONTROL_REG, value)
#define LED_Matrix_1_ReadControl(value)			CY_SGET_REG8(LED_Matrix_1_ControlReg_1__CONTROL_REG)

#define LED_Matrix_1_WriteF0(value)				CY_SET_REG8(LED_Matrix_1_F0_PTR, (uint8)value )
#define LED_Matrix_1_WriteF1(value)				CY_SET_REG8(LED_Matrix_1_F1_PTR, (uint8)value )


void LED_Matrix_1_Start();

#endif
//[] END OF FILE
