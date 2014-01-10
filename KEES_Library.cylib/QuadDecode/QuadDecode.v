
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
// Generated on 05/09/2009 at 23:36
// Component: QuadDecode
module QuadDecode (
	Count_Direction,
	Count_Enable,
	Clock,
	QuadA,
	QuadB,
	Reset
);
	output  Count_Direction;
	output  Count_Enable;
	input   Clock;
	input   QuadA;
	input   QuadB;
	input   Reset;

//`#start body` -- edit after this line, do not edit this line
//reg [2:0] quadA_delayed, quadB_delayed;
//always @(posedge clk) quadA_delayed <= {quadA_delayed[1:0], quadA};
//always @(posedge clk) quadB_delayed <= {quadB_delayed[1:0], quadB};
//
//wire count_enable = quadA_delayed[1] ^ quadA_delayed[2] ^ quadB_delayed[1] ^ quadB_delayed[2];
//wire count_direction = quadA_delayed[1] ^ quadB_delayed[2];

reg QuadA_delayed, QuadB_delayed, Count_Enable, Count_Direction;

always @(posedge Clock or posedge Reset) 
begin
    if(Reset)
    begin
        QuadA_delayed <= 1'b0;
    end
    else
    begin
        QuadA_delayed <= QuadA;
    end
end

always @(posedge Clock or posedge Reset) 
begin
    if(Reset)
    begin
        QuadB_delayed <= 1'b0;
    end
    else
    begin
        QuadB_delayed <= QuadB;
    end
end

always @(posedge Clock)
begin
Count_Enable <= QuadA ^ QuadA_delayed ^ QuadB ^ QuadB_delayed;
Count_Direction <= QuadA ^ QuadB_delayed;
end

//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line
