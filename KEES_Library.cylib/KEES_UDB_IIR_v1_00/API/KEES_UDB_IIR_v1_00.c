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

void `$INSTANCE_NAME`_Start(void)
{
    // write the stagger offset
    `$INSTANCE_NAME`_DEC_CNT = `$Stagger`;
    // enable the count7 functionality
    `$INSTANCE_NAME`_AUX_CTRL |= (1 << 5);
}

/* [] END OF FILE */
