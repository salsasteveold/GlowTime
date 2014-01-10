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
	// initialize the D) register
	(*(reg8 *) `$INSTANCE_NAME`_Integrator16_u0__D0_REG) = (uint8) (`$IntegrationConstant` & 0x00FF);
	(*(reg8 *) `$INSTANCE_NAME`_Integrator16_u1__D0_REG) = (uint8) ((`$IntegrationConstant` >> 8) & 0x00FF);
	// initialize the integrator to "0" ouput (50% density)
	(*(reg8 *) `$INSTANCE_NAME`_Integrator16_u0__A1_REG) = (uint8) (0x7FFF & 0x00FF);
	(*(reg8 *) `$INSTANCE_NAME`_Integrator16_u1__A1_REG) = (uint8) ((0x7FFF >> 8) & 0x00FF);

}

/* [] END OF FILE */
