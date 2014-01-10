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

#if !defined(CY_DATAPATH8_`$INSTANCE_NAME`_H)
#define CY_DATAPATH8_`$INSTANCE_NAME`_H

#define `$INSTANCE_NAME`_D0   (*(reg8 *) `$INSTANCE_NAME`_Datapath_u0__D0_REG)
#define `$INSTANCE_NAME`_D1  (*(reg8 *) `$INSTANCE_NAME`_Datapath_u0__D1_REG)
#define `$INSTANCE_NAME`_A0   (*(reg8 *) `$INSTANCE_NAME`_Datapath_u0__A0_REG)
#define `$INSTANCE_NAME`_A1  (*(reg8 *) `$INSTANCE_NAME`_Datapath_u0__A1_REG)
#define `$INSTANCE_NAME`_F0   (*(reg8 *) `$INSTANCE_NAME`_Datapath_u0__F0_REG)
#define `$INSTANCE_NAME`_F1  (*(reg8 *) `$INSTANCE_NAME`_Datapath_u0__F1_REG)
//#define `$INSTANCE_NAME`_MASK   (*(reg8 *) `$INSTANCE_NAME`_Datapath_u0__MASK_REG)
//#define `$INSTANCE_NAME`_PERIOD  (*(reg8 *) `$INSTANCE_NAME`_Datapath_u0__PERIOD_REG)

/***************************************
 *   Function Prototypes
 **************************************/
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_WriteA0(uint8 A0);
void `$INSTANCE_NAME`_WriteA1(uint8 A1);
void `$INSTANCE_NAME`_WriteD0(uint8 D0);
void `$INSTANCE_NAME`_WriteD1(uint8 D1);
void `$INSTANCE_NAME`_WriteF0(uint8 F0);
void `$INSTANCE_NAME`_WriteF1(uint8 F1);
//void `$INSTANCE_NAME`_WriteMASK(uint8 MASK);
//void `$INSTANCE_NAME`_WritePERIOD(uint8 PERIOD);

#endif  /* CY_DATAPATH8_`$INSTANCE_NAME`_H */

//[] END OF FILE
