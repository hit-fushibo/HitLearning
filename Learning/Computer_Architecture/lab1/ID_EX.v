`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/07 18:42:08
// Design Name: 
// Module Name: ID_EX
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


module ID_EX(
input clk,
input resetn,

input [31:0]PC,
input [31:0]NPC,
input [31:0]A,
input [31:0]B,
input [31:0]IR,
input [31:0]Imm,

output reg [31:0] o_PC,
output reg [31:0] o_npc,
output reg [31:0] o_A,
output reg [31:0] o_B,
output reg [31:0] o_Imm,
output reg [31:0] o_IR,
output reg [10:0] o_ALUOPcode

    );
    always @(posedge clk) begin
        if (resetn==0) begin
            o_npc<=0;
            o_npc<=0;
            o_A<=0;
            o_B<=0;
            o_Imm<=0;
            o_IR<=0;
            o_PC<=0;
        end
        else begin
            o_npc<=NPC;
            o_A<=A;
            o_B<=B;
            o_Imm<=Imm;
            o_IR<=IR;
            o_PC<=PC;
            if (IR[31:26]==6'b000000)begin
                o_ALUOPcode=IR[10:0];
            end
            if (IR[31:26]==6'b101011||IR[31:26]==6'b100011)begin
                o_ALUOPcode=11'b00000_100000;
            end

        end
    end
endmodule
