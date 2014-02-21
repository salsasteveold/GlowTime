/*******************************************************************************
* File Name: RTC_sda.h  
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

#if !defined(CY_PINS_RTC_sda_H) /* Pins RTC_sda_H */
#define CY_PINS_RTC_sda_H

#include "cytypes.h"
#include "cyfitter.h"
#include "RTC_sda_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    RTC_sda_Write(uint8 value) ;
void    RTC_sda_SetDriveMode(uint8 mode) ;
uint8   RTC_sda_ReadDataReg(void) ;
uint8   RTC_sda_Read(void) ;
uint8   RTC_sda_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RTC_sda_DRIVE_MODE_BITS        (3)
#define RTC_sda_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - RTC_sda_DRIVE_MODE_BITS))
#define RTC_sda_DRIVE_MODE_SHIFT       (0x00u)
#define RTC_sda_DRIVE_MODE_MASK        (0x07u << RTC_sda_DRIVE_MODE_SHIFT)

#define RTC_sda_DM_ALG_HIZ         (0x00u << RTC_sda_DRIVE_MODE_SHIFT)
#define RTC_sda_DM_DIG_HIZ         (0x01u << RTC_sda_DRIVE_MODE_SHIFT)
#define RTC_sda_DM_RES_UP          (0x02u << RTC_sda_DRIVE_MODE_SHIFT)
#define RTC_sda_DM_RES_DWN         (0x03u << RTC_sda_DRIVE_MODE_SHIFT)
#define RTC_sda_DM_OD_LO           (0x04u << RTC_sda_DRIVE_MODE_SHIFT)
#define RTC_sda_DM_OD_HI           (0x05u << RTC_sda_DRIVE_MODE_SHIFT)
#define RTC_sda_DM_STRONG          (0x06u << RTC_sda_DRIVE_MODE_SHIFT)
#define RTC_sda_DM_RES_UPDWN       (0x07u << RTC_sda_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define RTC_sda_MASK               RTC_sda__MASK
#define RTC_sda_SHIFT              RTC_sda__SHIFT
#define RTC_sda_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RTC_sda_PS                     (* (reg32 *) RTC_sda__PS)
/* Port Configuration */
#define RTC_sda_PC                     (* (reg32 *) RTC_sda__PC)
/* Data Register */
#define RTC_sda_DR                     (* (reg32 *) RTC_sda__DR)
/* Input Buffer Disable Override */
#define RTC_sda_INP_DIS                (* (reg32 *) RTC_sda__PC2)


#if defined(RTC_sda__INTSTAT)  /* Interrupt Registers */

    #define RTC_sda_INTSTAT                (* (reg32 *) RTC_sda__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins RTC_sda_H */


/* [] END OF FILE */
