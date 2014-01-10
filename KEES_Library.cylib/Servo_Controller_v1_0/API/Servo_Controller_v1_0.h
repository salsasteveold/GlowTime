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

#include "cytypes.h"
#include "cyfitter.h"
#include "`$INSTANCE_NAME`_Servo_Datapath.h"
#include "`$INSTANCE_NAME`_Servo_Clock.h"
//#include "project.h"

#if !defined(CY_SERVO_CONTROLLER_`$INSTANCE_NAME`_H)
#define CY_SERVO_CONTROLLER_`$INSTANCE_NAME`_H

#define `$INSTANCE_NAME`_OFFSET `$INSTANCE_NAME`_Servo_Datapath_D0
#define `$INSTANCE_NAME`_POSITION `$INSTANCE_NAME`_Servo_Datapath_D1

/***************************************
 *   Function Prototypes
 **************************************/
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void);

void `$INSTANCE_NAME`_SetPosition(uint8 D1);
uint8 `$INSTANCE_NAME`_GetPosition(void);

void `$INSTANCE_NAME`_SetOffset(uint8 D0);
uint8 `$INSTANCE_NAME`_GetOffset(void);

#endif  /* CY_SERVO_CONTROLLER_`$INSTANCE_NAME`_H */


//[] END OF FILE
