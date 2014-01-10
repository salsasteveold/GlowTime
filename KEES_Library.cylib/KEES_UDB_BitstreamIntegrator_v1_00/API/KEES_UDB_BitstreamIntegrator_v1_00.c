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
	/* Enable the Count7 Start bit */
	`$INSTANCE_NAME`_AUX_CTL |= (1 << 5);

}

/* [] END OF FILE */
