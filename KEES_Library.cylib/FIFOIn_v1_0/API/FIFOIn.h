/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
* This component provides a convenient interface from programmable hardware to
* the CPU or DMA.  That interface is implemented using the 4-entry FIFO in the
* UDB.
*
********************************************************************************
* Copyright (2010), Cypress Semiconductor Corporation.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is 
* protected by and subject to worldwide patent protection (United States and 
* foreign), United States copyright laws and international treaty provisions. 
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable 
* license to copy, use, modify, create derivative works of, and compile the 
* Cypress Source Code and derivative works for the sole purpose of creating 
* custom software in support of licensee product to be used only in conjunction 
* with a Cypress integrated circuit as specified in the applicable agreement. 
* Any reproduction, modification, translation, compilation, or representation of 
* this software except as specified above is prohibited without the express 
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH 
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the 
* materials described herein. Cypress does not assume any liability arising out 
* of the application or use of any product or circuit described herein. Cypress 
* does not authorize its products for use as critical components in life-support 
* systems where a malfunction or failure may reasonably be expected to result in 
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of 
* such use and in doing so indemnifies Cypress against all charges. Use may be 
* limited by and subject to the applicable Cypress software license agreement. 
*******************************************************************************/

#if !defined(FIFOIN_`$INSTANCE_NAME`_H)
#define FIFOIN_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

/*************************************** 
*   Conditional Compilation Parameters
***************************************/

#define `$INSTANCE_NAME`_BUS_WIDTH (`$BitWidth`u)

/* PSoC3 ES2 or early */
#define `$INSTANCE_NAME`_PSOC3_ES2   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A) && \
                                      (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2))
                     
/* PSoC5 ES1 */
#define `$INSTANCE_NAME`_PSOC5_ES1   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A) && \
                                      (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_5A_ES1)) 

/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct _`$INSTANCE_NAME`_backupStruct
{
    uint8 enableState;
    
    #if (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1)
        uint8 IntMask;
    #endif /* (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) */    
} `$INSTANCE_NAME`_BACKUP_STRUCT;

/***************************************
*    Initial Parameter Constants        
***************************************/
#define `$INSTANCE_NAME`_LVL_SETTING 	(`$HalfFullTrigger` ? `$INSTANCE_NAME`_FIFO_LVL : 0)

/***************************************
*       Register Constants              
***************************************/
#define `$INSTANCE_NAME`_EN           (0x01u)

#define `$INSTANCE_NAME`_FIFO_CLR 	(1 << 0)
#define `$INSTANCE_NAME`_FIFO_LVL 	(1 << 2)

#define `$INSTANCE_NAME`_ST_MASK   (0x02u)

/***************************************
*             Registers                 
***************************************/
#define `$INSTANCE_NAME`_CONTROL_REG      (* (reg8 *) `$INSTANCE_NAME`_`$CtlModeReplacementString`_ControlReg__CONTROL_REG)
#if (`$INSTANCE_NAME`_BUS_WIDTH == 8u)
	#define `$INSTANCE_NAME`_LSB_AUX_CONTROL_REG  (* (reg8 *) `$INSTANCE_NAME`_Single_singleDP__DP_AUX_CTL_REG)
#else
	#define `$INSTANCE_NAME`_LSB_AUX_CONTROL_REG  (* (reg8 *) `$INSTANCE_NAME`_Dual_lsbDP__DP_AUX_CTL_REG)
	#define `$INSTANCE_NAME`_MSB_AUX_CONTROL_REG  (* (reg8 *) `$INSTANCE_NAME`_Dual_msbDP__DP_AUX_CTL_REG)
#endif
#define `$INSTANCE_NAME`_STATUS_REG       (* (reg8 *) `$INSTANCE_NAME`_StsReg__STATUS_REG)
#define `$INSTANCE_NAME`_STATUS_MASK_REG  (* (reg8 *) `$INSTANCE_NAME`_StsReg__MASK_REG)

#if (`$INSTANCE_NAME`_BUS_WIDTH == 8u)
	#define `$INSTANCE_NAME`_FIFO_PTR	((reg8 *) `$INSTANCE_NAME`_Single_singleDP__F0_REG)
	#define `$INSTANCE_NAME`_FIFO_REG  	(*(reg8 *) `$INSTANCE_NAME`_Single_singleDP__F0_REG)
#else
	#define `$INSTANCE_NAME`_FIFO_PTR	((reg8 *) `$INSTANCE_NAME`_Dual_lsbDP__F0_REG)
	#define `$INSTANCE_NAME`_FIFO_REG  	(*(reg8 *) `$INSTANCE_NAME`_Dual_lsbDP__F0_REG)
	#define `$INSTANCE_NAME`_FIFO16_PTR	((reg16 *) `$INSTANCE_NAME`_Dual_lsbDP__16BIT_F0_REG)
#endif

/***************************************
*           API Constants               
***************************************/
#define `$INSTANCE_NAME`_FIFO_OVERFLOW        (0x01u)
#define `$INSTANCE_NAME`_FIFO_NOT_EMPTY       (0x02u)

/***************************************
 *   Function Prototypes
 **************************************/
void `$INSTANCE_NAME`_Start(void)           `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void `$INSTANCE_NAME`_Stop(void)            `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void `$INSTANCE_NAME`_Enable(void)          `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void `$INSTANCE_NAME`_Init(void)            `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void `$INSTANCE_NAME`_Disable(void)         `=ReentrantKeil($INSTANCE_NAME . "_Disable")`;
void `$INSTANCE_NAME`_ClearFIFO(void)       `=ReentrantKeil($INSTANCE_NAME . "_ClearFIFO")`;
#if (`$INSTANCE_NAME`_BUS_WIDTH == 8u)
	uint8 `$INSTANCE_NAME`_Read(void)           `=ReentrantKeil($INSTANCE_NAME . "_Read")`;
#else
	uint16 `$INSTANCE_NAME`_Read(void)           `=ReentrantKeil($INSTANCE_NAME . "_Read")`;
#endif
uint8 `$INSTANCE_NAME`_ReadStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadStatus")`;
void `$INSTANCE_NAME`_SetInterruptMode(uint8 interruptSource) `=ReentrantKeil($INSTANCE_NAME . "_SetInterruptMode")`;
void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;

#endif  /* FIFOIN_`$INSTANCE_NAME`_H */
