`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/08/28 17:56:03
// Design Name: 
// Module Name: MUX_sim
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module MUX_sim(

    );
    reg [1:0] d0;
    reg [1:0] d1;
    reg select;
    wire [1:0]out;
    MUX MUX1(
    .d0(d0),
    .d1(d1),
    .select(select),
    .out(out)
    
    );
    
initial
begin
    d0=2'b10;
    d1=2'b01;
    select=0;
    #500;
    select=1;
    #500;

end
endmodule
