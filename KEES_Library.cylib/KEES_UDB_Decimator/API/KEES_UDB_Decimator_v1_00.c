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

#include "`$INSTANCE_NAME`.h"

void `$INSTANCE_NAME`_Start()
{
	// enable the count 7
	*(( reg8 *) `$INSTANCE_NAME`_Counter7__CONTROL_AUX_CTL_REG) |= (1 << 5);
	// set FIFO 0 in single buffer mode
	*(( reg8 *) `$INSTANCE_NAME`_CIC_Decimator_u0__DP_AUX_CTL_REG) |= (1 << 0);
	// set FIFO 0 in single buffer mode
	*(( reg8 *) `$INSTANCE_NAME`_CIC_Decimator_u1__DP_AUX_CTL_REG) |= (1 << 0);
	// preload the count (decimation) value
	*(( reg8 *) `$INSTANCE_NAME`_Counter7__COUNT_REG) = (uint8)(`$Decimation` - 1);
}

/* [] END OF FILE */
