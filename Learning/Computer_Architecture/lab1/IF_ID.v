`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/07 18:42:08
// Design Name: 
// Module Name: IF_ID
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


module IF_ID(
input clk,
input resetn,
input [31:0] PC,
input stall,
input [31:0]IR,
input [31:0]NPC,
output reg [31:0]O_IR,
output reg [31:0]O_NPC,
output reg [31:0]o_PC
    );
    
    always @(posedge clk) begin
        if(resetn==0)begin
            O_IR=32'b0;
            O_NPC=32'b0;
        end
        else begin
            if(stall==1)begin
                O_IR=32'b0;
                O_NPC=32'b0;
                o_PC=0;
            end
            else begin
                O_IR=IR;
                O_NPC=NPC;
                o_PC=PC;
            end 
        end
    end
endmodule
