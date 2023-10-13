`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/07 18:42:08
// Design Name: 
// Module Name: EX_MEM
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


module EX_MEM(
input clk,
input resetn,
input [31:0]PC,
input [31:0]IR,
input [31:0]ALUoutput,
input [31:0]B,
input cond,

output reg [31:0]o_PC,
output reg [31:0]o_ALUoutput,
output reg [31:0]o_B,
output reg [31:0]o_IR,
output reg o_cond,
output reg DMEM_wen
    );
    always @(posedge clk) begin
        if (resetn==0)begin
            o_ALUoutput<=0;
            o_B<=0;
            o_IR<=0;
            o_PC<=0;
            o_cond<=0;
        end
        else begin
            o_ALUoutput<=ALUoutput;
            o_B<=B;
            o_IR<=IR;
            o_cond<=cond;
            o_PC<=PC;
            if (IR[31:26]==6'b101011)begin
                DMEM_wen<=1;
            end
            else begin
                DMEM_wen<=0;
            end
        end
        
    end
endmodule
