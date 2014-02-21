/*******************************************************************************
* File Name: RTC_sda.c  
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
#include "RTC_sda.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        RTC_sda_PC =   (RTC_sda_PC & \
                                (uint32)(~(uint32)(RTC_sda_DRIVE_MODE_IND_MASK << (RTC_sda_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (RTC_sda_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: RTC_sda_Write
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
void RTC_sda_Write(uint8 value) 
{
    uint8 drVal = (uint8)(RTC_sda_DR & (uint8)(~RTC_sda_MASK));
    drVal = (drVal | ((uint8)(value << RTC_sda_SHIFT) & RTC_sda_MASK));
    RTC_sda_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: RTC_sda_SetDriveMode
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
void RTC_sda_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(RTC_sda__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: RTC_sda_Read
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
*  Macro RTC_sda_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 RTC_sda_Read(void) 
{
    return (uint8)((RTC_sda_PS & RTC_sda_MASK) >> RTC_sda_SHIFT);
}


/*******************************************************************************
* Function Name: RTC_sda_ReadDataReg
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
uint8 RTC_sda_ReadDataReg(void) 
{
    return (uint8)((RTC_sda_DR & RTC_sda_MASK) >> RTC_sda_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(RTC_sda_INTSTAT) 

    /*******************************************************************************
    * Function Name: RTC_sda_ClearInterrupt
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
    uint8 RTC_sda_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(RTC_sda_INTSTAT & RTC_sda_MASK);
		RTC_sda_INTSTAT = maskedStatus;
        return maskedStatus >> RTC_sda_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
