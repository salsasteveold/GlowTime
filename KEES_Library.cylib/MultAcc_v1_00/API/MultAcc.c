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

#if `$EnableBlock`

	/* DMA Configuration for DMA_IN_A */
	#define `$INSTANCE_NAME`_DMA_IN_A_BYTES_PER_BURST 4
	#define `$INSTANCE_NAME`_DMA_IN_A_REQUEST_PER_BURST 1
	#define `$INSTANCE_NAME`_DMA_IN_A_SRC_BASE (CYDEV_SRAM_BASE)
	#define `$INSTANCE_NAME`_DMA_IN_A_DST_BASE (CYDEV_PERIPH_BASE)

	/* DMA Configuration for DMA_IN_B */
	#define `$INSTANCE_NAME`_DMA_IN_B_BYTES_PER_BURST 4
	#define `$INSTANCE_NAME`_DMA_IN_B_REQUEST_PER_BURST 1
	#define `$INSTANCE_NAME`_DMA_IN_B_SRC_BASE (CYDEV_SRAM_BASE)
	#define `$INSTANCE_NAME`_DMA_IN_B_DST_BASE (CYDEV_PERIPH_BASE)
	
	`$INSTANCE_NAME`_ARRAY `$INSTANCE_NAME`_a;
	`$INSTANCE_NAME`_ARRAY `$INSTANCE_NAME`_b;

	//int32 `$INSTANCE_NAME`_data_a[`$ArraySize`];
	//int32 `$INSTANCE_NAME`_data_b[`$ArraySize`];

	uint8 `$INSTANCE_NAME`_DMA_IN_A_Chan;
	uint8 `$INSTANCE_NAME`_DMA_IN_A_TD[1];
	
	uint8 `$INSTANCE_NAME`_DMA_IN_B_Chan;
	uint8 `$INSTANCE_NAME`_DMA_IN_B_TD[1];
	
	uint8 `$INSTANCE_NAME`_DMAInitialized = 0;

#endif

void `$INSTANCE_NAME`_Init()
{
	`$INSTANCE_NAME`_MACC_Init();
	#if `$EnableBlock`
		`$INSTANCE_NAME`_DMAInit();
	#endif
}

void `$INSTANCE_NAME`_Enable()
{
	`$INSTANCE_NAME`_MACC_Enable();
	#if `$EnableBlock`
		`$INSTANCE_NAME`_DMAEnable();
	#endif
}

void `$INSTANCE_NAME`_Start()
{
	`$INSTANCE_NAME`_MACC_Start();
	#if `$EnableBlock`
		`$INSTANCE_NAME`_DMAInit();
		`$INSTANCE_NAME`_DMAEnable();
	#endif
}

void `$INSTANCE_NAME`_Stop()
{
	`$INSTANCE_NAME`_MACC_Stop();
	#if `$EnableBlock`
		`$INSTANCE_NAME`_DMADisable();
	#endif
}

//void `$INSTANCE_NAME`_Sleep()
//{
//	`$INSTANCE_NAME`_MACC_Sleep();
//}
//
//void `$INSTANCE_NAME`_Wakeup()
//{
//	`$INSTANCE_NAME`_MACC_Wakeup();
//}

#if `$EnableBlock`

void `$INSTANCE_NAME`_DMAInit(void)
{
	
	if(`$INSTANCE_NAME`_DMAInitialized == 0)
	{
		`$INSTANCE_NAME`_DMAInitialized = 1;

		`$INSTANCE_NAME`_DMA_IN_A_Chan = `$INSTANCE_NAME`_DMA_IN_A_DmaInitialize(`$INSTANCE_NAME`_DMA_IN_A_BYTES_PER_BURST, `$INSTANCE_NAME`_DMA_IN_A_REQUEST_PER_BURST, 
		    HI16(`$INSTANCE_NAME`_DMA_IN_A_SRC_BASE), HI16(`$INSTANCE_NAME`_DMA_IN_A_DST_BASE));
		`$INSTANCE_NAME`_DMA_IN_A_TD[0] = CyDmaTdAllocate();
		#if `$BigEndianCompiler`
			CyDmaTdSetConfiguration(`$INSTANCE_NAME`_DMA_IN_A_TD[0], `$ArraySize`*sizeof(uint32), `$INSTANCE_NAME`_DMA_IN_A_TD[0], TD_SWAP_EN | TD_SWAP_SIZE4 | `$INSTANCE_NAME`_DMA_IN_A__TD_TERMOUT_EN | TD_INC_SRC_ADR);
		#else
			CyDmaTdSetConfiguration(`$INSTANCE_NAME`_DMA_IN_A_TD[0], `$ArraySize`*sizeof(uint32), `$INSTANCE_NAME`_DMA_IN_A_TD[0], `$INSTANCE_NAME`_DMA_IN_A__TD_TERMOUT_EN | TD_INC_SRC_ADR);
		#endif
		CyDmaTdSetAddress(`$INSTANCE_NAME`_DMA_IN_A_TD[0], LO16((uint32)&`$INSTANCE_NAME`_a.dat[0]), LO16((uint32)`$INSTANCE_NAME`_IN_A32_PTR));  // 
		CyDmaChSetInitialTd(`$INSTANCE_NAME`_DMA_IN_A_Chan, `$INSTANCE_NAME`_DMA_IN_A_TD[0]);
		
		CyDmaChRoundRobin(`$INSTANCE_NAME`_DMA_IN_A_Chan, 1);

		`$INSTANCE_NAME`_DMA_IN_B_Chan = `$INSTANCE_NAME`_DMA_IN_B_DmaInitialize(`$INSTANCE_NAME`_DMA_IN_B_BYTES_PER_BURST, `$INSTANCE_NAME`_DMA_IN_B_REQUEST_PER_BURST, 
		    HI16(`$INSTANCE_NAME`_DMA_IN_B_SRC_BASE), HI16(`$INSTANCE_NAME`_DMA_IN_B_DST_BASE));
		`$INSTANCE_NAME`_DMA_IN_B_TD[0] = CyDmaTdAllocate();
		#if `$BigEndianCompiler`
			CyDmaTdSetConfiguration(`$INSTANCE_NAME`_DMA_IN_B_TD[0], `$ArraySize`*sizeof(uint32), `$INSTANCE_NAME`_DMA_IN_B_TD[0], TD_SWAP_EN | TD_SWAP_SIZE4 | `$INSTANCE_NAME`_DMA_IN_B__TD_TERMOUT_EN | TD_INC_SRC_ADR);
		#else
			CyDmaTdSetConfiguration(`$INSTANCE_NAME`_DMA_IN_B_TD[0], `$ArraySize`*sizeof(uint32), `$INSTANCE_NAME`_DMA_IN_B_TD[0], `$INSTANCE_NAME`_DMA_IN_B__TD_TERMOUT_EN | TD_INC_SRC_ADR);
		#endif
		CyDmaTdSetAddress(`$INSTANCE_NAME`_DMA_IN_B_TD[0], LO16((uint32)&`$INSTANCE_NAME`_b.dat[0]), LO16((uint32)`$INSTANCE_NAME`_IN_B32_PTR)); // 
		CyDmaChSetInitialTd(`$INSTANCE_NAME`_DMA_IN_B_Chan, `$INSTANCE_NAME`_DMA_IN_B_TD[0]);
		
		CyDmaChRoundRobin(`$INSTANCE_NAME`_DMA_IN_B_Chan, 1);
		
	}

}

void `$INSTANCE_NAME`_DMAEnable(void)
{
	CyDmaChSetRequest(`$INSTANCE_NAME`_DMA_IN_A_Chan, CPU_TERM_CHAIN);
	CyDmaChEnable(`$INSTANCE_NAME`_DMA_IN_A_Chan, 1);
	CyDmaChEnable(`$INSTANCE_NAME`_DMA_IN_A_Chan, 1);

	CyDmaChSetRequest(`$INSTANCE_NAME`_DMA_IN_B_Chan, CPU_TERM_CHAIN);
	CyDmaChEnable(`$INSTANCE_NAME`_DMA_IN_B_Chan, 1);
	CyDmaChEnable(`$INSTANCE_NAME`_DMA_IN_B_Chan, 1);
	
	`$INSTANCE_NAME`_Status_InterruptEnable();
}

void `$INSTANCE_NAME`_DMADisable(void)
{
	CyDmaChSetRequest(`$INSTANCE_NAME`_DMA_IN_A_Chan, CPU_TERM_CHAIN);

	CyDmaChSetRequest(`$INSTANCE_NAME`_DMA_IN_B_Chan, CPU_TERM_CHAIN);
	
	`$INSTANCE_NAME`_Status_InterruptDisable();
}

void `$INSTANCE_NAME`_ProcessBlock(uint8 reset_accum)
{
	`$INSTANCE_NAME`_CheckStatus(`$INSTANCE_NAME`_RESET_STATUS);
	
	if(reset_accum > 0)
	{
		`$INSTANCE_NAME`_Control_Write(`$INSTANCE_NAME`_DMA_GO | `$INSTANCE_NAME`_NRQ_RESET | `$INSTANCE_NAME`_MACC_RESET);
	}
	else
	{
		`$INSTANCE_NAME`_Control_Write(`$INSTANCE_NAME`_DMA_GO | `$INSTANCE_NAME`_NRQ_RESET);
	}
	
	`$INSTANCE_NAME`_Control_Write(0);
}

uint8 `$INSTANCE_NAME`_CheckStatus(uint8 flag_check)
{
	static uint8 status_flags;
	
	status_flags |= (`$INSTANCE_NAME`_Status_Read() & ~`$INSTANCE_NAME`_RESET_STATUS);
	
	if((flag_check & `$INSTANCE_NAME`_RESET_STATUS) > 0)
	{
		status_flags = 0;
		return 0;
	}
	
	if((status_flags & flag_check) > 0)
	{
		status_flags = status_flags & ~flag_check;
		return flag_check;
	}
	
	return 0;
}

#endif

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_LoadInput
********************************************************************************
*
* Summary:
*  This function loads an input value into the selected input register.
*
* Parameters:
*  channel: Use either `$INSTANCE_NAME`_A (1) or
*           `$INSTANCE_NAME`_B (0) asarguments to the function;
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
#if !`$EnableBlock`

void `$INSTANCE_NAME`_LoadInput(int32 A, int32 B) 
{
    uint32 value_A, value_B;

    value_A = (uint32) A;
	value_B = (uint32) B;

    /* Writes the STAGE-"H" reg last as it signals a complete wrote to the DFB.*/

    `$INSTANCE_NAME`_STAGEA_REG  = (uint8) value_A;
    `$INSTANCE_NAME`_STAGEAM_REG = (uint8) (value_A >> 8u);
    `$INSTANCE_NAME`_STAGEAH_REG = (uint8) (value_A >> 16u);

    `$INSTANCE_NAME`_STAGEB_REG  = (uint8) value_B;
    `$INSTANCE_NAME`_STAGEBM_REG = (uint8) (value_B >> 8u);
    `$INSTANCE_NAME`_STAGEBH_REG = (uint8) (value_B >> 16u);

}

#endif

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOutput
********************************************************************************
*
* Summary:
*  This function gets the value from one of the DFB Output Holding Registers.
*
* Parameters:
*  None
*
* Return:
*  The current output value in the holding register. This is
*  a 24-bit number packed into the least-significant 3 bytes of the output word
*
* Note:
*  Because of the architecture of the DFB, any value read from the Holding A or
*  B registers will be MSB aligned unless shifted otherwise by the Datapath
*  shifter. Pay attention to byte order if coherency or data alignment is
*  changed.
*
*******************************************************************************/
int32 `$INSTANCE_NAME`_GetResult() 
{
    uint8 data0;
    uint8 data1;
    uint8 data2;
    uint8 data3;
    uint32 output;
	
	// due to double buffer acting as a 2 element FIFO, I have to read the 
	// high byte once to clear out the "first" result, then read again
	// to get the most recent result.
	data2 = `$INSTANCE_NAME`_HOLDAH_REG;

    /* Reads the HOLD-"H" reg last as it signals a complete read to the DFB.*/
    data0 = `$INSTANCE_NAME`_HOLDA_REG;
    data1 = `$INSTANCE_NAME`_HOLDAM_REG;
    data2 = `$INSTANCE_NAME`_HOLDAH_REG;
    data3 = ((data2 & 0x80u) == 0x80u) ? 0xFFu : 0x00u;

    output = ((((((uint32) data3 << 8u) | data2) << 8u) | data1) << 8u) | data0;

    return ((int32) output);
}

float `$INSTANCE_NAME`_Q23ToFloat(int32 input)
{
	float output;
	
	// limit the input range to the valid values
	if(input > 8388607)
	{
		input = 8388607;
	}
	if(input < -8388608)
	{
		input = -8388608;
	}
	
	output = ((float) input) / 8388608.0;
	
	return output;
}

int32 `$INSTANCE_NAME`_FloatToQ23(float input)
{
	int32 output;
	
	// limit the input range to the valid values
	if(input > (1.0-0.00000011920928955078))
	{
		input = (1-0.00000011920928955078);
	}
	if(input < -1.0)
	{
		input = -1.0;
	}
	
	output = ((int32) (input * 8388608.0 + 0.5));
	
	return output;
}

/* [] END OF FILE */
