
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
// Generated on 11/28/2012 at 15:09
// Component: KEES_UDBSumCompare_v1_00
module KEES_UDBSumCompare_v1_00 (
	output reg  Compare,
	input   Calculate,
	input   Clock,
    output State_0,
    output State_1,
    output State_2,
    output Compare_non_reg,
    output SumComplete,
    output reg CDet
);

//`#start body` -- edit after this line, do not edit this line

    parameter [2:0] Beta = "3'b000";
	
//`#start body` -- edit after this line, do not edit this line

//State Machine Variables
	localparam STATE_0 	= 4'h0; 				// Wait for rising edge of Calculate
	localparam STATE_1 	= 4'h1;  				// Add A0 and D0, store in A0
	localparam STATE_2 	= 4'h2;	 				// Add A1 and D1, store in A1
	localparam STATE_3 	= 4'h3;  				// Compare A0 and A1, register the output, wait for calcalate to go low
	localparam STATE_4 	= 4'h4;  				// 
    localparam STATE_5 	= 4'h5;  				// 
    localparam STATE_6 	= 4'h6;  				// 
    localparam STATE_7 	= 4'h7;  				// 

    reg [2:0] State;        // current state, drives config ram for datapath
    reg Sign;               // stores the sign of the shifted result for sign magnitude conversion
    wire comp;              // output of the datapath A1 < A0 Compare
    wire FifoStat;           // if fifo not empty, assert SumComplete
    reg capture;            // signal to force the fifo to capture the result of A0 + A1 for RSSI
    assign State_0 = State[0];
    assign State_1 = State[1];
    assign State_2 = State[2];
    
    assign Compare_non_reg = comp;
    assign SumComplete = capture;
    
    always @(posedge Clock)
    begin
        Compare <= Compare;
        capture <= 1'b0;
        CDet <= CDet;
        case(State)
            STATE_0:  // wait for sample_clock to go high
            begin 
                if(Calculate == 1)
                begin
                    State <= STATE_1;
                end
                else
                begin
                    State <= STATE_0;
                end
            end
            
            STATE_1:  // Add A0 to D0, store in A0
            begin
                State <= STATE_2;
            end
            
            STATE_2:  // Add A1 to D1, store in A1
            begin
                State <= STATE_3;
            end
            
            STATE_3:  // compare A1 < A0, register output, divide A0 -> A0
            begin
                Compare <= comp;
                State <= STATE_4;
            end
            
            STATE_4:  // divide A1 -> A1
            begin
                State <= STATE_5;
            end
            
            STATE_5:  // Sum A0 and A1, load the result into the FIFO, load D1 with the contents of F1 for carrier detect comparison
            begin
                capture <= 1'b1;
                State <= STATE_6;
            end
            
            STATE_6:  // compare A1 < A0 and register for carrier detect
            begin
                CDet <= comp;
                if(Calculate == 0)
                begin
                    State <= STATE_0;
                end
                else
                begin
                    State <= STATE_6;
                end
            end
            
            STATE_7:
            begin
                State <= STATE_0;
            end
            
        endcase
    end

//`#end` -- edit above this line, do not edit this line
cy_psoc3_dp8 #(.cy_dpconfig_a(
{
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:      do nothing wait state*/
    `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:      add A0 and D0 -> A0*/
    `CS_ALU_OP__ADD, `CS_SRCA_A1, `CS_SRCB_D1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:      add A1 and D1 -> A1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A1,
    `CS_SHFT_OP___SR, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:     divide A0 by 2 to prevent overflow*/
    `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_A1,
    `CS_SHFT_OP___SR, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:     divide A1 by 2 to prevent overflow*/
    `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC___F1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5:   A0 +A1 ->A0,F0, F1 - A1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:  compare A0 and A1, for CD*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:      */
    8'hFF, 8'h00,  /*CFG9:      */
    8'hFF, 8'hFF,  /*CFG11-10:      */
    `SC_CMPB_A1_A0, `SC_CMPA_A1_A0, `SC_CI_B_ARITH,
    `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    `SC_SI_A_DEFSI, /*CFG13-12:      */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, `SC_PI_DYN_DS,
    1'h0, `SC_FIFO1_BUS, `SC_FIFO0_ALU,
    `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_NOCHN,
    `SC_CMP0_NOCHN, /*CFG15-14:      */
    10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
    `SC_WRK16CAT_DSBL /*CFG17-16:      */
}
)) SumCompare(
        /*  input                   */  .reset(1'b0),
        /*  input                   */  .clk(Clock),
        /*  input   [02:00]         */  .cs_addr(State),
        /*  input                   */  .route_si(1'b0),
        /*  input                   */  .route_ci(1'b0),
        /*  input                   */  .f0_load(capture),
        /*  input                   */  .f1_load(1'b0),
        /*  input                   */  .d0_load(1'b0),
        /*  input                   */  .d1_load(1'b0),
        /*  output                  */  .ce0(),
        /*  output                  */  .cl0(),
        /*  output                  */  .z0(),
        /*  output                  */  .ff0(),
        /*  output                  */  .ce1(),
        /*  output                  */  .cl1(comp),
        /*  output                  */  .z1(),
        /*  output                  */  .ff1(),
        /*  output                  */  .ov_msb(),
        /*  output                  */  .co_msb(),
        /*  output                  */  .cmsb(),
        /*  output                  */  .so(),
        /*  output                  */  .f0_bus_stat(FifoStat),
        /*  output                  */  .f0_blk_stat(),
        /*  output                  */  .f1_bus_stat(),
        /*  output                  */  .f1_blk_stat()
);
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line






