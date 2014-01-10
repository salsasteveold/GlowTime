/*******************************************************************************
* File Name: Pin4_0.h  
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

#if !defined(CY_PINS_Pin4_0_H) /* Pins Pin4_0_H */
#define CY_PINS_Pin4_0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin4_0_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin4_0_Write(uint8 value) ;
void    Pin4_0_SetDriveMode(uint8 mode) ;
uint8   Pin4_0_ReadDataReg(void) ;
uint8   Pin4_0_Read(void) ;
uint8   Pin4_0_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin4_0_DRIVE_MODE_BITS        (3)
#define Pin4_0_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin4_0_DRIVE_MODE_BITS))
#define Pin4_0_DRIVE_MODE_SHIFT       (0x00u)
#define Pin4_0_DRIVE_MODE_MASK        (0x07u << Pin4_0_DRIVE_MODE_SHIFT)

#define Pin4_0_DM_ALG_HIZ         (0x00u << Pin4_0_DRIVE_MODE_SHIFT)
#define Pin4_0_DM_DIG_HIZ         (0x01u << Pin4_0_DRIVE_MODE_SHIFT)
#define Pin4_0_DM_RES_UP          (0x02u << Pin4_0_DRIVE_MODE_SHIFT)
#define Pin4_0_DM_RES_DWN         (0x03u << Pin4_0_DRIVE_MODE_SHIFT)
#define Pin4_0_DM_OD_LO           (0x04u << Pin4_0_DRIVE_MODE_SHIFT)
#define Pin4_0_DM_OD_HI           (0x05u << Pin4_0_DRIVE_MODE_SHIFT)
#define Pin4_0_DM_STRONG          (0x06u << Pin4_0_DRIVE_MODE_SHIFT)
#define Pin4_0_DM_RES_UPDWN       (0x07u << Pin4_0_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Pin4_0_MASK               Pin4_0__MASK
#define Pin4_0_SHIFT              Pin4_0__SHIFT
#define Pin4_0_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin4_0_PS                     (* (reg32 *) Pin4_0__PS)
/* Port Configuration */
#define Pin4_0_PC                     (* (reg32 *) Pin4_0__PC)
/* Data Register */
#define Pin4_0_DR                     (* (reg32 *) Pin4_0__DR)
/* Input Buffer Disable Override */
#define Pin4_0_INP_DIS                (* (reg32 *) Pin4_0__PC2)


#if defined(Pin4_0__INTSTAT)  /* Interrupt Registers */

    #define Pin4_0_INTSTAT                (* (reg32 *) Pin4_0__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Pin4_0_H */


/* [] END OF FILE */
