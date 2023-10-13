`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/07 18:42:08
// Design Name: 
// Module Name: MEM_WB
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


module MEM_WB(
input clk,
input resetn,
input [31:0] PC,
input [31:0] LMD,
input [31:0] ALUoutput,
input [31:0] IR,
input MOVZ_cond,

output reg [31:0] o_PC,
output reg [31:0] o_LMD,
output reg [31:0] o_ALUoutput,
output reg [31:0] o_IR,
output reg [5:0] wb_addr,
output reg reg_wen
    );
    always @(posedge clk) begin
        if (resetn==0)begin
            o_PC<=0;
            o_LMD<=0;
            o_ALUoutput<=0;
            o_IR<=0;
            reg_wen<=0;
        end
        else begin
            o_PC<=PC;
            o_LMD<=LMD;
            o_ALUoutput<=ALUoutput;
            o_IR<=IR;
            if (IR[31:26]==6'b100011 || (IR[31:26]==6'b000000 && IR[10:0]!=11'b00000_001010) || (IR[31:26]==6'b000000 && IR[10:0]==11'b00000_001010 && MOVZ_cond==1))begin
                reg_wen<=1;
                if(IR[31:26]==6'b100011)begin
                    wb_addr=IR[20:16];
                end
                if(IR[31:26]==6'b000000)begin
                    wb_addr=IR[15:11];
                end
            end
            else begin
                reg_wen<=0;
            end  
        end
        
    end

endmodule
