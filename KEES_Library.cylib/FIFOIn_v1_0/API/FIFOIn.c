/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
* This component provides a convenient interface from programmable hardware to
* the CPU or DMA.  That interface is implemented using the 4-entry FIFO in the
* UDB.
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
*  Enables FIFO capture.
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
    `$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_EN;    
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
    uint8 enableInterrupts;
    
	/* Set the FIFO fill level threshold value */
	/* Only the LSB Bus Status is used, so only that Aux register needs setting */
	/* Must be done in a critical region since Aux Control is shared */
    /* Enter critical section */
    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_LSB_AUX_CONTROL_REG &= ~`$INSTANCE_NAME`_FIFO_LVL;
    `$INSTANCE_NAME`_LSB_AUX_CONTROL_REG |= `$INSTANCE_NAME`_LVL_SETTING;
    /* Exit critical section */
    CyExitCriticalSection(enableInterrupts);    
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
* Summary:
*  Initializes the FIFO setting for the component and enables the FIFO.
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
*  Disables the component and clears the FIFO.
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
    `$INSTANCE_NAME`_CONTROL_REG &= ~`$INSTANCE_NAME`_EN;    
    `$INSTANCE_NAME`_ClearFIFO();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Disable
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
void `$INSTANCE_NAME`_Disable(void) `=ReentrantKeil($INSTANCE_NAME . "_Disable")`
{
    `$INSTANCE_NAME`_CONTROL_REG &= ~`$INSTANCE_NAME`_EN;    
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Read
********************************************************************************
*
* Summary:
*  Returns a single byte/word from the FIFO.
*
* Parameters:
*  void
*
* Return:
*  Byte/word containing the data received.
* 
*******************************************************************************/
#if (`$INSTANCE_NAME`_BUS_WIDTH == 8u)
	uint8 `$INSTANCE_NAME`_Read(void) `=ReentrantKeil($INSTANCE_NAME . "_Read")`
	{               
		return(`$INSTANCE_NAME`_FIFO_REG);
	}
#else
	uint16 `$INSTANCE_NAME`_Read(void) `=ReentrantKeil($INSTANCE_NAME . "_Read")`
	{               
		return(CY_GET_REG16(`$INSTANCE_NAME`_FIFO_PTR));
	}
#endif

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
*  State of the status register
*   `$INSTANCE_NAME`_FIFO_OVERFLOW (Clear on Read)     
*   `$INSTANCE_NAME`_FIFO_NOT_EMPTY   
*
* Side Effects: 
*  Clears the bits of status register that are Clear on Read.
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
*   `$INSTANCE_NAME`_FIFO_OVERFLOW     
*   `$INSTANCE_NAME`_FIFO_NOT_EMPTY   
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
*  This call should be made only when the component is disabled.
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
    `$INSTANCE_NAME`_LSB_AUX_CONTROL_REG |=  `$INSTANCE_NAME`_FIFO_CLR;
    `$INSTANCE_NAME`_LSB_AUX_CONTROL_REG &= ~`$INSTANCE_NAME`_FIFO_CLR;
    #if (`$INSTANCE_NAME`_BUS_WIDTH == 16u)
		`$INSTANCE_NAME`_MSB_AUX_CONTROL_REG |=  `$INSTANCE_NAME`_FIFO_CLR;
		`$INSTANCE_NAME`_MSB_AUX_CONTROL_REG &= ~`$INSTANCE_NAME`_FIFO_CLR;
	#endif	
    /* Exit critical section */
    CyExitCriticalSection(enableInterrupts);
}
