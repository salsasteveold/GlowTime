/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the ADC 
*  User Module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "`$INSTANCE_NAME`.h"

uint8 `$INSTANCE_NAME`_initVar = 0u;

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
    /* Set DelSig mode */
    `$INSTANCE_NAME`_CR0_REG = 
        (`$INSTANCE_NAME`_MODE_1ST_MOD << `$INSTANCE_NAME`_MODE_SHIFT);
	
    // set the input range
	`$INSTANCE_NAME`_CR1_REG = 
        (`$Input_Range` << `$INSTANCE_NAME`_GAIN_SHIFT) | 
        (`$INSTANCE_NAME`_DRIVE_400UA << `$INSTANCE_NAME`_DRIVE_SHIFT) | 
        (`$INSTANCE_NAME`_COMP_3P6PF << `$INSTANCE_NAME`_COMP_SHIFT);
    
    // set bias control and compensetaion
	`$INSTANCE_NAME`_CR2_REG = 
        (`$INSTANCE_NAME`_BIAS_CTL_2X << `$INSTANCE_NAME`_BIAS_CTL_SHIFT);
    
    // enable the clock source and enable dynamic control for modulator reset
	`$INSTANCE_NAME`_CLK_REG |= 
        (`$INSTANCE_NAME`_CLK_EN_ENABLE << `$INSTANCE_NAME`_CLK_EN_SHIFT) | 
        (`$INSTANCE_NAME`_DYN_CNTL_EN_ENABLE << `$INSTANCE_NAME`_DYN_CNTL_EN_SHIFT);
}

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
    // enable the internal pump clock for the SC/CT block
	`$INSTANCE_NAME`_PUMP_CR1_REG |= (`$INSTANCE_NAME`_PUMP_INTERNAL << `$INSTANCE_NAME`_PUMP_SHIFT);
	
	 /* Enable power to the Amp in Active mode*/
    `$INSTANCE_NAME`_PM_ACT_CFG_REG |= `$INSTANCE_NAME`_ACT_PWR_EN;
    
    /* Enable power to the Amp in Alt Active mode*/
    `$INSTANCE_NAME`_PM_STBY_CFG_REG |= `$INSTANCE_NAME`_STBY_PWR_EN;
	
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

    if(`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }
    
    
    `$INSTANCE_NAME`_Enable();

	
}

/* [] END OF FILE */