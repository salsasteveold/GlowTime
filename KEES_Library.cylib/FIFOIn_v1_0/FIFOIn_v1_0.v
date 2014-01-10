
//`#start header` -- edit after this line, do not edit this line
// ========================================
//
// Copyright CYPRESS SEMICONDUCTOR, 2010
// All Rights Reserved
// UNPUBLISHED, LICENSED SOFTWARE.
//
// ========================================
/*******************************************************************************
* File Name: FIFOIn_v1_0.v
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
* This component provides a convenient interface from programmable hardware to
* the CPU or DMA.  That interface is implemented using the 4-entry FIFO in the
* UDB.
*
*------------------------------------------------------------------------------
*                 Control and Status Register definitions
*------------------------------------------------------------------------------
*
*  Control Register Definition
*  +=====+-------+-------+-------+--------+--------+-------+--------+--------+
*  | Bit |   7   |   6   |   5   |   4    |   3    |   2   |   1    |   0    |
*  +=====+-------+-------+-------+--------+--------+-------+--------+--------+
*  |Desc |                           unused                         | enable | 
*  +=====+-------+-------+-------+--------+--------+-------+--------+--------+
*
*    enable       =>   0 = disable component
*                      1 = enable component
*    
*  Interrupt Status Register Definition
*  +=======+---------+------+------+------+-----+---------+---------+---------+
*  |  Bit  |    7    |  6   |  5   |  4   |  3  |    2    |    1    |    0    |
*  +=======+---------+------+------+------+-----+---------+---------+---------+
*  | Desc  |interrupt|                unused              | n_empty | overflow|
*  +=======+---------+------+------+------+-----+---------+---------+---------+
*
*    n_empty       =>  0 = FIFO not empty event has not occured 
*                      1 = FIFO not empty event has occured
*
*    overflow      =>  0 = FIFO overflow event has not occured
*                      1 = FIFO overflow event has occured
*
********************************************************************************
* Data Path register definitions
********************************************************************************
* FIFOIn: dpLsb and dpMsb
* DESCRIPTION: Used to implement the two bytes of FIFO
* REGISTER USAGE:
* F0 => FIFO Used
* F1 => not used
* D0 => not used
* D1 => not used
* A0 => not used
* A1 => not used
*
********************************************************************************
* I*O Signals:
********************************************************************************
*    name              direction       Description
*    clk               input           Clock                      
*    d_lsb[7:0]        input           Least significant byte of data to capture  
*    d_msb[7:0]        input           Most significant byte of data to capture  
*    en                input           Enable capture
*    full              output          FIFO full indicator
*    irq               output          Interrupt request
*    drq               output          DMA request
*
********************************************************************************/
`include "cypress.v"
`ifdef FIFOIn_v1_0_V_ALREADY_INCLUDED
`else
`define FIFOIn_v1_0_V_ALREADY_INCLUDED

//`#end` -- edit above this line, do not edit this line
// Generated on 10/10/2010 at 20:39
// Component: FIFOIn_v1_0
module FIFOIn_v1_0 (
	drq,
	full,
	irq,
	clk,
	d_lsb,
	d_msb,
	en
);
	output  drq;
	output  full;
	output  irq;
	input   clk;
	input  [7:0] d_lsb;
	input  [7:0] d_msb;
	input   en;
	parameter BitWidth = 8;
	parameter EdgeEnable = 0;

//`#start body` -- edit after this line, do not edit this line

    /***************************************************************************
    *               Parameters                                                 *
    ***************************************************************************/
    localparam BIT_WIDTH_16 = 16;
    localparam BIT_WIDTH_8  = 8;
  
	/***************************************************************************
    *            Device Family and Silicon Revision definitions 
    ***************************************************************************/   
    
    /* PSoC3 ES2 or earlier */
    localparam PSOC3_ES2  = ((`CYDEV_CHIP_MEMBER_USED   == `CYDEV_CHIP_MEMBER_3A) && 
                             (`CYDEV_CHIP_REVISION_USED <= `CYDEV_CHIP_REVISION_3A_ES2));
    /* PSoC5 ES1 or earlier */                        
    localparam PSOC5_ES1  = ((`CYDEV_CHIP_MEMBER_USED   == `CYDEV_CHIP_MEMBER_5A) && 
                             (`CYDEV_CHIP_REVISION_USED <= `CYDEV_CHIP_REVISION_5A_ES1));
    
    /***************************************************************************
    *         Instantiation of udb_clock_enable  
    ****************************************************************************
    * The udb_clock_enable primitive component is used to indicate that the input
	* clock must always be synchronous and if implement synchronizers to make it
	* synchronous.
    */
    wire op_clk;    /* operational clock */
    
    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`TRUE)) ClkSync
    (
        /* input  */    .clock_in(clk),
        /* input  */    .enable(1'b1),
        /* output */    .clock_out(op_clk)
    );                         

    /***************************************************************************
    *       Control Register Implementation                                      
    ***************************************************************************/   
    wire [7:0] ctrl;
    /* Control Register bit location (bits 7-1 are unused) */
    localparam FIFOIN_CTRL_ENABLE      = 3'd0;
	wire enable_ctl;
	reg enable_ctl_reg;
    
    /* ES3 has a clock signal integrated */
    generate
    if(PSOC3_ES2 || PSOC5_ES1)
    begin: AsyncCtl
        cy_psoc3_control #(.cy_force_order(1)) ControlReg
        (
            /* output [07:00] */  .control(ctrl)
        );
		
		always @(posedge op_clk)
		begin
			enable_ctl_reg <= ctrl[FIFOIN_CTRL_ENABLE];
		end
		assign enable_ctl = enable_ctl_reg;
    end /* AsyncCtl */
    else
    begin: SyncCtl
        cy_psoc3_control #(.cy_force_order(1), .cy_ctrl_mode_1(8'h00), .cy_ctrl_mode_0(8'h01)) ControlReg
        (
            /*  input         */  .clock(op_clk),
            /* output [07:00] */  .control(ctrl)
        );
		assign enable_ctl = ctrl[FIFOIN_CTRL_ENABLE];
    end /* SyncCtl */
    endgenerate

    /***************************************************************************
    *       Status Register Implementation                                      
    ***************************************************************************/   
    /*    RX Status Register bit location (bits 6-2 unused)    */
    localparam FIFOIN_FIFO_OVERFLOW    = 3'd0;
    localparam FIFOIN_NOT_EMPTY        = 3'd1;
    
	/* Not empty flag is taken from just the LSB FIFO.  Both FIFOs are written at
	 * the same time and then both are read before checking the status again */
    wire fifo_not_empty;
    wire fifo_overflow;
    wire [6:0] status_val;
    assign status_val[FIFOIN_FIFO_OVERFLOW]    = fifo_overflow; 
    assign status_val[FIFOIN_NOT_EMPTY]        = fifo_not_empty; 
    assign status_val[6:2] = 5'b0;      /* Unused bits of status */
        
    /* Instantiation of Rx status register*/
    cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h01), .cy_int_mask(7'h00)) StsReg
    (
        /* input          */  .clock(op_clk),
        /* input  [06:00] */  .status(status_val),
        /* output         */  .interrupt(irq)      
    );

    /***************************************************************************
    *       Logic Implementation                                      
    ***************************************************************************/   
	/* Consider the FIFO to be full if either of the FIFOs are full.  The full
	 * flag is used to indicate whether to stop writing to the FIFO.  The FIFO
	 * should not be written if either of the FIFOs is full. */
	wire lsb_f0_blk_stat;
	wire msb_f0_blk_stat;
    generate
        if(BitWidth == BIT_WIDTH_8)
        begin: Full8
			assign full = lsb_f0_blk_stat;
		end
		else
		begin: Full16
			assign full = lsb_f0_blk_stat | msb_f0_blk_stat;
		end
	endgenerate
	
	/* en is either level triggered or edge triggered */
	wire en_internal;
	generate
		if(EdgeEnable)
		begin: enEdge
			reg last_en;
			always @(posedge op_clk)
			begin
				last_en <= en;
			end
			assign en_internal = en & ~last_en;
		end
		else
		begin: enLevel
			assign en_internal = en;
		end
	endgenerate
	
	/* Reads from the FIFO are done based on the FIFO being not empty.
	 * Since reads are done for the full width of the FIFO before checking on 
	 * this status again the flag can be taken from just one of the datapaths. */
	wire f0_bus_stat;
	assign drq = f0_bus_stat;	// Not empty
	assign fifo_not_empty = f0_bus_stat;
	
	// No operation, always pass Parallel In data
	localparam [2:0] FIFOIN_CMD_IDLE = 3'b0;
	wire [2:0] cs_addr;
	
	assign cs_addr = FIFOIN_CMD_IDLE;
	
	wire f0_load;
	assign f0_load = (enable_ctl & en_internal & !full);		// Enabled and not full
	
	assign fifo_overflow = (enable_ctl & en_internal & full);		// Enabled and full

    /***************************************************************************
    *       Datapath Implementation                                      
    ***************************************************************************/   
	// All datapaths use the same configuration
    localparam config = {
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CS_REG0 Comment:IDLE */
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
		`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
		`CS_CMP_SEL_CFGA, /*CS_REG1 Comment: */
		`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
		`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
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
		`SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
		`SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
		`SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
		`SC_SI_A_DEFSI, /*SC_REG6 Comment: */
		`SC_A0_SRC_PIN, `SC_SHIFT_SL, 1'b0,
		1'b0, `SC_FIFO1_BUS, `SC_FIFO0_ALU,
		`SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
		`SC_FB_NOCHN, `SC_CMP1_NOCHN,
		`SC_CMP0_NOCHN, /*SC_REG7 Comment: */
		10'h0, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
		`SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
		`SC_WRK16CAT_DSBL /*SC_REG8 Comment: */
    };

	generate
		if(BitWidth == BIT_WIDTH_8)
		begin: Single
			// Single DataPath
			cy_psoc3_dp #(.cy_dpconfig(config)) singleDP
			(
				/* input */ .clk(op_clk), 			// Clock
				/* input [02:00] */ .cs_addr(cs_addr), // Control Store RAM address
				/* input */ .route_si(1'b0), 		// Shift in from routing
				/* input */ .route_ci(1'b0), 		// Carry in from routing
				/* input */ .f0_load(f0_load), 		// Load FIFO 0
				/* input */ .f1_load(1'b0), 		// Load FIFO 1
				/* input */ .d0_load(1'b0), 		// Load Data Register 0
				/* input */ .d1_load(1'b0), 		// Load Data Register 1
				/* output */ .ce0(), 			// Accumulator 0 = Data register 0
				/* output */ .cl0(), 			// Accumulator 0 < Data register 0
				/* output */ .z0(), 			// Accumulator 0 = 0
				/* output */ .ff0(), 			// Accumulator 0 = FF
				/* output */ .ce1(), 			// Accumulator [0|1] = Data register 1
				/* output */ .cl1(), 			// Accumulator [0|1] < Data register 1
				/* output */ .z1(), 			// Accumulator 1 = 0
				/* output */ .ff1(), 			// Accumulator 1 = FF
				/* output */ .ov_msb(), 		// Operation over flow
				/* output */ .co_msb(), 		// Carry out
				/* output */ .cmsb(), 			// Carry out
				/* output */ .so(), 			// Shift out
				/* output */ .f0_bus_stat(f0_bus_stat), 	// FIFO 0 status to uP
				/* output */ .f0_blk_stat(lsb_f0_blk_stat), 	// FIFO 0 status to DP
				/* output */ .f1_bus_stat(), 	// FIFO 1 status to uP
				/* output */ .f1_blk_stat(), 	// FIFO 1 status to DP
				/* input */ .ci(1'b0), 				// Carry in from previous stage
				/* output */ .co(), 			// Carry out to next stage
				/* input */ .sir(1'b0), 			// Shift in from right side
				/* output */ .sor(), 			// Shift out to right side
				/* input */ .sil(1'b0), 			// Shift in from left side
				/* output */ .sol(), 			// Shift out to left side
				/* input */ .msbi(1'b0), 			// MSB chain in
				/* output */ .msbo(), 			// MSB chain out
				/* input [01:00] */ .cei(2'b0), 	// Compare equal in from prev stage
				/* output [01:00] */ .ceo(), 	// Compare equal out to next stage
				/* input [01:00] */ .cli(2'b0), 	// Compare less than in from prv stage
				/* output [01:00] */ .clo(), 	// Compare less than out to next stage
				/* input [01:00] */ .zi(2'b0), 		// Zero detect in from previous stage
				/* output [01:00] */ .zo(), 	// Zero detect out to next stage
				/* input [01:00] */ .fi(2'b0), 		// 0xFF detect in from previous stage
				/* output [01:00] */ .fo(), 	// 0xFF detect out to next stage
				/* input [01:00] */ .capi(2'b0),	// Capture in from previous stage
				/* output [01:00] */ .capo(),		// Capture out to next stage
				/* input */ .cfbi(1'b0), 			// CRC Feedback in from previous stage
				/* output */ .cfbo(), 			// CRC Feedback out to next stage
				/* input [07:00] */ .pi(d_lsb), 		// Parallel data port
				/* output [07:00] */ .po()	 	// Parallel data port
			);
		end
		else
		begin: Dual
    		// Dual DataPath
			wire [14:0] chain;
			cy_psoc3_dp #(.cy_dpconfig(config)) lsbDP
			(
				/* input */ .clk(op_clk), 			// Clock
				/* input [02:00] */ .cs_addr(cs_addr), // Control Store RAM address
				/* input */ .route_si(1'b0), 		// Shift in from routing
				/* input */ .route_ci(1'b0), 		// Carry in from routing
				/* input */ .f0_load(f0_load), 		// Load FIFO 0
				/* input */ .f1_load(1'b0), 		// Load FIFO 1
				/* input */ .d0_load(1'b0), 		// Load Data Register 0
				/* input */ .d1_load(1'b0), 		// Load Data Register 1
				/* output */ .ce0(), 			// Accumulator 0 = Data register 0
				/* output */ .cl0(), 			// Accumulator 0 < Data register 0
				/* output */ .z0(), 			// Accumulator 0 = 0
				/* output */ .ff0(), 			// Accumulator 0 = FF
				/* output */ .ce1(), 			// Accumulator [0|1] = Data register 1
				/* output */ .cl1(), 			// Accumulator [0|1] < Data register 1
				/* output */ .z1(), 			// Accumulator 1 = 0
				/* output */ .ff1(), 			// Accumulator 1 = FF
				/* output */ .ov_msb(), 		// Operation over flow
				/* output */ .co_msb(), 		// Carry out
				/* output */ .cmsb(), 			// Carry out
				/* output */ .so(), 			// Shift out
				/* output */ .f0_bus_stat(f0_bus_stat), 	// FIFO 0 status to uP
				/* output */ .f0_blk_stat(lsb_f0_blk_stat),	// FIFO 0 status to DP
				/* output */ .f1_bus_stat(), 	// FIFO 1 status to uP
				/* output */ .f1_blk_stat(), 	// FIFO 1 status to DP
				/* input */ .ci(), 				// Carry in from previous stage
				/* output */ .co(chain[14]), 			// Carry out to next stage
				/* input */ .sir(1'b0), 			// Shift in from right side
				/* output */ .sor(), 			// Shift out to right side
				/* input */ .sil(chain[12]), 			// Shift in from left side
				/* output */ .sol(chain[13]), 			// Shift out to left side
				/* input */ .msbi(chain[11]), 			// MSB chain in
				/* output */ .msbo(), 			// MSB chain out
				/* input [01:00] */ .cei(2'b0), 	// Compare equal in from prev stage
				/* output [01:00] */ .ceo(chain[10:9]), 	// Compare equal out to next stage
				/* input [01:00] */ .cli(2'b0), 	// Compare less than in from prv stage
				/* output [01:00] */ .clo(chain[8:7]), 	// Compare less than out to next stage
				/* input [01:00] */ .zi(2'b0), 		// Zero detect in from previous stage
				/* output [01:00] */ .zo(chain[6:5]), 	// Zero detect out to next stage
				/* input [01:00] */ .fi(2'b0), 		// 0xFF detect in from previous stage
				/* output [01:00] */ .fo(chain[4:3]), 	// 0xFF detect out to next stage
				/* input [01:00] */ .capi(2'b0),	// Capture in from previous stage
				/* output [01:00] */ .capo(chain[2:1]),		// Capture out to next stage
				/* input */ .cfbi(1'b0), 			// CRC Feedback in from previous stage
				/* output */ .cfbo(chain[0]), 			// CRC Feedback out to next stage
				/* input [07:00] */ .pi(d_lsb), 		// Parallel data port
				/* output [07:00] */ .po()	 	// Parallel data port
			);
			
			cy_psoc3_dp #(.cy_dpconfig(config)) msbDP
			(
				/* input */ .clk(op_clk), 			// Clock
				/* input [02:00] */ .cs_addr(cs_addr), // Control Store RAM address
				/* input */ .route_si(1'b0), 		// Shift in from routing
				/* input */ .route_ci(1'b0), 		// Carry in from routing
				/* input */ .f0_load(f0_load), 		// Load FIFO 0
				/* input */ .f1_load(1'b0), 		// Load FIFO 1
				/* input */ .d0_load(1'b0), 		// Load Data Register 0
				/* input */ .d1_load(1'b0), 		// Load Data Register 1
				/* output */ .ce0(), 			// Accumulator 0 = Data register 0
				/* output */ .cl0(), 			// Accumulator 0 < Data register 0
				/* output */ .z0(), 			// Accumulator 0 = 0
				/* output */ .ff0(), 			// Accumulator 0 = FF
				/* output */ .ce1(), 			// Accumulator [0|1] = Data register 1
				/* output */ .cl1(), 			// Accumulator [0|1] < Data register 1
				/* output */ .z1(), 			// Accumulator 1 = 0
				/* output */ .ff1(), 			// Accumulator 1 = FF
				/* output */ .ov_msb(), 		// Operation over flow
				/* output */ .co_msb(), 		// Carry out
				/* output */ .cmsb(), 			// Carry out
				/* output */ .so(), 			// Shift out
				/* output */ .f0_bus_stat(), 	// FIFO 0 status to uP
				/* output */ .f0_blk_stat(msb_f0_blk_stat),	// FIFO 0 status to DP
				/* output */ .f1_bus_stat(), 	// FIFO 1 status to uP
				/* output */ .f1_blk_stat(), 	// FIFO 1 status to DP
				/* input */ .ci(chain[14]), 				// Carry in from previous stage
				/* output */ .co(), 			// Carry out to next stage
				/* input */ .sir(chain[13]), 			// Shift in from right side
				/* output */ .sor(chain[12]), 			// Shift out to right side
				/* input */ .sil(1'b0), 			// Shift in from left side
				/* output */ .sol(), 			// Shift out to left side
				/* input */ .msbi(1'b0), 			// MSB chain in
				/* output */ .msbo(chain[11]), 			// MSB chain out
				/* input [01:00] */ .cei(chain[10:9]), 	// Compare equal in from prev stage
				/* output [01:00] */ .ceo(), 	// Compare equal out to next stage
				/* input [01:00] */ .cli(chain[8:7]), 	// Compare less than in from prv stage
				/* output [01:00] */ .clo(), 	// Compare less than out to next stage
				/* input [01:00] */ .zi(chain[6:5]), 		// Zero detect in from previous stage
				/* output [01:00] */ .zo(), 	// Zero detect out to next stage
				/* input [01:00] */ .fi(chain[4:3]), 		// 0xFF detect in from previous stage
				/* output [01:00] */ .fo(), 	// 0xFF detect out to next stage
				/* input [01:00] */ .capi(chain[2:1]),	// Capture in from previous stage
				/* output [01:00] */ .capo(),		// Capture out to next stage
				/* input */ .cfbi(chain[0]), 			// CRC Feedback in from previous stage
				/* output */ .cfbo(), 			// CRC Feedback out to next stage
				/* input [07:00] */ .pi(d_msb), 		// Parallel data port
				/* output [07:00] */ .po()	 	// Parallel data port
			);
		end
	endgenerate

//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
`endif /* FIFOIn_v1_0_V_ALREADY_INCLUDED */
//`#end` -- edit above this line, do not edit this line
