`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/09/01 16:01:30
// Design Name: 
// Module Name: cunter
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


module cunter(
    input clk,
    input rst,
    output reg [4:0] T
    );
    always @(posedge clk) begin
        if(!rst) begin
            T<=5'b10000;
        end
        else begin
            T<={T[0],T[4],T[3],T[2],T[1]};
        end
        
    end

endmodule
