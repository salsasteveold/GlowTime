/*******************************************************************************
* File Name: RTC_scl.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "RTC_scl.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        RTC_scl_PC =   (RTC_scl_PC & \
                                (uint32)(~(uint32)(RTC_scl_DRIVE_MODE_IND_MASK << (RTC_scl_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (RTC_scl_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: RTC_scl_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void RTC_scl_Write(uint8 value) 
{
    uint8 drVal = (uint8)(RTC_scl_DR & (uint8)(~RTC_scl_MASK));
    drVal = (drVal | ((uint8)(value << RTC_scl_SHIFT) & RTC_scl_MASK));
    RTC_scl_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: RTC_scl_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void RTC_scl_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(RTC_scl__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: RTC_scl_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro RTC_scl_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 RTC_scl_Read(void) 
{
    return (uint8)((RTC_scl_PS & RTC_scl_MASK) >> RTC_scl_SHIFT);
}


/*******************************************************************************
* Function Name: RTC_scl_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 RTC_scl_ReadDataReg(void) 
{
    return (uint8)((RTC_scl_DR & RTC_scl_MASK) >> RTC_scl_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(RTC_scl_INTSTAT) 

    /*******************************************************************************
    * Function Name: RTC_scl_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 RTC_scl_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(RTC_scl_INTSTAT & RTC_scl_MASK);
		RTC_scl_INTSTAT = maskedStatus;
        return maskedStatus >> RTC_scl_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
