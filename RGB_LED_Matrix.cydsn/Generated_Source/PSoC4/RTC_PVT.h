/*******************************************************************************
* File Name: .h
* Version 1.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in I2C mode.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_RTC_H)
#define CY_SCB_PVT_RTC_H

#include "RTC.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define RTC_SetI2CExtClkInterruptMode(interruptMask) RTC_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define RTC_ClearI2CExtClkInterruptSource(interruptMask) RTC_CLEAR_INTR_I2C_EC(interruptMask)
#define RTC_GetI2CExtClkInterruptSource()                (RTC_INTR_I2C_EC_REG)
#define RTC_GetI2CExtClkInterruptMode()                  (RTC_INTR_I2C_EC_MASK_REG)
#define RTC_GetI2CExtClkInterruptSourceMasked()          (RTC_INTR_I2C_EC_MASKED_REG)

/* APIs to service INTR_SPI_EC register */
#define RTC_SetSpiExtClkInterruptMode(interruptMask) RTC_WRITE_INTR_SPI_EC_MASK(interruptMask)
#define RTC_ClearSpiExtClkInterruptSource(interruptMask) RTC_CLEAR_INTR_SPI_EC(interruptMask)
#define RTC_GetExtSpiClkInterruptSource()                 (RTC_INTR_SPI_EC_REG)
#define RTC_GetExtSpiClkInterruptMode()                   (RTC_INTR_SPI_EC_MASK_REG)
#define RTC_GetExtSpiClkInterruptSourceMasked()           (RTC_INTR_SPI_EC_MASKED_REG)

#if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void RTC_SetPins(uint32 mode, uint32 subMode, uint32 uartTxRx);
#endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */

void RTC_DisableTxPinsInputBuffer(void);
void RTC_EnableTxPinsInputBuffer(void);


/**********************************
*     Vars with External Linkage
**********************************/

extern cyisraddress RTC_customIntrHandler;
extern RTC_BACKUP_STRUCT RTC_backup;

#if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common config vars */
    extern uint8 RTC_scbMode;
    extern uint8 RTC_scbEnableWake;
    extern uint8 RTC_scbEnableIntr;

    /* I2C config vars */
    extern uint8 RTC_mode;
    extern uint8 RTC_acceptAddr;

    /* SPI/UART config vars */
    extern volatile uint8 * RTC_rxBuffer;
    extern uint8   RTC_rxDataBits;
    extern uint32  RTC_rxBufferSize;

    extern volatile uint8 * RTC_txBuffer;
    extern uint8   RTC_txDataBits;
    extern uint32  RTC_txBufferSize;

    /* EZI2C config vars */
    extern uint8 RTC_numberOfAddr;
    extern uint8 RTC_subAddrSize;
#endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */

#endif /* (CY_SCB_PVT_RTC_H) */


/* [] END OF FILE */
