
//`#start header` -- edit after this line, do not edit this line
// ========================================
//
// Copyright CYPRESS SEMICONDUCTOR, 2011
// All Rights Reserved
// UNPUBLISHED, LICENSED SOFTWARE.
//
// ========================================
/*******************************************************************************
* File Name: Sensei_Delay2x8_v1_0.v
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
* This component delays the input 8-bit bus by two clock cycles.  This is very 
* similar to the functionality of two 8-bit wide D Flip-Flops that are in series.
* The differences are:
*  - Implemented using a single datapath
*  - Output is created by muxing the output of two 8-bit registers.  That can 
*    cause the output to glitch after a rising clock edge.
*    
********************************************************************************
* Data Path register definitions
********************************************************************************
* Datapath: DelayDP
* DESCRIPTION: Used to implement the two 8-bit registers
* REGISTER USAGE:
* F0 => not used
* F1 => not used
* D0 => not used
* D1 => not used
* A0 => Data Storage
* A1 => Data Storage
*
********************************************************************************
* I*O Signals:
********************************************************************************
*    name              direction       Description
*    clk               input           Clock                      
*    di[7:0]           input           8-bit data input
*    en                input           Enable for the clock
*    reset             input           Synchronous reset (priority over enable)
*    do2[7:0]          output          8-bit delayed data output
*
********************************************************************************/
`include "cypress.v"
`ifdef Sensei_Delay2x8_v1_0_V_ALREADY_INCLUDED
`else
`define Sensei_Delay2x8_v1_0_V_ALREADY_INCLUDED

//`#end` -- edit above this line, do not edit this line
// Generated on 03/03/2011 at 10:31
// Component: Sensei_Delay2x8_v1_0
module Sensei_Delay2x8_v1_0 (
	do2,
	clk,
	di,
	en,
	reset
);
	output [7:0] do2;
	input   clk;
	input  [7:0] di;
	input   en;
	input   reset;

//`#start body` -- edit after this line, do not edit this line

    /***************************************************************************
    *         Instantiation of udb_clock_enable  
    ****************************************************************************
    * The udb_clock_enable primitive component is used to indicate that the input
	* clock can be asynchronous.  Typically that is not the case for datapath
	* components, but since this component is only used for hardware 
	* functionality and does not communicate at all with the CPU it can be 
	* operated asynchronously if required.
    */
    wire op_clk;    /* operational clock */
    
    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`FALSE)) ClkSync
    (
        /* input  */    .clock_in(clk),
        /* input  */    .enable(1'b1),
        /* output */    .clock_out(op_clk)
    );                         

	/***************************************************************************
    *       Logic Implementation                                      
    ***************************************************************************/   
	reg state;
	wire [2:0] cs_addr = {state, reset, en};
	
	// Which of the accumulators that is output switches on each enabled clock
	// One accumulator is loaded and the other is output
	// Changing the value of state swaps which accumulator is used
	always @(posedge op_clk)
	begin
		if (en)
		begin
			state <= ~state;
		end
	end

    /***************************************************************************
    *       Datapath Implementation                                      
    ***************************************************************************/   
	cy_psoc3_dp #(.cy_dpconfig(
	{
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CFGRAM0: Idle A0*/
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CFGRAM1: Enabled A0*/
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC___D1,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CFGRAM2: Reset*/
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC___D1,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CFGRAM3: Reset*/
		`CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CFGRAM4: Idle A1*/
		`CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CFGRAM5: Enabled A1*/
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC___D1,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CFGRAM6: Reset*/
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC___D1,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CFGRAM7: Reset*/
		8'hFF, 8'h00,  /*CFG9:  */
		8'hFF, 8'hFF,  /*CFG11-10:  */
		`SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
		`SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
		`SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
		`SC_SI_A_DEFSI, /*CFG13-12:  */
		`SC_A0_SRC_PIN, `SC_SHIFT_SL, 1'h0,
		1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
		`SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
		`SC_FB_NOCHN, `SC_CMP1_NOCHN,
		`SC_CMP0_NOCHN, /*CFG15-14:  */
		10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
		`SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
		`SC_WRK16CAT_DSBL /*CFG17-16:  */
	}
	)) DelayDP(
			/*  input                   */  .reset(1'b0),
			/*  input                   */  .clk(clk),
			/*  input   [02:00]         */  .cs_addr(cs_addr),
			/*  input                   */  .route_si(1'b0),
			/*  input                   */  .route_ci(1'b0),
			/*  input                   */  .f0_load(1'b0),
			/*  input                   */  .f1_load(1'b0),
			/*  input                   */  .d0_load(1'b0),
			/*  input                   */  .d1_load(1'b0),
			/*  output                  */  .ce0(),
			/*  output                  */  .cl0(),
			/*  output                  */  .z0(),
			/*  output                  */  .ff0(),
			/*  output                  */  .ce1(),
			/*  output                  */  .cl1(),
			/*  output                  */  .z1(),
			/*  output                  */  .ff1(),
			/*  output                  */  .ov_msb(),
			/*  output                  */  .co_msb(),
			/*  output                  */  .cmsb(),
			/*  output                  */  .so(),
			/*  output                  */  .f0_bus_stat(),
			/*  output                  */  .f0_blk_stat(),
			/*  output                  */  .f1_bus_stat(),
			/*  output                  */  .f1_blk_stat(),
			
			/* input                    */  .ci(1'b0),     // Carry in from previous stage
			/* output                   */  .co(),         // Carry out to next stage
			/* input                    */  .sir(1'b0),    // Shift in from right side
			/* output                   */  .sor(),        // Shift out to right side
			/* input                    */  .sil(1'b0),    // Shift in from left side
			/* output                   */  .sol(),        // Shift out to left side
			/* input                    */  .msbi(1'b0),   // MSB chain in
			/* output                   */  .msbo(),       // MSB chain out
			/* input [01:00]            */  .cei(2'b0),    // Compare equal in from prev stage
			/* output [01:00]           */  .ceo(),        // Compare equal out to next stage
			/* input [01:00]            */  .cli(2'b0),    // Compare less than in from prv stage
			/* output [01:00]           */  .clo(),        // Compare less than out to next stage
			/* input [01:00]            */  .zi(2'b0),     // Zero detect in from previous stage
			/* output [01:00]           */  .zo(),         // Zero detect out to next stage
			/* input [01:00]            */  .fi(2'b0),     // 0xFF detect in from previous stage
			/* output [01:00]           */  .fo(),         // 0xFF detect out to next stage
			/* input [01:00]            */  .capi(2'b0),   // Software capture from previous stage
			/* output [01:00]           */  .capo(),       // Software capture to next stage
			/* input                    */  .cfbi(1'b0),   // CRC Feedback in from previous stage
			/* output                   */  .cfbo(),       // CRC Feedback out to next stage
			/* input [07:00]            */  .pi(di),       // Parallel data port
			/* output [07:00]           */  .po(do2)       // Parallel data port
	);
//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
`endif /* Sensei_Delay2x8_v1_0_V_ALREADY_INCLUDED */
//`#end` -- edit above this line, do not edit this line
