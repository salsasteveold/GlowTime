/*******************************************************************************
* File Name: RTC_BOOT.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the bootloader
*  communication support in SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "RTC.h"

#if(RTC_SCB_MODE_I2C_INC)
    #include "RTC_I2C.h"
#endif /* (RTC_SCB_MODE_I2C_INC) */

#if(RTC_SCB_MODE_EZI2C_INC)
    #include "RTC_EZI2C.h"
#endif /* (RTC_SCB_MODE_EZI2C_INC) */

#if(RTC_SCB_MODE_SPI_INC || RTC_SCB_MODE_UART_INC)
    #include "RTC_SPI_UART.h"
#endif /* (RTC_SCB_MODE_SPI_INC || RTC_SCB_MODE_UART_INC) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_RTC) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/*******************************************************************************
* Function Name: RTC_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls Start function fucntion of the bootloader communication component for
*  selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RTC_CyBtldrCommStart(void)
{
    #if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)
        if(RTC_SCB_MODE_I2C_RUNTM_CFG)
        {
            RTC_I2CCyBtldrCommStart();
        }
        else if(RTC_SCB_MODE_SPI_RUNTM_CFG)
        {
            RTC_SpiCyBtldrCommStart();
        }
        else if(RTC_SCB_MODE_UART_RUNTM_CFG)
        {
            RTC_UartCyBtldrCommStart();
        }
        else if(RTC_SCB_MODE_EZI2C_RUNTM_CFG)
        {
             RTC_EzI2CCyBtldrCommStart();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(RTC_SCB_MODE_I2C_CONST_CFG)
        RTC_I2CCyBtldrCommStart();

    #elif(RTC_SCB_MODE_SPI_CONST_CFG)
        RTC_SpiCyBtldrCommStart();

    #elif(RTC_SCB_MODE_UART_CONST_CFG)
        RTC_UartCyBtldrCommStart();

    #elif(RTC_SCB_MODE_EZI2C_CONST_CFG)
        RTC_EzI2CCyBtldrCommStart();

    #else
        /* Do nothing */

    #endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: RTC_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls Stop function fucntion of the bootloader communication component for
*  selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RTC_CyBtldrCommStop(void)
{
    #if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)
        if(RTC_SCB_MODE_I2C_RUNTM_CFG)
        {
            RTC_I2CCyBtldrCommStop();
        }
        else if(RTC_SCB_MODE_SPI_RUNTM_CFG)
        {
            RTC_SpiCyBtldrCommStop();
        }
        else if(RTC_SCB_MODE_UART_RUNTM_CFG)
        {
            RTC_UartCyBtldrCommStop();
        }
        else if(RTC_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            RTC_EzI2CCyBtldrCommStop();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(RTC_SCB_MODE_I2C_CONST_CFG)
        RTC_I2CCyBtldrCommStop();

    #elif(RTC_SCB_MODE_SPI_CONST_CFG)
        RTC_SpiCyBtldrCommStop();

    #elif(RTC_SCB_MODE_UART_CONST_CFG)
        RTC_UartCyBtldrCommStop();

    #elif(RTC_SCB_MODE_EZI2C_CONST_CFG)
        RTC_EzI2CCyBtldrCommStop();

    #else
        /* Do nothing */

    #endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: RTC_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls reset function fucntion of the bootloader communication component for
*  selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RTC_CyBtldrCommReset(void)
{
    #if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)
        if(RTC_SCB_MODE_I2C_RUNTM_CFG)
        {
            RTC_I2CCyBtldrCommReset();
        }
        else if(RTC_SCB_MODE_SPI_RUNTM_CFG)
        {
            RTC_SpiCyBtldrCommReset();
        }
        else if(RTC_SCB_MODE_UART_RUNTM_CFG)
        {
            RTC_UartCyBtldrCommReset();
        }
        else if(RTC_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            RTC_EzI2CCyBtldrCommReset();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(RTC_SCB_MODE_I2C_CONST_CFG)
        RTC_I2CCyBtldrCommReset();

    #elif(RTC_SCB_MODE_SPI_CONST_CFG)
        RTC_SpiCyBtldrCommReset();

    #elif(RTC_SCB_MODE_UART_CONST_CFG)
        RTC_UartCyBtldrCommReset();

    #elif(RTC_SCB_MODE_EZI2C_CONST_CFG)
        RTC_EzI2CCyBtldrCommReset();

    #else
        /* Do nothing */

    #endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: RTC_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls read fucntion of the bootloader communication component for selected
*  mode.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus RTC_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)
        if(RTC_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = RTC_I2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(RTC_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = RTC_SpiCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(RTC_SCB_MODE_UART_RUNTM_CFG)
        {
            status = RTC_UartCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(RTC_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = RTC_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }

    #elif(RTC_SCB_MODE_I2C_CONST_CFG)
        status = RTC_I2CCyBtldrCommRead(pData, size, count, timeOut);

    #elif(RTC_SCB_MODE_SPI_CONST_CFG)
        status = RTC_SpiCyBtldrCommRead(pData, size, count, timeOut);

    #elif(RTC_SCB_MODE_UART_CONST_CFG)
        status = RTC_UartCyBtldrCommRead(pData, size, count, timeOut);

    #elif(RTC_SCB_MODE_EZI2C_CONST_CFG)
        status = RTC_EzI2CCyBtldrCommRead(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}


/*******************************************************************************
* Function Name: RTC_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls write fucntion of the bootloader communication component for selected
*  mode.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus RTC_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(RTC_SCB_MODE_UNCONFIG_CONST_CFG)
        if(RTC_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = RTC_I2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(RTC_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = RTC_SpiCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(RTC_SCB_MODE_UART_RUNTM_CFG)
        {
            status = RTC_UartCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(RTC_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = RTC_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }
    #elif(RTC_SCB_MODE_I2C_CONST_CFG)
        status = RTC_I2CCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(RTC_SCB_MODE_SPI_CONST_CFG)
        status = RTC_SpiCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(RTC_SCB_MODE_UART_CONST_CFG)
        status = RTC_UartCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(RTC_SCB_MODE_EZI2C_CONST_CFG)
        status = RTC_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (RTC_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_RTC) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */


/* [] END OF FILE */
