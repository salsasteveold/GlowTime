
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
// Generated on 01/11/2013 at 12:42
// Component: KEES_UDB_Decimator
module KEES_UDB_Decimator (
	output  D0_load,
	output 	Decrement,
	output 	DPClockEnable,
	output 	DPClock,
	output  Done,
	output  F0_load,
	output  F1_load,
	output  State_0,
	output  State_1,
	output  State_2,
	output 	TermCount,
	input   Clock,
	input   ModIn,
	input   Reset,
	input   SampleClock
);

//`#start body` -- edit after this line, do not edit this line

parameter Decimate = "7'b0000000";

localparam STATE_1P = 3'h0;
localparam STATE_1M = 3'h1;
localparam STATE_2 = 3'h2;
localparam STATE_3 = 3'h3;
localparam STATE_4 = 3'h4;
localparam STATE_5 = 3'h5;
localparam STATE_6 = 3'h6;
localparam STATE_7 = 3'h7;

reg [2:0] State;
reg done;
wire f0_load;
wire f1_load;
wire d0_load;
wire decrement;
wire sample_edge;
reg sample_clock_delayed;

wire termcount;
wire DP_Clock;
reg DP_Clock_Enable;
wire [1:0] fifo_stat;

assign State_0 = State[0];
assign State_1 = State[1];
assign State_2 = State[2];
assign F0_load = f0_load;
assign F1_load = f1_load;
assign D0_load = d0_load;
assign Done = fifo_stat[0];
assign TermCount = termcount;
assign DPClockEnable = DP_Clock_Enable;
assign Decrement = decrement;
assign DPClock = DP_Clock;

// edge detector for sample clock signal
assign sample_edge = (SampleClock == 1'b1 && sample_clock_delayed == 1'b0) ? 1'b1 : 1'b0;

// cominbatorial datapath clock gating
//assign DP_Clock = Clock & DP_Clock_Enable;
// datapath clock gating through udb clock enable block
//assign DP_Clock_Enable = (State == STATE_2 && termcount == 0 && sample_edge == 0) || (State == STATE_7 && sample_edge == 0) ? 1'b0 : 1'b1;

// fifo 0 load signal logic
assign f0_load = (State == STATE_3 || State == STATE_6 || State == STATE_7) ? 1'b1 : 1'b0;
// fifo 1 load signal logic
assign f1_load = (State == STATE_5) ? 1'b1 : 1'b0;
// data register 0 load signal logic
assign d0_load = (State == STATE_3 || State == STATE_5 || State == STATE_7) ? 1'b1 : 1'b0;

// count 7 decrement signal logic
assign decrement = (State == STATE_1P || State == STATE_1M) ? 1'b1 : 1'b0;


always @(posedge Clock)
begin
	
	DP_Clock_Enable <= 1;
	// sample clock edge detector register
	sample_clock_delayed <= SampleClock;
	
	case(State)
	
		STATE_1P:
		begin
			//decrement <= 1;
			//DP_Clock_Enable <= 0;
			State <= STATE_2;
		end
		
		STATE_1M:
		begin
			//decrement <= 1;
			//DP_Clock_Enable <= 0;
			State <= STATE_2;
		end
		
		STATE_2:
		begin
			if(termcount == 1)
			begin
				State <= STATE_3;
			end
			else if((sample_edge == 1) && (ModIn == 1))
			begin
				State <= STATE_1P;
			end
			else if((sample_edge == 1) && (ModIn == 0))
			begin
				State <= STATE_1M;
			end
			else
			begin
				DP_Clock_Enable <= 0;
				State <= STATE_2;
			end
		end
		
		STATE_3:
		begin
			//f0_load <= 1;
			//d0_load <= 1;
			State <= STATE_4;
		end
		
		STATE_4:
		begin
			State <= STATE_5;
		end
		
		STATE_5:
		begin
			//f1_load <= 1;
			//d0_load <= 1;
			State <= STATE_6;
		end
		
		STATE_6:
		begin
			//f0_load <= 1;
			//DP_Clock_Enable <= 0;
			State <= STATE_7;
		end
		
		STATE_7:
		begin
			//f0_load <= 1;
			//d0_load <= 1;
			
			if((sample_edge == 1) && (ModIn == 1))
			begin
				State <= STATE_1P;
			end
			else if((sample_edge == 1) && (ModIn == 0))
			begin
				State <= STATE_1M;
			end
			else
			begin
				DP_Clock_Enable <= 0;
				State <= STATE_7;
			end
		end
		
	endcase
	
end


// Count7 cell
cy_psoc3_count7 #(.cy_period({Decimate}), .cy_route_ld(`FALSE), .cy_route_en(`TRUE))
Counter7 (
/* input */ .clock (Clock), // Clock
/* input */ .reset(Reset), // Reset
/* input */ .load(1'b0), // Load signal used if cy_route_ld = TRUE
/* input */ .enable(decrement), // Enable signal used if cy_route_en = TRUE
/* output [6:0] */ .count(), // Counter value output
/* output */ .tc(termcount) // Terminal Count output
);

// UDB clock enable
cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`FALSE)) MyCompClockSpec (
.enable(DP_Clock_Enable), /* Enable from interconnect */
.clock_in(Clock), /* Clock from interconnect */
.clock_out(DP_Clock) /* Clock to be used for UDB elements in this component */
);

//`#end` -- edit above this line, do not edit this line
cy_psoc3_dp16 #(.cy_dpconfig_a(
{
    `CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:     A0=A0+1*/
    `CS_ALU_OP__DEC, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:     A0=A0-1*/
    `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:     A1=A0+A1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:     F0=ALU,A0=D0,D0=F0*/
    `CS_ALU_OP__SUB, `CS_SRCA_A1, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:     A0=A1-A0*/
    `CS_ALU_OP__SUB, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5:     A0-D0,F1=ALU,D0=F0*/
    `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:     F0=ALU*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:     F0=ALU,A0=D0,D0=F0*/
    8'hFF, 8'h00,  /*CFG9:       */
    8'hFF, 8'hFF,  /*CFG11-10:       */
    `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
    `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    `SC_SI_A_DEFSI, /*CFG13-12:       */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    1'h0, `SC_FIFO1_ALU, `SC_FIFO0_ALU,
    `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_NOCHN,
    `SC_CMP0_NOCHN, /*CFG15-14:       */
    10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
    `SC_WRK16CAT_DSBL /*CFG17-16:       */
}
), .cy_dpconfig_b(
{
    `CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:     A0=A0+1*/
    `CS_ALU_OP__DEC, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:     A0=A0-1*/
    `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:     A1=A0+A1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:     F0=ALU,A0=D0,D0=F0*/
    `CS_ALU_OP__SUB, `CS_SRCA_A1, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:     A0=A1-A0*/
    `CS_ALU_OP__SUB, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5:     A0-D0,F1=ALU,D0=F0*/
    `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:     F0=ALU*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:     F0=ALU,A0=D0,D0=F0*/
    8'hFF, 8'h00,  /*CFG9:       */
    8'hFF, 8'hFF,  /*CFG11-10:       */
    `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
    `SC_CI_A_CHAIN, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    `SC_SI_A_DEFSI, /*CFG13-12:       */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    1'h0, `SC_FIFO1_ALU, `SC_FIFO0_ALU,
    `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_CHNED,
    `SC_CMP0_CHNED, /*CFG15-14:       */
    10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
    `SC_WRK16CAT_DSBL /*CFG17-16:       */
}
)) CIC_Decimator(
        /*  input                   */  .reset(Reset),
        /*  input                   */  .clk(DP_Clock),
        /*  input   [02:00]         */  .cs_addr(State),
        /*  input                   */  .route_si(1'b0),
        /*  input                   */  .route_ci(1'b0),
        /*  input                   */  .f0_load(f0_load),
        /*  input                   */  .f1_load(f1_load),
        /*  input                   */  .d0_load(d0_load),
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
        /*  output  [01:00]                  */  .co_msb(),
        /*  output  [01:00]                  */  .cmsb(),
        /*  output  [01:00]                  */  .so(),
        /*  output  [01:00]                  */  .f0_bus_stat(),
        /*  output  [01:00]                  */  .f0_blk_stat(),
        /*  output  [01:00]                  */  .f1_bus_stat(fifo_stat),
        /*  output  [01:00]                  */  .f1_blk_stat()
);
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line







