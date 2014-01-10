
//`#start header` -- edit after this line, do not edit this line
// ========================================
//
// Copyright CYPRESS SEMICONDUCTOR, 2010
// All Rights Reserved
// UNPUBLISHED, LICENSED SOFTWARE.
//
// ========================================
/*******************************************************************************
* File Name: UARTTx_v1_10.v
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
* This component provides a Transmit only UART.  It is designed to be smaller and
* higher performance than the standard UART component.  That is accomplished by
* removing flexibility and from the simplification of only supporting transmit.
* The format of transmission is always 8-N-1 (8-bits, Parity of None, and 1 Stop
* bit).  This component is also specifically designed to work with DMA along with
* standard CPU dataperation.
*
*------------------------------------------------------------------------------
*                 Control and Status Register definitions
*------------------------------------------------------------------------------
*
*  Control Register Definition
*    No Control registers used.  Since the component only has a clock input
*    and will stay in the UART idle state (tx pin high) until the CPU or DMA
*    provides data, there is no need to have an enable signal.
*    
*  Interrupt Status Register Definition
*  +=======+---------+------+------+------+-----+---------+---------+---------+
*  |  Bit  |    7    |  6   |  5   |  4   |  3  |    2    |    1    |    0    |
*  +=======+---------+------+------+------+-----+---------+---------+---------+
*  | Desc  |interrupt|                unused              |  idle   |  n_full |
*  +=======+---------+------+------+------+-----+---------+---------+---------+
*
*    n_full        =>  0 = FIFO not full event has not occured 
*                      1 = FIFO not full event has occured
*
*    idle          =>  0 = Transmitter is not in the idle state
*                      1 = Transmitter is in the idle state
*
********************************************************************************
* Data Path register definitions
********************************************************************************
* dpUART:
* DESCRIPTION: Used to implement the shift register
* REGISTER USAGE:
* F0 => Tx FIFO
* F1 => not used
* D0 => not used
* D1 => not used
* A0 => Shift register
* A1 => not used
*
********************************************************************************
* I*O Signals:
********************************************************************************
*    name              direction       Description
*    clk               input           Clock                      
*    tx                output          UART transmit
*    idle              output          Component in the idle state
*    irq               output          Interrupt request
*    drq               output          DMA request
*
********************************************************************************/
`include "cypress.v"
`ifdef UARTTx_v1_10_V_ALREADY_INCLUDED
`else
`define UARTTx_v1_10_V_ALREADY_INCLUDED

//`#end` -- edit above this line, do not edit this line
// Generated on 10/30/2010 at 19:06
// Component: UARTTx_v1_10
module UARTTx_v1_10 (
	drq,
	idle,
	irq,
	tx,
	clk
);
	output  drq;
	output  idle;
	output  irq;
	output  tx;
	input   clk;

//`#start body` -- edit after this line, do not edit this line

    /***************************************************************************
    *         Wire and Register declarations
    ****************************************************************************/
	reg tx;
	reg [3:0] State;	/* 11 states requires 4-bits */
	wire f0_blk_stat;	/* Set to 1 if the FIFO is empty */
	wire f0_bus_stat;	/* Set to 1 if the FIFO is not full */
	wire so;			/* Shift out value from the DP */
	wire [2:0] cfg;		/* Datapath control store address */

	assign drq = f0_bus_stat;	/* Request DMA when at least one more byte can be accepted */
	
    /***************************************************************************
    *         Instantiation of udb_clock_enable  
    ****************************************************************************
    * The udb_clock_enable primitive component is used to indicate that the input
	* clock must always be synchronous and if not implement synchronizers to make
	* it synchronous.
    */
    wire op_clk;    /* operational clock */
    
    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`TRUE)) ClkSync
    (
        /* input  */    .clock_in(clk),
        /* input  */    .enable(1'b1),
        /* output */    .clock_out(op_clk)
    );                         

    /***************************************************************************
    *       State Machine Implementation                                      
    ****************************************************************************
	* State machine states:
	*    IDLE:
	*      Transmit 1 when idle
	*      On FIFO not empty -> START
	*    START:
	*      Transmit a start bit (0)
	*      Proceed to transmit the data
	*    BIT0 to BIT7:
	*      Transmit the 8 bits in sequence
	*      Proceed to the STOP state
	*    STOP:
	*      Transmit a stop bit (1)
	*      On FIFO not empty -> START
	*      Else go to IDLE
	*/
	localparam UARTTX_STATE_IDLE 	= 4'd0;
	localparam UARTTX_STATE_START 	= 4'd1;
	localparam UARTTX_STATE_BIT0 	= 4'd2;
	localparam UARTTX_STATE_BIT1 	= 4'd3;
	localparam UARTTX_STATE_BIT2 	= 4'd4;
	localparam UARTTX_STATE_BIT3 	= 4'd5;
	localparam UARTTX_STATE_BIT4 	= 4'd6;
	localparam UARTTX_STATE_BIT5 	= 4'd7;
	localparam UARTTX_STATE_BIT6 	= 4'd8;
	localparam UARTTX_STATE_BIT7 	= 4'd9;
	localparam UARTTX_STATE_STOP 	= 4'd10;
	
	always @(posedge op_clk) begin
		case (State) 
			UARTTX_STATE_IDLE:
				if (~f0_blk_stat) State <= UARTTX_STATE_START;
			UARTTX_STATE_START: State <= UARTTX_STATE_BIT0;
			UARTTX_STATE_BIT0: State <= UARTTX_STATE_BIT1;
			UARTTX_STATE_BIT1: State <= UARTTX_STATE_BIT2;
			UARTTX_STATE_BIT2: State <= UARTTX_STATE_BIT3;
			UARTTX_STATE_BIT3: State <= UARTTX_STATE_BIT4;
			UARTTX_STATE_BIT4: State <= UARTTX_STATE_BIT5;
			UARTTX_STATE_BIT5: State <= UARTTX_STATE_BIT6;
			UARTTX_STATE_BIT6: State <= UARTTX_STATE_BIT7;
			UARTTX_STATE_BIT7: State <= UARTTX_STATE_STOP;
			UARTTX_STATE_STOP:
			begin
				if (~f0_blk_stat) State <= UARTTX_STATE_START;
				else State <= UARTTX_STATE_IDLE;
			end
			default: State <= UARTTX_STATE_IDLE;
		endcase
	end
	
	always @(posedge op_clk) begin
		case (State)
			UARTTX_STATE_IDLE,
			UARTTX_STATE_STOP: tx <= 1'b1;
			UARTTX_STATE_START: tx <= 1'b0;
			UARTTX_STATE_BIT0,
			UARTTX_STATE_BIT1,
			UARTTX_STATE_BIT2,
			UARTTX_STATE_BIT3,
			UARTTX_STATE_BIT4,
			UARTTX_STATE_BIT5,
			UARTTX_STATE_BIT6,
			UARTTX_STATE_BIT7: tx <= so; 
			default: tx <= 1'b1;
		endcase
	end

	/* Datapath Configuration addresses */
	localparam UARTTX_CONFIG_LOAD   	= 3'd0;		/* Load from the FIFO */
	localparam UARTTX_CONFIG_SHIFT 	= 3'd1;		/* Shift a bit out (also used when idle) */
	
	/* Load during the START bit and then shift the data out */
	assign cfg = (State == UARTTX_STATE_START) ? UARTTX_CONFIG_LOAD : UARTTX_CONFIG_SHIFT;
	
    /***************************************************************************
    *       Status Register Implementation                                      
    ***************************************************************************/   
    /*    RX Status Register bit location (bits 6-2 unused)    */
    localparam UARTTX_NOT_FULL    = 3'd0;
    localparam UARTTX_IDLE        = 3'd1;

	assign idle = (State == UARTTX_STATE_IDLE);

    wire [6:0] status_val;
    assign status_val[UARTTX_NOT_FULL]    = f0_bus_stat; 
    assign status_val[UARTTX_IDLE]        = idle;
    assign status_val[6:2] = 5'b0;      /* Unused bits of status */

    /* Instantiation of status register*/
    cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h00), .cy_int_mask(7'h00)) StsReg
    (
        /* input          */  .clock(op_clk),
        /* input  [06:00] */  .status(status_val),
        /* output         */  .interrupt(irq)      
    );
	
    /***************************************************************************
    *       Datapath Implementation                                      
    ***************************************************************************/   
	cy_psoc3_dp8 #(.cy_dpconfig_a(
	{
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CFGRAM0: Load */
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP___SR, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CFGRAM1: Shift */
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CFGRAM2:  */
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CFGRAM3:  */
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CFGRAM4:  */
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CFGRAM5:  */
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CFGRAM6:  */
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CFGRAM7:  */
		  8'hFF, 8'h00,	/*CFG9:  */
		  8'hFF, 8'hFF,	/*CFG11-10:  */
		`SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
		`SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
		`SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
		`SC_SI_A_DEFSI, /*CFG13-12:  */
		`SC_A0_SRC_ACC, `SC_SHIFT_SR, 1'h0,
		1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
		`SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
		`SC_FB_NOCHN, `SC_CMP1_NOCHN,
		`SC_CMP0_NOCHN, /*CFG15-14:  */
		 10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
		`SC_FIFO_LEVEL,`SC_FIFO_ASYNC,`SC_EXTCRC_DSBL,
		`SC_WRK16CAT_DSBL /*CFG17-16:  */
	})) dpUART(
		/*  input                   */  .clk(op_clk),
		/*  input   [02:00]         */  .cs_addr(cfg),
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
		/*  output                  */  .so(so),
		/*  output                  */  .f0_bus_stat(f0_bus_stat),
		/*  output                  */  .f0_blk_stat(f0_blk_stat),
		/*  output                  */  .f1_bus_stat(),
		/*  output                  */  .f1_blk_stat()
	);

//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
`endif /* UARTTx_v1_10_V_ALREADY_INCLUDED */
//`#end` -- edit above this line, do not edit this line

