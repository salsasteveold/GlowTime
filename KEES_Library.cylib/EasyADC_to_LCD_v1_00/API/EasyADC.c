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

#include "`$INSTANCE_NAME`.h"
#include "`$ADC_name`.h"
#include "`$LCD_name`.h"

/******************************************************************************* 
* Function Name: `$INSTANCE_NAME`_Start()
********************************************************************************
*
* Summary:
*  Initialize the associated components
*  
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Reentrance: 
*  Void
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
	// configure the LCD
	`$LCD_name`_Start();
	`$LCD_name`_ClearDisplay();
	
	// configure the ADC
	`$ADC_name`_Start();
	
	return;
}

/******************************************************************************* 
* Function Name: `$INSTANCE_NAME`_Display()
********************************************************************************
*
* Summary:
*  Starts an ADC conversion, waits for the result, grabs the result, optionally 
*  filters the value, then displays the resulting ADC voltage on the LCD
*  
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Reentrance: 
*  Void
*
*******************************************************************************/
void `$INSTANCE_NAME`_Display(void)
{
	char szBuffer[20];
	int32 temp;
	
	#if `$Enable_Filter` == 1
		static uint8 i;
		uint8 j;
		int32 average[`$Filter_Size`];
	#endif
	
	#if `$Enable_Transfer_Function` == 1
		float fVolts;
	#endif
	
	// start the ADC conversion
	`$ADC_name`_StartConvert();
	`$ADC_name`_IsEndConversion(`$ADC_name`_WAIT_FOR_RESULT);
	temp = `$ADC_name`_GetResult32();
	`$ADC_name`_StopConvert();
	
	#if `$Enable_Filter` == 1
		// Filter the results
		average[i] = temp;
		i = ++i % `$Filter_Size`;
		
		temp = 0;
		j = 0;
		do
		{
			temp = temp + average[j];
		}while(j++ < (`$Filter_Size`-1));
		
		temp = temp / `$Filter_Size`;
	#endif
	
	// display the data
	sprintf(szBuffer,"%0.`$Decimal_Places`f v  ", `$ADC_name`_CountsTo_Volts(temp));
	`$LCD_name`_Position(0,0);
	`$LCD_name`_PrintString(szBuffer);
	
	#if `$Enable_Transfer_Function` == 1
		// compute the transfer function
		fVolts = `$ADC_name`_CountsTo_Volts(temp);
		fVolts = `$Transfer_Function`;
		// display the data
		sprintf(szBuffer,"%0.`$Decimal_Places`f `$Unit`  ", fVolts);
		`$LCD_name`_Position(1,0);
		`$LCD_name`_PrintString(szBuffer);
	#endif 
	
	return;
}

/* [] END OF FILE */
