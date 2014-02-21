/*******************************************************************************
* File Name: RTC_PM.c
* Version 1.10
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "RTC.h"
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


/***************************************
*   Backup Structure declaration
***************************************/

RTC_BACKUP_STRUCT RTC_backup =
{
    0u, /* enableState */
};


/*******************************************************************************
* Function Name: RTC_Sleep
********************************************************************************
*
* Summary:
*  Calls SaveConfig function fucntion for selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RTC_Sleep(void)
{
#if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)

    if(0u != RTC_scbEnableWake)
    {
        if(RTC_SCB_MODE_I2C_RUNTM_CFG)
        {
            RTC_I2CSaveConfig();
        }
        else if(RTC_SCB_MODE_SPI_RUNTM_CFG)
        {
            RTC_SpiSaveConfig();
        }
        else if(RTC_SCB_MODE_UART_RUNTM_CFG)
        {
            RTC_UartSaveConfig();
        }
        else if(RTC_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            RTC_EzI2CSaveConfig();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    }
    else
    {
        RTC_backup.enableState = (uint8) RTC_GET_CTRL_ENABLED;
        
        if(0u != RTC_backup.enableState)
        {
            RTC_Stop();
        }
    }
    
    RTC_DisableTxPinsInputBuffer();
    
#else
    
    #if defined (RTC_I2C_WAKE_ENABLE_CONST) && (RTC_I2C_WAKE_ENABLE_CONST)
        RTC_I2CSaveConfig();
        
    #elif defined (RTC_SPI_WAKE_ENABLE_CONST) && (RTC_SPI_WAKE_ENABLE_CONST)
        RTC_SpiSaveConfig();
        
    #elif defined (RTC_UART_WAKE_ENABLE_CONST) && (RTC_UART_WAKE_ENABLE_CONST)
        RTC_UartSaveConfig();
        
    #elif defined (RTC_EZI2C_WAKE_ENABLE_CONST) && (RTC_EZI2C_WAKE_ENABLE_CONST)
        RTC_EzI2CSaveConfig();
    
    #else
        
        RTC_backup.enableState = (uint8) RTC_GET_CTRL_ENABLED;
        
        /* Check enable state */
        if(0u != RTC_backup.enableState)
        {
            RTC_Stop();
        }
        
    #endif /* defined (RTC_SCB_MODE_I2C_CONST_CFG) && (RTC_I2C_WAKE_ENABLE_CONST) */
    
    RTC_DisableTxPinsInputBuffer();
    
#endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: RTC_Wakeup
********************************************************************************
*
* Summary:
*  Calls RestoreConfig function fucntion for selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RTC_Wakeup(void)
{
#if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)

    RTC_EnableTxPinsInputBuffer();
        
    if(0u != RTC_scbEnableWake)
    {
        if(RTC_SCB_MODE_I2C_RUNTM_CFG)
        {
            RTC_I2CRestoreConfig();
        }
        else if(RTC_SCB_MODE_SPI_RUNTM_CFG)
        {
            RTC_SpiRestoreConfig();
        }
        else if(RTC_SCB_MODE_UART_RUNTM_CFG)
        {
            RTC_UartRestoreConfig();
        }
        else if(RTC_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            RTC_EzI2CRestoreConfig();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    }
    else
    {    
        /* Restore enable state */
        if(0u != RTC_backup.enableState)
        {
            RTC_Enable();
        }
    }

#else
    
    RTC_EnableTxPinsInputBuffer();
        
    #if defined (RTC_I2C_WAKE_ENABLE_CONST) && (RTC_I2C_WAKE_ENABLE_CONST)
        RTC_I2CRestoreConfig();
        
    #elif defined (RTC_SPI_WAKE_ENABLE_CONST) && (RTC_SPI_WAKE_ENABLE_CONST)
        RTC_SpiRestoreConfig();
        
    #elif defined (RTC_UART_WAKE_ENABLE_CONST) && (RTC_UART_WAKE_ENABLE_CONST)
        RTC_UartRestoreConfig();
        
    #elif defined (RTC_EZI2C_WAKE_ENABLE_CONST) && (RTC_EZI2C_WAKE_ENABLE_CONST)
        RTC_EzI2CRestoreConfig();
    
    #else
        /* Check enable state */
        if(0u != RTC_backup.enableState)
        {
            RTC_Enable();
        }
        
    #endif /* (RTC_I2C_WAKE_ENABLE_CONST) */

#endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: RTC_DisableTxPinsInputBuffer
********************************************************************************
*
* Summary:
*  Disables input buffers for TX pins. This action removes leakage current while
*  low power mode (Cypress ID 149635).
*   SCB mode is I2C and EZI2C: bus is pulled-up. Leave pins as it is.
*   SCB mode SPI:
*     Slave  - disable input buffer for MISO pin.
*     Master - disable input buffer for all pins.
*   SCB mode SmartCard: 
*     Standard and IrDA - disable input buffer for TX pin.
*     SmartCard - RX_TX pin is pulled-up. Leave pin as it is.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RTC_DisableTxPinsInputBuffer(void)
{
#if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)
    
    /* SCB mode is I2C and EZI2C: bus is pulled-up. Does nothing */
       
    if(RTC_SCB_MODE_SPI_RUNTM_CFG)
    {
        if(0u != (RTC_SPI_CTRL_REG & RTC_SPI_CTRL_MASTER))
        /* SPI Master */
        {
        #if(RTC_MOSI_SCL_RX_WAKE_PIN)
            RTC_spi_mosi_i2c_scl_uart_rx_wake_INP_DIS |= \
                                                                RTC_spi_mosi_i2c_scl_uart_rx_wake_MASK;
        #endif /* (RTC_MOSI_SCL_RX_WAKE_PIN) */

        #if(RTC_MOSI_SCL_RX_PIN)
            RTC_spi_mosi_i2c_scl_uart_rx_INP_DIS |= RTC_spi_mosi_i2c_scl_uart_rx_MASK;
        #endif /* (RTC_MOSI_SCL_RX_PIN) */

        #if(RTC_MISO_SDA_TX_PIN)
            RTC_spi_miso_i2c_sda_uart_tx_INP_DIS |= RTC_spi_miso_i2c_sda_uart_tx_MASK;
        #endif /* (RTC_MISO_SDA_TX_PIN_PIN) */

        #if(RTC_SCLK_PIN)
            RTC_spi_sclk_INP_DIS |= RTC_spi_sclk_MASK;
        #endif /* (RTC_SCLK_PIN) */

        #if(RTC_SS0_PIN)
            RTC_spi_ss0_INP_DIS |= RTC_spi_ss0_MASK;
        #endif /* (RTC_SS1_PIN) */

        #if(RTC_SS1_PIN)
            RTC_spi_ss1_INP_DIS |= RTC_spi_ss1_MASK;
        #endif /* (RTC_SS1_PIN) */

        #if(RTC_SS2_PIN)
            RTC_spi_ss2_INP_DIS |= RTC_spi_ss2_MASK;
        #endif /* (RTC_SS2_PIN) */

        #if(RTC_SS3_PIN)
            RTC_spi_ss3_INP_DIS |= RTC_spi_ss3_MASK;
        #endif /* (RTC_SS3_PIN) */
        }
        else
        /* SPI Slave */
        {
        #if(RTC_MISO_SDA_TX_PIN)
            RTC_spi_miso_i2c_sda_uart_tx_INP_DIS |= RTC_spi_miso_i2c_sda_uart_tx_MASK;
        #endif /* (RTC_MISO_SDA_TX_PIN_PIN) */
        }
    }
    else if (RTC_SCB_MODE_UART_RUNTM_CFG)
    {
        if(RTC_UART_CTRL_MODE_UART_SMARTCARD != 
            (RTC_UART_CTRL_REG & RTC_UART_CTRL_MODE_MASK))
        /* UART Standard or IrDA */
        {
        #if(RTC_MISO_SDA_TX_PIN)
            RTC_spi_miso_i2c_sda_uart_tx_INP_DIS |= RTC_spi_miso_i2c_sda_uart_tx_MASK;
        #endif /* (RTC_MISO_SDA_TX_PIN_PIN) */
        }
    }
    else
    {
        /* Does nothing */
    }
    
#else
    
    /* SCB mode is I2C and EZI2C: bus is pulled-up. Does nothing */
        
    /* SCB mode is SPI Master */
    #if(RTC_SPI_MASTER_PINS)
        RTC_sclk_m_INP_DIS |= RTC_sclk_m_MASK;
        RTC_mosi_m_INP_DIS |= RTC_mosi_m_MASK;
        RTC_miso_m_INP_DIS |= RTC_miso_m_MASK;
    #endif /* (RTC_SPI_MASTER_PINS) */

    #if(RTC_SPI_MASTER_SS0_PIN)
        RTC_ss0_m_INP_DIS |= RTC_ss0_m_MASK;
    #endif /* (RTC_SPI_MASTER_SS0_PIN) */

    #if(RTC_SPI_MASTER_SS1_PIN)
        RTC_ss1_m_INP_DIS |= RTC_ss1_m_MASK;
    #endif /* (RTC_SPI_MASTER_SS1_PIN) */

    #if(RTC_SPI_MASTER_SS2_PIN)
        RTC_ss2_m_INP_DIS |= RTC_ss2_m_MASK;
    #endif /* (RTC_SPI_MASTER_SS2_PIN) */

    #if(RTC_SPI_MASTER_SS3_PIN)
        RTC_ss3_m_INP_DIS |= RTC_ss3_m_MASK;
    #endif /* (RTC_SPI_MASTER_SS3_PIN) */
    
    /* SCB mode is SPI Slave */
    #if(RTC_SPI_SLAVE_PINS)
        RTC_miso_s_INP_DIS |= RTC_miso_s_MASK;
    #endif /* (RTC_SPI_SLAVE_PINS) */

    /* SCB mode is UART */
    #if(RTC_UART_TX_PIN)
        RTC_tx_INP_DIS |= RTC_tx_MASK;
    #endif /* (RTC_UART_TX_PIN) */

#endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: RTC_EnableTxPinsInputBuffer
********************************************************************************
*
* Summary:
*  Enables input buffers for TX pins. Restore changes done byte
*RTC_DisableTxPinsInputBuffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RTC_EnableTxPinsInputBuffer(void)
{
#if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)
    if(RTC_SCB_MODE_SPI_RUNTM_CFG)
    {
        if(0u != (RTC_SPI_CTRL_REG & RTC_SPI_CTRL_MASTER))
        /* SPI Master */
        {
        #if(RTC_MOSI_SCL_RX_WAKE_PIN)
            RTC_spi_mosi_i2c_scl_uart_rx_wake_INP_DIS &= \
                                            (uint32) ~((uint32) RTC_spi_mosi_i2c_scl_uart_rx_wake_MASK);
        #endif /* (RTC_MOSI_SCL_RX_WAKE_PIN) */

        #if(RTC_MOSI_SCL_RX_PIN)
            RTC_spi_mosi_i2c_scl_uart_rx_INP_DIS &= \
                                            (uint32) ~((uint32) RTC_spi_mosi_i2c_scl_uart_rx_MASK);
        #endif /* (RTC_MOSI_SCL_RX_PIN) */

        #if(RTC_MISO_SDA_TX_PIN)
            RTC_spi_miso_i2c_sda_uart_tx_INP_DIS &= \
                                            (uint32) ~((uint32) RTC_spi_miso_i2c_sda_uart_tx_MASK);
        #endif /* (RTC_MISO_SDA_TX_PIN_PIN) */

        #if(RTC_SCLK_PIN)
            RTC_spi_sclk_INP_DIS &= (uint32) ~((uint32) RTC_spi_sclk_MASK);
        #endif /* (RTC_SCLK_PIN) */

        #if(RTC_SS0_PIN)
            RTC_spi_ss0_INP_DIS &= (uint32) ~((uint32) RTC_spi_ss0_MASK);
        #endif /* (RTC_SS1_PIN) */

        #if(RTC_SS1_PIN)
            RTC_spi_ss1_INP_DIS &= (uint32) ~((uint32) RTC_spi_ss1_MASK);
        #endif /* (RTC_SS1_PIN) */

        #if(RTC_SS2_PIN)
            RTC_spi_ss2_INP_DIS &= (uint32) ~((uint32) RTC_spi_ss2_MASK);
        #endif /* (RTC_SS2_PIN) */

        #if(RTC_SS3_PIN)
            RTC_spi_ss3_INP_DIS &= (uint32) ~((uint32) RTC_spi_ss3_MASK);
        #endif /* (RTC_SS3_PIN) */
        }
        else
        /* SPI Slave */
        {
        #if(RTC_MISO_SDA_TX_PIN)
            RTC_spi_miso_i2c_sda_uart_tx_INP_DIS &= \
                                                (uint32) ~((uint32) RTC_spi_miso_i2c_sda_uart_tx_MASK);
        #endif /* (RTC_MISO_SDA_TX_PIN_PIN) */
        }
    }
    else if (RTC_SCB_MODE_UART_RUNTM_CFG)
    {
        if(RTC_UART_CTRL_MODE_UART_SMARTCARD != 
                (RTC_UART_CTRL_REG & RTC_UART_CTRL_MODE_MASK))
        /* UART Standard or IrDA */
        {
        #if(RTC_MISO_SDA_TX_PIN)
            RTC_spi_miso_i2c_sda_uart_tx_INP_DIS &= \
                                                (uint32) ~((uint32) RTC_spi_miso_i2c_sda_uart_tx_MASK);
        #endif /* (RTC_MISO_SDA_TX_PIN_PIN) */
        }
    }
    else
    {
        /* Does nothing */
    }
    
#else
        
    /* SCB mode is SPI Master */
    #if(RTC_SPI_MASTER_PINS)
        RTC_sclk_m_INP_DIS &= (uint32) ~((uint32) RTC_sclk_m_MASK);
        RTC_mosi_m_INP_DIS &= (uint32) ~((uint32) RTC_mosi_m_MASK);
        RTC_miso_m_INP_DIS &= (uint32) ~((uint32) RTC_miso_m_MASK);
    #endif /* (RTC_SPI_MASTER_PINS) */

    #if(RTC_SPI_MASTER_SS0_PIN)
        RTC_ss0_m_INP_DIS &= (uint32) ~((uint32) RTC_ss0_m_MASK);
    #endif /* (RTC_SPI_MASTER_SS0_PIN) */

    #if(RTC_SPI_MASTER_SS1_PIN)
        RTC_ss1_m_INP_DIS &= (uint32) ~((uint32) RTC_ss1_m_MASK);
    #endif /* (RTC_SPI_MASTER_SS1_PIN) */

    #if(RTC_SPI_MASTER_SS2_PIN)
        RTC_ss2_m_INP_DIS &= (uint32) ~((uint32) RTC_ss2_m_MASK);
    #endif /* (RTC_SPI_MASTER_SS2_PIN) */

    #if(RTC_SPI_MASTER_SS3_PIN)
        RTC_ss3_m_INP_DIS &= (uint32) ~((uint32) RTC_ss3_m_MASK);
    #endif /* (RTC_SPI_MASTER_SS3_PIN) */
    
    /* SCB mode is SPI Slave */
    #if(RTC_SPI_SLAVE_PINS)
        RTC_miso_s_INP_DIS &= (uint32) ~((uint32) RTC_miso_s_MASK);
    #endif /* (RTC_SPI_SLAVE_PINS) */

    /* SCB mode is UART */
    #if(RTC_UART_TX_PIN)
        RTC_tx_INP_DIS &= (uint32) ~((uint32) RTC_tx_MASK);
    #endif /* (RTC_UART_TX_PIN) */

#endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
