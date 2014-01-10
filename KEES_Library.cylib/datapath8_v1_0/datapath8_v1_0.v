
//`#start header` -- edit after this line, do not edit this line
// ========================================
//
// Copyright YOUR COMPANY, THE YEAR
// All Rights Reserved
// UNPUBLISHED, LICENSED SOFTWARE.
//
// CONFIDENTIAL AND PROPRIETARY INFORMATION
// WHICH IS THE PROPERTY OF your company.
//
// ========================================
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 01/30/2010 at 15:23
// Component: datapath8_v1_0
module datapath8_v1_0 (
	carry_out_msb,
	comp_equal_0,
	comp_equal_1,
	comp_less_0,
	comp_less_1,
	crc_msb,
	fifo_0_block_status,
	fifo_0_bus_status,
	fifo_1_block_status,
	fifo_1_bus_status,
	ones_0,
	ones_1,
	overflow_msb,
	shift_out,
	zeros_0,
	zeros_1,
	d1_load,
	clk,
	d0_load,
	fifo_0_load,
	fifo_1_load,
	instruction_addr,
	route_carry_in,
	route_shift_in
);
	output  carry_out_msb;
	output  comp_equal_0;
	output  comp_equal_1;
	output  comp_less_0;
	output  comp_less_1;
	output  crc_msb;
	output  fifo_0_block_status;
	output  fifo_0_bus_status;
	output  fifo_1_block_status;
	output  fifo_1_bus_status;
	output  ones_0;
	output  ones_1;
	output  overflow_msb;
	output  shift_out;
	output  zeros_0;
	output  zeros_1;
	inout   d1_load;
	input   clk;
	input   d0_load;
	input   fifo_0_load;
	input   fifo_1_load;
	input  [2:0] instruction_addr;
	input   route_carry_in;
	input   route_shift_in;

//`#start body` -- edit after this line, do not edit this line

//       // 8-Bit Datapath
	cy_psoc3_dp8 #(.d1_init_a(127),
	.cy_dpconfig_a(
	{
		`CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC__ALU,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CS_REG0 Comment: */
		`CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CS_REG1 Comment: */
		`CS_ALU_OP__INC, `CS_SRCA_A1, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CS_REG2 Comment: */
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CS_REG3 Comment: */
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CS_REG4 Comment: */
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CS_REG5 Comment: */
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CS_REG6 Comment: */
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CS_REG7 Comment: */
		  8'hFF, 8'h00,	/*SC_REG4	Comment: */
		  8'hFF, 8'hFF,	/*SC_REG5	Comment: */
		`SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_CHAIN,
		`SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
		`SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
		`SC_SI_A_DEFSI, /*SC_REG6 Comment: */
		`SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'b0,
		1'b0, `SC_FIFO1_BUS, `SC_FIFO0__A0,
		`SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
		`SC_FB_NOCHN, `SC_CMP1_NOCHN,
		`SC_CMP0_NOCHN, /*SC_REG7 Comment: */
		 10'h0, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
		`SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
		`SC_WRK16CAT_DSBL /*SC_REG8 Comment: */
	})) Datapath(
		/*  input                   */  .clk(clk),
		/*  input   [02:00]         */  .cs_addr(instruction_addr),
		/*  input                   */  .route_si(route_shift_in),
		/*  input                   */  .route_ci(route_carry_in),
		/*  input                   */  .f0_load(fifo_0_load),
		/*  input                   */  .f1_load(fifo_1_load),
		/*  input                   */  .d0_load(d0_load),
		/*  input                   */  .d1_load(d1_load),
		/*  output                  */  .ce0(comp_equal_0),
		/*  output                  */  .cl0(comp_less_0),
		/*  output                  */  .z0(zeros_0),
		/*  output                  */  .ff0(ones_0),
		/*  output                  */  .ce1(comp_equal_1),
		/*  output                  */  .cl1(comp_less_1),
		/*  output                  */  .z1(zeros_1),
		/*  output                  */  .ff1(ones_1),
		/*  output                  */  .ov_msb(overflow_msb),
		/*  output                  */  .co_msb(carry_out_msb),
		/*  output                  */  .cmsb(crc_msb),
		/*  output                  */  .so(shift_out),
		/*  output                  */  .f0_bus_stat(fifo_0_bus_status),
		/*  output                  */  .f0_blk_stat(fifo_0_block_status),
		/*  output                  */  .f1_bus_stat(fifo_1_bus_status),
		/*  output                  */  .f1_blk_stat(fifo_1_block_status)
	);


//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line
