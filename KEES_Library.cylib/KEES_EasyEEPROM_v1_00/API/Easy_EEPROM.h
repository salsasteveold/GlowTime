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
#ifndef `$INSTANCE_NAME`_HEADERFILE
#define `$INSTANCE_NAME`_HEADERFILE

#include "cytypes.h"
#include "cyfitter.h" 
#include "CyFlash.h"
#include "CySpc.h"

// total size of the EEPROM available in the device in bytes
#define `$INSTANCE_NAME`_EEPROM_SIZE CYDEV_EE_SIZE

#define `$INSTANCE_NAME`_EEPROM_BASE_ADDRESS CYDEV_EE_BASE
#define `$INSTANCE_NAME`_EEPROM_ROW_SIZE CYDEV_EEPROM_ROW_SIZE
#define `$INSTANCE_NAME`_SPC_BYTE_WRITE_SIZE     0x01u

void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_WriteByte(uint8 value, uint16 address);
uint8 `$INSTANCE_NAME`_ReadByte(uint16 address);
#define `$INSTANCE_NAME`_UpdateTemp() `$INSTANCE_NAME`_Start()

#endif
//[] END OF FILE
