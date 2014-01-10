
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
// Generated on 01/24/2013 at 16:14
// Component: KEES_UDB_BitstreamIntegrator_v1_100
module KEES_UDB_BitstreamIntegrator_v1_10 (
	output  Mod_Out,
	output  State_0,
	output  State_1,
	output  State_2,
	output  CarryOut,
	input   Clock,
	input   Mod_In,
	input   SampleClock
);

//`#start body` -- edit after this line, do not edit this line

parameter IntegrationConstant = "16'h01";

localparam STATE_0 = 3'h0;
localparam STATE_1 = 3'h1;
localparam STATE_2 = 3'h2;
localparam STATE_3 = 3'h3;
localparam STATE_4 = 3'h4;
localparam STATE_5 = 3'h5;
localparam STATE_6 = 3'h6;
localparam STATE_7 = 3'h7;

reg [2:0] State;
reg Done;
reg SampleClock_Reg_1;
reg SampleClock_Reg_2;
reg mod_out;

wire Carry;
wire SampleClock_Edge;
wire [1:0] temp;

// rising edge detect of SampleClock
assign SampleClock_Edge = ((SampleClock_Reg_1 == 1) && (SampleClock_Reg_2 == 0)) ? 1 : 0;
assign Mod_Out = mod_out;
assign CarryOut = Carry;
assign State_0 = State[0];
assign State_1 = State[1];
assign State_2 = State[2];
assign Carry = temp[1];

always @ (posedge Clock)
begin

	SampleClock_Reg_1 <= SampleClock;
	SampleClock_Reg_2 <= SampleClock_Reg_1;
	Done <= 0;
	mod_out <= mod_out;
	//TC <= tc;
	
	case(State)
	
		STATE_0:
		begin
			if(SampleClock_Edge == 1 && Mod_In == 1)
			begin
				State <= STATE_1;  // positive input (and we care)
			end
			else if(SampleClock_Edge == 1 && Mod_In == 0)
			begin
				State <= STATE_2; // negative input (and we care)
			end
			else if(SampleClock_Edge == 1)
			begin
				State <= STATE_7;  // ignoring input, just accumulate
			end
			else
			begin
				State <= STATE_0;
			end
		end
		
		STATE_1:
		begin
			if(Carry == 1)
			begin
				State <= STATE_5;  // overflow, saturate FF
			end
			else
			begin
				State <= STATE_3; // safe to add
			end
		end
		
		STATE_2:
		begin
			if(Carry == 0)
			begin
				State <= STATE_6; // underflow, saturate 0
			end
			else
			begin
				State <= STATE_4; // safe to subtract
			end
		end
		
		STATE_3:
		begin
			State <= STATE_7; // add D0 to A1 and store in A1
		end
		
		STATE_4:
		begin
			State <= STATE_7;  // subtract D0 from A1 and store in A1
		end
		
		STATE_5:
		begin
			State <= STATE_7; // saturate FF and store in A1
		end
		
		STATE_6:
		begin
			State <= STATE_7; // saturate 0 and store in A1
		end
		
		STATE_7:
		begin
			State <= STATE_0; // add A1 to A0 and store in A0, capture Carry Out as mod out
			mod_out <= Carry;
			Done <= 1;
		end
	
	endcase
end

cy_psoc3_dp16 #(.d0_init_a(8'h01), .d1_init_a(8'hFF), .d0_init_b(8'h00), 
.d1_init_b(8'hFF), 
.cy_dpconfig_a(
{
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:    wait*/
    `CS_ALU_OP__ADD, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:    A1+D0 (overflow test)*/
    `CS_ALU_OP__SUB, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:    A1-D0 (underflow test)*/
    `CS_ALU_OP__ADD, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:    A1=A1+D0*/
    `CS_ALU_OP__SUB, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:    A1=A1-D0*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC___D1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5:    A1=D1 (saturate FF)*/
    `CS_ALU_OP__XOR, `CS_SRCA_A1, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:    A1=A1^A1 (saturate 0)*/
    `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:    A0=A0+A1*/
    8'hFF, 8'h00,  /*CFG9:    */
    8'hFF, 8'hFF,  /*CFG11-10:    */
    `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
    `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    `SC_SI_A_DEFSI, /*CFG13-12:    */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
    `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_CHNED,
    `SC_FB_NOCHN, `SC_CMP1_NOCHN,
    `SC_CMP0_NOCHN, /*CFG15-14:    */
    10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
    `SC_WRK16CAT_DSBL /*CFG17-16:    */
}
), .cy_dpconfig_b(
{
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:    wait*/
    `CS_ALU_OP__ADD, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:    A1+D0 (overflow test)*/
    `CS_ALU_OP__SUB, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:    A1-D0 (underflow test)*/
    `CS_ALU_OP__ADD, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:    A1=A1+D0*/
    `CS_ALU_OP__SUB, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:    A1=A1-D0*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC___D1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5:    A1=D1 (saturate FF)*/
    `CS_ALU_OP__XOR, `CS_SRCA_A1, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:    A1=A1^A1 (saturate 0)*/
    `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:    A0=A0+A1*/
    8'hFF, 8'h00,  /*CFG9:    */
    8'hFF, 8'hFF,  /*CFG11-10:    */
    `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_CHAIN,
    `SC_CI_A_CHAIN, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_CHAIN,
    `SC_SI_A_CHAIN, /*CFG13-12:    */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
    `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
    `SC_FB_CHNED, `SC_CMP1_CHNED,
    `SC_CMP0_CHNED, /*CFG15-14:    */
    10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
    `SC_WRK16CAT_DSBL /*CFG17-16:    */
}
)) Integrator16(
        /*  input                   */  .reset(1'b0),
        /*  input                   */  .clk(Clock),
        /*  input   [02:00]         */  .cs_addr(State),
        /*  input                   */  .route_si(1'b0),
        /*  input                   */  .route_ci(1'b0),
        /*  input                   */  .f0_load(1'b0),
        /*  input                   */  .f1_load(1'b0),
        /*  input                   */  .d0_load(1'b0),
        /*  input                   */  .d1_load(1'b0),
        /*  output  [01:00]                  */  .ce0(),
        /*  output  [01:00]                  */  .cl0(),
        /*  output  [01:00]                  */  .z0(),
        /*  output  [01:00]                  */  .ff0(),
        /*  output  [01:00]                  */  .ce1(),
        /*  output  [01:00]                  */  .cl1(),
        /*  output  [01:00]                  */  .z1(),
        /*  output  [01:00]                  */  .ff1(),
        /*  output  [01:00]                  */  .ov_msb(),
        /*  output  [01:00]                  */  .co_msb(temp),
        /*  output  [01:00]                  */  .cmsb(),
        /*  output  [01:00]                  */  .so(),
        /*  output  [01:00]                  */  .f0_bus_stat(),
        /*  output  [01:00]                  */  .f0_blk_stat(),
        /*  output  [01:00]                  */  .f1_bus_stat(),
        /*  output  [01:00]                  */  .f1_blk_stat()
);
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line




