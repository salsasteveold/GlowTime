/*******************************************************************************
* File Name: P1_5_C.h  
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

#if !defined(CY_PINS_P1_5_C_H) /* Pins P1_5_C_H */
#define CY_PINS_P1_5_C_H

#include "cytypes.h"
#include "cyfitter.h"
#include "P1_5_C_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    P1_5_C_Write(uint8 value) ;
void    P1_5_C_SetDriveMode(uint8 mode) ;
uint8   P1_5_C_ReadDataReg(void) ;
uint8   P1_5_C_Read(void) ;
uint8   P1_5_C_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define P1_5_C_DRIVE_MODE_BITS        (3)
#define P1_5_C_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - P1_5_C_DRIVE_MODE_BITS))
#define P1_5_C_DRIVE_MODE_SHIFT       (0x00u)
#define P1_5_C_DRIVE_MODE_MASK        (0x07u << P1_5_C_DRIVE_MODE_SHIFT)

#define P1_5_C_DM_ALG_HIZ         (0x00u << P1_5_C_DRIVE_MODE_SHIFT)
#define P1_5_C_DM_DIG_HIZ         (0x01u << P1_5_C_DRIVE_MODE_SHIFT)
#define P1_5_C_DM_RES_UP          (0x02u << P1_5_C_DRIVE_MODE_SHIFT)
#define P1_5_C_DM_RES_DWN         (0x03u << P1_5_C_DRIVE_MODE_SHIFT)
#define P1_5_C_DM_OD_LO           (0x04u << P1_5_C_DRIVE_MODE_SHIFT)
#define P1_5_C_DM_OD_HI           (0x05u << P1_5_C_DRIVE_MODE_SHIFT)
#define P1_5_C_DM_STRONG          (0x06u << P1_5_C_DRIVE_MODE_SHIFT)
#define P1_5_C_DM_RES_UPDWN       (0x07u << P1_5_C_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define P1_5_C_MASK               P1_5_C__MASK
#define P1_5_C_SHIFT              P1_5_C__SHIFT
#define P1_5_C_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P1_5_C_PS                     (* (reg32 *) P1_5_C__PS)
/* Port Configuration */
#define P1_5_C_PC                     (* (reg32 *) P1_5_C__PC)
/* Data Register */
#define P1_5_C_DR                     (* (reg32 *) P1_5_C__DR)
/* Input Buffer Disable Override */
#define P1_5_C_INP_DIS                (* (reg32 *) P1_5_C__PC2)


#if defined(P1_5_C__INTSTAT)  /* Interrupt Registers */

    #define P1_5_C_INTSTAT                (* (reg32 *) P1_5_C__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins P1_5_C_H */


/* [] END OF FILE */
