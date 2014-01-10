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

//`#start body` -- edit after this line, do not edit this line
module CJCU_B_Fsqrt32_v1_0 (
    start,
	clk,
	eoc
);
	input start;
	input clk;
	output eoc;
	
	// state encoding: 1 bits unique, 3 bits opcode
	localparam B_SQRT_STATE_0 		= 4'b0000;	// 0th Op0
	localparam B_SQRT_STATE_1	 	= 4'b0001;	// 0th Op1 (f0_load)
	localparam B_SQRT_STATE_2 		= 4'b0010;	// 0th Op2
	localparam B_SQRT_STATE_3 		= 4'b0011;	// 0th Op3 (f1_load)
	localparam B_SQRT_STATE_4	 	= 4'b0100;	// 0th Op4
	localparam B_SQRT_STATE_5 		= 4'b0101;	// 0th Op5
	localparam B_SQRT_STATE_6	 	= 4'b1001;	// 1st Op1 (f0_load)
	localparam B_SQRT_STATE_7	 	= 4'b0110;	// 0th Op6
	localparam B_SQRT_STATE_8	 	= 4'b1100;	// 1st Op4
	localparam B_SQRT_STATE_9		= 4'b1011;	// 1st Op3 (f1_load)
	localparam B_SQRT_STATE_10	 	= 4'b1010;	// 1st Op2
	localparam B_SQRT_STATE_11	 	= 4'b0111;	// 0th Op7 (f1_load)
	localparam B_SQRT_STATE_12	 	= 4'b1110;	// 1st Op6
    localparam B_SQRT_STATE_13	 	= 4'b1101;	// 2nd Op3
    localparam B_SQRT_STATE_14	 	= 4'b1111;	// 1st Op7 (f1_load)
    localparam B_SQRT_STATE_15	 	= 4'b1000;	// 1st Op0

	reg [3:0] state;
	
	wire f0_load = (state == B_SQRT_STATE_1 ||
					state == B_SQRT_STATE_6);
					
	wire f1_load = (state == B_SQRT_STATE_3 ||
					state == B_SQRT_STATE_9 ||
					state == B_SQRT_STATE_11 ||
					state == B_SQRT_STATE_14);
								
	wire fifo_dyn = (state == B_SQRT_STATE_0 ||
					 state == B_SQRT_STATE_15);

	assign eoc = (state == B_SQRT_STATE_15);
					
	wire [2:0] cs_addr = (state == 4'b1101) ? 3'b011 : state[2:0];
	wire [3:0] sol_msb_reg;
	wire [3:0] cl1;
    wire [3:0] ce1;
    
	always @(posedge clk)
	begin
		case (state)
			B_SQRT_STATE_0: state <= (start ? B_SQRT_STATE_1 : B_SQRT_STATE_0);
			B_SQRT_STATE_1: state <= B_SQRT_STATE_2;
			B_SQRT_STATE_2: state <= (cl1[3] && !sol_msb_reg[3] ? B_SQRT_STATE_8 : B_SQRT_STATE_3);
			B_SQRT_STATE_3: state <= B_SQRT_STATE_4;
			B_SQRT_STATE_4: state <= B_SQRT_STATE_5;
			B_SQRT_STATE_5: state <= (ce1[3] ? B_SQRT_STATE_11 : B_SQRT_STATE_6);
			B_SQRT_STATE_6: state <= B_SQRT_STATE_7;
			B_SQRT_STATE_7: state <= B_SQRT_STATE_2;
			B_SQRT_STATE_8: state <= B_SQRT_STATE_9;
			B_SQRT_STATE_9: state <= B_SQRT_STATE_10;
			B_SQRT_STATE_10: state <= B_SQRT_STATE_5;
			B_SQRT_STATE_11: state <= B_SQRT_STATE_12;
			B_SQRT_STATE_12: state <= B_SQRT_STATE_13;
            B_SQRT_STATE_13: state <= (cl1[3] && !sol_msb_reg[3] ? B_SQRT_STATE_15 : B_SQRT_STATE_14);
            B_SQRT_STATE_14: state <= B_SQRT_STATE_15;
            B_SQRT_STATE_15: state <= B_SQRT_STATE_0;
			default: state <= B_SQRT_STATE_0;
		endcase
	end
	
//`#end` -- edit above this line, do not edit this line

//`#start footer` -- edit after this line, do not edit this line








cy_psoc3_dp32 #(.d0_init_a(8'h00), .d1_init_a(8'h01), .d0_init_b(8'h00), 
.d1_init_b(8'h00), .d0_init_c(8'h00), .d1_init_c(8'h00), 
.d0_init_d(8'h40), .d1_init_d(8'h00), 
.cy_dpconfig_a(
{
    `CS_ALU_OP__XOR, `CS_SRCA_A1, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:               A0 = D0, A1 = A1^A1*/
    `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC___F1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:               A0 = A0 + A1, A1 = F1*/
    `CS_ALU_OP__SUB, `CS_SRCA_A1, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:               A1 = A1 - A0*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:               A0 = F0, A1 = A0*/
    `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:               A1 = A0 + A1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP___SR, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGB,
    `CS_CMP_SEL_CFGB, /*CFGRAM5:               A0 = A0 >> 1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP___SL, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:               A1 = A1 << 1*/
    `CS_ALU_OP__ADD, `CS_SRCA_A1, `CS_SRCB_D1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC___F1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:               A0 = A1 + D1, A1 = F1*/
    8'hFF, 8'h00,  /*CFG9:                             */
    8'hFF, 8'hFF,  /*CFG11-10:                             */
    `SC_CMPB_A0_D1, `SC_CMPA_A1_A0, `SC_CI_B_ARITH,
    `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_CHAIN,
    `SC_SI_A_DEFSI, /*CFG13-12:                             */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    1'h0, `SC_FIFO1__A1, `SC_FIFO0__A0,
    `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_NOCHN,
    `SC_CMP0_NOCHN, /*CFG15-14:                             */
    6'h00, `SC_FIFO1_DYN_ON,`SC_FIFO0_DYN_ON,
    2'h00,`SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO_LEVEL /*CFG17-16:                             */
,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,`SC_WRK16CAT_DSBL}
), .cy_dpconfig_b(
{
    `CS_ALU_OP__XOR, `CS_SRCA_A1, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:               A0 = D0, A1 = A1^A1*/
    `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC___F1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:               A0 = A0 + A1, A1 = F1*/
    `CS_ALU_OP__SUB, `CS_SRCA_A1, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:               A1 = A1 - A0*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:               A0 = F0, A1 = A0*/
    `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:               A1 = A0 + A1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP___SR, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGB,
    `CS_CMP_SEL_CFGB, /*CFGRAM5:               A0 = A0 >> 1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP___SL, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:               A1 = A1 << 1*/
    `CS_ALU_OP__ADD, `CS_SRCA_A1, `CS_SRCB_D1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC___F1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:               A0 = A1 + D1, A1 = F1*/
    8'hFF, 8'h00,  /*CFG9:                             */
    8'hFF, 8'hFF,  /*CFG11-10:                             */
    `SC_CMPB_A0_D1, `SC_CMPA_A1_A0, `SC_CI_B_ARITH,
    `SC_CI_A_CHAIN, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_CHAIN,
    `SC_SI_A_CHAIN, /*CFG13-12:                             */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    1'h0, `SC_FIFO1__A1, `SC_FIFO0__A0,
    `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_CHNED,
    `SC_CMP0_NOCHN, /*CFG15-14:                             */
    6'h00, `SC_FIFO1_DYN_ON,`SC_FIFO0_DYN_ON,
    2'h00,`SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO_LEVEL /*CFG17-16:                             */
,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,`SC_WRK16CAT_DSBL}
), .cy_dpconfig_c(
{
    `CS_ALU_OP__XOR, `CS_SRCA_A1, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:               A0 = D0, A1 = A1^A1*/
    `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC___F1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:               A0 = A0 + A1, A1 = F1*/
    `CS_ALU_OP__SUB, `CS_SRCA_A1, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:               A1 = A1 - A0*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:               A0 = F0, A1 = A0*/
    `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:               A1 = A0 + A1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP___SR, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGB,
    `CS_CMP_SEL_CFGB, /*CFGRAM5:               A0 = A0 >> 1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP___SL, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:               A1 = A1 << 1*/
    `CS_ALU_OP__ADD, `CS_SRCA_A1, `CS_SRCB_D1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC___F1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:               A0 = A1 + D1, A1 = F1*/
    8'hFF, 8'h00,  /*CFG9:                             */
    8'hFF, 8'hFF,  /*CFG11-10:                             */
    `SC_CMPB_A0_D1, `SC_CMPA_A1_A0, `SC_CI_B_ARITH,
    `SC_CI_A_CHAIN, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_CHAIN,
    `SC_SI_A_CHAIN, /*CFG13-12:                             */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    1'h0, `SC_FIFO1__A1, `SC_FIFO0__A0,
    `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_CHNED,
    `SC_CMP0_NOCHN, /*CFG15-14:                             */
    6'h00, `SC_FIFO1_DYN_ON,`SC_FIFO0_DYN_ON,
    2'h00,`SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO_LEVEL /*CFG17-16:                             */
,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,`SC_WRK16CAT_DSBL}
), .cy_dpconfig_d(
{
    `CS_ALU_OP__XOR, `CS_SRCA_A1, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:               A0 = D0, A1 = A1^A1*/
    `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC___F1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:               A0 = A0 + A1, A1 = F1*/
    `CS_ALU_OP__SUB, `CS_SRCA_A1, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:               A1 = A1 - A0*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:               A0 = F0, A1 = A0*/
    `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:               A1 = A0 + A1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP___SR, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGB,
    `CS_CMP_SEL_CFGB, /*CFGRAM5:               A0 = A0 >> 1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP___SL, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:               A1 = A1 << 1*/
    `CS_ALU_OP__ADD, `CS_SRCA_A1, `CS_SRCB_D1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC___F1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:               A0 = A1 + D1, A1 = F1*/
    8'hFF, 8'h00,  /*CFG9:                             */
    8'hFF, 8'hFF,  /*CFG11-10:                             */
    `SC_CMPB_A0_D1, `SC_CMPA_A1_A0, `SC_CI_B_ARITH,
    `SC_CI_A_CHAIN, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    `SC_SI_A_CHAIN, /*CFG13-12:                             */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    1'h0, `SC_FIFO1__A1, `SC_FIFO0__A0,
    `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_CHNED,
    `SC_CMP0_NOCHN, /*CFG15-14:                             */
    6'h00, `SC_FIFO1_DYN_ON,`SC_FIFO0_DYN_ON,
    2'h00,`SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO_LEVEL /*CFG17-16:                             */
,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,`SC_WRK16CAT_DSBL}
)) dp(
        /*  input                   */  .reset(1'b0),
        /*  input                   */  .clk(clk),
        /*  input   [02:00]         */  .cs_addr(cs_addr),
        /*  input                   */  .route_si(1'b0),
        /*  input                   */  .route_ci(1'b0),
        /*  input                   */  .f0_load(f0_load),
        /*  input                   */  .f1_load(f1_load),
        /*  input                   */  .d0_load(1'b0),
        /*  input                   */  .d1_load(fifo_dyn),
        /*  output  [03:00]                  */  .ce0(),
        /*  output  [03:00]                  */  .cl0(),
        /*  output  [03:00]                  */  .z0(),
        /*  output  [03:00]                  */  .ff0(),
        /*  output  [03:00]                  */  .ce1(ce1),
        /*  output  [03:00]                  */  .cl1(cl1),
        /*  output  [03:00]                  */  .z1(),
        /*  output  [03:00]                  */  .ff1(),
        /*  output  [03:00]                  */  .ov_msb(),
        /*  output  [03:00]                  */  .co_msb(),
        /*  output  [03:00]                  */  .cmsb(),
        /*  output  [03:00]                  */  .so_reg(sol_msb_reg),
        /*  output  [03:00]                  */  .f0_bus_stat(),
        /*  output  [03:00]                  */  .f0_blk_stat(),
        /*  output  [03:00]                  */  .f1_bus_stat(),
        /*  output  [03:00]                  */  .f1_blk_stat()
);
//`#end` -- edit above this line, do not edit this line
endmodule

//[] END OF FILE











