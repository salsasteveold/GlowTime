/*******************************************************************************
* File Name: RTC_I2C.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "RTC_PVT.h"
#include "RTC_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 RTC_state;  /* Current state of I2C FSM */


#if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Config Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const RTC_I2C_INIT_STRUCT RTC_configI2C =
    {
        RTC_I2C_MODE,
        RTC_I2C_OVS_FACTOR_LOW,
        RTC_I2C_OVS_FACTOR_HIGH,
        RTC_I2C_MEDIAN_FILTER_ENABLE,
        RTC_I2C_SLAVE_ADDRESS,
        RTC_I2C_SLAVE_ADDRESS_MASK,
        RTC_I2C_ACCEPT_ADDRESS,
        RTC_I2C_WAKE_ENABLE
    };

    /*******************************************************************************
    * Function Name: RTC_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for I2C operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void RTC_I2CInit(const RTC_I2C_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due bad fucntion parameter */
        }
        else
        {
            /* Configure pins */
            RTC_SetPins(RTC_SCB_MODE_I2C, RTC_DUMMY_PARAM,
                                                                    RTC_DUMMY_PARAM);

            /* Store internal configuration */
            RTC_scbMode       = (uint8) RTC_SCB_MODE_I2C;
            RTC_scbEnableWake = (uint8) config->enableWake;
            RTC_scbEnableIntr = (uint8) RTC_SCB_IRQ_INTERNAL;

            RTC_mode          = (uint8) config->mode;
            RTC_acceptAddr    = (uint8) config->acceptAddr;

            /* Configure I2C interface */
            RTC_CTRL_REG     = RTC_GET_CTRL_ADDR_ACCEPT(config->acceptAddr) |
                                            RTC_GET_CTRL_EC_AM_MODE (config->enableWake);

            RTC_I2C_CTRL_REG = RTC_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                                            RTC_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)  |
                                            RTC_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode)           |
                                            RTC_I2C_CTRL;

            /* Adjust SDA filter settigns */
            RTC_SET_I2C_CFG_SDA_FILT_TRIM(RTC_EC_AM_I2C_CFG_SDA_FILT_TRIM);


            /* Configure RX direction */
            RTC_RX_CTRL_REG      = RTC_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                RTC_I2C_RX_CTRL;
            RTC_RX_FIFO_CTRL_REG = RTC_CLEAR_REG;

            /* Set default address and mask */
            RTC_RX_MATCH_REG    = ((RTC_I2C_SLAVE) ?
                                                (RTC_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 RTC_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (RTC_CLEAR_REG));


            /* Configure TX direction */
            RTC_TX_CTRL_REG      = RTC_I2C_TX_CTRL;
            RTC_TX_FIFO_CTRL_REG = RTC_CLEAR_REG;

            /* Configure interrupt with I2C handler */
            RTC_SCB_IRQ_Disable();
            RTC_SCB_IRQ_SetVector(&RTC_I2C_ISR);
            RTC_SCB_IRQ_SetPriority((uint8)RTC_SCB_IRQ_INTC_PRIOR_NUMBER);

            
            /* Configure interrupt sources */
            RTC_INTR_I2C_EC_MASK_REG = RTC_NO_INTR_SOURCES;
            RTC_INTR_SPI_EC_MASK_REG = RTC_NO_INTR_SOURCES;
            RTC_INTR_RX_MASK_REG     = RTC_NO_INTR_SOURCES;
            RTC_INTR_TX_MASK_REG     = RTC_NO_INTR_SOURCES;

            RTC_INTR_SLAVE_MASK_REG  = ((RTC_I2C_SLAVE) ?
                                                     (RTC_I2C_INTR_SLAVE_MASK) :
                                                     (RTC_CLEAR_REG));

            RTC_INTR_MASTER_MASK_REG = ((RTC_I2C_MASTER) ?
                                                     (RTC_I2C_INTR_MASTER_MASK) :
                                                     (RTC_CLEAR_REG));

            /* Configure global variables */
            RTC_state = RTC_I2C_FSM_IDLE;

            /* Internal slave variable */
            RTC_slStatus        = 0u;
            RTC_slRdBufIndex    = 0u;
            RTC_slWrBufIndex    = 0u;
            RTC_slOverFlowCount = 0u;

            /* Internal master variable */
            RTC_mstrStatus     = 0u;
            RTC_mstrRdBufIndex = 0u;
            RTC_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: RTC_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for I2C operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void RTC_I2CInit(void)
    {
        /* Configure I2C interface */
        RTC_CTRL_REG     = RTC_I2C_DEFAULT_CTRL;
        RTC_I2C_CTRL_REG = RTC_I2C_DEFAULT_I2C_CTRL;

        /* Adjust SDA filter settigns */
        RTC_SET_I2C_CFG_SDA_FILT_TRIM(RTC_EC_AM_I2C_CFG_SDA_FILT_TRIM);

        /* Configure RX direction */
        RTC_RX_CTRL_REG      = RTC_I2C_DEFAULT_RX_CTRL;
        RTC_RX_FIFO_CTRL_REG = RTC_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        RTC_RX_MATCH_REG     = RTC_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        RTC_TX_CTRL_REG      = RTC_I2C_DEFAULT_TX_CTRL;
        RTC_TX_FIFO_CTRL_REG = RTC_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler */
        RTC_SCB_IRQ_Disable();
        RTC_SCB_IRQ_SetVector(&RTC_I2C_ISR);
        RTC_SCB_IRQ_SetPriority((uint8)RTC_SCB_IRQ_INTC_PRIOR_NUMBER);
        
        /* Configure interrupt sources */
        RTC_INTR_I2C_EC_MASK_REG = RTC_I2C_DEFAULT_INTR_I2C_EC_MASK;
        RTC_INTR_SPI_EC_MASK_REG = RTC_I2C_DEFAULT_INTR_SPI_EC_MASK;
        RTC_INTR_SLAVE_MASK_REG  = RTC_I2C_DEFAULT_INTR_SLAVE_MASK;
        RTC_INTR_MASTER_MASK_REG = RTC_I2C_DEFAULT_INTR_MASTER_MASK;
        RTC_INTR_RX_MASK_REG     = RTC_I2C_DEFAULT_INTR_RX_MASK;
        RTC_INTR_TX_MASK_REG     = RTC_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        RTC_state = RTC_I2C_FSM_IDLE;

        #if(RTC_I2C_SLAVE)
            /* Internal slave variable */
            RTC_slStatus        = 0u;
            RTC_slRdBufIndex    = 0u;
            RTC_slWrBufIndex    = 0u;
            RTC_slOverFlowCount = 0u;
        #endif /* (RTC_I2C_SLAVE) */

        #if(RTC_I2C_MASTER)
        /* Internal master variable */
            RTC_mstrStatus     = 0u;
            RTC_mstrRdBufIndex = 0u;
            RTC_mstrWrBufIndex = 0u;
        #endif /* (RTC_I2C_MASTER) */
    }
#endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: RTC_I2CStop
********************************************************************************
*
* Summary:
*  Initializes I2C registers with initial values provided from customizer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*
*
*******************************************************************************/
void RTC_I2CStop(void)
{
    RTC_state = RTC_I2C_FSM_IDLE;
}


#if(RTC_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: RTC_I2CSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Wakeup disabled: does nothing.
    *  Wakeup  enabled: clears SCB_backup.enableState and enables
    *  SCB_INTR_I2C_EC_WAKE_UP interrupt used for wakeup. This interrupt source
    *  tracks in active mode therefore it does not require to be cleared.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void RTC_I2CSaveConfig(void)
    {
        /* Enable interrupt to wakeup the device */
        RTC_SetI2CExtClkInterruptMode(RTC_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: RTC_I2CRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Does nothing.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void RTC_I2CRestoreConfig(void)
    {
        /* Does nothing: as wake is masked-off in the interrupt */
    }
#endif /* (RTC_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
