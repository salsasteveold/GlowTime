/*******************************************************************************
* File Name: RTC_PINS.h
* Version 1.10
*
* Description:
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_RTC_H)
#define CY_SCB_PINS_RTC_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define RTC_REMOVE_MOSI_SCL_RX_WAKE_PIN    (1u)
#define RTC_REMOVE_MOSI_SCL_RX_PIN         (1u)
#define RTC_REMOVE_MISO_SDA_TX_PIN         (1u)
#define RTC_REMOVE_SCLK_PIN                (1u)
#define RTC_REMOVE_SS0_PIN                 (1u)
#define RTC_REMOVE_SS1_PIN                 (1u)
#define RTC_REMOVE_SS2_PIN                 (1u)
#define RTC_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define RTC_REMOVE_I2C_PINS                (0u)
#define RTC_REMOVE_SPI_MASTER_PINS         (1u)
#define RTC_REMOVE_SPI_SLAVE_PINS          (1u)
#define RTC_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define RTC_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define RTC_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define RTC_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define RTC_REMOVE_UART_TX_PIN             (1u)
#define RTC_REMOVE_UART_RX_TX_PIN          (1u)
#define RTC_REMOVE_UART_RX_PIN             (1u)
#define RTC_REMOVE_UART_RX_WAKE_PIN        (1u)

/* Unconfigured pins */
#define RTC_MOSI_SCL_RX_WAKE_PIN   (0u == RTC_REMOVE_MOSI_SCL_RX_WAKE_PIN)
#define RTC_MOSI_SCL_RX_PIN        (0u == RTC_REMOVE_MOSI_SCL_RX_PIN)
#define RTC_MISO_SDA_TX_PIN        (0u == RTC_REMOVE_MISO_SDA_TX_PIN)
#define RTC_SCLK_PIN               (0u == RTC_REMOVE_SCLK_PIN)
#define RTC_SS0_PIN                (0u == RTC_REMOVE_SS0_PIN)
#define RTC_SS1_PIN                (0u == RTC_REMOVE_SS1_PIN)
#define RTC_SS2_PIN                (0u == RTC_REMOVE_SS2_PIN)
#define RTC_SS3_PIN                (0u == RTC_REMOVE_SS3_PIN)

/* Mode defined pins */
#define RTC_I2C_PINS               (0u == RTC_REMOVE_I2C_PINS)
#define RTC_SPI_MASTER_PINS        (0u == RTC_REMOVE_SPI_MASTER_PINS) 
#define RTC_SPI_SLAVE_PINS         (0u == RTC_REMOVE_SPI_SLAVE_PINS)
#define RTC_SPI_MASTER_SS0_PIN     (0u == RTC_REMOVE_SPI_MASTER_SS0_PIN)
#define RTC_SPI_MASTER_SS1_PIN     (0u == RTC_REMOVE_SPI_MASTER_SS1_PIN)
#define RTC_SPI_MASTER_SS2_PIN     (0u == RTC_REMOVE_SPI_MASTER_SS2_PIN)
#define RTC_SPI_MASTER_SS3_PIN     (0u == RTC_REMOVE_SPI_MASTER_SS3_PIN)
#define RTC_UART_TX_PIN            (0u == RTC_REMOVE_UART_TX_PIN)
#define RTC_UART_RX_TX_PIN         (0u == RTC_REMOVE_UART_RX_TX_PIN)
#define RTC_UART_RX_PIN            (0u == RTC_REMOVE_UART_RX_PIN)
#define RTC_UART_RX_WAKE_PIN       (0u == RTC_REMOVE_UART_RX_WAKE_PIN)


/***************************************
*             Includes
****************************************/

#if(RTC_MOSI_SCL_RX_WAKE_PIN)
    #include "RTC_spi_mosi_i2c_scl_uart_rx_wake.h"
#endif /* (RTC_MOSI_SCL_RX_WAKE_PIN) */

#if(RTC_MOSI_SCL_RX_PIN)
    #include "RTC_spi_mosi_i2c_scl_uart_rx.h"
#endif /* (RTC_MOSI_SCL_RX_PIN) */

#if(RTC_MISO_SDA_TX_PIN)
    #include "RTC_spi_miso_i2c_sda_uart_tx.h"
#endif /* (RTC_MISO_SDA_TX_PIN_PIN) */

#if(RTC_SCLK_PIN)
    #include "RTC_spi_sclk.h"
#endif /* (RTC_SCLK_PIN) */

#if(RTC_SS0_PIN)
    #include "RTC_spi_ss0.h"
#endif /* (RTC_SS1_PIN) */

#if(RTC_SS1_PIN)
    #include "RTC_spi_ss1.h"
#endif /* (RTC_SS1_PIN) */

#if(RTC_SS2_PIN)
    #include "RTC_spi_ss2.h"
#endif /* (RTC_SS2_PIN) */

#if(RTC_SS3_PIN)
    #include "RTC_spi_ss3.h"
#endif /* (RTC_SS3_PIN) */

#if(RTC_I2C_PINS)
    #include "RTC_scl.h"
    #include "RTC_sda.h"
#endif /* (RTC_I2C_PINS) */
    
#if(RTC_SPI_MASTER_PINS)
    #include "RTC_sclk_m.h"
    #include "RTC_mosi_m.h"
    #include "RTC_miso_m.h"
#endif /* (RTC_SPI_MASTER_PINS) */

#if(RTC_SPI_SLAVE_PINS)
    #include "RTC_sclk_s.h"
    #include "RTC_mosi_s.h"
    #include "RTC_miso_s.h"
    #include "RTC_ss_s.h"
#endif /* (RTC_SPI_SLAVE_PINS) */

#if(RTC_SPI_MASTER_SS0_PIN)
    #include "RTC_ss0_m.h"
#endif /* (RTC_SPI_MASTER_SS0_PIN) */

#if(RTC_SPI_MASTER_SS1_PIN)
    #include "RTC_ss1_m.h"
#endif /* (RTC_SPI_MASTER_SS1_PIN) */

#if(RTC_SPI_MASTER_SS2_PIN)
    #include "RTC_ss2_m.h"
#endif /* (RTC_SPI_MASTER_SS2_PIN) */

#if(RTC_SPI_MASTER_SS3_PIN)
    #include "RTC_ss3_m.h"
#endif /* (RTC_SPI_MASTER_SS3_PIN) */

#if(RTC_UART_TX_PIN)
    #include "RTC_tx.h"
#endif /* (RTC_UART_TX_PIN) */

#if(RTC_UART_RX_TX_PIN)
    #include "RTC_rx_tx.h"
#endif /* (RTC_UART_RX_TX_PIN) */

#if(RTC_UART_RX_PIN)
    #include "RTC_rx.h"
#endif /* (RTC_UART_RX_PIN) */

#if(RTC_UART_RX_WAKE_PIN)
    #include "RTC_rx_wake.h"
#endif /* (RTC_UART_RX_WAKE_PIN) */


/***************************************
*              Registers
***************************************/

#if(RTC_MOSI_SCL_RX_WAKE_PIN)
    #define RTC_MOSI_SCL_RX_WAKE_HSIOM_REG  \
                                                (*(reg32 *) RTC_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define RTC_MOSI_SCL_RX_WAKE_HSIOM_PTR  \
                                                ( (reg32 *) RTC_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define RTC_MOSI_SCL_RX_WAKE_HSIOM_MASK \
                                                (RTC_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_MASK)
    #define RTC_MOSI_SCL_RX_WAKE_HSIOM_POS  \
                                                (RTC_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_SHIFT)

    #define RTC_MOSI_SCL_RX_WAKE_INTCFG_REG    (*(reg32 *) \
                                                              RTC_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)
    #define RTC_MOSI_SCL_RX_WAKE_INTCFG_PTR    ( (reg32 *) \
                                                              RTC_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)

    #define RTC_INTCFG_TYPE_MASK                  (0x03u)
    #define RTC_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS  (RTC_spi_mosi_i2c_scl_uart_rx_wake__SHIFT)
    #define RTC_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK ((uint32)                                           \
                                                                    ((uint32) RTC_INTCFG_TYPE_MASK << \
                                                                    RTC_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS))
#endif /* (RTC_MOSI_SCL_RX_WAKE_PIN) */

#if(RTC_MOSI_SCL_RX_PIN)
    #define RTC_MOSI_SCL_RX_HSIOM_REG      (*(reg32 *) RTC_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define RTC_MOSI_SCL_RX_HSIOM_PTR      ( (reg32 *) RTC_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define RTC_MOSI_SCL_RX_HSIOM_MASK     (RTC_spi_mosi_i2c_scl_uart_rx__0__HSIOM_MASK)
    #define RTC_MOSI_SCL_RX_HSIOM_POS      (RTC_spi_mosi_i2c_scl_uart_rx__0__HSIOM_SHIFT)
#endif /* (RTC_MOSI_SCL_RX_PIN) */

#if(RTC_MISO_SDA_TX_PIN)
    #define RTC_MISO_SDA_TX_HSIOM_REG      (*(reg32 *) RTC_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define RTC_MISO_SDA_TX_HSIOM_PTR      ( (reg32 *) RTC_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define RTC_MISO_SDA_TX_HSIOM_MASK     (RTC_spi_miso_i2c_sda_uart_tx__0__HSIOM_MASK)
    #define RTC_MISO_SDA_TX_HSIOM_POS      (RTC_spi_miso_i2c_sda_uart_tx__0__HSIOM_SHIFT)
#endif /* (RTC_MISO_SDA_TX_PIN_PIN) */

#if(RTC_SCLK_PIN)
    #define RTC_SCLK_HSIOM_REG     (*(reg32 *) RTC_spi_sclk__0__HSIOM)
    #define RTC_SCLK_HSIOM_PTR     ( (reg32 *) RTC_spi_sclk__0__HSIOM)
    #define RTC_SCLK_HSIOM_MASK    (RTC_spi_sclk__0__HSIOM_MASK)
    #define RTC_SCLK_HSIOM_POS     (RTC_spi_sclk__0__HSIOM_SHIFT)
#endif /* (RTC_SCLK_PIN) */

#if(RTC_SS0_PIN)
    #define RTC_SS0_HSIOM_REG      (*(reg32 *) RTC_spi_ss0__0__HSIOM)
    #define RTC_SS0_HSIOM_PTR      ( (reg32 *) RTC_spi_ss0__0__HSIOM)
    #define RTC_SS0_HSIOM_MASK     (RTC_spi_ss0__0__HSIOM_MASK)
    #define RTC_SS0_HSIOM_POS      (RTC_spi_ss0__0__HSIOM_SHIFT)
#endif /* (RTC_SS1_PIN) */

#if(RTC_SS1_PIN)
    #define RTC_SS1_HSIOM_REG      (*(reg32 *) RTC_spi_ss1__0__HSIOM)
    #define RTC_SS1_HSIOM_PTR      ( (reg32 *) RTC_spi_ss1__0__HSIOM)
    #define RTC_SS1_HSIOM_MASK     (RTC_spi_ss1__0__HSIOM_MASK)
    #define RTC_SS1_HSIOM_POS      (RTC_spi_ss1__0__HSIOM_SHIFT)
#endif /* (RTC_SS1_PIN) */

#if(RTC_SS2_PIN)
    #define RTC_SS2_HSIOM_REG     (*(reg32 *) RTC_spi_ss2__0__HSIOM)
    #define RTC_SS2_HSIOM_PTR     ( (reg32 *) RTC_spi_ss2__0__HSIOM)
    #define RTC_SS2_HSIOM_MASK    (RTC_spi_ss2__0__HSIOM_MASK)
    #define RTC_SS2_HSIOM_POS     (RTC_spi_ss2__0__HSIOM_SHIFT)
#endif /* (RTC_SS2_PIN) */

#if(RTC_SS3_PIN)
    #define RTC_SS3_HSIOM_REG     (*(reg32 *) RTC_spi_ss3__0__HSIOM)
    #define RTC_SS3_HSIOM_PTR     ( (reg32 *) RTC_spi_ss3__0__HSIOM)
    #define RTC_SS3_HSIOM_MASK    (RTC_spi_ss3__0__HSIOM_MASK)
    #define RTC_SS3_HSIOM_POS     (RTC_spi_ss3__0__HSIOM_SHIFT)
#endif /* (RTC_SS3_PIN) */

#if(RTC_I2C_PINS)
    #define RTC_SCL_HSIOM_REG     (*(reg32 *) RTC_scl__0__HSIOM)
    #define RTC_SCL_HSIOM_PTR     ( (reg32 *) RTC_scl__0__HSIOM)
    #define RTC_SCL_HSIOM_MASK    (RTC_scl__0__HSIOM_MASK)
    #define RTC_SCL_HSIOM_POS     (RTC_scl__0__HSIOM_SHIFT)

    #define RTC_SDA_HSIOM_REG     (*(reg32 *) RTC_sda__0__HSIOM)
    #define RTC_SDA_HSIOM_PTR     ( (reg32 *) RTC_sda__0__HSIOM)
    #define RTC_SDA_HSIOM_MASK    (RTC_sda__0__HSIOM_MASK)
    #define RTC_SDA_HSIOM_POS     (RTC_sda__0__HSIOM_SHIFT)
#endif /* (RTC_I2C_PINS) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constanst */
#define RTC_HSIOM_DEF_SEL      (0x00u)
#define RTC_HSIOM_GPIO_SEL     (0x00u)
#define RTC_HSIOM_UART_SEL     (0x09u)
#define RTC_HSIOM_I2C_SEL      (0x0Eu)
#define RTC_HSIOM_SPI_SEL      (0x0Fu)

#define RTC_SCB_PINS_NUMBER            (7u)
#define RTC_MOSI_SCL_RX_PIN_INDEX      (0u) /* RX pins without interrupt */
#define RTC_MOSI_SCL_RX_WAKE_PIN_INDEX (0u) /* RX pin with interrupt     */
#define RTC_MISO_SDA_TX_PIN_INDEX      (1u)
#define RTC_SCLK_PIN_INDEX             (2u)
#define RTC_SS0_PIN_INDEX              (3u)
#define RTC_SS1_PIN_INDEX              (4u)
#define RTC_SS2_PIN_INDEX              (5u)
#define RTC_SS3_PIN_INDEX              (6u)

#define RTC_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin DM defines */
#define RTC_PIN_DM_ALG_HIZ  (0u)
#define RTC_PIN_DM_DIG_HIZ  (1u)
#define RTC_PIN_DM_OD_LO    (4u)
#define RTC_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

#define RTC_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        /* Sets new bits-mask */                 \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

#define RTC_SET_HSIOM_SEL(reg, mask, pos, sel) RTC_SET_REGISTER_BITS(reg, mask, pos, sel)
#define RTC_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        RTC_SET_REGISTER_BITS(reg, mask, pos, intType)


/* RTC_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  RTC_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* Unconfigured SCB: scl singnal */
#if(RTC_MOSI_SCL_RX_WAKE_PIN)
    #define RTC_SET_I2C_SCL_DR(val) \
                            RTC_spi_mosi_i2c_scl_uart_rx_wake_Write(val)

    #define RTC_SET_I2C_SCL_HSIOM_SEL(sel) \
                    RTC_SET_HSIOM_SEL(RTC_MOSI_SCL_RX_WAKE_HSIOM_REG,  \
                                                   RTC_MOSI_SCL_RX_WAKE_HSIOM_MASK, \
                                                   RTC_MOSI_SCL_RX_WAKE_HSIOM_POS,  \
                                                   (sel))

#elif(RTC_MOSI_SCL_RX_PIN)
    #define RTC_SET_I2C_SCL_DR(val) \
                            RTC_spi_mosi_i2c_scl_uart_rx_Write(val)


    #define RTC_SET_I2C_SCL_HSIOM_SEL(sel) \
                            RTC_SET_HSIOM_SEL(RTC_MOSI_SCL_RX_HSIOM_REG,  \
                                                           RTC_MOSI_SCL_RX_HSIOM_MASK, \
                                                           RTC_MOSI_SCL_RX_HSIOM_POS,  \
                                                           (sel))
#else
    #if(!RTC_I2C_PINS)
        #define RTC_SET_I2C_SCL_DR(val) \
                                                 do{ ; }while(0)
        #define RTC_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                        do{ ; }while(0)

    #endif /* (!RTC_I2C_PINS) */
#endif /* (RTC_MOSI_SCL_RX_PIN) */

/* SCB I2C: scl singal */
#if(RTC_I2C_PINS)
    #define RTC_SET_I2C_SCL_DR(val) RTC_scl_Write(val)

    #define RTC_SET_I2C_SCL_HSIOM_SEL(sel) \
                          RTC_SET_HSIOM_SEL(RTC_SCL_HSIOM_REG,  \
                                                         RTC_SCL_HSIOM_MASK, \
                                                         RTC_SCL_HSIOM_POS,  \
                                                         (sel))

#endif /* (RTC_I2C_PINS) */


#endif /* (CY_SCB_PINS_RTC_H) */


/* [] END OF FILE */
