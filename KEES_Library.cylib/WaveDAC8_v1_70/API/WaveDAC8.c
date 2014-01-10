/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  Description:
*    This file provides the source code for the 8-bit Waveform DAC 
*    (WaveDAC8) Component.
*
*   Note:
*
*
*******************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#include "cytypes.h"
#include "`$INSTANCE_NAME`.h"
#include "cyfitter.h"
#include <math.h>

#if(`$INSTANCE_NAME`_DACMODE == `$INSTANCE_NAME`_VOLT_MODE)
#include <`$INSTANCE_NAME`_VDAC8.h>
#else
#include <`$INSTANCE_NAME`_IDAC8.h>
#endif

uint8  `$INSTANCE_NAME`_initVar = 0;

uint8  `$INSTANCE_NAME`_wave1[`$INSTANCE_NAME`_WAVE1_LENGTH] = { `$Wave1_Data` };
uint8  `$INSTANCE_NAME`_wave2[`$INSTANCE_NAME`_WAVE2_LENGTH] = { `$Wave2_Data` };

uint8  `$INSTANCE_NAME`_Wave1Chan;
uint8  `$INSTANCE_NAME`_Wave2Chan;
uint8  `$INSTANCE_NAME`_Wave1TD;
uint8  `$INSTANCE_NAME`_Wave2TD;


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
*  void
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{

#if(`$INSTANCE_NAME`_DACMODE == `$INSTANCE_NAME`_VOLT_MODE)
   `$INSTANCE_NAME`_VDAC8_Init();
   `$INSTANCE_NAME`_VDAC8_SetSpeed(`$INSTANCE_NAME`_HIGHSPEED);
   `$INSTANCE_NAME`_VDAC8_SetRange(`$INSTANCE_NAME`_DAC_RANGE );
#else
   `$INSTANCE_NAME`_IDAC8_Init();
   `$INSTANCE_NAME`_IDAC8_SetSpeed(`$INSTANCE_NAME`_HIGHSPEED);
   `$INSTANCE_NAME`_IDAC8_SetPolarity(`$INSTANCE_NAME`_DAC_POL);
   `$INSTANCE_NAME`_IDAC8_SetRange(`$INSTANCE_NAME`_DAC_RANGE );
#endif
  
    /* Get the TD Number for the DMA channel 1 and 2   */
    `$INSTANCE_NAME`_Wave1TD = CyDmaTdAllocate();
    `$INSTANCE_NAME`_Wave2TD = CyDmaTdAllocate();
	
    /* Initialize waveform pointers  */
    `$INSTANCE_NAME`_Wave1Setup( &`$INSTANCE_NAME`_wave1[0], `$INSTANCE_NAME`_WAVE1_LENGTH) ;
    `$INSTANCE_NAME`_Wave2Setup( &`$INSTANCE_NAME`_wave2[0], `$INSTANCE_NAME`_WAVE2_LENGTH) ;
	
    /* Initialize the internal clock if one present  */
    #if defined(`$INSTANCE_NAME`_DacClk__CFG3)
       `$INSTANCE_NAME`_DacClk_SetPhase(1);
    #endif
	
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*  
* Summary: 
*  Enables the DAC block and DMA operation
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{

#if(`$INSTANCE_NAME`_DACMODE == `$INSTANCE_NAME`_VOLT_MODE)
   `$INSTANCE_NAME`_VDAC8_Enable();
#else
   `$INSTANCE_NAME`_IDAC8_Enable();
#endif	

    // Enable the channel
    // It is configured to remember the TD value so that it can be
    // restored from the place where it has been stopped.  
    CyDmaChEnable(`$INSTANCE_NAME`_Wave1Chan, 1);
    CyDmaChEnable(`$INSTANCE_NAME`_Wave2Chan, 1);
	
    CyDmaChSetRequest(`$INSTANCE_NAME`_Wave1Chan, CPU_REQ);
    CyDmaChSetRequest(`$INSTANCE_NAME`_Wave2Chan, CPU_REQ);

    #if(`$INSTANCE_NAME`_CLOCK_SRC)  	
       `$INSTANCE_NAME`_DacClk_Start();
    #endif
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as executing
*  the stop function.
*
* Parameters:  
*  Power:   Sets power level between off (0) and (3) high power
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
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
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Powers down DAC to lowest power state.
*
* Parameters:  
*  (void)  
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{

    /* Turn off internal clock, if one present */
    #if(`$INSTANCE_NAME`_CLOCK_SRC)  	
       `$INSTANCE_NAME`_DacClk_Start();
    #endif
	
   /* Disble power to DAC */
   CyDmaChDisable(`$INSTANCE_NAME`_Wave1Chan);
   CyDmaChDisable(`$INSTANCE_NAME`_Wave2Chan);


#if(`$INSTANCE_NAME`_DACMODE == `$INSTANCE_NAME`_VOLT_MODE)
   `$INSTANCE_NAME`_VDAC8_Stop();
#else
   `$INSTANCE_NAME`_IDAC8_Stop();
#endif

}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wave1Setup
********************************************************************************
*
* Summary:
*  Set pointer and size for waveform 1.                                    
*
* Parameters:  
*   uint8 * WavePtr:     Pointer to the waveform array.
*   uint16  SampleSize:  The amount of samples in the waveform.
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wave1Setup( uint8 * WavePtr, uint16 SampleSize) 
{

    #if (defined(__C51__))   /* PSoC 3 */
        `$INSTANCE_NAME`_Wave1Chan = `$INSTANCE_NAME`_Wave1_DMA_DmaInitialize(`$INSTANCE_NAME`_Wave1_DMA_BYTES_PER_BURST, \
		            	     `$INSTANCE_NAME`_Wave1_DMA_REQUEST_PER_BURST, 0, 0x0);

    #else /* PSoC 5 */
        `$INSTANCE_NAME`_Wave1Chan = `$INSTANCE_NAME`_Wave1_DMA_DmaInitialize(`$INSTANCE_NAME`_Wave1_DMA_BYTES_PER_BURST, 
			             `$INSTANCE_NAME`_Wave1_DMA_REQUEST_PER_BURST, 
				         HI16(WavePtr), HI16(`$INSTANCE_NAME`_DAC8__D));
    #endif
	
    /* Setup the TD. In this the TD is looped it itself so that        */
    /* the wave form generation is continuous. This is an example of   */
    /* Auto repeat DMA                                                 */
    CyDmaTdSetConfiguration(`$INSTANCE_NAME`_Wave1TD, SampleSize, `$INSTANCE_NAME`_Wave1TD, TD_INC_SRC_ADR|`$INSTANCE_NAME`_Wave1_DMA_TD_TERMOUT_EN ); 
							
    /* Set the TD start and destination address                          */
    /* The DAC_SetValue function cannot be used to write the DAC values  */
    /* Instead the DAC data register address should be passed.           */
    /* The Data register address can be got from cyfitter.h              */
    CyDmaTdSetAddress(`$INSTANCE_NAME`_Wave1TD, (LO16( (uint32)WavePtr )), (LO16((uint32)`$INSTANCE_NAME`_DAC8__D)));
	
    /* Associate the TD with the channel */
    CyDmaChSetInitialTd(`$INSTANCE_NAME`_Wave1Chan, `$INSTANCE_NAME`_Wave1TD);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wave2Setup
********************************************************************************
*
* Summary:
*  Set pointer and size for waveform 2.                                    
*
* Parameters:  
*   uint8 * WavePtr:     Pointer to the waveform array.
*   uint16  SampleSize:  The amount of samples in the waveform.
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wave2Setup( uint8 * WavePtr, uint16 SampleSize) 
{

    #if (defined(__C51__))   /* PSoC 3 */
        `$INSTANCE_NAME`_Wave2Chan = `$INSTANCE_NAME`_Wave2_DMA_DmaInitialize(`$INSTANCE_NAME`_Wave2_DMA_BYTES_PER_BURST, \
		            	     `$INSTANCE_NAME`_Wave2_DMA_REQUEST_PER_BURST, 0, 0x0);

    #else /* PSoC 5 */
        `$INSTANCE_NAME`_Wave2Chan = `$INSTANCE_NAME`_Wave2_DMA_DmaInitialize(`$INSTANCE_NAME`_Wave2_DMA_BYTES_PER_BURST, 
			             `$INSTANCE_NAME`_Wave2_DMA_REQUEST_PER_BURST, 
				          HI16(WavePtr), HI16(`$INSTANCE_NAME`_DAC8__D));
    #endif

    /* Setup the TD. In this the TD is looped it itself so that        */
    /* the wave form generation is continuous. This is an example of   */
    /* Auto repeat DMA                                                 */
    CyDmaTdSetConfiguration(`$INSTANCE_NAME`_Wave2TD, SampleSize, `$INSTANCE_NAME`_Wave2TD,TD_INC_SRC_ADR|`$INSTANCE_NAME`_Wave2_DMA_TD_TERMOUT_EN ); 
							
    /* Set the TD start and destination address                         */
    /* The DAC_SetValue function cannot be used to write the DAC values */
    /* Instead the DAC data register address should be passed.          */
    /* The Data register address can be got from cyfitter.h             */
    CyDmaTdSetAddress(`$INSTANCE_NAME`_Wave2TD, LO16( (uint32)WavePtr ), LO16((uint32)`$INSTANCE_NAME`_DAC8__D));
	
    /* Associate the TD with the channel */
    CyDmaChSetInitialTd(`$INSTANCE_NAME`_Wave2Chan, `$INSTANCE_NAME`_Wave2TD);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSpeed
********************************************************************************
*
* Summary:
*  Set DAC speed
*
* Parameters:  
*  power:   Sets speed value 
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetSpeed(uint8 speed) 
{
#if(`$INSTANCE_NAME`_DACMODE == `$INSTANCE_NAME`_VOLT_MODE)
   `$INSTANCE_NAME`_VDAC8_SetSpeed(speed);
#else
   `$INSTANCE_NAME`_IDAC8_SetSpeed(speed);
#endif
   
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetRange
********************************************************************************
*
* Summary:
*  Set current or voltage range.
*
* Parameters:  
*  Range:  Range constant.
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetRange(uint8 range)
{
#if(`$INSTANCE_NAME`_DACMODE == `$INSTANCE_NAME`_VOLT_MODE)
   `$INSTANCE_NAME`_VDAC8_SetRange(range);
#else
   `$INSTANCE_NAME`_IDAC8_SetRange(range);
#endif
 
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetValue
********************************************************************************
*
* Summary:
*  Set 8-bit DAC value
*
* Parameters:  
*  value:  Sets DAC value between 0 and 255.
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetValue(uint8 value)
{
#if(`$INSTANCE_NAME`_DACMODE == `$INSTANCE_NAME`_VOLT_MODE)
   `$INSTANCE_NAME`_VDAC8_SetValue(value);
#else
   `$INSTANCE_NAME`_IDAC8_SetValue(value);
#endif

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DacTrim
********************************************************************************
*
* Summary:
*  Set the trim value for the given range.
*
* Parameters:  
*   range:  Sets trim for voltage and current modes  
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void `$INSTANCE_NAME`_DacTrim(void)
{
#if(`$INSTANCE_NAME`_DACMODE == `$INSTANCE_NAME`_VOLT_MODE)
   `$INSTANCE_NAME`_VDAC8_DacTrim();
#else
   `$INSTANCE_NAME`_IDAC8_DacTrim();
#endif
 
}


/* [] END OF FILE */



