/*******************************************************************************
* File Name: Pin4_0.c  
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
#include "Pin4_0.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Pin4_0_PC =   (Pin4_0_PC & \
                                (uint32)(~(uint32)(Pin4_0_DRIVE_MODE_IND_MASK << (Pin4_0_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Pin4_0_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Pin4_0_Write
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
void Pin4_0_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Pin4_0_DR & (uint8)(~Pin4_0_MASK));
    drVal = (drVal | ((uint8)(value << Pin4_0_SHIFT) & Pin4_0_MASK));
    Pin4_0_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Pin4_0_SetDriveMode
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
void Pin4_0_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Pin4_0__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Pin4_0_Read
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
*  Macro Pin4_0_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Pin4_0_Read(void) 
{
    return (uint8)((Pin4_0_PS & Pin4_0_MASK) >> Pin4_0_SHIFT);
}


/*******************************************************************************
* Function Name: Pin4_0_ReadDataReg
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
uint8 Pin4_0_ReadDataReg(void) 
{
    return (uint8)((Pin4_0_DR & Pin4_0_MASK) >> Pin4_0_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Pin4_0_INTSTAT) 

    /*******************************************************************************
    * Function Name: Pin4_0_ClearInterrupt
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
    uint8 Pin4_0_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Pin4_0_INTSTAT & Pin4_0_MASK);
		Pin4_0_INTSTAT = maskedStatus;
        return maskedStatus >> Pin4_0_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
