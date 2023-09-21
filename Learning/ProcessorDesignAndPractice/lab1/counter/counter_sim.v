`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/08/28 18:43:18
// Design Name: 
// Module Name: counter_sim
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


module counter_sim(

    );
    
    reg clk,reset;
    wire [3:0] T;
    initial begin
    clk=0;
    reset=0;
    #50 reset=1;
    end
    always #5 clk=~clk;
    
    counter u_counter(
    .clk(clk),
    .rst(reset),
    .T(T)
    );
endmodule
