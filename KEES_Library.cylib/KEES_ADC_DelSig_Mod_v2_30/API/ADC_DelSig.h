/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Delta-Sigma ADC user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_ADC_DELSIG_`$INSTANCE_NAME`_H) 
#define CY_ADC_DELSIG_`$INSTANCE_NAME`_H 

#include "cytypes.h"
#include "cylib.h"
#include "cyfitter.h"
#include "cydevice_trm.h" 

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/***************************************
*       Type defines
***************************************/

/* Sleep Mode API Support */
typedef struct `$INSTANCE_NAME`_backupStruct 
{
    uint8 enableState;
    uint8 deccr;
}   `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*       Type defines
***************************************/

/* only valid for PSoCA */
#if (CY_PSOC5A)
    /* Power Mode register backup Support */
    typedef struct `$INSTANCE_NAME`_powerModeBackupStruct 
    {
        uint8 DSM_CR_14;
        uint8 DSM_CR_15;
        uint8 DSM_CR_16;
        uint8 DSM_CR_17;
        uint8 DSM_REF0;
        uint8 DSM_BUF0;
        uint8 DSM_BUF1;
        uint8 DSM_CLK;
        /* field to decide whether or not to save the registers 
           in the stop API*/
        uint8 bypassRestore;
    }   `$INSTANCE_NAME`_POWERMODE_BACKUP_STRUCT;
#endif /* CY_PSOC5A */


/***************************************
*        Function Prototypes 
***************************************/

void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`;   
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;
void `$INSTANCE_NAME`_SetBufferGain(uint8 gain) `=ReentrantKeil($INSTANCE_NAME . "_SetBufferGain")`;
void `$INSTANCE_NAME`_StartConvert(void) `=ReentrantKeil($INSTANCE_NAME . "_StartConvert")`;
void `$INSTANCE_NAME`_SetCoherency(uint8 coherency) `=ReentrantKeil($INSTANCE_NAME . "_SetCoherency")`;
uint8 `$INSTANCE_NAME`_SetGCOR(float gainAdjust) `=ReentrantKeil($INSTANCE_NAME . "_SetGCOR")`;
uint16 `$INSTANCE_NAME`_ReadGCOR(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadGCOR")`;
void `$INSTANCE_NAME`_StopConvert(void) `=ReentrantKeil($INSTANCE_NAME . "_StopConvert")`;
void `$INSTANCE_NAME`_SetOffset(int32 offset) `=ReentrantKeil($INSTANCE_NAME . "_SetOffset")`; 
void `$INSTANCE_NAME`_SetGain(int32 adcGain) `=ReentrantKeil($INSTANCE_NAME . "_SetGain")`; 
int8 `$INSTANCE_NAME`_GetResult8(void) `=ReentrantKeil($INSTANCE_NAME . "_GetResult8")`;
int16 `$INSTANCE_NAME`_GetResult16(void) `=ReentrantKeil($INSTANCE_NAME . "_GetResult16")`;
int32 `$INSTANCE_NAME`_GetResult32(void) `=ReentrantKeil($INSTANCE_NAME . "_GetResult32")`;
uint8 `$INSTANCE_NAME`_IsEndConversion(uint8 retMode) `=ReentrantKeil($INSTANCE_NAME . "_IsEndConversion")`;
int16 `$INSTANCE_NAME`_CountsTo_mVolts( int32 adcCounts) `=ReentrantKeil($INSTANCE_NAME . "_CountsTo_mVolts")`; 
float `$INSTANCE_NAME`_CountsTo_Volts( int32 adcCounts) `=ReentrantKeil($INSTANCE_NAME . "_CountsTo_Volts")`; 
int32 `$INSTANCE_NAME`_CountsTo_uVolts( int32 adcCounts) `=ReentrantKeil($INSTANCE_NAME . "_CountsTo_uVolts")`;
CY_ISR_PROTO(`$INSTANCE_NAME`_ISR1);
CY_ISR_PROTO(`$INSTANCE_NAME`_ISR2);
CY_ISR_PROTO(`$INSTANCE_NAME`_ISR3);
CY_ISR_PROTO(`$INSTANCE_NAME`_ISR4);
void `$INSTANCE_NAME`_SelectConfiguration(uint8 config, uint8 restart) \
                                           `=ReentrantKeil($INSTANCE_NAME . "_SelectConfiguration")`;
void `$INSTANCE_NAME`_InitConfig(uint8 config) `=ReentrantKeil($INSTANCE_NAME . "_InitConfig")`;
void `$INSTANCE_NAME`_GainCompensation(uint8 inputRange, uint16 IdealDecGain, uint16 IdealOddDecGain, uint8 resolution)\
                                              `=ReentrantKeil($INSTANCE_NAME . "_GainCompensation")`;
#if (CY_PSOC5A)
    void `$INSTANCE_NAME`_SavePowerRegisters(void) `=ReentrantKeil($INSTANCE_NAME . "_SavePowerRegisters")`;
    void `$INSTANCE_NAME`_RestorePowerRegisters(void) `=ReentrantKeil($INSTANCE_NAME . "_RestorePowerRegisters")`;
    void `$INSTANCE_NAME`_SetLowPower(void) `=ReentrantKeil($INSTANCE_NAME . "_SetLowPower")`;
#endif /* CY_PSOC5A */
uint16 `$INSTANCE_NAME`_RoundValue(uint32 busClockFreq, uint32 clockFreq) \
                                              `=ReentrantKeil($INSTANCE_NAME . "_RoundValue")`;
void `$INSTANCE_NAME`_SetDSMRef0Reg(uint8 value) `=ReentrantKeil($INSTANCE_NAME . "_SetDSMRef0Reg")`;

/* These functions may not be supported in the released version */
void    `$INSTANCE_NAME`_SetBufferChop(uint8 chopen, uint8 chopFreq) \
                                                  `=ReentrantKeil($INSTANCE_NAME . "_SetBufferChop")`;
#define `$INSTANCE_NAME`_IRQ_Enable() CyIntEnable(`$INSTANCE_NAME`_IRQ__INTC_NUMBER ); 
#define `$INSTANCE_NAME`_IRQ_Disable() CyIntDisable(`$INSTANCE_NAME`_IRQ__INTC_NUMBER );


/*******************************************************************************
* The following API?s are to support legacy code.  The IRQ_Start
* And IRQ_Stop routine have been replaced by the library source code
* for interrupts. IRQ_Start() and IRQ_Stop() should not be used in new
* designs
*******************************************************************************/
void `$INSTANCE_NAME`_IRQ_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_IRQ_Start")`;
#define `$INSTANCE_NAME`_IRQ_Stop() CyIntDisable(`$INSTANCE_NAME`_IRQ__INTC_NUMBER )


/**************************************
*           Parameter Defaults        
**************************************/

/* Default config values from user parameters */

#define `$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION         (`$ADC_Resolution`u )
#define `$INSTANCE_NAME`_`$Config1_Name`_RANGE              (`$ADC_Input_Range`u)    
#define `$INSTANCE_NAME`_`$Config1_Name`_SRATE              (`$Sample_Rate`u)         
#define `$INSTANCE_NAME`_`$Config1_Name`_REFERENCE          (`$ADC_Reference`u)       
#define `$INSTANCE_NAME`_`$Config1_Name`_BUF_GAIN           (`$Input_Buffer_Gain`u)   
#define `$INSTANCE_NAME`_`$Config1_Name`_CONV_MODE          (`$Conversion_Mode`u)     
#define `$INSTANCE_NAME`_`$Config1_Name`_RANGE_VALUE        (`$ADC_Input_RangeValue`)
#define `$INSTANCE_NAME`_DEFAULT_STROBE                     (`$Start_of_Conversion`u) 
#define `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK               (`$ADC_Clock`u)           
#define `$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS                (`$Configs`u)    
#define `$INSTANCE_NAME`_DEFAULT_CHARGE_PUMP_CLOCK          (`$ADC_Charge_Pump_Clock`u)    
#define `$INSTANCE_NAME`_DEFAULT_INPUT_MODE                 (`$ADC_Input_Mode`u)

/* Config Constants which can be used as the "config" parameter of
   `$INSTANCE_NAME`_SelectConfiguration() API. */
#define `$INSTANCE_NAME`_`$Config1_Name`        1
#define `$INSTANCE_NAME`_`$Config2_Name`        2
#define `$INSTANCE_NAME`_`$Config3_Name`        3
#define `$INSTANCE_NAME`_`$Config4_Name`        4


/**************************************
*           API Constants        
**************************************/

/* Component's enable/disable state */
#define `$INSTANCE_NAME`_ENABLED                    (0x01u)
#define `$INSTANCE_NAME`_DISABLED                   (0x00u)

/* Defines for deciding whether or not to restore the 
   power registers in Enable API. Valid only for PSoC5A*/
#if (CY_PSOC5A)
    #define `$INSTANCE_NAME`_BYPASS_ENABLED                    (0x01u)
    #define `$INSTANCE_NAME`_BYPASS_DISABLED                   (0x00u)
#endif /* CY_PSOC5A */

/* Ideal Gain Constant */
#define `$INSTANCE_NAME`_IDEAL_GAIN_CONST           (0x8000u)

/* Gvalue constant */
#define `$INSTANCE_NAME`_MAX_GVAL                   (0x0Fu)

/* Gvalue constants based on resolution */
#define `$INSTANCE_NAME`_GVAL_RESOLUTIN_8           (0x09u)
#define `$INSTANCE_NAME`_GVAL_RESOLUTIN_9           (0x0Au)
#define `$INSTANCE_NAME`_GVAL_RESOLUTIN_10          (0x0Bu)
#define `$INSTANCE_NAME`_GVAL_RESOLUTIN_11          (0x0Cu)
#define `$INSTANCE_NAME`_GVAL_RESOLUTIN_12          (0x0Du)
#define `$INSTANCE_NAME`_GVAL_RESOLUTIN_13          (0x0Eu)

/* Constants for SetPower(), "power" paramter */
#define `$INSTANCE_NAME`_LOWPOWER                   (0x00u) 
#define `$INSTANCE_NAME`_MEDPOWER                   (0x01u) 
#define `$INSTANCE_NAME`_HIGHPOWER                  (0x02u) 
#define `$INSTANCE_NAME`_HIGHPOWER_1_5              (0x03u)  /* Reserved */
#define `$INSTANCE_NAME`_HIGHPOWER_2_0              (0x04u)  /* Reserved */
#define `$INSTANCE_NAME`_HIGHPOWER_2_5              (0x07u)  /* Reserved */
#define `$INSTANCE_NAME`_POWER_MASK                 (0x07u) 

/* Constants for SetBufferGain() "gain" paramter */
#define `$INSTANCE_NAME`_BUF_GAIN_1X                (0x00u) 
#define `$INSTANCE_NAME`_BUF_GAIN_2X                (0x01u) 
#define `$INSTANCE_NAME`_BUF_GAIN_4X                (0x02u) 
#define `$INSTANCE_NAME`_BUF_GAIN_8X                (0x03u) 
#define `$INSTANCE_NAME`_BUF_GAIN_MASK              (0x03u)

/* Constants for IsEndConversion() "retMode" parameter */
#define `$INSTANCE_NAME`_RETURN_STATUS              (0x01u) 
#define `$INSTANCE_NAME`_WAIT_FOR_RESULT            (0x00u)

/* Constants for input range parameter */

#define `$INSTANCE_NAME`_IR_VSSA_TO_VREF            (0x00u)
#define `$INSTANCE_NAME`_IR_VSSA_TO_2VREF           (0x01u)
#define `$INSTANCE_NAME`_IR_VSSA_TO_VDDA            (0x02u)
#define `$INSTANCE_NAME`_IR_VSSA_TO_6VREF           (0x03u)
#define `$INSTANCE_NAME`_IR_VNEG_VREF_DIFF          (0x04u)
#define `$INSTANCE_NAME`_IR_VNEG_2VREF_DIFF         (0x05u)
#define `$INSTANCE_NAME`_IR_VNEG_6VREF_DIFF         (0x06u)
#define `$INSTANCE_NAME`_IR_VNEG_VREF_2_DIFF        (0x07u)
#define `$INSTANCE_NAME`_IR_VNEG_VREF_4_DIFF        (0x08u)
#define `$INSTANCE_NAME`_IR_VNEG_VREF_8_DIFF        (0x09u)
#define `$INSTANCE_NAME`_IR_VNEG_VREF_16_DIFF       (0x0Au)

/* Constants for ADC reference parameter */

#define `$INSTANCE_NAME`_INT_REF_NOT_BYPASSED       (0x00u)
#define `$INSTANCE_NAME`_INT_REF_BYPASSED_ON_P03    (0x01u)
#define `$INSTANCE_NAME`_INT_REF_BYPASSED_ON_P32    (0x02u)
#define `$INSTANCE_NAME`_EXT_REF_ON_P03             (0x03u)
#define `$INSTANCE_NAME`_EXT_REF_ON_P32             (0x04u)
#define `$INSTANCE_NAME`_INT_REF_VDDA_4             (0x05u)
#define `$INSTANCE_NAME`_INT_REF_VDDA_3             (0x06u)

/* Priority of the ADC_IRQ interrupt. */
#define `$INSTANCE_NAME`_IRQ_INTC_PRIOR_NUMBER      `$INSTANCE_NAME`_IRQ__INTC_PRIOR_NUM

/* Constants for ADC coherency parameter */

#define `$INSTANCE_NAME`_COHER_LOW                  (0x01u) 
#define `$INSTANCE_NAME`_COHER_MID                  (0x02u) 
#define `$INSTANCE_NAME`_COHER_HIGH                 (0x03u)

/* Trim value defines */

#if (CY_PSOC3 || CY_PSOC5LP)
    #define `$INSTANCE_NAME`_DEC_TRIM_VREF_DIFF_8_15        (CY_GET_XTND_REG8(`$INSTANCE_NAME`_DEC__TRIM__M5))
    #define `$INSTANCE_NAME`_DEC_TRIM_VREF_DIFF_16_20       (CY_GET_XTND_REG8(`$INSTANCE_NAME`_DEC__TRIM__M1))
    #define `$INSTANCE_NAME`_DEC_TRIM_VREF_2_DIFF_8_15      (CY_GET_XTND_REG8(`$INSTANCE_NAME`_DEC__TRIM__M6))
    #define `$INSTANCE_NAME`_DEC_TRIM_VREF_2_DIFF_16_20     (CY_GET_XTND_REG8(`$INSTANCE_NAME`_DEC__TRIM__M2))
    #define `$INSTANCE_NAME`_DEC_TRIM_VREF_4_DIFF_8_15      (CY_GET_XTND_REG8(`$INSTANCE_NAME`_DEC__TRIM__M7))
    #define `$INSTANCE_NAME`_DEC_TRIM_VREF_4_DIFF_16_20     (CY_GET_XTND_REG8(`$INSTANCE_NAME`_DEC__TRIM__M3))
    #define `$INSTANCE_NAME`_DEC_TRIM_VREF_16_DIFF_8_15     (CY_GET_XTND_REG8(`$INSTANCE_NAME`_DEC__TRIM__M8))
    #define `$INSTANCE_NAME`_DEC_TRIM_VREF_16_DIFF_16_20    (CY_GET_XTND_REG8(`$INSTANCE_NAME`_DEC__TRIM__M4))
#elif (CY_PSOC5A)
    #define `$INSTANCE_NAME`_DEC_TRIM_VREF_DIFF_8_15        (CY_GET_XTND_REG8(`$INSTANCE_NAME`_DEC__TRIM__16L))
    #define `$INSTANCE_NAME`_DEC_TRIM_VREF_DIFF_16_20       (CY_GET_XTND_REG8(`$INSTANCE_NAME`_DEC__TRIM__1L))
    #define `$INSTANCE_NAME`_DEC_TRIM_VREF_2_DIFF_8_15      (CY_GET_XTND_REG8(`$INSTANCE_NAME`_DEC__TRIM__16H))
    #define `$INSTANCE_NAME`_DEC_TRIM_VREF_2_DIFF_16_20     (CY_GET_XTND_REG8(`$INSTANCE_NAME`_DEC__TRIM__1H))
    #define `$INSTANCE_NAME`_DEC_TRIM_VREF_4_DIFF_8_15      (CY_GET_XTND_REG8(`$INSTANCE_NAME`_DEC__TRIM__P25L))
    #define `$INSTANCE_NAME`_DEC_TRIM_VREF_4_DIFF_16_20     (CY_GET_XTND_REG8(`$INSTANCE_NAME`_DEC__TRIM__4L))
    #define `$INSTANCE_NAME`_DEC_TRIM_VREF_16_DIFF_8_15     (CY_GET_XTND_REG8(`$INSTANCE_NAME`_DEC__TRIM__P25H))
    #define `$INSTANCE_NAME`_DEC_TRIM_VREF_16_DIFF_16_20    (CY_GET_XTND_REG8(`$INSTANCE_NAME`_DEC__TRIM__4H))

#endif /* CY_PSOC5A */


/**************************************
*      Unsupported API Constants        
**************************************/

/* Constants for SetBuffer() "bufMode" parameter */   
#define `$INSTANCE_NAME`_BUF_DIFF_MODE              (0x00u)  /* Differential mode */
#define `$INSTANCE_NAME`_BUF_BYPASS_POS             (0x04u)  /* Bypass and power down positive channel */
#define `$INSTANCE_NAME`_BUF_BYPASS_NEG             (0x08u)  /* Bypass and power down negative channel */
#define `$INSTANCE_NAME`_BUF_RAIL_TO_RAIL           (0x10u)  /* Enables Rail-to-rail mode */
#define `$INSTANCE_NAME`_BUF_FILTER_EN              (0x20u)  /* Output filter enable */
#define `$INSTANCE_NAME`_BUF_LOW_PWR                (0x40u)  /* Enable  Low power mode */

/* Constants for SetInputRange() "inputMode" parameter */
#define `$INSTANCE_NAME`_INMODE_VSSA_TO_VREF        (0x00u) 
#define `$INSTANCE_NAME`_INMODE_VSSA_TO_2VREF       (0x01u) 
#define `$INSTANCE_NAME`_INMODE_VSSA_TO_VDDA        (0x02u) 
#define `$INSTANCE_NAME`_INMODE_VNEG_PM_VREF_DIFF   (0x03u) 
#define `$INSTANCE_NAME`_INMODE_VNEG_PM_2VREF_DIFF  (0x04u)

/* Constants for SetBufferChop() "chopen" parameter */
#define `$INSTANCE_NAME`_BUF_CHOP_ENABLE            (0x01u)
#define `$INSTANCE_NAME`_BUF_CHOP_DISABLE           (0x00u)

/* Constants for SetBufferChop() "chopFreq" parameter */
#define `$INSTANCE_NAME`_BUF_CHOP_FREQ_FS2          (0x00u) 
#define `$INSTANCE_NAME`_BUF_CHOP_FREQ_FS4          (0x01u) 
#define `$INSTANCE_NAME`_BUF_CHOP_FREQ_FS8          (0x02u) 
#define `$INSTANCE_NAME`_BUF_CHOP_FREQ_FS16         (0x03u) 
#define `$INSTANCE_NAME`_BUF_CHOP_FREQ_FS32         (0x04u) 
#define `$INSTANCE_NAME`_BUF_CHOP_FREQ_FS64         (0x05u) 
#define `$INSTANCE_NAME`_BUF_CHOP_FREQ_FS128        (0x06u) 
#define `$INSTANCE_NAME`_BUF_CHOP_FREQ_FS256        (0x07u) 

/* Constants for custom reference mode settings */
#define `$INSTANCE_NAME`_REF_INTREF                 (0x80u) 
#define `$INSTANCE_NAME`_REF_REFMODE_MASK           (0x07u) 
#define `$INSTANCE_NAME`_INTREF_MASK                (0x07u)

#define `$INSTANCE_NAME`_MIN_RES                    (8u)
#define `$INSTANCE_NAME`_MAX_RES                    (20u) 


/**************************************
*       Register Constants        
**************************************/


/******************************************/
/* DSM.CR0 Control Register 0 definitions */
/******************************************/

/* Bit Field  DSM_NONOV */
#define `$INSTANCE_NAME`_DSM_NONOV_MASK             (0x0Cu)
#define `$INSTANCE_NAME`_DSM_NONOV_LOW              (0x00u)
#define `$INSTANCE_NAME`_DSM_NONOV_MED              (0x04u)
#define `$INSTANCE_NAME`_DSM_NONOV_HIGH             (0x08u)
#define `$INSTANCE_NAME`_DSM_NONOV_VHIGH            (0x0Cu)

/* Bit Field  DSM_QLEV */
#define `$INSTANCE_NAME`_DSM_QLEV_MASK              (0x03u)
#define `$INSTANCE_NAME`_DSM_QLEV_2                 (0x00u)
#define `$INSTANCE_NAME`_DSM_QLEV_3                 (0x01u)
#define `$INSTANCE_NAME`_DSM_QLEV_9                 (0x02u)
#define `$INSTANCE_NAME`_DSM_QLEV_9x                (0x03u)


/******************************************/
/* DSM.CR1 Control Register 1 definitions */
/******************************************/
#define `$INSTANCE_NAME`_DSM_ODET_TH_MASK           (0x1Fu)
#define `$INSTANCE_NAME`_DSM_ODEN                   (0x20u)
#define `$INSTANCE_NAME`_DSM_DPMODE                 (0x40u)


/******************************************/
/* DSM.CR2 Control Register 2 definitions */
/******************************************/

/* Bit Field  DSM_FCHOP */
#define `$INSTANCE_NAME`_DSM_FCHOP_MASK             (0x07u)
#define `$INSTANCE_NAME`_DSM_FCHOP_DIV2             (0x00u)
#define `$INSTANCE_NAME`_DSM_FCHOP_DIV4             (0x01u)
#define `$INSTANCE_NAME`_DSM_FCHOP_DIV8             (0x02u)
#define `$INSTANCE_NAME`_DSM_FCHOP_DIV16            (0x03u)
#define `$INSTANCE_NAME`_DSM_FCHOP_DIV32            (0x04u)
#define `$INSTANCE_NAME`_DSM_FCHOP_DIV64            (0x05u)
#define `$INSTANCE_NAME`_DSM_FCHOP_DIV128           (0x06u)
#define `$INSTANCE_NAME`_DSM_FCHOP_DIV256           (0x07u)

/* Bit Field  DSM_MOD_CHOP_EN */
#define `$INSTANCE_NAME`_DSM_MOD_CHOP_EN            (0x08u)

/* Bit Field  DSM_MX_RESET */
#define `$INSTANCE_NAME`_DSM_MX_RESET               (0x80u)

/* Bit Field  DSM_RESET1_EN */
#define `$INSTANCE_NAME`_DSM_RESET1_EN              (0x10u)

/* Bit Field  DSM_RESET2_EN */
#define `$INSTANCE_NAME`_DSM_RESET2_EN              (0x20u)

/* Bit Field  DSM_RESET3_EN */
#define `$INSTANCE_NAME`_DSM_RESET3_EN              (0x40u)


/******************************************/
/* DSM.CR3 Control Register 3 definitions */
/******************************************/

/* Bit Field  DSM_SELECT_MOD_BIT */
#define `$INSTANCE_NAME`_DSM_MODBITIN_MASK          (0x0Fu)
#define `$INSTANCE_NAME`_DSM_MODBITIN_LUT0          (0x00u)
#define `$INSTANCE_NAME`_DSM_MODBITIN_LUT1          (0x01u)
#define `$INSTANCE_NAME`_DSM_MODBITIN_LUT2          (0x02u)
#define `$INSTANCE_NAME`_DSM_MODBITIN_LUT3          (0x03u)
#define `$INSTANCE_NAME`_DSM_MODBITIN_LUT4          (0x04u)
#define `$INSTANCE_NAME`_DSM_MODBITIN_LUT5          (0x05u)
#define `$INSTANCE_NAME`_DSM_MODBITIN_LUT6          (0x06u)
#define `$INSTANCE_NAME`_DSM_MODBITIN_LUT7          (0x07u)
#define `$INSTANCE_NAME`_DSM_MODBITIN_UDB           (0x08u)

/* Bit Field  DSM_MODBIT_EN */
#define `$INSTANCE_NAME`_DSM_MODBIT_EN              (0x10u)

/* Bit Field  DSM_MX_DOUT */
#define `$INSTANCE_NAME`_DSM_MX_DOUT_8BIT           (0x00u)
#define `$INSTANCE_NAME`_DSM_MX_DOUT_2SCOMP         (0x20u)

/* Bit Field  DSM_MODBIT  TBD */
#define `$INSTANCE_NAME`_DSM_MODBIT                 (0x40u)

/* Bit Field  DSM_SIGN */
#define `$INSTANCE_NAME`_DSM_SIGN_NINV              (0x00u)
#define `$INSTANCE_NAME`_DSM_SIGN_INV               (0x80u)


/******************************************/
/* DSM.CR4 Control Register 4 definitions */
/******************************************/

/* Bit Field  DSM_SELECT_FCAP_EN */
#define `$INSTANCE_NAME`_DSM_FCAP1_EN               (0x80u)
#define `$INSTANCE_NAME`_DSM_FCAP1_DIS              (0x00u)

/* Bit Field  DSM_SELECT_FCAP1 */
#define `$INSTANCE_NAME`_DSM_FCAP1_MASK             (0x7Fu)
#define `$INSTANCE_NAME`_DSM_FCAP1_MIN              (0x00u)
#define `$INSTANCE_NAME`_DSM_FCAP1_MAX              (0x7Fu)
#define `$INSTANCE_NAME`_DSM_FCAP1_100FF            (0x01u)
#define `$INSTANCE_NAME`_DSM_FCAP1_200FF            (0x02u)
#define `$INSTANCE_NAME`_DSM_FCAP1_400FF            (0x04u)
#define `$INSTANCE_NAME`_DSM_FCAP1_800FF            (0x08u)
#define `$INSTANCE_NAME`_DSM_FCAP1_1600FF           (0x10u)
#define `$INSTANCE_NAME`_DSM_FCAP1_3200FF           (0x20u)
#define `$INSTANCE_NAME`_DSM_FCAP1_6400FF           (0x40u)


/******************************************/
/* DSM.CR5 Control Register 5 definitions */
/******************************************/

/* Bit Field  DSM_SELECT_IPCAP_EN */
#define `$INSTANCE_NAME`_DSM_IPCAP1_EN              (0x80u)
#define `$INSTANCE_NAME`_DSM_IPCAP1_DIS             (0x00u)

/* Bit Field  DSM_SELECT_IPCAP1 */
#define `$INSTANCE_NAME`_DSM_IPCAP1_MASK            (0x7Fu)
#define `$INSTANCE_NAME`_DSM_IPCAP1_MIN             (0x00u)
#define `$INSTANCE_NAME`_DSM_IPCAP1_MAX             (0x7Fu)
#define `$INSTANCE_NAME`_DSM_IPCAP1_96FF            (0x01u)
#define `$INSTANCE_NAME`_DSM_IPCAP1_192FF           (0x02u)
#define `$INSTANCE_NAME`_DSM_IPCAP1_400FF           (0x04u)
#define `$INSTANCE_NAME`_DSM_IPCAP1_800FF           (0x08u)
#define `$INSTANCE_NAME`_DSM_IPCAP1_1600FF          (0x10u)
#define `$INSTANCE_NAME`_DSM_IPCAP1_3200FF          (0x20u)
#define `$INSTANCE_NAME`_DSM_IPCAP1_6400FF          (0x40u)


/******************************************/
/* DSM.CR6 Control Register 6 definitions */
/******************************************/

/* Bit Field  DSM_SELECT_DACCAP_EN */
#define `$INSTANCE_NAME`_DSM_DACCAP_EN              (0x40u)
#define `$INSTANCE_NAME`_DSM_DACCAP_DIS             (0x00u)

/* Bit Field  DSM_SELECT_DACCAP */
#define `$INSTANCE_NAME`_DSM_DACCAP_MASK            (0x3Fu)
#define `$INSTANCE_NAME`_DSM_DACCAP_MIN             (0x00u)
#define `$INSTANCE_NAME`_DSM_DACCAP_MAX             (0x3Fu)
#define `$INSTANCE_NAME`_DSM_DACCAP_96FF            (0x01u)
#define `$INSTANCE_NAME`_DSM_DACCAP_192FF           (0x02u)
#define `$INSTANCE_NAME`_DSM_DACCAP_400FF           (0x04u)
#define `$INSTANCE_NAME`_DSM_DACCAP_800FF           (0x08u)
#define `$INSTANCE_NAME`_DSM_DACCAP_1600FF          (0x10u)
#define `$INSTANCE_NAME`_DSM_DACCAP_3200FF          (0x20u)


/******************************************/
/* DSM.CR7 Control Register 7 definitions */
/******************************************/

/* Bit Field  DSM_SELECT_RESCAP_EN */
#define `$INSTANCE_NAME`_DSM_RESCAP_EN              (0x08u)
#define `$INSTANCE_NAME`_DSM_RESCAP_DIS             (0x00u)

/* Bit Field  DSM_SELECT_RESCAP */
#define `$INSTANCE_NAME`_DSM_RESCAP_MASK            (0x07u)
#define `$INSTANCE_NAME`_DSM_RESCAP_MIN             (0x00u)
#define `$INSTANCE_NAME`_DSM_RESCAP_MAX             (0x07u)
#define `$INSTANCE_NAME`_DSM_RESCAP_12FF            (0x00u)
#define `$INSTANCE_NAME`_DSM_RESCAP_24FF            (0x01u)
#define `$INSTANCE_NAME`_DSM_RESCAP_36FF            (0x02u)
#define `$INSTANCE_NAME`_DSM_RESCAP_48FF            (0x03u)
#define `$INSTANCE_NAME`_DSM_RESCAP_60FF            (0x04u)
#define `$INSTANCE_NAME`_DSM_RESCAP_72FF            (0x05u)
#define `$INSTANCE_NAME`_DSM_RESCAP_84FF            (0x06u)
#define `$INSTANCE_NAME`_DSM_RESCAP_96FF            (0x07u)

#define `$INSTANCE_NAME`_DSM_FCAP2_DIS              (0x00u)
#define `$INSTANCE_NAME`_DSM_FCAP2_EN               (0x80u)

#define `$INSTANCE_NAME`_DSM_FCAP3_DIS              (0x00u)
#define `$INSTANCE_NAME`_DSM_FCAP3_EN               (0x40u)

#define `$INSTANCE_NAME`_DSM_IPCAP1OFFSET           (0x20u)
#define `$INSTANCE_NAME`_DSM_FPCAP1OFFSET           (0x10u)


/******************************************/
/* DSM.CR8 Control Register 8 definitions */
/******************************************/

#define `$INSTANCE_NAME`_DSM_IPCAP2_EN              (0x80u)

#define `$INSTANCE_NAME`_DSM_IPCAP2_MASK            (0x70u)
#define `$INSTANCE_NAME`_DSM_IPCAP2_0_FF            (0x00u)
#define `$INSTANCE_NAME`_DSM_IPCAP2_50_FF           (0x10u)
#define `$INSTANCE_NAME`_DSM_IPCAP2_100_FF          (0x20u)
#define `$INSTANCE_NAME`_DSM_IPCAP2_150_FF          (0x30u)
#define `$INSTANCE_NAME`_DSM_IPCAP2_200_FF          (0x40u)
#define `$INSTANCE_NAME`_DSM_IPCAP2_250_FF          (0x50u)
#define `$INSTANCE_NAME`_DSM_IPCAP2_300_FF          (0x60u)
#define `$INSTANCE_NAME`_DSM_IPCAP2_350_FF          (0x70u)

#define `$INSTANCE_NAME`_DSM_FCAP2_MASK             (0x0Fu)
#define `$INSTANCE_NAME`_DSM_FCAP2_0_FF             (0x00u)
#define `$INSTANCE_NAME`_DSM_FCAP2_50_FF            (0x01u)
#define `$INSTANCE_NAME`_DSM_FCAP2_100_FF           (0x02u)
#define `$INSTANCE_NAME`_DSM_FCAP2_150_FF           (0x03u)
#define `$INSTANCE_NAME`_DSM_FCAP2_200_FF           (0x04u)
#define `$INSTANCE_NAME`_DSM_FCAP2_250_FF           (0x05u)
#define `$INSTANCE_NAME`_DSM_FCAP2_300_FF           (0x06u)
#define `$INSTANCE_NAME`_DSM_FCAP2_350_FF           (0x07u)
#define `$INSTANCE_NAME`_DSM_FCAP2_400_FF           (0x08u)
#define `$INSTANCE_NAME`_DSM_FCAP2_450_FF           (0x09u)
#define `$INSTANCE_NAME`_DSM_FCAP2_500_FF           (0x0Au)
#define `$INSTANCE_NAME`_DSM_FCAP2_550_FF           (0x0Bu)
#define `$INSTANCE_NAME`_DSM_FCAP2_600_FF           (0x0Cu)
#define `$INSTANCE_NAME`_DSM_FCAP2_650_FF           (0x0Du)
#define `$INSTANCE_NAME`_DSM_FCAP2_700_FF           (0x0Eu)
#define `$INSTANCE_NAME`_DSM_FCAP2_750_FF           (0x0Fu)


/******************************************/
/* DSM.CR9 Control Register 9 definitions */
/******************************************/

#define `$INSTANCE_NAME`_DSM_IPCAP3_EN              (0x80u)

#define `$INSTANCE_NAME`_DSM_IPCAP3_MASK            (0x70u)
#define `$INSTANCE_NAME`_DSM_IPCAP3_0_FF            (0x00u)
#define `$INSTANCE_NAME`_DSM_IPCAP3_50_FF           (0x10u)
#define `$INSTANCE_NAME`_DSM_IPCAP3_100_FF          (0x20u)
#define `$INSTANCE_NAME`_DSM_IPCAP3_150_FF          (0x30u)
#define `$INSTANCE_NAME`_DSM_IPCAP3_200_FF          (0x40u)
#define `$INSTANCE_NAME`_DSM_IPCAP3_250_FF          (0x50u)
#define `$INSTANCE_NAME`_DSM_IPCAP3_300_FF          (0x60u)
#define `$INSTANCE_NAME`_DSM_IPCAP3_350_FF          (0x70u)

#define `$INSTANCE_NAME`_DSM_FCAP3_MASK             (0x0Fu)
#define `$INSTANCE_NAME`_DSM_FCAP3_0_FF             (0x00u)
#define `$INSTANCE_NAME`_DSM_FCAP3_50_FF            (0x01u)
#define `$INSTANCE_NAME`_DSM_FCAP3_100_FF           (0x02u)
#define `$INSTANCE_NAME`_DSM_FCAP3_150_FF           (0x03u)
#define `$INSTANCE_NAME`_DSM_FCAP3_200_FF           (0x04u)
#define `$INSTANCE_NAME`_DSM_FCAP3_250_FF           (0x05u)
#define `$INSTANCE_NAME`_DSM_FCAP3_300_FF           (0x06u)
#define `$INSTANCE_NAME`_DSM_FCAP3_350_FF           (0x07u)
#define `$INSTANCE_NAME`_DSM_FCAP3_400_FF           (0x08u)
#define `$INSTANCE_NAME`_DSM_FCAP3_450_FF           (0x09u)
#define `$INSTANCE_NAME`_DSM_FCAP3_500_FF           (0x0Au)
#define `$INSTANCE_NAME`_DSM_FCAP3_550_FF           (0x0Bu)
#define `$INSTANCE_NAME`_DSM_FCAP3_600_FF           (0x0Cu)
#define `$INSTANCE_NAME`_DSM_FCAP3_650_FF           (0x0Du)
#define `$INSTANCE_NAME`_DSM_FCAP3_700_FF           (0x0Eu)
#define `$INSTANCE_NAME`_DSM_FCAP3_750_FF           (0x0Fu)


/********************************************/
/* DSM.CR10 Control Register 10 definitions */
/********************************************/

#define `$INSTANCE_NAME`_DSM_SUMCAP1_EN             (0x80u)
#define `$INSTANCE_NAME`_DSM_SUMCAP2_EN             (0x08u)

#define `$INSTANCE_NAME`_DSM_SUMCAP1_MASK           (0x70u)
#define `$INSTANCE_NAME`_DSM_SUMCAP1_0_FF           (0x00u)
#define `$INSTANCE_NAME`_DSM_SUMCAP1_50_FF          (0x10u)
#define `$INSTANCE_NAME`_DSM_SUMCAP1_100_FF         (0x20u)
#define `$INSTANCE_NAME`_DSM_SUMCAP1_150_FF         (0x30u)
#define `$INSTANCE_NAME`_DSM_SUMCAP1_200_FF         (0x40u)
#define `$INSTANCE_NAME`_DSM_SUMCAP1_250_FF         (0x50u)
#define `$INSTANCE_NAME`_DSM_SUMCAP1_300_FF         (0x60u)
#define `$INSTANCE_NAME`_DSM_SUMCAP1_350_FF         (0x70u)

#define `$INSTANCE_NAME`_DSM_SUMCAP2_MASK           (0x07u)
#define `$INSTANCE_NAME`_DSM_SUMCAP2_0_FF           (0x00u)
#define `$INSTANCE_NAME`_DSM_SUMCAP2_50_FF          (0x01u)
#define `$INSTANCE_NAME`_DSM_SUMCAP2_100_FF         (0x02u)
#define `$INSTANCE_NAME`_DSM_SUMCAP2_150_FF         (0x03u)
#define `$INSTANCE_NAME`_DSM_SUMCAP2_200_FF         (0x04u)
#define `$INSTANCE_NAME`_DSM_SUMCAP2_250_FF         (0x05u)
#define `$INSTANCE_NAME`_DSM_SUMCAP2_300_FF         (0x06u)
#define `$INSTANCE_NAME`_DSM_SUMCAP2_350_FF         (0x07u)


/********************************************/
/* DSM.CR11 Control Register 11 definitions */
/********************************************/

#define `$INSTANCE_NAME`_DSM_SUMCAP3_EN             (0x08u)

#define `$INSTANCE_NAME`_DSM_SUMCAP3_MASK           (0x70u)
#define `$INSTANCE_NAME`_DSM_SUMCAP3_0_FF           (0x00u)
#define `$INSTANCE_NAME`_DSM_SUMCAP3_50_FF          (0x10u)
#define `$INSTANCE_NAME`_DSM_SUMCAP3_100_FF         (0x20u)
#define `$INSTANCE_NAME`_DSM_SUMCAP3_150_FF         (0x30u)
#define `$INSTANCE_NAME`_DSM_SUMCAP3_200_FF         (0x40u)
#define `$INSTANCE_NAME`_DSM_SUMCAP3_250_FF         (0x50u)
#define `$INSTANCE_NAME`_DSM_SUMCAP3_300_FF         (0x60u)
#define `$INSTANCE_NAME`_DSM_SUMCAP3_350_FF         (0x70u)

#define `$INSTANCE_NAME`_DSM_SUMCAPFB_MASK          (0x07u)
#define `$INSTANCE_NAME`_DSM_SUMCAPFB_0_FF          (0x00u)
#define `$INSTANCE_NAME`_DSM_SUMCAPFB_50_FF         (0x01u)
#define `$INSTANCE_NAME`_DSM_SUMCAPFB_100_FF        (0x02u)
#define `$INSTANCE_NAME`_DSM_SUMCAPFB_150_FF        (0x03u)
#define `$INSTANCE_NAME`_DSM_SUMCAPFB_200_FF        (0x04u)
#define `$INSTANCE_NAME`_DSM_SUMCAPFB_250_FF        (0x05u)
#define `$INSTANCE_NAME`_DSM_SUMCAPFB_300_FF        (0x06u)
#define `$INSTANCE_NAME`_DSM_SUMCAPFB_350_FF        (0x07u)
#define `$INSTANCE_NAME`_DSM_SUMCAPFB_400_FF        (0x08u)
#define `$INSTANCE_NAME`_DSM_SUMCAPFB_450_FF        (0x09u)
#define `$INSTANCE_NAME`_DSM_SUMCAPFB_500_FF        (0x0Au)
#define `$INSTANCE_NAME`_DSM_SUMCAPFB_550_FF        (0x0Bu)
#define `$INSTANCE_NAME`_DSM_SUMCAPFB_600_FF        (0x0Cu)
#define `$INSTANCE_NAME`_DSM_SUMCAPFB_650_FF        (0x0Du)
#define `$INSTANCE_NAME`_DSM_SUMCAPFB_700_FF        (0x0Eu)
#define `$INSTANCE_NAME`_DSM_SUMCAPFB_750_FF        (0x0Fu)


/********************************************/
/* DSM.CR12 Control Register 12 definitions */
/********************************************/

#define `$INSTANCE_NAME`_DSM_SUMCAPFB_EN            (0x40u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_EN            (0x20u)

#define `$INSTANCE_NAME`_DSM_SUMCAPIN_MASK          (0x1Fu)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_0_FF          (0x00u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_50_FF         (0x01u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_100_FF        (0x02u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_150_FF        (0x03u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_200_FF        (0x04u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_250_FF        (0x05u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_300_FF        (0x06u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_350_FF        (0x07u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_400_FF        (0x08u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_450_FF        (0x09u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_500_FF        (0x0Au)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_550_FF        (0x0Bu)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_600_FF        (0x0Cu)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_650_FF        (0x0Du)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_700_FF        (0x0Eu)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_750_FF        (0x0Fu)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_800_FF        (0x10u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_850_FF        (0x11u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_900_FF        (0x12u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_950_FF        (0x13u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_1000_FF       (0x14u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_1050_FF       (0x15u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_1100_FF       (0x16u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_1150_FF       (0x17u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_1200_FF       (0x18u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_1250_FF       (0x19u)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_1300_FF       (0x1Au)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_1350_FF       (0x1Bu)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_1400_FF       (0x1Cu)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_1450_FF       (0x1Du)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_1500_FF       (0x1Eu)
#define `$INSTANCE_NAME`_DSM_SUMCAPIN_1550_FF       (0x15u)


/********************************************/
/* DSM.CR13 Control Register 13 definitions */
/********************************************/

#define `$INSTANCE_NAME`_DSM_CR13_RSVD              (0xFFu)


/********************************************/
/* DSM.CR14 Control Register 14 definitions */
/********************************************/

/* Bit Field  DSM_POWER1 */
#define `$INSTANCE_NAME`_DSM_POWER1_MASK            (0x07u)

#define `$INSTANCE_NAME`_DSM_POWER1_0               (0x00u)
#define `$INSTANCE_NAME`_DSM_POWER1_1               (0x01u)
#define `$INSTANCE_NAME`_DSM_POWER1_2               (0x02u)
#define `$INSTANCE_NAME`_DSM_POWER1_3               (0x03u)
#define `$INSTANCE_NAME`_DSM_POWER1_4               (0x04u)
#define `$INSTANCE_NAME`_DSM_POWER1_5               (0x05u)
#define `$INSTANCE_NAME`_DSM_POWER1_6               (0x06u)
#define `$INSTANCE_NAME`_DSM_POWER1_7               (0x07u)
  
#define `$INSTANCE_NAME`_DSM_POWER1_44UA            (0x00u)
#define `$INSTANCE_NAME`_DSM_POWER1_123UA           (0x01u)
#define `$INSTANCE_NAME`_DSM_POWER1_492UA           (0x02u)
#define `$INSTANCE_NAME`_DSM_POWER1_750UA           (0x03u)
#define `$INSTANCE_NAME`_DSM_POWER1_1MA             (0x04u)

/* Bit Field  DSM_OPAMP1_BW */
#define `$INSTANCE_NAME`_DSM_OPAMP1_BW_MASK         (0xF0u)
#define `$INSTANCE_NAME`_DSM_OPAMP1_BW_0            (0x00u)
#define `$INSTANCE_NAME`_DSM_OPAMP1_BW_1            (0x10u)
#define `$INSTANCE_NAME`_DSM_OPAMP1_BW_2            (0x20u)
#define `$INSTANCE_NAME`_DSM_OPAMP1_BW_3            (0x30u)
#define `$INSTANCE_NAME`_DSM_OPAMP1_BW_4            (0x40u)
#define `$INSTANCE_NAME`_DSM_OPAMP1_BW_5            (0x50u)
#define `$INSTANCE_NAME`_DSM_OPAMP1_BW_6            (0x60u)
#define `$INSTANCE_NAME`_DSM_OPAMP1_BW_7            (0x70u)
#define `$INSTANCE_NAME`_DSM_OPAMP1_BW_8            (0x80u)
#define `$INSTANCE_NAME`_DSM_OPAMP1_BW_9            (0x90u)
#define `$INSTANCE_NAME`_DSM_OPAMP1_BW_A            (0xA0u)
#define `$INSTANCE_NAME`_DSM_OPAMP1_BW_B            (0xB0u)
#define `$INSTANCE_NAME`_DSM_OPAMP1_BW_C            (0xC0u)
#define `$INSTANCE_NAME`_DSM_OPAMP1_BW_D            (0xD0u)
#define `$INSTANCE_NAME`_DSM_OPAMP1_BW_E            (0xE0u)
#define `$INSTANCE_NAME`_DSM_OPAMP1_BW_F            (0xF0u)


/********************************************/
/* DSM.CR15 Control Register 15 definitions */
/********************************************/

/* Bit Field  DSM_POWER2_3 */
#define `$INSTANCE_NAME`_DSM_POWER2_3_MASK          (0x07u)

#define `$INSTANCE_NAME`_DSM_POWER2_3_LOW           (0x00u)
#define `$INSTANCE_NAME`_DSM_POWER2_3_MED           (0x01u)
#define `$INSTANCE_NAME`_DSM_POWER2_3_HIGH          (0x02u)
#define `$INSTANCE_NAME`_DSM_POWER2_3_IP5X          (0x03u)
#define `$INSTANCE_NAME`_DSM_POWER2_3_2X            (0x04u)
#define `$INSTANCE_NAME`_DSM_POWER2_3_HIGH_5        (0x05u)
#define `$INSTANCE_NAME`_DSM_POWER2_3_HIGH_6        (0x06u)
#define `$INSTANCE_NAME`_DSM_POWER2_3_HIGH_7        (0x07u)

/* Bit Field  DSM_POWER_COMP */
#define `$INSTANCE_NAME`_DSM_POWER_COMP_MASK        (0x30u)

#define `$INSTANCE_NAME`_DSM_POWER_VERYLOW          (0x00u)
#define `$INSTANCE_NAME`_DSM_POWER_NORMAL           (0x10u)
#define `$INSTANCE_NAME`_DSM_POWER_6MHZ             (0x20u)
#define `$INSTANCE_NAME`_DSM_POWER_12MHZ            (0x30u)


/********************************************/
/* DSM.CR16 Control Register 16 definitions */
/********************************************/

/* Bit Field  DSM_POWER_SUM */
#define `$INSTANCE_NAME`_DSM_POWER_SUM_MASK         (0x70u)

#define `$INSTANCE_NAME`_DSM_POWER_SUM_LOW          (0x00u)
#define `$INSTANCE_NAME`_DSM_POWER_SUM_MED          (0x10u)
#define `$INSTANCE_NAME`_DSM_POWER_SUM_HIGH         (0x20u)
#define `$INSTANCE_NAME`_DSM_POWER_SUM_IP5X         (0x30u)
#define `$INSTANCE_NAME`_DSM_POWER_SUM_2X           (0x40u)
#define `$INSTANCE_NAME`_DSM_POWER_SUM_HIGH_5       (0x50u)
#define `$INSTANCE_NAME`_DSM_POWER_SUM_HIGH_6       (0x60u)
#define `$INSTANCE_NAME`_DSM_POWER_SUM_HIGH_7       (0x70u)

#define `$INSTANCE_NAME`_DSM_CP_ENABLE              (0x08u)
#define `$INSTANCE_NAME`_DSM_CP_PWRCTL_MASK         (0x07u)
#define `$INSTANCE_NAME`_DSM_CP_PWRCTL_DEFAULT      (0x0Au)
#define `$INSTANCE_NAME`_DSM_CP_PWRCTL_2X           (0x09u)
#define `$INSTANCE_NAME`_DSM_CP_PWRCTL_LOW          (0x04u)


/********************************************/
/* DSM.CR17 Control Register 17 definitions */
/********************************************/

/* Bit Field  DSM_EN_BUF */
#define `$INSTANCE_NAME`_DSM_EN_BUF_VREF            (0x01u)
#define `$INSTANCE_NAME`_DSM_EN_BUF_VCM             (0x02u)

#define `$INSTANCE_NAME`_DSM_PWR_CTRL_VREF_MASK     (0x0Cu)
#define `$INSTANCE_NAME`_DSM_PWR_CTRL_VREF_0        (0x00u)
#define `$INSTANCE_NAME`_DSM_PWR_CTRL_VREF_1        (0x04u)
#define `$INSTANCE_NAME`_DSM_PWR_CTRL_VREF_2        (0x08u)
#define `$INSTANCE_NAME`_DSM_PWR_CTRL_VREF_3        (0x0Cu)

#define `$INSTANCE_NAME`_DSM_PWR_CTRL_VCM_MASK      (0x30u)
#define `$INSTANCE_NAME`_DSM_PWR_CTRL_VCM_0         (0x00u)
#define `$INSTANCE_NAME`_DSM_PWR_CTRL_VCM_1         (0x10u)
#define `$INSTANCE_NAME`_DSM_PWR_CTRL_VCM_2         (0x20u)
#define `$INSTANCE_NAME`_DSM_PWR_CTRL_VCM_3         (0x30u)

#define `$INSTANCE_NAME`_DSM_PWR_CTRL_VREF_INN_MASK (0xC0u)
#define `$INSTANCE_NAME`_DSM_PWR_CTRL_VREF_INN_0    (0x00u)
#define `$INSTANCE_NAME`_DSM_PWR_CTRL_VREF_INN_1    (0x40u)
#define `$INSTANCE_NAME`_DSM_PWR_CTRL_VREF_INN_2    (0x80u)
#define `$INSTANCE_NAME`_DSM_PWR_CTRL_VREF_INN_3    (0xC0u)


/*********************************************/
/* DSM.REF0 Reference Register 0 definitions */
/*********************************************/

#define `$INSTANCE_NAME`_DSM_REFMUX_MASK            (0x07u)
#define `$INSTANCE_NAME`_DSM_REFMUX_NONE            (0x00u)
#define `$INSTANCE_NAME`_DSM_REFMUX_UVCM            (0x01u)
#define `$INSTANCE_NAME`_DSM_REFMUX_VDA_4           (0x02u)
#define `$INSTANCE_NAME`_DSM_REFMUX_VDAC0           (0x03u)
#define `$INSTANCE_NAME`_DSM_REFMUX_1_024V          (0x04u)
#define `$INSTANCE_NAME`_DSM_REFMUX_1_20V           (0x05u)

#define `$INSTANCE_NAME`_DSM_EN_BUF_VREF_INN        (0x08u)
#define `$INSTANCE_NAME`_DSM_VREF_RES_DIV_EN        (0x10u)
#define `$INSTANCE_NAME`_DSM_VCM_RES_DIV_EN         (0x20u)
#define `$INSTANCE_NAME`_DSM_VCMSEL_MASK            (0xC0u)
#define `$INSTANCE_NAME`_DSM_VCMSEL_NOSEL           (0x00u)
#define `$INSTANCE_NAME`_DSM_VCMSEL_0_8V            (0x40u)
#define `$INSTANCE_NAME`_DSM_VCMSEL_0_7V            (0x80u)
#define `$INSTANCE_NAME`_DSM_VCMSEL_VPWRA_2         (0xC0u)


/*********************************************/
/* DSM.REF1 Reference Register 1 definitions */
/*********************************************/

#define `$INSTANCE_NAME`_DSM_REF1_MASK              (0xFFu)


/*********************************************/
/* DSM.REF2 Reference Register 2 definitions */
/*********************************************/

#define `$INSTANCE_NAME`_DSM_REF2_MASK              (0xFFu)
#define `$INSTANCE_NAME`_DSM_REF2_S0_EN             (0x01u)
#define `$INSTANCE_NAME`_DSM_REF2_S1_EN             (0x02u)
#define `$INSTANCE_NAME`_DSM_REF2_S2_EN             (0x04u)
#define `$INSTANCE_NAME`_DSM_REF2_S3_EN             (0x08u)
#define `$INSTANCE_NAME`_DSM_REF2_S4_EN             (0x10u)
#define `$INSTANCE_NAME`_DSM_REF2_S5_EN             (0x20u)
#define `$INSTANCE_NAME`_DSM_REF2_S6_EN             (0x40u)
#define `$INSTANCE_NAME`_DSM_REF2_S7_EN             (0x80u)


/*********************************************/
/* DSM.REF3 Reference Register 3 definitions */
/*********************************************/

#define `$INSTANCE_NAME`_DSM_REF3_MASK              (0xFFu)
#define `$INSTANCE_NAME`_DSM_REF2_S8_EN             (0x01u)
#define `$INSTANCE_NAME`_DSM_REF2_S9_EN             (0x02u)
#define `$INSTANCE_NAME`_DSM_REF2_S10_EN            (0x04u)
#define `$INSTANCE_NAME`_DSM_REF2_S11_EN            (0x08u)
#define `$INSTANCE_NAME`_DSM_REF2_S12_EN            (0x10u)
#define `$INSTANCE_NAME`_DSM_REF2_S13_EN            (0x20u)


/************************************************/
/* DSM.DEM0 Dynamic Element Matching Register 0 */
/************************************************/

#define `$INSTANCE_NAME`_DSM_EN_SCRAMBLER0          (0x01u)
#define `$INSTANCE_NAME`_DSM_EN_SCRAMBLER1          (0x02u)
#define `$INSTANCE_NAME`_DSM_EN_DEM                 (0x04u)
#define `$INSTANCE_NAME`_DSM_ADC_TEST_EN            (0x08u)
#define `$INSTANCE_NAME`_DSM_DEMTEST_SRC            (0x10u)


/************************************************/
/* DSM.DEM1 Dynamic Element Matching Register 1 */
/************************************************/

#define `$INSTANCE_NAME`_DSM_DEM1_MASK              (0xFF)


/***********************************************/
/* DSM.BUF0 Buffer Register 0                  */
/***********************************************/

#define `$INSTANCE_NAME`_DSM_ENABLE_P               (0x01u)
#define `$INSTANCE_NAME`_DSM_BYPASS_P               (0x02u)
#define `$INSTANCE_NAME`_DSM_RAIL_RAIL_EN           (0x04u)

#define `$INSTANCE_NAME`_DSM_BUFSEL                 (0x08u)
#define `$INSTANCE_NAME`_DSM_BUFSEL_A               (0x00u)
#define `$INSTANCE_NAME`_DSM_BUFSEL_B               (0x08u)


/***********************************************/
/* DSM.BUF1 Buffer Register 1                  */
/***********************************************/

#define `$INSTANCE_NAME`_DSM_ENABLE_N               (0x01u)
#define `$INSTANCE_NAME`_DSM_BYPASS_N               (0x02u)
#define `$INSTANCE_NAME`_DSM_GAIN_MASK              (0x0Cu)


/***********************************************/
/* DSM.BUF2 Buffer Register 2                  */
/***********************************************/

#define `$INSTANCE_NAME`_DSM_LOWPOWER_EN            (0x01u)
#define `$INSTANCE_NAME`_DSM_ADD_EXTRA_RC           (0x02u)


/***********************************************/
/* DSM.BUF3 Buffer Register 3                  */
/***********************************************/

#define `$INSTANCE_NAME`_DSM_BUF_CHOP_EN            (0x08u)

#define `$INSTANCE_NAME`_DSM_BUF_FCHOP_MASK         (0x07u)
#define `$INSTANCE_NAME`_DSM_BUF_FCHOP_FS2          (0x00u)
#define `$INSTANCE_NAME`_DSM_BUF_FCHOP_FS4          (0x01u)
#define `$INSTANCE_NAME`_DSM_BUF_FCHOP_FS8          (0x02u)
#define `$INSTANCE_NAME`_DSM_BUF_FCHOP_FS16         (0x03u)
#define `$INSTANCE_NAME`_DSM_BUF_FCHOP_FS32         (0x04u)
#define `$INSTANCE_NAME`_DSM_BUF_FCHOP_FS64         (0x05u)
#define `$INSTANCE_NAME`_DSM_BUF_FCHOP_FS128        (0x06u)
#define `$INSTANCE_NAME`_DSM_BUF_FCHOP_FS256        (0x07u)


/***********************************************/
/* DSM.MISC Delta Sigma Misc Register          */
/***********************************************/

#define `$INSTANCE_NAME`_DSM_SEL_ICLK_CP            (0x01u)


/************************************************/
/* DSM.CLK Delta Sigma Clock selection Register */
/************************************************/

#define `$INSTANCE_NAME`_DSM_CLK_MX_CLK_MSK         (0x07u)
#define `$INSTANCE_NAME`_DSM_CLK_CLK_EN             (0x08u)
#define `$INSTANCE_NAME`_DSM_CLK_BYPASS_SYNC        (0x10u)


/***********************************************/
/* DSM.OUT0 Output Register 0                  */
/***********************************************/
#define `$INSTANCE_NAME`_DSM_DOUT0                  (0xFFu)


/***********************************************/
/* DSM.OUT1 Output Register 1                  */
/***********************************************/
#define `$INSTANCE_NAME`_DSM_DOUT2SCOMP_MASK        (0x0Fu)
#define `$INSTANCE_NAME`_DSM_OVDFLAG                (0x10u)
#define `$INSTANCE_NAME`_DSM_OVDCAUSE               (0x20u)


/***********************************************/
/*          Decimator                          */
/***********************************************/


/***********************************************/
/* DEC.CR Control Register 0                   */
/***********************************************/

#define `$INSTANCE_NAME`_DEC_SAT_EN                 (0x80u) /* Enable post process offset correction */
#define `$INSTANCE_NAME`_DEC_FIR_EN                 (0x40u) /* Post process FIR enable  */
#define `$INSTANCE_NAME`_DEC_OCOR_EN                (0x20u) /* Offest correction enable */
#define `$INSTANCE_NAME`_DEC_GCOR_EN                (0x10u) /* Enable gain correction feature */

#define `$INSTANCE_NAME`_MODE_MASK                  (0x0Cu) /* Conversion Mode */
#define `$INSTANCE_NAME`_MODE_SINGLE_SAMPLE         (0x00u)
#define `$INSTANCE_NAME`_MODE_FAST_FILTER           (0x04u)
#define `$INSTANCE_NAME`_MODE_CONTINUOUS            (0x08u)
#define `$INSTANCE_NAME`_MODE_FAST_FIR              (0x0Cu)

#define `$INSTANCE_NAME`_DEC_XSTART_EN              (0x02u) /* Enables external start signal */
#define `$INSTANCE_NAME`_DEC_START_CONV             (0x01u) /* A write to this bit starts a conversion */


/***********************************************/
/* DEC.SR Status and Control Register 0        */
/***********************************************/

#define `$INSTANCE_NAME`_DEC_CORECLK_DISABLE        (0x20u) /* Controls gating of the Core clock */
#define `$INSTANCE_NAME`_DEC_INTR_PULSE             (0x10u) /* Controls interrupt mode */ 
#define `$INSTANCE_NAME`_DEC_OUT_ALIGN              (0x08u) /* Controls 8-bit shift of SAMP registers */
#define `$INSTANCE_NAME`_DEC_INTR_CLEAR             (0x04u) /* A write to this bit clears bit0 */
#define `$INSTANCE_NAME`_DEC_INTR_MASK              (0x02u) /* Controls the generation of the conversion comp. INTR */
#define `$INSTANCE_NAME`_DEC_CONV_DONE              (0x01u) /* Bit set if conversion has completed  */


/***********************************************/
/* DEC.SHIFT1 Decimator Input Shift Register 1 */
/***********************************************/

#define `$INSTANCE_NAME`_DEC_SHIFT1_MASK            (0x1Fu) /* Input shift1 control */


/***********************************************/
/* DEC.SHIFT2 Decimator Input Shift Register 2 */
/***********************************************/

#define `$INSTANCE_NAME`_DEC_SHIFT2_MASK            (0x0Fu) /* Input shift2 control */


/****************************************************************/
/* DEC.DR2 Decimator Decimation Rate of FIR Filter Low Register */
/****************************************************************/

#define `$INSTANCE_NAME`_DEC_DR2_MASK               (0xFFu)


/******************************************************************/
/* DEC.DR2H Decimator Decimation Rate of FIR Filter High Register */
/******************************************************************/

#define `$INSTANCE_NAME`_DEC_DR2H_MASK              (0x03u)


/***********************************************/
/* DEC.COHR Decimator Coherency Register       */
/***********************************************/

#define `$INSTANCE_NAME`_DEC_GCOR_KEY_MASK          (0x30u) 
#define `$INSTANCE_NAME`_DEC_GCOR_KEY_OFF           (0x00u) 
#define `$INSTANCE_NAME`_DEC_GCOR_KEY_LOW           (0x10u) 
#define `$INSTANCE_NAME`_DEC_GCOR_KEY_MID           (0x20u) 
#define `$INSTANCE_NAME`_DEC_GCOR_KEY_HIGH          (0x30u) 

#define `$INSTANCE_NAME`_DEC_OCOR_KEY_MASK          (0x0Cu)
#define `$INSTANCE_NAME`_DEC_OCOR_KEY_OFF           (0x00u) 
#define `$INSTANCE_NAME`_DEC_OCOR_KEY_LOW           (0x04u) 
#define `$INSTANCE_NAME`_DEC_OCOR_KEY_MID           (0x08u) 
#define `$INSTANCE_NAME`_DEC_OCOR_KEY_HIGH          (0x0Cu) 

#define `$INSTANCE_NAME`_DEC_SAMP_KEY_MASK          (0x03u) 
#define `$INSTANCE_NAME`_DEC_SAMP_KEY_OFF           (0x00u) 
#define `$INSTANCE_NAME`_DEC_SAMP_KEY_LOW           (0x01u) 
#define `$INSTANCE_NAME`_DEC_SAMP_KEY_MID           (0x02u) 
#define `$INSTANCE_NAME`_DEC_SAMP_KEY_HIGH          (0x03u)

/* PM_ACT_CFG (Active Power Mode CFG Register) mask */ 
#define `$INSTANCE_NAME`_ACT_PWR_DEC_EN             `$INSTANCE_NAME`_DEC__PM_ACT_MSK /* Power enable mask */
#define `$INSTANCE_NAME`_STBY_PWR_DEC_EN            `$INSTANCE_NAME`_DEC__PM_STBY_MSK /* Power enable mask */

/* Active and Alternative active power masks for DSM */

#if (CY_PSOC3 || CY_PSOC5LP)
    #define `$INSTANCE_NAME`_ACT_PWR_DSM_EN         (0x10u) /* Active Power enable mask */
    #define `$INSTANCE_NAME`_STBY_PWR_DSM_EN        (0x10u) /* Alternate active Power enable mask */
#elif (CY_PSOC5A)
    #define `$INSTANCE_NAME`_ACT_PWR_DSM_EN         (0x01u) /* Power enable mask */
#endif /* CY_PSOC5A */


/* Internal and charge pump clock power enable masks */
#if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
    #define `$INSTANCE_NAME`_ACT_PWR_CLK_EN              `$INSTANCE_NAME`_theACLK__PM_ACT_MSK 
    #define `$INSTANCE_NAME`_STBY_PWR_CLK_EN             `$INSTANCE_NAME`_theACLK__PM_STBY_MSK 
#endif /* `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */

#define `$INSTANCE_NAME`_ACT_PWR_CHARGE_PUMP_CLK_EN  `$INSTANCE_NAME`_Ext_CP_Clk__PM_ACT_MSK 
#define `$INSTANCE_NAME`_STBY_PWR_CHARGE_PUMP_CLK_EN `$INSTANCE_NAME`_Ext_CP_Clk__PM_STBY_MSK 


/***********************************************/
/* DSM.SW3 DSM Analog Routing Register 3       */
/***********************************************/
#define `$INSTANCE_NAME`_DSM_VP_VSSA                (0x04u) 

/* To connect negative input to analog mux Bus. This is valid only
   for PSoC5A */
#if(CY_PSOC5A)
    #define `$INSTANCE_NAME`_DSM_VN_AMX             (0x10u) 
#endif /* CY_PSOC5A */

/* To connect positive input to analog mux Bus. This is valid only
   for PSoC3 or PSoC5LP silicon */
#if(CY_PSOC3 || CY_PSOC5LP)
    #define `$INSTANCE_NAME`_DSM_VP_AMX             (0x01u) 
#endif /* CY_PSOC3 || CY_PSOC5LP */

#define `$INSTANCE_NAME`_DSM_VN_VREF                (0x20u) 
#define `$INSTANCE_NAME`_DSM_VN_VSSA                (0x40u) 
#define `$INSTANCE_NAME`_DSM_VN_REF_MASK            (0x60u) 


/***********************************************/
/* ANIF.PUMP.CR1 Pump Configuration Register 1 */
/***********************************************/

#define `$INSTANCE_NAME`_PUMP_CR1_CLKSEL            (0x04u)
#define `$INSTANCE_NAME`_PUMP_CR1_FORCE             (0x02u)
#define `$INSTANCE_NAME`_PUMP_CR1_AUTO              (0x01u)

/***********************************************/
/* RESET_CR4 Reset Ignore Control Register     */
/***********************************************/ 

#define `$INSTANCE_NAME`_IGNORE_PRESD1              (0x01u) 
#define `$INSTANCE_NAME`_IGNORE_PRESA1              (0x02u)
#define `$INSTANCE_NAME`_IGNORE_LPCOMPD1            (0x04u)
#define `$INSTANCE_NAME`_IGNORE_LPCOMPA1            (0x08u)
#define `$INSTANCE_NAME`_IGNORE_HBR1                (0x10u)


/***********************************************/
/* RESET_CR5 Reset Ignore Control Register     */
/***********************************************/ 

#define `$INSTANCE_NAME`_IGNORE_PRESD2              (0x01u) 
#define `$INSTANCE_NAME`_IGNORE_PRESA2              (0x02u)
#define `$INSTANCE_NAME`_IGNORE_LPCOMPD2            (0x04u)
#define `$INSTANCE_NAME`_IGNORE_LPCOMPA2            (0x08u)
#define `$INSTANCE_NAME`_IGNORE_HBR2                (0x10u)


/***********************************************/
/* RESET_CR1 Reset Ignore Control Register     */
/***********************************************/ 

#define `$INSTANCE_NAME`_DIS_HBR1                   (0x20u) 
#define `$INSTANCE_NAME`_DIS_PRES1                  (0x10u)
#define `$INSTANCE_NAME`_VMON_HVI_SEL               (0x08u)
#define `$INSTANCE_NAME`_EN_HVI_A                   (0x04u)
#define `$INSTANCE_NAME`_EN_LVI_A                   (0x02u)
#define `$INSTANCE_NAME`_EN_LVI_D                   (0x01u)


/***********************************************/
/* RESET_CR3 Reset Ignore Control Register     */
/***********************************************/ 

#define `$INSTANCE_NAME`_DIS_PRES2                  (0x08u) 
#define `$INSTANCE_NAME`_DIS_HBR2                   (0x10u)


/***************************************
*              Registers        
***************************************/

/* Decimator (DEC) Registers */
#define `$INSTANCE_NAME`_DEC_CR_REG               (* (reg8 *) `$INSTANCE_NAME`_DEC__CR )
#define `$INSTANCE_NAME`_DEC_CR_PTR               (  (reg8 *) `$INSTANCE_NAME`_DEC__CR )

#define `$INSTANCE_NAME`_DEC_SR_REG               (* (reg8 *) `$INSTANCE_NAME`_DEC__SR )
#define `$INSTANCE_NAME`_DEC_SR_PTR               (  (reg8 *) `$INSTANCE_NAME`_DEC__SR )

#define `$INSTANCE_NAME`_DEC_SHIFT1_REG           (* (reg8 *) `$INSTANCE_NAME`_DEC__SHIFT1 )
#define `$INSTANCE_NAME`_DEC_SHIFT1_PTR           (  (reg8 *) `$INSTANCE_NAME`_DEC__SHIFT1 )

#define `$INSTANCE_NAME`_DEC_SHIFT2_REG           (* (reg8 *) `$INSTANCE_NAME`_DEC__SHIFT2 )
#define `$INSTANCE_NAME`_DEC_SHIFT2_PTR           ( (reg8 *) `$INSTANCE_NAME`_DEC__SHIFT2 )

#define `$INSTANCE_NAME`_DEC_DR2_REG              (* (reg8 *) `$INSTANCE_NAME`_DEC__DR2 )
#define `$INSTANCE_NAME`_DEC_DR2_PTR              (  (reg8 *) `$INSTANCE_NAME`_DEC__DR2 )

#define `$INSTANCE_NAME`_DEC_DR2H_REG             (* (reg8 *) `$INSTANCE_NAME`_DEC__DR2H )
#define `$INSTANCE_NAME`_DEC_DR2H_PTR             (  (reg8 *) `$INSTANCE_NAME`_DEC__DR2H )

#define `$INSTANCE_NAME`_DEC_DR1_REG              (* (reg8 *) `$INSTANCE_NAME`_DEC__DR1 )
#define `$INSTANCE_NAME`_DEC_DR1_PTR              (  (reg8 *) `$INSTANCE_NAME`_DEC__DR1 )

#define `$INSTANCE_NAME`_DEC_OCOR_REG             (* (reg8 *) `$INSTANCE_NAME`_DEC__OCOR )
#define `$INSTANCE_NAME`_DEC_OCOR_PTR             (  (reg8 *) `$INSTANCE_NAME`_DEC__OCOR )

#define `$INSTANCE_NAME`_DEC_OCORM_REG            (* (reg8 *) `$INSTANCE_NAME`_DEC__OCORM )
#define `$INSTANCE_NAME`_DEC_OCORM_PTR            (  (reg8 *) `$INSTANCE_NAME`_DEC__OCORM )

#define `$INSTANCE_NAME`_DEC_OCORH_REG            (* (reg8 *) `$INSTANCE_NAME`_DEC__OCORH )
#define `$INSTANCE_NAME`_DEC_OCORH_PTR            (  (reg8 *) `$INSTANCE_NAME`_DEC__OCORH )

#define `$INSTANCE_NAME`_DEC_GVAL_REG             (* (reg8 *) `$INSTANCE_NAME`_DEC__GVAL )
#define `$INSTANCE_NAME`_DEC_GVAL_PTR             (  (reg8 *) `$INSTANCE_NAME`_DEC__GVAL )

#define `$INSTANCE_NAME`_DEC_GCOR_REG             (* (reg8 *) `$INSTANCE_NAME`_DEC__GCOR )
#define `$INSTANCE_NAME`_DEC_GCOR_PTR             (  (reg8 *) `$INSTANCE_NAME`_DEC__GCOR )

#define `$INSTANCE_NAME`_DEC_GCORH_REG            (* (reg8 *) `$INSTANCE_NAME`_DEC__GCORH )
#define `$INSTANCE_NAME`_DEC_GCORH_PTR            (  (reg8 *) `$INSTANCE_NAME`_DEC__GCORH )

#define `$INSTANCE_NAME`_DEC_SAMP_REG             (* (reg8 *) `$INSTANCE_NAME`_DEC__OUTSAMP )
#define `$INSTANCE_NAME`_DEC_SAMP_PTR             (  (reg8 *) `$INSTANCE_NAME`_DEC__OUTSAMP )

#define `$INSTANCE_NAME`_DEC_SAMPM_REG            (* (reg8 *) `$INSTANCE_NAME`_DEC__OUTSAMPM )
#define `$INSTANCE_NAME`_DEC_SAMPM_PTR            (  (reg8 *) `$INSTANCE_NAME`_DEC__OUTSAMPM )

#define `$INSTANCE_NAME`_DEC_SAMPH_REG            (* (reg8 *) `$INSTANCE_NAME`_DEC__OUTSAMPH )
#define `$INSTANCE_NAME`_DEC_SAMPH_PTR            (  (reg8 *) `$INSTANCE_NAME`_DEC__OUTSAMPH )

#define `$INSTANCE_NAME`_DEC_COHER_REG            (* (reg8 *) `$INSTANCE_NAME`_DEC__COHER )
#define `$INSTANCE_NAME`_DEC_COHER_PTR            (  (reg8 *) `$INSTANCE_NAME`_DEC__COHER )

#define `$INSTANCE_NAME`_PWRMGR_DEC_REG           (* (reg8 *) `$INSTANCE_NAME`_DEC__PM_ACT_CFG )    
#define `$INSTANCE_NAME`_PWRMGR_DEC_PTR           (  (reg8 *) `$INSTANCE_NAME`_DEC__PM_ACT_CFG )

#define `$INSTANCE_NAME`_STBY_PWRMGR_DEC_REG      (* (reg8 *) `$INSTANCE_NAME`_DEC__PM_STBY_CFG )     
#define `$INSTANCE_NAME`_STBY_PWRMGR_DEC_PTR      (  (reg8 *) `$INSTANCE_NAME`_DEC__PM_STBY_CFG )

/* Delta Sigma Modulator (DSM) Registers */  
#define `$INSTANCE_NAME`_DSM_CR0_REG              (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR0 )
#define `$INSTANCE_NAME`_DSM_CR0_PTR              (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR0 )

#define `$INSTANCE_NAME`_DSM_CR1_REG              (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR1 )
#define `$INSTANCE_NAME`_DSM_CR1_PTR              (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR1 )

#define `$INSTANCE_NAME`_DSM_CR2_REG              (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR2 )
#define `$INSTANCE_NAME`_DSM_CR2_PTR              (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR2 )

#define `$INSTANCE_NAME`_DSM_CR3_REG              (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR3 )
#define `$INSTANCE_NAME`_DSM_CR3_PTR              (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR3 )

#define `$INSTANCE_NAME`_DSM_CR4_REG              (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR4 )
#define `$INSTANCE_NAME`_DSM_CR4_PTR              (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR4 )

#define `$INSTANCE_NAME`_DSM_CR5_REG              (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR5 )
#define `$INSTANCE_NAME`_DSM_CR5_PTR              (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR5 )

#define `$INSTANCE_NAME`_DSM_CR6_REG              (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR6 )
#define `$INSTANCE_NAME`_DSM_CR6_PTR              (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR6 )

#define `$INSTANCE_NAME`_DSM_CR7_REG              (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR7 )
#define `$INSTANCE_NAME`_DSM_CR7_PTR              (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR7 )

#define `$INSTANCE_NAME`_DSM_CR8_REG              (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR8 )
#define `$INSTANCE_NAME`_DSM_CR8_PTR              (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR8 )

#define `$INSTANCE_NAME`_DSM_CR9_REG              (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR9 )
#define `$INSTANCE_NAME`_DSM_CR9_PTR              (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR9 )

#define `$INSTANCE_NAME`_DSM_CR10_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR10 )
#define `$INSTANCE_NAME`_DSM_CR10_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR10 )

#define `$INSTANCE_NAME`_DSM_CR11_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR11 )
#define `$INSTANCE_NAME`_DSM_CR11_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR11 )

#define `$INSTANCE_NAME`_DSM_CR12_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR12 )
#define `$INSTANCE_NAME`_DSM_CR12_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR12 )

#define `$INSTANCE_NAME`_DSM_CR13_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR13 )
#define `$INSTANCE_NAME`_DSM_CR13_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR13 )

#define `$INSTANCE_NAME`_DSM_CR14_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR14 )
#define `$INSTANCE_NAME`_DSM_CR14_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR14 )

#define `$INSTANCE_NAME`_DSM_CR15_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR15 )
#define `$INSTANCE_NAME`_DSM_CR15_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR15 )

#define `$INSTANCE_NAME`_DSM_CR16_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR16 )
#define `$INSTANCE_NAME`_DSM_CR16_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR16 )

#define `$INSTANCE_NAME`_DSM_CR17_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR17 )
#define `$INSTANCE_NAME`_DSM_CR17_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CR17 )

#define `$INSTANCE_NAME`_DSM_REF0_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__REF0 )
#define `$INSTANCE_NAME`_DSM_REF0_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__REF0 )

#define `$INSTANCE_NAME`_DSM_REF1_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__REF1 )
#define `$INSTANCE_NAME`_DSM_REF1_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__REF1 )

#define `$INSTANCE_NAME`_DSM_REF2_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__REF2 )
#define `$INSTANCE_NAME`_DSM_REF2_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__REF2 )

#define `$INSTANCE_NAME`_DSM_REF3_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__REF3 )
#define `$INSTANCE_NAME`_DSM_REF3_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__REF3 )

#define `$INSTANCE_NAME`_DSM_DEM0_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__DEM0 )
#define `$INSTANCE_NAME`_DSM_DEM0_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__DEM0 )

#define `$INSTANCE_NAME`_DSM_DEM1_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__DEM1 )
#define `$INSTANCE_NAME`_DSM_DEM1_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__DEM1 )

#define `$INSTANCE_NAME`_DSM_MISC_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__MISC )
#define `$INSTANCE_NAME`_DSM_MISC_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__MISC )

#define `$INSTANCE_NAME`_DSM_CLK_REG              (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CLK )
#define `$INSTANCE_NAME`_DSM_CLK_PTR              (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__CLK )

#define `$INSTANCE_NAME`_DSM_TST0_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__TST0 )
#define `$INSTANCE_NAME`_DSM_TST0_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__TST0 )

#define `$INSTANCE_NAME`_DSM_TST1_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__TST1 )
#define `$INSTANCE_NAME`_DSM_TST1_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__TST1 )

#define `$INSTANCE_NAME`_DSM_BUF0_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__BUF0 )
#define `$INSTANCE_NAME`_DSM_BUF0_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__BUF0 )

#define `$INSTANCE_NAME`_DSM_BUF1_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__BUF1 )
#define `$INSTANCE_NAME`_DSM_BUF1_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__BUF1 )

#define `$INSTANCE_NAME`_DSM_BUF2_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__BUF2 )
#define `$INSTANCE_NAME`_DSM_BUF2_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__BUF2 )

#define `$INSTANCE_NAME`_DSM_BUF3_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__BUF3 )
#define `$INSTANCE_NAME`_DSM_BUF3_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__BUF3 )

#define `$INSTANCE_NAME`_DSM_OUT0_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__OUT0 )
#define `$INSTANCE_NAME`_DSM_OUT0_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__OUT0 )

#define `$INSTANCE_NAME`_DSM_OUT1_REG             (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__OUT1 )
#define `$INSTANCE_NAME`_DSM_OUT1_PTR             (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__OUT1 )

#define `$INSTANCE_NAME`_DSM_SW0_REG              (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__SW0 )
#define `$INSTANCE_NAME`_DSM_SW0_PTR              (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__SW0 )

#define `$INSTANCE_NAME`_DSM_SW2_REG              (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__SW2 )
#define `$INSTANCE_NAME`_DSM_SW2_PTR              (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__SW2 )

#define `$INSTANCE_NAME`_DSM_SW3_REG              (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__SW3 )
#define `$INSTANCE_NAME`_DSM_SW3_PTR              (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__SW3 )

#define `$INSTANCE_NAME`_DSM_SW4_REG              (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__SW4 )
#define `$INSTANCE_NAME`_DSM_SW4_PTR              (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__SW4 )

#define `$INSTANCE_NAME`_DSM_SW6_REG              (* (reg8 *) `$INSTANCE_NAME`_`$DsmName`__SW6 )
#define `$INSTANCE_NAME`_DSM_SW6_PTR              (  (reg8 *) `$INSTANCE_NAME`_`$DsmName`__SW6 )

/* Charge pump configuration register */
#define `$INSTANCE_NAME`_PUMP_CR1_REG             (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)
#define `$INSTANCE_NAME`_PUMP_CR1_PTR             (  (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)

/* DSM Active Power manager register */

#if(CY_PSOC3 || CY_PSOC5LP)
    #define `$INSTANCE_NAME`_PWRMGR_DSM_REG       (* (reg8 *) CYDEV_PM_ACT_CFG10 )  /* Modulator Power manager */
    #define `$INSTANCE_NAME`_PWRMGR_DSM_PTR       (  (reg8 *) CYDEV_PM_ACT_CFG10 )  /* Modulator Power manager */
#elif (CY_PSOC5A)
    #define `$INSTANCE_NAME`_PWRMGR_DSM_REG       (* (reg8 *) CYDEV_PM_AVAIL_CR5 )  /* Modulator Power manager */
    #define `$INSTANCE_NAME`_PWRMGR_DSM_PTR       (  (reg8 *) CYDEV_PM_AVAIL_CR5 )  /* Modulator Power manager */
#endif /* CY_PSOC5A */

/* DSM Alternative Active Power manager register */

#if(CY_PSOC3 || CY_PSOC5LP)
    #define `$INSTANCE_NAME`_STBY_PWRMGR_DSM_REG  (* (reg8 *) CYDEV_PM_STBY_CFG10 )  
    #define `$INSTANCE_NAME`_STBY_PWRMGR_DSM_PTR  (  (reg8 *) CYDEV_PM_STBY_CFG10 )  
#endif /* CY_PSOC3 || CY_PSOC5LP */

/* This is only valid if there is an internal clock */
#if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
    #define `$INSTANCE_NAME`_PWRMGR_CLK_REG       (* (reg8 *) `$INSTANCE_NAME`_theACLK__PM_ACT_CFG ) 
    #define `$INSTANCE_NAME`_PWRMGR_CLK_PTR       (  (reg8 *) `$INSTANCE_NAME`_theACLK__PM_ACT_CFG ) 

    #define `$INSTANCE_NAME`_STBY_PWRMGR_CLK_REG  (* (reg8 *) `$INSTANCE_NAME`_theACLK__PM_STBY_CFG )
    #define `$INSTANCE_NAME`_STBY_PWRMGR_CLK_PTR  (  (reg8 *) `$INSTANCE_NAME`_theACLK__PM_STBY_CFG )
#endif /* `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */

/* This is only valid if there is an external charge clock */

/* Clock power manager register */
#define `$INSTANCE_NAME`_PWRMGR_CHARGE_PUMP_CLK_REG       (* (reg8 *) `$INSTANCE_NAME`_Ext_CP_Clk__PM_ACT_CFG )
#define `$INSTANCE_NAME`_PWRMGR_CHARGE_PUMP_CLK_PTR       (  (reg8 *) `$INSTANCE_NAME`_Ext_CP_Clk__PM_ACT_CFG )

#define `$INSTANCE_NAME`_STBY_PWRMGR_CHARGE_PUMP_CLK_REG  (* (reg8 *) `$INSTANCE_NAME`_Ext_CP_Clk__PM_STBY_CFG ) 
#define `$INSTANCE_NAME`_STBY_PWRMGR_CHARGE_PUMP_CLK_PTR  (  (reg8 *) `$INSTANCE_NAME`_Ext_CP_Clk__PM_STBY_CFG ) 

/* PRES-A related registers */
#if (CY_PSOC3 || CY_PSOC5LP)

    #define `$INSTANCE_NAME`_RESET_CR4_REG                    (* (reg8 *) CYDEV_RESET_CR4)
    #define `$INSTANCE_NAME`_RESET_CR4_PTR                    (  (reg8 *) CYDEV_RESET_CR4)

    #define `$INSTANCE_NAME`_RESET_CR5_REG                    (* (reg8 *) CYDEV_RESET_CR5)
    #define `$INSTANCE_NAME`_RESET_CR5_PTR                    (  (reg8 *) CYDEV_RESET_CR5)
    
#elif (CY_PSOC5A)
    #define `$INSTANCE_NAME`_RESET_CR1_REG                    (* (reg8 *) CYDEV_RESET_CR1)
    #define `$INSTANCE_NAME`_RESET_CR1_PTR                    (  (reg8 *) CYDEV_RESET_CR1)

    #define `$INSTANCE_NAME`_RESET_CR3_REG                    (* (reg8 *) CYDEV_RESET_CR3)
    #define `$INSTANCE_NAME`_RESET_CR3_PTR                    (  (reg8 *) CYDEV_RESET_CR3)
    
#endif /* CY_PSOC5A */
    

/* Default register settings for the Config 1 */
/* `$Comment_Config1` */
/* `$INSTANCE_NAME`_`$Config1_Name` Sample Rate: `$Sample_Rate` Samples per Second */
/* `$INSTANCE_NAME`_`$Config1_Name` Conversion Mode: `$Conversion_Mode` */
/* `$INSTANCE_NAME`_`$Config1_Name` Input Buffer Gain: `$Input_Buffer_Gain`   */
/* `$INSTANCE_NAME`_`$Config1_Name` Reference: `$ADC_Reference` */
/* `$INSTANCE_NAME`_`$Config1_Name` Input Range: `$ADC_Input_Range`  */
/* `$INSTANCE_NAME`_`$Config1_Name` Resolution: `$ADC_Resolution` bits */
/* `$INSTANCE_NAME`_`$Config1_Name` Clock: `$DFLT_CLK_FREQ` Hz */

#define `$INSTANCE_NAME`_`$Config1_Name`_DEC_CR             (`$DFLT_DEC_CR`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DEC_SR             (`$DFLT_DEC_SR`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DEC_SHIFT1         (`$DFLT_DEC_SHIFT1`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DEC_SHIFT2         (`$DFLT_DEC_SHIFT2`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DEC_DR2            (`$DFLT_DEC_DR2`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DEC_DR2H           (`$DFLT_DEC_DR2H`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DEC_DR1            (`$DFLT_DEC_DR1`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DEC_OCOR           (`$DFLT_DEC_OCOR`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DEC_OCORM          (`$DFLT_DEC_OCORM`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DEC_OCORH          (`$DFLT_DEC_OCORH`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DEC_GVAL           (`$DFLT_DEC_GVAL`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DEC_GCOR           (`$DFLT_DEC_GCOR`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DEC_GCORH          (`$DFLT_DEC_GCORH`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DEC_COHER          (`$DFLT_DEC_COHER`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR0            (`$DFLT_DSM_CR0`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR1            (`$DFLT_DSM_CR1`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR2            (`$DFLT_DSM_CR2`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR3            (`$DFLT_DSM_CR3`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR4            (`$DFLT_DSM_CR4`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR5            (`$DFLT_DSM_CR5`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR6            (`$DFLT_DSM_CR6`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR7            (`$DFLT_DSM_CR7`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR8            (`$DFLT_DSM_CR8`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR9            (`$DFLT_DSM_CR9`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR10           (`$DFLT_DSM_CR10`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR11           (`$DFLT_DSM_CR11`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR12           (`$DFLT_DSM_CR12`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR13           (`$DFLT_DSM_CR13`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR14           (`$DFLT_DSM_CR14`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR15           (`$DFLT_DSM_CR15`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR16           (`$DFLT_DSM_CR16`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR17           (`$DFLT_DSM_CR17`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_REF0           (`$DFLT_DSM_REF0`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_REF1           (`$DFLT_DSM_REF1`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_REF2           (`$DFLT_DSM_REF2`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_REF3           (`$DFLT_DSM_REF3`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_DEM0           (`$DFLT_DSM_DEM0`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_DEM1           (`$DFLT_DSM_DEM1`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_MISC           (`$DFLT_DSM_MISC`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_CLK            (`$DFLT_DSM_CLK`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_BUF0           (`$DFLT_DSM_BUF0`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_BUF1           (`$DFLT_DSM_BUF1`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_BUF2           (`$DFLT_DSM_BUF2`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_BUF3           (`$DFLT_DSM_BUF3`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_OUT0           (`$DFLT_DSM_OUT0`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_OUT1           (`$DFLT_DSM_OUT1`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DSM_SW3            (`$DFLT_DSM_SW3`)
#define `$INSTANCE_NAME`_`$Config1_Name`_CLOCKS_PER_SAMPLE  (`$DFLT_CLOCKS_PER_SAMPLE`)
#define `$INSTANCE_NAME`_`$Config1_Name`_CLOCK_FREQ         (`$DFLT_CLK_FREQ`u)
#define `$INSTANCE_NAME`_`$Config1_Name`_CP_CLOCK_FREQ      (`$DFLT_CP_CLK_FREQ`u)
#define `$INSTANCE_NAME`_`$Config1_Name`_REFERENCE_VOLTAGE  (`$DFLT_REF_VOLTAGE`)
#define `$INSTANCE_NAME`_`$Config1_Name`_COUNTS_PER_VOLT    (`$DFLT_COUNTS_PER_VOLT`u)
#define `$INSTANCE_NAME`_`$Config1_Name`_IDEAL_DEC_GAIN     (`$DFLT_IDEAL_DEC_GAIN`)

#define `$INSTANCE_NAME`_`$Config1_Name`_IDEAL_ODDDEC_GAIN  (`$DFLT_IDEAL_ODDDEC_GAIN`)

/* Input and DAC Cap values in pF */
#define `$INSTANCE_NAME`_`$Config1_Name`_IPCAP1VALUE        (`$DFLT_IPCap1Value`)
#define `$INSTANCE_NAME`_`$Config1_Name`_DACAPVALUE         (`$DFLT_DACCapValue`)

/* Below defines are depricated and should not be used. These are provided 
   just to keep the component backward compatible */
#define `$INSTANCE_NAME`_DEFAULT_SRATE                      `$INSTANCE_NAME`_`$Config1_Name`_SRATE              
#define `$INSTANCE_NAME`_CLOCKS_PER_SAMPLE                  `$INSTANCE_NAME`_`$Config1_Name`_CLOCKS_PER_SAMPLE  
#define `$INSTANCE_NAME`_DFLT_CLOCK_FREQ                    `$INSTANCE_NAME`_`$Config1_Name`_CLOCK_FREQ         
#define `$INSTANCE_NAME`_REFERENCE_VOLTAGE                  `$INSTANCE_NAME`_`$Config1_Name`_REFERENCE_VOLTAGE  
#define `$INSTANCE_NAME`_DFLT_COUNTS_PER_VOLT               `$INSTANCE_NAME`_`$Config1_Name`_COUNTS_PER_VOLT    
#define `$INSTANCE_NAME`_DEFAULT_RESOLUTION                 `$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION         
#define `$INSTANCE_NAME`_DEFAULT_CONV_MODE                  `$INSTANCE_NAME`_`$Config1_Name`_CONV_MODE           
#define `$INSTANCE_NAME`_DEFAULT_IDEAL_DEC_GAIN             `$INSTANCE_NAME`_`$Config1_Name`_IDEAL_DEC_GAIN     
#define `$INSTANCE_NAME`_DEFAULT_RANGE                      `$INSTANCE_NAME`_`$Config1_Name`_RANGE        
#define `$INSTANCE_NAME`_DEFAULT_RANGE_VALUE                `$INSTANCE_NAME`_`$Config1_Name`_RANGE_VALUE  
#define `$INSTANCE_NAME`_DEFAULT_REFERENCE                  `$INSTANCE_NAME`_`$Config1_Name`_REFERENCE         
#define `$INSTANCE_NAME`_DEFAULT_BUF_GAIN                   `$INSTANCE_NAME`_`$Config1_Name`_BUF_GAIN       

/* Input and DAC Cap values in pF */
#define `$INSTANCE_NAME`_DEFAULT_IPCAP1VALUE                `$INSTANCE_NAME`_`$Config1_Name`_IPCAP1VALUE       
#define `$INSTANCE_NAME`_DEFAULT_DACAPVALUE                 `$INSTANCE_NAME`_`$Config1_Name`_DACAPVALUE        
#define `$INSTANCE_NAME`_DEFAULT_IDEAL_ODDDEC_GAIN          `$INSTANCE_NAME`_`$Config1_Name`_IDEAL_ODDDEC_GAIN 


/* Default register settings for the Config 2 */
/* `$Comment_Config2` */
/* `$INSTANCE_NAME`_`$Config2_Name` Sample Rate: `$Sample_Rate_Config2` Samples per Second */
/* `$INSTANCE_NAME`_`$Config2_Name` Conversion Mode: `$Conversion_Mode_Config2` */
/* `$INSTANCE_NAME`_`$Config2_Name` Input Buffer Gain: `$Input_Buffer_Gain_Config2`   */
/* `$INSTANCE_NAME`_`$Config2_Name` Reference: `$ADC_Reference_Config2` */
/* `$INSTANCE_NAME`_`$Config2_Name` Input Range: `$ADC_Input_Range_Config2`  */
/* `$INSTANCE_NAME`_`$Config2_Name` Resolution: `$ADC_Resolution_Config2` bits */
/* `$INSTANCE_NAME`_`$Config2_Name` Clock: `$DFLT_CLK_FREQ_CFG2` Hz */

#define `$INSTANCE_NAME`_`$Config2_Name`_DEC_CR             (`$DFLT_DEC_CR_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DEC_SR             (`$DFLT_DEC_SR_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DEC_SHIFT1         (`$DFLT_DEC_SHIFT1_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DEC_SHIFT2         (`$DFLT_DEC_SHIFT2_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DEC_DR2            (`$DFLT_DEC_DR2_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DEC_DR2H           (`$DFLT_DEC_DR2H_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DEC_DR1            (`$DFLT_DEC_DR1_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DEC_OCOR           (`$DFLT_DEC_OCOR_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DEC_OCORM          (`$DFLT_DEC_OCORM_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DEC_OCORH          (`$DFLT_DEC_OCORH_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DEC_GVAL           (`$DFLT_DEC_GVAL_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DEC_GCOR           (`$DFLT_DEC_GCOR_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DEC_GCORH          (`$DFLT_DEC_GCORH_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DEC_COHER          (`$DFLT_DEC_COHER_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR0            (`$DFLT_DSM_CR0_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR1            (`$DFLT_DSM_CR1_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR2            (`$DFLT_DSM_CR2_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR3            (`$DFLT_DSM_CR3_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR4            (`$DFLT_DSM_CR4_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR5            (`$DFLT_DSM_CR5_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR6            (`$DFLT_DSM_CR6_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR7            (`$DFLT_DSM_CR7_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR8            (`$DFLT_DSM_CR8_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR9            (`$DFLT_DSM_CR9_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR10           (`$DFLT_DSM_CR10_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR11           (`$DFLT_DSM_CR11_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR12           (`$DFLT_DSM_CR12_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR13           (`$DFLT_DSM_CR13_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR14           (`$DFLT_DSM_CR14_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR15           (`$DFLT_DSM_CR15_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR16           (`$DFLT_DSM_CR16_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR17           (`$DFLT_DSM_CR17_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_REF0           (`$DFLT_DSM_REF0_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_REF2           (`$DFLT_DSM_REF2_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_REF3           (`$DFLT_DSM_REF3_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_DEM0           (`$DFLT_DSM_DEM0_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_DEM1           (`$DFLT_DSM_DEM1_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_BUF0           (`$DFLT_DSM_BUF0_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_BUF1           (`$DFLT_DSM_BUF1_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_BUF2           (`$DFLT_DSM_BUF2_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_BUF3           (`$DFLT_DSM_BUF3_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_OUT0           (`$DFLT_DSM_OUT0_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_OUT1           (`$DFLT_DSM_OUT1_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DSM_SW3            (`$DFLT_DSM_SW3_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_SRATE              (`$Sample_Rate_Config2`u )
#define `$INSTANCE_NAME`_`$Config2_Name`_CLOCKS_PER_SAMPLE  (`$DFLT_CLOCKS_PER_SAMPLE_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_CLOCK_FREQ         (`$DFLT_CLK_FREQ_CFG2`u)
#define `$INSTANCE_NAME`_`$Config2_Name`_CP_CLOCK_FREQ      (`$DFLT_CP_CLK_FREQ_CFG2`u)
#define `$INSTANCE_NAME`_`$Config2_Name`_REFERENCE_VOLTAGE  (`$DFLT_REF_VOLTAGE_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_COUNTS_PER_VOLT    (`$DFLT_COUNTS_PER_VOLT_CFG2`u)
#define `$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION         (`$ADC_Resolution_Config2`u)
#define `$INSTANCE_NAME`_`$Config2_Name`_CONVMODE           (`$Conversion_Mode_Config2`u)
#define `$INSTANCE_NAME`_`$Config2_Name`_IDEAL_DEC_GAIN     (`$DFLT_IDEAL_DEC_GAIN_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_INPUT_RANGE        (`$ADC_Input_Range_Config2`u)
#define `$INSTANCE_NAME`_`$Config2_Name`_INPUT_RANGE_VALUE  (`$ADC_Input_RangeValue_Config2`)

#define `$INSTANCE_NAME`_`$Config2_Name`_INPUT_MODE         (`$ADC_Input_Mode_Config2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_REFERENCE          (`$ADC_Reference_Config2`u)
#define `$INSTANCE_NAME`_`$Config2_Name`_BUFFER_GAIN        (`$Input_Buffer_Gain_Config2`u)

/* Input and DAC Cap values in pF */
#define `$INSTANCE_NAME`_`$Config2_Name`_IPCAP1VALUE        (`$DFLT_IPCap1Value_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_DACAPVALUE         (`$DFLT_DACCapValue_CFG2`)
#define `$INSTANCE_NAME`_`$Config2_Name`_IDEAL_ODDDEC_GAIN  (`$DFLT_IDEAL_ODDDEC_GAIN_CFG2`)

/* Below defines are depricated and should not be used. These are provided 
   just to keep the component backward compatible */
#define `$INSTANCE_NAME`_DEFAULT_SRATE_CFG2                 `$INSTANCE_NAME`_`$Config2_Name`_SRATE              
#define `$INSTANCE_NAME`_CLOCKS_PER_SAMPLE_CFG2             `$INSTANCE_NAME`_`$Config2_Name`_CLOCKS_PER_SAMPLE  
#define `$INSTANCE_NAME`_DFLT_CLOCK_FREQ_CFG2               `$INSTANCE_NAME`_`$Config2_Name`_CLOCK_FREQ         
#define `$INSTANCE_NAME`_REFERENCE_VOLTAGE_CFG2             `$INSTANCE_NAME`_`$Config2_Name`_REFERENCE_VOLTAGE  
#define `$INSTANCE_NAME`_DFLT_COUNTS_PER_VOLT_CFG2          `$INSTANCE_NAME`_`$Config2_Name`_COUNTS_PER_VOLT    
#define `$INSTANCE_NAME`_DEFAULT_RESOLUTION_CFG2            `$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION         
#define `$INSTANCE_NAME`_CONVMODE_CFG2                      `$INSTANCE_NAME`_`$Config2_Name`_CONVMODE           
#define `$INSTANCE_NAME`_DEFAULT_IDEAL_DEC_GAIN_CFG2        `$INSTANCE_NAME`_`$Config2_Name`_IDEAL_DEC_GAIN     
#define `$INSTANCE_NAME`_DEFAULT_INPUT_RANGE_CFG2           `$INSTANCE_NAME`_`$Config2_Name`_INPUT_RANGE        
#define `$INSTANCE_NAME`_DEFAULT_INPUT_RANGE_VALUE_CFG2     `$INSTANCE_NAME`_`$Config2_Name`_INPUT_RANGE_VALUE  
#define `$INSTANCE_NAME`_DEFAULT_INPUT_MODE_CFG2            `$INSTANCE_NAME`_`$Config2_Name`_INPUT_MODE         
#define `$INSTANCE_NAME`_DEFAULT_REFERENCE_CFG2             `$INSTANCE_NAME`_`$Config2_Name`_REFERENCE         
#define `$INSTANCE_NAME`_DEFAULT_BUFFER_GAIN_CONFIG2        `$INSTANCE_NAME`_`$Config2_Name`_BUFFER_GAIN       

/* Input and DAC Cap values in pF */
#define `$INSTANCE_NAME`_DEFAULT_IPCAP1VALUE_CFG2           `$INSTANCE_NAME`_`$Config2_Name`_IPCAP1VALUE       
#define `$INSTANCE_NAME`_DEFAULT_DACAPVALUE_CFG2            `$INSTANCE_NAME`_`$Config2_Name`_DACAPVALUE        
#define `$INSTANCE_NAME`_DEFAULT_IDEAL_ODDDEC_GAIN_CFG2     `$INSTANCE_NAME`_`$Config2_Name`_IDEAL_ODDDEC_GAIN 


/* Default register settings for the following configuration */
/* `$Comment_Config3` */
/* `$INSTANCE_NAME`_`$Config3_Name` Sample Rate: `$Sample_Rate_Config3` Samples per Second */
/* `$INSTANCE_NAME`_`$Config3_Name` Conversion Mode: `$Conversion_Mode_Config3` */
/* `$INSTANCE_NAME`_`$Config3_Name` Input Buffer Gain: `$Input_Buffer_Gain_Config3`   */
/* `$INSTANCE_NAME`_`$Config3_Name` Reference: `$ADC_Reference_Config3` */
/* `$INSTANCE_NAME`_`$Config3_Name` Input Range: `$ADC_Input_Range_Config3`  */
/* `$INSTANCE_NAME`_`$Config3_Name` Resolution: `$ADC_Resolution_Config3` bits */
/* `$INSTANCE_NAME`_`$Config3_Name` Clock: `$DFLT_CLK_FREQ_CFG3` Hz */

#define `$INSTANCE_NAME`_`$Config3_Name`_DEC_CR             (`$DFLT_DEC_CR_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DEC_SR             (`$DFLT_DEC_SR_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DEC_SHIFT1         (`$DFLT_DEC_SHIFT1_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DEC_SHIFT2         (`$DFLT_DEC_SHIFT2_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DEC_DR2            (`$DFLT_DEC_DR2_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DEC_DR2H           (`$DFLT_DEC_DR2H_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DEC_DR1            (`$DFLT_DEC_DR1_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DEC_OCOR           (`$DFLT_DEC_OCOR_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DEC_OCORM          (`$DFLT_DEC_OCORM_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DEC_OCORH          (`$DFLT_DEC_OCORH_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DEC_GVAL           (`$DFLT_DEC_GVAL_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DEC_GCOR           (`$DFLT_DEC_GCOR_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DEC_GCORH          (`$DFLT_DEC_GCORH_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DEC_COHER          (`$DFLT_DEC_COHER_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR0            (`$DFLT_DSM_CR0_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR1            (`$DFLT_DSM_CR1_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR2            (`$DFLT_DSM_CR2_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR3            (`$DFLT_DSM_CR3_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR4            (`$DFLT_DSM_CR4_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR5            (`$DFLT_DSM_CR5_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR6            (`$DFLT_DSM_CR6_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR7            (`$DFLT_DSM_CR7_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR8            (`$DFLT_DSM_CR8_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR9            (`$DFLT_DSM_CR9_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR10           (`$DFLT_DSM_CR10_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR11           (`$DFLT_DSM_CR11_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR12           (`$DFLT_DSM_CR12_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR13           (`$DFLT_DSM_CR13_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR14           (`$DFLT_DSM_CR14_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR15           (`$DFLT_DSM_CR15_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR16           (`$DFLT_DSM_CR16_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR17           (`$DFLT_DSM_CR17_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_REF0           (`$DFLT_DSM_REF0_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_REF2           (`$DFLT_DSM_REF2_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_REF3           (`$DFLT_DSM_REF3_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_DEM0           (`$DFLT_DSM_DEM0_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_DEM1           (`$DFLT_DSM_DEM1_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_BUF0           (`$DFLT_DSM_BUF0_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_BUF1           (`$DFLT_DSM_BUF1_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_BUF2           (`$DFLT_DSM_BUF2_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_BUF3           (`$DFLT_DSM_BUF3_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_OUT0           (`$DFLT_DSM_OUT0_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_OUT1           (`$DFLT_DSM_OUT1_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DSM_SW3            (`$DFLT_DSM_SW3_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_SRATE              (`$Sample_Rate_Config3`u)
#define `$INSTANCE_NAME`_`$Config3_Name`_CLOCKS_PER_SAMPLE  (`$DFLT_CLOCKS_PER_SAMPLE_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_CLOCK_FREQ         (`$DFLT_CLK_FREQ_CFG3`u)
#define `$INSTANCE_NAME`_`$Config3_Name`_CP_CLOCK_FREQ      (`$DFLT_CP_CLK_FREQ_CFG3`u)
#define `$INSTANCE_NAME`_`$Config3_Name`_REFERENCE_VOLTAGE  (`$DFLT_REF_VOLTAGE_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_COUNTS_PER_VOLT    (`$DFLT_COUNTS_PER_VOLT_CFG3`u)
#define `$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION         (`$ADC_Resolution_Config3`u)
#define `$INSTANCE_NAME`_`$Config3_Name`_CONVMODE           (`$Conversion_Mode_Config3`u)
#define `$INSTANCE_NAME`_`$Config3_Name`_IDEAL_DEC_GAIN     (`$DFLT_IDEAL_DEC_GAIN_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_INPUT_RANGE        (`$ADC_Input_Range_Config3`u)
#define `$INSTANCE_NAME`_`$Config3_Name`_INPUT_MODE         (`$ADC_Input_Mode_Config3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_REFERENCE          (`$ADC_Reference_Config3`u)
#define `$INSTANCE_NAME`_`$Config3_Name`_BUFFER_GAIN        (`$Input_Buffer_Gain_Config3`u)
#define `$INSTANCE_NAME`_`$Config3_Name`_INPUT_RANGE_VALUE  (`$ADC_Input_RangeValue_Config3`)

/* Input and DAC Cap values in pF */
#define `$INSTANCE_NAME`_`$Config3_Name`_IPCAP1VALUE        (`$DFLT_IPCap1Value_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_DACAPVALUE         (`$DFLT_DACCapValue_CFG3`)
#define `$INSTANCE_NAME`_`$Config3_Name`_IDEAL_ODDDEC_GAIN  (`$DFLT_IDEAL_ODDDEC_GAIN_CFG3`)

/* Below defines are depricated and should not be used. These are provided 
   just to keep the component backward compatible */
#define `$INSTANCE_NAME`_DEFAULT_SRATE_CFG3                 `$INSTANCE_NAME`_`$Config3_Name`_SRATE              
#define `$INSTANCE_NAME`_CLOCKS_PER_SAMPLE_CFG3             `$INSTANCE_NAME`_`$Config3_Name`_CLOCKS_PER_SAMPLE  
#define `$INSTANCE_NAME`_DFLT_CLOCK_FREQ_CFG3               `$INSTANCE_NAME`_`$Config3_Name`_CLOCK_FREQ         
#define `$INSTANCE_NAME`_REFERENCE_VOLTAGE_CFG3             `$INSTANCE_NAME`_`$Config3_Name`_REFERENCE_VOLTAGE  
#define `$INSTANCE_NAME`_DFLT_COUNTS_PER_VOLT_CFG3          `$INSTANCE_NAME`_`$Config3_Name`_COUNTS_PER_VOLT    
#define `$INSTANCE_NAME`_DEFAULT_RESOLUTION_CFG3            `$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION         
#define `$INSTANCE_NAME`_CONVMODE_CFG3                      `$INSTANCE_NAME`_`$Config3_Name`_CONVMODE           
#define `$INSTANCE_NAME`_DEFAULT_IDEAL_DEC_GAIN_CFG3        `$INSTANCE_NAME`_`$Config3_Name`_IDEAL_DEC_GAIN     
#define `$INSTANCE_NAME`_DEFAULT_INPUT_RANGE_CFG3           `$INSTANCE_NAME`_`$Config3_Name`_INPUT_RANGE        
#define `$INSTANCE_NAME`_DEFAULT_INPUT_RANGE_VALUE_CFG3     `$INSTANCE_NAME`_`$Config3_Name`_INPUT_RANGE_VALUE  
#define `$INSTANCE_NAME`_DEFAULT_INPUT_MODE_CFG3            `$INSTANCE_NAME`_`$Config3_Name`_INPUT_MODE         
#define `$INSTANCE_NAME`_DEFAULT_REFERENCE_CFG3             `$INSTANCE_NAME`_`$Config3_Name`_REFERENCE         
#define `$INSTANCE_NAME`_DEFAULT_BUFFER_GAIN_CONFIG3        `$INSTANCE_NAME`_`$Config3_Name`_BUFFER_GAIN       

/* Input and DAC Cap values in pF */
#define `$INSTANCE_NAME`_DEFAULT_IPCAP1VALUE_CFG3           `$INSTANCE_NAME`_`$Config3_Name`_IPCAP1VALUE       
#define `$INSTANCE_NAME`_DEFAULT_DACAPVALUE_CFG3            `$INSTANCE_NAME`_`$Config3_Name`_DACAPVALUE        
#define `$INSTANCE_NAME`_DEFAULT_IDEAL_ODDDEC_GAIN_CFG3     `$INSTANCE_NAME`_`$Config3_Name`_IDEAL_ODDDEC_GAIN 


/* Default register settings for the following configuration */
/* `$Comment_Config4` */
/* `$INSTANCE_NAME`_`$Config4_Name` Sample Rate: `$Sample_Rate_Config4` Samples per Second */
/* `$INSTANCE_NAME`_`$Config4_Name` Conversion Mode: `$Conversion_Mode_Config4` */
/* `$INSTANCE_NAME`_`$Config4_Name` Input Buffer Gain: `$Input_Buffer_Gain_Config4`   */
/* `$INSTANCE_NAME`_`$Config4_Name` Reference: `$ADC_Reference_Config4` */
/* `$INSTANCE_NAME`_`$Config4_Name` Input Range: `$ADC_Input_Range_Config4`  */
/* `$INSTANCE_NAME`_`$Config4_Name` Resolution: `$ADC_Resolution_Config4` bits */
/* `$INSTANCE_NAME`_`$Config4_Name` Clock: `$DFLT_CLK_FREQ_CFG4` Hz */

#define `$INSTANCE_NAME`_`$Config4_Name`_DEC_CR             (`$DFLT_DEC_CR_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DEC_SR             (`$DFLT_DEC_SR_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DEC_SHIFT1         (`$DFLT_DEC_SHIFT1_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DEC_SHIFT2         (`$DFLT_DEC_SHIFT2_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DEC_DR2            (`$DFLT_DEC_DR2_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DEC_DR2H           (`$DFLT_DEC_DR2H_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DEC_DR1            (`$DFLT_DEC_DR1_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DEC_OCOR           (`$DFLT_DEC_OCOR_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DEC_OCORM          (`$DFLT_DEC_OCORM_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DEC_OCORH          (`$DFLT_DEC_OCORH_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DEC_GVAL           (`$DFLT_DEC_GVAL_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DEC_GCOR           (`$DFLT_DEC_GCOR_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DEC_GCORH          (`$DFLT_DEC_GCORH_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DEC_COHER          (`$DFLT_DEC_COHER_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR0            (`$DFLT_DSM_CR0_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR1            (`$DFLT_DSM_CR1_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR2            (`$DFLT_DSM_CR2_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR3            (`$DFLT_DSM_CR3_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR4            (`$DFLT_DSM_CR4_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR5            (`$DFLT_DSM_CR5_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR6            (`$DFLT_DSM_CR6_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR7            (`$DFLT_DSM_CR7_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR8            (`$DFLT_DSM_CR8_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR9            (`$DFLT_DSM_CR9_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR10           (`$DFLT_DSM_CR10_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR11           (`$DFLT_DSM_CR11_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR12           (`$DFLT_DSM_CR12_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR13           (`$DFLT_DSM_CR13_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR14           (`$DFLT_DSM_CR14_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR15           (`$DFLT_DSM_CR15_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR16           (`$DFLT_DSM_CR16_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR17           (`$DFLT_DSM_CR17_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_REF0           (`$DFLT_DSM_REF0_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_REF2           (`$DFLT_DSM_REF2_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_REF3           (`$DFLT_DSM_REF3_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_DEM0           (`$DFLT_DSM_DEM0_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_DEM1           (`$DFLT_DSM_DEM1_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_BUF0           (`$DFLT_DSM_BUF0_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_BUF1           (`$DFLT_DSM_BUF1_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_BUF2           (`$DFLT_DSM_BUF2_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_BUF3           (`$DFLT_DSM_BUF3_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_OUT0           (`$DFLT_DSM_OUT0_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_OUT1           (`$DFLT_DSM_OUT1_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DSM_SW3            (`$DFLT_DSM_SW3_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_SRATE              (`$Sample_Rate_Config4`u)         
#define `$INSTANCE_NAME`_`$Config4_Name`_CLOCKS_PER_SAMPLE  (`$DFLT_CLOCKS_PER_SAMPLE_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_CLOCK_FREQ         (`$DFLT_CLK_FREQ_CFG4`u)
#define `$INSTANCE_NAME`_`$Config4_Name`_CP_CLOCK_FREQ      (`$DFLT_CP_CLK_FREQ_CFG4`u)
#define `$INSTANCE_NAME`_`$Config4_Name`_REFERENCE_VOLTAGE  (`$DFLT_REF_VOLTAGE_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_COUNTS_PER_VOLT    (`$DFLT_COUNTS_PER_VOLT_CFG4`u)
#define `$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION         (`$ADC_Resolution_Config4`u)
#define `$INSTANCE_NAME`_`$Config4_Name`_CONVMODE           (`$Conversion_Mode_Config4`u)
#define `$INSTANCE_NAME`_`$Config4_Name`_IDEAL_DEC_GAIN     (`$DFLT_IDEAL_DEC_GAIN_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_INPUT_RANGE        (`$ADC_Input_Range_Config4`u)
#define `$INSTANCE_NAME`_`$Config4_Name`_INPUT_MODE         (`$ADC_Input_Mode_Config4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_REFERENCE          (`$ADC_Reference_Config4`u)
#define `$INSTANCE_NAME`_`$Config4_Name`_BUFFER_GAIN        (`$Input_Buffer_Gain_Config4`u)
#define `$INSTANCE_NAME`_`$Config4_Name`_INPUT_RANGE_VALUE  (`$ADC_Input_RangeValue_Config4`)

/* Input cap and DAC Cap values in pF */
#define `$INSTANCE_NAME`_`$Config4_Name`_IPCAP1VALUE        (`$DFLT_IPCap1Value_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_DACAPVALUE         (`$DFLT_DACCapValue_CFG4`)
#define `$INSTANCE_NAME`_`$Config4_Name`_IDEAL_ODDDEC_GAIN  (`$DFLT_IDEAL_ODDDEC_GAIN_CFG4`)

/* Below defines are depricated and should not be used. These are provided 
   just to keep the component backward compatible */
#define `$INSTANCE_NAME`_DEFAULT_SRATE_CFG4                 `$INSTANCE_NAME`_`$Config4_Name`_SRATE              
#define `$INSTANCE_NAME`_CLOCKS_PER_SAMPLE_CFG4             `$INSTANCE_NAME`_`$Config4_Name`_CLOCKS_PER_SAMPLE  
#define `$INSTANCE_NAME`_DFLT_CLOCK_FREQ_CFG4               `$INSTANCE_NAME`_`$Config4_Name`_CLOCK_FREQ         
#define `$INSTANCE_NAME`_REFERENCE_VOLTAGE_CFG4             `$INSTANCE_NAME`_`$Config4_Name`_REFERENCE_VOLTAGE  
#define `$INSTANCE_NAME`_DFLT_COUNTS_PER_VOLT_CFG4          `$INSTANCE_NAME`_`$Config4_Name`_COUNTS_PER_VOLT    
#define `$INSTANCE_NAME`_DEFAULT_RESOLUTION_CFG4            `$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION         
#define `$INSTANCE_NAME`_CONVMODE_CFG4                      `$INSTANCE_NAME`_`$Config4_Name`_CONVMODE           
#define `$INSTANCE_NAME`_DEFAULT_IDEAL_DEC_GAIN_CFG4        `$INSTANCE_NAME`_`$Config4_Name`_IDEAL_DEC_GAIN     
#define `$INSTANCE_NAME`_DEFAULT_INPUT_RANGE_CFG4           `$INSTANCE_NAME`_`$Config4_Name`_INPUT_RANGE        
#define `$INSTANCE_NAME`_DEFAULT_INPUT_RANGE_VALUE_CFG4     `$INSTANCE_NAME`_`$Config4_Name`_INPUT_RANGE_VALUE  
#define `$INSTANCE_NAME`_DEFAULT_INPUT_MODE_CFG4            `$INSTANCE_NAME`_`$Config4_Name`_INPUT_MODE         
#define `$INSTANCE_NAME`_DEFAULT_REFERENCE_CFG4             `$INSTANCE_NAME`_`$Config4_Name`_REFERENCE         
#define `$INSTANCE_NAME`_DEFAULT_BUFFER_GAIN_CONFIG4        `$INSTANCE_NAME`_`$Config4_Name`_BUFFER_GAIN       

/* Input and DAC Cap values in pF */
#define `$INSTANCE_NAME`_DEFAULT_IPCAP1VALUE_CFG4           `$INSTANCE_NAME`_`$Config4_Name`_IPCAP1VALUE       
#define `$INSTANCE_NAME`_DEFAULT_DACAPVALUE_CFG4            `$INSTANCE_NAME`_`$Config4_Name`_DACAPVALUE        
#define `$INSTANCE_NAME`_DEFAULT_IDEAL_ODDDEC_GAIN_CFG4     `$INSTANCE_NAME`_`$Config4_Name`_IDEAL_ODDDEC_GAIN 

#endif /* CY_ADC_DELSIG_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
