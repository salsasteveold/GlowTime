/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the Delta-Sigma ADC
*  Component.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "`$INSTANCE_NAME`.h"

#if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
    #include "`$INSTANCE_NAME`_theACLK.h"
#endif /* `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */

#include "`$INSTANCE_NAME`_Ext_CP_Clk.h"

#if(`$INSTANCE_NAME`_DEFAULT_INPUT_MODE)
    #include "`$INSTANCE_NAME`_AMux.h"
#endif /* `$INSTANCE_NAME`_DEFAULT_INPUT_MODE */

/* Software flag for checking conversion completed or not */
volatile uint8 `$INSTANCE_NAME`_convDone = 0u;

/* Software flag to stop conversion for single sample conversion mode 
   with resolution above 16 bits */
volatile uint8 `$INSTANCE_NAME`_stopConversion = 0u;

/* To run the initialization block only at the start up */
uint8 `$INSTANCE_NAME`_initVar = 0u;

/* To check whether ADC started or not before switching the configuration */
volatile uint8 `$INSTANCE_NAME`_started = 0u;

/* Flag to hold ADC config number. By default active config is 1. */
volatile uint8 `$INSTANCE_NAME`_Config = 1u;

volatile int32 `$INSTANCE_NAME`_Offset = 0u;
volatile int32 `$INSTANCE_NAME`_CountsPerVolt = (uint32)`$INSTANCE_NAME`_`$Config1_Name`_COUNTS_PER_VOLT;

/* Only valid for PSoC5A */
/* Variable to decide whether or not to restore the register values from
    backup structure */
#if (CY_PSOC5A)
    uint8 `$INSTANCE_NAME`_restoreReg = 0u;
#endif /* CY_PSOC5A */

/* Valid only for PSoC5A silicon */
#if (CY_PSOC5A)
    /* Backup struct for power mode registers */
    static `$INSTANCE_NAME`_POWERMODE_BACKUP_STRUCT `$INSTANCE_NAME`_powerModeBackup = 
    {
        /* Initializing the structure fields with power mode registers of 
           config1 */
        `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR14,
        `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR15,
        `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR16,
        `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR17,
        `$INSTANCE_NAME`_`$Config1_Name`_DSM_REF0,
        `$INSTANCE_NAME`_`$Config1_Name`_DSM_BUF0,
        `$INSTANCE_NAME`_`$Config1_Name`_DSM_BUF1,
        `$INSTANCE_NAME`_`$Config1_Name`_DSM_CLK,
        `$INSTANCE_NAME`_BYPASS_DISABLED
    };
#endif /* CY_PSOC5A */


/****************************************************************************** 
* Function Name: `$INSTANCE_NAME`_Init
*******************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
* `$INSTANCE_NAME`_Start().
*  
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    /* Initialize the registers with default customizer settings for config1 */
    `$INSTANCE_NAME`_InitConfig(1);

    /* This is only valid if there is an internal clock */
    #if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
        `$INSTANCE_NAME`_theACLK_SetMode(CYCLK_DUTY);
    #endif /* `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */
    
    /* Set the duty cycle for charge pump clock */
    `$INSTANCE_NAME`_Ext_CP_Clk_SetMode(CYCLK_DUTY);

    /* To perform ADC calibration */
    `$INSTANCE_NAME`_GainCompensation(`$INSTANCE_NAME`_`$Config1_Name`_RANGE, 
                                      `$INSTANCE_NAME`_`$Config1_Name`_IDEAL_DEC_GAIN, 
                                      `$INSTANCE_NAME`_`$Config1_Name`_IDEAL_ODDDEC_GAIN, 
                                      `$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION);        
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
*******************************************************************************
*
* Summary: 
*  Enables the ADC DelSig block operation.
*  
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    /* Restore the power registers if silicon used is PSoC5A */
    #if (CY_PSOC5A)
        if(`$INSTANCE_NAME`_restoreReg && 
           (!(`$INSTANCE_NAME`_powerModeBackup.bypassRestore)))
        {
            `$INSTANCE_NAME`_RestorePowerRegisters();
            `$INSTANCE_NAME`_restoreReg = 0u;
        }
        `$INSTANCE_NAME`_powerModeBackup.bypassRestore = `$INSTANCE_NAME`_BYPASS_DISABLED;
    #endif /* CY_PSOC5A */

    /* Enable active mode power for ADC */
    `$INSTANCE_NAME`_PWRMGR_DEC_REG |= `$INSTANCE_NAME`_ACT_PWR_DEC_EN;
    `$INSTANCE_NAME`_PWRMGR_DSM_REG |= `$INSTANCE_NAME`_ACT_PWR_DSM_EN;
    
     /* Enable alternative active mode power for ADC */
    `$INSTANCE_NAME`_STBY_PWRMGR_DEC_REG |= `$INSTANCE_NAME`_STBY_PWR_DEC_EN;
    #if (CY_PSOC3 || CY_PSOC5LP)
    `$INSTANCE_NAME`_STBY_PWRMGR_DSM_REG |= `$INSTANCE_NAME`_STBY_PWR_DSM_EN;
    #endif /* CY_PSOC3 || CY_PSOC5LP */

    /* Config selected is 1, then before enablign the REFBUF0, REFBUF1 and 
	   VCMBUF's enable and press circuit and then after a delay of 3
	   microseconds, disable the press circuit. */
    if (`$INSTANCE_NAME`_Config == 1u)
	{
	    /* Disable PRES, Enable power to VCMBUF0, REFBUF0 and REFBUF1, enable 
	       PRES */
	    #if (CY_PSOC3 || CY_PSOC5LP)
	        `$INSTANCE_NAME`_RESET_CR4_REG |= `$INSTANCE_NAME`_IGNORE_PRESA1;
	        `$INSTANCE_NAME`_RESET_CR5_REG |= `$INSTANCE_NAME`_IGNORE_PRESA2;
	    #elif (CY_PSOC5A)
	        `$INSTANCE_NAME`_RESET_CR1_REG |= `$INSTANCE_NAME`_DIS_PRES1;
	        `$INSTANCE_NAME`_RESET_CR3_REG |= `$INSTANCE_NAME`_DIS_PRES2;
	    #endif /* CY_PSOC5A */
	    
	    `$INSTANCE_NAME`_DSM_CR17_REG |= (`$INSTANCE_NAME`_DSM_EN_BUF_VREF | `$INSTANCE_NAME`_DSM_EN_BUF_VCM);
	    #if ((`$INSTANCE_NAME`_`$Config1_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P03) || \
	         (`$INSTANCE_NAME`_`$Config1_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P32))
	        `$INSTANCE_NAME`_DSM_CR17_REG &= ~`$INSTANCE_NAME`_DSM_EN_BUF_VREF;
	    #endif /* Check for exteranl reference option */
	    #if ((`$INSTANCE_NAME`_`$Config1_Name`_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) && \
	          (CY_PSOC3 || CY_PSOC5LP) && \
	          ((`$INSTANCE_NAME`_`$Config1_Name`_REFERENCE != `$INSTANCE_NAME`_EXT_REF_ON_P03) && \
	         (`$INSTANCE_NAME`_`$Config1_Name`_REFERENCE != `$INSTANCE_NAME`_EXT_REF_ON_P32)))
	        `$INSTANCE_NAME`_DSM_REF0_REG |= `$INSTANCE_NAME`_DSM_EN_BUF_VREF_INN;
	    #endif /* `$INSTANCE_NAME`_IR_VSSA_TO_2VREF */
	    
	        /* Wait for 3 microseconds */
	    CyDelayUs(3);
        /* Enable the press circuit */
	    #if (CY_PSOC3 || CY_PSOC5LP)
	        `$INSTANCE_NAME`_RESET_CR4_REG &= ~`$INSTANCE_NAME`_IGNORE_PRESA1;
	        `$INSTANCE_NAME`_RESET_CR5_REG &= ~`$INSTANCE_NAME`_IGNORE_PRESA2;
	    #elif (CY_PSOC5A)
	        `$INSTANCE_NAME`_RESET_CR1_REG &= ~`$INSTANCE_NAME`_DIS_PRES1;
	        `$INSTANCE_NAME`_RESET_CR3_REG &= ~`$INSTANCE_NAME`_DIS_PRES2;
	    #endif /* CY_PSOC5A */
	}
    
    /* Enable negative pumps for DSM  */
    `$INSTANCE_NAME`_PUMP_CR1_REG  |= ( `$INSTANCE_NAME`_PUMP_CR1_CLKSEL | `$INSTANCE_NAME`_PUMP_CR1_FORCE );
 
    /* This is only valid if there is an internal clock */
    #if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
        `$INSTANCE_NAME`_PWRMGR_CLK_REG |= `$INSTANCE_NAME`_ACT_PWR_CLK_EN;        
        `$INSTANCE_NAME`_STBY_PWRMGR_CLK_REG |= `$INSTANCE_NAME`_STBY_PWR_CLK_EN;
    #endif /* `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */
    
    /* Enable the active and alternate active power for charge pump clock */
    `$INSTANCE_NAME`_PWRMGR_CHARGE_PUMP_CLK_REG |= `$INSTANCE_NAME`_ACT_PWR_CHARGE_PUMP_CLK_EN;
    `$INSTANCE_NAME`_STBY_PWRMGR_CHARGE_PUMP_CLK_REG |= `$INSTANCE_NAME`_STBY_PWR_CHARGE_PUMP_CLK_EN;
        
}


#if (CY_PSOC5A) /* valid only for PSoC5A silicon */
    /******************************************************************************* 
    * Function Name: `$INSTANCE_NAME`_RestorePowerRegisters
    ********************************************************************************
    *
    * Summary: 
    *  Restores the power registers on calling Start() API. This API is only 
    *   for internal use and valid only for PSoC5A.
    *  
    *
    * Parameters:  
    *  void
    *
    * Return: 
    *  void 
    *
    ***************************************************************************/
    void `$INSTANCE_NAME`_RestorePowerRegisters(void) `=ReentrantKeil($INSTANCE_NAME . "_RestorePowerRegisters")`
    {
        `$INSTANCE_NAME`_DSM_CR14_REG = `$INSTANCE_NAME`_powerModeBackup.DSM_CR_14;
        `$INSTANCE_NAME`_DSM_CR15_REG = `$INSTANCE_NAME`_powerModeBackup.DSM_CR_15;
        `$INSTANCE_NAME`_DSM_CR16_REG = `$INSTANCE_NAME`_powerModeBackup.DSM_CR_16;
        `$INSTANCE_NAME`_DSM_CR17_REG = `$INSTANCE_NAME`_powerModeBackup.DSM_CR_17;
        `$INSTANCE_NAME`_DSM_REF0_REG = `$INSTANCE_NAME`_powerModeBackup.DSM_REF0;
        `$INSTANCE_NAME`_DSM_BUF0_REG = `$INSTANCE_NAME`_powerModeBackup.DSM_BUF0;
        `$INSTANCE_NAME`_DSM_BUF1_REG = `$INSTANCE_NAME`_powerModeBackup.DSM_BUF1;
        `$INSTANCE_NAME`_DSM_CLK_REG = `$INSTANCE_NAME`_powerModeBackup.DSM_CLK;
    }


    /************************************************************************** 
    * Function Name: `$INSTANCE_NAME`_SavePowerRegisters
    ***************************************************************************
    *
    * Summary: 
    *  Save the power registers before stopping the block operation. This is 
    *  called by Stop() API. This API is only for internal use and valid only 
    *  for PSoC5A.
    *  
    *
    * Parameters:  
    *  void
    *
    * Return: 
    *  void 
    *
    **************************************************************************/
    void `$INSTANCE_NAME`_SavePowerRegisters(void) `=ReentrantKeil($INSTANCE_NAME . "_SavePowerRegisters")`
    {
        `$INSTANCE_NAME`_powerModeBackup.DSM_CR_14 = `$INSTANCE_NAME`_DSM_CR14_REG;
        `$INSTANCE_NAME`_powerModeBackup.DSM_CR_15 = `$INSTANCE_NAME`_DSM_CR15_REG;
        `$INSTANCE_NAME`_powerModeBackup.DSM_CR_16 = `$INSTANCE_NAME`_DSM_CR16_REG;
        `$INSTANCE_NAME`_powerModeBackup.DSM_CR_17 = `$INSTANCE_NAME`_DSM_CR17_REG;
        `$INSTANCE_NAME`_powerModeBackup.DSM_REF0 = `$INSTANCE_NAME`_DSM_REF0_REG;
        `$INSTANCE_NAME`_powerModeBackup.DSM_BUF0 = `$INSTANCE_NAME`_DSM_BUF0_REG;
        `$INSTANCE_NAME`_powerModeBackup.DSM_BUF1 = `$INSTANCE_NAME`_DSM_BUF1_REG;
        `$INSTANCE_NAME`_powerModeBackup.DSM_CLK = `$INSTANCE_NAME`_DSM_CLK_REG;
    }


    /************************************************************************* 
    * Function Name: `$INSTANCE_NAME`_SetLowPower
    ***************************************************************************
    *
    * Summary: 
    *  Set all the power registers of DSM block to low power mode. This API is
    *   called by Stop() API. This API is only for internal use and valid for 
    *   only PSoC5A.
    *  
    *
    * Parameters:  
    *  void
    *
    * Return: 
    *  void 
    *
    ***************************************************************************/
    void `$INSTANCE_NAME`_SetLowPower(void) `=ReentrantKeil($INSTANCE_NAME . "_SetLowPower")`
    {
        `$INSTANCE_NAME`_DSM_CR14_REG &= ~`$INSTANCE_NAME`_DSM_POWER1_MASK;
        `$INSTANCE_NAME`_DSM_CR14_REG |= `$INSTANCE_NAME`_DSM_POWER1_44UA;
        
        `$INSTANCE_NAME`_DSM_CR15_REG &= ~(`$INSTANCE_NAME`_DSM_POWER2_3_MASK | `$INSTANCE_NAME`_DSM_POWER_COMP_MASK);
        `$INSTANCE_NAME`_DSM_CR15_REG |= (`$INSTANCE_NAME`_DSM_POWER2_3_LOW | `$INSTANCE_NAME`_DSM_POWER_VERYLOW);
        
        `$INSTANCE_NAME`_DSM_CR16_REG &= ~(`$INSTANCE_NAME`_DSM_CP_PWRCTL_MASK | `$INSTANCE_NAME`_DSM_POWER_SUM_MASK |
                                           `$INSTANCE_NAME`_DSM_CP_ENABLE);
        `$INSTANCE_NAME`_DSM_CR16_REG |= (`$INSTANCE_NAME`_DSM_POWER_SUM_LOW | `$INSTANCE_NAME`_DSM_CP_PWRCTL_LOW);
        
        `$INSTANCE_NAME`_DSM_CR17_REG &= ~(`$INSTANCE_NAME`_DSM_EN_BUF_VREF | `$INSTANCE_NAME`_DSM_PWR_CTRL_VCM_MASK |
                                           `$INSTANCE_NAME`_DSM_PWR_CTRL_VREF_MASK | `$INSTANCE_NAME`_DSM_EN_BUF_VCM |
                                           `$INSTANCE_NAME`_DSM_PWR_CTRL_VREF_INN_MASK);
        `$INSTANCE_NAME`_DSM_CR17_REG |= (`$INSTANCE_NAME`_DSM_PWR_CTRL_VREF_0 | `$INSTANCE_NAME`_DSM_PWR_CTRL_VCM_0 |
                                           `$INSTANCE_NAME`_DSM_PWR_CTRL_VREF_INN_0);
        
        /* Disable reference buffers */
        `$INSTANCE_NAME`_DSM_REF0_REG &= ~(`$INSTANCE_NAME`_DSM_EN_BUF_VREF_INN | `$INSTANCE_NAME`_DSM_VREF_RES_DIV_EN |
                                           `$INSTANCE_NAME`_DSM_VCM_RES_DIV_EN);
            
        /* Disable the positive input buffer */
        `$INSTANCE_NAME`_DSM_BUF0_REG &= ~`$INSTANCE_NAME`_DSM_ENABLE_P;
        /* Disable the negative input buffer */
        `$INSTANCE_NAME`_DSM_BUF1_REG &= ~`$INSTANCE_NAME`_DSM_ENABLE_N;
        /* Disable the clock to DSM */
        `$INSTANCE_NAME`_DSM_CLK_REG &= ~(`$INSTANCE_NAME`_DSM_CLK_CLK_EN | `$INSTANCE_NAME`_DSM_CLK_BYPASS_SYNC);
    }
#endif /* CY_PSOC5A */


/******************************************************************************* 
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Delta Sigma Modulator with the default  
*  values, and sets the power to the given level.  A power level of 0, is the 
*  same as executing the stop function.
*
* Parameters:  
*  None
*
* Return: 
*  void 
*
* Global variables:
*  `$INSTANCE_NAME`_initVar:  Used to check the initial configuration,
*  modified when this function is called for the first time.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start() `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    if(`$INSTANCE_NAME`_initVar == 0u)
    {
        if(!(`$INSTANCE_NAME`_started))
        {
            `$INSTANCE_NAME`_Init();
        }
        `$INSTANCE_NAME`_initVar = 1u;
    }

    /* Enable the ADC */
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Stops and powers down ADC to lowest power state.
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    /* Stop conversions */
    `$INSTANCE_NAME`_DEC_CR_REG &= ~`$INSTANCE_NAME`_DEC_START_CONV;
    `$INSTANCE_NAME`_DEC_SR_REG |=  `$INSTANCE_NAME`_DEC_INTR_CLEAR;
    
    /* Disable PRES, Disable power to VCMBUF0, REFBUF0 and REFBUF1, 
       enable PRES */
    #if (CY_PSOC3 || CY_PSOC5LP)
        `$INSTANCE_NAME`_RESET_CR4_REG |= `$INSTANCE_NAME`_IGNORE_PRESA1;
        `$INSTANCE_NAME`_RESET_CR5_REG |= `$INSTANCE_NAME`_IGNORE_PRESA2;
    #elif (CY_PSOC5A)
        `$INSTANCE_NAME`_RESET_CR1_REG |= `$INSTANCE_NAME`_DIS_PRES1;
        `$INSTANCE_NAME`_RESET_CR3_REG |= `$INSTANCE_NAME`_DIS_PRES2;
    #endif /* CY_PSOC5A */
    
    `$INSTANCE_NAME`_DSM_CR17_REG &= ~(`$INSTANCE_NAME`_DSM_EN_BUF_VREF | `$INSTANCE_NAME`_DSM_EN_BUF_VCM);
    `$INSTANCE_NAME`_DSM_REF0_REG &= ~`$INSTANCE_NAME`_DSM_EN_BUF_VREF_INN;
    
    /* Wait for 3 microseconds. */
    CyDelayUs(3);
    
	/* Enable the press circuit */
    #if (CY_PSOC3 || CY_PSOC5LP)
        `$INSTANCE_NAME`_RESET_CR4_REG &= ~`$INSTANCE_NAME`_IGNORE_PRESA1;
        `$INSTANCE_NAME`_RESET_CR5_REG &= ~`$INSTANCE_NAME`_IGNORE_PRESA2;
    #elif (CY_PSOC5A)
        `$INSTANCE_NAME`_RESET_CR1_REG &= ~`$INSTANCE_NAME`_DIS_PRES1;
        `$INSTANCE_NAME`_RESET_CR3_REG &= ~`$INSTANCE_NAME`_DIS_PRES2;
    #endif /* CY_PSOC5A */
    
    /* If PSoC5A then don't disable the power instead put the block to  
       low power mode. Also, save current state of all the power configuration 
       registers before putting block to low power mode */
    #if (CY_PSOC5A)
        
        /* set the flag */
        `$INSTANCE_NAME`_restoreReg = 1u;
        
        `$INSTANCE_NAME`_SavePowerRegisters();
        `$INSTANCE_NAME`_SetLowPower();
    #else    
        /* Disable power to the ADC */
        `$INSTANCE_NAME`_PWRMGR_DSM_REG &= ~`$INSTANCE_NAME`_ACT_PWR_DSM_EN;
    #endif /* CY_PSOC5A */
    
    /* Disable power to Decimator block */
    `$INSTANCE_NAME`_PWRMGR_DEC_REG &= ~`$INSTANCE_NAME`_ACT_PWR_DEC_EN;
    
    /* Disable alternative active power to the ADC */
    `$INSTANCE_NAME`_STBY_PWRMGR_DEC_REG &= ~`$INSTANCE_NAME`_STBY_PWR_DEC_EN;
    #if (CY_PSOC3 || CY_PSOC5LP)
    `$INSTANCE_NAME`_STBY_PWRMGR_DSM_REG &= ~`$INSTANCE_NAME`_STBY_PWR_DSM_EN;
    #endif /* CY_PSOC3 || CY_PSOC5LP */

   /* Disable negative pumps for DSM  */
    `$INSTANCE_NAME`_PUMP_CR1_REG &= ~(`$INSTANCE_NAME`_PUMP_CR1_CLKSEL | `$INSTANCE_NAME`_PUMP_CR1_FORCE );
    
    /* This is only valid if there is an internal clock */
    #if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
        `$INSTANCE_NAME`_PWRMGR_CLK_REG &= ~`$INSTANCE_NAME`_ACT_PWR_CLK_EN;
        `$INSTANCE_NAME`_STBY_PWRMGR_CLK_REG &= ~`$INSTANCE_NAME`_STBY_PWR_CLK_EN;
    #endif /* `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */
    
    /* Disable power to charge pump clock */
    `$INSTANCE_NAME`_PWRMGR_CHARGE_PUMP_CLK_REG &= ~`$INSTANCE_NAME`_ACT_PWR_CHARGE_PUMP_CLK_EN;
    `$INSTANCE_NAME`_STBY_PWRMGR_CHARGE_PUMP_CLK_REG &= ~`$INSTANCE_NAME`_STBY_PWR_CHARGE_PUMP_CLK_EN;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetBufferGain
********************************************************************************
*
* Summary:
*  Set input buffer range.
*
* Parameters:  
*  gain:  Two bit value to select a gain of 1, 2, 4, or 8.
*
* Return: 
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetBufferGain(uint8 gain) `=ReentrantKeil($INSTANCE_NAME . "_SetBufferGain")`
{
    uint8 tmpReg;
    tmpReg = `$INSTANCE_NAME`_DSM_BUF1_REG & ~`$INSTANCE_NAME`_DSM_GAIN_MASK;
    tmpReg |= (gain << 2);
    `$INSTANCE_NAME`_DSM_BUF1_REG = tmpReg;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetCoherency
********************************************************************************
*
* Summary:
*  Sets the ADC output register coherency bit.
*
* Parameters:  
*  gain:  Two bit value to set the coherency bit.
          00-Coherency checking off
          01-low byte is key byte
          02-middle byte is the key byte
          03-high byte is the key byte
*
* Return: 
*  void
*
* Side Effects:  If the coherency is changed, for any reason, it should be 
*                changed back to the LSB when the provided "GetResult" API 
*                is used.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetCoherency(uint8 coherency) `=ReentrantKeil($INSTANCE_NAME . "_SetCoherency")`
{
    uint8 tmpReg;    
    tmpReg = `$INSTANCE_NAME`_DEC_COHER_REG & ~`$INSTANCE_NAME`_DEC_SAMP_KEY_MASK;
    tmpReg |= coherency;
    `$INSTANCE_NAME`_DEC_COHER_REG = tmpReg;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetGCOR
********************************************************************************
*
* Summary:
*  Calculates a new GCOR value and writes it into the GCOR register.
*
* Parameters:  
*  gainAdjust:  floating point value to set GCOR registers.
*
* Return: 
*  uint8:  0-if GCOR value is within the expected range.
           1- if GCOR is outside the expected range.
*
* Side Effects:  The GVAL register is set to the amount of valid bits in the
*                GCOR  register minus one. If GVAL is 15 (0x0F), all 16 bits
*                of the GCOR registers will be valid. If for example GVAL is 
*                11 (0x0B) only 12 bits will be valid. The least 4 bits will
*                be lost when the GCOR value is shifted 4 places to the right.
*
******************************************************************************/
uint8 `$INSTANCE_NAME`_SetGCOR(float gainAdjust) `=ReentrantKeil($INSTANCE_NAME . "_SetGCOR")`
{
    uint16 tmpReg;
    uint8 status;
    float tmpValue;
    
    tmpReg = `$INSTANCE_NAME`_DEC_GCORH_REG;
    tmpReg = (tmpReg << 8) | `$INSTANCE_NAME`_DEC_GCOR_REG;
    tmpValue = ((float)tmpReg / `$INSTANCE_NAME`_IDEAL_GAIN_CONST);
    tmpValue = tmpValue * gainAdjust;
    
    if (tmpValue > 1.9999)
    {
        status = 1;
    }
    else
    {
        tmpReg = (uint16)(tmpValue * `$INSTANCE_NAME`_IDEAL_GAIN_CONST);
        `$INSTANCE_NAME`_DEC_GCOR_REG = (uint8)tmpReg;
        `$INSTANCE_NAME`_DEC_GCORH_REG = (uint8) (tmpReg >> 8);
        status = 0;
    }
    
    return status;
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadGCOR
*******************************************************************************
*
* Summary:
*  This API returns the current GCOR register value, normalized based on the 
*  GVAL register settings.
*
* Parameters:  
*  void
*
* Return: 
*  uint16:  Normalized GCOR value.
*
* Side Effects:  If the GVAL register is set to a value greater than 0x0F, then
                 it gives unexpected value.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_ReadGCOR(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadGCOR")`
{
    uint8 gValue;
    uint16 gcorValue, gcorRegValue;
    
    gValue = `$INSTANCE_NAME`_DEC_GVAL_REG;
    gcorRegValue = CY_GET_REG16(`$INSTANCE_NAME`_DEC_GCOR_PTR);
    
    switch (gValue)
    {
        case `$INSTANCE_NAME`_GVAL_RESOLUTIN_8:
            gcorValue = gcorRegValue << (`$INSTANCE_NAME`_MAX_GVAL - gValue);
            break;
        
        case `$INSTANCE_NAME`_GVAL_RESOLUTIN_9:
            gcorValue = gcorRegValue << (`$INSTANCE_NAME`_MAX_GVAL - gValue);
            break;
            
        case `$INSTANCE_NAME`_GVAL_RESOLUTIN_10:
            gcorValue = gcorRegValue << (`$INSTANCE_NAME`_MAX_GVAL - gValue);
            break;
            
        case `$INSTANCE_NAME`_GVAL_RESOLUTIN_11:
            gcorValue = gcorRegValue << (`$INSTANCE_NAME`_MAX_GVAL - gValue);
            break;
            
        case `$INSTANCE_NAME`_GVAL_RESOLUTIN_12:
            gcorValue = gcorRegValue << (`$INSTANCE_NAME`_MAX_GVAL - gValue);
            break;
            
        case `$INSTANCE_NAME`_GVAL_RESOLUTIN_13:
            gcorValue = gcorRegValue << (`$INSTANCE_NAME`_MAX_GVAL - gValue);
            break;
            
        default:
            gcorValue = gcorRegValue;
            break;
    }
        
    return gcorValue;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetBufferChop
********************************************************************************
*
* Summary:
*  Sets the Delta Sigma Modulator Buffer chopper mode.
*
* Parameters:  
*  chopen:  If non-zero set the chopper mode.
*  chopFreq:  Chop frequency value.
*
* Return: 
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetBufferChop(uint8 chopen, uint8 chopFreq) `=ReentrantKeil($INSTANCE_NAME . "_SetBufferChop")`
{
    if(chopen != 0u)
    {
        `$INSTANCE_NAME`_DSM_BUF2_REG = (`$INSTANCE_NAME`_DSM_BUF_FCHOP_MASK & chopFreq) | \
                                         `$INSTANCE_NAME`_DSM_BUF_CHOP_EN;
    }
    else
    {
        `$INSTANCE_NAME`_DSM_BUF2_REG = 0x00u;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_StartConvert
********************************************************************************
*
* Summary:
*  Starts ADC conversion using the given mode.
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
*******************************************************************************/
void `$INSTANCE_NAME`_StartConvert(void) `=ReentrantKeil($INSTANCE_NAME . "_StartConvert")`
{
    /* Start the conversion */
    `$INSTANCE_NAME`_DEC_CR_REG |= `$INSTANCE_NAME`_DEC_START_CONV;  
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_StopConvert
********************************************************************************
*
* Summary:
*  Starts ADC conversion using the given mode.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  `$INSTANCE_NAME`_convDone:  Modified when conversion is complete for single
*   sample mode with resolution is above 16.
*
*******************************************************************************/
void `$INSTANCE_NAME`_StopConvert(void) `=ReentrantKeil($INSTANCE_NAME . "_StopConvert")`
{
    /* Stop all conversions */
    `$INSTANCE_NAME`_DEC_CR_REG &= ~`$INSTANCE_NAME`_DEC_START_CONV; 
    
    /* Software flag for checking conversion complete or not. Will be used when
       resolution is above 16 bits and conversion mode is single sample */
    `$INSTANCE_NAME`_convDone = 1u;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsEndConversion
********************************************************************************
*
* Summary:
*  Queries the ADC to see if conversion is complete
*
* Parameters:  
*  wMode:  Wait mode, 0 if return with answer immediately.
*                     1 if wait until conversion is complete, then return.
*
* Return: 
*  uint8 status:  0 =>  Conversion not complete.
*                 1 =>  Conversion complete.
*
* Global variables:
*  `$INSTANCE_NAME`_convDone:  Used to check whether conversion is complete
*  or not for single sample mode with resolution is above 16
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_IsEndConversion(uint8 wMode) `=ReentrantKeil($INSTANCE_NAME . "_IsEndConversion")`
{
    uint8 status;
        
    /* Check for stop convert if conversion mode is Single Sample with 
       resolution above 16 bit */
    if(`$INSTANCE_NAME`_stopConversion == 1u)
    {
        do
        {
            status = `$INSTANCE_NAME`_convDone;
        } while((status != `$INSTANCE_NAME`_DEC_CONV_DONE) && (wMode == `$INSTANCE_NAME`_WAIT_FOR_RESULT));
    }
    else
    {
        do 
        {
            status = `$INSTANCE_NAME`_DEC_SR_REG & `$INSTANCE_NAME`_DEC_CONV_DONE;
        } while((status != `$INSTANCE_NAME`_DEC_CONV_DONE) && (wMode == `$INSTANCE_NAME`_WAIT_FOR_RESULT));
    }
    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetResult8
********************************************************************************
*
* Summary:
*  Returns an 8-bit result or the LSB of the last conversion.
*
* Parameters:  
*  void
*
* Return: 
*  int8:  ADC result.
*
*******************************************************************************/
int8 `$INSTANCE_NAME`_GetResult8( void ) `=ReentrantKeil($INSTANCE_NAME . "_GetResult8")`
{
     return( `$INSTANCE_NAME`_DEC_SAMP_REG );
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetResult16
********************************************************************************
*
* Summary:
*  Returns a 16-bit result from the last ADC conversion.
*
* Parameters:  
*   void
*
* Return: 
*  int16:  ADC result.
*
*******************************************************************************/
int16 `$INSTANCE_NAME`_GetResult16(void) `=ReentrantKeil($INSTANCE_NAME . "_GetResult16")`
{
    uint16 result;
    
    #if (CY_PSOC3)
        result = `$INSTANCE_NAME`_DEC_SAMPM_REG ;
        result = (result << 8 ) | `$INSTANCE_NAME`_DEC_SAMP_REG;
    #else
        result = (CY_GET_REG16(`$INSTANCE_NAME`_DEC_SAMP_PTR));
    #endif /* CY_PSOC3 */
    
    return result;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetResult32
********************************************************************************
*
* Summary:
*  Returns an 32-bit result from ADC
*
* Parameters:  
*  void
*
* Return: 
*  int32:  ADC result.
*
*******************************************************************************/
int32 `$INSTANCE_NAME`_GetResult32(void) `=ReentrantKeil($INSTANCE_NAME . "_GetResult32")`
{
    uint32 result;

    #if (CY_PSOC3)
        /* to make upper bits fo result to 0 */
        result = (int8) (0xff & `$INSTANCE_NAME`_DEC_SAMPH_REG); 
        result = (result << 8) | `$INSTANCE_NAME`_DEC_SAMPM_REG;
        result = (result << 8) | `$INSTANCE_NAME`_DEC_SAMP_REG;
    #else
        result = CY_GET_REG16(`$INSTANCE_NAME`_DEC_SAMPH_PTR);
        result = (result << 16) | (CY_GET_REG16(`$INSTANCE_NAME`_DEC_SAMP_PTR));
    #endif /* CY_PSOC3 */
    
    return result;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOffset
********************************************************************************
*
* Summary:
*  This function sets the offset for voltage readings.
*
* Parameters:  
*  int32:  offset  Offset in counts
*
* Return: 
*  void
*
* Global variables:
*  `$INSTANCE_NAME`_Offset:  Modified to set the user provided offset. This 
*  variable is used for offset calibration purpose.
*  Affects the `$INSTANCE_NAME`_CountsTo_Volts, 
*  `$INSTANCE_NAME`_CountsTo_mVolts, `$INSTANCE_NAME`_CountsTo_uVolts functions 
*  by subtracting the given offset. 
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOffset(int32 offset) `=ReentrantKeil($INSTANCE_NAME . "_SetOffset")`
{
 
    `$INSTANCE_NAME`_Offset = offset;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetGain
********************************************************************************
*
* Summary:
*  This function sets the ADC gain in counts per volt.
*
* Parameters:  
*  int32:  offset  Offset in counts
*
* Return: 
*  void 
*
* Global variables:
*  `$INSTANCE_NAME`_CountsPerVolt:  modified to set the ADC gain in counts 
*   per volt.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetGain(int32 adcGain) `=ReentrantKeil($INSTANCE_NAME . "_SetGain")`
{
 
    `$INSTANCE_NAME`_CountsPerVolt = adcGain;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_mVolts
********************************************************************************
*
* Summary:
*  This function converts ADC counts to mVolts.
*
* Parameters:  
*  int32:  adcCounts   Reading from ADC.
*
* Return: 
*  int32:  Result in mVolts
*
* Global variables:
*  `$INSTANCE_NAME`_CountsPerVolt:  used to convert ADC counts to mVolts.
*  `$INSTANCE_NAME`_Offset:  Used as the offset while converting ADC counts 
*   to mVolts.
*
*******************************************************************************/
int16 `$INSTANCE_NAME`_CountsTo_mVolts( int32 adcCounts) `=ReentrantKeil($INSTANCE_NAME . "_CountsTo_mVolts")`
{

    int32 mVolts = 0;
    int32 A, B;
	uint8 resolution = 16;

    /* Subtract ADC offset */
    adcCounts -= `$INSTANCE_NAME`_Offset;
	
	/* Set the resolution based on the configuration */
	if (`$INSTANCE_NAME`_Config == `$INSTANCE_NAME`_`$Config1_Name`)
	{
        resolution = `$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION;
	}	
	else if (`$INSTANCE_NAME`_Config == `$INSTANCE_NAME`_`$Config2_Name`)
	{
	    resolution = `$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION;
	}
	else if (`$INSTANCE_NAME`_Config == `$INSTANCE_NAME`_`$Config3_Name`)
	{
	    resolution = `$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION;
	}
	else
	{
	    resolution = `$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION;
	}
	
    if(resolution < 17)
    {
        A = 1000;
        B = 1;
    }
    else
    {
        A = 100;
        B = 10;
    }

    mVolts = ((A * adcCounts) / ((int32)`$INSTANCE_NAME`_CountsPerVolt/B)) ;   

    return( (int16)mVolts );
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_Volts
********************************************************************************
*
* Summary:
*  This function converts ADC counts to Volts
*
* Parameters:  
*  int32:  adcCounts   Reading from ADC.
*
* Return: 
*  float:  Result in Volts
*
* Global variables:
*  `$INSTANCE_NAME`_CountsPerVolt:  used to convert to Volts.
*  `$INSTANCE_NAME`_Offset:  Used as the offset while converting ADC counts 
*   to Volts.
*
*******************************************************************************/
float `$INSTANCE_NAME`_CountsTo_Volts( int32 adcCounts) `=ReentrantKeil($INSTANCE_NAME . "_CountsTo_Volts")`
{

    float Volts = 0;

    /* Subtract ADC offset */
    adcCounts -= `$INSTANCE_NAME`_Offset;

    Volts = (float)adcCounts / (float)`$INSTANCE_NAME`_CountsPerVolt;   
    
    return( Volts );
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_uVolts
********************************************************************************
*
* Summary:
*  This function converts ADC counts to uVolts
*
* Parameters:  
*  int32:  adcCounts   Reading from ADC.
*
* Return: 
*  int32:  Result in uVolts
*
* Global variables:
*  `$INSTANCE_NAME`_CountsPerVolt:  used to convert ADC counts to mVolts.
*  `$INSTANCE_NAME`_Offset:  Used as the offset while converting ADC counts 
*   to mVolts.
*
* Theory: 
* Care must be taken to not exceed the maximum value for a 32 bit signed
* number in the conversion to uVolts and at the same time not loose 
* resolution.
*
* uVolts = ((A * adcCounts) / ((int32)`$INSTANCE_NAME`_CountsPerVolt/B)) ;   
*
*  Resolution       A           B
*   8 - 11      1,000,000         1
*  12 - 14        100,000        10
*  15 - 17         10,000       100
*  18 - 20           1000      1000
*
*******************************************************************************/
int32 `$INSTANCE_NAME`_CountsTo_uVolts( int32 adcCounts) `=ReentrantKeil($INSTANCE_NAME . "_CountsTo_uVolts")`
{

    int32 uVolts = 0;
    int32 A, B;
	uint8 resolution = 16;
	
	/* Set the resolution based on the configuration */
	if (`$INSTANCE_NAME`_Config == `$INSTANCE_NAME`_`$Config1_Name`)
	{
        resolution = `$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION;
	}	
	else if (`$INSTANCE_NAME`_Config == `$INSTANCE_NAME`_`$Config2_Name`)
	{
	    resolution = `$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION;
	}
	else if (`$INSTANCE_NAME`_Config == `$INSTANCE_NAME`_`$Config3_Name`)
	{
	    resolution = `$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION;
	}
	else
	{
	    resolution = `$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION;
	}
    
    if(resolution < 12)
    {
        A = 1000000;
        B = 1;
    }
    else if(resolution < 15)
    {
        A = 100000;
        B = 10;
    }
    else if(resolution < 18)
    {
        A = 10000;
        B = 100;
    }
    else
    {
        A = 1000;
        B = 1000;
    }

    /* Subtract ADC offset */
    adcCounts -= `$INSTANCE_NAME`_Offset;

    uVolts = ((A * adcCounts) / ((int32)`$INSTANCE_NAME`_CountsPerVolt/B)) ;   
  
    return( uVolts );
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IRQ_Start(void)
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it. The IRQ_Start() API is included to 
*  support legacy code. The routine has been replaced by the library source 
*  code for interrupts. IRQ_Start() should not be used in new designs.
* 
* Parameters:  
*   void.
*
* Return:
*   void.
*
*******************************************************************************/
void `$INSTANCE_NAME`_IRQ_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_IRQ_Start")`
{
    /* For all we know the interrupt is active. */
    CyIntDisable(`$INSTANCE_NAME`_IRQ__INTC_NUMBER );

    /* Set the ISR to point to the ADC_DelSig_1_IRQ Interrupt. */
    CyIntSetVector(`$INSTANCE_NAME`_IRQ__INTC_NUMBER, `$INSTANCE_NAME`_ISR1);

    /* Set the priority. */
    CyIntSetPriority(`$INSTANCE_NAME`_IRQ__INTC_NUMBER, `$INSTANCE_NAME`_IRQ_INTC_PRIOR_NUMBER);

    /* Enable interrupt. */
    CyIntEnable(`$INSTANCE_NAME`_IRQ__INTC_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitConfig(uint8 config)
********************************************************************************
*
* Summary:
*  Initializes all registers based on customizer settings
*
* Parameters:  
*   void
*
* Return: 
*  void
*
* Global variables:
*  `$INSTANCE_NAME`_initVar:  used to set the common registers in the beginning.
*  `$INSTANCE_NAME`_CountsPerVolt:  Used to set the default counts per volt.
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitConfig(uint8 config) `=ReentrantKeil($INSTANCE_NAME . "_InitConfig")`
{
    `$INSTANCE_NAME`_stopConversion = 0u;
    
    if(`$INSTANCE_NAME`_initVar == 0u)
        {
            `$INSTANCE_NAME`_DSM_DEM0_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_DEM0;    
            `$INSTANCE_NAME`_DSM_DEM1_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_DEM1;    
            `$INSTANCE_NAME`_DSM_MISC_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_MISC;    
            `$INSTANCE_NAME`_DSM_CLK_REG    |= `$INSTANCE_NAME`_`$Config1_Name`_DSM_CLK; 
            `$INSTANCE_NAME`_DSM_REF1_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_REF1;    
        
            `$INSTANCE_NAME`_DSM_OUT0_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_OUT0;    
            `$INSTANCE_NAME`_DSM_OUT1_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_OUT1;   
        
            `$INSTANCE_NAME`_DSM_CR0_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR0;     
            `$INSTANCE_NAME`_DSM_CR1_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR1;     
            `$INSTANCE_NAME`_DSM_CR2_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR2;     
            `$INSTANCE_NAME`_DSM_CR3_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR3;     
            `$INSTANCE_NAME`_DSM_CR13_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR13;     
            
            `$INSTANCE_NAME`_DEC_SR_REG      = `$INSTANCE_NAME`_`$Config1_Name`_DEC_SR;      
            `$INSTANCE_NAME`_DEC_COHER_REG   = `$INSTANCE_NAME`_`$Config1_Name`_DEC_COHER;   
        }

    if (config == 1u)
    {
        /* `$Comment_Config1` */   
        `$INSTANCE_NAME`_DEC_CR_REG      = `$INSTANCE_NAME`_`$Config1_Name`_DEC_CR;      
        `$INSTANCE_NAME`_DEC_SHIFT1_REG  = `$INSTANCE_NAME`_`$Config1_Name`_DEC_SHIFT1;  
        `$INSTANCE_NAME`_DEC_SHIFT2_REG  = `$INSTANCE_NAME`_`$Config1_Name`_DEC_SHIFT2;  
        `$INSTANCE_NAME`_DEC_DR2_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DEC_DR2;     
        `$INSTANCE_NAME`_DEC_DR2H_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DEC_DR2H;    
        `$INSTANCE_NAME`_DEC_DR1_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DEC_DR1;     
        `$INSTANCE_NAME`_DEC_OCOR_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DEC_OCOR;    
        `$INSTANCE_NAME`_DEC_OCORM_REG   = `$INSTANCE_NAME`_`$Config1_Name`_DEC_OCORM;   
        `$INSTANCE_NAME`_DEC_OCORH_REG   = `$INSTANCE_NAME`_`$Config1_Name`_DEC_OCORH;   
        
        `$INSTANCE_NAME`_DSM_CR4_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR4;     
        `$INSTANCE_NAME`_DSM_CR5_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR5;     
        `$INSTANCE_NAME`_DSM_CR6_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR6;     
        `$INSTANCE_NAME`_DSM_CR7_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR7;     
        `$INSTANCE_NAME`_DSM_CR8_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR8;     
        `$INSTANCE_NAME`_DSM_CR9_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR9;     
        `$INSTANCE_NAME`_DSM_CR10_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR10;    
        `$INSTANCE_NAME`_DSM_CR11_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR11;    
        `$INSTANCE_NAME`_DSM_CR12_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR12;    
        `$INSTANCE_NAME`_DSM_CR14_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR14;    
        `$INSTANCE_NAME`_DSM_CR15_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR15;    
        `$INSTANCE_NAME`_DSM_CR16_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR16;    
        `$INSTANCE_NAME`_DSM_CR17_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR17;
		/* Set DSM_REF0_REG by disabling and enabling the PRESS cirucit */
		`$INSTANCE_NAME`_SetDSMRef0Reg(`$INSTANCE_NAME`_`$Config1_Name`_DSM_REF0);
        `$INSTANCE_NAME`_DSM_REF2_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_REF2;    
        `$INSTANCE_NAME`_DSM_REF3_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_REF3;    
        
        `$INSTANCE_NAME`_DSM_BUF0_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_BUF0;    
        `$INSTANCE_NAME`_DSM_BUF1_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_BUF1;    
        `$INSTANCE_NAME`_DSM_BUF2_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_BUF2;   
        `$INSTANCE_NAME`_DSM_BUF3_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_BUF3;
        #if (CY_PSOC5A)
            `$INSTANCE_NAME`_DSM_CLK_REG    |= `$INSTANCE_NAME`_`$Config1_Name`_DSM_CLK; 
        #endif /* CY_PSOC5A */
        
        /* To select either Vssa or Vref to -ve input of DSM depending on 
          the input  range selected.
        */
        
        #if(`$INSTANCE_NAME`_DEFAULT_INPUT_MODE)
            #if (CY_PSOC3 || CY_PSOC5LP)
                #if (`$INSTANCE_NAME`_`$Config1_Name`_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF)
                    `$INSTANCE_NAME`_AMux_Select(1);
                #else
                    `$INSTANCE_NAME`_AMux_Select(0);
                #endif /* `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) */
            #elif (CY_PSOC5A)
                `$INSTANCE_NAME`_AMux_Select(0);
            #endif /* CY_PSOC3 || CY_PSOC5LP */
        #endif /* `$INSTANCE_NAME`_DEFAULT_INPUT_MODE */
        
        /* Set the Conversion stop if resolution is above 16 bit and conversion 
           mode is Single sample */
        #if(`$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION > 16 && \
            `$INSTANCE_NAME`_`$Config1_Name`_CONV_MODE == `$INSTANCE_NAME`_MODE_SINGLE_SAMPLE) 
            `$INSTANCE_NAME`_stopConversion = 1;
        #endif /* Single sample with resolution above 16 bits. */
        `$INSTANCE_NAME`_CountsPerVolt = (uint32)`$INSTANCE_NAME`_`$Config1_Name`_COUNTS_PER_VOLT;
        
        /* Start and set interrupt vector */
        CyIntSetPriority(`$INSTANCE_NAME`_IRQ__INTC_NUMBER, `$INSTANCE_NAME`_IRQ_INTC_PRIOR_NUMBER);
        CyIntSetVector(`$INSTANCE_NAME`_IRQ__INTC_NUMBER, `$INSTANCE_NAME`_ISR1 );
        CyIntEnable(`$INSTANCE_NAME`_IRQ__INTC_NUMBER);
    }
    
    #if(`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 1)
        if(config == 2u)
        {
            /* `$Comment_Config2` */
            `$INSTANCE_NAME`_DEC_CR_REG      = `$INSTANCE_NAME`_`$Config2_Name`_DEC_CR;      
            `$INSTANCE_NAME`_DEC_SHIFT1_REG  = `$INSTANCE_NAME`_`$Config2_Name`_DEC_SHIFT1;  
            `$INSTANCE_NAME`_DEC_SHIFT2_REG  = `$INSTANCE_NAME`_`$Config2_Name`_DEC_SHIFT2;  
            `$INSTANCE_NAME`_DEC_DR2_REG     = `$INSTANCE_NAME`_`$Config2_Name`_DEC_DR2;     
            `$INSTANCE_NAME`_DEC_DR2H_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DEC_DR2H;    
            `$INSTANCE_NAME`_DEC_DR1_REG     = `$INSTANCE_NAME`_`$Config2_Name`_DEC_DR1;     
            `$INSTANCE_NAME`_DEC_OCOR_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DEC_OCOR;    
            `$INSTANCE_NAME`_DEC_OCORM_REG   = `$INSTANCE_NAME`_`$Config2_Name`_DEC_OCORM;   
            `$INSTANCE_NAME`_DEC_OCORH_REG   = `$INSTANCE_NAME`_`$Config2_Name`_DEC_OCORH;   
        
            `$INSTANCE_NAME`_DSM_CR4_REG     = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR4;     
            `$INSTANCE_NAME`_DSM_CR5_REG     = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR5;     
            `$INSTANCE_NAME`_DSM_CR6_REG     = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR6;     
            `$INSTANCE_NAME`_DSM_CR7_REG     = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR7;     
            `$INSTANCE_NAME`_DSM_CR8_REG     = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR8;     
            `$INSTANCE_NAME`_DSM_CR9_REG     = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR9;     
            `$INSTANCE_NAME`_DSM_CR10_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR10;    
            `$INSTANCE_NAME`_DSM_CR11_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR11;    
            `$INSTANCE_NAME`_DSM_CR12_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR12;    
            `$INSTANCE_NAME`_DSM_CR14_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR14;    
            `$INSTANCE_NAME`_DSM_CR15_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR15;    
            `$INSTANCE_NAME`_DSM_CR16_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR16;    
            `$INSTANCE_NAME`_DSM_CR17_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR17;    
			/* Set DSM_REF0_REG by disabling and enabling the PRESS cirucit */
			`$INSTANCE_NAME`_SetDSMRef0Reg(`$INSTANCE_NAME`_`$Config2_Name`_DSM_REF0);
            `$INSTANCE_NAME`_DSM_REF2_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_REF2;    
            `$INSTANCE_NAME`_DSM_REF3_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_REF3;    
        
            `$INSTANCE_NAME`_DSM_BUF0_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_BUF0;    
            `$INSTANCE_NAME`_DSM_BUF1_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_BUF1;    
            `$INSTANCE_NAME`_DSM_BUF2_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_BUF2;    
            `$INSTANCE_NAME`_DSM_BUF3_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_BUF3; 
            #if (CY_PSOC5A)
                `$INSTANCE_NAME`_DSM_CLK_REG    |= `$INSTANCE_NAME`_`$Config1_Name`_DSM_CLK; 
            #endif /* CY_PSOC5A */
            
            /* To select either Vssa or Vref to -ve input of DSM depending on 
               the input range selected.
            */
            
            #if(`$INSTANCE_NAME`_DEFAULT_INPUT_MODE)
                #if (CY_PSOC3 || CY_PSOC5LP)
                    #if (`$INSTANCE_NAME`_`$Config2_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF)
                        `$INSTANCE_NAME`_AMux_Select(1);
                    #else
                        `$INSTANCE_NAME`_AMux_Select(0);
                    #endif /* `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) */
                #elif (CY_PSOC5A)
                    `$INSTANCE_NAME`_AMux_Select(0);
                #endif /* CY_PSOC3 || CY_PSOC5LP */
            #endif /* `$INSTANCE_NAME`_DEFAULT_INPUT_MODE */
            
            /* Set the Conversion stop if resolution is above 16 bit and 
               conversion mode is Single sample */
            #if(`$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION > 16 && \
                `$INSTANCE_NAME`_`$Config2_Name`_CONVMODE == `$INSTANCE_NAME`_MODE_SINGLE_SAMPLE) 
                `$INSTANCE_NAME`_stopConversion = 1;
            #endif /* Single sample with resolution above 16 bits. */
            
            `$INSTANCE_NAME`_CountsPerVolt = (uint32)`$INSTANCE_NAME`_`$Config2_Name`_COUNTS_PER_VOLT;
            
            /* Start and set interrupt vector */
            CyIntSetPriority(`$INSTANCE_NAME`_IRQ__INTC_NUMBER, `$INSTANCE_NAME`_IRQ_INTC_PRIOR_NUMBER);
            CyIntSetVector(`$INSTANCE_NAME`_IRQ__INTC_NUMBER, `$INSTANCE_NAME`_ISR2 );
            CyIntEnable(`$INSTANCE_NAME`_IRQ__INTC_NUMBER);
        }
    #endif /* `$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 1 */

    #if(`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 2)
        if(config == 3u)
        {
            /* `$Comment_Config3` */
            `$INSTANCE_NAME`_DEC_CR_REG      = `$INSTANCE_NAME`_`$Config3_Name`_DEC_CR;      
            `$INSTANCE_NAME`_DEC_SHIFT1_REG  = `$INSTANCE_NAME`_`$Config3_Name`_DEC_SHIFT1;  
            `$INSTANCE_NAME`_DEC_SHIFT2_REG  = `$INSTANCE_NAME`_`$Config3_Name`_DEC_SHIFT2;  
            `$INSTANCE_NAME`_DEC_DR2_REG     = `$INSTANCE_NAME`_`$Config3_Name`_DEC_DR2;     
            `$INSTANCE_NAME`_DEC_DR2H_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DEC_DR2H;    
            `$INSTANCE_NAME`_DEC_DR1_REG     = `$INSTANCE_NAME`_`$Config3_Name`_DEC_DR1;     
            `$INSTANCE_NAME`_DEC_OCOR_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DEC_OCOR;    
            `$INSTANCE_NAME`_DEC_OCORM_REG   = `$INSTANCE_NAME`_`$Config3_Name`_DEC_OCORM;   
            `$INSTANCE_NAME`_DEC_OCORH_REG   = `$INSTANCE_NAME`_`$Config3_Name`_DEC_OCORH;   
         
            `$INSTANCE_NAME`_DSM_CR4_REG     = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR4;     
            `$INSTANCE_NAME`_DSM_CR5_REG     = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR5;     
            `$INSTANCE_NAME`_DSM_CR6_REG     = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR6;     
            `$INSTANCE_NAME`_DSM_CR7_REG     = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR7;     
            `$INSTANCE_NAME`_DSM_CR8_REG     = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR8;     
            `$INSTANCE_NAME`_DSM_CR9_REG     = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR9;     
            `$INSTANCE_NAME`_DSM_CR10_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR10;    
            `$INSTANCE_NAME`_DSM_CR11_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR11;    
            `$INSTANCE_NAME`_DSM_CR12_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR12;    
            `$INSTANCE_NAME`_DSM_CR14_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR14;    
            `$INSTANCE_NAME`_DSM_CR15_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR15;    
            `$INSTANCE_NAME`_DSM_CR16_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR16;    
            `$INSTANCE_NAME`_DSM_CR17_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR17;    
			/* Set DSM_REF0_REG by disabling and enabling the PRESS cirucit */
			`$INSTANCE_NAME`_SetDSMRef0Reg(`$INSTANCE_NAME`_`$Config3_Name`_DSM_REF0);
            `$INSTANCE_NAME`_DSM_REF2_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_REF2;    
            `$INSTANCE_NAME`_DSM_REF3_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_REF3;    
        
            `$INSTANCE_NAME`_DSM_BUF0_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_BUF0;    
            `$INSTANCE_NAME`_DSM_BUF1_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_BUF1;    
            `$INSTANCE_NAME`_DSM_BUF2_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_BUF2;
            `$INSTANCE_NAME`_DSM_BUF3_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_BUF3;
            #if (CY_PSOC5A)
                `$INSTANCE_NAME`_DSM_CLK_REG    |= `$INSTANCE_NAME`_`$Config1_Name`_DSM_CLK; 
            #endif /* CY_PSOC5A */
            
            /* To select either Vssa or Vref to -ve input of DSM depending on 
               the input range selected.
            */
            
            #if(`$INSTANCE_NAME`_DEFAULT_INPUT_MODE)
                #if (CY_PSOC3 || CY_PSOC5LP)
                    #if (`$INSTANCE_NAME`_`$Config3_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF)
                        `$INSTANCE_NAME`_AMux_Select(1);
                    #else
                        `$INSTANCE_NAME`_AMux_Select(0);
                    #endif /* `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) */
                #elif (CY_PSOC5A)
                    `$INSTANCE_NAME`_AMux_Select(0);
                #endif /* CY_PSOC3 || CY_PSOC5LP */
            #endif /* `$INSTANCE_NAME`_DEFAULT_INPUT_MODE */
                       
            /* Set the Conversion stop if resolution is above 16 bit and 
               conversion  mode is Single sample */
            #if(`$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION > 16 && \
                `$INSTANCE_NAME`_`$Config3_Name`_CONVMODE == `$INSTANCE_NAME`_MODE_SINGLE_SAMPLE) 
                `$INSTANCE_NAME`_stopConversion = 1;
            #endif /* Single sample with resolution above 16 bits */
            
            `$INSTANCE_NAME`_CountsPerVolt = (uint32)`$INSTANCE_NAME`_`$Config3_Name`_COUNTS_PER_VOLT;
            
            /* Start and set interrupt vector */
            CyIntSetPriority(`$INSTANCE_NAME`_IRQ__INTC_NUMBER, `$INSTANCE_NAME`_IRQ_INTC_PRIOR_NUMBER);
            CyIntSetVector(`$INSTANCE_NAME`_IRQ__INTC_NUMBER, `$INSTANCE_NAME`_ISR3 );
            CyIntEnable(`$INSTANCE_NAME`_IRQ__INTC_NUMBER);
        }
    #endif /* `$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 3 */

    #if(`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS == 4)
        if (config == 4u)
        {
            /* `$Comment_Config4` */
            `$INSTANCE_NAME`_DEC_CR_REG      = `$INSTANCE_NAME`_`$Config4_Name`_DEC_CR;      
            `$INSTANCE_NAME`_DEC_SHIFT1_REG  = `$INSTANCE_NAME`_`$Config4_Name`_DEC_SHIFT1;  
            `$INSTANCE_NAME`_DEC_SHIFT2_REG  = `$INSTANCE_NAME`_`$Config4_Name`_DEC_SHIFT2;  
            `$INSTANCE_NAME`_DEC_DR2_REG     = `$INSTANCE_NAME`_`$Config4_Name`_DEC_DR2;     
            `$INSTANCE_NAME`_DEC_DR2H_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DEC_DR2H;    
            `$INSTANCE_NAME`_DEC_DR1_REG     = `$INSTANCE_NAME`_`$Config4_Name`_DEC_DR1;     
            `$INSTANCE_NAME`_DEC_OCOR_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DEC_OCOR;    
            `$INSTANCE_NAME`_DEC_OCORM_REG   = `$INSTANCE_NAME`_`$Config4_Name`_DEC_OCORM;   
            `$INSTANCE_NAME`_DEC_OCORH_REG   = `$INSTANCE_NAME`_`$Config4_Name`_DEC_OCORH;   

            `$INSTANCE_NAME`_DSM_CR4_REG     = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR4;     
            `$INSTANCE_NAME`_DSM_CR5_REG     = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR5;     
            `$INSTANCE_NAME`_DSM_CR6_REG     = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR6;     
            `$INSTANCE_NAME`_DSM_CR7_REG     = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR7;     
            `$INSTANCE_NAME`_DSM_CR8_REG     = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR8;     
            `$INSTANCE_NAME`_DSM_CR9_REG     = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR9;     
            `$INSTANCE_NAME`_DSM_CR10_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR10;    
            `$INSTANCE_NAME`_DSM_CR11_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR11;    
            `$INSTANCE_NAME`_DSM_CR12_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR12;    
            `$INSTANCE_NAME`_DSM_CR14_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR14;    
            `$INSTANCE_NAME`_DSM_CR15_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR15;    
            `$INSTANCE_NAME`_DSM_CR16_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR16;    
            `$INSTANCE_NAME`_DSM_CR17_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR17;
			/* Set DSM_REF0_REG by disabling and enabling the PRESS cirucit */
			`$INSTANCE_NAME`_SetDSMRef0Reg(`$INSTANCE_NAME`_`$Config4_Name`_DSM_REF0);
            `$INSTANCE_NAME`_DSM_REF2_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_REF2;    
            `$INSTANCE_NAME`_DSM_REF3_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_REF3;    
        
            `$INSTANCE_NAME`_DSM_BUF0_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_BUF0;    
            `$INSTANCE_NAME`_DSM_BUF1_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_BUF1;    
            `$INSTANCE_NAME`_DSM_BUF2_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_BUF2;
            `$INSTANCE_NAME`_DSM_BUF3_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_BUF3;
            #if (CY_PSOC5A)
                `$INSTANCE_NAME`_DSM_CLK_REG    |= `$INSTANCE_NAME`_`$Config1_Name`_DSM_CLK; 
            #endif /* CY_PSOC5A */
            
            /* To select either Vssa or Vref to -ve input of DSM depending on 
               the input range selected.
            */
            
            #if(`$INSTANCE_NAME`_DEFAULT_INPUT_MODE)
                #if (CY_PSOC3 || CY_PSOC5LP)
                    #if (`$INSTANCE_NAME`_`$Config4_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF)
                        `$INSTANCE_NAME`_AMux_Select(1);
                    #else
                        `$INSTANCE_NAME`_AMux_Select(0);
                    #endif /* `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) */
                #elif (CY_PSOC5A)
                    `$INSTANCE_NAME`_AMux_Select(0);
                #endif /* CY_PSOC3 || CY_PSOC5LP */
            #endif /* `$INSTANCE_NAME`_DEFAULT_INPUT_MODE */
                       
            /* Set the Conversion stop if resolution is above 16 bit and 
               conversion mode is Single sample */
            #if(`$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION > 16 && \
                `$INSTANCE_NAME`_`$Config4_Name`_CONVMODE == `$INSTANCE_NAME`_MODE_SINGLE_SAMPLE) 
                `$INSTANCE_NAME`_stopConversion = 1;
            #endif /* Single sample with resolution above 16 bits */
            
            `$INSTANCE_NAME`_CountsPerVolt = (uint32)`$INSTANCE_NAME`_`$Config4_Name`_COUNTS_PER_VOLT;

            /* Start and set interrupt vector */
            CyIntSetPriority(`$INSTANCE_NAME`_IRQ__INTC_NUMBER, `$INSTANCE_NAME`_IRQ_INTC_PRIOR_NUMBER);
            CyIntSetVector(`$INSTANCE_NAME`_IRQ__INTC_NUMBER, `$INSTANCE_NAME`_ISR4 );
            CyIntEnable(`$INSTANCE_NAME`_IRQ__INTC_NUMBER);
        }
    #endif /* `$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 4 */
	
	// KEES enable the modbit
	// clear the mx_modbitin field
	`$INSTANCE_NAME`_DSM_CR3_REG &= ~`$INSTANCE_NAME`_DSM_MODBITIN_MASK;
	// enable the modbit input (ES2 has DSM_MODBIT), select UDB as modbit source
	`$INSTANCE_NAME`_DSM_CR3_REG |= `$INSTANCE_NAME`_DSM_MODBIT_EN | `$INSTANCE_NAME`_DSM_MODBIT | `$INSTANCE_NAME`_DSM_MODBITIN_UDB;
	
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RoundValue(uint32 busClockFreq, 
*                                            uint32 clockFreq)
********************************************************************************
*
* Summary:
*  Function to round an integer value.
*
* Parameters:  
*  busClockFreq:  Frequency of the bus clock.
*  clockFreq:  Frequency of the component clock.
*
* Return: 
*  uint16: rounded integer value.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_RoundValue(uint32 busClockFreq, uint32 clockFreq) \
                                  `=ReentrantKeil($INSTANCE_NAME . "_RoundValue")`
{
    uint16 divider1, divider2;
    
    divider1 = ((busClockFreq * 10) / clockFreq);
    divider2 = (busClockFreq / clockFreq);
    if ( divider1 - (divider2 * 10) >= 5)
    {
        divider2 += 1;
    }
    return divider2;
}
         

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SelectCofiguration(uint8 config, 
*                                                    uint8 restart)
********************************************************************************
*
* Summary:
*  Selects the user defined configuration. This API first stops the current ADC
*  and then initializes the registers with the default values for that config. 
*  This also performs calibration by writing GCOR registers with trim values 
*  stored in the flash.
*
* Parameters:  
*  config:  configuration user wants to select.
*
* Return: 
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_SelectConfiguration(uint8 config, uint8 restart) \
                                              `=ReentrantKeil($INSTANCE_NAME . "_SelectConfiguration")`
{
    uint8 inputRange = 0, resolution = 16;
    uint16 idealGain = 0, adcClockDivider = 1;    
    uint16 cpClockDivider = 1;
    uint16 idealOddGain = 0;
    
    /* Check whether the config is valid or not */
    if( config <= `$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS)
    {   
       /* Set the flag to ensure start() API dont override the config
           selected if ADC is not already started */
        if(`$INSTANCE_NAME`_initVar == 0u)
        {
            `$INSTANCE_NAME`_started = 1u;
        }
		
		/* Update the config flag */
		`$INSTANCE_NAME`_Config = config;
       
        /* Stop the ADC  */
        `$INSTANCE_NAME`_Stop();
        
        #if (CY_PSOC5A)
            /* Set the structure field which checks whether or not to
               restore the power registers */
            `$INSTANCE_NAME`_powerModeBackup.bypassRestore = `$INSTANCE_NAME`_BYPASS_ENABLED;
        #endif /* CY_PSOC5A */
        
        /* Set the  ADC registers based on the configuration */
        `$INSTANCE_NAME`_InitConfig(config);
        
        /* Trim value calculation */
        if(config == 1u)
        {
            inputRange = `$INSTANCE_NAME`_`$Config1_Name`_RANGE;
            resolution = `$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION;
            idealGain = `$INSTANCE_NAME`_`$Config1_Name`_IDEAL_DEC_GAIN;
            idealOddGain = `$INSTANCE_NAME`_`$Config1_Name`_IDEAL_ODDDEC_GAIN;
            adcClockDivider = `$INSTANCE_NAME`_RoundValue((uint32)BCLK__BUS_CLK__HZ,
                                                       (uint32)`$INSTANCE_NAME`_`$Config1_Name`_CLOCK_FREQ);
            cpClockDivider = `$INSTANCE_NAME`_RoundValue((uint32)BCLK__BUS_CLK__HZ,
                                                       (uint32)`$INSTANCE_NAME`_`$Config1_Name`_CP_CLOCK_FREQ);
        }

        #if (`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 1)
            if(config == 2u)
            {
                inputRange = `$INSTANCE_NAME`_`$Config2_Name`_INPUT_RANGE;
                resolution = `$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION;
                idealGain = `$INSTANCE_NAME`_`$Config2_Name`_IDEAL_DEC_GAIN;
                idealOddGain = `$INSTANCE_NAME`_`$Config2_Name`_IDEAL_ODDDEC_GAIN;
                adcClockDivider = `$INSTANCE_NAME`_RoundValue((uint32)BCLK__BUS_CLK__HZ,
                                                            (uint32)`$INSTANCE_NAME`_`$Config2_Name`_CLOCK_FREQ);
                cpClockDivider = `$INSTANCE_NAME`_RoundValue((uint32)BCLK__BUS_CLK__HZ,
                                                       (uint32)`$INSTANCE_NAME`_`$Config2_Name`_CP_CLOCK_FREQ);
            }
        #endif /* `$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 1 */

        #if(`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 2)
            if(config == 3u)
            {
                inputRange = `$INSTANCE_NAME`_`$Config3_Name`_INPUT_RANGE;
                resolution = `$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION;
                idealGain = `$INSTANCE_NAME`_`$Config3_Name`_IDEAL_DEC_GAIN;
                idealOddGain = `$INSTANCE_NAME`_`$Config3_Name`_IDEAL_ODDDEC_GAIN;
                adcClockDivider = `$INSTANCE_NAME`_RoundValue((uint32)BCLK__BUS_CLK__HZ,
                                                            (uint32)`$INSTANCE_NAME`_`$Config3_Name`_CLOCK_FREQ);
                cpClockDivider = `$INSTANCE_NAME`_RoundValue((uint32)BCLK__BUS_CLK__HZ,
                                                       (uint32)`$INSTANCE_NAME`_`$Config3_Name`_CP_CLOCK_FREQ);
            }
        #endif /* `$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 2 */

        #if (`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 3)
            if(config == 4u)
            {
                inputRange = `$INSTANCE_NAME`_`$Config4_Name`_INPUT_RANGE;
                resolution = `$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION;
                idealGain = `$INSTANCE_NAME`_`$Config4_Name`_IDEAL_DEC_GAIN;
                idealOddGain = `$INSTANCE_NAME`_`$Config4_Name`_IDEAL_ODDDEC_GAIN;
                adcClockDivider = `$INSTANCE_NAME`_RoundValue((uint32)BCLK__BUS_CLK__HZ,  
                                                            (uint32)`$INSTANCE_NAME`_`$Config4_Name`_CLOCK_FREQ);
                cpClockDivider = `$INSTANCE_NAME`_RoundValue((uint32)BCLK__BUS_CLK__HZ,
                                                       (uint32)`$INSTANCE_NAME`_`$Config4_Name`_CP_CLOCK_FREQ);
            }
        #endif /* `$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 3 */
        
        adcClockDivider = adcClockDivider - 1;
        /* Set the proper divider for the internal clock */
        #if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
            `$INSTANCE_NAME`_theACLK_SetDividerRegister(adcClockDivider, 1);
        #endif /* `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */
        
        cpClockDivider = cpClockDivider - 1;
        /* Set the proper divider for the Charge pump clock */
        `$INSTANCE_NAME`_Ext_CP_Clk_SetDividerRegister(cpClockDivider, 1);
        
        /* Compensate the gain */
        `$INSTANCE_NAME`_GainCompensation(inputRange, idealGain, idealOddGain, resolution);
        
        if(restart == 1u)
        {        
            /* Restart the ADC */
            `$INSTANCE_NAME`_Start();
            
            /* Code to disable the REFBUF0 if reference chosen is External ref */
            #if (((`$INSTANCE_NAME`_`$Config2_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P03) || \
                 (`$INSTANCE_NAME`_`$Config2_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P32)) || \
                 ((`$INSTANCE_NAME`_`$Config3_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P03) || \
                 (`$INSTANCE_NAME`_`$Config3_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P32)) || \
                 ((`$INSTANCE_NAME`_`$Config4_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P03) || \
                 (`$INSTANCE_NAME`_`$Config4_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P32)))
                if (((config == 2) && 
                    ((`$INSTANCE_NAME`_`$Config2_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P03) ||
                    (`$INSTANCE_NAME`_`$Config2_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P32))) ||
                    ((config == 3) && 
                    ((`$INSTANCE_NAME`_`$Config3_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P03) ||
                    (`$INSTANCE_NAME`_`$Config3_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P32))) ||
                    ((config == 4) && 
                    ((`$INSTANCE_NAME`_`$Config4_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P03) ||
                    (`$INSTANCE_NAME`_`$Config4_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P32))))
                {
                    /* Disable PRES, Enable power to VCMBUF0, REFBUF0 and 
                       REFBUF1, enable PRES */
                    #if (CY_PSOC3 || CY_PSOC5LP)
                        `$INSTANCE_NAME`_RESET_CR4_REG |= `$INSTANCE_NAME`_IGNORE_PRESA1;
                        `$INSTANCE_NAME`_RESET_CR5_REG |= `$INSTANCE_NAME`_IGNORE_PRESA2;
                    #elif (CY_PSOC5A)
                        `$INSTANCE_NAME`_RESET_CR1_REG |= `$INSTANCE_NAME`_DIS_PRES1;
                        `$INSTANCE_NAME`_RESET_CR3_REG |= `$INSTANCE_NAME`_DIS_PRES2;
                    #endif /* CY_PSOC5A */
        
                    /* Disable the REFBUF0 */
                    `$INSTANCE_NAME`_DSM_CR17_REG &= ~`$INSTANCE_NAME`_DSM_EN_BUF_VREF;
                    
                    /* Wait for 3 microseconds */
                    CyDelayUs(3);
                    /* Enable the press circuit */
                    #if (CY_PSOC3 || CY_PSOC5LP)
                        `$INSTANCE_NAME`_RESET_CR4_REG &= ~`$INSTANCE_NAME`_IGNORE_PRESA1;
                        `$INSTANCE_NAME`_RESET_CR5_REG &= ~`$INSTANCE_NAME`_IGNORE_PRESA2;
                    #elif (CY_PSOC5A)
                        `$INSTANCE_NAME`_RESET_CR1_REG &= ~`$INSTANCE_NAME`_DIS_PRES1;
                        `$INSTANCE_NAME`_RESET_CR3_REG &= ~`$INSTANCE_NAME`_DIS_PRES2;
                    #endif /* CY_PSOC5A */
                }
            #endif /* */
            
            #if ((CY_PSOC3 || CY_PSOC5LP) && \
                 ((`$INSTANCE_NAME`_`$Config2_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) || \
                  (`$INSTANCE_NAME`_`$Config3_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) || \
                  (`$INSTANCE_NAME`_`$Config4_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF)))
                if(((config == 2) && 
                    (`$INSTANCE_NAME`_`$Config2_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) && 
                    ((`$INSTANCE_NAME`_`$Config2_Name`_REFERENCE != `$INSTANCE_NAME`_EXT_REF_ON_P03) && 
                     (`$INSTANCE_NAME`_`$Config2_Name`_REFERENCE != `$INSTANCE_NAME`_EXT_REF_ON_P32))) ||
                     ((config == 3) && 
                      (`$INSTANCE_NAME`_`$Config3_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) && 
                     ((`$INSTANCE_NAME`_`$Config3_Name`_REFERENCE != `$INSTANCE_NAME`_EXT_REF_ON_P03) && 
                     (`$INSTANCE_NAME`_`$Config3_Name`_REFERENCE != `$INSTANCE_NAME`_EXT_REF_ON_P32))) ||
                     ((config == 4) && 
                      (`$INSTANCE_NAME`_`$Config4_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) && 
                     ((`$INSTANCE_NAME`_`$Config4_Name`_REFERENCE != `$INSTANCE_NAME`_EXT_REF_ON_P03) && 
                     (`$INSTANCE_NAME`_`$Config4_Name`_REFERENCE != `$INSTANCE_NAME`_EXT_REF_ON_P32))))
                {
                    /* Disable PRES, Enable power to VCMBUF0, REFBUF0 and 
                       REFBUF1, enable PRES */
                    #if (CY_PSOC3 || CY_PSOC5LP)
                        `$INSTANCE_NAME`_RESET_CR4_REG |= `$INSTANCE_NAME`_IGNORE_PRESA1;
                        `$INSTANCE_NAME`_RESET_CR5_REG |= `$INSTANCE_NAME`_IGNORE_PRESA2;
                    #elif (CY_PSOC5A)
                        `$INSTANCE_NAME`_RESET_CR1_REG |= `$INSTANCE_NAME`_DIS_PRES1;
                        `$INSTANCE_NAME`_RESET_CR3_REG |= `$INSTANCE_NAME`_DIS_PRES2;
                    #endif /* CY_PSOC5A */
        
                    /* Enable the REFBUF1 */
                    `$INSTANCE_NAME`_DSM_REF0_REG |= `$INSTANCE_NAME`_DSM_EN_BUF_VREF_INN;
                    
                    /* Wait for 3 microseconds */
                    CyDelayUs(3);
                    /* Enable the press circuit */
                    #if (CY_PSOC3 || CY_PSOC5LP)
                        `$INSTANCE_NAME`_RESET_CR4_REG &= ~`$INSTANCE_NAME`_IGNORE_PRESA1;
                        `$INSTANCE_NAME`_RESET_CR5_REG &= ~`$INSTANCE_NAME`_IGNORE_PRESA2;
                    #elif (CY_PSOC5A)
                        `$INSTANCE_NAME`_RESET_CR1_REG &= ~`$INSTANCE_NAME`_DIS_PRES1;
                        `$INSTANCE_NAME`_RESET_CR3_REG &= ~`$INSTANCE_NAME`_DIS_PRES2;
                    #endif /* CY_PSOC5A */
                }
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
            /* Restart the ADC conversion */
            `$INSTANCE_NAME`_StartConvert();
        }
    }
}     


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GainCompensation(uint8, uint16, uint16, uint8)
********************************************************************************
*
* Summary:
*  This API calculates the trim value and then loads this to GCOR register.
*
* Parameters:  
*  inputRange:  input range for which trim value is to be calculated.
*  IdealDecGain:  Ideal Decimator gain for the selected resolution and 
*                 conversion  mode.
*  IdealOddDecGain:  Ideal odd decimation gain for the selected resolution and 
                     conversion mode.
*  resolution:  Resolution to select the proper flash location for trim value.
*
* Return: 
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_GainCompensation(uint8 inputRange, uint16 IdealDecGain, uint16 IdealOddDecGain,  \
                                       uint8 resolution) `=ReentrantKeil($INSTANCE_NAME . "_GainCompensation")`
{
    int8 flash;
    int16 Normalised;
    uint16 GcorValue;
    uint32 GcorTmp;
    
    switch(inputRange)
    {         
        case `$INSTANCE_NAME`_IR_VNEG_VREF_DIFF:
        
        /* Normalize the flash Value */
        if(resolution > 15)
        {
            flash = `$INSTANCE_NAME`_DEC_TRIM_VREF_DIFF_16_20; 
        }    
        else
        {
            flash = `$INSTANCE_NAME`_DEC_TRIM_VREF_DIFF_8_15;
        }        
        break;
        
        case `$INSTANCE_NAME`_IR_VNEG_VREF_2_DIFF:
        
        /* Normalize the flash Value */
        if(resolution > 15)
        {
            flash = `$INSTANCE_NAME`_DEC_TRIM_VREF_2_DIFF_16_20;
        }    
        else
        {
            flash = `$INSTANCE_NAME`_DEC_TRIM_VREF_2_DIFF_8_15;
        }    
        break;
        
        case `$INSTANCE_NAME`_IR_VNEG_VREF_4_DIFF:
        
        /* Normalize the flash Value */
        if(resolution > 15)
        {
            flash = `$INSTANCE_NAME`_DEC_TRIM_VREF_4_DIFF_16_20;
        }    
        else
        {
            flash = `$INSTANCE_NAME`_DEC_TRIM_VREF_4_DIFF_8_15;
        }    
        break;
        
        case `$INSTANCE_NAME`_IR_VNEG_VREF_16_DIFF:
        
        /* Normalize the flash Value */
        if(resolution > 15)
        {
            flash = `$INSTANCE_NAME`_DEC_TRIM_VREF_16_DIFF_16_20;
        }    
        else
        {
            flash = `$INSTANCE_NAME`_DEC_TRIM_VREF_16_DIFF_8_15;
        }    
        break;
        
        default:
            flash = 0;
        break;
    }    
    if(inputRange == `$INSTANCE_NAME`_IR_VSSA_TO_VREF || inputRange == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF || 
       inputRange == `$INSTANCE_NAME`_IR_VSSA_TO_VDDA || inputRange == `$INSTANCE_NAME`_IR_VSSA_TO_6VREF || 
       inputRange == `$INSTANCE_NAME`_IR_VNEG_2VREF_DIFF || inputRange == `$INSTANCE_NAME`_IR_VNEG_6VREF_DIFF ||
       inputRange == `$INSTANCE_NAME`_IR_VNEG_VREF_8_DIFF)
    {
        Normalised  = 0;
    }
    else
    {
        Normalised  = ((int16)flash) * 32;
    }
                    
    /* Add two values */
    GcorValue = IdealDecGain + Normalised;  
    GcorTmp = (uint32)GcorValue * (uint32)IdealOddDecGain;
    GcorValue = (uint16)(GcorTmp / `$INSTANCE_NAME`_IDEAL_GAIN_CONST);
        
    if (resolution < 14)
    {
        GcorValue = (GcorValue >> (15 - (resolution + 1)));
        `$INSTANCE_NAME`_DEC_GVAL_REG = (resolution + 1);
    }
    else
    {
        /* Use all 16 bits */
        `$INSTANCE_NAME`_DEC_GVAL_REG = 15u;  
    }
      
    /* Load the gain correction register */    
    `$INSTANCE_NAME`_DEC_GCOR_REG  = (uint8)GcorValue;
    `$INSTANCE_NAME`_DEC_GCORH_REG = (uint8)(GcorValue >> 8);    
    
    /* Workaround for 0 to 2*Vref mode with PSoC5A siliocn */
    #if( CY_PSOC5A) 
        if( inputRange == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF)
        {
            `$INSTANCE_NAME`_DEC_GCOR_REG = 0x00u;
            `$INSTANCE_NAME`_DEC_GCORH_REG = 0x00u;
            `$INSTANCE_NAME`_DEC_GVAL_REG = 0x00u;
        }
    #endif /* CY_PSOC5A */
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDSMRef0Reg(uint8)
******************************************************************************
*
* Summary:
*  This API sets the DSM_REF0 register. This is written for internal use.
*
* Parameters:  
*  value:  Value to be written to DSM_REF0 register.
*
* Return: 
*  void
*
******************************************************************************/
void `$INSTANCE_NAME`_SetDSMRef0Reg(uint8 value) `=ReentrantKeil($INSTANCE_NAME . "_SetDSMRef0Reg")`
{
    /* Disable PRES, Enable power to VCMBUF0, REFBUF0 and REFBUF1, enable 
       PRES */
    #if (CY_PSOC3 || CY_PSOC5LP)
        `$INSTANCE_NAME`_RESET_CR4_REG |= (`$INSTANCE_NAME`_IGNORE_PRESA1 | `$INSTANCE_NAME`_IGNORE_PRESD1);
        `$INSTANCE_NAME`_RESET_CR5_REG |= (`$INSTANCE_NAME`_IGNORE_PRESA2 | `$INSTANCE_NAME`_IGNORE_PRESD2);
    #elif (CY_PSOC5A)
        `$INSTANCE_NAME`_RESET_CR1_REG |= `$INSTANCE_NAME`_DIS_PRES1;
        `$INSTANCE_NAME`_RESET_CR3_REG |= `$INSTANCE_NAME`_DIS_PRES2;
    #endif /* CY_PSOC5A */
        `$INSTANCE_NAME`_DSM_REF0_REG = value;   
		
	/* Wait for 3 microseconds */
    CyDelayUs(3);
    /* Enable the press circuit */
    #if (CY_PSOC3 || CY_PSOC5LP)
        `$INSTANCE_NAME`_RESET_CR4_REG &= ~(`$INSTANCE_NAME`_IGNORE_PRESA1 | `$INSTANCE_NAME`_IGNORE_PRESD1);
        `$INSTANCE_NAME`_RESET_CR5_REG &= ~(`$INSTANCE_NAME`_IGNORE_PRESA2 | `$INSTANCE_NAME`_IGNORE_PRESD2);
    #elif (CY_PSOC5A)
        `$INSTANCE_NAME`_RESET_CR1_REG &= ~`$INSTANCE_NAME`_DIS_PRES1;
        `$INSTANCE_NAME`_RESET_CR3_REG &= ~`$INSTANCE_NAME`_DIS_PRES2;
    #endif /* CY_PSOC5A */
}


/* [] END OF FILE */
