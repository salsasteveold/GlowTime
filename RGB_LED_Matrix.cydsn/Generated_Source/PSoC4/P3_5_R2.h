/*******************************************************************************
* File Name: P3_5_R2.h  
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

#if !defined(CY_PINS_P3_5_R2_H) /* Pins P3_5_R2_H */
#define CY_PINS_P3_5_R2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "P3_5_R2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    P3_5_R2_Write(uint8 value) ;
void    P3_5_R2_SetDriveMode(uint8 mode) ;
uint8   P3_5_R2_ReadDataReg(void) ;
uint8   P3_5_R2_Read(void) ;
uint8   P3_5_R2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define P3_5_R2_DRIVE_MODE_BITS        (3)
#define P3_5_R2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - P3_5_R2_DRIVE_MODE_BITS))
#define P3_5_R2_DRIVE_MODE_SHIFT       (0x00u)
#define P3_5_R2_DRIVE_MODE_MASK        (0x07u << P3_5_R2_DRIVE_MODE_SHIFT)

#define P3_5_R2_DM_ALG_HIZ         (0x00u << P3_5_R2_DRIVE_MODE_SHIFT)
#define P3_5_R2_DM_DIG_HIZ         (0x01u << P3_5_R2_DRIVE_MODE_SHIFT)
#define P3_5_R2_DM_RES_UP          (0x02u << P3_5_R2_DRIVE_MODE_SHIFT)
#define P3_5_R2_DM_RES_DWN         (0x03u << P3_5_R2_DRIVE_MODE_SHIFT)
#define P3_5_R2_DM_OD_LO           (0x04u << P3_5_R2_DRIVE_MODE_SHIFT)
#define P3_5_R2_DM_OD_HI           (0x05u << P3_5_R2_DRIVE_MODE_SHIFT)
#define P3_5_R2_DM_STRONG          (0x06u << P3_5_R2_DRIVE_MODE_SHIFT)
#define P3_5_R2_DM_RES_UPDWN       (0x07u << P3_5_R2_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define P3_5_R2_MASK               P3_5_R2__MASK
#define P3_5_R2_SHIFT              P3_5_R2__SHIFT
#define P3_5_R2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P3_5_R2_PS                     (* (reg32 *) P3_5_R2__PS)
/* Port Configuration */
#define P3_5_R2_PC                     (* (reg32 *) P3_5_R2__PC)
/* Data Register */
#define P3_5_R2_DR                     (* (reg32 *) P3_5_R2__DR)
/* Input Buffer Disable Override */
#define P3_5_R2_INP_DIS                (* (reg32 *) P3_5_R2__PC2)


#if defined(P3_5_R2__INTSTAT)  /* Interrupt Registers */

    #define P3_5_R2_INTSTAT                (* (reg32 *) P3_5_R2__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins P3_5_R2_H */


/* [] END OF FILE */
