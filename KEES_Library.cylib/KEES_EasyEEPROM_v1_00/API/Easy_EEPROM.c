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

// total size of the EEPROM available in the device in bytes
//#define `$INSTANCE_NAME`_EEPROM_SIZE CYDEV_EE_SIZE

//#define `$INSTANCE_NAME`_EEPROM_BASE_ADDRESS CYDEV_EE_BASE
//#define `$INSTANCE_NAME`_EEPROM_ROW_SIZE

void `$INSTANCE_NAME`_Start(void)
{   
    //  The EEPROM requires  the temperature of the device in order to write to the EEPROM efficiently
    // if you are concerned that the temperature of the device has changed by more than 5 degrees
    // since this function was initially called, you can call it again to update the temperature.
    // this is only needed when writing to the EEPROM.
    
    // enable power to the EEPROM.  if you dont do this, you will not be able to read the EEPROM
    #if (CY_PSOC3 || CY_PSOC5LP)
    CyEEPROM_Start();
    #endif
    
    // check the temperature of the device
    CySetTemp();
}

void `$INSTANCE_NAME`_WriteByte(uint8 value, uint16 address)
{
    uint8 row, offset;
    cystatus status;
    
    if(address < `$INSTANCE_NAME`_EEPROM_SIZE)
    {
        // calculate the row, and offset within the row
        row = address / `$INSTANCE_NAME`_EEPROM_ROW_SIZE;
        offset = address - ((uint16)row*(uint16)`$INSTANCE_NAME`_EEPROM_ROW_SIZE);
        
        // Turn on the SPC
        CySpcStart();
        
        // lock the spc to prevent some other process from using it
        CySpcLock();

        // loads a byte of data into the temporary SPC write buffer.  Write the byte into the proper offset
        // in the temporary SPC buffer.  The offset is an artifact of the "row" oriented write operations of
        // our EEPROM and flash.  The load multibyte SPC function loads the temporary "row" with the data we intend
        // to write.  later, this temporary row is written into the proper "row" with another function call.
        // to place the byte where we want it, we have to calculate the destination row, and offset within that
        // row.
        if(CySpcLoadMultiByte(CY_SPC_FIRST_EE_ARRAYID, offset, &value, `$INSTANCE_NAME`_SPC_BYTE_WRITE_SIZE) == CYRET_STARTED)
        {
            while(CY_SPC_BUSY)
            {
                /* Wait until SPC becomes idle */
            }

            // this is where we tell the SPC to write the write the temporary row into the EEPROM.
            if(CySpcWriteRow(CY_SPC_FIRST_EE_ARRAYID, row, dieTemperature[0], dieTemperature[1]) == CYRET_STARTED)
            {
                while(CY_SPC_BUSY)
                {
                    /* Wait until SPC becomes idle */
                }
            }
        }

        /* Unlock the SPC so someone else can use it. */
        CySpcUnlock();
            
            
        // turn off the SPC
        CySpcStop();
    }
}

uint8 `$INSTANCE_NAME`_ReadByte(uint16 address)
{
    return (uint8)((reg8 *) `$INSTANCE_NAME`_EEPROM_BASE_ADDRESS)[address];
}

void `$INSTANCE_NAME`_Stop(void)
{      
    // turn off the EEPROM in the power manager.  you will no longer be able to read the contets of the eerprom
    #if (CY_PSOC3 || CY_PSOC5LP)
    CyEEPROM_Stop();
    #endif
}

/* [] END OF FILE */
