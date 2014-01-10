/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the power manager source code to the API for the 
*  Delta-Sigma ADC Component.
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

static `$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup = 
{
    `$INSTANCE_NAME`_DISABLED,
    `$INSTANCE_NAME`_`$Config1_Name`_DEC_CR
};


/*******************************************************************************  
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  Save the register configuration which are not retention.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
* Global variables:
*  `$INSTANCE_NAME`_backup:  This global structure variable is used to store 
*  configuration registers which are non retention whenever user wants to go 
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`
{
    `$INSTANCE_NAME`_backup.deccr = `$INSTANCE_NAME`_DEC_CR_REG;
}


/*******************************************************************************  
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the register configurations which are not retention.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
* Global variables:
*  `$INSTANCE_NAME`_backup:  This global structure variable is used to restore 
*  configuration registers which are non retention whenever user wants to switch 
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`
{
    `$INSTANCE_NAME`_DEC_CR_REG = `$INSTANCE_NAME`_backup.deccr;
}


/******************************************************************************* 
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Stops the operation of the block and saves the user configuration. 
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  `$INSTANCE_NAME`_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`
{
    /* Save ADC enable state */
    if((`$INSTANCE_NAME`_ACT_PWR_DEC_EN == (`$INSTANCE_NAME`_PWRMGR_DEC_REG & `$INSTANCE_NAME`_ACT_PWR_DEC_EN)) &&
       (`$INSTANCE_NAME`_ACT_PWR_DSM_EN == (`$INSTANCE_NAME`_PWRMGR_DSM_REG & `$INSTANCE_NAME`_ACT_PWR_DSM_EN)))
    {
        /* Component is enabled */
        `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_ENABLED;
    }
    else
    {
        /* Component is disabled */
        `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_DISABLED;
    }

    /* Stop the configuration */
    `$INSTANCE_NAME`_Stop();

    /* Save the user configuration */
    `$INSTANCE_NAME`_SaveConfig();
}


/******************************************************************************* 
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and enables the power to the block.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  `$INSTANCE_NAME`_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`
{
    /* Restore the configuration */
    `$INSTANCE_NAME`_RestoreConfig();

    /* Enable's the component operation */
    if(`$INSTANCE_NAME`_backup.enableState == `$INSTANCE_NAME`_ENABLED)
    {
        `$INSTANCE_NAME`_Enable();

        /* Start the conversion only if conversion is not triggered by the hardware */
        if(!(`$INSTANCE_NAME`_DEC_CR_REG & `$INSTANCE_NAME`_DEC_XSTART_EN))
        {
            `$INSTANCE_NAME`_StartConvert();
        }

    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
