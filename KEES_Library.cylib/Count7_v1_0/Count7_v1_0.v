
//`#start header` -- edit after this line, do not edit this line
// ========================================
//
// Copyright CYPRESS SEMICONDUCTOR, 2010
// All Rights Reserved
// UNPUBLISHED, LICENSED SOFTWARE.
//
// ========================================
/*******************************************************************************
* File Name: Count7_v1_0.v
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
* This component provides access to the hardware primitive 7-bit down counter
* which is referred to in the hardware documentation as a "count7".  This
* hardware primitive uses a Control Register and portions of a Status Register
* (depends on settings for RoutedEnable and RoutedLoad) to implement a 7-bit
* down counter with programmable period value.
*
********************************************************************************
* I*O Signals:
********************************************************************************
*    name              direction       Description
*    clk               input           Clock                 
*    en                input		   Level sensitive enable signal
*    load              input           Level sensitive load signal (load period)
*    reset             input           Async reset signal
*    count[6:0]        output          Counter value
*    tc                output          Terminal count.  Active on the cycle after
*                                      count is equal to 0.
*
********************************************************************************/
`include "cypress.v"
`ifdef Count7_v1_0_V_ALREADY_INCLUDED
`else
`define Count7_v1_0_V_ALREADY_INCLUDED
//`#end` -- edit above this line, do not edit this line
// Generated on 12/27/2010 at 09:52
// Component: Count7_v1_0
module Count7_v1_0 (
	count,
	tc,
	clk,
	en,
	load,
	reset
);
	output [6:0] count;
	output  tc;
	input   clk;
	input   en;
	input   load;
	input   reset;
	parameter Period = 127;
	parameter RoutedEnable = 0;
	parameter RoutedLoad = 0;

//`#start body` -- edit after this line, do not edit this line

    cy_psoc3_count7 #(.cy_period(Period), 
					  .cy_route_ld(RoutedLoad), 
					  .cy_route_en(RoutedEnable)) Count7
    (
        /*  input             */  .clock(clk),
        /*  input             */  .reset(reset),
        /*  input             */  .load(load),
        /*  input             */  .enable(en),
        /*  output  [06:00]   */  .count(count),
        /*  output            */  .tc(tc)
    );

//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
`endif /* Count7_v1_0_V_ALREADY_INCLUDED */
//`#end` -- edit above this line, do not edit this line
