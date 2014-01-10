/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the API source code for the DFB component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2011-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

static void `$INSTANCE_NAME`_LoadReg32(reg32 regAddress[], const uint32 source[], uint8 count);
static void `$INSTANCE_NAME`_ZeroReg32(reg32 regAddress[], uint8 count);

uint8 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_LoadReg32
********************************************************************************
* 
* Summary:
*  This function loads initial values/data to appropriate registers.
*
* Parameters:
*  reg32 regAddress[]: register address;
*  const uint32 source[]: data for load;
*  uint8 count: number of 32-bit registers for load.
*
* Return:
*  None.
*
* Note:
*  Data loads starts from "regAddress" address and affects on "count" numbers of
*  successive registers.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_LoadReg32(reg32 regAddress[], const uint32 source[], uint8 count)
{
    uint8 i = 0u;
    
    while (count > 0u)
    {
        CY_SET_REG32(& regAddress[i], source[i]);
        count--;
        i++;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ZeroReg32
********************************************************************************
* 
* Summary:
*  This function zeroize registers.
*
* Parameters:
*  reg32 regAddress[]: register address;
*  uint8 count: number of 32-bit registers for zeroing.
*
* Return:
*  None.
*
* Note:
*  Zeroing starts from "regAddress" address and affects on "count" numbers of
*  successive registers.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_ZeroReg32(reg32 regAddress[], uint8 count)
{
    uint8 i = 0u;
    
    while (count > 0u)
    {
        CY_SET_REG32(& regAddress[i], 0u);
        count--;
        i++;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
* 
* Summary:
*  This function initializes or restores default the DFB component configuration
*  provided with customizer:
*   powers on DFB(PM_ACT_CFG), power on the RAM(DFB_RAM_EN),
*   moves CSA/CSB/FSM/DataA/DataB/ACU data to the DFB ram using an 8051/ARM
*   core,
*   changes RAM DIR to DFB,
*   sets interrupt mode,
*   sets DMA mode,
*   sets DSI outputs,
*   clears all semaphore bits an pending interrupts.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  All registers will be reset to their initial values. This will reinitializes
*  the component. This function turns off Run bit and enables power to the DFB
*  block.
*  Program loading takes ~6 ms.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Powers on DFB block */
    `$INSTANCE_NAME`_PM_ACT_CFG_REG |= `$INSTANCE_NAME`_PM_ACT_MSK;
    /* Enables DFB block in Alternate Active (Standby) mode */
    `$INSTANCE_NAME`_PM_STBY_CFG_REG |= `$INSTANCE_NAME`_PM_STBY_MSK;

    CyExitCriticalSection(enableInterrupts);

    /* Turns off Run Bit */
    `$INSTANCE_NAME`_CR_REG &= (uint8) (~`$INSTANCE_NAME`_RUN_MASK);
    /* Powers up the DFB RAMS */
    `$INSTANCE_NAME`_RAM_EN_REG = `$INSTANCE_NAME`_RAM_DIR_BUS;
    /* Puts DFB RAM on the bus */
    `$INSTANCE_NAME`_RAM_DIR_REG = `$INSTANCE_NAME`_RAM_DIR_BUS;

    /* Clears all DFB RAM */
    `$INSTANCE_NAME`_ZeroReg32(`$INSTANCE_NAME`_DA_RAM_PTR, `$INSTANCE_NAME`_DA_RAM_SIZE);
    `$INSTANCE_NAME`_ZeroReg32(`$INSTANCE_NAME`_DB_RAM_PTR, `$INSTANCE_NAME`_DB_RAM_SIZE);
    `$INSTANCE_NAME`_ZeroReg32(`$INSTANCE_NAME`_CSA_RAM_PTR, `$INSTANCE_NAME`_CSA_RAM_SIZE);
    `$INSTANCE_NAME`_ZeroReg32(`$INSTANCE_NAME`_CSB_RAM_PTR, `$INSTANCE_NAME`_CSB_RAM_SIZE);
    `$INSTANCE_NAME`_ZeroReg32(`$INSTANCE_NAME`_ACU_RAM_PTR, `$INSTANCE_NAME`_ACU_RAM_SIZE);
    `$INSTANCE_NAME`_ZeroReg32(`$INSTANCE_NAME`_CFSM_RAM_PTR, `$INSTANCE_NAME`_CFSM_RAM_SIZE);

    /* Writes DFB RAMs */
    /* Control Store RAMs */
    #if (`$INSTANCE_NAME`_OPTIMIZE_ASSEMBLY)
        `$INSTANCE_NAME`_LoadReg32(`$INSTANCE_NAME`_CSA_RAM_PTR, `$INSTANCE_NAME`_cstoreA,
                                    `$INSTANCE_NAME`_CSA_RAM_SIZE_CUR);
        `$INSTANCE_NAME`_LoadReg32(`$INSTANCE_NAME`_CSB_RAM_PTR, `$INSTANCE_NAME`_cstoreB,
                                    `$INSTANCE_NAME`_CSB_RAM_SIZE_CUR);
    #else
        `$INSTANCE_NAME`_LoadReg32(`$INSTANCE_NAME`_CSA_RAM_PTR, `$INSTANCE_NAME`_control,
                                    `$INSTANCE_NAME`_CSA_RAM_SIZE_CUR);
        `$INSTANCE_NAME`_LoadReg32(`$INSTANCE_NAME`_CSB_RAM_PTR, `$INSTANCE_NAME`_control,
                                    `$INSTANCE_NAME`_CSB_RAM_SIZE_CUR);
    #endif /* `$INSTANCE_NAME`_OPTIMIZE_ASSEMBLY */

    /* Loads initial data to Data RAMs */
    `$INSTANCE_NAME`_LoadReg32(`$INSTANCE_NAME`_DA_RAM_PTR, `$INSTANCE_NAME`_data_a, `$INSTANCE_NAME`_DA_RAM_SIZE_CUR);
    `$INSTANCE_NAME`_LoadReg32(`$INSTANCE_NAME`_DB_RAM_PTR, `$INSTANCE_NAME`_data_b, `$INSTANCE_NAME`_DB_RAM_SIZE_CUR);
    /* Loads initial data to ACU RAM */
    `$INSTANCE_NAME`_LoadReg32(`$INSTANCE_NAME`_ACU_RAM_PTR, `$INSTANCE_NAME`_acu, `$INSTANCE_NAME`_ACU_RAM_SIZE_CUR);
    /* Loads initial data to CFSM RAM */
    `$INSTANCE_NAME`_LoadReg32(`$INSTANCE_NAME`_CFSM_RAM_PTR, `$INSTANCE_NAME`_cfsm,
                                `$INSTANCE_NAME`_CFSM_RAM_SIZE_CUR);

    /* Takes DFB RAM off the bus */
    `$INSTANCE_NAME`_RAM_DIR_REG = `$INSTANCE_NAME`_RAM_DIR_DFB;

    /* Sets up interrupt and DMA events */
    `$INSTANCE_NAME`_SetInterruptMode(`$INSTANCE_NAME`_INIT_INTERRUPT_MODE);
    `$INSTANCE_NAME`_SetDMAMode(`$INSTANCE_NAME`_INIT_DMA_MODE);

    /* Sets up internal signals, which will be mapped to the DSI outputs */
    `$INSTANCE_NAME`_SetOutput1Source(`$INSTANCE_NAME`_INIT_OUT1_SOURCE);
    `$INSTANCE_NAME`_SetOutput2Source(`$INSTANCE_NAME`_INIT_OUT2_SOURCE);

    /* Clears any pending interrupts and semaphore bits */
    `$INSTANCE_NAME`_SR_REG = 0xFFu;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  This function enables the DFB hardware block, sets the DFB run bit and powers
*  on the DFB block.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Powers on DFB block */
    `$INSTANCE_NAME`_PM_ACT_CFG_REG |= `$INSTANCE_NAME`_PM_ACT_MSK;
    /* Enables DFB block in Alternate Active (Standby) mode */
    `$INSTANCE_NAME`_PM_STBY_CFG_REG |= `$INSTANCE_NAME`_PM_STBY_MSK;

    CyExitCriticalSection(enableInterrupts);
    
    /* Powers up the DFB RAMS */
    `$INSTANCE_NAME`_RAM_EN_REG = `$INSTANCE_NAME`_RAM_DIR_BUS;
    /* Turns on Run Bit */
    `$INSTANCE_NAME`_CR_REG |= `$INSTANCE_NAME`_RUN_MASK;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  This function initializes and enables the DFB component using the DFB_Init()
*  and DFB_Enable() functions.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  `$INSTANCE_NAME`_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    if (`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }

    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  This function turns off the run bit. If DMA control is used to feed the
*  channels, function allows arguments to turn off one of the TD channels off.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Disables power to the DFB Core.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Powers off DFB */
    `$INSTANCE_NAME`_PM_ACT_CFG_REG &= (uint8) (~`$INSTANCE_NAME`_PM_ACT_MSK);
    /* Disables DFB block in Alternate Active (Standby) mode */
    `$INSTANCE_NAME`_PM_STBY_CFG_REG &= (uint8) (~`$INSTANCE_NAME`_PM_STBY_MSK);

    CyExitCriticalSection(enableInterrupts);

    /* Turns off Run Bit */
    `$INSTANCE_NAME`_CR_REG &= (uint8) (~`$INSTANCE_NAME`_RUN_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Pause
********************************************************************************
*
* Summary:
*  This function pauses DFB and enables writing to the DFB RAM:
*   turns off the Run bit,
*   connects the DFB RAM to the data bus,
*   clears the DFB run bit and passes the control of all DFB RAMs onto bus.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Pause(void) `=ReentrantKeil($INSTANCE_NAME . "_Pause")`
{
     /* Turns off Run Bit */
    `$INSTANCE_NAME`_CR_REG &= (uint8) (~`$INSTANCE_NAME`_RUN_MASK);
     /* Puts DFB RAM on the bus */
    `$INSTANCE_NAME`_RAM_DIR_REG = `$INSTANCE_NAME`_RAM_DIR_BUS;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Resume
********************************************************************************
*
* Summary:
*  This function disables writing to the DFB RAM, clear any pending interrupts,
*  disconnects the DFB RAM from the data bus, and runs the DFB.
*  It passes the control of all DFB RAM to the DFB and then sets the run bit.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Resume(void) `=ReentrantKeil($INSTANCE_NAME . "_Resume")`
{
    /* Takes DFB RAM off the bus */
    `$INSTANCE_NAME`_RAM_DIR_REG = `$INSTANCE_NAME`_RAM_DIR_DFB;
    /* Clears any pending interrupts */
    `$INSTANCE_NAME`_SR_REG = 0xFFu;
    /* Turns on Run Bit */
    `$INSTANCE_NAME`_CR_REG |= `$INSTANCE_NAME`_RUN_MASK;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetCoherency
********************************************************************************
*
* Summary:
*  This function sets the coherency key to low/mid/high byte based on the
*  coherencyKey parameter that is passed to the DFB.
*  Function allows you to select which of the 3 bytes of each of the STAGEA,
*  STAGEB, HOLDA and HOLDB will be used as the Key Coherency Byte. Coherency
*  refers to the HW added to this block to protect against malfunctions of the
*  block in cases where register fields are wider than the bus access, leaving
*  intervals in time when fields are partially written/read (incoherent). The
*  Key Coherency Byte is the SW's way of telling the HW which byte of the field
*  will be written/read last when an update to the field is desired. When the
*  Key byte is written/read, the field is flagged coherent. If any other byte
*  is written or read, the field is flagged incoherent.
*
* Parameters:
*  uint8 coherencyKeyByte: specifies bits in the DFB Coherency Register.
*   Sets the Key Coherency Byte of the Staging A register
*    Define                             Description
*     `$INSTANCE_NAME`_STGA_KEY_LOW      Key Byte is low byte.
*     `$INSTANCE_NAME`_STGA_KEY_MID      Key Byte is med byte.
*     `$INSTANCE_NAME`_STGA_KEY_HIGH     Key Byte is high byte.
*   Sets the Key Coherency Byte of the Staging B register
*    Define                             Description
*     `$INSTANCE_NAME`_STGB_KEY_LOW      Key Byte is low byte.
*     `$INSTANCE_NAME`_STGB_KEY_MID      Key Byte is med byte.
*     `$INSTANCE_NAME`_STGB_KEY_HIGH     Key Byte is high byte.
*   Sets the Key Coherency Byte of the Holding A register
*    Define                             Description
*     `$INSTANCE_NAME`_HOLDA_KEY_LOW     Key Byte is low byte.
*     `$INSTANCE_NAME`_HOLDA_KEY_MID     Key Byte is med byte.
*     `$INSTANCE_NAME`_HOLDA_KEY_HIGH    Key Byte is high byte.
*   Sets the Key Coherency Byte of the Holding B register
*    Define                             Description
*     `$INSTANCE_NAME`_HOLDB_KEY_LOW     Key Byte is low byte.
*     `$INSTANCE_NAME`_HOLDB_KEY_MID     Key Byte is med byte.
*     `$INSTANCE_NAME`_HOLDB_KEY_HIGH    Key Byte is high byte.
*
* Return:
*  None.
*
* Note:
*  Default key byte configuration for Staging A and B, and Holding A and B
*  registers is high byte.
*
* Side Effects:
*  Coherency affects data loading using the LoadInputValue() function and
*  data retrieval using the GetOutputValue() function.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetCoherency(uint8 coherencyKeyByte) `=ReentrantKeil($INSTANCE_NAME . "_SetCoherency")`
{
    `$INSTANCE_NAME`_COHER_REG = coherencyKeyByte;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDalign
********************************************************************************
*
* Summary:
*  This feature allows 9- to 16-bit input and output samples to travel as 16-bit
*  values on the AHB bus. These bits when set high cause an 8-bit shift in the
*  data to all access of the corresponding Staging and Holding registers.
*  Because the DFB datapath is inherently MSB aligned, it is convenient to the
*  System SW to align values on bits 23:8 of the Staging and Holding register
*  to bits 15:0 of the bus. A read of this register produces the last value
*  written to this register.
*
* Parameters:
*  uint8 dalignKeyByte: specifies bits in the DFB Data Alignment Register.
*   Shifts the write left by a byte.
*    Define                               Description
*     `$INSTANCE_NAME`_STGA_DALIGN_LOW     Writes normally.
*     `$INSTANCE_NAME`_STGA_DALIGN_HIGH    Writes shifted left by 8-bits.
*   Shifts the write left by a byte.
*    Define                               Description
*     `$INSTANCE_NAME`_STGB_DALIGN_LOW     Writes normally.
*     `$INSTANCE_NAME`_STGB_DALIGN_HIGH    Writes shifted left by 8-bits.
*   Shifts the read right by a byte.
*    Define                               Description
*     `$INSTANCE_NAME`_HOLDA_DALIGN_LOW     Reads normally.
*     `$INSTANCE_NAME`_HOLDA_DALIGN_HIGH    Reads shifted right by 8-bits.
*   Shifts the read right by a byte.
*    Define                               Description
*     `$INSTANCE_NAME`_HOLDB_DALIGN_LOW     Reads normally.
*     `$INSTANCE_NAME`_HOLDB_DALIGN_HIGH    Reads shifted right by 8-bits.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetDalign(uint8 dalignKeyByte) `=ReentrantKeil($INSTANCE_NAME . "_SetDalign")`
{
    `$INSTANCE_NAME`_DALIGN_REG = dalignKeyByte;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_LoadDataRAMA
********************************************************************************
*
* Summary:
*  This function loads data to DFB RAM A memory.
*
* Parameters:
*  const int32 ptr[]: pointer on data source for load;
*  uint32     addr[]: start address for loading the data in DFB RAM A;
*  uint8        size: number of data words to load.
*
* Return:
*  `$INSTANCE_NAME`_SUCCESS - Loading data is successful.
*  `$INSTANCE_NAME`_ADDRESS_OUT_OF_RANGE - error code, indicates that the
*  address is out of range.
*  `$INSTANCE_NAME`_DATA_OUT_OF_RANGE - error code, indicates a data overflow
*  error.
*
* Side Effects:
*  This API doesn't stop the DFB if it is already started. Hence, recommended
*  method is to call Init() API, then LoadDataRAMA() API and then Enable() API.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_LoadDataRAMA(const int32 ptr[], uint32 addr[], uint8 size)
     `=ReentrantKeil($INSTANCE_NAME . "_LoadDataRAMA")`
{
    uint8 result = `$INSTANCE_NAME`_SUCCESS;
    uint8 i = 0u;

    if (((& addr[0u]) < `$INSTANCE_NAME`_DA_RAM_PTR) || ((& addr[0u]) > `$INSTANCE_NAME`_DA_RAM_LAST_ELEM_PTR))
    {
        result = `$INSTANCE_NAME`_ADDRESS_OUT_OF_RANGE;
    }
    else if ((size == 0u) || ((& addr[size - 1u]) > `$INSTANCE_NAME`_DA_RAM_LAST_ELEM_PTR))
    {
        result = `$INSTANCE_NAME`_DATA_OUT_OF_RANGE;
    }
    else
    {
        /* Puts DFB RAM on the bus */
        `$INSTANCE_NAME`_RAM_DIR_REG |= `$INSTANCE_NAME`_RAM_DPA_DIR;
        while (size > 0u)
        {
            CY_SET_REG32((reg32 *) (& addr[i]), (uint32) ptr[i]);
            size--;            
            i++;
        }
        /* Takes DFB RAM off the bus */
        `$INSTANCE_NAME`_RAM_DIR_REG &= (uint8) (~`$INSTANCE_NAME`_RAM_DPA_DIR);
    }

    return (result);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_LoadDataRAMB
********************************************************************************
*
* Summary:
*  This function loads data to DFB RAM B memory.
*
* Parameters:
*  const int32 ptr[]: pointer on data source for load;
*  uint32     addr[]: start addres for loading the data in DFB RAM B;
*  uint8        size: number of data words to load.
*
* Return:
*  `$INSTANCE_NAME`_SUCCESS - Loading data is successful.
*  `$INSTANCE_NAME`_ADDRESS_OUT_OF_RANGE - error code, indicates that the
*  address is out of range.
*  `$INSTANCE_NAME`_DATA_OUT_OF_RANGE - error code, indicates data overflow
*  error.
*
* Side Effects:
*  This API doesn't stop the DFB if it is already started. Hence, recommended
*  method is to call Init() API, then LoadDataRAMB() API and then Enable() API.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_LoadDataRAMB(const int32 ptr[], uint32 addr[], uint8 size)
     `=ReentrantKeil($INSTANCE_NAME . "_LoadDataRAMB")`
{
    uint8 result = `$INSTANCE_NAME`_SUCCESS;
    uint8 i = 0u;

    if (((& addr[0u]) < `$INSTANCE_NAME`_DB_RAM_PTR) || ((& addr[0u]) > `$INSTANCE_NAME`_DB_RAM_LAST_ELEM_PTR))
    {
        result = `$INSTANCE_NAME`_ADDRESS_OUT_OF_RANGE;
    }
    else if ((size == 0u) || ((& addr[size - 1u]) > `$INSTANCE_NAME`_DB_RAM_LAST_ELEM_PTR))
    {
        result = `$INSTANCE_NAME`_DATA_OUT_OF_RANGE;
    }
    else
    {
        /* Puts DFB RAM on the bus */
        `$INSTANCE_NAME`_RAM_DIR_REG |= `$INSTANCE_NAME`_RAM_DPB_DIR;
        while (size > 0u)
        {
            CY_SET_REG32((reg32 *) (& addr[i]), (uint32) ptr[i]);
            size--;
            i++;
        }
        /* Takes DFB RAM off the bus */
        `$INSTANCE_NAME`_RAM_DIR_REG &= (uint8) (~`$INSTANCE_NAME`_RAM_DPB_DIR);
    }

    return (result);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_LoadInputValue
********************************************************************************
*
* Summary:
*  This function loads input value in selected channel.
*
* Parameters:
*  channel: Use either `$INSTANCE_NAME`_CHANNEL_A (1) or
*           `$INSTANCE_NAME`_CHANNEL_B (0) asarguments to the function;
*  sample: The 24-bit, right justified input sample.
*
* Return:
*  None.
*
* Note:
*  The write order is important. When the high byte is loaded, the DFB sets
*  the input ready bit. Pay attention to byte order if coherency or data
*  alignment is changed.
*
*******************************************************************************/
void `$INSTANCE_NAME`_LoadInputValue(uint8 channel, int32 sample) `=ReentrantKeil($INSTANCE_NAME . "_LoadInputValue")`
{
    uint32 value;

    value = (uint32) sample;

    /* Writes the STAGE-"H" reg last as it signals a complete wrote to the DFB.*/
    if (channel == `$INSTANCE_NAME`_CHANNEL_A)
    {
        `$INSTANCE_NAME`_STAGEA_REG  = (uint8) value;
        `$INSTANCE_NAME`_STAGEAM_REG = (uint8) (value >> 8u);
        `$INSTANCE_NAME`_STAGEAH_REG = (uint8) (value >> 16u);
    }
    else if (channel == `$INSTANCE_NAME`_CHANNEL_B)
    {
        `$INSTANCE_NAME`_STAGEB_REG  = (uint8) value;
        `$INSTANCE_NAME`_STAGEBM_REG = (uint8) (value >> 8u);
        `$INSTANCE_NAME`_STAGEBH_REG = (uint8) (value >> 16u);
    }
    else
    {
        /* No value is loaded on bad channel input */
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOutputValue
********************************************************************************
*
* Summary:
*  This function gets the value from one of the DFB Output Holding Registers.
*
* Parameters:
*  channel: Use either `$INSTANCE_NAME`_CHANNEL_A (1) or
*           `$INSTANCE_NAME`_CHANNEL_B (0) as arguments to the function.
*
* Return:
*  The current output value in the chosen channel's holding register. This is
*  a 24-bit number packed into the least-significant 3 bytes of the output word
*  or 0xFF000000 for invalid channel numbers
*
* Note:
*  Because of the architecture of the DFB, any value read from the Holding A or
*  B registers will be MSB aligned unless shifted otherwise by the Datapath
*  shifter. Pay attention to byte order if coherency or data alignment is
*  changed.
*
*******************************************************************************/
int32 `$INSTANCE_NAME`_GetOutputValue(uint8 channel) `=ReentrantKeil($INSTANCE_NAME . "_GetOutputValue")`
{
    uint8 data0;
    uint8 data1;
    uint8 data2;
    uint8 data3;
    uint32 output;

    /* Reads the HOLD-"H" reg last as it signals a complete read to the DFB.*/
    if (channel == `$INSTANCE_NAME`_CHANNEL_A)
    {
        data0 = `$INSTANCE_NAME`_HOLDA_REG;
        data1 = `$INSTANCE_NAME`_HOLDAM_REG;
        data2 = `$INSTANCE_NAME`_HOLDAH_REG;
        data3 = ((data2 & 0x80u) == 0x80u) ? 0xFFu : 0x00u;
    }
    else if (channel == `$INSTANCE_NAME`_CHANNEL_B)
    {
        data0 = `$INSTANCE_NAME`_HOLDB_REG;
        data1 = `$INSTANCE_NAME`_HOLDBM_REG;
        data2 = `$INSTANCE_NAME`_HOLDBH_REG;
        data3 = ((data2 & 0x80u) == 0x80u) ? 0xFFu : 0x00u;
    }
    else
    {
        data0 = 0x00u;
        data1 = 0x00u;
        data2 = 0x00u;
        data3 = 0xFFu;
    }

    output = ((((((uint32) data3 << 8u) | data2) << 8u) | data1) << 8u) | data0;

    return ((int32) output);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMode
********************************************************************************
*
* Summary:
*  This function assigns the events which will trigger a DFB interrupt to be
*  triggered.
*
* Parameters:
*  events: Bits [0:5] of events represent the events that trigger DFB
*          interrupts.
*    Define                    Description
*     `$INSTANCE_NAME`_HOLDA    Interrupt is generated each time new valid data
*                               is written into the output Holding register A;
*     `$INSTANCE_NAME`_HOLDB    Interrupt is generated each time new valid data
*                               is written into the output Holding register B;
*     `$INSTANCE_NAME`_SEMA0    Interrupt is generated each time a '1' is
*                               written into the semaphore register bit 0;
*     `$INSTANCE_NAME`_SEMA1    Interrupt is generated each time a '1' is
*                               written into the semaphore register bit 1;
*     `$INSTANCE_NAME`_SEMA2    Interrupt is generated each time a '1' is
*                               written into the semaphore register bit 2.
*
* Return:
*  None.
*
* Note:
*  Do not configure semaphore 0 and semaphore 1 for both a DMA request and for
*  an interrupt event. This is because, after one clock cycle, the system
*  automatically clears any semaphore that triggered a DMA request.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetInterruptMode(uint8 events) `=ReentrantKeil($INSTANCE_NAME . "_SetInterruptMode")`
{
    `$INSTANCE_NAME`_INT_CTRL_REG = events & `$INSTANCE_NAME`_EVENT_MASK;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptSource
********************************************************************************
*
* Summary:
*  This function looks at the `$INSTANCE_NAME`_SR register to see which
*  interrupt sources have been triggered.
*
* Parameters:
*  None.
*
* Return:
*  uint8 value in which bits [0:5] of represent the events that triggered the
*  DFB interrupt.
*    Define                    Description
*     `$INSTANCE_NAME`_HOLDA    Holding register A is a source of the current
*                               interrupt;
*     `$INSTANCE_NAME`_HOLDB    Holding register B is a source of the current
*                               interrupt;
*     `$INSTANCE_NAME`_SEMA0    Semaphore register bit 0 is a source of the
*                               current interrupt;
*     `$INSTANCE_NAME`_SEMA1    Semaphore register bit 1 is a source of the
*                               current interrupt;
*     `$INSTANCE_NAME`_SEMA2    Semaphore register bit 2 is a source of the
*                               current interrupt.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetInterruptSource(void) `=ReentrantKeil($INSTANCE_NAME . "_GetInterruptSource")`
{
    /* Shifts the event bits down to [0:5] */
    return ((uint8) (`$INSTANCE_NAME`_SR_REG >> `$INSTANCE_NAME`_SR_EVENT_SHIFT));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearInterrupt
********************************************************************************
*
* Summary:
*  This function clears the interrupt request.
*
* Parameters:
*  interruptMask: Mask of interrupts to clear.
*    Define                    Description
*     `$INSTANCE_NAME`_HOLDA    Clear interrupt from Holding register A.
*                               (Reading the Holding register A also clears this
*                                bit);
*     `$INSTANCE_NAME`_HOLDB    Clear interrupt from Holding register B.
*                               (Reading the Holding register B also clears this
*                                bit);
*     `$INSTANCE_NAME`_SEMA0    Clear interrupt from semaphore register bit 0;
*     `$INSTANCE_NAME`_SEMA1    Clear interrupt from semaphore register bit 1;
*     `$INSTANCE_NAME`_SEMA2    Clear interrupt from semaphore register bit 2.
*
* Return:
*  None.
*
* Note:
*  Clearing semaphore interrupts also clears semaphore bits.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ClearInterrupt(uint8 interruptMask) `=ReentrantKeil($INSTANCE_NAME . "_ClearInterrupt")`
{
    `$INSTANCE_NAME`_SR_REG &= (uint8) (interruptMask << `$INSTANCE_NAME`_SR_EVENT_SHIFT);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDMAMode
********************************************************************************
*
* Summary:
*  This function assigns the events that trigger a DMA request for the DFB.
*  Two different DMA requests that can be triggered.
*
* Parameters:
*  events: A set of 4 bits which configure what event, if any, triggers a DMA
*          request for the DFB.
*   DMA Request 1:
*    Define                                 Description
*    `$INSTANCE_NAME`_DMAREQ1_DISABLED       No request will be generated;
*    `$INSTANCE_NAME`_DMAREQ1_HOLDA          Output value ready in the holding
                                             register on channel A;
*    `$INSTANCE_NAME`_DMAREQ1_SEM0           Semaphore 0;
*    `$INSTANCE_NAME`_DMAREQ1_SEM1           Sempahore 1.
*   DMA Request 2:
*    Define                                 Description
*    `$INSTANCE_NAME`_DMAREQ2_DISABLED       No request will be generated;
*    `$INSTANCE_NAME`_DMAREQ2_HOLDB          Output value ready in the holding
                                             register on channel B;
*    `$INSTANCE_NAME`_DMAREQ2_SEM0           Semaphore 0;
*    `$INSTANCE_NAME`_DMAREQ2_SEM1           Sempahore 1.
*
* Return:
*  None.
*
* Note:
*  Do not configure semaphore 0 and semaphore 1 for both a DMA request and for
*  an interrupt event. This is because, after one clock cycle, the system
*  automatically clears any semaphore that triggered a DMA request.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetDMAMode(uint8 events) `=ReentrantKeil($INSTANCE_NAME . "_SetDMAMode")`
{
    `$INSTANCE_NAME`_DMA_CTRL_REG = events & `$INSTANCE_NAME`_DMA_CTRL_MASK;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSemaphore
********************************************************************************
*
* Summary:
*  This function sets semaphores specified with a 1.
*
* Parameters:
*  mask: mask specifying the bits to set.
*    Define                          Description
*     `$INSTANCE_NAME`_SEMAPHORE0     Semaphore 0;
*     `$INSTANCE_NAME`_SEMAPHORE1     Semaphore 1;
*     `$INSTANCE_NAME`_SEMAPHORE2     Semaphore 2.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetSemaphores(uint8 mask) `=ReentrantKeil($INSTANCE_NAME . "_SetSemaphores")`
{
    `$INSTANCE_NAME`_SEM_REG = (uint8) ((mask & `$INSTANCE_NAME`_SEM_MASK) << `$INSTANCE_NAME`_SEM_ENABLE_SHIFT) |
                                 `$INSTANCE_NAME`_SEM_MASK;
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_GetSempahores
********************************************************************************
*
* Summary:
*  This function checks the current status of the DFB semaphores and return that
*  value.
*
* Parameters:
*  None.
*
* Return:
*  uint8 value between 0 and 7 where bit 0 represents semaphore 0 and so on.
*    Define                          Description
*     `$INSTANCE_NAME`_SEMAPHORE0     Semaphore 0;
*     `$INSTANCE_NAME`_SEMAPHORE1     Semaphore 1;
*     `$INSTANCE_NAME`_SEMAPHORE2     Semaphore 2.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetSemaphores(void) `=ReentrantKeil($INSTANCE_NAME . "_GetSemaphores")`
{
    /* Masked the valide bits in case the reserved bits in SEM_REG [4 and 7] get used for something */
    return (`$INSTANCE_NAME`_SEM_REG & `$INSTANCE_NAME`_SEM_MASK);
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_ClearSemaphore
********************************************************************************
*
* Summary:
*  This function clears semaphore bits specified with a 1.
*
* Parameters:
*  mask: mask specifying the bits to clear.
*    Define                          Description
*     `$INSTANCE_NAME`_SEMAPHORE0     Semaphore 0;
*     `$INSTANCE_NAME`_SEMAPHORE1     Semaphore 1;
*     `$INSTANCE_NAME`_SEMAPHORE2     Semaphore 2.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ClearSemaphores(uint8 mask) `=ReentrantKeil($INSTANCE_NAME . "_ClearSemaphores")`
{
    /* Writes the semaphore register: Clears the semaphores masked */
    `$INSTANCE_NAME`_SEM_REG = (uint8) ((mask & `$INSTANCE_NAME`_SEM_MASK) << `$INSTANCE_NAME`_SEM_ENABLE_SHIFT);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOutput1Source
********************************************************************************
*
* Summary:
*  This function allows you to choose which internal signal will be mapped to
*  the DSI output 1.
*
* Parameters:
*  source: internal signal which is mapped to the output global signal 1.
*   Signal                      Description
*    `$INSTANCE_NAME`_DFB_RUN    DFB RUN Bit. This is the same bit as the RUN
*                                bit in the DFB_CR register.
*    `$INSTANCE_NAME`_SEM0       Semaphore Bit 0.
*    `$INSTANCE_NAME`_SEM1       Semaphore Bit 1.
*    `$INSTANCE_NAME`_DFB_INTR   DFB Interrupt. This is the same signal as the
*                                primary DFB Interrupt output signal.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOutput1Source(uint8 source) `=ReentrantKeil($INSTANCE_NAME . "_SetOutput1Source")`
{
    `$INSTANCE_NAME`_DSI_CTRL_REG = (`$INSTANCE_NAME`_DSI_CTRL_REG & `$INSTANCE_NAME`_DFB_GBL1_OUT_MASK) | source;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOutput2Source
********************************************************************************
*
* Summary:
*  This function allows you to choose which internal signal will be mapped to
*  the DSI output 2.
*
* Parameters:
*  source: internal signal which is mapped to the output global signal 2.
*   Signal                      Description
*    `$INSTANCE_NAME`_SEM2       Semaphore Bit 2.
*    `$INSTANCE_NAME`_DPSIGN     Datapath Sign. This signal asserts anytime the
*                                 output of the ALU in the Datapath unit is
*                                 negative. It will remain high for each cycle
*                                 this condition is true.
*    `$INSTANCE_NAME`_DPTHRESH   Datapath Threshold Crossed. This signal
*                                 asserts anytime the threshold of 0 is crossed
*                                 in the ALU when one of the following
*                                 instructions is executing: TDECA, TSUBA,
*                                 TSUBB, TADDABSA, TADDABSB. It will remain high
*                                 for each cycle this condition is true.
*    `$INSTANCE_NAME`_DPEQ       Datapath ALU=0. This signal asserts high when
*                                 the output of the ALU in the Datapath unit
*                                 equals 0 and one of the following ALU commands
*                                 is executing: TDECA, TSUBA, TSUBB, TADDABSA,
*                                 TADDABSB. It will remain high for each cycle
*                                 this condition is true.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOutput2Source(uint8 source) `=ReentrantKeil($INSTANCE_NAME . "_SetOutput2Source")`
{
    `$INSTANCE_NAME`_DSI_CTRL_REG = (`$INSTANCE_NAME`_DSI_CTRL_REG & `$INSTANCE_NAME`_DFB_GBL2_OUT_MASK) | source;
}


/* [] END OF FILE */
