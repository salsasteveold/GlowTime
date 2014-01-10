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

//uint8 `$INSTANCE_NAME`_offset;
//uint8 `$INSTANCE_NAME`_position;

void `$INSTANCE_NAME`_Start(void)
{
	`$INSTANCE_NAME`_OFFSET = 64;
	`$INSTANCE_NAME`_POSITION= 127;
	
//	`$INSTANCE_NAME`_Servo_Datapath_WriteD0(`$INSTANCE_NAME`_offset);  // sets initial on time offset to 0.5 ms with a 128 Khz clock
//	`$INSTANCE_NAME`_Servo_Datapath_WriteD1(`$INSTANCE_NAME`_position);  // sets initial servo signal to midrange (1.5 ms) with 128 Khz clock
	`$INSTANCE_NAME`_Servo_Clock_Start(); // just to be sure the 128 Khz clock gets started
	`$INSTANCE_NAME`_Servo_Datapath_Start();
}

void `$INSTANCE_NAME`_Stop(void)
{
	`$INSTANCE_NAME`_Servo_Clock_Stop();
	`$INSTANCE_NAME`_Servo_Datapath_Stop();
}

void `$INSTANCE_NAME`_SetPosition(uint8 D1)
{
	`$INSTANCE_NAME`_POSITION = D1;
	//`$INSTANCE_NAME`_Servo_Datapath_WriteD1(D1);
}

void `$INSTANCE_NAME`_SetOffset(uint8 D0)
{	
	`$INSTANCE_NAME`_OFFSET = D0;
	//`$INSTANCE_NAME`_Servo_Datapath_WriteD0(D0);
}

uint8 `$INSTANCE_NAME`_GetPosition(void)
{
	return `$INSTANCE_NAME`_POSITION;
}

uint8 `$INSTANCE_NAME`_GetOffset(void)
{
	return `$INSTANCE_NAME`_OFFSET;
}

/* [] END OF FILE */
