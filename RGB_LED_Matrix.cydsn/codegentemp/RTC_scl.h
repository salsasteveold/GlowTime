/*******************************************************************************
* File Name: RTC_scl.h  
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

#if !defined(CY_PINS_RTC_scl_H) /* Pins RTC_scl_H */
#define CY_PINS_RTC_scl_H

#include "cytypes.h"
#include "cyfitter.h"
#include "RTC_scl_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    RTC_scl_Write(uint8 value) ;
void    RTC_scl_SetDriveMode(uint8 mode) ;
uint8   RTC_scl_ReadDataReg(void) ;
uint8   RTC_scl_Read(void) ;
uint8   RTC_scl_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RTC_scl_DRIVE_MODE_BITS        (3)
#define RTC_scl_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - RTC_scl_DRIVE_MODE_BITS))
#define RTC_scl_DRIVE_MODE_SHIFT       (0x00u)
#define RTC_scl_DRIVE_MODE_MASK        (0x07u << RTC_scl_DRIVE_MODE_SHIFT)

#define RTC_scl_DM_ALG_HIZ         (0x00u << RTC_scl_DRIVE_MODE_SHIFT)
#define RTC_scl_DM_DIG_HIZ         (0x01u << RTC_scl_DRIVE_MODE_SHIFT)
#define RTC_scl_DM_RES_UP          (0x02u << RTC_scl_DRIVE_MODE_SHIFT)
#define RTC_scl_DM_RES_DWN         (0x03u << RTC_scl_DRIVE_MODE_SHIFT)
#define RTC_scl_DM_OD_LO           (0x04u << RTC_scl_DRIVE_MODE_SHIFT)
#define RTC_scl_DM_OD_HI           (0x05u << RTC_scl_DRIVE_MODE_SHIFT)
#define RTC_scl_DM_STRONG          (0x06u << RTC_scl_DRIVE_MODE_SHIFT)
#define RTC_scl_DM_RES_UPDWN       (0x07u << RTC_scl_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define RTC_scl_MASK               RTC_scl__MASK
#define RTC_scl_SHIFT              RTC_scl__SHIFT
#define RTC_scl_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RTC_scl_PS                     (* (reg32 *) RTC_scl__PS)
/* Port Configuration */
#define RTC_scl_PC                     (* (reg32 *) RTC_scl__PC)
/* Data Register */
#define RTC_scl_DR                     (* (reg32 *) RTC_scl__DR)
/* Input Buffer Disable Override */
#define RTC_scl_INP_DIS                (* (reg32 *) RTC_scl__PC2)


#if defined(RTC_scl__INTSTAT)  /* Interrupt Registers */

    #define RTC_scl_INTSTAT                (* (reg32 *) RTC_scl__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins RTC_scl_H */


/* [] END OF FILE */
