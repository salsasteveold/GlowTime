
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
// Generated on 11/26/2012 at 16:34
// Component: KEES_UDB_IIR_v1_00
module KEES_UDB_IIR_v1_00 (
	output  reg Done,
	output  State_0,
	output  State_1,
	output  State_2,
    output  msb,
    output  TermC,
	input   Bitstream,
	input   Clock,
	input   Sample_Clock
);
	parameter [2:0] Beta = "3'b000";
	parameter [7:0] Resolution = "8'b00000000";
    parameter Enable_Sign_Magnitude = "1'b0";
    parameter Decimation = "7'b0000000";
    parameter Enable_ABS = "1'b0";
    parameter Enable_Offset = "1'b0";

//`#start body` -- edit after this line, do not edit this line

//State Machine Variables
	localparam STATE_0 	= 4'h0; 				// Wait for rising edge of Sample_Clock
	localparam STATE_1 	= 4'h1;  				// increment A0, store result in A0 and A1
	localparam STATE_2 	= 4'h2;	 				// decrement A0, store result in A0 and A1
	localparam STATE_3 	= 4'h3;  				// shift A1 right
	localparam STATE_4 	= 4'h4;  				// subtract A1 from A0 and store result in A0
    localparam STATE_5 	= 4'h5;  				// invert A0, store result in A0
    localparam STATE_6 	= 4'h6;  				// add 1, store result in A0 and A1
    localparam STATE_7 	= 4'h7;  				// wait for sample clock to go low

    reg [2:0] State;        // current state, dives config ram for datapath
    reg [2:0] Shift;        // counts the number of times the shift occurs
    reg Sign;               // stores the sign of the shifted result for sign magnitude conversion
    
    reg Decrement;
    wire TermCount;
    wire [1:0] temp;
    //wire abs_mode;
    
    assign msb = Sign;
    assign TermC = TermCount;
    //assign abs_mode = Enable_ABS;
    
    assign State_0 = State[0];
    assign State_1 = State[1];
    assign State_2 = State[2];
    
    //assign Decrement = (State == STATE_7);
    
    always @(posedge Clock)
    begin
        Done <= 0;
        Decrement <= 0;
        case(State)
            STATE_0:  // wait for sample_clock to go high
            begin
                Shift <= Beta;  // shift by this value + 1  beta = 2^(value+1)
                if((Sample_Clock == 1) && (Bitstream == 1))
                begin
                    State <= STATE_1;
                    Decrement <= 1;
                end
                else if((Sample_Clock == 1) && (Bitstream == 0))
                begin
                    State <= STATE_2;
                    Decrement <= 1;
                end
                else
                begin
                    State <= STATE_0;
                end
            end
            
            STATE_1:  // increment A0, store in A0 and A1, then move to shift state
            begin
                State <= STATE_3;
            end

            STATE_2:  // decrement A0, store in A0 and A1, then move to shift state
            begin
                State <= STATE_3;
            end
            
            STATE_3:  // shift by BETA
            begin  // ARITHMATIC shift information in the UDB BROS (001-08005) page # 99 under SI SELA and SI SELB
                Shift <= Shift - 1'b1;
                if(Shift == 0)
                begin  
                    Sign <= temp[1];
                    State <= STATE_4;
                end
                else
                begin
                    State <= STATE_3;
                end
            end
            
            STATE_4:  // subtract A1 from A0 -> A0
            begin
                if(Enable_Offset == 1)
                begin
                    State <= STATE_5;
                end
                else if(Enable_Sign_Magnitude == 1 && Sign == 1)
                begin
                    State <= STATE_5;
                end
                else
                begin
                    State <= STATE_7;
                    Done <= TermCount;
                end
            end
            
            STATE_5:  // invert all the bits except the MSBs, store result in A1 (or add offset)
            begin
                if(Enable_Offset == 0)
                begin
                    State <= STATE_6;
                end
                else
                begin
                    Done <= TermCount;
                    State <= STATE_7;
                end
            end
            
            STATE_6:  // add 1, store result in A1
            begin
                Done <= TermCount;
                State <= STATE_7;
            end
            
            STATE_7:  // wait for sample clock to go low
            begin
                if(Sample_Clock == 0)
                begin
                    State <= STATE_0;
                end
                else
                begin
                    State <= STATE_7;
                end
            end
        endcase
    end
    
cy_psoc3_count7 #(.cy_period(Decimation), .cy_route_ld(`FALSE), .cy_route_en(`TRUE))
Counter7Name (
/* input */ .clock (Clock), // Clock
/* input */ .reset(1'b0), // Reset
/* input */ .load(1'b0), // Load signal used if cy_route_ld = TRUE
/* input */ .enable(Decrement), // Enable signal used if cy_route_en = TRUE
/* output [6:0] */ .count(), // Counter value output
/* output */ .tc(TermCount) // Terminal Count output
);

//  reg [7:0] Decimator;    // counts the "done" signals, and when it reaches the count value, stores the result in the FIFO
//                if(Decimator == 0)
//                begin
//                    Done <= 1;
//                    Decimator <= Decimation;
//                end
//                else
//                begin
//                    Done <= 0;
//                    Decimator <= Decimator - 1'b1;
//                end

//`#end` -- edit above this line, do not edit this line

//`#start footer` -- edit after this line, do not edit this line
cy_psoc3_dp16 #(.d0_init_a(Resolution), .d1_init_a({Enable_ABS == 0 ? 1'b0 : 1'b1,7'b1111111}), .d0_init_b(8'b00000000), 
.d1_init_b(8'b00000000), 
.cy_dpconfig_a(
{
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:     do nothing wait state, copy A0 into A1*/
    `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:     mod bit is high, increment A0 -> A0*/
    `CS_ALU_OP__SUB, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:     mod bit is low, decrement A0 -> A0*/
    `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP___SR, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:     shift A1 right*/
    `CS_ALU_OP__SUB, `CS_SRCA_A0, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:     A0 - A1 ->A0*/
    Enable_Offset == 0 ? `CS_ALU_OP__XOR : `CS_ALU_OP__ADD, `CS_SRCA_A1, `CS_SRCB_D1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5:     Invert all bits in A1(but ! Msb) -> A1*/
    `CS_ALU_OP__INC, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:     add 1 to A1, store in A1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:     do nothing wait state*/
    8'hFF, 8'h00,  /*CFG9:                       */
    8'hFF, 8'hFF,  /*CFG11-10:                       */
    `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
    `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_CHAIN,
    `SC_SI_A_CHAIN, /*CFG13-12:                       */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    1'h0, `SC_FIFO1_BUS, `SC_FIFO0__A1,
    `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_NOCHN,
    `SC_CMP0_NOCHN, /*CFG15-14:                       */
    10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
    `SC_WRK16CAT_DSBL /*CFG17-16:                       */
}
), .cy_dpconfig_b(
{
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:     do nothing wait state, copy A0 into A1*/
    `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:     mod bit is high, increment A0 -> A0*/
    `CS_ALU_OP__SUB, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:     mod bit is low, decrement A0 ->A0*/
    `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP___SR, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:     shift A1 right*/
    `CS_ALU_OP__SUB, `CS_SRCA_A0, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:     A0 - A1 ->A0*/
    Enable_Offset == 0 ? `CS_ALU_OP__XOR : `CS_ALU_OP__ADD, `CS_SRCA_A1, `CS_SRCB_D1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5:     invert all bits in A1 -> A1*/
    `CS_ALU_OP__INC, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:     increment A1 ->A1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:     do nothing wait state*/
    8'hFF, 8'h00,  /*CFG9:                       */
    8'hFF, 8'hFF,  /*CFG11-10:                       */
    `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_CHAIN,
    `SC_CI_A_CHAIN, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    `SC_SI_A_DEFSI, /*CFG13-12:                       */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    `SC_SR_SRC_MSB, `SC_FIFO1_BUS, `SC_FIFO0__A1,
    `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_CHNED,
    `SC_CMP0_CHNED, /*CFG15-14:                       */
    10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
    `SC_WRK16CAT_DSBL /*CFG17-16:                       */
}
)) UDB_IIR(
        /*  input                   */  .reset(1'b0),
        /*  input                   */  .clk(Clock),
        /*  input   [02:00]         */  .cs_addr(State[2:0]),
        /*  input                   */  .route_si(1'b0),
        /*  input                   */  .route_ci(1'b0),
        /*  input                   */  .f0_load(Done),
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
        /*  output  [01:00]                  */  .co_msb(),
        /*  output  [01:00]                  */  .cmsb(),
        /*  output  [01:00]                  */  .so(temp),
        /*  output  [01:00]                  */  .f0_bus_stat(),
        /*  output  [01:00]                  */  .f0_blk_stat(),
        /*  output  [01:00]                  */  .f1_bus_stat(),
        /*  output  [01:00]                  */  .f1_blk_stat()
);
//`#end` -- edit above this line, do not edit this line
endmodule



