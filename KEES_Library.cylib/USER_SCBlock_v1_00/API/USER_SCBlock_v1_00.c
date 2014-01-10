/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the unknown 
*  User Module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "`$INSTANCE_NAME`.h"

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
*  No
* 
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
	// registers, masks, modes and shifts are all available in the header file
	
    // set the mode
    `$INSTANCE_NAME`_CR0_REG = 0;
	
    // configure gain, clock div by 2, compensation and drive
	`$INSTANCE_NAME`_CR1_REG = 0;
    
    // configure Vref gnd, feedback resistance, feedback capacitor, input impedance and bias control
	`$INSTANCE_NAME`_CR2_REG = 0;
    
    // enable the clock, clock source and enable dynamic control
	// creator will automatically select the clock mux options for you
	// all you need to do is enable the clock
	`$INSTANCE_NAME`_CLK_REG |= 
        (`$INSTANCE_NAME`_CLK_EN_ENABLE << `$INSTANCE_NAME`_CLK_EN_SHIFT) | // Keep this line
        (`$INSTANCE_NAME`_DYN_CNTL_EN_ENABLE << `$INSTANCE_NAME`_DYN_CNTL_EN_SHIFT);  // if the DynCtl input is going to be used, then leave this line
}

/* ------ EXAMPLE INIT FUNCTION FOR DELTA SIGMA MODULATOR MODE --------
void `$INSTANCE_NAME`_Init(void)
{
	// registers, masks, modes and shifts are all available in the header file
	
    // set the mode
    `$INSTANCE_NAME`_CR0_REG = 
        (`$INSTANCE_NAME`_MODE_1ST_MOD << `$INSTANCE_NAME`_MODE_SHIFT);
	
    // configure gain, drive and compensation
	`$INSTANCE_NAME`_CR1_REG = 
        (`$INSTANCE_NAME`_DRIVE_400UA << `$INSTANCE_NAME`_DRIVE_SHIFT) | 
        (`$INSTANCE_NAME`_COMP_3P6PF << `$INSTANCE_NAME`_COMP_SHIFT);
    
    // set bias control
	`$INSTANCE_NAME`_CR2_REG = 
        (`$INSTANCE_NAME`_BIAS_CTL_2X << `$INSTANCE_NAME`_BIAS_CTL_SHIFT);
    
    // enable the clock source and enable dynamic control
	// creator will automatically select the clock mux options for you
	// all you need to do is enable the clock
	`$INSTANCE_NAME`_CLK_REG |= 
        (`$INSTANCE_NAME`_CLK_EN_ENABLE << `$INSTANCE_NAME`_CLK_EN_SHIFT) | // Keep this line
        (`$INSTANCE_NAME`_DYN_CNTL_EN_ENABLE << `$INSTANCE_NAME`_DYN_CNTL_EN_SHIFT);  // if the DynCtl input is going to be used, then leave this line
}
*/

/*******************************************************************************   
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables the ADC block operation
*
* Parameters:
*  void
*l
* Return:
*  void
*
* Reentrant:
*  No
* 
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
	// ---- there should be no need to change any of this API ----
	
    // enable the internal pump clock for the SC/CT block
	`$INSTANCE_NAME`_PUMP_CR1_REG |= (`$INSTANCE_NAME`_PUMP_INTERNAL << `$INSTANCE_NAME`_PUMP_SHIFT);
	
	 // Enable power to the SCCTBlock in Active mode
    `$INSTANCE_NAME`_PM_ACT_CFG_REG |= `$INSTANCE_NAME`_ACT_PWR_EN;
    
    // Enable power to the SCCTBlock in Alt Active mode
    `$INSTANCE_NAME`_PM_STBY_CFG_REG |= `$INSTANCE_NAME`_STBY_PWR_EN;
	
	// this section of code enables or disables the internal boost pumps
	// based on the voltage settings in the CYDWR resource file.
	// to ensure proper operation at any voltage, leave this code intact
	#if (CYDEV_VARIABLE_VDDA == 1u)
        if(CyScPumpEnabled == 1u)
        {
            `$INSTANCE_NAME`_BST_REG &= (uint8)(~`$INSTANCE_NAME`_MX_BST_CLK_MASK);
            `$INSTANCE_NAME`_BST_REG |= (uint8)(`$INSTANCE_NAME`_BST_CLK_EN_ENABLE << `$INSTANCE_NAME`_BST_CLK_EN_SHIFT) | CyScBoostClk__INDEX;
            `$INSTANCE_NAME`_SC_MISC_REG |= (uint8)(`$INSTANCE_NAME`_SC_PUMP_FORCE << `$INSTANCE_NAME`_SC_PUMP_FORCE_SHIFT);
            CyScBoostClk_Start();
        }
        else
        {
            `$INSTANCE_NAME`_BST_REG &= (uint8)(~`$INSTANCE_NAME`_MX_BST_CLK_MASK);
            `$INSTANCE_NAME`_SC_MISC_REG &= (uint8)(~`$INSTANCE_NAME`_SC_PUMP_FORCE_MASK);
        }
    #endif
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  The start function initializes the PGA with the default values, and sets
*  the power to the given level.  A power level of 0, is the same as executing
*  the stop function.
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Reentrant: 
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) 
{   
    `$INSTANCE_NAME`_Init();
    `$INSTANCE_NAME`_Enable();
}


/* [] END OF FILE */