/* ========================================
 * File Name: `$INSTANCE_NAME`.c  
 * Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
 *
 * Copyright Cypress Semiconductor, 2012
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "cytypes.h"
#include "`$INSTANCE_NAME`.h"

#if `$INSTANCE_NAME`_CPU_MODE

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ComputeIsqrt
********************************************************************************
* Summary:
*  Computes a `$resultWidth`-bit integer square root given a `$regWidth`-bit value.
*
* Parameters:
*  square: The `$regWidth`-bit value.
*
* Return:
*  The resulting `$resultWidth`-bit integer square root.
*  
*******************************************************************************/
uint`$resultWidth` `$INSTANCE_NAME`_ComputeIsqrt(uint`$regWidth` square)
{
	/* Set up FIFOs, start the computation. */
	`$INSTANCE_NAME`_ComputeIsqrtAsync(square);
	
	/* Wait for computation to complete. */
	while (!(CY_GET_REG8(`$INSTANCE_NAME`_STS) & 0x01)){}
	
	/* Read back result, empty FIFOs. */
	return `$INSTANCE_NAME`_ReadIsqrtAsync();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ComputeIsqrtAsync
********************************************************************************
* Summary:
*  Triggers computation of a `$resultWidth`-bit integer square root given a `$regWidth`-bit value.
*
* Parameters:
*  square: The `$regWidth`-bit value.
*
* Return: 
*  void
*  
*******************************************************************************/
void `$INSTANCE_NAME`_ComputeIsqrtAsync(uint`$regWidth` square)
{
	/* Set up FIFOs, start the computation. */
	CY_SET_REG`$dpWidth`(`$INSTANCE_NAME`_F1, square);
	CY_SET_REG8(`$INSTANCE_NAME`_CTL, 0x01);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadIsqrtAsync
********************************************************************************
* Summary:
*  Reads `$resultWidth`-bit integer square root that resulted from a previous call to
*  `$INSTANCE_NAME`_ComputeIsqrtAsync.
*
* Parameters:
*  void
*
* Return: 
*  The resulting `$resultWidth`-bit integer square root.
*  
*******************************************************************************/
uint`$resultWidth` `$INSTANCE_NAME`_ReadIsqrtAsync()
{
	/* Read back result. */
	return CY_GET_REG`$dpWidth`(`$INSTANCE_NAME`_F1);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_AsyncComplete
********************************************************************************
* Summary:
*  Reads the status of the component:
*   0x00: Busy
*   0x01: Calculation complete
*
* Parameters:
*  void
*
* Return: 
*  Returns 0x01 if the component is done processing. Returns 0x00 if busy.
*  
*******************************************************************************/
uint8 `$INSTANCE_NAME`_AsyncComplete()
{
	return CY_GET_REG8(`$INSTANCE_NAME`_STS) & 0x01;
}
#endif

/* [] END OF FILE */
