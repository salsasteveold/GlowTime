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
	#if `$FIFO_0_AlternateLevelReport` > 0
		`$INSTANCE_NAME`_AUX_CTL_A_REG |= (`$INSTANCE_NAME`_F0_LEVEL_MODE_1 << `$INSTANCE_NAME`_F0_LEVEL_SHIFT);
	#endif
	
	#if `$FIFO_1_AlternateLevelReport` > 0
		`$INSTANCE_NAME`_AUX_CTL_A_REG |= (`$INSTANCE_NAME`_F1_LEVEL_MODE_1 << `$INSTANCE_NAME`_F1_LEVEL_SHIFT);
	#endif
	
	#if `$FIFO_0_SingleBufferMode` > 0
		`$INSTANCE_NAME`_AUX_CTL_A_REG |= (`$INSTANCE_NAME`_F0_SINGLE_BUFFER_ENABLE << `$INSTANCE_NAME`_F0_SINGLE_BUFFER_SHIFT);
	#endif
	
	#if `$FIFO_1_SingleBufferMode` > 0
		`$INSTANCE_NAME`_AUX_CTL_A_REG |= (`$INSTANCE_NAME`_F1_SINGLE_BUFFER_ENABLE << `$INSTANCE_NAME`_F1_SINGLE_BUFFER_SHIFT);
	#endif
	
	return;
}

/* [] END OF FILE */
