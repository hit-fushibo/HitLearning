`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/07 18:41:26
// Design Name: 
// Module Name: ALU
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


module ALU(
input [10:0]OP_code,
input [31:0]rs,
input [31:0]rt,
output reg [31:0]ALU_output,
output reg Cond,
output reg Zero,
output reg Cout
    );
    reg [5:0] OPcode;
    reg [4:0] sa;
    always @(*) begin
        OPcode=OP_code[5:0];
        sa=OP_code[10:6];
        Cond=0;
        Cout=0;
        Zero=0;
        case (OPcode)
            6'b100000:
            begin
                {Cout,ALU_output}=rs+rt;

            end
            6'b100010:
            begin
                {Cout,ALU_output}=rs-rt;
            end 
            6'b100100:
            begin
                ALU_output=rs&rt;

            end 
            6'b100101:
            begin
                ALU_output=rs|rt;

            end 
            6'b100110:
            begin
                ALU_output=rs^rt;
            end 
            6'b101010:
            begin
                if(rs<rt)begin
                    ALU_output=1;
                end
                else begin
                    ALU_output=0;
                end 
            end 
            6'b001010:
            begin
                if(rt==0)begin
                    ALU_output=rs;
                end
                else begin
                    Cond=1;
                end 
            end 
            6'b000000:
            begin
                ALU_output=rt<<sa;
            end  
        endcase
        if(ALU_output==0)begin
            Zero=1;
        end
        else begin
            Zero=0;
        end
    end
endmodule
