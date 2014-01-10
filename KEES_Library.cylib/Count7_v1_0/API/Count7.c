/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
* This component provides access to the hardware primitive 7-bit down counter
* which is referred to in the hardware documentation as a "count7".  This
* hardware primitive uses a Control Register and portions of a Status Register
* (depends on settings for RoutedEnable and RoutedLoad) to implement a 7-bit
* down counter with programmable period value.
*
********************************************************************************
* Copyright (2010), Cypress Semiconductor Corporation.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is 
* protected by and subject to worldwide patent protection (United States and 
* foreign), United States copyright laws and international treaty provisions. 
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable 
* license to copy, use, modify, create derivative works of, and compile the 
* Cypress Source Code and derivative works for the sole purpose of creating 
* custom software in support of licensee product to be used only in conjunction 
* with a Cypress integrated circuit as specified in the applicable agreement. 
* Any reproduction, modification, translation, compilation, or representation of 
* this software except as specified above is prohibited without the express 
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH 
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the 
* materials described herein. Cypress does not assume any liability arising out 
* of the application or use of any product or circuit described herein. Cypress 
* does not authorize its products for use as critical components in life-support 
* systems where a malfunction or failure may reasonably be expected to result in 
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of 
* such use and in doing so indemnifies Cypress against all charges. Use may be 
* limited by and subject to the applicable Cypress software license agreement. 
*******************************************************************************/

#include "cytypes.h"
#include "`$INSTANCE_NAME`.h"

uint8 `$INSTANCE_NAME`_initVar = 0u;

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables the Count7.  The Count7 hardware has a bit in the Aux Control
*  register for a software enable.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{  
    uint8 enableInterrupts;
    
	/* Must be done in a critical region since Aux Control is shared */
    /* Enter critical section */
    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_AUX_CONTROL_REG |= `$INSTANCE_NAME`_CNT_START;
    /* Exit critical section */
    CyExitCriticalSection(enableInterrupts);    
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
	/* Write the default Period value.  This is done at startup time, but */
	/* rewrite here so that it can be reinitialized by software if desired. */
    `$INSTANCE_NAME`_PERIOD_REG = `$INSTANCE_NAME`_PERIOD;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
* Summary:
*  Initializes and then enables the component.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    if (`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }
      
    `$INSTANCE_NAME`_Enable();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
* Summary:
*  Disables the component.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    `$INSTANCE_NAME`_Disable();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Disable
********************************************************************************
* Summary:
*  Disables the Count7.  The Count7 hardware has a bit in the Aux Control
*  register for a software enable.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_Disable(void) `=ReentrantKeil($INSTANCE_NAME . "_Disable")`
{
    uint8 enableInterrupts;
    
	/* Must be done in a critical region since Aux Control is shared */
    /* Enter critical section */
    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_AUX_CONTROL_REG &= ~`$INSTANCE_NAME`_CNT_START;
    /* Exit critical section */
    CyExitCriticalSection(enableInterrupts);    
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadCounter
********************************************************************************
*
* Summary:
*  Returns the current count value.
*
* Parameters:
*  void
*
* Return:
*  Current count value.
* 
*******************************************************************************/
uint8 `$INSTANCE_NAME`_ReadCounter(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadCounter")`
{               
	return(`$INSTANCE_NAME`_COUNT_REG);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteCounter
********************************************************************************
*
* Summary:
*  Writes the counter to the provided value.
*
* Parameters:
*  Byte containing the value to write to the counter
*
* Return:
*  void
* 
*******************************************************************************/
void `$INSTANCE_NAME`_WriteCounter(uint8 count) `=ReentrantKeil($INSTANCE_NAME . "_WriteCounter")`
{               
	`$INSTANCE_NAME`_COUNT_REG = count;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadPeriod
********************************************************************************
*
* Summary:
*  Returns the period value.  The period is the value stored in the period 
*  register of the Count7 hardware.  The counter will cycle through the values
*  period to 0 for a total number of cycles of (period+1).
*
* Parameters:
*  void
*
* Return:
*  Current period value.
* 
*******************************************************************************/
uint8 `$INSTANCE_NAME`_ReadPeriod(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadPeriod")`
{               
	return(`$INSTANCE_NAME`_PERIOD_REG);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WritePeriod
********************************************************************************
*
* Summary:
*  Write the period value.  The period is the value stored in the period 
*  register of the Count7 hardware.  The counter will cycle through the values
*  period to 0 for a total number of cycles of (period+1).
*
* Parameters:
*  Byte containing the value to write to the period
*
* Return:
*  void
* 
*******************************************************************************/
void `$INSTANCE_NAME`_WritePeriod(uint8 period) `=ReentrantKeil($INSTANCE_NAME . "_WritePeriod")`
{               
	`$INSTANCE_NAME`_PERIOD_REG = period;
}
