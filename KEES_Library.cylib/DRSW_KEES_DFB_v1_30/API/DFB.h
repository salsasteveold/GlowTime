/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the DFB Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2011-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_DFB_`$INSTANCE_NAME`_H) /* DFB Header File */
#define CY_DFB_`$INSTANCE_NAME`_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

extern uint8 `$INSTANCE_NAME`_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define `$INSTANCE_NAME`_OPTIMIZE_ASSEMBLY      (`$OptimizeAssembly`u)
#define `$INSTANCE_NAME`_INIT_INTERRUPT_MODE    (`$InitialInterruptMode`u)
#define `$INSTANCE_NAME`_INIT_DMA_MODE          (`$InitialDMAMode`u)
#define `$INSTANCE_NAME`_INIT_OUT1_SOURCE       (`$InitialOutput1Source`u)
#define `$INSTANCE_NAME`_INIT_OUT2_SOURCE       (`$InitialOutput2Source`u)

/* Sizes of current DFB program */
#define `$INSTANCE_NAME`_DA_RAM_SIZE_CUR        (`$data_a_size`)
#define `$INSTANCE_NAME`_DB_RAM_SIZE_CUR        (`$data_b_size`)
#define `$INSTANCE_NAME`_CSA_RAM_SIZE_CUR       (`$cstoreA_size``$control_size`)
#define `$INSTANCE_NAME`_CSB_RAM_SIZE_CUR       (`$cstoreB_size``$control_size`)
#define `$INSTANCE_NAME`_CFSM_RAM_SIZE_CUR      (`$cfsm_size`)
#define `$INSTANCE_NAME`_ACU_RAM_SIZE_CUR       (`$acu_size`)


/***************************************
*     Data Types Definitions
***************************************/

#if (`$INSTANCE_NAME`_OPTIMIZE_ASSEMBLY)
    extern const uint32 CYCODE `$INSTANCE_NAME`_cstoreA[`$INSTANCE_NAME`_CSA_RAM_SIZE_CUR];
    extern const uint32 CYCODE `$INSTANCE_NAME`_cstoreB[`$INSTANCE_NAME`_CSB_RAM_SIZE_CUR];
#else
    extern const uint32 CYCODE `$INSTANCE_NAME`_control[`$INSTANCE_NAME`_CSA_RAM_SIZE_CUR];
#endif /* `$INSTANCE_NAME`_OPTIMIZE_ASSEMBLY */

extern const uint32 CYCODE `$INSTANCE_NAME`_data_a[`$INSTANCE_NAME`_DA_RAM_SIZE_CUR];
extern const uint32 CYCODE `$INSTANCE_NAME`_data_b[`$INSTANCE_NAME`_DB_RAM_SIZE_CUR];
extern const uint32 CYCODE `$INSTANCE_NAME`_cfsm[`$INSTANCE_NAME`_CFSM_RAM_SIZE_CUR];
extern const uint32 CYCODE `$INSTANCE_NAME`_acu[`$INSTANCE_NAME`_ACU_RAM_SIZE_CUR];

/* Sleep Mode API Support */
typedef struct
{
    uint8  enableState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void   `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void   `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void   `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void   `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void   `$INSTANCE_NAME`_Pause(void) `=ReentrantKeil($INSTANCE_NAME . "_Pause")`;
void   `$INSTANCE_NAME`_Resume(void) `=ReentrantKeil($INSTANCE_NAME . "_Resume")`;
void   `$INSTANCE_NAME`_SetCoherency(uint8 coherencyKeyByte) `=ReentrantKeil($INSTANCE_NAME . "_SetCoherency")`;
void   `$INSTANCE_NAME`_SetDalign(uint8 dalignKeyByte) `=ReentrantKeil($INSTANCE_NAME . "_SetDalign")`;
uint8  `$INSTANCE_NAME`_LoadDataRAMA(const int32 ptr[], uint32 addr[], uint8 size)
        `=ReentrantKeil($INSTANCE_NAME . "_LoadDataRAMA")`;
uint8  `$INSTANCE_NAME`_LoadDataRAMB(const int32 ptr[], uint32 addr[], uint8 size)
        `=ReentrantKeil($INSTANCE_NAME . "_LoadDataRAMB")`;
void   `$INSTANCE_NAME`_LoadInputValue(uint8 channel, int32 sample)
        `=ReentrantKeil($INSTANCE_NAME . "_LoadInputValue")`;
int32  `$INSTANCE_NAME`_GetOutputValue(uint8 channel) `=ReentrantKeil($INSTANCE_NAME . "_GetOutputValue")`;
void   `$INSTANCE_NAME`_SetInterruptMode(uint8 events) `=ReentrantKeil($INSTANCE_NAME . "_SetInterruptMode")`;
uint8  `$INSTANCE_NAME`_GetInterruptSource(void) `=ReentrantKeil($INSTANCE_NAME . "_GetInterruptSource")`;
void   `$INSTANCE_NAME`_ClearInterrupt(uint8 interruptMask) `=ReentrantKeil($INSTANCE_NAME . "_ClearInterrupt")`;
void   `$INSTANCE_NAME`_SetDMAMode(uint8 events) `=ReentrantKeil($INSTANCE_NAME . "_SetDMAMode")`;
void   `$INSTANCE_NAME`_SetSemaphores(uint8 mask) `=ReentrantKeil($INSTANCE_NAME . "_SetSemaphores")`;
uint8  `$INSTANCE_NAME`_GetSemaphores(void) `=ReentrantKeil($INSTANCE_NAME . "_GetSemaphores")`;
void   `$INSTANCE_NAME`_ClearSemaphores(uint8 mask) `=ReentrantKeil($INSTANCE_NAME . "_ClearSemaphores")`;
void   `$INSTANCE_NAME`_SetOutput1Source(uint8 source) `=ReentrantKeil($INSTANCE_NAME . "_SetOutput1Source")`;
void   `$INSTANCE_NAME`_SetOutput2Source(uint8 source) `=ReentrantKeil($INSTANCE_NAME . "_SetOutput2Source")`;
void   `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void   `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;
void   `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void   `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;

/* Macros */
#define `$INSTANCE_NAME`_ClearInterruptSource(event) \
do { \
    `$INSTANCE_NAME`_SR_REG = (uint8) (((event) & `$INSTANCE_NAME`_EVENT_MASK) << `$INSTANCE_NAME`_SR_EVENT_SHIFT); \
} while (0)


/***************************************
*           API Constants
***************************************/

/* Channel Definitions */
#define `$INSTANCE_NAME`_CHANNEL_A              (1u)
#define `$INSTANCE_NAME`_CHANNEL_B              (0u)

/* Sizes of DFB memories */
#define `$INSTANCE_NAME`_DA_RAM_SIZE            (0x80u)
#define `$INSTANCE_NAME`_DB_RAM_SIZE            (0x80u)
#define `$INSTANCE_NAME`_CSA_RAM_SIZE           (0x40u)
#define `$INSTANCE_NAME`_CSB_RAM_SIZE           (0x40u)
#define `$INSTANCE_NAME`_CFSM_RAM_SIZE          (0x40u)
#define `$INSTANCE_NAME`_ACU_RAM_SIZE           (0x10u)

#define `$INSTANCE_NAME`_SUCCESS                (CYRET_SUCCESS)
#define `$INSTANCE_NAME`_DATA_OUT_OF_RANGE      (0xFEu)
#define `$INSTANCE_NAME`_ADDRESS_OUT_OF_RANGE   (0xFFu)


/***************************************
*             Registers
***************************************/

/* RAM memory map offsets */
#define `$INSTANCE_NAME`_DA_RAM_REG             (* (reg32 *) (`$INSTANCE_NAME`_DFB__DPA_SRAM_DATA))
#define `$INSTANCE_NAME`_DA_RAM_PTR             (  (reg32 *) (`$INSTANCE_NAME`_DFB__DPA_SRAM_DATA))
#define `$INSTANCE_NAME`_DB_RAM_REG             (* (reg32 *) (`$INSTANCE_NAME`_DFB__DPB_SRAM_DATA))
#define `$INSTANCE_NAME`_DB_RAM_PTR             (  (reg32 *) (`$INSTANCE_NAME`_DFB__DPB_SRAM_DATA))
#define `$INSTANCE_NAME`_CSA_RAM_REG            (* (reg32 *) (`$INSTANCE_NAME`_DFB__CSA_SRAM_DATA))
#define `$INSTANCE_NAME`_CSA_RAM_PTR            (  (reg32 *) (`$INSTANCE_NAME`_DFB__CSA_SRAM_DATA))
#define `$INSTANCE_NAME`_CSB_RAM_REG            (* (reg32 *) (`$INSTANCE_NAME`_DFB__CSB_SRAM_DATA))
#define `$INSTANCE_NAME`_CSB_RAM_PTR            (  (reg32 *) (`$INSTANCE_NAME`_DFB__CSB_SRAM_DATA))
#define `$INSTANCE_NAME`_CFSM_RAM_REG           (* (reg32 *) (`$INSTANCE_NAME`_DFB__FSM_SRAM_DATA))
#define `$INSTANCE_NAME`_CFSM_RAM_PTR           (  (reg32 *) (`$INSTANCE_NAME`_DFB__FSM_SRAM_DATA))
#define `$INSTANCE_NAME`_ACU_RAM_REG            (* (reg32 *) (`$INSTANCE_NAME`_DFB__ACU_SRAM_DATA))
#define `$INSTANCE_NAME`_ACU_RAM_PTR            (  (reg32 *) (`$INSTANCE_NAME`_DFB__ACU_SRAM_DATA))

#define `$INSTANCE_NAME`_SEM_REG                (* (reg8 *) `$INSTANCE_NAME`_DFB__SEMA)
#define `$INSTANCE_NAME`_SEM_PTR                (  (reg8 *) `$INSTANCE_NAME`_DFB__SEMA)
#define `$INSTANCE_NAME`_CR_REG                 (* (reg8 *) `$INSTANCE_NAME`_DFB__CR)
#define `$INSTANCE_NAME`_CR_PTR                 (  (reg8 *) `$INSTANCE_NAME`_DFB__CR)
#define `$INSTANCE_NAME`_SR_REG                 (* (reg8 *) `$INSTANCE_NAME`_DFB__SR)
#define `$INSTANCE_NAME`_SR_PTR                 (  (reg8 *) `$INSTANCE_NAME`_DFB__SR)
#define `$INSTANCE_NAME`_INT_CTRL_REG           (* (reg8 *) `$INSTANCE_NAME`_DFB__INT_CTRL)
#define `$INSTANCE_NAME`_INT_CTRL_PTR           (  (reg8 *) `$INSTANCE_NAME`_DFB__INT_CTRL)
#define `$INSTANCE_NAME`_DMA_CTRL_REG           (* (reg8 *) `$INSTANCE_NAME`_DFB__DMA_CTRL)
#define `$INSTANCE_NAME`_DMA_CTRL_PTR           (  (reg8 *) `$INSTANCE_NAME`_DFB__DMA_CTRL)
#define `$INSTANCE_NAME`_RAM_DIR_REG            (* (reg8 *) `$INSTANCE_NAME`_DFB__RAM_DIR)
#define `$INSTANCE_NAME`_RAM_DIR_PTR            (  (reg8 *) `$INSTANCE_NAME`_DFB__RAM_DIR)

#define `$INSTANCE_NAME`_DALIGN_REG             (* (reg8 *) `$INSTANCE_NAME`_DFB__DALIGN)
#define `$INSTANCE_NAME`_DALIGN_PTR             (  (reg8 *) `$INSTANCE_NAME`_DFB__DALIGN)
#define `$INSTANCE_NAME`_DSI_CTRL_REG           (* (reg8 *) `$INSTANCE_NAME`_DFB__DSI_CTRL)
#define `$INSTANCE_NAME`_DSI_CTRL_PTR           (  (reg8 *) `$INSTANCE_NAME`_DFB__DSI_CTRL)
#define `$INSTANCE_NAME`_HOLDA_REG              (* (reg8 *) `$INSTANCE_NAME`_DFB__HOLDA)
#define `$INSTANCE_NAME`_HOLDA_PTR              (  (reg8 *) `$INSTANCE_NAME`_DFB__HOLDA)
#define `$INSTANCE_NAME`_HOLDAH_REG             (* (reg8 *) `$INSTANCE_NAME`_DFB__HOLDAH)
#define `$INSTANCE_NAME`_HOLDAH_PTR             (  (reg8 *) `$INSTANCE_NAME`_DFB__HOLDAH)
#define `$INSTANCE_NAME`_HOLDAM_REG             (* (reg8 *) `$INSTANCE_NAME`_DFB__HOLDAM)
#define `$INSTANCE_NAME`_HOLDAM_PTR             (  (reg8 *) `$INSTANCE_NAME`_DFB__HOLDAM)
#define `$INSTANCE_NAME`_HOLDB_REG              (* (reg8 *) `$INSTANCE_NAME`_DFB__HOLDB)
#define `$INSTANCE_NAME`_HOLDB_PTR              (  (reg8 *) `$INSTANCE_NAME`_DFB__HOLDB)
#define `$INSTANCE_NAME`_HOLDBH_REG             (* (reg8 *) `$INSTANCE_NAME`_DFB__HOLDBH)
#define `$INSTANCE_NAME`_HOLDBH_PTR             (  (reg8 *) `$INSTANCE_NAME`_DFB__HOLDBH)
#define `$INSTANCE_NAME`_HOLDBM_REG             (* (reg8 *) `$INSTANCE_NAME`_DFB__HOLDBM)
#define `$INSTANCE_NAME`_HOLDBM_PTR             (  (reg8 *) `$INSTANCE_NAME`_DFB__HOLDBM)
#define `$INSTANCE_NAME`_PM_ACT_CFG_REG         (* (reg8 *) `$INSTANCE_NAME`_DFB__PM_ACT_CFG)
#define `$INSTANCE_NAME`_PM_ACT_CFG_PTR         (  (reg8 *) `$INSTANCE_NAME`_DFB__PM_ACT_CFG)
#define `$INSTANCE_NAME`_PM_STBY_CFG_REG        (* (reg8 *) `$INSTANCE_NAME`_DFB__PM_STBY_CFG)
#define `$INSTANCE_NAME`_PM_STBY_CFG_PTR        (  (reg8 *) `$INSTANCE_NAME`_DFB__PM_STBY_CFG)
#define `$INSTANCE_NAME`_RAM_EN_REG             (* (reg8 *) `$INSTANCE_NAME`_DFB__RAM_EN)
#define `$INSTANCE_NAME`_RAM_EN_PTR             (  (reg8 *) `$INSTANCE_NAME`_DFB__RAM_EN)
#define `$INSTANCE_NAME`_STAGEA_REG             (* (reg8 *) `$INSTANCE_NAME`_DFB__STAGEA)
#define `$INSTANCE_NAME`_STAGEA_PTR             (  (reg8 *) `$INSTANCE_NAME`_DFB__STAGEA)
#define `$INSTANCE_NAME`_STAGEAH_REG            (* (reg8 *) `$INSTANCE_NAME`_DFB__STAGEAH)
#define `$INSTANCE_NAME`_STAGEAH_PTR            (  (reg8 *) `$INSTANCE_NAME`_DFB__STAGEAH)
#define `$INSTANCE_NAME`_STAGEAM_REG            (* (reg8 *) `$INSTANCE_NAME`_DFB__STAGEAM)
#define `$INSTANCE_NAME`_STAGEAM_PTR            (  (reg8 *) `$INSTANCE_NAME`_DFB__STAGEAM)
#define `$INSTANCE_NAME`_STAGEB_REG             (* (reg8 *) `$INSTANCE_NAME`_DFB__STAGEB)
#define `$INSTANCE_NAME`_STAGEB_PTR             (  (reg8 *) `$INSTANCE_NAME`_DFB__STAGEB)
#define `$INSTANCE_NAME`_STAGEBH_REG            (* (reg8 *) `$INSTANCE_NAME`_DFB__STAGEBH)
#define `$INSTANCE_NAME`_STAGEBH_PTR            (  (reg8 *) `$INSTANCE_NAME`_DFB__STAGEBH)
#define `$INSTANCE_NAME`_STAGEBM_REG            (* (reg8 *) `$INSTANCE_NAME`_DFB__STAGEBM)
#define `$INSTANCE_NAME`_STAGEBM_PTR            (  (reg8 *) `$INSTANCE_NAME`_DFB__STAGEBM)
#define `$INSTANCE_NAME`_COHER_REG              (* (reg8 *) `$INSTANCE_NAME`_DFB__COHER)
#define `$INSTANCE_NAME`_COHER_PTR              (  (reg8 *) `$INSTANCE_NAME`_DFB__COHER)

#define `$INSTANCE_NAME`_DA_RAM_LAST_ELEM_PTR   (  (reg32 *) (`$INSTANCE_NAME`_DFB__DPB_SRAM_DATA - 4u))
#define `$INSTANCE_NAME`_DB_RAM_LAST_ELEM_PTR   (  (reg32 *) (`$INSTANCE_NAME`_DFB__CSA_SRAM_DATA - 4u))


/***************************************
*       Register Constants
***************************************/

#define `$INSTANCE_NAME`_PM_ACT_MSK             (`$INSTANCE_NAME`_DFB__PM_ACT_MSK)
#define `$INSTANCE_NAME`_PM_STBY_MSK            (`$INSTANCE_NAME`_DFB__PM_STBY_MSK)

#define `$INSTANCE_NAME`_RUN_MASK               (0x01u)
#define `$INSTANCE_NAME`_CORECLK_DISABLE        (0x04u)
#define `$INSTANCE_NAME`_RAM_DIR_BUS            (0x3Fu)
#define `$INSTANCE_NAME`_RAM_DIR_DFB            (0x00u)
#define `$INSTANCE_NAME`_RAM_DPA_DIR            (0x10u)
#define `$INSTANCE_NAME`_RAM_DPB_DIR            (0x20u)

/* Mask for bits within DFB Coherency Register */
#define `$INSTANCE_NAME`_STGA_KEY_SHIFT         (0x00u)
#define `$INSTANCE_NAME`_STGB_KEY_SHIFT         (0x02u)
#define `$INSTANCE_NAME`_HOLDA_KEY_SHIFT        (0x04u)
#define `$INSTANCE_NAME`_HOLDB_KEY_SHIFT        (0x06u)

#define `$INSTANCE_NAME`_STGA_KEY_LOW           ((uint8) (0x00u << `$INSTANCE_NAME`_STGA_KEY_SHIFT))
#define `$INSTANCE_NAME`_STGA_KEY_MID           ((uint8) (0x01u << `$INSTANCE_NAME`_STGA_KEY_SHIFT))
#define `$INSTANCE_NAME`_STGA_KEY_HIGH          ((uint8) (0x02u << `$INSTANCE_NAME`_STGA_KEY_SHIFT))
#define `$INSTANCE_NAME`_STGB_KEY_LOW           ((uint8) (0x00u << `$INSTANCE_NAME`_STGB_KEY_SHIFT))
#define `$INSTANCE_NAME`_STGB_KEY_MID           ((uint8) (0x01u << `$INSTANCE_NAME`_STGB_KEY_SHIFT))
#define `$INSTANCE_NAME`_STGB_KEY_HIGH          ((uint8) (0x02u << `$INSTANCE_NAME`_STGB_KEY_SHIFT))
#define `$INSTANCE_NAME`_HOLDA_KEY_LOW          ((uint8) (0x00u << `$INSTANCE_NAME`_HOLDA_KEY_SHIFT))
#define `$INSTANCE_NAME`_HOLDA_KEY_MID          ((uint8) (0x01u << `$INSTANCE_NAME`_HOLDA_KEY_SHIFT))
#define `$INSTANCE_NAME`_HOLDA_KEY_HIGH         ((uint8) (0x02u << `$INSTANCE_NAME`_HOLDA_KEY_SHIFT))
#define `$INSTANCE_NAME`_HOLDB_KEY_LOW          ((uint8) (0x00u << `$INSTANCE_NAME`_HOLDB_KEY_SHIFT))
#define `$INSTANCE_NAME`_HOLDB_KEY_MID          ((uint8) (0x01u << `$INSTANCE_NAME`_HOLDB_KEY_SHIFT))
#define `$INSTANCE_NAME`_HOLDB_KEY_HIGH         ((uint8) (0x02u << `$INSTANCE_NAME`_HOLDB_KEY_SHIFT))

/* Mask for bits within DFB Data Alignment Register */
#define `$INSTANCE_NAME`_STGA_DALIGN_SHIFT      (0x00u)
#define `$INSTANCE_NAME`_STGB_DALIGN_SHIFT      (0x01u)
#define `$INSTANCE_NAME`_HOLDA_DALIGN_SHIFT     (0x02u)
#define `$INSTANCE_NAME`_HOLDB_DALIGN_SHIFT     (0x03u)

#define `$INSTANCE_NAME`_STGA_DALIGN_LOW        ((uint8) (0x00u << `$INSTANCE_NAME`_STGA_DALIGN_SHIFT))
#define `$INSTANCE_NAME`_STGA_DALIGN_HIGH       ((uint8) (0x01u << `$INSTANCE_NAME`_STGA_DALIGN_SHIFT))
#define `$INSTANCE_NAME`_STGB_DALIGN_LOW        ((uint8) (0x00u << `$INSTANCE_NAME`_STGB_DALIGN_SHIFT))
#define `$INSTANCE_NAME`_STGB_DALIGN_HIGH       ((uint8) (0x01u << `$INSTANCE_NAME`_STGB_DALIGN_SHIFT))
#define `$INSTANCE_NAME`_HOLDA_DALIGN_LOW       ((uint8) (0x00u << `$INSTANCE_NAME`_HOLDA_DALIGN_SHIFT))
#define `$INSTANCE_NAME`_HOLDA_DALIGN_HIGH      ((uint8) (0x01u << `$INSTANCE_NAME`_HOLDA_DALIGN_SHIFT))
#define `$INSTANCE_NAME`_HOLDB_DALIGN_LOW       ((uint8) (0x00u << `$INSTANCE_NAME`_HOLDB_DALIGN_SHIFT))
#define `$INSTANCE_NAME`_HOLDB_DALIGN_HIGH      ((uint8) (0x01u << `$INSTANCE_NAME`_HOLDB_DALIGN_SHIFT))

/* Mask for bits within DFB Interrupt Control and Status Registers */
#define `$INSTANCE_NAME`_SEM_MASK               (0x07u)
#define `$INSTANCE_NAME`_SEM_ENABLE_SHIFT       (0x04u)
#define `$INSTANCE_NAME`_EVENT_MASK             (0x1Fu)
#define `$INSTANCE_NAME`_SR_EVENT_SHIFT         (0x03u)

#define `$INSTANCE_NAME`_HOLDA_SHIFT            (0x00u)
#define `$INSTANCE_NAME`_HOLDB_SHIFT            (0x01u)
#define `$INSTANCE_NAME`_SEMA0_SHIFT            (0x02u)
#define `$INSTANCE_NAME`_SEMA1_SHIFT            (0x03u)
#define `$INSTANCE_NAME`_SEMA2_SHIFT            (0x04u)

#define `$INSTANCE_NAME`_HOLDA                  ((uint8) (0x01u << `$INSTANCE_NAME`_HOLDA_SHIFT))
#define `$INSTANCE_NAME`_HOLDB                  ((uint8) (0x01u << `$INSTANCE_NAME`_HOLDB_SHIFT))
#define `$INSTANCE_NAME`_SEMA0                  ((uint8) (0x01u << `$INSTANCE_NAME`_SEMA0_SHIFT))
#define `$INSTANCE_NAME`_SEMA1                  ((uint8) (0x01u << `$INSTANCE_NAME`_SEMA1_SHIFT))
#define `$INSTANCE_NAME`_SEMA2                  ((uint8) (0x01u << `$INSTANCE_NAME`_SEMA2_SHIFT))

/* Mask for bits within DFB DMAREQ Control Register */
#define `$INSTANCE_NAME`_DMA_CTRL_MASK          (0x0Fu)
#define `$INSTANCE_NAME`_DMAREQ1_DISABLED       (0x00u)
#define `$INSTANCE_NAME`_DMAREQ1_HOLDA          (0x01u)
#define `$INSTANCE_NAME`_DMAREQ1_SEM0           (0x02u)
#define `$INSTANCE_NAME`_DMAREQ1_SEM1           (0x03u)
#define `$INSTANCE_NAME`_DMAREQ2_DISABLED       (0x00u)
#define `$INSTANCE_NAME`_DMAREQ2_HOLDB          (0x04u)
#define `$INSTANCE_NAME`_DMAREQ2_SEM0           (0x08u)
#define `$INSTANCE_NAME`_DMAREQ2_SEM1           (0x0Cu)

/* Mask for bits within DFB Semaphore Register */
#define `$INSTANCE_NAME`_SEMAPHORE0             (0x01u)
#define `$INSTANCE_NAME`_SEMAPHORE1             (0x02u)
#define `$INSTANCE_NAME`_SEMAPHORE2             (0x04u)

/* Mask for bits within Global Control Register */
#define `$INSTANCE_NAME`_DFB_RUN                (0x00u)
#define `$INSTANCE_NAME`_SEM0                   (0x01u)
#define `$INSTANCE_NAME`_SEM1                   (0x02u)
#define `$INSTANCE_NAME`_DFB_INTR               (0x03u)
#define `$INSTANCE_NAME`_SEM2                   (0x00u)
#define `$INSTANCE_NAME`_DPSIGN                 (0x04u)
#define `$INSTANCE_NAME`_DPTHRESH               (0x08u)
#define `$INSTANCE_NAME`_DPEQ                   (0x0Cu)
#define `$INSTANCE_NAME`_DFB_GBL1_OUT_MASK      (0xFCu)
#define `$INSTANCE_NAME`_DFB_GBL2_OUT_MASK      (0xF3u)

#endif /* End DFB Header File */


/* [] END OF FILE */

