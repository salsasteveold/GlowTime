/*******************************************************************************
* File Name: RTC.h
* Version 1.10
*
* Description:
*  This file provides constants and parameter values for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_RTC_H)
#define CY_SCB_RTC_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"


/***************************************
*  Conditional Compilation Parameters
****************************************/

#define RTC_SCB_MODE                     (1u)

/* SCB modes enum */
#define RTC_SCB_MODE_I2C                 (0x01u)
#define RTC_SCB_MODE_SPI                 (0x02u)
#define RTC_SCB_MODE_UART                (0x04u)
#define RTC_SCB_MODE_EZI2C               (0x08u)
#define RTC_SCB_MODE_UNCONFIG            (0xFFu)

/* Define run time operation mode */
#define RTC_SCB_MODE_I2C_RUNTM_CFG       (RTC_SCB_MODE_I2C       == RTC_scbMode)
#define RTC_SCB_MODE_SPI_RUNTM_CFG       (RTC_SCB_MODE_SPI       == RTC_scbMode)
#define RTC_SCB_MODE_UART_RUNTM_CFG      (RTC_SCB_MODE_UART      == RTC_scbMode)
#define RTC_SCB_MODE_EZI2C_RUNTM_CFG     (RTC_SCB_MODE_EZI2C     == RTC_scbMode)
#define RTC_SCB_MODE_UNCONFIG_RUNTM_CFG  (RTC_SCB_MODE_UNCONFIG  == RTC_scbMode)

/* Condition compilation depends on operation mode: unconfigured implies apply to all modes */
#define RTC_SCB_MODE_I2C_CONST_CFG       (RTC_SCB_MODE_I2C       == RTC_SCB_MODE)
#define RTC_SCB_MODE_SPI_CONST_CFG       (RTC_SCB_MODE_SPI       == RTC_SCB_MODE)
#define RTC_SCB_MODE_UART_CONST_CFG      (RTC_SCB_MODE_UART      == RTC_SCB_MODE)
#define RTC_SCB_MODE_EZI2C_CONST_CFG     (RTC_SCB_MODE_EZI2C     == RTC_SCB_MODE)
#define RTC_SCB_MODE_UNCONFIG_CONST_CFG  (RTC_SCB_MODE_UNCONFIG  == RTC_SCB_MODE)

/* Condition compilation for includes */
#define RTC_SCB_MODE_I2C_INC       (0u !=(RTC_SCB_MODE_I2C       & RTC_SCB_MODE))
#define RTC_SCB_MODE_SPI_INC       (0u !=(RTC_SCB_MODE_SPI       & RTC_SCB_MODE))
#define RTC_SCB_MODE_UART_INC      (0u !=(RTC_SCB_MODE_UART      & RTC_SCB_MODE))
#define RTC_SCB_MODE_EZI2C_INC     (0u !=(RTC_SCB_MODE_EZI2C     & RTC_SCB_MODE))

/* Interrupts remove options */
#define RTC_REMOVE_SCB_IRQ             (0u)
#define RTC_SCB_IRQ_INTERNAL           (0u == RTC_REMOVE_SCB_IRQ)

#define RTC_REMOVE_UART_RX_WAKEUP_IRQ  (1u)
#define RTC_UART_RX_WAKEUP_IRQ         (0u == RTC_REMOVE_UART_RX_WAKEUP_IRQ)

/* SCB interrupt enum */
#define RTC_SCB_INTR_MODE_NONE     (0u)
#define RTC_SCB_INTR_MODE_INTERNAL (1u)
#define RTC_SCB_INTR_MODE_EXTERNAL (2u)

/* Bootloader communication interface enable */
#define RTC_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_RTC) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))


/***************************************
*       Includes
****************************************/

#include "RTC_PINS.h"

#if(RTC_SCB_IRQ_INTERNAL)
    #include "RTC_SCB_IRQ.h"
#endif /* (RTC_SCB_IRQ_INTERNAL) */

#if(RTC_UART_RX_WAKEUP_IRQ)
    #include "RTC_RX_WAKEUP_IRQ.h"
#endif /* (RTC_UART_RX_WAKEUP_IRQ) */


/***************************************
*       Type Definitions
***************************************/

typedef struct
{
    uint8 enableState;
} RTC_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* Start and Stop APIs */
void RTC_Init(void);
void RTC_Enable(void);
void RTC_Start(void);
void RTC_Stop(void);

/* Sleep and Wakeup APis */
void RTC_Sleep(void);
void RTC_Wakeup(void);

/* Customer interrupt handler */
void RTC_SetCustomInterruptHandler(cyisraddress func);

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (RTC_BTLDR_COMM_ENABLED)

    /* Bootloader Physical layer functions */
    void RTC_CyBtldrCommStart(void);
    void RTC_CyBtldrCommStop (void);
    void RTC_CyBtldrCommReset(void);
    cystatus RTC_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus RTC_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    #if(CYDEV_BOOTLOADER_IO_COMP == CyBtldr_RTC)
        #define CyBtldrCommStart    RTC_CyBtldrCommStart
        #define CyBtldrCommStop     RTC_CyBtldrCommStop
        #define CyBtldrCommReset    RTC_CyBtldrCommReset
        #define CyBtldrCommWrite    RTC_CyBtldrCommWrite
        #define CyBtldrCommRead     RTC_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_RTC) */

#endif /*defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_RTC) || \
                                                     (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */

/* Interface to internal interrupt component */
#if(RTC_SCB_IRQ_INTERNAL)
    #define RTC_EnableInt()    RTC_SCB_IRQ_Enable()
    #define RTC_DisableInt()   RTC_SCB_IRQ_Disable()
#endif /* (RTC_SCB_IRQ_INTERNAL) */

/* Get interrupt cause */
#define RTC_GetInterruptCause()    (RTC_INTR_CAUSE_REG)

/* APIs to service INTR_RX register */
#define RTC_SetRxInterruptMode(interruptMask)     RTC_WRITE_INTR_RX_MASK(interruptMask)
#define RTC_ClearRxInterruptSource(interruptMask) RTC_CLEAR_INTR_RX(interruptMask)
#define RTC_SetRxInterrupt(interruptMask)         RTC_SET_INTR_RX(interruptMask)
#define RTC_GetRxInterruptSource()                (RTC_INTR_RX_REG)
#define RTC_GetRxInterruptMode()                  (RTC_INTR_RX_MASK_REG)
#define RTC_GetRxInterruptSourceMasked()          (RTC_INTR_RX_MASKED_REG)

/* APIs to service INTR_TX register */
#define RTC_SetTxInterruptMode(interruptMask)     RTC_WRITE_INTR_TX_MASK(interruptMask)
#define RTC_ClearTxInterruptSource(interruptMask) RTC_CLEAR_INTR_TX(interruptMask)
#define RTC_SetTxInterrupt(interruptMask)         RTC_SET_INTR_TX(interruptMask)
#define RTC_GetTxInterruptSource()                (RTC_INTR_TX_REG)
#define RTC_GetTxInterruptMode()                  (RTC_INTR_TX_MASK_REG)
#define RTC_GetTxInterruptSourceMasked()          (RTC_INTR_TX_MASKED_REG)

/* APIs to service INTR_MASTER register */
#define RTC_SetMasterInterruptMode(interruptMask)    RTC_WRITE_INTR_MASTER_MASK(interruptMask)
#define RTC_ClearMasterInterruptSource(interruptMask) RTC_CLEAR_INTR_MASTER(interruptMask)
#define RTC_SetMasterInterrupt(interruptMask)         RTC_SET_INTR_MASTER(interruptMask)
#define RTC_GetMasterInterruptSource()                (RTC_INTR_MASTER_REG)
#define RTC_GetMasterInterruptMode()                  (RTC_INTR_MASTER_MASK_REG)
#define RTC_GetMasterInterruptSourceMasked()          (RTC_INTR_MASTER_MASKED_REG)

/* APIs to service INTR_SLAVE register */
#define RTC_SetSlaveInterruptMode(interruptMask)     RTC_WRITE_INTR_SLAVE_MASK(interruptMask)
#define RTC_ClearSlaveInterruptSource(interruptMask) RTC_CLEAR_INTR_SLAVE(interruptMask)
#define RTC_SetSlaveInterrupt(interruptMask)         RTC_SET_INTR_SLAVE(interruptMask)
#define RTC_GetSlaveInterruptSource()                (RTC_INTR_SLAVE_REG)
#define RTC_GetSlaveInterruptMode()                  (RTC_INTR_SLAVE_MASK_REG)
#define RTC_GetSlaveInterruptSourceMasked()          (RTC_INTR_SLAVE_MASKED_REG)


/**********************************
*     Vars with External Linkage
**********************************/

extern uint8 RTC_initVar;


/***************************************
*              Registers
***************************************/

#define RTC_CTRL_REG               (*(reg32 *) RTC_SCB__CTRL)
#define RTC_CTRL_PTR               ( (reg32 *) RTC_SCB__CTRL)

#define RTC_STATUS_REG             (*(reg32 *) RTC_SCB__STATUS)
#define RTC_STATUS_PTR             ( (reg32 *) RTC_SCB__STATUS)

#define RTC_SPI_CTRL_REG           (*(reg32 *) RTC_SCB__SPI_CTRL)
#define RTC_SPI_CTRL_PTR           ( (reg32 *) RTC_SCB__SPI_CTRL)

#define RTC_SPI_STATUS_REG         (*(reg32 *) RTC_SCB__SPI_STATUS)
#define RTC_SPI_STATUS_PTR         ( (reg32 *) RTC_SCB__SPI_STATUS)

#define RTC_UART_CTRL_REG          (*(reg32 *) RTC_SCB__UART_CTRL)
#define RTC_UART_CTRL_PTR          ( (reg32 *) RTC_SCB__UART_CTRL)

#define RTC_UART_TX_CTRL_REG       (*(reg32 *) RTC_SCB__UART_TX_CTRL)
#define RTC_UART_TX_CTRL_PTR       ( (reg32 *) RTC_SCB__UART_RX_CTRL)

#define RTC_UART_RX_CTRL_REG       (*(reg32 *) RTC_SCB__UART_RX_CTRL)
#define RTC_UART_RX_CTRL_PTR       ( (reg32 *) RTC_SCB__UART_RX_CTRL)

#define RTC_UART_RX_STATUS_REG     (*(reg32 *) RTC_SCB__UART_RX_STATUS)
#define RTC_UART_RX_STATUS_PTR     ( (reg32 *) RTC_SCB__UART_RX_STATUS)

#define RTC_I2C_CTRL_REG           (*(reg32 *) RTC_SCB__I2C_CTRL)
#define RTC_I2C_CTRL_PTR           ( (reg32 *) RTC_SCB__I2C_CTRL)

#define RTC_I2C_STATUS_REG         (*(reg32 *) RTC_SCB__I2C_STATUS)
#define RTC_I2C_STATUS_PTR         ( (reg32 *) RTC_SCB__I2C_STATUS)

#define RTC_I2C_MASTER_CMD_REG     (*(reg32 *) RTC_SCB__I2C_M_CMD)
#define RTC_I2C_MASTER_CMD_PTR     ( (reg32 *) RTC_SCB__I2C_M_CMD)

#define RTC_I2C_SLAVE_CMD_REG      (*(reg32 *) RTC_SCB__I2C_S_CMD)
#define RTC_I2C_SLAVE_CMD_PTR      ( (reg32 *) RTC_SCB__I2C_S_CMD)

#define RTC_I2C_CFG_REG            (*(reg32 *) RTC_SCB__I2C_CFG)
#define RTC_I2C_CFG_PTR            ( (reg32 *) RTC_SCB__I2C_CFG)

#define RTC_TX_CTRL_REG            (*(reg32 *) RTC_SCB__TX_CTRL)
#define RTC_TX_CTRL_PTR            ( (reg32 *) RTC_SCB__TX_CTRL)

#define RTC_TX_FIFO_CTRL_REG       (*(reg32 *) RTC_SCB__TX_FIFO_CTRL)
#define RTC_TX_FIFO_CTRL_PTR       ( (reg32 *) RTC_SCB__TX_FIFO_CTRL)

#define RTC_TX_FIFO_STATUS_REG     (*(reg32 *) RTC_SCB__TX_FIFO_STATUS)
#define RTC_TX_FIFO_STATUS_PTR     ( (reg32 *) RTC_SCB__TX_FIFO_STATUS)

#define RTC_TX_FIFO_WR_REG         (*(reg32 *) RTC_SCB__TX_FIFO_WR)
#define RTC_TX_FIFO_WR_PTR         ( (reg32 *) RTC_SCB__TX_FIFO_WR)

#define RTC_RX_CTRL_REG            (*(reg32 *) RTC_SCB__RX_CTRL)
#define RTC_RX_CTRL_PTR            ( (reg32 *) RTC_SCB__RX_CTRL)

#define RTC_RX_FIFO_CTRL_REG       (*(reg32 *) RTC_SCB__RX_FIFO_CTRL)
#define RTC_RX_FIFO_CTRL_PTR       ( (reg32 *) RTC_SCB__RX_FIFO_CTRL)

#define RTC_RX_FIFO_STATUS_REG     (*(reg32 *) RTC_SCB__RX_FIFO_STATUS)
#define RTC_RX_FIFO_STATUS_PTR     ( (reg32 *) RTC_SCB__RX_FIFO_STATUS)

#define RTC_RX_MATCH_REG           (*(reg32 *) RTC_SCB__RX_MATCH)
#define RTC_RX_MATCH_PTR           ( (reg32 *) RTC_SCB__RX_MATCH)

#define RTC_RX_FIFO_RD_REG         (*(reg32 *) RTC_SCB__RX_FIFO_RD)
#define RTC_RX_FIFO_RD_PTR         ( (reg32 *) RTC_SCB__RX_FIFO_RD)

#define RTC_RX_FIFO_RD_SILENT_REG  (*(reg32 *) RTC_SCB__RX_FIFO_RD_SILENT)
#define RTC_RX_FIFO_RD_SILENT_PTR  ( (reg32 *) RTC_SCB__RX_FIFO_RD_SILENT)

#define RTC_EZBUF_DATA00_REG       (*(reg32 *) RTC_SCB__EZ_DATA00)
#define RTC_EZBUF_DATA00_PTR       ( (reg32 *) RTC_SCB__EZ_DATA00)

#define RTC_INTR_CAUSE_REG         (*(reg32 *) RTC_SCB__INTR_CAUSE)
#define RTC_INTR_CAUSE_PTR         ( (reg32 *) RTC_SCB__INTR_CAUSE)

#define RTC_INTR_I2C_EC_REG        (*(reg32 *) RTC_SCB__INTR_I2C_EC)
#define RTC_INTR_I2C_EC_PTR        ( (reg32 *) RTC_SCB__INTR_I2C_EC)

#define RTC_INTR_I2C_EC_MASK_REG   (*(reg32 *) RTC_SCB__INTR_I2C_EC_MASK)
#define RTC_INTR_I2C_EC_MASK_PTR   ( (reg32 *) RTC_SCB__INTR_I2C_EC_MASK)

#define RTC_INTR_I2C_EC_MASKED_REG (*(reg32 *) RTC_SCB__INTR_I2C_EC_MASKED)
#define RTC_INTR_I2C_EC_MASKED_PTR ( (reg32 *) RTC_SCB__INTR_I2C_EC_MASKED)

#define RTC_INTR_SPI_EC_REG        (*(reg32 *) RTC_SCB__INTR_SPI_EC)
#define RTC_INTR_SPI_EC_PTR        ( (reg32 *) RTC_SCB__INTR_SPI_EC)

#define RTC_INTR_SPI_EC_MASK_REG   (*(reg32 *) RTC_SCB__INTR_SPI_EC_MASK)
#define RTC_INTR_SPI_EC_MASK_PTR   ( (reg32 *) RTC_SCB__INTR_SPI_EC_MASK)

#define RTC_INTR_SPI_EC_MASKED_REG (*(reg32 *) RTC_SCB__INTR_SPI_EC_MASKED)
#define RTC_INTR_SPI_EC_MASKED_PTR ( (reg32 *) RTC_SCB__INTR_SPI_EC_MASKED)

#define RTC_INTR_MASTER_REG        (*(reg32 *) RTC_SCB__INTR_M)
#define RTC_INTR_MASTER_PTR        ( (reg32 *) RTC_SCB__INTR_M)

#define RTC_INTR_MASTER_SET_REG    (*(reg32 *) RTC_SCB__INTR_M_SET)
#define RTC_INTR_MASTER_SET_PTR    ( (reg32 *) RTC_SCB__INTR_M_SET)

#define RTC_INTR_MASTER_MASK_REG   (*(reg32 *) RTC_SCB__INTR_M_MASK)
#define RTC_INTR_MASTER_MASK_PTR   ( (reg32 *) RTC_SCB__INTR_M_MASK)

#define RTC_INTR_MASTER_MASKED_REG (*(reg32 *) RTC_SCB__INTR_M_MASKED)
#define RTC_INTR_MASTER_MASKED_PTR ( (reg32 *) RTC_SCB__INTR_M_MASKED)

#define RTC_INTR_SLAVE_REG         (*(reg32 *) RTC_SCB__INTR_S)
#define RTC_INTR_SLAVE_PTR         ( (reg32 *) RTC_SCB__INTR_S)

#define RTC_INTR_SLAVE_SET_REG     (*(reg32 *) RTC_SCB__INTR_S_SET)
#define RTC_INTR_SLAVE_SET_PTR     ( (reg32 *) RTC_SCB__INTR_S_SET)

#define RTC_INTR_SLAVE_MASK_REG    (*(reg32 *) RTC_SCB__INTR_S_MASK)
#define RTC_INTR_SLAVE_MASK_PTR    ( (reg32 *) RTC_SCB__INTR_S_MASK)

#define RTC_INTR_SLAVE_MASKED_REG  (*(reg32 *) RTC_SCB__INTR_S_MASKED)
#define RTC_INTR_SLAVE_MASKED_PTR  ( (reg32 *) RTC_SCB__INTR_S_MASKED)

#define RTC_INTR_TX_REG            (*(reg32 *) RTC_SCB__INTR_TX)
#define RTC_INTR_TX_PTR            ( (reg32 *) RTC_SCB__INTR_TX)

#define RTC_INTR_TX_SET_REG        (*(reg32 *) RTC_SCB__INTR_TX_SET)
#define RTC_INTR_TX_SET_PTR        ( (reg32 *) RTC_SCB__INTR_TX_SET)

#define RTC_INTR_TX_MASK_REG       (*(reg32 *) RTC_SCB__INTR_TX_MASK)
#define RTC_INTR_TX_MASK_PTR       ( (reg32 *) RTC_SCB__INTR_TX_MASK)

#define RTC_INTR_TX_MASKED_REG     (*(reg32 *) RTC_SCB__INTR_TX_MASKED)
#define RTC_INTR_TX_MASKED_PTR     ( (reg32 *) RTC_SCB__INTR_TX_MASKED)

#define RTC_INTR_RX_REG            (*(reg32 *) RTC_SCB__INTR_RX)
#define RTC_INTR_RX_PTR            ( (reg32 *) RTC_SCB__INTR_RX)

#define RTC_INTR_RX_SET_REG        (*(reg32 *) RTC_SCB__INTR_RX_SET)
#define RTC_INTR_RX_SET_PTR        ( (reg32 *) RTC_SCB__INTR_RX_SET)

#define RTC_INTR_RX_MASK_REG       (*(reg32 *) RTC_SCB__INTR_RX_MASK)
#define RTC_INTR_RX_MASK_PTR       ( (reg32 *) RTC_SCB__INTR_RX_MASK)

#define RTC_INTR_RX_MASKED_REG     (*(reg32 *) RTC_SCB__INTR_RX_MASKED)
#define RTC_INTR_RX_MASKED_PTR     ( (reg32 *) RTC_SCB__INTR_RX_MASKED)


/***************************************
*        Registers Constants
***************************************/

/* RTC_CTRL */
#define RTC_CTRL_OVS_POS           (0u)  /* [3:0]   Oversampling factor                 */
#define RTC_CTRL_EC_AM_MODE_POS    (8u)  /* [8]     Externally clocked address match    */
#define RTC_CTRL_EC_OP_MODE_POS    (9u)  /* [9]     Externally clocked operation mode   */
#define RTC_CTRL_EZBUF_MODE_POS    (10u) /* [10]    EZ buffer is enabled                */
#define RTC_CTRL_ADDR_ACCEPT_POS   (16u) /* [16]    Put matched address in RX FIFO      */
#define RTC_CTRL_BLOCK_POS         (17u) /* [17]    Ext and Int logic to resolve colide */
#define RTC_CTRL_MODE_POS          (24u) /* [25:24] Operation mode                      */
#define RTC_CTRL_ENABLED_POS       (31u) /* [31]    Enable SCB block                    */
#define RTC_CTRL_OVS_MASK          ((uint32) 0x0Fu)
#define RTC_CTRL_EC_AM_MODE        ((uint32) ((uint32) 0x01u << RTC_CTRL_EC_AM_MODE_POS))
#define RTC_CTRL_EC_OP_MODE        ((uint32) ((uint32) 0x01u << RTC_CTRL_EC_OP_MODE_POS))
#define RTC_CTRL_EZBUF_MODE        ((uint32) ((uint32) 0x01u << RTC_CTRL_EZBUF_MODE_POS))
#define RTC_CTRL_ADDR_ACCEPT       ((uint32) ((uint32) 0x01u << RTC_CTRL_ADDR_ACCEPT_POS))
#define RTC_CTRL_BLOCK             ((uint32) ((uint32) 0x01u << RTC_CTRL_BLOCK_POS))
#define RTC_CTRL_MODE_MASK         ((uint32) ((uint32) 0x03u << RTC_CTRL_MODE_POS))
#define RTC_CTRL_MODE_I2C          ((uint32)  0x00u)
#define RTC_CTRL_MODE_SPI          ((uint32) ((uint32) 0x01u << RTC_CTRL_MODE_POS))
#define RTC_CTRL_MODE_UART         ((uint32) ((uint32) 0x02u << RTC_CTRL_MODE_POS))
#define RTC_CTRL_ENABLED           ((uint32) ((uint32) 0x01u << RTC_CTRL_ENABLED_POS))


/* RTC_STATUS_REG */
#define RTC_STATUS_EC_BUSY_POS     (0u)  /* [0] Bus busy. Externaly clocked loigc access to EZ memory */
#define RTC_STATUS_EC_BUSY         ((uint32) 0x0Fu)


/* RTC_SPI_CTRL_REG  */
#define RTC_SPI_CTRL_CONTINUOUS_POS        (0u)  /* [0]     Continuous or Separated SPI data transfers */
#define RTC_SPI_CTRL_SELECT_PRECEDE_POS    (1u)  /* [1]     Precedes or coincides start of data frame  */
#define RTC_SPI_CTRL_CPHA_POS              (2u)  /* [2]     SCLK phase                                 */
#define RTC_SPI_CTRL_CPOL_POS              (3u)  /* [3]     SCLK polarity                              */
#define RTC_SPI_CTRL_LATE_MISO_SAMPLE_POS  (4u)  /* [4]     Late MISO sample enabled                   */
#define RTC_SPI_CTRL_LOOPBACK_POS          (16u) /* [16]    Local loopback control enabled             */
#define RTC_SPI_CTRL_MODE_POS              (24u) /* [25:24] Submode of SPI operation                   */
#define RTC_SPI_CTRL_SLAVE_SELECT_POS      (26u) /* [27:26] Selects SPI SS signal                      */
#define RTC_SPI_CTRL_MASTER_MODE_POS       (31u) /* [31]    Master mode enabled                        */
#define RTC_SPI_CTRL_CONTINUOUS            ((uint32) 0x01u)
#define RTC_SPI_CTRL_SELECT_PRECEDE        ((uint32) ((uint32) 0x01u << \
                                                                    RTC_SPI_CTRL_SELECT_PRECEDE_POS))
#define RTC_SPI_CTRL_SCLK_MODE_MASK        ((uint32) ((uint32) 0x03u << \
                                                                    RTC_SPI_CTRL_CPHA_POS))
#define RTC_SPI_CTRL_CPHA                  ((uint32) ((uint32) 0x01u << \
                                                                    RTC_SPI_CTRL_CPHA_POS))
#define RTC_SPI_CTRL_CPOL                  ((uint32) ((uint32) 0x01u << \
                                                                    RTC_SPI_CTRL_CPOL_POS))
#define RTC_SPI_CTRL_LATE_MISO_SAMPLE      ((uint32) ((uint32) 0x01u << \
                                                                    RTC_SPI_CTRL_LATE_MISO_SAMPLE_POS))
#define RTC_SPI_CTRL_LOOPBACK              ((uint32) ((uint32) 0x01u << \
                                                                    RTC_SPI_CTRL_LOOPBACK_POS))
#define RTC_SPI_CTRL_MODE_MASK             ((uint32) ((uint32) 0x03u << \
                                                                    RTC_SPI_CTRL_MODE_POS))
#define RTC_SPI_CTRL_MODE_MOTOROLA         ((uint32) 0x00u)
#define RTC_SPI_CTRL_MODE_TI               ((uint32) ((uint32) 0x01u << RTC_CTRL_MODE_POS))
#define RTC_SPI_CTRL_MODE_NS               ((uint32) ((uint32) 0x02u << RTC_CTRL_MODE_POS))
#define RTC_SPI_CTRL_SLAVE_SELECT_MASK     ((uint32) ((uint32) 0x03u << \
                                                                    RTC_SPI_CTRL_SLAVE_SELECT_POS))
#define RTC_SPI_CTRL_SLAVE_SELECT0         ((uint32) 0x00u)
#define RTC_SPI_CTRL_SLAVE_SELECT1         ((uint32) ((uint32) 0x01u << \
                                                                    RTC_SPI_CTRL_SLAVE_SELECT_POS))
#define RTC_SPI_CTRL_SLAVE_SELECT2         ((uint32) ((uint32) 0x02u << \
                                                                    RTC_SPI_CTRL_SLAVE_SELECT_POS))
#define RTC_SPI_CTRL_SLAVE_SELECT3         ((uint32) ((uint32) 0x03u << \
                                                                    RTC_SPI_CTRL_SLAVE_SELECT_POS))
#define RTC_SPI_CTRL_MASTER                ((uint32) ((uint32) 0x01u << \
                                                                    RTC_SPI_CTRL_MASTER_MODE_POS))
#define RTC_SPI_CTRL_SLAVE                 ((uint32) 0x00u)


/* RTC_SPI_STATUS_REG  */
#define RTC_SPI_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy - slave selected */
#define RTC_SPI_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EzAddress                 */
#define RTC_SPI_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define RTC_SPI_STATUS_EZBUF_ADDR_MASK    ((uint32) ((uint32) 0xFFu << \
                                                                    RTC_I2C_STATUS_EZBUF_ADDR_POS))


/* RTC_UART_CTRL */
#define RTC_UART_CTRL_LOOPBACK_POS         (16u) /* [16] Loopback     */
#define RTC_UART_CTRL_MODE_POS             (24u) /* [24] UART subMode */
#define RTC_UART_CTRL_LOOPBACK             ((uint32) ((uint32) 0x01u << \
                                                                        RTC_UART_CTRL_LOOPBACK_POS))
#define RTC_UART_CTRL_MODE_UART_STD        ((uint32) 0x00u)
#define RTC_UART_CTRL_MODE_UART_SMARTCARD  ((uint32) ((uint32) 0x01u << \
                                                                        RTC_UART_CTRL_MODE_POS))
#define RTC_UART_CTRL_MODE_UART_IRDA       ((uint32) ((uint32) 0x02u << \
                                                                        RTC_UART_CTRL_MODE_POS))
#define RTC_UART_CTRL_MODE_MASK            ((uint32) ((uint32) 0x03u << \
                                                                        RTC_UART_CTRL_MODE_POS))


/* RTC_UART_TX_CTRL */
#define RTC_UART_TX_CTRL_STOP_BITS_POS         (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period */
#define RTC_UART_TX_CTRL_PARITY_POS            (4u)  /* [4]   Parity bit                              */
#define RTC_UART_TX_CTRL_PARITY_ENABLED_POS    (5u)  /* [5]   Parity enable                           */
#define RTC_UART_TX_CTRL_RETRY_ON_NACK_POS     (8u)  /* [8]   Smart Card: re-send frame on NACK       */
#define RTC_UART_TX_CTRL_ONE_STOP_BIT          ((uint32) 0x01u)
#define RTC_UART_TX_CTRL_ONE_HALF_STOP_BITS    ((uint32) 0x02u)
#define RTC_UART_TX_CTRL_TWO_STOP_BITS         ((uint32) 0x03u)
#define RTC_UART_TX_CTRL_STOP_BITS_MASK        ((uint32) 0x07u)
#define RTC_UART_TX_CTRL_PARITY                ((uint32) ((uint32) 0x01u << \
                                                                    RTC_UART_TX_CTRL_PARITY_POS))
#define RTC_UART_TX_CTRL_PARITY_ENABLED        ((uint32) ((uint32) 0x01u << \
                                                                    RTC_UART_TX_CTRL_PARITY_ENABLED_POS))
#define RTC_UART_TX_CTRL_RETRY_ON_NACK         ((uint32) ((uint32) 0x01u << \
                                                                    RTC_UART_TX_CTRL_RETRY_ON_NACK_POS))


/* RTC_UART_RX_CTRL */
#define RTC_UART_RX_CTRL_STOP_BITS_POS             (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 prd   */
#define RTC_UART_RX_CTRL_PARITY_POS                (4u)  /* [4]   Parity bit                             */
#define RTC_UART_RX_CTRL_PARITY_ENABLED_POS        (5u)  /* [5]   Parity enable                          */
#define RTC_UART_RX_CTRL_POLARITY_POS              (6u)  /* [6]   IrDA: inverts polarity of RX signal    */
#define RTC_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS    (8u)  /* [8]   Drop and lost RX FIFO on parity error  */
#define RTC_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS     (9u)  /* [9]   Drop and lost RX FIFO on frame error   */
#define RTC_UART_RX_CTRL_MP_MODE_POS               (10u) /* [10]  Multi-processor mode                   */
#define RTC_UART_RX_CTRL_LIN_MODE_POS              (12u) /* [12]  Lin mode: applicable for UART Standart */
#define RTC_UART_RX_CTRL_SKIP_START_POS            (13u) /* [13]  Skip start not: only for UART Standart */
#define RTC_UART_RX_CTRL_BREAK_WIDTH_POS           (16u) /* [19:16]  Break width: (Break width + 1)      */
#define RTC_UART_TX_CTRL_ONE_STOP_BIT              ((uint32) 0x01u)
#define RTC_UART_TX_CTRL_ONE_HALF_STOP_BITS        ((uint32) 0x02u)
#define RTC_UART_TX_CTRL_TWO_STOP_BITS             ((uint32) 0x03u)
#define RTC_UART_RX_CTRL_STOP_BITS_MASK            ((uint32) 0x07u)
#define RTC_UART_RX_CTRL_PARITY                    ((uint32) ((uint32) 0x01u << \
                                                                    RTC_UART_RX_CTRL_PARITY_POS))
#define RTC_UART_RX_CTRL_PARITY_ENABLED            ((uint32) ((uint32) 0x01u << \
                                                                    RTC_UART_RX_CTRL_PARITY_ENABLED_POS))
#define RTC_UART_RX_CTRL_POLARITY                  ((uint32) ((uint32) 0x01u << \
                                                                    RTC_UART_RX_CTRL_POLARITY_POS))
#define RTC_UART_RX_CTRL_DROP_ON_PARITY_ERR        ((uint32) ((uint32) 0x01u << \
                                                                RTC_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS))
#define RTC_UART_RX_CTRL_DROP_ON_FRAME_ERR         ((uint32) ((uint32) 0x01u << \
                                                                RTC_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS))
#define RTC_UART_RX_CTRL_MP_MODE                   ((uint32) ((uint32) 0x01u << \
                                                                    RTC_UART_RX_CTRL_MP_MODE_POS))
#define RTC_UART_RX_CTRL_LIN_MODE                  ((uint32) ((uint32) 0x01u << \
                                                                    RTC_UART_RX_CTRL_LIN_MODE_POS))
#define RTC_UART_RX_CTRL_SKIP_START                ((uint32) ((uint32) 0x01u << \
                                                                  RTC_UART_RX_CTRL_SKIP_START_POS))
#define RTC_UART_RX_CTRL_BREAK_WIDTH_MASK          ((uint32) ((uint32) 0x0Fu << \
                                                                  RTC_UART_RX_CTRL_BREAK_WIDTH_POS))

/* RTC_UART_RX_STATUS_REG */
#define RTC_UART_RX_STATUS_BR_COUNTER_POS     (0u)  /* [11:0] Baute Rate counter */
#define RTC_UART_RX_STATUS_BR_COUNTER_MASK    ((uint32) 0xFFFu)


/* RTC_I2C_CTRL */
#define RTC_I2C_CTRL_HIGH_PHASE_OVS_POS           (0u)   /* [3:0] Oversampling factor high: masrer only */
#define RTC_I2C_CTRL_LOW_PHASE_OVS_POS            (4u)   /* [7:4] Oversampling factor low:  masrer only */
#define RTC_I2C_CTRL_M_READY_DATA_ACK_POS         (8u)   /* [8]   Master ACKs data wgile RX FIFO != FULL*/
#define RTC_I2C_CTRL_M_NOT_READY_DATA_NACK_POS    (9u)   /* [9]   Master NACKs data if RX FIFO ==  FULL */
#define RTC_I2C_CTRL_S_GENERAL_IGNORE_POS         (11u)  /* [11]  Slave ignores General call            */
#define RTC_I2C_CTRL_S_READY_ADDR_ACK_POS         (12u)  /* [12]  Slave ACKs Address if RX FIFO != FULL */
#define RTC_I2C_CTRL_S_READY_DATA_ACK_POS         (13u)  /* [13]  Slave ACKs data while RX FIFO == FULL */
#define RTC_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS    (14u)  /* [14]  Slave NACKs address if RX FIFO == FULL*/
#define RTC_I2C_CTRL_S_NOT_READY_DATA_NACK_POS    (15u)  /* [15]  Slave NACKs data if RX FIFO is  FULL  */
#define RTC_I2C_CTRL_LOOPBACK_POS                 (16u)  /* [16]  Loopback                              */
#define RTC_I2C_CTRL_SLAVE_MODE_POS               (30u)  /* [30]  Slave mode enabled                    */
#define RTC_I2C_CTRL_MASTER_MODE_POS              (31u)  /* [31]  Master mode enabled                   */
#define RTC_I2C_CTRL_HIGH_PHASE_OVS_MASK  ((uint32) 0x0Fu)
#define RTC_I2C_CTRL_LOW_PHASE_OVS_MASK   ((uint32) ((uint32) 0x0Fu << \
                                                                RTC_I2C_CTRL_LOW_PHASE_OVS_POS))
#define RTC_I2C_CTRL_M_READY_DATA_ACK      ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_CTRL_M_READY_DATA_ACK_POS))
#define RTC_I2C_CTRL_M_NOT_READY_DATA_NACK ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_CTRL_M_NOT_READY_DATA_NACK_POS))
#define RTC_I2C_CTRL_S_GENERAL_IGNORE      ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_CTRL_S_GENERAL_IGNORE_POS))
#define RTC_I2C_CTRL_S_READY_ADDR_ACK      ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_CTRL_S_READY_ADDR_ACK_POS))
#define RTC_I2C_CTRL_S_READY_DATA_ACK      ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_CTRL_S_READY_DATA_ACK_POS))
#define RTC_I2C_CTRL_S_NOT_READY_ADDR_NACK ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS))
#define RTC_I2C_CTRL_S_NOT_READY_DATA_NACK ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_CTRL_S_NOT_READY_DATA_NACK_POS))
#define RTC_I2C_CTRL_LOOPBACK              ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_CTRL_LOOPBACK_POS))
#define RTC_I2C_CTRL_SLAVE_MODE            ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_CTRL_SLAVE_MODE_POS))
#define RTC_I2C_CTRL_MASTER_MODE           ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_CTRL_MASTER_MODE_POS))
#define RTC_I2C_CTRL_SLAVE_MASTER_MODE_MASK    ((uint32) ((uint32) 0x03u << \
                                                                RTC_I2C_CTRL_SLAVE_MODE_POS))


/* RTC_I2C_STATUS_REG  */
#define RTC_I2C_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy: internally clocked */
#define RTC_I2C_STATUS_S_READ_POS      (4u)  /* [4]    Slave is read by master      */
#define RTC_I2C_STATUS_M_READ_POS      (5u)  /* [5]    Master reads Slave           */
#define RTC_I2C_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EZAddress                    */
#define RTC_I2C_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define RTC_I2C_STATUS_S_READ          ((uint32) ((uint32) 0x01u << \
                                                                    RTC_I2C_STATUS_S_READ_POS))
#define RTC_I2C_STATUS_M_READ          ((uint32) ((uint32) 0x01u << \
                                                                    RTC_I2C_STATUS_M_READ_POS))
#define RTC_I2C_STATUS_EZBUF_ADDR_MASK ((uint32) ((uint32) 0xFFu << \
                                                                    RTC_I2C_STATUS_EZBUF_ADDR_POS))


/* RTC_I2C_MASTER_CMD_REG */
#define RTC_I2C_MASTER_CMD_M_START_POS             (0u)  /* [0] Master generate Start                */
#define RTC_I2C_MASTER_CMD_M_START_ON_IDLE_POS     (1u)  /* [1] Master generate Start if bus is free */
#define RTC_I2C_MASTER_CMD_M_ACK_POS               (2u)  /* [2] Master generate ACK                  */
#define RTC_I2C_MASTER_CMD_M_NACK_POS              (3u)  /* [3] Master generate NACK                 */
#define RTC_I2C_MASTER_CMD_M_STOP_POS              (4u)  /* [4] Master generate Stop                 */
#define RTC_I2C_MASTER_CMD_M_START         ((uint32) 0x01u)
#define RTC_I2C_MASTER_CMD_M_START_ON_IDLE ((uint32) ((uint32) 0x01u << \
                                                                   RTC_I2C_MASTER_CMD_M_START_ON_IDLE_POS))
#define RTC_I2C_MASTER_CMD_M_ACK           ((uint32) ((uint32) 0x01u << \
                                                                   RTC_I2C_MASTER_CMD_M_ACK_POS))
#define RTC_I2C_MASTER_CMD_M_NACK          ((uint32) ((uint32) 0x01u << \
                                                                    RTC_I2C_MASTER_CMD_M_NACK_POS))
#define RTC_I2C_MASTER_CMD_M_STOP          ((uint32) ((uint32) 0x01u << \
                                                                    RTC_I2C_MASTER_CMD_M_STOP_POS))


/* RTC_I2C_SLAVE_CMD_REG  */
#define RTC_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define RTC_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define RTC_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define RTC_I2C_SLAVE_CMD_S_NACK       ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_SLAVE_CMD_S_NACK_POS))

#define RTC_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define RTC_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define RTC_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define RTC_I2C_SLAVE_CMD_S_NACK       ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_SLAVE_CMD_S_NACK_POS))
/* RTC_I2C_CFG  */
#define RTC_I2C_CFG_SDA_FILT_HYS_POS           (0u)  /* [1:0]   Trim bits for the I2C SDA filter         */
#define RTC_I2C_CFG_SDA_FILT_TRIM_POS          (2u)  /* [3:2]   Trim bits for the I2C SDA filter         */
#define RTC_I2C_CFG_SCL_FILT_HYS_POS           (4u)  /* [5:4]   Trim bits for the I2C SCL filter         */
#define RTC_I2C_CFG_SCL_FILT_TRIM_POS          (6u)  /* [7:6]   Trim bits for the I2C SCL filter         */
#define RTC_I2C_CFG_SDA_FILT_OUT_HYS_POS       (8u)  /* [9:8]   Trim bits for I2C SDA filter output path */
#define RTC_I2C_CFG_SDA_FILT_OUT_TRIM_POS      (10u) /* [11:10] Trim bits for I2C SDA filter output path */
#define RTC_I2C_CFG_SDA_FILT_HS_POS            (16u) /* [16]    '0': 50 ns filter, '1': 10 ns filter     */
#define RTC_I2C_CFG_SDA_FILT_ENABLED_POS       (17u) /* [17]    I2C SDA filter enabled                   */
#define RTC_I2C_CFG_SCL_FILT_HS_POS            (24u) /* [24]    '0': 50 ns filter, '1': 10 ns filter     */
#define RTC_I2C_CFG_SCL_FILT_ENABLED_POS       (25u) /* [25]    I2C SCL filter enabled                   */
#define RTC_I2C_CFG_SDA_FILT_OUT_HS_POS        (26u) /* [26]    '0': 50ns filter, '1': 10 ns filter      */
#define RTC_I2C_CFG_SDA_FILT_OUT_ENABLED_POS   (27u) /* [27]    I2C SDA output delay filter enabled      */
#define RTC_I2C_CFG_SDA_FILT_HYS_MASK          ((uint32) 0x00u)
#define RTC_I2C_CFG_SDA_FILT_TRIM_MASK         ((uint32) ((uint32) 0x03u << \
                                                                RTC_I2C_CFG_SDA_FILT_TRIM_POS))
#define RTC_I2C_CFG_SCL_FILT_HYS_MASK          ((uint32) ((uint32) 0x03u << \
                                                                RTC_I2C_CFG_SCL_FILT_HYS_POS))
#define RTC_I2C_CFG_SCL_FILT_TRIM_MASK         ((uint32) ((uint32) 0x03u << \
                                                                RTC_I2C_CFG_SCL_FILT_TRIM_POS))
#define RTC_I2C_CFG_SDA_FILT_OUT_HYS_MASK      ((uint32) ((uint32) 0x03u << \
                                                                RTC_I2C_CFG_SDA_FILT_OUT_HYS_POS))
#define RTC_I2C_CFG_SDA_FILT_OUT_TRIM_MASK     ((uint32) ((uint32) 0x03u << \
                                                                RTC_I2C_CFG_SDA_FILT_OUT_TRIM_POS))
#define RTC_I2C_CFG_SDA_FILT_HS                ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_CFG_SDA_FILT_HS_POS))
#define RTC_I2C_CFG_SDA_FILT_ENABLED           ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_CFG_SDA_FILT_ENABLED_POS))
#define RTC_I2C_CFG_SCL_FILT_HS                ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_CFG_SCL_FILT_HS_POS))
#define RTC_I2C_CFG_SCL_FILT_ENABLED           ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_CFG_SCL_FILT_ENABLED_POS))
#define RTC_I2C_CFG_SDA_FILT_OUT_HS            ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_CFG_SDA_FILT_OUT_HS_POS))
#define RTC_I2C_CFG_SDA_FILT_OUT_ENABLED       ((uint32) ((uint32) 0x01u << \
                                                                RTC_I2C_CFG_SDA_FILT_OUT_ENABLED_POS))


/* RTC_TX_CTRL_REG */
#define RTC_TX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Dataframe width: (Data width - 1) */
#define RTC_TX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define RTC_TX_CTRL_ENABLED_POS        (31u) /* [31]  Transmitter enabled               */
#define RTC_TX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define RTC_TX_CTRL_MSB_FIRST          ((uint32) ((uint32) 0x01u << \
                                                                        RTC_TX_CTRL_MSB_FIRST_POS))
#define RTC_TX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define RTC_TX_CTRL_ENABLED            ((uint32) ((uint32) 0x01u << RTC_TX_CTRL_ENABLED_POS))


/* RTC_TX_CTRL_FIFO_REG */
#define RTC_TX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)  /* [2:0] Trigger level                              */
#define RTC_TX_FIFO_CTRL_CLEAR_POS             (16u) /* [16]  Clear TX FIFO: claared after set           */
#define RTC_TX_FIFO_CTRL_FREEZE_POS            (17u) /* [17]  Freeze TX FIFO: HW do not inc read pointer */
#define RTC_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) 0x07u)
#define RTC_TX_FIFO_CTRL_CLEAR                 ((uint32) ((uint32) 0x01u << \
                                                                    RTC_TX_FIFO_CTRL_CLEAR_POS))
#define RTC_TX_FIFO_CTRL_FREEZE                ((uint32) ((uint32) 0x01u << \
                                                                    RTC_TX_FIFO_CTRL_FREEZE_POS))


/* RTC_TX_FIFO_STATUS_REG */
#define RTC_TX_FIFO_STATUS_USED_POS    (0u)  /* [3:0]   Amount of entries in TX FIFO */
#define RTC_TX_FIFO_SR_VALID_POS       (15u) /* [15]    Shifter status of TX FIFO    */
#define RTC_TX_FIFO_STATUS_RD_PTR_POS  (16u) /* [18:16] TX FIFO read pointer         */
#define RTC_TX_FIFO_STATUS_WR_PTR_POS  (24u) /* [26:24] TX FIFO write pointer        */
#define RTC_TX_FIFO_STATUS_USED_MASK   ((uint32) 0x0Fu)
#define RTC_TX_FIFO_SR_VALID           ((uint32) ((uint32) 0x01u << \
                                                                    RTC_TX_FIFO_SR_VALID_POS))
#define RTC_TX_FIFO_STATUS_RD_PTR_MASK ((uint32) ((uint32) 0x07u << \
                                                                    RTC_TX_FIFO_STATUS_RD_PTR_POS))
#define RTC_TX_FIFO_STATUS_WR_PTR_MASK ((uint32) ((uint32) 0x07u << \
                                                                    RTC_TX_FIFO_STATUS_WR_PTR_POS))


/* RTC_TX_FIFO_WR_REG */
#define RTC_TX_FIFO_WR_POS    (0u)  /* [15:0] Data written into TX FIFO */
#define RTC_TX_FIFO_WR_MASK   ((uint32) 0xFFu)


/* RTC_RX_CTRL_REG */
#define RTC_RX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Dataframe width: (Data width - 1) */
#define RTC_RX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define RTC_RX_CTRL_MEDIAN_POS         (9u)  /* [9]   Median filter                     */
#define RTC_RX_CTRL_ENABLED_POS        (31u) /* [31]  Receiver enabled                  */
#define RTC_RX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define RTC_RX_CTRL_MSB_FIRST          ((uint32) ((uint32) 0x01u << \
                                                                        RTC_RX_CTRL_MSB_FIRST_POS))
#define RTC_RX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define RTC_RX_CTRL_MEDIAN             ((uint32) ((uint32) 0x01u << RTC_RX_CTRL_MEDIAN_POS))
#define RTC_RX_CTRL_ENABLED            ((uint32) ((uint32) 0x01u << RTC_RX_CTRL_ENABLED_POS))


/* RTC_RX_FIFO_CTRL_REG */
#define RTC_RX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)   /* [2:0] Trigger level                            */
#define RTC_RX_FIFO_CTRL_CLEAR_POS             (16u)  /* [16]  Clear RX FIFO: claar after set           */
#define RTC_RX_FIFO_CTRL_FREEZE_POS            (17u)  /* [17]  Freeze RX FIFO: HW writes has not effect */
#define RTC_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) 0x07u)
#define RTC_RX_FIFO_CTRL_CLEAR                 ((uint32) ((uint32) 0x01u << \
                                                                    RTC_RX_FIFO_CTRL_CLEAR_POS))
#define RTC_RX_FIFO_CTRL_FREEZE                ((uint32) ((uint32) 0x01u << \
                                                                    RTC_RX_FIFO_CTRL_FREEZE_POS))


/* RTC_RX_FIFO_STATUS_REG */
#define RTC_RX_FIFO_STATUS_USED_POS    (0u)   /* [3:0]   Amount of entries in RX FIFO */
#define RTC_RX_FIFO_SR_VALID_POS       (15u)  /* [15]    Shifter status of RX FIFO    */
#define RTC_RX_FIFO_STATUS_RD_PTR_POS  (16u)  /* [18:16] RX FIFO read pointer         */
#define RTC_RX_FIFO_STATUS_WR_PTR_POS  (24u)  /* [26:24] RX FIFO write pointer        */
#define RTC_RX_FIFO_STATUS_USED_MASK   ((uint32) 0x0Fu)
#define RTC_RX_FIFO_SR_VALID           ((uint32) ((uint32) 0x01u << \
                                                                  RTC_RX_FIFO_SR_VALID_POS))
#define RTC_RX_FIFO_STATUS_RD_PTR_MASK ((uint32) ((uint32) 0x07u << \
                                                                  RTC_RX_FIFO_STATUS_RD_PTR_POS))
#define RTC_RX_FIFO_STATUS_WR_PTR_MASK ((uint32) ((uint32) 0x07u << \
                                                                  RTC_RX_FIFO_STATUS_WR_PTR_POS))


/* RTC_RX_MATCH_REG */
#define RTC_RX_MATCH_ADDR_POS     (0u)  /* [7:0]   Slave address                        */
#define RTC_RX_MATCH_MASK_POS     (16u) /* [23:16] Slave address mask: 0 - doesn't care */
#define RTC_RX_MATCH_ADDR_MASK    ((uint32) 0xFFu)
#define RTC_RX_MATCH_MASK_MASK    ((uint32) ((uint32) 0xFFu << RTC_RX_MATCH_MASK_POS))


/* RTC_RX_FIFO_WR_REG */
#define RTC_RX_FIFO_RD_POS    (0u)  /* [15:0] Data read from RX FIFO */
#define RTC_RX_FIFO_RD_MASK   ((uint32) 0xFFu)


/* RTC_RX_FIFO_RD_SILENT_REG */
#define RTC_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define RTC_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* RTC_RX_FIFO_RD_SILENT_REG */
#define RTC_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define RTC_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* RTC_EZBUF_DATA_REG */
#define RTC_EZBUF_DATA_POS   (0u)  /* [7:0] Data from Ez Memory */
#define RTC_EZBUF_DATA_MASK  ((uint32) 0xFFu)

/*  RTC_INTR_CAUSE_REG */
#define RTC_INTR_CAUSE_MASTER_POS  (0u)  /* [0] Master interrupt active                 */
#define RTC_INTR_CAUSE_SLAVE_POS   (1u)  /* [1] Slave interrupt active                  */
#define RTC_INTR_CAUSE_TX_POS      (2u)  /* [2] Transmitter interrupt active            */
#define RTC_INTR_CAUSE_RX_POS      (3u)  /* [3] Receiver interrupt active               */
#define RTC_INTR_CAUSE_I2C_EC_POS  (4u)  /* [4] Externally clock I2C interrupt active   */
#define RTC_INTR_CAUSE_SPI_EC_POS  (5u)  /* [5] Externally clocked SPI interrupt active */
#define RTC_INTR_CAUSE_MASTER      ((uint32) 0x01u)
#define RTC_INTR_CAUSE_SLAVE       ((uint32) ((uint32) 0x01u << RTC_INTR_CAUSE_SLAVE_POS))
#define RTC_INTR_CAUSE_TX          ((uint32) ((uint32) 0x01u << RTC_INTR_CAUSE_TX_POS))
#define RTC_INTR_CAUSE_RX          ((uint32) ((uint32) 0x01u << RTC_INTR_CAUSE_RX_POS))
#define RTC_INTR_CAUSE_I2C_EC      ((uint32) ((uint32) 0x01u << RTC_INTR_CAUSE_I2C_EC_POS))
#define RTC_INTR_CAUSE_SPI_EC      ((uint32) ((uint32) 0x01u << RTC_INTR_CAUSE_SPI_EC_POS))


/* RTC_INTR_SPI_EC_REG, RTC_INTR_SPI_EC_MASK_REG, RTC_INTR_SPI_EC_MASKED_REG */
#define RTC_INTR_SPI_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define RTC_INTR_SPI_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define RTC_INTR_SPI_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define RTC_INTR_SPI_EC_WAKE_UP              ((uint32) 0x01u)
#define RTC_INTR_SPI_EC_EZBUF_STOP           ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_SPI_EC_EZBUF_STOP_POS))
#define RTC_INTR_SPI_EC_EZBUF_WRITE_STOP     ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_SPI_EC_EZBUF_WRITE_STOP_POS))


/* RTC_INTR_I2C_EC, RTC_INTR_I2C_EC_MASK, RTC_INTR_I2C_EC_MASKED */
#define RTC_INTR_I2C_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define RTC_INTR_I2C_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define RTC_INTR_I2C_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define RTC_INTR_I2C_EC_WAKE_UP              ((uint32) 0x01u)
#define RTC_INTR_I2C_EC_EZBUF_STOP           ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_I2C_EC_EZBUF_STOP_POS))
#define RTC_INTR_I2C_EC_EZBUF_WRITE_STOP     ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_I2C_EC_EZBUF_WRITE_STOP_POS))


/* RTC_INTR_MASTER, RTC_INTR_MASTER_SET,
   RTC_INTR_MASTER_MASK, RTC_INTR_MASTER_MASKED */
#define RTC_INTR_MASTER_I2C_ARB_LOST_POS   (0u)  /* [0] Master lost arbitration                          */
#define RTC_INTR_MASTER_I2C_NACK_POS       (1u)  /* [1] Master receives NACK: address or write to slave  */
#define RTC_INTR_MASTER_I2C_ACK_POS        (2u)  /* [2] Master receives NACK: address or write to slave  */
#define RTC_INTR_MASTER_I2C_STOP_POS       (4u)  /* [4] Master detects the Stop: only self generated Stop*/
#define RTC_INTR_MASTER_I2C_BUS_ERROR_POS  (8u)  /* [8] Master detects bus error: misplaced Start or Stop*/
#define RTC_INTR_MASTER_SPI_DONE_POS       (9u)  /* [9] Master complete trasfer: Only for SPI            */
#define RTC_INTR_MASTER_I2C_ARB_LOST       ((uint32) 0x01u)
#define RTC_INTR_MASTER_I2C_NACK           ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_MASTER_I2C_NACK_POS))
#define RTC_INTR_MASTER_I2C_ACK            ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_MASTER_I2C_ACK_POS))
#define RTC_INTR_MASTER_I2C_STOP           ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_MASTER_I2C_STOP_POS))
#define RTC_INTR_MASTER_I2C_BUS_ERROR      ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_MASTER_I2C_BUS_ERROR_POS))
#define RTC_INTR_MASTER_SPI_DONE           ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_MASTER_SPI_DONE_POS))

/*
* RTC_INTR_SLAVE, RTC_INTR_SLAVE_SET,
* RTC_INTR_SLAVE_MASK, RTC_INTR_SLAVE_MASKED
*/
#define RTC_INTR_SLAVE_I2C_ARB_LOST_POS         (0u)  /* [0]  Slave lost arbitration                   */
#define RTC_INTR_SLAVE_I2C_NACK_POS             (1u)  /* [1]  Slave receives NACK: master reads data   */
#define RTC_INTR_SLAVE_I2C_ACK_POS              (2u)  /* [2]  Slave receives ACK: master reads data    */
#define RTC_INTR_SLAVE_I2C_WRITE_STOP_POS       (3u)  /* [3]  Slave detects end of write transaction   */
#define RTC_INTR_SLAVE_I2C_STOP_POS             (4u)  /* [4]  Slave detects end of transaction intened */
#define RTC_INTR_SLAVE_I2C_START_POS            (5u)  /* [5]  Slave detects Start                      */
#define RTC_INTR_SLAVE_I2C_ADDR_MATCH_POS       (6u)  /* [6]  Slave address matches                    */
#define RTC_INTR_SLAVE_I2C_GENERAL_POS          (7u)  /* [7]  General call received                    */
#define RTC_INTR_SLAVE_I2C_BUS_ERROR_POS        (8u)  /* [8]  Slave detects bus error                  */
#define RTC_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS (9u)  /* [9]  Slave write complete: Only for SPI       */
#define RTC_INTR_SLAVE_SPI_EZBUF_STOP_POS       (10u) /* [10] Slave end of transaciton: Only for SPI   */
#define RTC_INTR_SLAVE_SPI_BUS_ERROR_POS        (11u) /* [11] Slave detects bus error: Only for SPI    */
#define RTC_INTR_SLAVE_I2C_ARB_LOST             ((uint32) 0x01u)
#define RTC_INTR_SLAVE_I2C_NACK                 ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_SLAVE_I2C_NACK_POS))
#define RTC_INTR_SLAVE_I2C_ACK                  ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_SLAVE_I2C_ACK_POS))
#define RTC_INTR_SLAVE_I2C_WRITE_STOP           ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_SLAVE_I2C_WRITE_STOP_POS))
#define RTC_INTR_SLAVE_I2C_STOP                 ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_SLAVE_I2C_STOP_POS))
#define RTC_INTR_SLAVE_I2C_START                ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_SLAVE_I2C_START_POS))
#define RTC_INTR_SLAVE_I2C_ADDR_MATCH           ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_SLAVE_I2C_ADDR_MATCH_POS))
#define RTC_INTR_SLAVE_I2C_GENERAL              ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_SLAVE_I2C_GENERAL_POS))
#define RTC_INTR_SLAVE_I2C_BUS_ERROR            ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_SLAVE_I2C_BUS_ERROR_POS))
#define RTC_INTR_SLAVE_SPI_EZBUF_WRITE_STOP     ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS))
#define RTC_INTR_SLAVE_SPI_EZBUF_STOP           ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_SLAVE_SPI_EZBUF_STOP_POS))
#define RTC_INTR_SLAVE_SPI_BUS_ERROR           ((uint32) ((uint32) 0x01u << \
                                                                    RTC_INTR_SLAVE_SPI_BUS_ERROR_POS))


/*
* RTC_INTR_TX, RTC_INTR_TX_SET,
* RTC_INTR_TX_MASK, RTC_INTR_TX_MASKED
*/
#define RTC_INTR_TX_TRIGGER_POS        (0u)  /* [0]  Trigger on TX FIFO entires                       */
#define RTC_INTR_TX_NOT_FULL_POS       (1u)  /* [1]  TX FIFO is not full                              */
#define RTC_INTR_TX_EMPTY_POS          (4u)  /* [4]  TX FIFO is empty                                 */
#define RTC_INTR_TX_OVERFLOW_POS       (5u)  /* [5]  Attempt to write to a full TX FIFO               */
#define RTC_INTR_TX_UNDERFLOW_POS      (6u)  /* [6]  Attempt to read from an empty TX FIFO            */
#define RTC_INTR_TX_BLOCKED_POS        (7u)  /* [7]  No access to the EZ memory                       */
#define RTC_INTR_TX_UART_NACK_POS      (8u)  /* [8]  UART transmitter received a NACK: SmartCard mode */
#define RTC_INTR_TX_UART_DONE_POS      (9u)  /* [9]  UART transmitter done even                       */
#define RTC_INTR_TX_UART_ARB_LOST_POS  (10u) /* [10] UART lost arbitration: LIN or SmartCard          */
#define RTC_INTR_TX_TRIGGER            ((uint32) 0x01u)
#define RTC_INTR_TX_NOT_FULL           ((uint32) ((uint32) 0x01u << \
                                                                        RTC_INTR_TX_NOT_FULL_POS))
#define RTC_INTR_TX_EMPTY              ((uint32) ((uint32) 0x01u << \
                                                                        RTC_INTR_TX_EMPTY_POS))
#define RTC_INTR_TX_OVERFLOW           ((uint32) ((uint32) 0x01u << \
                                                                        RTC_INTR_TX_OVERFLOW_POS))
#define RTC_INTR_TX_UNDERFLOW          ((uint32) ((uint32) 0x01u << \
                                                                        RTC_INTR_TX_UNDERFLOW_POS))
#define RTC_INTR_TX_BLOCKED            ((uint32) ((uint32) 0x01u << \
                                                                        RTC_INTR_TX_BLOCKED_POS))
#define RTC_INTR_TX_UART_NACK          ((uint32) ((uint32) 0x01u << \
                                                                        RTC_INTR_TX_UART_NACK_POS))
#define RTC_INTR_TX_UART_DONE          ((uint32) ((uint32) 0x01u << \
                                                                        RTC_INTR_TX_UART_DONE_POS))
#define RTC_INTR_TX_UART_ARB_LOST      ((uint32) ((uint32) 0x01u << \
                                                                        RTC_INTR_TX_UART_ARB_LOST_POS))


/*
* RTC_INTR_RX, RTC_INTR_RX_SET,
* RTC_INTR_RX_MASK, RTC_INTR_RX_MASKED
*/
#define RTC_INTR_RX_TRIGGER_POS        (0u)   /* [0]  Trigger on RX FIFO entires            */
#define RTC_INTR_RX_NOT_EMPTY_POS      (2u)   /* [2]  RX FIFO is not empty                  */
#define RTC_INTR_RX_FULL_POS           (3u)   /* [3]  RX FIFO is full                       */
#define RTC_INTR_RX_OVERFLOW_POS       (5u)   /* [5]  Attempt to write to a full RX FIFO    */
#define RTC_INTR_RX_UNDERFLOW_POS      (6u)   /* [6]  Attempt to read from an empty RX FIFO */
#define RTC_INTR_RX_BLOCKED_POS        (7u)   /* [7]  No access to the EZ memory            */
#define RTC_INTR_RX_FRAME_ERROR_POS    (8u)   /* [8]  Frame error in received data frame    */
#define RTC_INTR_RX_PARITY_ERROR_POS   (9u)   /* [9]  Parity error in received data frame   */
#define RTC_INTR_RX_BAUD_DETECT_POS    (10u)  /* [10] LIN baudrate detection is completed   */
#define RTC_INTR_RX_BREAK_DETECT_POS   (11u)  /* [11] Break detection is successful         */
#define RTC_INTR_RX_TRIGGER            ((uint32) 0x01u)
#define RTC_INTR_RX_NOT_EMPTY          ((uint32) ((uint32) 0x01u << \
                                                                        RTC_INTR_RX_NOT_EMPTY_POS))
#define RTC_INTR_RX_FULL               ((uint32) ((uint32) 0x01u << \
                                                                        RTC_INTR_RX_FULL_POS))
#define RTC_INTR_RX_OVERFLOW           ((uint32) ((uint32) 0x01u << \
                                                                        RTC_INTR_RX_OVERFLOW_POS))
#define RTC_INTR_RX_UNDERFLOW          ((uint32) ((uint32) 0x01u << \
                                                                        RTC_INTR_RX_UNDERFLOW_POS))
#define RTC_INTR_RX_BLOCKED            ((uint32) ((uint32) 0x01u << \
                                                                        RTC_INTR_RX_BLOCKED_POS))
#define RTC_INTR_RX_FRAME_ERROR        ((uint32) ((uint32) 0x01u << \
                                                                        RTC_INTR_RX_FRAME_ERROR_POS))
#define RTC_INTR_RX_PARITY_ERROR       ((uint32) ((uint32) 0x01u << \
                                                                        RTC_INTR_RX_PARITY_ERROR_POS))
#define RTC_INTR_RX_BAUD_DETECT        ((uint32) ((uint32) 0x01u << \
                                                                        RTC_INTR_RX_BAUD_DETECT_POS))
#define RTC_INTR_RX_BREAK_DETECT       ((uint32) ((uint32) 0x01u << \
                                                                        RTC_INTR_RX_BREAK_DETECT_POS))


/* Define all interupt soureces */
#define RTC_INTR_I2C_EC_ALL    (RTC_INTR_I2C_EC_WAKE_UP    | \
                                             RTC_INTR_I2C_EC_EZBUF_STOP | \
                                             RTC_INTR_I2C_EC_EZBUF_WRITE_STOP)

#define RTC_INTR_SPI_EC_ALL    (RTC_INTR_SPI_EC_WAKE_UP    | \
                                             RTC_INTR_SPI_EC_EZBUF_STOP | \
                                             RTC_INTR_SPI_EC_EZBUF_WRITE_STOP)

#define RTC_INTR_MASTER_ALL    (RTC_INTR_MASTER_I2C_ARB_LOST  | \
                                             RTC_INTR_MASTER_I2C_NACK      | \
                                             RTC_INTR_MASTER_I2C_ACK       | \
                                             RTC_INTR_MASTER_I2C_STOP      | \
                                             RTC_INTR_MASTER_I2C_BUS_ERROR | \
                                             RTC_INTR_MASTER_SPI_DONE )

#define RTC_INTR_SLAVE_ALL     (RTC_INTR_SLAVE_I2C_ARB_LOST      | \
                                             RTC_INTR_SLAVE_I2C_NACK          | \
                                             RTC_INTR_SLAVE_I2C_ACK           | \
                                             RTC_INTR_SLAVE_I2C_WRITE_STOP    | \
                                             RTC_INTR_SLAVE_I2C_STOP          | \
                                             RTC_INTR_SLAVE_I2C_START         | \
                                             RTC_INTR_SLAVE_I2C_ADDR_MATCH    | \
                                             RTC_INTR_SLAVE_I2C_GENERAL       | \
                                             RTC_INTR_SLAVE_I2C_BUS_ERROR     | \
                                             RTC_INTR_SLAVE_SPI_EZBUF_WRITE_STOP | \
                                             RTC_INTR_SLAVE_SPI_EZBUF_STOP       | \
                                             RTC_INTR_SLAVE_SPI_BUS_ERROR)

#define RTC_INTR_TX_ALL        (RTC_INTR_TX_TRIGGER   | \
                                             RTC_INTR_TX_NOT_FULL  | \
                                             RTC_INTR_TX_EMPTY     | \
                                             RTC_INTR_TX_OVERFLOW  | \
                                             RTC_INTR_TX_UNDERFLOW | \
                                             RTC_INTR_TX_BLOCKED   | \
                                             RTC_INTR_TX_UART_NACK | \
                                             RTC_INTR_TX_UART_DONE | \
                                             RTC_INTR_TX_UART_ARB_LOST)

#define RTC_INTR_RX_ALL        (RTC_INTR_RX_TRIGGER      | \
                                             RTC_INTR_RX_NOT_EMPTY    | \
                                             RTC_INTR_RX_FULL         | \
                                             RTC_INTR_RX_OVERFLOW     | \
                                             RTC_INTR_RX_UNDERFLOW    | \
                                             RTC_INTR_RX_BLOCKED      | \
                                             RTC_INTR_RX_FRAME_ERROR  | \
                                             RTC_INTR_RX_PARITY_ERROR | \
                                             RTC_INTR_RX_BAUD_DETECT  | \
                                             RTC_INTR_RX_BREAK_DETECT)

/* General usage HW definitions */
#define RTC_ONE_BYTE_WIDTH (8u)   /* Number of bits in one byte           */
#define RTC_FIFO_SIZE      (8u)   /* Size of TX or RX FIFO: defined by HW */
#define RTC_EZBUFFER_SIZE  (32u)  /* EZ Buffer size: defined by HW        */

/* I2C and EZI2C slave address defines */
#define RTC_I2C_SLAVE_ADDR_POS    (0x01u)    /* 7-bit address shift */
#define RTC_I2C_SLAVE_ADDR_MASK   (0xFEu)    /* 8-bit address mask */

/* OVS constants for IrDA Low Power operation */
#define RTC_CTRL_OVS_IRDA_LP_OVS16     (0x00u)
#define RTC_CTRL_OVS_IRDA_LP_OVS32     (0x01u)
#define RTC_CTRL_OVS_IRDA_LP_OVS48     (0x02u)
#define RTC_CTRL_OVS_IRDA_LP_OVS96     (0x03u)
#define RTC_CTRL_OVS_IRDA_LP_OVS192    (0x04u)
#define RTC_CTRL_OVS_IRDA_LP_OVS768    (0x05u)
#define RTC_CTRL_OVS_IRDA_LP_OVS1536   (0x06u)

/* OVS constant for IrDA */
#define RTC_CTRL_OVS_IRDA_OVS16        (RTC_UART_IRDA_LP_OVS16)


/***************************************
*    SCB Common Macro Definitions
***************************************/

/*
* Re-enables SCB IP: this cause partial reset of IP: state, status, TX and RX FIFOs.
* The triggered interrupts remains set.
*/
#define RTC_SCB_SW_RESET \
                        do{ \
                            RTC_CTRL_REG &= ((uint32) ~RTC_CTRL_ENABLED ); \
                            RTC_CTRL_REG |= ((uint32)  RTC_CTRL_ENABLED ); \
                        }while(0)

/* TX FIFO macro */
#define RTC_CLEAR_TX_FIFO \
                            do{        \
                                RTC_TX_FIFO_CTRL_REG |= ((uint32)  RTC_TX_FIFO_CTRL_CLEAR); \
                                RTC_TX_FIFO_CTRL_REG &= ((uint32) ~RTC_TX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define RTC_GET_TX_FIFO_ENTRIES    (RTC_TX_FIFO_STATUS_REG & \
                                                 RTC_TX_FIFO_STATUS_USED_MASK)

#define RTC_GET_TX_FIFO_SR_VALID   ((0u != (RTC_TX_FIFO_STATUS_REG & \
                                                         RTC_TX_FIFO_SR_VALID)) ? (1u) : (0u))

/* RX FIFO macro */
#define RTC_CLEAR_RX_FIFO \
                            do{        \
                                RTC_RX_FIFO_CTRL_REG |= ((uint32)  RTC_RX_FIFO_CTRL_CLEAR); \
                                RTC_RX_FIFO_CTRL_REG &= ((uint32) ~RTC_RX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define RTC_GET_RX_FIFO_ENTRIES    (RTC_RX_FIFO_STATUS_REG & \
                                                    RTC_RX_FIFO_STATUS_USED_MASK)

#define RTC_GET_RX_FIFO_SR_VALID   ((0u != (RTC_RX_FIFO_STATUS_REG & \
                                                         RTC_RX_FIFO_SR_VALID)) ? (1u) : (0u))

/* Writes interrupt source: set sourceMask bits in RTC_INTR_X_MASK_REG */
#define RTC_WRITE_INTR_I2C_EC_MASK(sourceMask) \
                                                do{         \
                                                    RTC_INTR_I2C_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define RTC_WRITE_INTR_SPI_EC_MASK(sourceMask) \
                                                do{         \
                                                    RTC_INTR_SPI_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define RTC_WRITE_INTR_MASTER_MASK(sourceMask) \
                                                do{         \
                                                    RTC_INTR_MASTER_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define RTC_WRITE_INTR_SLAVE_MASK(sourceMask)  \
                                                do{         \
                                                    RTC_INTR_SLAVE_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define RTC_WRITE_INTR_TX_MASK(sourceMask)     \
                                                do{         \
                                                    RTC_INTR_TX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define RTC_WRITE_INTR_RX_MASK(sourceMask)     \
                                                do{         \
                                                    RTC_INTR_RX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Enables interrupt source: set sourceMask bits in RTC_INTR_X_MASK_REG */
#define RTC_ENABLE_INTR_I2C_EC(sourceMask) \
                                                do{     \
                                                    RTC_INTR_I2C_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define RTC_ENABLE_INTR_SPI_EC(sourceMask) \
                                                do{     \
                                                    RTC_INTR_SPI_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define RTC_ENABLE_INTR_MASTER(sourceMask) \
                                                do{     \
                                                    RTC_INTR_MASTER_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define RTC_ENABLE_INTR_SLAVE(sourceMask)  \
                                                do{     \
                                                    RTC_INTR_SLAVE_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define RTC_ENABLE_INTR_TX(sourceMask)     \
                                                do{     \
                                                    RTC_INTR_TX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define RTC_ENABLE_INTR_RX(sourceMask)     \
                                                do{     \
                                                    RTC_INTR_RX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

/* Disables interrupt source: clear sourceMask bits in RTC_INTR_X_MASK_REG */
#define RTC_DISABLE_INTR_I2C_EC(sourceMask) \
                                do{                      \
                                    RTC_INTR_I2C_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define RTC_DISABLE_INTR_SPI_EC(sourceMask) \
                                do{                      \
                                    RTC_INTR_SPI_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)

#define RTC_DISABLE_INTR_MASTER(sourceMask) \
                                do{                      \
                                RTC_INTR_MASTER_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define RTC_DISABLE_INTR_SLAVE(sourceMask) \
                                do{                     \
                                    RTC_INTR_SLAVE_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define RTC_DISABLE_INTR_TX(sourceMask)    \
                                do{                     \
                                    RTC_INTR_TX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)

#define RTC_DISABLE_INTR_RX(sourceMask)    \
                                do{                     \
                                    RTC_INTR_RX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

/* Sets interrupt sources: write sourceMask bits in RTC_INTR_X_SET_REG */
#define RTC_SET_INTR_MASTER(sourceMask)    \
                                                do{     \
                                                    RTC_INTR_MASTER_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define RTC_SET_INTR_SLAVE(sourceMask) \
                                                do{ \
                                                    RTC_INTR_SLAVE_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define RTC_SET_INTR_TX(sourceMask)    \
                                                do{ \
                                                    RTC_INTR_TX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define RTC_SET_INTR_RX(sourceMask)    \
                                                do{ \
                                                    RTC_INTR_RX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Clears interrupt sources: write sourceMask bits in RTC_INTR_X_REG */
#define RTC_CLEAR_INTR_I2C_EC(sourceMask)  \
                                                do{     \
                                                    RTC_INTR_I2C_EC_REG = (uint32) (sourceMask); \
                                                }while(0)

#define RTC_CLEAR_INTR_SPI_EC(sourceMask)  \
                                                do{     \
                                                    RTC_INTR_SPI_EC_REG = (uint32) (sourceMask); \
                                                }while(0)

#define RTC_CLEAR_INTR_MASTER(sourceMask)  \
                                                do{     \
                                                    RTC_INTR_MASTER_REG = (uint32) (sourceMask); \
                                                }while(0)

#define RTC_CLEAR_INTR_SLAVE(sourceMask)   \
                                                do{     \
                                                    RTC_INTR_SLAVE_REG  = (uint32) (sourceMask); \
                                                }while(0)

#define RTC_CLEAR_INTR_TX(sourceMask)      \
                                                do{     \
                                                    RTC_INTR_TX_REG     = (uint32) (sourceMask); \
                                                }while(0)

#define RTC_CLEAR_INTR_RX(sourceMask)      \
                                                do{     \
                                                    RTC_INTR_RX_REG     = (uint32) (sourceMask); \
                                                }while(0)

/* Return true if sourceMask is set in RTC_INTR_CAUSE_REG */
#define RTC_CHECK_CAUSE_INTR(sourceMask)    (0u != (RTC_INTR_CAUSE_REG & (sourceMask)))

/* Return true if sourceMask is set in  INTR_X_MASKED_REG */
#define RTC_CHECK_INTR_EC_I2C(sourceMask)  (0u != (RTC_INTR_I2C_EC_REG & (sourceMask)))
#define RTC_CHECK_INTR_EC_SPI(sourceMask)  (0u != (RTC_INTR_SPI_EC_REG & (sourceMask)))
#define RTC_CHECK_INTR_MASTER(sourceMask)  (0u != (RTC_INTR_MASTER_REG & (sourceMask)))
#define RTC_CHECK_INTR_SLAVE(sourceMask)   (0u != (RTC_INTR_SLAVE_REG  & (sourceMask)))
#define RTC_CHECK_INTR_TX(sourceMask)      (0u != (RTC_INTR_TX_REG     & (sourceMask)))
#define RTC_CHECK_INTR_RX(sourceMask)      (0u != (RTC_INTR_RX_REG     & (sourceMask)))

/* Return true if sourceMask is set in RTC_INTR_X_MASKED_REG */
#define RTC_CHECK_INTR_I2C_EC_MASKED(sourceMask)   (0u != (RTC_INTR_I2C_EC_MASKED_REG & \
                                                                       (sourceMask)))
#define RTC_CHECK_INTR_SPI_EC_MASKED(sourceMask)   (0u != (RTC_INTR_SPI_EC_MASKED_REG & \
                                                                       (sourceMask)))
#define RTC_CHECK_INTR_MASTER_MASKED(sourceMask)   (0u != (RTC_INTR_MASTER_MASKED_REG & \
                                                                       (sourceMask)))
#define RTC_CHECK_INTR_SLAVE_MASKED(sourceMask)    (0u != (RTC_INTR_SLAVE_MASKED_REG  & \
                                                                       (sourceMask)))
#define RTC_CHECK_INTR_TX_MASKED(sourceMask)       (0u != (RTC_INTR_TX_MASKED_REG     & \
                                                                       (sourceMask)))
#define RTC_CHECK_INTR_RX_MASKED(sourceMask)       (0u != (RTC_INTR_RX_MASKED_REG     & \
                                                                       (sourceMask)))

/* Return true if sourceMask is set in RTC_CTRL_REG: generaly is used to check enable bit */
#define RTC_GET_CTRL_ENABLED    (0u != (RTC_CTRL_REG & RTC_CTRL_ENABLED))

#define RTC_CHECK_SLAVE_AUTO_ADDR_NACK     (0u != (RTC_I2C_CTRL_REG & \
                                                                RTC_I2C_CTRL_S_NOT_READY_DATA_NACK))


/***************************************
*      I2C Macro Definitions
***************************************/

/* Enable auto ACK/NACK */
#define RTC_ENABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                      \
                                RTC_I2C_CTRL_REG |= RTC_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define RTC_ENABLE_SLAVE_AUTO_DATA_ACK \
                            do{                     \
                                RTC_I2C_CTRL_REG |= RTC_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define RTC_ENABLE_SLAVE_AUTO_DATA_NACK \
                            do{                      \
                                RTC_I2C_CTRL_REG |= RTC_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define RTC_ENABLE_MASTER_AUTO_DATA_ACK \
                            do{                      \
                                RTC_I2C_CTRL_REG |= RTC_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define RTC_ENABLE_MASTER_AUTO_DATA_NACK \
                            do{                       \
                                RTC_I2C_CTRL_REG |= RTC_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Disable auto ACK/NACK */
#define RTC_DISABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                       \
                                RTC_I2C_CTRL_REG &= ~RTC_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define RTC_DISABLE_SLAVE_AUTO_DATA_ACK \
                            do{                      \
                                RTC_I2C_CTRL_REG &= ~RTC_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define RTC_DISABLE_SLAVE_AUTO_DATA_NACK \
                            do{                       \
                                RTC_I2C_CTRL_REG &= ~RTC_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define RTC_DISABLE_MASTER_AUTO_DATA_ACK \
                            do{                       \
                                RTC_I2C_CTRL_REG &= ~RTC_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define RTC_DISABLE_MASTER_AUTO_DATA_NACK \
                            do{                        \
                                RTC_I2C_CTRL_REG &= ~RTC_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Enable Slave autoACK/NACK Data */
#define RTC_ENABLE_SLAVE_AUTO_DATA \
                            do{                 \
                                RTC_I2C_CTRL_REG |= (RTC_I2C_CTRL_S_READY_DATA_ACK |      \
                                                                  RTC_I2C_CTRL_S_NOT_READY_DATA_NACK); \
                            }while(0)

/* Disable Slave autoACK/NACK Data */
#define RTC_DISABLE_SLAVE_AUTO_DATA \
                            do{                  \
                                RTC_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(RTC_I2C_CTRL_S_READY_DATA_ACK |       \
                                                                    RTC_I2C_CTRL_S_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Disable Master autoACK/NACK Data */
#define RTC_DISABLE_MASTER_AUTO_DATA \
                            do{                   \
                                RTC_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(RTC_I2C_CTRL_M_READY_DATA_ACK |       \
                                                                    RTC_I2C_CTRL_M_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Master commands */
#define RTC_I2C_MASTER_GENERATE_START \
                            do{                    \
                                RTC_I2C_MASTER_CMD_REG = RTC_I2C_MASTER_CMD_M_START_ON_IDLE; \
                            }while(0)

#define RTC_I2C_MASTER_CLEAR_START \
                            do{                 \
                                RTC_I2C_MASTER_CMD_REG =  ((uint32) 0u); \
                            }while(0)

#define RTC_I2C_MASTER_GENERATE_RESTART RTC_I2CReStartGeneration()

#define RTC_I2C_MASTER_GENERATE_STOP \
                            do{                   \
                                RTC_I2C_MASTER_CMD_REG =                                            \
                                    (RTC_I2C_MASTER_CMD_M_STOP |                                    \
                                        (RTC_CHECK_I2C_STATUS(RTC_I2C_STATUS_M_READ) ? \
                                            (RTC_I2C_MASTER_CMD_M_NACK) : (0u)));                   \
                            }while(0)

#define RTC_I2C_MASTER_GENERATE_ACK \
                            do{                  \
                                RTC_I2C_MASTER_CMD_REG = RTC_I2C_MASTER_CMD_M_ACK; \
                            }while(0)

#define RTC_I2C_MASTER_GENERATE_NACK \
                            do{                   \
                                RTC_I2C_MASTER_CMD_REG = RTC_I2C_MASTER_CMD_M_NACK; \
                            }while(0)

/* Slave comamnds */
#define RTC_I2C_SLAVE_GENERATE_ACK \
                            do{                 \
                                RTC_I2C_SLAVE_CMD_REG = RTC_I2C_SLAVE_CMD_S_ACK; \
                            }while(0)

#define RTC_I2C_SLAVE_GENERATE_NACK \
                            do{                  \
                                RTC_I2C_SLAVE_CMD_REG = RTC_I2C_SLAVE_CMD_S_NACK; \
                            }while(0)


/* Return 8-bit address. The input address should be 7-bits */
#define RTC_GET_I2C_8BIT_ADDRESS(addr) (((uint32) ((uint32) (addr) << \
                                                                    RTC_I2C_SLAVE_ADDR_POS)) & \
                                                                        RTC_I2C_SLAVE_ADDR_MASK)

#define RTC_GET_I2C_7BIT_ADDRESS(addr) ((uint32) (addr) >> RTC_I2C_SLAVE_ADDR_POS)


/* Adjust SDA filter Trim settings */
#define RTC_DEFAULT_I2C_CFG_SDA_FILT_TRIM  (0x02u)
#define RTC_EC_AM_I2C_CFG_SDA_FILT_TRIM    (0x03u)

#define RTC_SET_I2C_CFG_SDA_FILT_TRIM(sdaTrim) \
        do{                                                 \
            RTC_I2C_CFG_REG =                  \
                            ((RTC_I2C_CFG_REG & (uint32) ~RTC_I2C_CFG_SDA_FILT_TRIM_MASK) | \
                             ((uint32) ((uint32) (sdaTrim) <<RTC_I2C_CFG_SDA_FILT_TRIM_POS)));           \
        }while(0)

/* Returns slave select number in SPI_CTRL */
#define RTC_GET_SPI_CTRL_SS(activeSelect) (((uint32) ((uint32) (activeSelect) << \
                                                                    RTC_SPI_CTRL_SLAVE_SELECT_POS)) & \
                                                                        RTC_SPI_CTRL_SLAVE_SELECT_MASK)

/* Returns true if bit is set in RTC_I2C_STATUS_REG */
#define RTC_CHECK_I2C_STATUS(sourceMask)   (0u != (RTC_I2C_STATUS_REG & (sourceMask)))

/* Returns true if bit is set in RTC_SPI_STATUS_REG */
#define RTC_CHECK_SPI_STATUS(sourceMask)   (0u != (RTC_SPI_STATUS_REG & (sourceMask)))


/***************************************
*       SCB Init Macros Definitions
***************************************/

/* RTC_CTRL */
#define RTC_GET_CTRL_OVS(oversample)   ((((uint32) (oversample)) - 1u) & RTC_CTRL_OVS_MASK)

#define RTC_GET_CTRL_EC_OP_MODE(opMode)        ((0u != (opMode)) ? \
                                                                (RTC_CTRL_EC_OP_MODE)  : (0u))

#define RTC_GET_CTRL_EC_AM_MODE(amMode)        ((0u != (amMode)) ? \
                                                                (RTC_CTRL_EC_AM_MODE)  : (0u))

#define RTC_GET_CTRL_BLOCK(block)              ((0u != (block))  ? \
                                                                (RTC_CTRL_BLOCK)       : (0u))

#define RTC_GET_CTRL_ADDR_ACCEPT(acceptAddr)   ((0u != (acceptAddr)) ? \
                                                                (RTC_CTRL_ADDR_ACCEPT) : (0u))

/* RTC_I2C_CTRL */
#define RTC_GET_I2C_CTRL_HIGH_PHASE_OVS(oversampleHigh) (((uint32) (oversampleHigh) - 1u) & \
                                                                        RTC_I2C_CTRL_HIGH_PHASE_OVS_MASK)

#define RTC_GET_I2C_CTRL_LOW_PHASE_OVS(oversampleLow)   (((uint32) (((uint32) (oversampleLow) - 1u) << \
                                                                    RTC_I2C_CTRL_LOW_PHASE_OVS_POS)) &  \
                                                                    RTC_I2C_CTRL_LOW_PHASE_OVS_MASK)

#define RTC_GET_I2C_CTRL_S_NOT_READY_ADDR_NACK(wakeNack) ((0u != (wakeNack)) ? \
                                                            (RTC_I2C_CTRL_S_NOT_READY_ADDR_NACK) : (0u))

#define RTC_GET_I2C_CTRL_SL_MSTR_MODE(mode)    ((uint32) ((uint32)(mode) << \
                                                                    RTC_I2C_CTRL_SLAVE_MODE_POS))

/* RTC_SPI_CTRL */
#define RTC_GET_SPI_CTRL_CONTINUOUS(separate)  ((0u != (separate)) ? \
                                                                (RTC_SPI_CTRL_CONTINUOUS) : (0u))

#define RTC_GET_SPI_CTRL_SELECT_PRECEDE(mode)  ((0u != (mode)) ? \
                                                                      (RTC_SPI_CTRL_SELECT_PRECEDE) : (0u))

#define RTC_GET_SPI_CTRL_SCLK_MODE(mode)       (((uint32) ((uint32) (mode) << \
                                                                        RTC_SPI_CTRL_CPHA_POS)) & \
                                                                        RTC_SPI_CTRL_SCLK_MODE_MASK)

#define RTC_GET_SPI_CTRL_LATE_MISO_SAMPLE(lateMiso) ((0u != (lateMiso)) ? \
                                                                    (RTC_SPI_CTRL_LATE_MISO_SAMPLE) : (0u))

#define RTC_GET_SPI_CTRL_SUB_MODE(mode)        (((uint32) (((uint32) (mode)) << \
                                                                        RTC_SPI_CTRL_MODE_POS)) & \
                                                                        RTC_SPI_CTRL_MODE_MASK)

#define RTC_GET_SPI_CTRL_SLAVE_SELECT(select)  (((uint32) ((uint32) (select) << \
                                                                      RTC_SPI_CTRL_SLAVE_SELECT_POS)) & \
                                                                      RTC_SPI_CTRL_SLAVE_SELECT_MASK)

#define RTC_GET_SPI_CTRL_MASTER_MODE(mode)     ((0u != (mode)) ? \
                                                                (RTC_SPI_CTRL_MASTER) : (0u))

/* RTC_UART_CTRL */
#define RTC_GET_UART_CTRL_MODE(mode)           (((uint32) ((uint32) (mode) << \
                                                                            RTC_UART_CTRL_MODE_POS)) & \
                                                                                RTC_UART_CTRL_MODE_MASK)

/* RTC_UART_RX_CTRL */
#define RTC_GET_UART_RX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                        RTC_UART_RX_CTRL_STOP_BITS_MASK)

#define RTC_GET_UART_RX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                                    (RTC_UART_RX_CTRL_PARITY) : (0u))

#define RTC_GET_UART_RX_CTRL_POLARITY(polarity)    ((0u != (polarity)) ? \
                                                                    (RTC_UART_RX_CTRL_POLARITY) : (0u))

#define RTC_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (RTC_UART_RX_CTRL_DROP_ON_PARITY_ERR) : (0u))

#define RTC_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (RTC_UART_RX_CTRL_DROP_ON_FRAME_ERR) : (0u))

#define RTC_GET_UART_RX_CTRL_MP_MODE(mpMode)   ((0u != (mpMode)) ? \
                                                        (RTC_UART_RX_CTRL_MP_MODE) : (0u))

/* RTC_UART_TX_CTRL */
#define RTC_GET_UART_TX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                RTC_UART_RX_CTRL_STOP_BITS_MASK)

#define RTC_GET_UART_TX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                               (RTC_UART_TX_CTRL_PARITY) : (0u))

#define RTC_GET_UART_TX_CTRL_RETRY_NACK(nack)  ((0u != (nack)) ? \
                                                               (RTC_UART_TX_CTRL_RETRY_ON_NACK) : (0u))

/* RTC_RX_CTRL */
#define RTC_GET_RX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                RTC_RX_CTRL_DATA_WIDTH_MASK)

#define RTC_GET_RX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (RTC_RX_CTRL_MSB_FIRST) : (0u))

#define RTC_GET_RX_CTRL_MEDIAN(filterEn)       ((0u != (filterEn)) ? \
                                                                (RTC_RX_CTRL_MEDIAN) : (0u))

/* RTC_RX_MATCH */
#define RTC_GET_RX_MATCH_ADDR(addr)    ((uint32) (addr) & RTC_RX_MATCH_ADDR_MASK)
#define RTC_GET_RX_MATCH_MASK(mask)    (((uint32) ((uint32) (mask) << \
                                                            RTC_RX_MATCH_MASK_POS)) & \
                                                            RTC_RX_MATCH_MASK_MASK)

/* RTC_RX_FIFO_CTRL */
#define RTC_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    RTC_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* RTC_TX_CTRL */
#define RTC_GET_TX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                RTC_RX_CTRL_DATA_WIDTH_MASK)

#define RTC_GET_TX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (RTC_TX_CTRL_MSB_FIRST) : (0u))

/* RTC_TX_FIFO_CTRL */
#define RTC_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    RTC_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* Clears register: config and interrupt mask */
#define RTC_CLEAR_REG          ((uint32) (0u))
#define RTC_NO_INTR_SOURCES    ((uint32) (0u))
#define RTC_DUMMY_PARAM        ((uint32) (0u))
#define RTC_SUBMODE_SPI_SLAVE  ((uint32) (0u))

/* Return in case I2C read error */
#define RTC_I2C_INVALID_BYTE   ((uint32) 0xFFFFFFFFu)
#define RTC_CHECK_VALID_BYTE   ((uint32) 0x80000000u)

#endif /* (CY_SCB_RTC_H) */


/* [] END OF FILE */
