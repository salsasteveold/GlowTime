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

#if !defined(CY_SCB_I2C_PVT_RTC_H)
#define CY_SCB_I2C_PVT_RTC_H

#include "RTC_I2C.h"


/***************************************
*     Private Global Vars
***************************************/

extern volatile uint8 RTC_state; /* Current state of I2C FSM */

#if(RTC_I2C_SLAVE_CONST)
    extern volatile uint8 RTC_slStatus;          /* Slave Status */

    /* Receive buffer variables */
    extern volatile uint8 * RTC_slWrBufPtr;      /* Pointer to Receive buffer  */
    extern volatile uint32  RTC_slWrBufSize;     /* Slave Receive buffer size  */
    extern volatile uint32  RTC_slWrBufIndex;    /* Slave Receive buffer Index */

    /* Transmit buffer variables */
    extern volatile uint8 * RTC_slRdBufPtr;      /* Pointer to Transmit buffer  */
    extern volatile uint32  RTC_slRdBufSize;     /* Slave Transmit buffer size  */
    extern volatile uint32  RTC_slRdBufIndex;    /* Slave Transmit buffer Index */
    extern volatile uint32  RTC_slRdBufIndexTmp; /* Slave Transmit buffer Index Tmp */
    extern volatile uint8   RTC_slOverFlowCount; /* Slave Transmit Overflow counter */
#endif /* (RTC_I2C_SLAVE_CONST) */

#if(RTC_I2C_MASTER_CONST)
    extern volatile uint16 RTC_mstrStatus;      /* Master Status byte  */
    extern volatile uint8  RTC_mstrControl;     /* Master Control byte */

    /* Receive buffer variables */
    extern volatile uint8 * RTC_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint32  RTC_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint32  RTC_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Transmit buffer variables */
    extern volatile uint8 * RTC_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint32  RTC_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint32  RTC_mstrWrBufIndex; /* Master Write buffer Index      */
    extern volatile uint32  RTC_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */
#endif /* (RTC_I2C_MASTER_CONST) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(RTC_SCB_MODE_I2C_CONST_CFG)
    void RTC_I2CInit(void);
#endif /* (RTC_SCB_MODE_I2C_CONST_CFG) */

void RTC_I2CStop(void);
void RTC_I2CSaveConfig(void);
void RTC_I2CRestoreConfig(void);

#if(RTC_I2C_MASTER_CONST)
    void RTC_I2CReStartGeneration(void);
#endif /* (RTC_I2C_MASTER_CONST) */

#endif /* (CY_SCB_I2C_PVT_RTC_H) */


/* [] END OF FILE */
