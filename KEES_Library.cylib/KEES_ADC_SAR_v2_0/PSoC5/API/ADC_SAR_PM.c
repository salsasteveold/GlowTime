/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"


/***************************************
* Local data allocation
***************************************/

static `$INSTANCE_NAME`_BACKUP_STRUCT  `$INSTANCE_NAME`_backup =
{
    `$INSTANCE_NAME`_DISABLED
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - modified.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void)
{
    if((`$INSTANCE_NAME`_PWRMGR_SAR_REG  & `$INSTANCE_NAME`_ACT_PWR_SAR_EN) != 0u)
    {
        if((`$INSTANCE_NAME`_SAR_CSR0_REG & `$INSTANCE_NAME`_SAR_SOF_START_CONV) != 0u)
        {
            `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_ENABLED | `$INSTANCE_NAME`_STARTED;
        }
        else
        {
            `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_ENABLED;
        }
        `$INSTANCE_NAME`_Stop();
    }
    else
    {
        `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_DISABLED;
    }
    /*`$INSTANCE_NAME`_SaveConfig();*/
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - used.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void)
{
    /*`$INSTANCE_NAME`_RestoreConfig();*/
    if(`$INSTANCE_NAME`_backup.enableState != `$INSTANCE_NAME`_DISABLED)
    {
        `$INSTANCE_NAME`_Enable();
        #if(`$INSTANCE_NAME`_DEFAULT_CONV_MODE != `$INSTANCE_NAME`__HARDWARE_TRIGGER)
            if((`$INSTANCE_NAME`_backup.enableState & `$INSTANCE_NAME`_STARTED) != 0u)
            {
                `$INSTANCE_NAME`_StartConvert();
            }
        #endif /* End `$INSTANCE_NAME`_DEFAULT_CONV_MODE != `$INSTANCE_NAME`__HARDWARE_TRIGGER */
        
    }
}


/* [] END OF FILE */
