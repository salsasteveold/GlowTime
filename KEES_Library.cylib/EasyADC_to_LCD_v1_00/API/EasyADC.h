/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef `$INSTANCE_NAME`_EASYADC
#define `$INSTANCE_NAME`_EASYADC

// default includes
#include "cytypes.h"
#include "cyfitter.h"
#include <device.h>
#if `$Enable_Transfer_Function` == 1
	#include <math.h>
#endif

// needed for sprintf
#include <stdio.h>

// customizer parameters
// ADC Instance name: `$ADC_name`
// LCD Instance name: `$LCD_name`
// Enable filter: `$Enable_Filter`
// Number of samples in the filter: `$Filter_Size`
// Number of decimal places to display: `$Decimal_Places`

// starts the associated hardware
void `$INSTANCE_NAME`_Start(void);

// gets the ADC result, converts it to a voltage and displays it on the LCD
void `$INSTANCE_NAME`_Display(void);


#endif 

//[] END OF FILE
