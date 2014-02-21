/*******************************************************************************
* File Name: RTC_SCBCLK.h
* Version 2.0
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_RTC_SCBCLK_H)
#define CY_CLOCK_RTC_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void RTC_SCBCLK_Start(void);
void RTC_SCBCLK_Stop(void);

void RTC_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 RTC_SCBCLK_GetDividerRegister(void);
uint8  RTC_SCBCLK_GetFractionalDividerRegister(void);

#define RTC_SCBCLK_Enable()                         RTC_SCBCLK_Start()
#define RTC_SCBCLK_Disable()                        RTC_SCBCLK_Stop()
#define RTC_SCBCLK_SetDividerRegister(clkDivider, reset)  \
                        RTC_SCBCLK_SetFractionalDividerRegister((clkDivider), 0)
#define RTC_SCBCLK_SetDivider(clkDivider)           RTC_SCBCLK_SetDividerRegister((clkDivider), 1)
#define RTC_SCBCLK_SetDividerValue(clkDivider)      RTC_SCBCLK_SetDividerRegister((clkDivider) - 1, 1)


/***************************************
*             Registers
***************************************/

#define RTC_SCBCLK_DIV_REG    (*(reg32 *)RTC_SCBCLK__REGISTER)
#define RTC_SCBCLK_ENABLE_REG RTC_SCBCLK_DIV_REG

#endif /* !defined(CY_CLOCK_RTC_SCBCLK_H) */

/* [] END OF FILE */
