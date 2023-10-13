`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/07 18:41:26
// Design Name: 
// Module Name: PC
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


module PC(
input clk,
input resetn,
input [31:0] npc,
input stall,
output reg [31:0] c_pc
    );
        always @(posedge clk) begin
        if(resetn==0) begin
            c_pc<=32'b0;
        end
        else if (stall==1) begin
            c_pc<=npc-4;
        end
        else begin
            c_pc<=npc;
        end
        
    end
endmodule
