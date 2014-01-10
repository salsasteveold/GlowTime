/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
* This component implements a transmit only UART operating in 8-None-1 format.
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
    uint8 enableInterrupts;
    
	/* Enable the generation of the irq bit */
	/* Must be done in a critical region since Aux Control is shared */
    /* Enter critical section */
    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_STATUS_AUX_CONTROL_REG |= `$INSTANCE_NAME`_STATUS_INT_EN;
    /* Exit critical section */
    CyExitCriticalSection(enableInterrupts);    
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
* Summary:
*  Initializes and enables the component.
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
	`$INSTANCE_NAME`_Init();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
* Summary:
*  Clears the FIFO.
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
    `$INSTANCE_NAME`_ClearFIFO();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteData
********************************************************************************
*
* Summary:
*  Writes a single byte to the FIFO for transmission.  Doesn't check the current
*  status of the FIFO first.
*
* Parameters:
*  Value to be sent.
*
* Return:
*  None.
* 
*******************************************************************************/
void `$INSTANCE_NAME`_WriteData(uint8 val) `=ReentrantKeil($INSTANCE_NAME . "_WriteData")`
{               
	`$INSTANCE_NAME`_FIFO_REG = val;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadStatus
********************************************************************************
*
* Summary:
*  Returns state in the status register.
*
* Parameters:
*  None.
*
* Return:
*  State of the status register (all bits are transparent)
*   `$INSTANCE_NAME`_NOT_FULL     
*   `$INSTANCE_NAME`_IDLE
*
* Side Effects: 
*  None.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_ReadStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadStatus")`
{
    return (`$INSTANCE_NAME`_STATUS_REG & `$INSTANCE_NAME`_ST_MASK);
}
        
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt source.
*
* Parameters:
*  Byte containing the constant for the selected interrupt sources.
*   `$INSTANCE_NAME`_NOT_FULL    
*   `$INSTANCE_NAME`_IDLE
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetInterruptMode(uint8 interruptSource) `=ReentrantKeil($INSTANCE_NAME . "_SetInterruptMode")`
{
    `$INSTANCE_NAME`_STATUS_MASK_REG = (interruptSource & `$INSTANCE_NAME`_ST_MASK); 
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearFIFO
********************************************************************************
*
* Summary:
*  Clears out the FIFO.  Any data present in the FIFO will be lost.
*
* Parameters:
*  None.
*
* Return:
*  None.
* 
*******************************************************************************/
void `$INSTANCE_NAME`_ClearFIFO(void) `=ReentrantKeil($INSTANCE_NAME . "_ClearFIFO")`
{
    uint8 enableInterrupts;

    /* Enter critical section */
    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_AUX_CONTROL_REG |=  `$INSTANCE_NAME`_FIFO_CLR;
    `$INSTANCE_NAME`_AUX_CONTROL_REG &= ~`$INSTANCE_NAME`_FIFO_CLR;
    /* Exit critical section */
    CyExitCriticalSection(enableInterrupts);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PutString
********************************************************************************
*
* Summary:
*  Transmits a null terminated string.
*
* Parameters:
*  String to be sent.
*
* Return:
*  None.
* 
*******************************************************************************/
void `$INSTANCE_NAME`_PutString(uint8 *string) `=ReentrantKeil($INSTANCE_NAME . "_PutString")`
{
	while (*string)
	{
		while ((`$INSTANCE_NAME`_STATUS_REG & `$INSTANCE_NAME`_NOT_FULL) == 0) ;	/* Wait for space available */
		`$INSTANCE_NAME`_FIFO_REG = *string;
		string++;
	}
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PutArray
********************************************************************************
*
* Summary:
*  Transmits an array of bytes.
*
* Parameters:
*  string: Array of bytes.
*  byteCount: Length of the array.
*
* Return:
*  None.
* 
*******************************************************************************/
void `$INSTANCE_NAME`_PutArray(uint8 *string, uint16 byteCount) `=ReentrantKeil($INSTANCE_NAME . "_PutArray")`
{
	while (byteCount--)
	{
		while ((`$INSTANCE_NAME`_STATUS_REG & `$INSTANCE_NAME`_NOT_FULL) == 0) ;	/* Wait for space available */
		`$INSTANCE_NAME`_FIFO_REG = *string;
		string++;
	}
}
