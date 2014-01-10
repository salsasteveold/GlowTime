/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Successive approximation ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/



#if !defined(CY_ADC_SAR_`$INSTANCE_NAME`_H) /* CY_ADC_SAR_`$INSTANCE_NAME`_H */
#define CY_ADC_SAR_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;
/* Acceptable types from MISRA-C specifying signedness and size.*/


/***************************************
*        Function Prototypes
***************************************/

void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_SetPower(uint8 power);
void `$INSTANCE_NAME`_SetResolution(uint8 resolution);
    
uint8 `$INSTANCE_NAME`_IsEndConversion(uint8 retMode);
int8 `$INSTANCE_NAME`_GetResult8(void);
int16 `$INSTANCE_NAME`_GetResult16(void);

void `$INSTANCE_NAME`_SetOffset(int16 offset);
void `$INSTANCE_NAME`_SetGain(int16 adcGain);
int16 `$INSTANCE_NAME`_CountsTo_mVolts(int16 adcCounts);
int32 `$INSTANCE_NAME`_CountsTo_uVolts(int16 adcCounts);
float32 `$INSTANCE_NAME`_CountsTo_Volts(int16 adcCounts);

void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Enable(void);

void `$INSTANCE_NAME`_SaveConfig(void);
void `$INSTANCE_NAME`_RestoreConfig(void);
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_Wakeup(void);

CY_ISR_PROTO( `$INSTANCE_NAME`_ISR );


/***************************************
* Global variables external identifier
***************************************/

extern uint8 `$INSTANCE_NAME`_initVar;
extern volatile int16 `$INSTANCE_NAME`_offset;
extern volatile int16 `$INSTANCE_NAME`_countsPerVolt;
extern volatile int16 `$INSTANCE_NAME`_shift;


/**************************************
*           API Constants
**************************************/

/* Resolution setting constants  */
`#cy_declare_enum ADC_Resolution_Type`

/*   Constants for IsEndConversion() "retMode" parameter  */
#define `$INSTANCE_NAME`_RETURN_STATUS              (0x01u)
#define `$INSTANCE_NAME`_WAIT_FOR_RESULT            (0x00u)

/* Constants for SetPower(power), "power" paramter */
`#cy_declare_enum ADC_Power_Type`
#define `$INSTANCE_NAME`_SAR_API_POWER_MASK         (0x03u)

/* Constants for Sleep mode states */
#define `$INSTANCE_NAME`_STARTED                    (0x02u)
#define `$INSTANCE_NAME`_ENABLED                    (0x01u)
#define `$INSTANCE_NAME`_DISABLED                   (0x00u)

#if(CY_PSOC5A)
    #define `$INSTANCE_NAME`_MAX_FREQUENCY          (14000000)       /*14Mhz*/
#else
    #define `$INSTANCE_NAME`_MAX_FREQUENCY          (18000000)       /*18Mhz*/
#endif /* CY_PSOC5A */


/**************************************
*    Enumerated Types and Parameters
**************************************/

/*  Reference constants */
`#cy_declare_enum ADC_Ref_Type`
/*  Input Range setting constants */
`#cy_declare_enum ADC_Input_Range_Type`
/*  Sample Mode setting constants */
`#cy_declare_enum ADC_SampleMode_Type`
/*  Extended Sample Mode setting constants */
`#cy_declare_enum ADC_SampleMode_revA_Type`
/*  Clock Source setting constants */
`#cy_declare_enum ADC_ClockSrc_Type`


/**************************************
*    Initial Parameter Constants
**************************************/

/* Default config values from user parameters */
#define `$INSTANCE_NAME`_DEFAULT_RESOLUTION     (`$ADC_Resolution`u)   /* ADC resolution selected with parameters.*/
#define `$INSTANCE_NAME`_DEFAULT_CONV_MODE      (`$ADC_SampleMode`u)        /* Default conversion method */
#define `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK   (`$ADC_Clock`u)             /* Default clock selection */
#define `$INSTANCE_NAME`_DEFAULT_REFERENCE      (`$ADC_Reference`u)         /* Default reference */
#define `$INSTANCE_NAME`_DEFAULT_RANGE          (`$ADC_Input_Range`u)       /* ADC Input Range selection */
#define `$INSTANCE_NAME`_CLOCK_FREQUENCY        (`$ADC_Clock_Frequency`u)   /* Clock frequency */
#define `$INSTANCE_NAME`_NOMINAL_CLOCK_FREQ     (`$NominalClockFrequency`)  /* Nominal Clock Frequency */
#define `$INSTANCE_NAME`_HIGH_POWER_PULSE       (`$HighPowerPulse`u)        /* Not zero when clock pulse > 50 ns */
#define `$INSTANCE_NAME`_IRQ_REMOVE             (`$rm_int`u)                /* Removes internal interrupt */

/* Use VDDA voltage define directly from cyfitter.h when VDDA reference has been used */
#define `$INSTANCE_NAME`_DEFAULT_REF_VOLTAGE \
                                   (((`$INSTANCE_NAME`_DEFAULT_REFERENCE != (uint8)`$INSTANCE_NAME`__EXT_REF) && \
                                    ((`$INSTANCE_NAME`_DEFAULT_RANGE == (uint8)`$INSTANCE_NAME`__VSSA_TO_VDDA) || \
                                     (`$INSTANCE_NAME`_DEFAULT_RANGE == (uint8)`$INSTANCE_NAME`__VNEG_VDDA_2_DIFF))) ? \
                                     (CYDEV_VDDA / 2) : \
                                   (((`$INSTANCE_NAME`_DEFAULT_REFERENCE != (uint8)`$INSTANCE_NAME`__EXT_REF) && \
                                     (`$INSTANCE_NAME`_DEFAULT_RANGE == (uint8)`$INSTANCE_NAME`__VNEG_VDDA_2_DIFF)) ? \
                                     CYDEV_VDDA : (`$Ref_Voltage`)))      /* ADC reference voltage. */
#define `$INSTANCE_NAME`_DEFAULT_REF_VOLTAGE_MV \
                                   (((`$INSTANCE_NAME`_DEFAULT_REFERENCE != (uint8)`$INSTANCE_NAME`__EXT_REF) && \
                                    ((`$INSTANCE_NAME`_DEFAULT_RANGE == (uint8)`$INSTANCE_NAME`__VSSA_TO_VDDA) || \
                                     (`$INSTANCE_NAME`_DEFAULT_RANGE == (uint8)`$INSTANCE_NAME`__VNEG_VDDA_2_DIFF))) ? \
                                     (CYDEV_VDDA_MV / 2) : \
                                  (((`$INSTANCE_NAME`_DEFAULT_REFERENCE != (uint8)`$INSTANCE_NAME`__EXT_REF) && \
                                    (`$INSTANCE_NAME`_DEFAULT_RANGE == (uint8)`$INSTANCE_NAME`__VNEG_VDDA_2_DIFF)) ? \
                                     CYDEV_VDDA_MV : (`$Ref_Voltage_mV`)))   /* ADC reference voltage in mV */
/* The power is set to normal power, 1/2, 1/3, 1/4 power depend on the clock setting. */
#define `$INSTANCE_NAME`_DEFAULT_POWER \
       ((`$INSTANCE_NAME`_NOMINAL_CLOCK_FREQ > (`$INSTANCE_NAME`_MAX_FREQUENCY / 2)) ? `$INSTANCE_NAME`__HIGHPOWER : \
       ((`$INSTANCE_NAME`_NOMINAL_CLOCK_FREQ > (`$INSTANCE_NAME`_MAX_FREQUENCY / 4)) ? `$INSTANCE_NAME`__MEDPOWER : \
                                                                                        `$INSTANCE_NAME`__MINPOWER))
/* Constant for a global usage */
/* Number of additional clocks for sampling data*/
#define `$INSTANCE_NAME`_SAMPLE_PRECHARGE       (`$Sample_Precharge`u)


/***************************************
*    Optional Function Prototypes
***************************************/

#if(`$INSTANCE_NAME`_DEFAULT_CONV_MODE != `$INSTANCE_NAME`__HARDWARE_TRIGGER)
    void `$INSTANCE_NAME`_StartConvert(void);
    void `$INSTANCE_NAME`_StopConvert(void);
#endif /* End `$INSTANCE_NAME`_DEFAULT_CONV_MODE != `$INSTANCE_NAME`__HARDWARE_TRIGGER */


/***************************************
*              Registers
***************************************/

#define `$INSTANCE_NAME`_SAR_TR0_REG                (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__TR0 )
#define `$INSTANCE_NAME`_SAR_TR0_PTR                (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__TR0 )
#define `$INSTANCE_NAME`_SAR_CSR0_REG               (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CSR0 )
#define `$INSTANCE_NAME`_SAR_CSR0_PTR               (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CSR0 )
#define `$INSTANCE_NAME`_SAR_CSR1_REG               (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CSR1 )
#define `$INSTANCE_NAME`_SAR_CSR1_PTR               (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CSR1 )
#define `$INSTANCE_NAME`_SAR_CSR2_REG               (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CSR2 )
#define `$INSTANCE_NAME`_SAR_CSR2_PTR               (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CSR2 )
#define `$INSTANCE_NAME`_SAR_CSR3_REG               (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CSR3 )
#define `$INSTANCE_NAME`_SAR_CSR3_PTR               (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CSR3 )
#define `$INSTANCE_NAME`_SAR_CSR4_REG               (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CSR4 )
#define `$INSTANCE_NAME`_SAR_CSR4_PTR               (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CSR4 )
#define `$INSTANCE_NAME`_SAR_CSR5_REG               (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CSR5 )
#define `$INSTANCE_NAME`_SAR_CSR5_PTR               (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CSR5 )
#define `$INSTANCE_NAME`_SAR_CSR6_REG               (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CSR6 )
#define `$INSTANCE_NAME`_SAR_CSR6_PTR               (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CSR6 )
#if(CY_PSOC5A)
    #define `$INSTANCE_NAME`_SAR_CSR7_REG               (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CSR7 )
    #define `$INSTANCE_NAME`_SAR_CSR7_PTR               (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CSR7 )
#endif /* End CY_PSOC5A */
#define `$INSTANCE_NAME`_SAR_SW0_REG                (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__SW0 )
#define `$INSTANCE_NAME`_SAR_SW0_PTR                (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__SW0 )
#define `$INSTANCE_NAME`_SAR_SW2_REG                (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__SW2 )
#define `$INSTANCE_NAME`_SAR_SW2_PTR                (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__SW2 )
#define `$INSTANCE_NAME`_SAR_SW3_REG                (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__SW3 )
#define `$INSTANCE_NAME`_SAR_SW3_PTR                (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__SW3 )
#define `$INSTANCE_NAME`_SAR_SW4_REG                (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__SW4 )
#define `$INSTANCE_NAME`_SAR_SW4_PTR                (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__SW4 )
#define `$INSTANCE_NAME`_SAR_SW6_REG                (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__SW6 )
#define `$INSTANCE_NAME`_SAR_SW6_PTR                (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__SW6 )
#define `$INSTANCE_NAME`_SAR_CLK_REG                (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CLK )
#define `$INSTANCE_NAME`_SAR_CLK_PTR                (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__CLK )
#define `$INSTANCE_NAME`_SAR_WRK0_REG               (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__WRK0 )
#define `$INSTANCE_NAME`_SAR_WRK0_PTR               (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__WRK0 )
#define `$INSTANCE_NAME`_SAR_WRK1_REG               (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__WRK1 )
#define `$INSTANCE_NAME`_SAR_WRK1_PTR               (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__WRK1 )
#define `$INSTANCE_NAME`_SAR_WRK_PTR                (  (reg16 *) `$INSTANCE_NAME`_ADC_SAR__WRK0 )
#define `$INSTANCE_NAME`_PWRMGR_SAR_REG             (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__PM_ACT_CFG )
#define `$INSTANCE_NAME`_PWRMGR_SAR_PTR             (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__PM_ACT_CFG )
#define `$INSTANCE_NAME`_STBY_PWRMGR_SAR_REG        (* (reg8 *) `$INSTANCE_NAME`_ADC_SAR__PM_STBY_CFG )
#define `$INSTANCE_NAME`_STBY_PWRMGR_SAR_PTR        (  (reg8 *) `$INSTANCE_NAME`_ADC_SAR__PM_STBY_CFG )

/* renamed registers for backward compatible */
#define `$INSTANCE_NAME`_SAR_WRK0                   `$INSTANCE_NAME`_SAR_WRK0_REG
#define `$INSTANCE_NAME`_SAR_WRK1                   `$INSTANCE_NAME`_SAR_WRK1_REG

/* This is only valid if there is an internal clock */
#if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
    /* Clock Power manager Reg */
    #define `$INSTANCE_NAME`_PWRMGR_CLK_REG         (* (reg8 *) `$INSTANCE_NAME`_theACLK__PM_ACT_CFG )
    #define `$INSTANCE_NAME`_PWRMGR_CLK_PTR         (  (reg8 *) `$INSTANCE_NAME`_theACLK__PM_ACT_CFG )
    #define `$INSTANCE_NAME`_STBY_PWRMGR_CLK_REG    (* (reg8 *) `$INSTANCE_NAME`_theACLK__PM_STBY_CFG )
    #define `$INSTANCE_NAME`_STBY_PWRMGR_CLK_PTR    (  (reg8 *) `$INSTANCE_NAME`_theACLK__PM_STBY_CFG )
#endif /*End `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */


/**************************************
*       Register Constants
**************************************/
/* PM_ACT_CFG (Active Power Mode CFG Register) Power enable mask */
#define `$INSTANCE_NAME`_ACT_PWR_SAR_EN             (uint8)(`$INSTANCE_NAME`_ADC_SAR__PM_ACT_MSK)

/* PM_STBY_CFG (Alternate Active Power Mode CFG Register) Power enable mask */
#define `$INSTANCE_NAME`_STBY_PWR_SAR_EN            (uint8)(`$INSTANCE_NAME`_ADC_SAR__PM_STBY_MSK)

/* This is only valid if there is an internal clock */
#if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
    /* Power enable mask */
    #define `$INSTANCE_NAME`_ACT_PWR_CLK_EN         (uint8)(`$INSTANCE_NAME`_theACLK__PM_ACT_MSK)
    /* Standby power enable mask */
    #define `$INSTANCE_NAME`_STBY_PWR_CLK_EN        (uint8)(`$INSTANCE_NAME`_theACLK__PM_STBY_MSK)
#endif /*End `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */

#if(`$INSTANCE_NAME`_IRQ_REMOVE == 0u)

    /* Priority of the ADC_SAR_IRQ interrupt. */
    #define `$INSTANCE_NAME`_INTC_PRIOR_NUMBER          (uint8)(`$INSTANCE_NAME`_IRQ__INTC_PRIOR_NUM)

    /* ADC_SAR_IRQ interrupt number */
    #define `$INSTANCE_NAME`_INTC_NUMBER                (uint8)(`$INSTANCE_NAME`_IRQ__INTC_NUMBER)

#endif   /* End `$INSTANCE_NAME`_IRQ_REMOVE */        


/******************************************/
/* SAR.TR0 Trim Register 0 definitions    */
/******************************************/

/* Bit Field  SAR_CAP_TRIM_ENUM */
#define `$INSTANCE_NAME`_SAR_CAP_TRIM_MASK          (0x07u)
#define `$INSTANCE_NAME`_SAR_CAP_TRIM_0             (0x00u)    /*decrease attenuation capacitor by 0*/
#define `$INSTANCE_NAME`_SAR_CAP_TRIM_1             (0x01u)    /*decrease by 0.5 LSB*/
#define `$INSTANCE_NAME`_SAR_CAP_TRIM_2             (0x02u)    /*decrease by 2*0.5 LSB = 1 LSB*/
#define `$INSTANCE_NAME`_SAR_CAP_TRIM_3             (0x03u)    /*decrease by 3*0.5 LSB = 1.5 LSB*/
#define `$INSTANCE_NAME`_SAR_CAP_TRIM_4             (0x04u)    /*decrease by 4*0.5 LSB = 2 LSB*/
#define `$INSTANCE_NAME`_SAR_CAP_TRIM_5             (0x05u)    /*decrease by 5*0.5 LSB = 2.5 LSB*/
#define `$INSTANCE_NAME`_SAR_CAP_TRIM_6             (0x06u)    /*decrease by 6*0.5 LSB = 3 LSB*/
#define `$INSTANCE_NAME`_SAR_CAP_TRIM_7             (0x07u)    /*decrease by 7*0.5 LSB = 3.5 LSB*/

#define `$INSTANCE_NAME`_SAR_TRIMUNIT               (0x08u)    /*Increase by 6fF*/

/*******************************************************/
/* SAR.CSR0 Satatus and Control Register 0 definitions */
/*******************************************************/

/* Bit Field  SAR_ICONT_LV_ENUM */
#define `$INSTANCE_NAME`_SAR_POWER_MASK             (0xC0u)
#define `$INSTANCE_NAME`_SAR_POWER_SHIFT            (0x06u)
#define `$INSTANCE_NAME`_ICONT_LV_0                 (0x00u)
#define `$INSTANCE_NAME`_ICONT_LV_1                 (0x40u)
#define `$INSTANCE_NAME`_ICONT_LV_2                 (0x80u)
#define `$INSTANCE_NAME`_ICONT_LV_3                 (0xC0u)
#define `$INSTANCE_NAME`_ICONT_FULL_CURRENT         (0x00u)

/* Bit Field SAR_RESET_SOFT_ENUM */
#define `$INSTANCE_NAME`_SAR_RESET_SOFT_NOTACTIVE   (0x00u)
#define `$INSTANCE_NAME`_SAR_RESET_SOFT_ACTIVE      (0x20u)

/* Bit Field  SAR_COHERENCY_EN_ENUM */
#define `$INSTANCE_NAME`_SAR_COHERENCY_EN_NOLOCK    (0x00u)
#define `$INSTANCE_NAME`_SAR_COHERENCY_EN_LOCK      (0x10u)

/* Bit Field  SAR_HIZ_ENUM */
#define `$INSTANCE_NAME`_SAR_HIZ_RETAIN             (0x00u)
#define `$INSTANCE_NAME`_SAR_HIZ_CLEAR              (0x08u)

/* Bit Field SAR_MX_SOF_ENUM */
#define `$INSTANCE_NAME`_SAR_MX_SOF_BIT             (0x00u)
#define `$INSTANCE_NAME`_SAR_MX_SOF_UDB             (0x04u)

/* Bit Field SAR_SOF_MODE_ENUM */
#define `$INSTANCE_NAME`_SAR_SOF_MODE_LEVEL         (0x00u)
#define `$INSTANCE_NAME`_SAR_SOF_MODE_EDGE          (0x02u)

/* Bit Field SAR_SOF_BIT_ENUM */
#define `$INSTANCE_NAME`_SAR_SOF_STOP_CONV          (0x00u)            /* Disable conversion */
#define `$INSTANCE_NAME`_SAR_SOF_START_CONV         (0x01u)            /* Enable conversion */

/*******************************************************/
/* SAR.CSR1 Satatus and Control Register 1 definitions */
/*******************************************************/

/* Bit Field  SAR_MUXREF_ENUM */
#define `$INSTANCE_NAME`_SAR_MUXREF_MASK            (0xE0u)
#define `$INSTANCE_NAME`_SAR_MUXREF_NONE            (0x00u)
#define `$INSTANCE_NAME`_SAR_MUXREF_VDDA_2          (0x40u)
#define `$INSTANCE_NAME`_SAR_MUXREF_DAC             (0x60u)
#define `$INSTANCE_NAME`_SAR_MUXREF_1_024V          (0x80u)
#define `$INSTANCE_NAME`_SAR_MUXREF_1_20V           (0xA0u)

/* Bit Field  SAR_SWVP_SRC_ENUM */
#define `$INSTANCE_NAME`_SAR_SWVP_SRC_REG           (0x00u)
#define `$INSTANCE_NAME`_SAR_SWVP_SRC_UDB           (0x10u)

/* Bit Field  SAR_SWVP_SRC_ENUM */
#define `$INSTANCE_NAME`_SAR_SWVN_SRC_REG           (0x00u)
#define `$INSTANCE_NAME`_SAR_SWVN_SRC_UDB           (0x08u)

/* Bit Field  SAR_IRQ_MODE_ENUM */
#define `$INSTANCE_NAME`_SAR_IRQ_MODE_LEVEL         (0x00u)
#define `$INSTANCE_NAME`_SAR_IRQ_MODE_EDGE          (0x04u)

/* Bit Field  SAR_IRQ_MASK_ENUM */
#define `$INSTANCE_NAME`_SAR_IRQ_MASK_DIS           (0x00u)
#define `$INSTANCE_NAME`_SAR_IRQ_MASK_EN            (0x02u)

/* Bit Field  SAR_EOF_ENUM */
#define `$INSTANCE_NAME`_SAR_EOF_0                  (0x00u)
#define `$INSTANCE_NAME`_SAR_EOF_1                  (0x01u)

/*******************************************************/
/* SAR.CSR2 Satatus and Control Register 2 definitions */
/*******************************************************/

/* Bit Field  SAR_RESOLUTION_ENUM */
#define `$INSTANCE_NAME`_SAR_RESOLUTION_MASK        (0xC0u)
#define `$INSTANCE_NAME`_SAR_RESOLUTION_SHIFT       (0x06u)
#define `$INSTANCE_NAME`_SAR_RESOLUTION_12BIT       (0xC0u)
#define `$INSTANCE_NAME`_SAR_RESOLUTION_10BIT       (0x80u)
#define `$INSTANCE_NAME`_SAR_RESOLUTION_8BIT        (0x40u)

/* Bit Field SAR_SAMPLE_WIDTH_ENUM */
#define `$INSTANCE_NAME`_SAR_SAMPLE_WIDTH_MASK      (0x3Fu)
#define `$INSTANCE_NAME`_SAR_SAMPLE_WIDTH_MIN       (0x00u)   /* minimum sample time: +1 clock cycle */
#define `$INSTANCE_NAME`_SAR_SAMPLE_WIDTH           (`$INSTANCE_NAME`_SAMPLE_PRECHARGE - 0x02u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_WIDTH_MAX       (0x07u)   /* maximum sample time: +8 clock cycles */

/*******************************************************/
/* SAR.CSR3 Satatus and Control Register 3 definitions */
/*******************************************************/

/* Bit Field  SAR_EN_CP_ENUM */
#define `$INSTANCE_NAME`_SAR_EN_CP_DIS              (0x00u)
#define `$INSTANCE_NAME`_SAR_EN_CP_EN               (0x80u)

/* Bit Field  SAR_EN_RESVDA_ENUM */
#define `$INSTANCE_NAME`_SAR_EN_RESVDA_DIS          (0x00u)
#define `$INSTANCE_NAME`_SAR_EN_RESVDA_EN           (0x40u)

/* Bit Field  SAR_PWR_CTRL_VCM_ENUM */
#define `$INSTANCE_NAME`_SAR_PWR_CTRL_VCM_MASK      (0x30u)
#define `$INSTANCE_NAME`_SAR_PWR_CTRL_VCM_0         (0x00u)
#define `$INSTANCE_NAME`_SAR_PWR_CTRL_VCM_1         (0x10u)
#define `$INSTANCE_NAME`_SAR_PWR_CTRL_VCM_2         (0x20u)
#define `$INSTANCE_NAME`_SAR_PWR_CTRL_VCM_3         (0x30u)

/* Bit Field  SAR_PWR_CTRL_VREF_ENUM */
#define `$INSTANCE_NAME`_SAR_PWR_CTRL_VREF_MASK     (0x0Cu)
#define `$INSTANCE_NAME`_SAR_PWR_CTRL_VREF_0        (0x00u)
#define `$INSTANCE_NAME`_SAR_PWR_CTRL_VREF_DIV_BY2  (0x04u)
#define `$INSTANCE_NAME`_SAR_PWR_CTRL_VREF_DIV_BY3  (0x08u)
#define `$INSTANCE_NAME`_SAR_PWR_CTRL_VREF_DIV_BY4  (0x0Cu)

/* Bit Field  SAR_EN_BUF_VCM_ENUM */
#define `$INSTANCE_NAME`_SAR_EN_BUF_VCM_DIS         (0x00u)
#define `$INSTANCE_NAME`_SAR_EN_BUF_VCM_EN          (0x02u)

/* Bit Field  SAR_EN_BUF_VREF_ENUM */
#define `$INSTANCE_NAME`_SAR_EN_BUF_VREF_DIS        (0x00u)
#define `$INSTANCE_NAME`_SAR_EN_BUF_VREF_EN         (0x01u)

/*******************************************************/
/* SAR.CSR4 Satatus and Control Register 4 definitions */
/*******************************************************/

/* Bit Field  SAR_DFT_INC_ENUM */
#define `$INSTANCE_NAME`_SAR_DFT_INC_MASK           (0x0Fu)
#define `$INSTANCE_NAME`_SAR_DFT_INC_DIS            (0x00u)
#define `$INSTANCE_NAME`_SAR_DFT_INC_EN             (0x0Fu)

/* Bit Field  SAR_DFT_INC_ENUM */
#define `$INSTANCE_NAME`_SAR_DFT_OUTC_MASK          (0x70u)
#define `$INSTANCE_NAME`_SAR_DFT_OUTC_DIS           (0x00u)
#define `$INSTANCE_NAME`_SAR_DFT_OUTC_EN            (0x70u)

/*******************************************************/
/* SAR.CSR5 Satatus and Control Register 5 definitions */
/*******************************************************/

/* Bit Field  SAR_OVERRUN_DET_EN_ENUM */
#define `$INSTANCE_NAME`_SAR_OVERRUN_DET_EN_EN      (0x80u)

/* Bit Field  SAR_DLY_INC_ENUM */
#define `$INSTANCE_NAME`_SAR_DLY_INC                (0x40u)

/* Bit Field  SAR_DCEN_ENUM */
#define `$INSTANCE_NAME`_SAR_DCEN                   (0x20u)

/* Bit Field  SAR_EN_CSEL_DFT_ENUM */
#define `$INSTANCE_NAME`_SAR_EN_CSEL_DFT_DISABLED   (0x00u)
#define `$INSTANCE_NAME`_SAR_EN_CSEL_DFT_ENABLED    (0x10u)

/* Bit Field  SAR_SEL_CSEL_DFT_ENUM */
#define `$INSTANCE_NAME`_SAR_SEL_CSEL_DFT_MASK      (0x0Fu)
#define `$INSTANCE_NAME`_SAR_SEL_CSEL_DFT_MIN       (0x00u)
#define `$INSTANCE_NAME`_SAR_SEL_CSEL_DFT_MAX       (0x0Fu)

/*******************************************************/
/* SAR.CSR6 Satatus and Control Register 6 definitions */
/*******************************************************/
#define `$INSTANCE_NAME`_INT_VREF                   (0x18u)
#define `$INSTANCE_NAME`_INT_BYPASS_EXT_VREF        (0x04u)
#define `$INSTANCE_NAME`_VDDA_VREF                  (0x80u)

/*******************************************************/
/* SAR.CSR7 Satatus and Control Register 7 definitions */
/*******************************************************/

/* Bit Field  SAR_REF_S_ENUM */
#define `$INSTANCE_NAME`_SAR_REF_S_MSB_MASK         (0x3Fu)
#define `$INSTANCE_NAME`_SAR_REF_S_MSB_DIS          (0x00u)
#define `$INSTANCE_NAME`_SAR_REF_S8_MSB_DIS         (0x01u)
#define `$INSTANCE_NAME`_SAR_REF_S9_MSB_EN          (0x02u)
#define `$INSTANCE_NAME`_SAR_REF_S10_MSB_EN         (0x04u)
#define `$INSTANCE_NAME`_SAR_REF_S11_MSB_EN         (0x08u)
#define `$INSTANCE_NAME`_SAR_REF_S12_MSB_EN         (0x10u)
#define `$INSTANCE_NAME`_SAR_REF_S13_MSB_EN         (0x20u)

/*******************************************************/
/* SAR.CLK SAR Clock Selection Register definitions    */
/*******************************************************/

/* Bit Field  MX_PUMPCLK_ENUM */
#define `$INSTANCE_NAME`_SAR_MX_PUMPCLK_MASK        (0xE0u)
#define `$INSTANCE_NAME`_SAR_MX_PUMPCLK_0           (0x00u)
#define `$INSTANCE_NAME`_SAR_MX_PUMPCLK_1           (0x20u)
#define `$INSTANCE_NAME`_SAR_MX_PUMPCLK_2           (0x40u)
#define `$INSTANCE_NAME`_SAR_MX_PUMPCLK_3           (0x60u)
#define `$INSTANCE_NAME`_SAR_MX_PUMPCLK_4           (0x80u)

/* Bit Field  BYPASS_SYNC_ENUM */
#define `$INSTANCE_NAME`_SAR_BYPASS_SYNC_0          (0x00u)
#define `$INSTANCE_NAME`_SAR_BYPASS_SYNC_1          (0x10u)

/* Bit Field  MX_CLK_EN_ENUM */
#define `$INSTANCE_NAME`_SAR_MX_CLK_EN              (0x08u)

/* Bit Field  MX_CLK_ENUM  */
#define `$INSTANCE_NAME`_SAR_MX_CLK_MASK            (0x07u)
#define `$INSTANCE_NAME`_SAR_MX_CLK_0               (0x00u)
#define `$INSTANCE_NAME`_SAR_MX_CLK_1               (0x01u)
#define `$INSTANCE_NAME`_SAR_MX_CLK_2               (0x02u)
#define `$INSTANCE_NAME`_SAR_MX_CLK_3               (0x03u)
#define `$INSTANCE_NAME`_SAR_MX_CLK_4               (0x04u)

/*********************************************************/
/* ANAIF.WRK.SARS.SOF SAR Global Start-of-frame register */
/*********************************************************/

/* Bit Field  SAR_SOF_BIT_ENUM */
#define `$INSTANCE_NAME`_SAR_SOFR_BIT_MASK          (0x03u)
#define `$INSTANCE_NAME`_SAR_SOFR_BIT_0             (0x00u)
#define `$INSTANCE_NAME`_SAR_SOFR_BIT_1             (0x01u)

/***********************************************/
/* SAR.SW3 SAR Analog Routing Register 3       */
/***********************************************/
#define `$INSTANCE_NAME`_SAR_VP_VSSA                (0x04u)
#define `$INSTANCE_NAME`_SAR_VN_AMX                 (0x10u)
#define `$INSTANCE_NAME`_SAR_VN_VREF                (0x20u)
#define `$INSTANCE_NAME`_SAR_VN_VSSA                (0x40u)
#define `$INSTANCE_NAME`_SAR_VN_MASK                (0x60u)

/***********************************************/
/* SAR.WRKx SAR Working Register               */
/***********************************************/
#define `$INSTANCE_NAME`_SAR_WRK_MAX                (0xFFFu)
#define `$INSTANCE_NAME`_SAR_DIFF_SHIFT             (0x800u)

#endif /* End CY_ADC_SAR_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
