/*******************************************************************************
* File Name: P2_1_ADC1.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_P2_1_ADC1_H) /* Pins P2_1_ADC1_H */
#define CY_PINS_P2_1_ADC1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "P2_1_ADC1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    P2_1_ADC1_Write(uint8 value) ;
void    P2_1_ADC1_SetDriveMode(uint8 mode) ;
uint8   P2_1_ADC1_ReadDataReg(void) ;
uint8   P2_1_ADC1_Read(void) ;
uint8   P2_1_ADC1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define P2_1_ADC1_DRIVE_MODE_BITS        (3)
#define P2_1_ADC1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - P2_1_ADC1_DRIVE_MODE_BITS))
#define P2_1_ADC1_DRIVE_MODE_SHIFT       (0x00u)
#define P2_1_ADC1_DRIVE_MODE_MASK        (0x07u << P2_1_ADC1_DRIVE_MODE_SHIFT)

#define P2_1_ADC1_DM_ALG_HIZ         (0x00u << P2_1_ADC1_DRIVE_MODE_SHIFT)
#define P2_1_ADC1_DM_DIG_HIZ         (0x01u << P2_1_ADC1_DRIVE_MODE_SHIFT)
#define P2_1_ADC1_DM_RES_UP          (0x02u << P2_1_ADC1_DRIVE_MODE_SHIFT)
#define P2_1_ADC1_DM_RES_DWN         (0x03u << P2_1_ADC1_DRIVE_MODE_SHIFT)
#define P2_1_ADC1_DM_OD_LO           (0x04u << P2_1_ADC1_DRIVE_MODE_SHIFT)
#define P2_1_ADC1_DM_OD_HI           (0x05u << P2_1_ADC1_DRIVE_MODE_SHIFT)
#define P2_1_ADC1_DM_STRONG          (0x06u << P2_1_ADC1_DRIVE_MODE_SHIFT)
#define P2_1_ADC1_DM_RES_UPDWN       (0x07u << P2_1_ADC1_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define P2_1_ADC1_MASK               P2_1_ADC1__MASK
#define P2_1_ADC1_SHIFT              P2_1_ADC1__SHIFT
#define P2_1_ADC1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P2_1_ADC1_PS                     (* (reg32 *) P2_1_ADC1__PS)
/* Port Configuration */
#define P2_1_ADC1_PC                     (* (reg32 *) P2_1_ADC1__PC)
/* Data Register */
#define P2_1_ADC1_DR                     (* (reg32 *) P2_1_ADC1__DR)
/* Input Buffer Disable Override */
#define P2_1_ADC1_INP_DIS                (* (reg32 *) P2_1_ADC1__PC2)


#if defined(P2_1_ADC1__INTSTAT)  /* Interrupt Registers */

    #define P2_1_ADC1_INTSTAT                (* (reg32 *) P2_1_ADC1__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins P2_1_ADC1_H */


/* [] END OF FILE */
