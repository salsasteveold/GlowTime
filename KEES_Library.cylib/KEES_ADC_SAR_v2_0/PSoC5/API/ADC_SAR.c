/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the Successive
*  approximation ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include "`$INSTANCE_NAME`.h"

#if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
    #include "`$INSTANCE_NAME`_theACLK.h"
#endif /* End `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */


/***************************************
* Forward function references
***************************************/
static void `$INSTANCE_NAME`_CalcGain(uint8 resolution);


/***************************************
* Global data allocation
***************************************/
uint8 `$INSTANCE_NAME`_initVar = 0u;
volatile int16 `$INSTANCE_NAME`_offset;
volatile int16 `$INSTANCE_NAME`_countsPerVolt;   /* Gain compensation */
volatile int16 `$INSTANCE_NAME`_shift;


/***************************************
* Local data allocation
***************************************/
#if(CY_PSOC5A)
    static uint8 `$INSTANCE_NAME`_resolution;
#endif /* End CY_PSOC5A */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Performs all required initialization for this component and enables the
*  power.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The `$INSTANCE_NAME`_initVar variable is used to indicate when/if initial
*  configuration of this component has happened. The variable is initialized to
*  zero and set to 1 the first time ADC_Start() is called. This allows for
*  component Re-Start without re-initialization in all subsequent calls to the
*  `$INSTANCE_NAME`_Start() routine.
*  If re-initialization of the component is required the variable should be set
*  to zero before call of `$INSTANCE_NAME`_Start() routine, or the user may call
*  `$INSTANCE_NAME`_Init() and `$INSTANCE_NAME`_Enable() as done in the
*  `$INSTANCE_NAME`_Start() routine.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{

    /* If not Initialized then initialize all required hardware and software */
    if(`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  `$INSTANCE_NAME`_Start().
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The `$INSTANCE_NAME`_offset variable is initialized to 0.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{

    /* This is only valid if there is an internal clock */
    #if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
        `$INSTANCE_NAME`_theACLK_SetMode(CYCLK_DUTY);
    #endif /* End `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */

    #if(`$INSTANCE_NAME`_IRQ_REMOVE == 0u)
        /* Start and set interrupt vector */
        CyIntSetPriority(`$INSTANCE_NAME`_INTC_NUMBER, `$INSTANCE_NAME`_INTC_PRIOR_NUMBER);
        (void)CyIntSetVector(`$INSTANCE_NAME`_INTC_NUMBER, &`$INSTANCE_NAME`_ISR);
    #endif   /* End `$INSTANCE_NAME`_IRQ_REMOVE */        

    /* Enable IRQ mode*/
    `$INSTANCE_NAME`_SAR_CSR1_REG |= `$INSTANCE_NAME`_SAR_IRQ_MASK_EN | `$INSTANCE_NAME`_SAR_IRQ_MODE_EDGE;

    /*Set SAR ADC resolution ADC */
    `$INSTANCE_NAME`_SetResolution(`$INSTANCE_NAME`_DEFAULT_RESOLUTION);
    `$INSTANCE_NAME`_offset = 0;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables the reference, clock and power for SAR ADC.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
    uint8 tmpReg;
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Enable the SAR ADC block in Active Power Mode */
    `$INSTANCE_NAME`_PWRMGR_SAR_REG |= `$INSTANCE_NAME`_ACT_PWR_SAR_EN;

     /* Enable the SAR ADC in Standby Power Mode*/
    `$INSTANCE_NAME`_STBY_PWRMGR_SAR_REG |= `$INSTANCE_NAME`_STBY_PWR_SAR_EN;

    /* This is only valid if there is an internal clock */
    #if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
        `$INSTANCE_NAME`_PWRMGR_CLK_REG |= `$INSTANCE_NAME`_ACT_PWR_CLK_EN;
        `$INSTANCE_NAME`_STBY_PWRMGR_CLK_REG |= `$INSTANCE_NAME`_STBY_PWR_CLK_EN;
    #endif /* End `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */

    /* Enable VCM buffer and Enable Int Ref Amp */
    tmpReg = `$INSTANCE_NAME`_SAR_CSR3_REG;
    #if(CY_PSOC5A) /* Make sure that full power is applied for VREF buffer */
        tmpReg &= (uint8)~`$INSTANCE_NAME`_SAR_PWR_CTRL_VREF_DIV_BY4;
    #endif /* CY_PSOC5A */
    tmpReg |= `$INSTANCE_NAME`_SAR_EN_BUF_VCM_EN;
    /* PD_BUF_VREF is OFF in External reference or Vdda reference mode */
    #if((`$INSTANCE_NAME`_DEFAULT_REFERENCE == `$INSTANCE_NAME`__EXT_REF) || \
        (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VNEG_VDDA_DIFF))
        tmpReg &= (uint8)~`$INSTANCE_NAME`_SAR_EN_BUF_VREF_EN;
    #else /* In INTREF or INTREF Bypassed this buffer is ON */
        tmpReg |= `$INSTANCE_NAME`_SAR_EN_BUF_VREF_EN;
    #endif /* `$INSTANCE_NAME`_DEFAULT_REFERENCE == `$INSTANCE_NAME`__EXT_REF */
    `$INSTANCE_NAME`_SAR_CSR3_REG = tmpReg;

    /* Set reference for ADC */
    #if(`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VNEG_VDDA_DIFF)
        #if(`$INSTANCE_NAME`_DEFAULT_REFERENCE == `$INSTANCE_NAME`__EXT_REF)
            `$INSTANCE_NAME`_SAR_CSR6_REG = `$INSTANCE_NAME`_INT_BYPASS_EXT_VREF; /* S2 */
        #else /* Internal Vdda reference or obsolete bypass mode */
            `$INSTANCE_NAME`_SAR_CSR6_REG = `$INSTANCE_NAME`_VDDA_VREF;           /* S7 */
        #endif /* `$INSTANCE_NAME`_DEFAULT_REFERENCE == `$INSTANCE_NAME`__EXT_REF */
    #else  /* Reference goes through internal buffer */
        #if(`$INSTANCE_NAME`_DEFAULT_REFERENCE == `$INSTANCE_NAME`__INT_REF_NOT_BYPASSED)
            `$INSTANCE_NAME`_SAR_CSR6_REG = `$INSTANCE_NAME`_INT_VREF;            /* S3 + S4 */
        #else /* INTREF Bypassed of External */
            `$INSTANCE_NAME`_SAR_CSR6_REG = `$INSTANCE_NAME`_INT_BYPASS_EXT_VREF; /* S2 */
        #endif /* `$INSTANCE_NAME`_DEFAULT_REFERENCE == `$INSTANCE_NAME`__INT_REF_NOT_BYPASSED */
    #endif /* VNEG_VDDA_DIFF */

    /* Low non-overlap delay for sampling clock signals (for 1MSPS) */
    #if(`$INSTANCE_NAME`_HIGH_POWER_PULSE == 0u) /* MinPulseWidth <= 50 ns */
        `$INSTANCE_NAME`_SAR_CSR5_REG &= (uint8)~`$INSTANCE_NAME`_SAR_DLY_INC;
    #else /* Set High non-overlap delay for sampling clock signals (for <500KSPS)*/
        `$INSTANCE_NAME`_SAR_CSR5_REG |= `$INSTANCE_NAME`_SAR_DLY_INC;
    #endif /* `$INSTANCE_NAME`_CLOCK_FREQUENCY > (`$INSTANCE_NAME`_MAX_FREQUENCY / 2) */

     /* Delay control for comparator latch enable, low delay, (Default for 1MSPS) */
    #if(`$INSTANCE_NAME`_HIGH_POWER_PULSE == 0u) /* MinPulseWidth <= 50 ns */
        `$INSTANCE_NAME`_SAR_CSR5_REG |= `$INSTANCE_NAME`_SAR_DCEN;
    #else /* Delay control for comparator latch enable, high delay (for <500ksps)*/
        `$INSTANCE_NAME`_SAR_CSR5_REG &= (uint8)~`$INSTANCE_NAME`_SAR_DCEN;
    #endif /* `$INSTANCE_NAME`_CLOCK_FREQUENCY > (`$INSTANCE_NAME`_MAX_FREQUENCY / 2) */

    /* Set default power and other configurations for control register 0 in multiple lines */
    `$INSTANCE_NAME`_SAR_CSR0_REG = (uint8)((uint8)`$INSTANCE_NAME`_DEFAULT_POWER << `$INSTANCE_NAME`_SAR_POWER_SHIFT)
    /* SAR_HIZ_CLEAR:   Should not be used for LP */
    #if ((CY_PSOC5LP) || (`$INSTANCE_NAME`_DEFAULT_REFERENCE != `$INSTANCE_NAME`__EXT_REF))
        | `$INSTANCE_NAME`_SAR_HIZ_CLEAR
    #endif /* SAR_HIZ_CLEAR */
    /*Set Convertion mode */
    #if(`$INSTANCE_NAME`_DEFAULT_CONV_MODE != `$INSTANCE_NAME`__FREE_RUNNING)      /* If triggered mode */
        | `$INSTANCE_NAME`_SAR_MX_SOF_UDB           /* source: UDB */
        | `$INSTANCE_NAME`_SAR_SOF_MODE_EDGE        /* Set edge-sensitive sof source */
    #endif /* `$INSTANCE_NAME`_DEFAULT_CONV_MODE */
    ; /* end of multiple line initialization */

    /* Enable clock for SAR ADC*/
    `$INSTANCE_NAME`_SAR_CLK_REG |= `$INSTANCE_NAME`_SAR_MX_CLK_EN;

    #if(CY_PSOC5A)
        /* Software Reset */
        `$INSTANCE_NAME`_SAR_CSR0_REG |= `$INSTANCE_NAME`_SAR_RESET_SOFT_ACTIVE;
        CyDelayUs(2u); /* 2us delay is required for the lowest 1Mhz clock connected to SAR */
        `$INSTANCE_NAME`_SAR_CSR0_REG &= (uint8)~`$INSTANCE_NAME`_SAR_RESET_SOFT_ACTIVE;
    #else
        CyDelayUs(10u); /* The block is ready to use 10 us after the enable signal is set high. */
    #endif /* End CY_PSOC5A */

    #if(`$INSTANCE_NAME`_IRQ_REMOVE == 0u)
        /* Clear a pending interrupt */
        CyIntClearPending(`$INSTANCE_NAME`_INTC_NUMBER);
    #endif   /* End `$INSTANCE_NAME`_IRQ_REMOVE */        

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Stops convertion and reduce the power to the minimum.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Stop all conversions */
    `$INSTANCE_NAME`_SAR_CSR0_REG &= (uint8)~`$INSTANCE_NAME`_SAR_SOF_START_CONV;

    #if(CY_PSOC5A)
        /* Leave the SAR block powered and reduce the power to the minimum */
        `$INSTANCE_NAME`_SAR_CSR0_REG |= `$INSTANCE_NAME`_ICONT_LV_3;
         /* Disconnect Bypass Cap */
        `$INSTANCE_NAME`_SAR_CSR6_REG &= (uint8)~`$INSTANCE_NAME`_INT_BYPASS_EXT_VREF;
        /* Disable reference buffer and reduce the reference power to the minimum */
        `$INSTANCE_NAME`_SAR_CSR3_REG &= (uint8)~`$INSTANCE_NAME`_SAR_EN_BUF_VREF_EN; /*VCM buffer is absent in PSOC5A*/
        `$INSTANCE_NAME`_SAR_CSR3_REG |= `$INSTANCE_NAME`_SAR_PWR_CTRL_VREF_DIV_BY4;
    #else
        /* Disable the SAR ADC block in Active Power Mode */
        `$INSTANCE_NAME`_PWRMGR_SAR_REG &= (uint8)~`$INSTANCE_NAME`_ACT_PWR_SAR_EN;
        /* Disable the SAR ADC in Standby Power Mode */
        `$INSTANCE_NAME`_STBY_PWRMGR_SAR_REG &= (uint8)~`$INSTANCE_NAME`_STBY_PWR_SAR_EN;
    #endif /* End CY_PSOC5A */

    /* This is only valid if there is an internal clock */
    #if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
        `$INSTANCE_NAME`_PWRMGR_CLK_REG &= (uint8)~`$INSTANCE_NAME`_ACT_PWR_CLK_EN;
        `$INSTANCE_NAME`_STBY_PWRMGR_CLK_REG &= (uint8)~`$INSTANCE_NAME`_STBY_PWR_CLK_EN;
    #endif /* End `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */

    CyExitCriticalSection(enableInterrupts);

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPower
********************************************************************************
*
* Summary:
*  Sets the Power mode.
*
* Parameters:
*  power:  Power setting for ADC
*  0 ->    Normal
*  1 ->    Half power
*  2 ->    1/3rd power
*  3 ->    Quarter power.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPower(uint8 power)
{
    uint8 tmpReg;

    /* mask off invalid power settings */
    power &= `$INSTANCE_NAME`_SAR_API_POWER_MASK;

    /* Set Power parameter  */
    tmpReg = `$INSTANCE_NAME`_SAR_CSR0_REG & (uint8)~`$INSTANCE_NAME`_SAR_POWER_MASK;
    tmpReg |= (uint8)(power << `$INSTANCE_NAME`_SAR_POWER_SHIFT);
    `$INSTANCE_NAME`_SAR_CSR0_REG = tmpReg;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetResolution
********************************************************************************
*
* Summary:
*  Sets the Relution of the SAR.
*  This function does not affect the actual conversion with PSoC5 ES1 silicon.
*
* Parameters:
*  resolution:
*  12 ->    RES12
*  10 ->    RES10
*  8  ->    RES8
*
* Return:
*  None.
*
* Side Effects:
*  The ADC resolution cannot be changed during a conversion cycle. The
*  recommended best practice is to stop conversions with
*  ADC_StopConvert(), change the resolution, then restart the
*  conversions with ADC_StartConvert().
*  If you decide not to stop conversions before calling this API, you
*  should use ADC_IsEndConversion() to wait until conversion is complete
*  before changing the resolution.
*  If you call ADC_SetResolution() during a conversion, the resolution will
*  not be changed until the current conversion is complete. Data will not be
*  available in the new resolution for another 6 + "New Resolution(in bits)"
*  clock cycles.
*  You may need add a delay of this number of clock cycles after
*  ADC_SetResolution() is called before data is valid again.
*  Affects ADC_CountsTo_Volts(), ADC_CountsTo_mVolts(), and
*  ADC_CountsTo_uVolts() by calculating the correct conversion between ADC
*  counts and the applied input voltage. Calculation depends on resolution,
*  input range, and voltage reference.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetResolution(uint8 resolution)
{
    uint8 tmpReg;

    /* remember resolution for the GetResult APIs */
    #if(CY_PSOC5A)
        `$INSTANCE_NAME`_resolution = resolution;
    #endif /* End CY_PSOC5A */

    /* Set SAR ADC resolution and sample width: 18 conversion cycles at 12bits + 1 gap */
    switch (resolution)
    {
        case (uint8)`$INSTANCE_NAME`__BITS_12:
            tmpReg = `$INSTANCE_NAME`_SAR_RESOLUTION_12BIT | `$INSTANCE_NAME`_SAR_SAMPLE_WIDTH;
            break;
        case (uint8)`$INSTANCE_NAME`__BITS_10:
            /* Use 12bits for PSoC5 production silicon and shift the
            *  results for lower resolution in GetResult16() API
            */
            #if(CY_PSOC5A)
                tmpReg = `$INSTANCE_NAME`_SAR_RESOLUTION_12BIT | `$INSTANCE_NAME`_SAR_SAMPLE_WIDTH;
            #else
                tmpReg = `$INSTANCE_NAME`_SAR_RESOLUTION_10BIT | `$INSTANCE_NAME`_SAR_SAMPLE_WIDTH;
            #endif /* End CY_PSOC5A */
            break;
        case (uint8)`$INSTANCE_NAME`__BITS_8:
            #if(CY_PSOC5A)
                tmpReg = `$INSTANCE_NAME`_SAR_RESOLUTION_12BIT | `$INSTANCE_NAME`_SAR_SAMPLE_WIDTH;
            #else
                tmpReg = `$INSTANCE_NAME`_SAR_RESOLUTION_8BIT | `$INSTANCE_NAME`_SAR_SAMPLE_WIDTH;
            #endif /* End CY_PSOC5A */
            break;
        default:
            tmpReg = `$INSTANCE_NAME`_SAR_RESOLUTION_12BIT | `$INSTANCE_NAME`_SAR_SAMPLE_WIDTH;
            /* Halt CPU in debug mode if resolution is out of valid range */
            CYASSERT(0u != 0u);
            break;
    }
    `$INSTANCE_NAME`_SAR_CSR2_REG = tmpReg;

     /* Calculate gain for convert counts to volts */
    `$INSTANCE_NAME`_CalcGain(resolution);
}


#if(`$INSTANCE_NAME`_DEFAULT_CONV_MODE != `$INSTANCE_NAME`__HARDWARE_TRIGGER)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_StartConvert
    ********************************************************************************
    *
    * Summary:
    *  Starts ADC conversion using the given mode. The API is available in the 
    *  free running and the software trigger mode.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Forces the ADC to initiate a conversion. In Free Running mode, the ADC will
    *  run continuously. In a software trigger mode the function also acts as a 
    *  software version of the SOC. Here every conversion has to be triggered by 
    *  the routine. This writes into the SOC bit in SAR_CTRL reg.
    *
    * Side Effects:
    *  In a software trigger mode the function switches source for SOF from the 
    *  external pin to the internal SOF generation. Application should not call 
    *  StartConvert if external source used for SOF.
    *******************************************************************************/
    void `$INSTANCE_NAME`_StartConvert(void)
    {
        #if(`$INSTANCE_NAME`_DEFAULT_CONV_MODE != `$INSTANCE_NAME`__FREE_RUNNING)  /* If software triggered mode */
            `$INSTANCE_NAME`_SAR_CSR0_REG &= (uint8)~`$INSTANCE_NAME`_SAR_MX_SOF_UDB;   /* source: SOF bit */
        #endif /* End `$INSTANCE_NAME`_DEFAULT_CONV_MODE */

        /* Start the conversion */
        `$INSTANCE_NAME`_SAR_CSR0_REG |= `$INSTANCE_NAME`_SAR_SOF_START_CONV;
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_StopConvert
    ********************************************************************************
    *
    * Summary:
    *  Stops ADC conversion using the given mode. The API is available in the 
    *  free running and the software trigger mode.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Stops ADC conversion in Free Running mode.
    *  This writes into the SOC bit in SAR_CTRL reg.
    *
    * Side Effects:
    *  In a software trigger mode the function set a software version of the SOC 
    *  to low level and switch SOF source to hardware SOF input.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_StopConvert(void)
    {
        /* Stop all conversions */
        `$INSTANCE_NAME`_SAR_CSR0_REG &= (uint8)~`$INSTANCE_NAME`_SAR_SOF_START_CONV;

        #if(`$INSTANCE_NAME`_DEFAULT_CONV_MODE != `$INSTANCE_NAME`__FREE_RUNNING)  /* If software triggered mode */
            /* Return source to UDB for hardware SOF signal */
            `$INSTANCE_NAME`_SAR_CSR0_REG |= `$INSTANCE_NAME`_SAR_MX_SOF_UDB;    /* source: UDB */
        #endif /* End `$INSTANCE_NAME`_DEFAULT_CONV_MODE */

    }

#endif /* End `$INSTANCE_NAME`_DEFAULT_CONV_MODE != `$INSTANCE_NAME`__HARDWARE_TRIGGER */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsEndConversion
********************************************************************************
*
* Summary:
*  Queries the ADC to see if conversion is complete
*
* Parameters:
*  retMode:  Wait mode,
*   0 if return with answer imediately.
*   1 if wait until conversion is complete, then return.
*
* Return:
*  (uint8)  0 =>  Conversion not complete.
*           1 =>  Conversion complete.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_IsEndConversion(uint8 retMode)
{
    uint8 status;

    do
    {
        status = `$INSTANCE_NAME`_SAR_CSR1_REG & `$INSTANCE_NAME`_SAR_EOF_1;
    } while ((status != `$INSTANCE_NAME`_SAR_EOF_1) && (retMode == `$INSTANCE_NAME`_WAIT_FOR_RESULT));
    /* If convertion complete, wait until EOF bit released */
    if(status == `$INSTANCE_NAME`_SAR_EOF_1)
    {
        /* wait one ADC clock to let the EOC status bit release */
        CyDelayUs(1u);
        /* Do the unconditional read operation of the CSR1 register to make sure the EOC bit has been cleared */
        CY_GET_REG8(`$INSTANCE_NAME`_SAR_CSR1_PTR);
    }

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetResult8
********************************************************************************
*
* Summary:
*  Returns an 8-bit result or the LSB of the last conversion.
*  `$INSTANCE_NAME`_IsEndConversion() should be called to verify that the data
*   sample is ready
*
* Parameters:
*  None.
*
* Return:
*  ADC result.
*
* Global Variables:
*  `$INSTANCE_NAME`_shift - used to convert the ADC counts to the 2's
*  compliment form.
*  `$INSTANCE_NAME`_resolution - used to shift the results for lower
*   resolution.
*
*******************************************************************************/
int8 `$INSTANCE_NAME`_GetResult8( void )
{

    #if(CY_PSOC5A)

        uint16 res;

        res = CY_GET_REG16(`$INSTANCE_NAME`_SAR_WRK_PTR);

        /* Use 12bits for PSoC5 production silicon and shift the results for lower resolution in this API */
        switch (`$INSTANCE_NAME`_resolution)
        {
            case (uint8)`$INSTANCE_NAME`__BITS_10:
                res >>= 2u;
                break;
            case (uint8)`$INSTANCE_NAME`__BITS_8:
                res >>= 4u;
                break;
            default: /* Do not shift for 12 bits */
                break;
        }
        return( (int8)((int16)res - `$INSTANCE_NAME`_shift) );
    #else
        return( (int8)`$INSTANCE_NAME`_SAR_WRK0_REG - (int8)`$INSTANCE_NAME`_shift);
    #endif /* End CY_PSOC5A */

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetResult16
********************************************************************************
*
* Summary:
*  Gets the data available in the SAR DATA registers.
*  `$INSTANCE_NAME`_IsEndConversion() should be called to verify that the data
*   sample is ready
*
* Parameters:
*  None.
*
* Return:
*  ADC result. WORD value which has the converted 12bits. In the differential
*  input mode the SAR ADC outputs digitally converted data in binary offset
*  scheme, this function converts the data into 2's compliment form.
*
* Global Variables:
*  `$INSTANCE_NAME`_shift - used to convert the ADC counts to the 2's
*  compliment form.
*  `$INSTANCE_NAME`_resolution - used to shift the results for lower
*   resolution.
*
*******************************************************************************/
int16 `$INSTANCE_NAME`_GetResult16( void )
{
    uint16 res;

    res = CY_GET_REG16(`$INSTANCE_NAME`_SAR_WRK_PTR);

    #if(CY_PSOC5A)
        /* Use 12bits for PSoC5 production silicon and shift the results for lower resolution in this API */
        switch (`$INSTANCE_NAME`_resolution)
        {
            case (uint8)`$INSTANCE_NAME`__BITS_10:
                res >>= 2u;
                break;
            case (uint8)`$INSTANCE_NAME`__BITS_8:
                res >>= 4u;
                break;
            default: /* Do not shift for 12 bits */
                break;
        }
    #endif /* End CY_PSOC5A */

    return( (int16)res - `$INSTANCE_NAME`_shift );
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOffset
********************************************************************************
*
* Summary:
*  This function sets the offset for voltage readings.
*
* Parameters:
*  int16: Offset in counts
*
* Return:
*  None.
*
* Global Variables:
*  The `$INSTANCE_NAME`_offset variable modified. This variable is used for
*  offset calibration purpose.
*  Affects the `$INSTANCE_NAME`_CountsTo_Volts,
*  `$INSTANCE_NAME`_CountsTo_mVolts, `$INSTANCE_NAME`_CountsTo_uVolts functions
*  by subtracting the given offset.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOffset(int16 offset)
{
    `$INSTANCE_NAME`_offset = offset;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CalcGain
********************************************************************************
*
* Summary:
*  This function calculates the ADC gain in counts per volt.
*
* Parameters:
*  uint8: resolution
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_shift variable initialized. This variable is used to
*  convert the ADC counts to the 2's compliment form.
*  `$INSTANCE_NAME`_countsPerVolt variable initialized. This variable is used
*  for gain calibration purpose.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_CalcGain( uint8 resolution )
{
    int32 counts;
    #if(!((`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSS_TO_VREF) || \
         (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSSA_TO_VDDA) || \
         (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSSA_TO_VDAC)) )
        uint16 diff_zero;
    #endif /* End `$INSTANCE_NAME`_DEFAULT_RANGE */

    switch (resolution)
    {
        case (uint8)`$INSTANCE_NAME`__BITS_12:
            counts = (int32)`$INSTANCE_NAME`_SAR_WRK_MAX;
            #if(!((`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSS_TO_VREF) || \
                 (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSSA_TO_VDDA) || \
                 (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSSA_TO_VDAC)) )
                diff_zero = `$INSTANCE_NAME`_SAR_DIFF_SHIFT;
            #endif /* End `$INSTANCE_NAME`_DEFAULT_RANGE */
            break;
        case (uint8)`$INSTANCE_NAME`__BITS_10:
            counts = (int32)(`$INSTANCE_NAME`_SAR_WRK_MAX >> 2u);
            #if(!((`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSS_TO_VREF) || \
                 (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSSA_TO_VDDA) || \
                 (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSSA_TO_VDAC)) )
                diff_zero = `$INSTANCE_NAME`_SAR_DIFF_SHIFT >> 2u;
            #endif /* End `$INSTANCE_NAME`_DEFAULT_RANGE */
            break;
        case (uint8)`$INSTANCE_NAME`__BITS_8:
            counts = (int32)(`$INSTANCE_NAME`_SAR_WRK_MAX >> 4u);
            #if(!((`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSS_TO_VREF) || \
                 (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSSA_TO_VDDA) || \
                 (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSSA_TO_VDAC)) )
                diff_zero = `$INSTANCE_NAME`_SAR_DIFF_SHIFT >> 4u;
            #endif /* End `$INSTANCE_NAME`_DEFAULT_RANGE */
            break;
        default: /* Halt CPU in debug mode if resolution is out of valid range */
            counts = 0;
            #if(!((`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSS_TO_VREF) || \
                 (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSSA_TO_VDDA) || \
                 (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSSA_TO_VDAC)) )
                diff_zero = 0u;
            #endif /* End `$INSTANCE_NAME`_DEFAULT_RANGE */
            CYASSERT(0u != 0u);
            break;
    }
    counts *= 1000; /* To avoid float point arithmetic*/
    `$INSTANCE_NAME`_countsPerVolt = (int16)(counts / `$INSTANCE_NAME`_DEFAULT_REF_VOLTAGE_MV / 2);

    #if( (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSS_TO_VREF) || \
         (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSSA_TO_VDDA) || \
         (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`__VSSA_TO_VDAC) )
        `$INSTANCE_NAME`_shift = 0;
    #else
        `$INSTANCE_NAME`_shift = diff_zero;
    #endif /* End `$INSTANCE_NAME`_DEFAULT_RANGE */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetGain
********************************************************************************
*
* Summary:
*  This function sets the ADC gain in counts per volt.
*
* Parameters:
*  int16  adcGain  counts per volt
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_countsPerVolt variable modified. This variable is used
*  for gain calibration purpose.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetGain(int16 adcGain)
{
    `$INSTANCE_NAME`_countsPerVolt = adcGain;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_mVolts
********************************************************************************
*
* Summary:
*  This function converts ADC counts to mVolts
*
* Parameters:
*  int16  adcCounts   Reading from ADC.
*
* Return:
*  int16  Result in mVolts
*
* Global Variables:
*  `$INSTANCE_NAME`_offset variable used.
*  `$INSTANCE_NAME`_countsPerVolt variable used.
*
*******************************************************************************/
int16 `$INSTANCE_NAME`_CountsTo_mVolts(int16 adcCounts)
{

    int16 mVolts;

    /* Subtract ADC offset */
    adcCounts -= `$INSTANCE_NAME`_offset;

    mVolts = (int16)(( (int32)adcCounts * 1000 ) / `$INSTANCE_NAME`_countsPerVolt) ;

    return( mVolts );
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_uVolts
********************************************************************************
*
* Summary:
*  This function converts ADC counts to micro Volts
*
* Parameters:
*  int16  adcCounts   Reading from ADC.
*
* Return:
*  int32  Result in micro Volts
*
* Global Variables:
*  `$INSTANCE_NAME`_offset variable used.
*  `$INSTANCE_NAME`_countsPerVolt variable used.
*
*******************************************************************************/
int32 `$INSTANCE_NAME`_CountsTo_uVolts(int16 adcCounts)
{

    int32 uVolts;

    /* Subtract ADC offset */
    adcCounts -= `$INSTANCE_NAME`_offset;
    /* To convert adcCounts to microVolts it is required to be multiplied
    *  on 1 million. It is multiplied on 500000 and later on 2 to
    *  to avoid 32bit arithmetic overflows.
    */
    uVolts = (( (int32)adcCounts * 500000 ) / `$INSTANCE_NAME`_countsPerVolt) * 2;

    return( uVolts );
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_Volts
********************************************************************************
*
* Summary:
*  This function converts ADC counts to Volts
*
* Parameters:
*  int16  adcCounts   Reading from ADC.
*
* Return:
*  float  Result in mVolts
*
* Global Variables:
*  `$INSTANCE_NAME`_offset variable used.
*  `$INSTANCE_NAME`_countsPerVolt variable used.
*
*******************************************************************************/
float32 `$INSTANCE_NAME`_CountsTo_Volts(int16 adcCounts)
{
    float32 volts;

    /* Subtract ADC offset */
    adcCounts -= `$INSTANCE_NAME`_offset;

    volts = (float32)adcCounts / (float32)`$INSTANCE_NAME`_countsPerVolt;

    return( volts );
}


/* [] END OF FILE */
