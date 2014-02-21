/*******************************************************************************
* File Name: RTC.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the SCB Component.
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

#if(RTC_SCB_MODE_I2C_INC)
    #include "RTC_I2C_PVT.h"
#endif /* (RTC_SCB_MODE_I2C_INC) */

#if(RTC_SCB_MODE_EZI2C_INC)
    #include "RTC_EZI2C_PVT.h"
#endif /* (RTC_SCB_MODE_EZI2C_INC) */

#if(RTC_SCB_MODE_SPI_INC || RTC_SCB_MODE_UART_INC)
    #include "RTC_SPI_UART_PVT.h"
#endif /* (RTC_SCB_MODE_SPI_INC || RTC_SCB_MODE_UART_INC) */


/**********************************
*    Run Time Configuration Vars
**********************************/

/* Stores internal component configuration for unconfigured mode */
#if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common config vars */
    uint8 RTC_scbMode = RTC_SCB_MODE_UNCONFIG;
    uint8 RTC_scbEnableWake;
    uint8 RTC_scbEnableIntr;

    /* I2C config vars */
    uint8 RTC_mode;
    uint8 RTC_acceptAddr;

    /* SPI/UART config vars */
    volatile uint8 * RTC_rxBuffer;
    uint8  RTC_rxDataBits;
    uint32 RTC_rxBufferSize;

    volatile uint8 * RTC_txBuffer;
    uint8  RTC_txDataBits;
    uint32 RTC_txBufferSize;

    /* EZI2C config vars */
    uint8 RTC_numberOfAddr;
    uint8 RTC_subAddrSize;
#endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */


/**********************************
*     Common SCB Vars
**********************************/

uint8 RTC_initVar = 0u;
cyisraddress RTC_customIntrHandler = NULL;


/***************************************
*    Private Function Prototypes
***************************************/

static void RTC_ScbEnableIntr(void);
static void RTC_ScbModeStop(void);


/*******************************************************************************
* Function Name: RTC_Init
********************************************************************************
*
* Summary:
*  Initializes SCB component to operate in one of selected configurations:
*  I2C, SPI, UART, EZI2C or EZSPI.
*  This function does not do any initialization when configuration is set to
*  Unconfigured SCB.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RTC_Init(void)
{
#if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)
    if(RTC_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        RTC_initVar = 0u; /* Clear init var */
    }
    else
    {
        /* Initialization was done before call */
    }

#elif(RTC_SCB_MODE_I2C_CONST_CFG)
    RTC_I2CInit();

#elif(RTC_SCB_MODE_SPI_CONST_CFG)
    RTC_SpiInit();

#elif(RTC_SCB_MODE_UART_CONST_CFG)
    RTC_UartInit();

#elif(RTC_SCB_MODE_EZI2C_CONST_CFG)
    RTC_EzI2CInit();

#endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: RTC_Enable
********************************************************************************
*
* Summary:
*  Enables SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RTC_Enable(void)
{
#if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)
    if(!RTC_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        /* Enable SCB block, only if already configured */
        RTC_CTRL_REG |= RTC_CTRL_ENABLED;
        
        /* Enable interrupt */
        RTC_ScbEnableIntr();
    }
#else
    RTC_CTRL_REG |= RTC_CTRL_ENABLED; /* Enable SCB block */
    
    RTC_ScbEnableIntr();
#endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: RTC_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call the component is enabled and ready for operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  RTC_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void RTC_Start(void)
{
    if(0u == RTC_initVar)
    {
        RTC_initVar = 1u; /* Component was initialized */
        RTC_Init();       /* Initialize component      */
    }

    RTC_Enable();
}


/*******************************************************************************
* Function Name: RTC_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RTC_Stop(void)
{
#if(RTC_SCB_IRQ_INTERNAL)
    RTC_SCB_IRQ_Disable();     /* Disable interrupt before block */
#endif /* (RTC_SCB_IRQ_INTERNAL) */

    RTC_CTRL_REG &= (uint32) ~RTC_CTRL_ENABLED;  /* Disable SCB block */

#if(RTC_SCB_IRQ_INTERNAL)
    RTC_SCB_IRQ_ClearPending(); /* Clear pending interrupt */
#endif /* (RTC_SCB_IRQ_INTERNAL) */
    
    RTC_ScbModeStop(); /* Calls scbMode specific Stop function */
}


/*******************************************************************************
* Function Name: RTC_SetCustomInterruptHandler
********************************************************************************
*
* Summary:
*  Registers a function to be called by the internal interrupt handler.
*  First the function that is registered is called, then the internal interrupt
*  handler performs any operations such as software buffer management functions
*  before the interrupt returns.  It is user's responsibility to not break the
*  software buffer operations. Only one custom handler is supported, which is
*  the function provided by the most recent call.
*  At initialization time no custom handler is registered.
*
* Parameters:
*  func: Pointer to the function to register.
*        The value NULL indicates to remove the current custom interrupt
*        handler.
*
* Return:
*  None
*
*******************************************************************************/
void RTC_SetCustomInterruptHandler(cyisraddress func)
{
    RTC_customIntrHandler = func; /* Register interrupt handler */
}


/*******************************************************************************
* Function Name: RTC_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables interrupt for specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void RTC_ScbEnableIntr(void)
{
#if(RTC_SCB_IRQ_INTERNAL)
    #if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Enable interrupt source */
        if(0u != RTC_scbEnableIntr)
        {
            RTC_SCB_IRQ_Enable();
        }
    #else
        RTC_SCB_IRQ_Enable();
        
    #endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (RTC_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: RTC_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Calls Stop function for specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void RTC_ScbModeStop(void)
{
#if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)
    if(RTC_SCB_MODE_I2C_RUNTM_CFG)
    {
        RTC_I2CStop();
    }
    else if(RTC_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        RTC_EzI2CStop();
    }
    else
    {
        /* None of modes above */
    }
#elif(RTC_SCB_MODE_I2C_CONST_CFG)
    RTC_I2CStop();

#elif(RTC_SCB_MODE_EZI2C_CONST_CFG)
    RTC_EzI2CStop();

#endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: RTC_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets pins settings accordingly to selected operation mode.
    *  Only available in Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when specific mode of operation
    *  selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Submode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartTxRx:  Direction for UART.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void RTC_SetPins(uint32 mode, uint32 subMode, uint32 uartTxRx)
    {
        uint32 hsiomSel[RTC_SCB_PINS_NUMBER];
        uint32 pinsDm  [RTC_SCB_PINS_NUMBER];
        uint32 i;

        /* Make all unused */
        for(i = 0u; i < RTC_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i] = RTC_HSIOM_DEF_SEL;
            pinsDm[i]   = RTC_PIN_DM_ALG_HIZ;
        }

        /* Choice the Dm and HSIOM */
        if((RTC_SCB_MODE_I2C   == mode) ||
           (RTC_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[RTC_MOSI_SCL_RX_PIN_INDEX] = RTC_HSIOM_I2C_SEL;
            hsiomSel[RTC_MISO_SDA_TX_PIN_INDEX] = RTC_HSIOM_I2C_SEL;

            pinsDm[RTC_MOSI_SCL_RX_PIN_INDEX] = RTC_PIN_DM_OD_LO;
            pinsDm[RTC_MISO_SDA_TX_PIN_INDEX] = RTC_PIN_DM_OD_LO;
        }
        else if(RTC_SCB_MODE_SPI == mode)
        {
            hsiomSel[RTC_MOSI_SCL_RX_PIN_INDEX] = RTC_HSIOM_SPI_SEL;
            hsiomSel[RTC_MISO_SDA_TX_PIN_INDEX] = RTC_HSIOM_SPI_SEL;
            hsiomSel[RTC_SCLK_PIN_INDEX]        = RTC_HSIOM_SPI_SEL;

            if(RTC_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[RTC_MOSI_SCL_RX_PIN_INDEX] = RTC_PIN_DM_DIG_HIZ;
                pinsDm[RTC_MISO_SDA_TX_PIN_INDEX] = RTC_PIN_DM_STRONG;
                pinsDm[RTC_SCLK_PIN_INDEX]        = RTC_PIN_DM_DIG_HIZ;

            #if(RTC_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[RTC_SS0_PIN_INDEX] = RTC_HSIOM_SPI_SEL;
                pinsDm  [RTC_SS0_PIN_INDEX] = RTC_PIN_DM_DIG_HIZ;
            #endif /* (RTC_SS1_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[RTC_MOSI_SCL_RX_PIN_INDEX] = RTC_PIN_DM_STRONG;
                pinsDm[RTC_MISO_SDA_TX_PIN_INDEX] = RTC_PIN_DM_DIG_HIZ;
                pinsDm[RTC_SCLK_PIN_INDEX]        = RTC_PIN_DM_STRONG;

            #if(RTC_SS0_PIN)
                hsiomSel[RTC_SS0_PIN_INDEX] = RTC_HSIOM_SPI_SEL;
                pinsDm  [RTC_SS0_PIN_INDEX] = RTC_PIN_DM_STRONG;
            #endif /* (RTC_SS0_PIN) */

            #if(RTC_SS1_PIN)
                hsiomSel[RTC_SS1_PIN_INDEX] = RTC_HSIOM_SPI_SEL;
                pinsDm  [RTC_SS1_PIN_INDEX] = RTC_PIN_DM_STRONG;
            #endif /* (RTC_SS1_PIN) */

            #if(RTC_SS2_PIN)
                hsiomSel[RTC_SS2_PIN_INDEX] = RTC_HSIOM_SPI_SEL;
                pinsDm  [RTC_SS2_PIN_INDEX] = RTC_PIN_DM_STRONG;
            #endif /* (RTC_SS2_PIN) */

            #if(RTC_SS3_PIN)
                hsiomSel[RTC_SS3_PIN_INDEX] = RTC_HSIOM_SPI_SEL;
                pinsDm  [RTC_SS3_PIN_INDEX] = RTC_PIN_DM_STRONG;
            #endif /* (RTC_SS2_PIN) */
            }
        }
        else /* UART */
        {
            if(RTC_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[RTC_MISO_SDA_TX_PIN_INDEX] = RTC_HSIOM_UART_SEL;
                pinsDm  [RTC_MISO_SDA_TX_PIN_INDEX] = RTC_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if(0u != (RTC_UART_RX & uartTxRx))
                {
                    hsiomSel[RTC_MOSI_SCL_RX_PIN_INDEX] = RTC_HSIOM_UART_SEL;
                    pinsDm  [RTC_MOSI_SCL_RX_PIN_INDEX] = RTC_PIN_DM_DIG_HIZ;
                }

                if(0u != (RTC_UART_TX & uartTxRx))
                {
                    hsiomSel[RTC_MISO_SDA_TX_PIN_INDEX] = RTC_HSIOM_UART_SEL;
                    pinsDm  [RTC_MISO_SDA_TX_PIN_INDEX] = RTC_PIN_DM_STRONG;
                }
            }
        }

        /* Condfigure pins: set HSIOM and DM */
        /* Condfigure pins: DR registers configuration remains unchanged for cyfitter_cfg() */

    #if(RTC_MOSI_SCL_RX_PIN)
        RTC_SET_HSIOM_SEL(RTC_MOSI_SCL_RX_HSIOM_REG,
                                       RTC_MOSI_SCL_RX_HSIOM_MASK,
                                       RTC_MOSI_SCL_RX_HSIOM_POS,
                                       hsiomSel[RTC_MOSI_SCL_RX_PIN_INDEX]);
    #endif /* (RTC_MOSI_SCL_RX_PIN) */

    #if(RTC_MOSI_SCL_RX_WAKE_PIN)
        RTC_SET_HSIOM_SEL(RTC_MOSI_SCL_RX_WAKE_HSIOM_REG,
                                       RTC_MOSI_SCL_RX_WAKE_HSIOM_MASK,
                                       RTC_MOSI_SCL_RX_WAKE_HSIOM_POS,
                                       hsiomSel[RTC_MOSI_SCL_RX_WAKE_PIN_INDEX]);
    #endif /* (RTC_MOSI_SCL_RX_WAKE_PIN) */

    #if(RTC_MISO_SDA_TX_PIN)
        RTC_SET_HSIOM_SEL(RTC_MISO_SDA_TX_HSIOM_REG,
                                       RTC_MISO_SDA_TX_HSIOM_MASK,
                                       RTC_MISO_SDA_TX_HSIOM_POS,
                                       hsiomSel[RTC_MISO_SDA_TX_PIN_INDEX]);
    #endif /* (RTC_MOSI_SCL_RX_PIN) */

    #if(RTC_SCLK_PIN)
        RTC_SET_HSIOM_SEL(RTC_SCLK_HSIOM_REG, RTC_SCLK_HSIOM_MASK,
                                       RTC_SCLK_HSIOM_POS, hsiomSel[RTC_SCLK_PIN_INDEX]);
    #endif /* (RTC_SCLK_PIN) */

    #if(RTC_SS0_PIN)
        RTC_SET_HSIOM_SEL(RTC_SS0_HSIOM_REG, RTC_SS0_HSIOM_MASK,
                                       RTC_SS0_HSIOM_POS, hsiomSel[RTC_SS0_PIN_INDEX]);
    #endif /* (RTC_SS1_PIN) */

    #if(RTC_SS1_PIN)
        RTC_SET_HSIOM_SEL(RTC_SS1_HSIOM_REG, RTC_SS1_HSIOM_MASK,
                                       RTC_SS1_HSIOM_POS, hsiomSel[RTC_SS1_PIN_INDEX]);
    #endif /* (RTC_SS1_PIN) */

    #if(RTC_SS2_PIN)
        RTC_SET_HSIOM_SEL(RTC_SS2_HSIOM_REG, RTC_SS2_HSIOM_MASK,
                                       RTC_SS2_HSIOM_POS, hsiomSel[RTC_SS2_PIN_INDEX]);
    #endif /* (RTC_SS2_PIN) */

    #if(RTC_SS3_PIN)
        RTC_SET_HSIOM_SEL(RTC_SS3_HSIOM_REG,  RTC_SS3_HSIOM_MASK,
                                       RTC_SS3_HSIOM_POS, hsiomSel[RTC_SS3_PIN_INDEX]);
    #endif /* (RTC_SS3_PIN) */



    #if(RTC_MOSI_SCL_RX_PIN)
        RTC_spi_mosi_i2c_scl_uart_rx_SetDriveMode((uint8)
                                                               pinsDm[RTC_MOSI_SCL_RX_PIN_INDEX]);
    #endif /* (RTC_MOSI_SCL_RX_PIN) */

    #if(RTC_MOSI_SCL_RX_WAKE_PIN)
    RTC_spi_mosi_i2c_scl_uart_rx_wake_SetDriveMode((uint8)
                                                               pinsDm[RTC_MOSI_SCL_RX_WAKE_PIN_INDEX]);

    /* Set interrupt on rising edge */
    RTC_SET_INCFG_TYPE(RTC_MOSI_SCL_RX_WAKE_INTCFG_REG,
                                    RTC_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK,
                                    RTC_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS,
                                    RTC_INTCFG_TYPE_FALLING_EDGE);

    #endif /* (RTC_MOSI_SCL_RX_WAKE_PIN) */

    #if(RTC_MISO_SDA_TX_PIN)
        RTC_spi_miso_i2c_sda_uart_tx_SetDriveMode((uint8)
                                                                    pinsDm[RTC_MISO_SDA_TX_PIN_INDEX]);
    #endif /* (RTC_MOSI_SCL_RX_PIN) */

    #if(RTC_SCLK_PIN)
        RTC_spi_sclk_SetDriveMode((uint8) pinsDm[RTC_SCLK_PIN_INDEX]);
    #endif /* (RTC_SCLK_PIN) */

    #if(RTC_SS0_PIN)
        RTC_spi_ss0_SetDriveMode((uint8) pinsDm[RTC_SS0_PIN_INDEX]);
    #endif /* (RTC_SS0_PIN) */

    #if(RTC_SS1_PIN)
        RTC_spi_ss1_SetDriveMode((uint8) pinsDm[RTC_SS1_PIN_INDEX]);
    #endif /* (RTC_SS1_PIN) */

    #if(RTC_SS2_PIN)
        RTC_spi_ss2_SetDriveMode((uint8) pinsDm[RTC_SS2_PIN_INDEX]);
    #endif /* (RTC_SS2_PIN) */

    #if(RTC_SS3_PIN)
        RTC_spi_ss3_SetDriveMode((uint8) pinsDm[RTC_SS3_PIN_INDEX]);
    #endif /* (RTC_SS3_PIN) */
    }

#endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
