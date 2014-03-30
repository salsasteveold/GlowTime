/*******************************************************************************
* File Name: PB.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_PB_H)
#define CY_ISR_PB_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void PB_Start(void);
void PB_StartEx(cyisraddress address);
void PB_Stop(void);

CY_ISR_PROTO(PB_Interrupt);

void PB_SetVector(cyisraddress address);
cyisraddress PB_GetVector(void);

void PB_SetPriority(uint8 priority);
uint8 PB_GetPriority(void);

void PB_Enable(void);
uint8 PB_GetState(void);
void PB_Disable(void);

void PB_SetPending(void);
void PB_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the PB ISR. */
#define PB_INTC_VECTOR            ((reg32 *) PB__INTC_VECT)

/* Address of the PB ISR priority. */
#define PB_INTC_PRIOR             ((reg32 *) PB__INTC_PRIOR_REG)

/* Priority of the PB interrupt. */
#define PB_INTC_PRIOR_NUMBER      PB__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable PB interrupt. */
#define PB_INTC_SET_EN            ((reg32 *) PB__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the PB interrupt. */
#define PB_INTC_CLR_EN            ((reg32 *) PB__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the PB interrupt state to pending. */
#define PB_INTC_SET_PD            ((reg32 *) PB__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the PB interrupt. */
#define PB_INTC_CLR_PD            ((reg32 *) PB__INTC_CLR_PD_REG)



#endif /* CY_ISR_PB_H */


/* [] END OF FILE */
