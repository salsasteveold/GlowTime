/*******************************************************************************
* File Name: P0_6_OE.h  
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

#if !defined(CY_PINS_P0_6_OE_H) /* Pins P0_6_OE_H */
#define CY_PINS_P0_6_OE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "P0_6_OE_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    P0_6_OE_Write(uint8 value) ;
void    P0_6_OE_SetDriveMode(uint8 mode) ;
uint8   P0_6_OE_ReadDataReg(void) ;
uint8   P0_6_OE_Read(void) ;
uint8   P0_6_OE_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define P0_6_OE_DRIVE_MODE_BITS        (3)
#define P0_6_OE_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - P0_6_OE_DRIVE_MODE_BITS))
#define P0_6_OE_DRIVE_MODE_SHIFT       (0x00u)
#define P0_6_OE_DRIVE_MODE_MASK        (0x07u << P0_6_OE_DRIVE_MODE_SHIFT)

#define P0_6_OE_DM_ALG_HIZ         (0x00u << P0_6_OE_DRIVE_MODE_SHIFT)
#define P0_6_OE_DM_DIG_HIZ         (0x01u << P0_6_OE_DRIVE_MODE_SHIFT)
#define P0_6_OE_DM_RES_UP          (0x02u << P0_6_OE_DRIVE_MODE_SHIFT)
#define P0_6_OE_DM_RES_DWN         (0x03u << P0_6_OE_DRIVE_MODE_SHIFT)
#define P0_6_OE_DM_OD_LO           (0x04u << P0_6_OE_DRIVE_MODE_SHIFT)
#define P0_6_OE_DM_OD_HI           (0x05u << P0_6_OE_DRIVE_MODE_SHIFT)
#define P0_6_OE_DM_STRONG          (0x06u << P0_6_OE_DRIVE_MODE_SHIFT)
#define P0_6_OE_DM_RES_UPDWN       (0x07u << P0_6_OE_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define P0_6_OE_MASK               P0_6_OE__MASK
#define P0_6_OE_SHIFT              P0_6_OE__SHIFT
#define P0_6_OE_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P0_6_OE_PS                     (* (reg32 *) P0_6_OE__PS)
/* Port Configuration */
#define P0_6_OE_PC                     (* (reg32 *) P0_6_OE__PC)
/* Data Register */
#define P0_6_OE_DR                     (* (reg32 *) P0_6_OE__DR)
/* Input Buffer Disable Override */
#define P0_6_OE_INP_DIS                (* (reg32 *) P0_6_OE__PC2)


#if defined(P0_6_OE__INTSTAT)  /* Interrupt Registers */

    #define P0_6_OE_INTSTAT                (* (reg32 *) P0_6_OE__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins P0_6_OE_H */


/* [] END OF FILE */
