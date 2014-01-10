/*******************************************************************************
* File Name: Pin1_7.h  
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

#if !defined(CY_PINS_Pin1_7_H) /* Pins Pin1_7_H */
#define CY_PINS_Pin1_7_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin1_7_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin1_7_Write(uint8 value) ;
void    Pin1_7_SetDriveMode(uint8 mode) ;
uint8   Pin1_7_ReadDataReg(void) ;
uint8   Pin1_7_Read(void) ;
uint8   Pin1_7_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin1_7_DRIVE_MODE_BITS        (3)
#define Pin1_7_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin1_7_DRIVE_MODE_BITS))
#define Pin1_7_DRIVE_MODE_SHIFT       (0x00u)
#define Pin1_7_DRIVE_MODE_MASK        (0x07u << Pin1_7_DRIVE_MODE_SHIFT)

#define Pin1_7_DM_ALG_HIZ         (0x00u << Pin1_7_DRIVE_MODE_SHIFT)
#define Pin1_7_DM_DIG_HIZ         (0x01u << Pin1_7_DRIVE_MODE_SHIFT)
#define Pin1_7_DM_RES_UP          (0x02u << Pin1_7_DRIVE_MODE_SHIFT)
#define Pin1_7_DM_RES_DWN         (0x03u << Pin1_7_DRIVE_MODE_SHIFT)
#define Pin1_7_DM_OD_LO           (0x04u << Pin1_7_DRIVE_MODE_SHIFT)
#define Pin1_7_DM_OD_HI           (0x05u << Pin1_7_DRIVE_MODE_SHIFT)
#define Pin1_7_DM_STRONG          (0x06u << Pin1_7_DRIVE_MODE_SHIFT)
#define Pin1_7_DM_RES_UPDWN       (0x07u << Pin1_7_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Pin1_7_MASK               Pin1_7__MASK
#define Pin1_7_SHIFT              Pin1_7__SHIFT
#define Pin1_7_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin1_7_PS                     (* (reg32 *) Pin1_7__PS)
/* Port Configuration */
#define Pin1_7_PC                     (* (reg32 *) Pin1_7__PC)
/* Data Register */
#define Pin1_7_DR                     (* (reg32 *) Pin1_7__DR)
/* Input Buffer Disable Override */
#define Pin1_7_INP_DIS                (* (reg32 *) Pin1_7__PC2)


#if defined(Pin1_7__INTSTAT)  /* Interrupt Registers */

    #define Pin1_7_INTSTAT                (* (reg32 *) Pin1_7__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Pin1_7_H */


/* [] END OF FILE */
