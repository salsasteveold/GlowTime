/*******************************************************************************
* File Name: ADC_P2_0.h  
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

#if !defined(CY_PINS_ADC_P2_0_H) /* Pins ADC_P2_0_H */
#define CY_PINS_ADC_P2_0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ADC_P2_0_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ADC_P2_0_Write(uint8 value) ;
void    ADC_P2_0_SetDriveMode(uint8 mode) ;
uint8   ADC_P2_0_ReadDataReg(void) ;
uint8   ADC_P2_0_Read(void) ;
uint8   ADC_P2_0_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ADC_P2_0_DRIVE_MODE_BITS        (3)
#define ADC_P2_0_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ADC_P2_0_DRIVE_MODE_BITS))
#define ADC_P2_0_DRIVE_MODE_SHIFT       (0x00u)
#define ADC_P2_0_DRIVE_MODE_MASK        (0x07u << ADC_P2_0_DRIVE_MODE_SHIFT)

#define ADC_P2_0_DM_ALG_HIZ         (0x00u << ADC_P2_0_DRIVE_MODE_SHIFT)
#define ADC_P2_0_DM_DIG_HIZ         (0x01u << ADC_P2_0_DRIVE_MODE_SHIFT)
#define ADC_P2_0_DM_RES_UP          (0x02u << ADC_P2_0_DRIVE_MODE_SHIFT)
#define ADC_P2_0_DM_RES_DWN         (0x03u << ADC_P2_0_DRIVE_MODE_SHIFT)
#define ADC_P2_0_DM_OD_LO           (0x04u << ADC_P2_0_DRIVE_MODE_SHIFT)
#define ADC_P2_0_DM_OD_HI           (0x05u << ADC_P2_0_DRIVE_MODE_SHIFT)
#define ADC_P2_0_DM_STRONG          (0x06u << ADC_P2_0_DRIVE_MODE_SHIFT)
#define ADC_P2_0_DM_RES_UPDWN       (0x07u << ADC_P2_0_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define ADC_P2_0_MASK               ADC_P2_0__MASK
#define ADC_P2_0_SHIFT              ADC_P2_0__SHIFT
#define ADC_P2_0_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ADC_P2_0_PS                     (* (reg32 *) ADC_P2_0__PS)
/* Port Configuration */
#define ADC_P2_0_PC                     (* (reg32 *) ADC_P2_0__PC)
/* Data Register */
#define ADC_P2_0_DR                     (* (reg32 *) ADC_P2_0__DR)
/* Input Buffer Disable Override */
#define ADC_P2_0_INP_DIS                (* (reg32 *) ADC_P2_0__PC2)


#if defined(ADC_P2_0__INTSTAT)  /* Interrupt Registers */

    #define ADC_P2_0_INTSTAT                (* (reg32 *) ADC_P2_0__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins ADC_P2_0_H */


/* [] END OF FILE */
