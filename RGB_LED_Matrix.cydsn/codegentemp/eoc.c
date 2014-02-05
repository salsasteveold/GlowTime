/*******************************************************************************
* File Name: eoc.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <eoc.h>

#if !defined(eoc__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START eoc_intc` */

/* `#END` */

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: eoc_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void eoc_Start(void)
{
    /* For all we know the interrupt is active. */
    eoc_Disable();

    /* Set the ISR to point to the eoc Interrupt. */
    eoc_SetVector(&eoc_Interrupt);

    /* Set the priority. */
    eoc_SetPriority((uint8)eoc_INTC_PRIOR_NUMBER);

    /* Enable it. */
    eoc_Enable();
}


/*******************************************************************************
* Function Name: eoc_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void eoc_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    eoc_Disable();

    /* Set the ISR to point to the eoc Interrupt. */
    eoc_SetVector(address);

    /* Set the priority. */
    eoc_SetPriority((uint8)eoc_INTC_PRIOR_NUMBER);

    /* Enable it. */
    eoc_Enable();
}


/*******************************************************************************
* Function Name: eoc_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
void eoc_Stop(void)
{
    /* Disable this interrupt. */
    eoc_Disable();

    /* Set the ISR to point to the passive one. */
    eoc_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: eoc_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for eoc.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(eoc_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START eoc_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: eoc_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling eoc_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use eoc_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void eoc_SetVector(cyisraddress address)
{
    CyRamVectors[CYINT_IRQ_BASE + eoc__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: eoc_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress eoc_GetVector(void)
{
    return CyRamVectors[CYINT_IRQ_BASE + eoc__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: eoc_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling eoc_Start
*   or eoc_StartEx will override any effect this method would 
*   have had. This method should only be called after eoc_Start or 
*   eoc_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 3, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void eoc_SetPriority(uint8 priority)
{
	uint8 interruptState;
    uint32 priorityOffset = ((eoc__INTC_NUMBER % 4u) * 8u) + 6u;
    
	interruptState = CyEnterCriticalSection();
    *eoc_INTC_PRIOR = (*eoc_INTC_PRIOR & (uint32)(~eoc__INTC_PRIOR_MASK)) |
                                    ((uint32)priority << priorityOffset);
	CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: eoc_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 3, 0 being the highest.
*
*******************************************************************************/
uint8 eoc_GetPriority(void)
{
    uint32 priority;
	uint32 priorityOffset = ((eoc__INTC_NUMBER % 4u) * 8u) + 6u;

    priority = (*eoc_INTC_PRIOR & eoc__INTC_PRIOR_MASK) >> priorityOffset;

    return (uint8)priority;
}


/*******************************************************************************
* Function Name: eoc_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void eoc_Enable(void)
{
    /* Enable the general interrupt. */
    *eoc_INTC_SET_EN = eoc__INTC_MASK;
}


/*******************************************************************************
* Function Name: eoc_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 eoc_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*eoc_INTC_SET_EN & (uint32)eoc__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: eoc_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void eoc_Disable(void)
{
    /* Disable the general interrupt. */
    *eoc_INTC_CLR_EN = eoc__INTC_MASK;
}


/*******************************************************************************
* Function Name: eoc_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void eoc_SetPending(void)
{
    *eoc_INTC_SET_PD = eoc__INTC_MASK;
}


/*******************************************************************************
* Function Name: eoc_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void eoc_ClearPending(void)
{
    *eoc_INTC_CLR_PD = eoc__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
